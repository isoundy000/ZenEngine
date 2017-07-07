#include "zcCore.h"
#include <DXGI.h>
#include <DXGI1_4.h>

namespace zcGfx
{

//! @todo 2 temp until final location found
DescriptorRangeSRV			gNullSRVView;
DescriptorRangeSRV			gNullUAVView;
DescriptorRangeSRV			gNullCBVView;
DX12QueryDisjoint::List		DX12QueryDisjoint::slstQueryCreated;
DX12QueryTimestamp::List	DX12QueryTimestamp::slstQueryCreated;

DX12QueryDisjoint::DX12QueryDisjoint()
{
#if !ZEN_RENDERER_DX12
	D3D12_QUERY_DESC QueryDesc;
	QueryDesc.Query		= D3D11_QUERY_TIMESTAMP_DISJOINT;
	QueryDesc.MiscFlags	= 0;
	HRESULT result		= zcMgr::GfxRender.DX12GetDevice()->CreateQuery(&QueryDesc, &mpDX12Query);
	zenAssert(result == S_OK);
#endif
	slstQueryCreated.PushHead(*this);
}

void DX12QueryDisjoint::ReferenceDeleteCB()
{
	slstQueryCreated.PushHead(*this);
} 

void DX12QueryDisjoint::Start()
{
#if !ZEN_RENDERER_DX12
	muFrameStop				= zUInt(-1);
	mbValidResult			= false;
	mDisjointInfo.Disjoint	= true;
	zcMgr::GfxRender.DX12GetDeviceContext()->Begin(mpDX12Query);	
#endif
}

void DX12QueryDisjoint::Stop()
{
#if !ZEN_RENDERER_DX12
	if( muFrameStop )
	{
		muFrameStop	= zcMgr::GfxRender.GetFrameRendered();
		zcMgr::GfxRender.DX12GetDeviceContext()->End(mpDX12Query);
	}
#endif
}

zU64 DX12QueryDisjoint::GetClockRate()
{
#if !ZEN_RENDERER_DX12
	zenAssertMsg(muFrameStop != zUInt(-1), "Query need to be started and stopped before we get results back");
	zenAssertMsg(muFrameStop < zcMgr::GfxRender.GetFrameRendered(), "Must wait a complete frame before getting results");
	if( !mbValidResult ) 
	{		
		HRESULT result	= zcMgr::GfxRender.DX12GetDeviceContext()->GetData(mpDX12Query, &mDisjointInfo, sizeof(mDisjointInfo), 0);
		mbValidResult	= (result == S_OK);
	}
#endif
	return mDisjointInfo.Disjoint ? 0 : mDisjointInfo.Frequency;
}

zEngineRef<DX12QueryDisjoint> DX12QueryDisjoint::Create()
{	
	const zUInt uGrowSize = 8;
	if( slstQueryCreated.IsEmpty() )
	{
		for(zUInt idx(0); idx<uGrowSize; ++idx)
			zenNewDefault DX12QueryDisjoint();
	}
	return slstQueryCreated.PopTail();
}

DX12QueryTimestamp::DX12QueryTimestamp()
{
#if !ZEN_RENDERER_DX12
	D3D11_QUERY_DESC QueryDesc;
	QueryDesc.Query		= D3D11_QUERY_TIMESTAMP;
	QueryDesc.MiscFlags	= 0;
	HRESULT result		= zcMgr::GfxRender.DX12GetDevice()->CreateQuery(&QueryDesc, &mpDX12Query);
	zenAssert(result == S_OK);
#endif
	slstQueryCreated.PushHead(*this);
}

void DX12QueryTimestamp::ReferenceDeleteCB()
{
	if( mrQueryDisjoint.IsValid() )
	{
		zU64 uDiscard = GetTimestampUSec(); // This prevents DX warning about starting a new query(when query reused), without having retrieved the value first
		mrQueryDisjoint	= nullptr;
		mbValidResult	= false;
	}
	slstQueryCreated.PushHead(*this);
}

zU64 DX12QueryTimestamp::GetTimestampUSec()
{	
#if !ZEN_RENDERER_DX12
	if( mbValidResult == false )
	{
		zU64 uClockRate = mrQueryDisjoint->GetClockRate();		
		if( uClockRate != 0 )
		{
			zcMgr::GfxRender.DX12GetDeviceContext()->GetData(mpDX12Query, &muTimestamp, sizeof(muTimestamp), 0);
			muTimestamp		= uClockRate ? (muTimestamp*1000*1000/uClockRate) : 0;
			mbValidResult	= true;
		}
	}
#endif
	return muTimestamp;
}

zEngineRef<DX12QueryTimestamp> DX12QueryTimestamp::Create()
{	
#if !ZEN_RENDERER_DX12
	const zUInt uGrowSize = 128;
	if( slstQueryCreated.IsEmpty() )
	{
		for(zUInt idx(0); idx<uGrowSize; ++idx)
			zenNewDefault DX12QueryTimestamp();
	}

	DX12QueryTimestamp* pQuery	= slstQueryCreated.PopTail();
	pQuery->mrQueryDisjoint		= zcMgr::GfxRender.GetQueryDisjoint();
	pQuery->mbValidResult		= false;
	pQuery->muTimestamp			= 0;
	zcMgr::GfxRender.DX12GetDeviceContext()->End(pQuery->mpDX12Query);
	return pQuery;
#else
	return slstQueryCreated.PopTail();
#endif
}

// Helper function for acquiring the first available hardware adapter that supports Direct3D 12.
// If no such adapter can be found, *ppAdapter will be set to nullptr.
void GetHardwareAdapter(IDXGIFactory2* pFactory, IDXGIAdapter1** ppAdapter)
{
	Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
	*ppAdapter = nullptr;

	for (UINT adapterIndex = 0; DXGI_ERROR_NOT_FOUND != pFactory->EnumAdapters1(adapterIndex, &adapter); ++adapterIndex)
	{
		DXGI_ADAPTER_DESC1 desc;
		adapter->GetDesc1(&desc);

		if (desc.Flags & DXGI_ADAPTER_FLAG_SOFTWARE)
		{
			// Don't select the Basic Render Driver adapter.
			// If you want a software adapter, pass in "/warp" on the command line.
			continue;
		}

		// Check to see if the adapter supports Direct3D 12, but don't create the
		// actual device yet.
		if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_11_0, _uuidof(ID3D12Device), nullptr)))
		{
			break;
		}
	}

	*ppAdapter = adapter.Detach();
}

bool ManagerRender_DX12::Load()
{	
	HRESULT hr	= S_OK;
	
	//-------------------------------------------------------------------------
	// Configure Texture Format mapping
	//-------------------------------------------------------------------------
	zenMem::Set(meFormatConv,			DXGI_FORMAT_UNKNOWN, sizeof(meFormatConv) );	
	zenMem::Set(meFormatConvTypeless,	DXGI_FORMAT_UNKNOWN, sizeof(meFormatConvTypeless) );	
	zenMem::Set(meFormatConvDepthDSV,	DXGI_FORMAT_UNKNOWN, sizeof(meFormatConvDepthDSV) );	
	zenMem::Set(meFormatConvDepthSRV,	DXGI_FORMAT_UNKNOWN, sizeof(meFormatConvDepthSRV) );	
	zenMem::Set(meFormatConvStencilSRV, DXGI_FORMAT_UNKNOWN, sizeof(meFormatConvStencilSRV) );	
	
	// Surface formats
	meFormatConv[zenConst::keTexFormat_R8]				= DXGI_FORMAT_R8_UNORM;	
	meFormatConv[zenConst::keTexFormat_RGB8]			= DXGI_FORMAT_R10G10B10A2_UNORM;
	meFormatConv[zenConst::keTexFormat_RGBA8]			= DXGI_FORMAT_R8G8B8A8_UNORM;
	meFormatConv[zenConst::keTexFormat_D24S8]			= DXGI_FORMAT_D24_UNORM_S8_UINT;
	meFormatConv[zenConst::keTexFormat_D32]				= DXGI_FORMAT_D32_FLOAT;
	meFormatConv[zenConst::keTexFormat_BC1]				= DXGI_FORMAT_BC1_UNORM;	
	meFormatConv[zenConst::keTexFormat_BC2]				= DXGI_FORMAT_BC2_UNORM;
	meFormatConv[zenConst::keTexFormat_BC3]				= DXGI_FORMAT_BC3_UNORM;
	meFormatConv[zenConst::keTexFormat_BC5]				= DXGI_FORMAT_BC5_UNORM;
	meFormatConv[zenConst::keTexFormat_BC7]				= DXGI_FORMAT_BC7_UNORM;
	meFormatConv[zenConst::keTexFormat_RGBA32f]			= DXGI_FORMAT_R32_FLOAT;
	
	// Typeless format
	meFormatConvTypeless[zenConst::keTexFormat_R8]		= DXGI_FORMAT_R8_TYPELESS;	
	meFormatConvTypeless[zenConst::keTexFormat_RGB8]	= DXGI_FORMAT_UNKNOWN;
	meFormatConvTypeless[zenConst::keTexFormat_RGBA8]	= DXGI_FORMAT_R8G8B8A8_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_D24S8]	= DXGI_FORMAT_R24G8_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_D32]		= DXGI_FORMAT_R32_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_BC1]		= DXGI_FORMAT_BC1_TYPELESS;	
	meFormatConvTypeless[zenConst::keTexFormat_BC2]		= DXGI_FORMAT_BC2_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_BC3]		= DXGI_FORMAT_BC3_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_BC5]		= DXGI_FORMAT_BC5_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_BC7]		= DXGI_FORMAT_BC7_TYPELESS;
	meFormatConvTypeless[zenConst::keTexFormat_RGBA32f]	= DXGI_FORMAT_R32_TYPELESS;

	// Pending Format to add: DXGI_FORMAT_D32_FLOAT_S8X24_UINT, DXGI_FORMAT_D16_UNORM 
	meFormatConvDepthDSV[zenConst::keTexFormat_D24S8]	= DXGI_FORMAT_D24_UNORM_S8_UINT;
	meFormatConvDepthDSV[zenConst::keTexFormat_D32]		= DXGI_FORMAT_D32_FLOAT;
	// Pending Format to add: DXGI_FORMAT_R32G8X24_TYPELESS, DXGI_FORMAT_R16_UNORM
	meFormatConvDepthSRV[zenConst::keTexFormat_D24S8]	= DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	meFormatConvDepthSRV[zenConst::keTexFormat_D32]		= DXGI_FORMAT_R32_FLOAT;
	// Pending Format to add: DXGI_FORMAT_X32_TYPELESS_G8X24_UINT
	meFormatConvStencilSRV[zenConst::keTexFormat_D24S8]	= DXGI_FORMAT_X24_TYPELESS_G8_UINT;

	PSO_DX12::StaticInitialize();

	//----------------------------------------------------------------------------------------------
	// Create DirectX Device
	//----------------------------------------------------------------------------------------------
	UINT uDxgiFactoryFlags = 0;

	// Enable the D3D12 debug layer.
#if _DEBUG
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&mrDXDebugController))))
	{
		mrDXDebugController->EnableDebugLayer();
		mrDXDebugController->SetEnableGPUBasedValidation(true);
		uDxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
	}	
#endif

	// Create DirectX GI Factory	
	hr = CreateDXGIFactory2(uDxgiFactoryFlags, IID_PPV_ARGS(&mrDXFactory) );
	if( FAILED(hr) )
		return false;
	
	//SF Temp Find first valid GPU
	{
		Microsoft::WRL::ComPtr<IDXGIAdapter1> DrawAdapter;
	#if 1
		GetHardwareAdapter(mrDXFactory.Get(), &DrawAdapter);
	#else
		hr = mrDXFactory->EnumWarpAdapter(IID_PPV_ARGS(&DrawAdapter));
		if( FAILED(hr) )
			return false;
		hr = DrawAdapter.As(&mrDXAdapter);
		if( FAILED(hr) )
			return false;
	//	if(FAILED(mrDXFactory->EnumAdapters1(0, &hardwareAdapter)))
	//		throw "Failed to retrieve default adapter";

	#endif
	}
	
	hr =  D3D12CreateDevice(mrDXAdapter.Get(), D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&mrDXDevice) );
	if( FAILED( hr ) )
		return FALSE;

#if !ZEN_BUILD_FINAL	
	mrDXDevice->SetStablePowerState(TRUE); // Prevent the GPU from overclocking or underclocking to get consistent timings
#endif
	//----------------------------------------------------------------------------------------------
	// Create and initialize Descriptors heap support
	//----------------------------------------------------------------------------------------------
	DescriptorRangeSRV::StaticInit();
	DescriptorRangeRTV::StaticInit();
	DescriptorRangeDSV::StaticInit();
	DescriptorRangeSampler::StaticInit();

	if( !mDescriptorHeapSRV.Load(4096) )
		return false;
	if( !mDescriptorHeapRTV.Load(256) )
		return false;
	if( !mDescriptorHeapDSV.Load(64) )
		return false;
	if( !mDescriptorHeapSampler.Load(1024) )
		return false;

	for(zUInt idx(0); idx<zenArrayCount(maFrameDescriptorHeapSRV); ++idx)
	{
		if( !maFrameDescriptorHeapSRV[idx].Load(muFrameDescriptorCount, D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE) )
			return false;
		maFrameDescriptorSRV[idx] = maFrameDescriptorHeapSRV[idx].Allocate(muFrameDescriptorCount);
	}

	D3D12_SHADER_RESOURCE_VIEW_DESC NullSRVDesc = {};
	NullSRVDesc.Format							= DXGI_FORMAT_R8G8B8A8_UNORM;
	NullSRVDesc.ViewDimension					= D3D12_SRV_DIMENSION_TEXTURE2D;
	NullSRVDesc.Shader4ComponentMapping			= D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
	NullSRVDesc.Texture2D.MipLevels				= 1;
	NullSRVDesc.Texture2D.MostDetailedMip		= 0;
	NullSRVDesc.Texture2D.ResourceMinLODClamp	= 0.0f;
	gNullSRVView								= mDescriptorHeapSRV.Allocate(1);
	zcMgr::GfxRender.GetDevice()->CreateShaderResourceView(nullptr, &NullSRVDesc, gNullSRVView.GetCpu());	

	D3D12_UNORDERED_ACCESS_VIEW_DESC NullUAVDesc= {};
	NullUAVDesc.Format							= zcMgr::GfxRender.ZenFormatToNative(keTexFormat_R8);
	NullUAVDesc.ViewDimension					= D3D12_UAV_DIMENSION_TEXTURE2D;
	NullUAVDesc.Texture2D.MipSlice				= 0;
	NullUAVDesc.Texture2D.PlaneSlice			= 0;
	gNullUAVView								= mDescriptorHeapSRV.Allocate(1);
	zcMgr::GfxRender.GetDevice()->CreateUnorderedAccessView(nullptr, nullptr, &NullUAVDesc, gNullUAVView.GetCpu());

 	D3D12_CONSTANT_BUFFER_VIEW_DESC NullCbvDesc = {};
	NullCbvDesc.BufferLocation					= (D3D12_GPU_VIRTUAL_ADDRESS)0;
 	NullCbvDesc.SizeInBytes						= 0;
 	gNullCBVView								= mDescriptorHeapSRV.Allocate(1);						
	zcMgr::GfxRender.GetDevice()->CreateConstantBufferView(&NullCbvDesc, gNullCBVView.GetCpu());

	//----------------------------------------------------------------------------------------------
	// Create Commandlist/Queue
	//----------------------------------------------------------------------------------------------
	hr = mrDXDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&mrCommandAllocator));
	if( FAILED( hr ) )
		return FALSE;	
	
	// Create the command list.
	DirectXComRef<ID3D12GraphicsCommandList>* pCmdList = &marCommandList[0][0];
	
	for( zUInt idxCmdList(0); idxCmdList< sizeof(marCommandList) / sizeof(DirectXComRef<ID3D12GraphicsCommandList>); ++idxCmdList )
	{
		DirectXComRef<ID3D12GraphicsCommandList> rCmdList;
		mrDXDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, mrCommandAllocator.Get(), nullptr, IID_PPV_ARGS(&rCmdList));
		wchar_t zName[64];
		swprintf_s(zName, L"CommandList %02i", static_cast<int>(idxCmdList) );
		rCmdList->SetName( zName );		
		rCmdList->Close(); // Command lists are created in the recording state but main loop expects it to be closed
		pCmdList[idxCmdList] = rCmdList;
	}

	// Describe and create the command queue.
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	mrDXDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&mrCommandQueue));

	//----------------------------------------------------------------------------------------------
	// Create a root signature 
	//----------------------------------------------------------------------------------------------
	{
		RootSignature::StaticInitialize();
		CD3DX12_DESCRIPTOR_RANGE1 aRanges[3];
        //D3D12_DESCRIPTOR_RANGE_TYPE_SAMPLER	= ( D3D12_DESCRIPTOR_RANGE_TYPE_CBV + 1 ) 
		aRanges[D3D12_DESCRIPTOR_RANGE_TYPE_CBV].Init(D3D12_DESCRIPTOR_RANGE_TYPE_CBV, (UINT)10, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_NONE);
		aRanges[D3D12_DESCRIPTOR_RANGE_TYPE_UAV].Init(D3D12_DESCRIPTOR_RANGE_TYPE_UAV, (UINT) 8, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_NONE);
		aRanges[D3D12_DESCRIPTOR_RANGE_TYPE_SRV].Init(D3D12_DESCRIPTOR_RANGE_TYPE_SRV, (UINT)10, 0, 0, D3D12_DESCRIPTOR_RANGE_FLAG_DESCRIPTORS_VOLATILE/* D3D12_DESCRIPTOR_RANGE_FLAG_DATA_STATIC*/);		

		mRootSignatureDefault = RootSignature( 
			{
				RootSignature::SlotConstant(1,10,0,D3D12_SHADER_VISIBILITY_VERTEX),	//Vertex offset constant
				RootSignature::SlotTable(1, &aRanges[0], D3D12_SHADER_VISIBILITY_VERTEX),
				RootSignature::SlotTable(1, &aRanges[1], D3D12_SHADER_VISIBILITY_VERTEX),
				RootSignature::SlotTable(1, &aRanges[2], D3D12_SHADER_VISIBILITY_VERTEX),
				RootSignature::SlotTable(1, &aRanges[0], D3D12_SHADER_VISIBILITY_PIXEL),
				RootSignature::SlotTable(1, &aRanges[1], D3D12_SHADER_VISIBILITY_PIXEL),
				RootSignature::SlotTable(1, &aRanges[2], D3D12_SHADER_VISIBILITY_PIXEL),
				//RootSignature::SlotTable(3, aRanges, D3D12_SHADER_VISIBILITY_VERTEX),
				//RootSignature::SlotTable(3,	aRanges, D3D12_SHADER_VISIBILITY_PIXEL),				
			}, 
			D3D12_ROOT_SIGNATURE_FLAG_NONE);
	}

	// Command list allocators can only be reset when the associated 
	// command lists have finished execution on the GPU; apps should use 
	// fences to determine GPU execution progress.
	mrCommandAllocator->Reset();

	// However, when ExecuteCommandList() is called on a particular command 
	// list, that command list can then be reset at any time and must be before re-recording.
	marCommandList[0][0]->Reset(mrCommandAllocator.Get(), nullptr);
	
	// Close the command list and execute it to begin the initial GPU setup.
	hr = marCommandList[0][0]->Close();
	if( FAILED(hr) )
		return false;

	ID3D12CommandList* ppCommandLists[] = { marCommandList[0][0].Get() };
	mrCommandQueue->ExecuteCommandLists(_countof(ppCommandLists), ppCommandLists);
	
	//----------------------------------------------------------------------------------------------
	// Create synchronization objects and wait until assets have been uploaded to the GPU.
	//----------------------------------------------------------------------------------------------
	{
		mrDXDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence));
		m_fenceValue = 1;

		// Create an event handle to use for frame synchronization.
		m_fenceEvent = CreateEvent(nullptr, FALSE, FALSE, nullptr);
//		if (m_fenceEvent == nullptr);
		//{
		//	ThrowIfFailed(HRESULT_FROM_WIN32(GetLastError()));
		//}

		// Wait for the command list to execute; we are reusing the same command 
		// list in our main loop but for now, we just want to wait for setup to 
		// complete before continuing.
		WaitForPreviousFrame();
	}

		/*
#if !DISABLE_DX12
	D3D11_INPUT_ELEMENT_DESC EmptyDesc;
	hr = mDX12pContextImmediate->QueryInterface( __uuidof(mDX12pPerf), reinterpret_cast<void**>(&mDX12pPerf) );	
	if( FAILED( hr ) )
		return FALSE;
#endif*/
	return true;
}

bool ManagerRender_DX12::Unload()
{
#if !ZEN_RENDERER_DX12
	if( mDX12pPerf ) 
		mDX12pPerf->Release();
#endif	
	//mrDXCmdQueueDirect.Reset(); //SF Clear/Release?
	mrDXDevice.Reset();
	mrDXFactory.Reset();
#if !ZEN_RENDERER_DX12
	mDX12pPerf				= nullptr;
	mDX12pContextImmediate	= nullptr;
#endif
	
	return true;
}

void ManagerRender_DX12::WaitForPreviousFrame()
{
	// WAITING FOR THE FRAME TO COMPLETE BEFORE CONTINUING IS NOT BEST PRACTICE.
	// This is code implemented as such for simplicity. The D3D12HelloFrameBuffering
	// sample illustrates how to use fences for efficient resource usage and to
	// maximize GPU utilization.

	// Signal and increment the fence value.
	const UINT64 fence = m_fenceValue;
	mrCommandQueue->Signal(m_fence.Get(), fence);
	m_fenceValue++;

	// Wait until the previous frame is finished.
	if (m_fence->GetCompletedValue() < fence)
	{
		m_fence->SetEventOnCompletion(fence, m_fenceEvent);
		WaitForSingleObject(m_fenceEvent, INFINITE);
	}

	//m_frameIndex = m_swapChain->GetCurrentBackBufferIndex();
}

void ManagerRender_DX12::FrameBegin(zcRes::GfxWindowRef _FrameWindow)
{	
	WaitForPreviousFrame();

	// Command list allocators can only be reset when the associated 
	// command lists have finished execution on the GPU; apps should use 
	// fences to determine GPU execution progress.
	mrCommandAllocator->Reset();

	//! @todo 1 support multiple context/cmdlist
	// However, when ExecuteCommandList() is called on a particular command 
	// list, that command list can then be reset at any time and must be before re-recording.
	muFrameDescriptorIndex = 0;
	marCommandList[muFrameRendered%kuFrameBufferCount][0]->Reset(mrCommandAllocator.Get(), nullptr);	
	mGpuContext[0].Reset( mrDXDevice, marCommandList[muFrameRendered%kuFrameBufferCount][0], maFrameDescriptorHeapSRV[muFrameRendered%kuFrameBufferCount].GetHeap() );
	Super::FrameBegin(_FrameWindow);
	
	// Indicate that the back buffer will be used as a render target.
	const zcRes::GfxTarget2DRef& rBackbuffer = grWindowRender->GetBackbuffer();
	mGpuContext[0].GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(rBackbuffer.HAL()->mrResource.Get(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET) );
	
#if !ZEN_RENDERER_DX12
	mrPreviousDrawcall		= nullptr;
	mbProfilerDetected		= mDX12pPerf && mDX12pPerf->GetStatus();
	mrQueryDisjoint			= DX12QueryDisjoint::Create();
	mrQueryDisjoint->Start();
#endif
}

void ManagerRender_DX12::FrameEnd()
{	
	// Indicate that the back buffer will now be used to present.
	if( mrFrameContext.IsValid() )
	{
		mrFrameContext.Submit();
		mrFrameContext = nullptr;
	}

	const zcRes::GfxTarget2DRef& rBackbuffer = grWindowRender->GetBackbuffer();
	mGpuContext[0].GetCommandList()->ResourceBarrier(1, &CD3DX12_RESOURCE_BARRIER::Transition(rBackbuffer.HAL()->mrResource.Get(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT));
	//mrQueryDisjoint->Stop();

	HRESULT hr = mGpuContext[0].GetCommandList()->Close();
	if( SUCCEEDED(hr) )
	{
		ID3D12CommandList* ppCommandLists[] = { marCommandList[muFrameRendered%kuFrameBufferCount][0].Get() };
		mrCommandQueue->ExecuteCommandLists(zenArrayCount(ppCommandLists), ppCommandLists);
		grWindowRender.HAL()->mrDXSwapChain->Present( 0, 0 );	
	
		/*
		DXGI_FRAME_STATISTICS FrameStatistics;
		hr = m_pDXGISwapChain->GetFrameStatistics(&FrameStatistics);

		if (FrameStatistics.PresentCount > m_PreviousPresentCount)
		{
			if (m_PreviousRefreshCount > 0 &&
				(FrameStatistics.PresentRefreshCount - m_PreviousRefreshCount) > (FrameStatistics.PresentCount - m_PreviousPresentCount))
			{
				++m_GlitchCount;
			}
		}
		m_PreviousPresentCount = FrameStatistics.PresentCount;
		m_PreviousRefreshCount = FrameStatistics.SyncRefreshCount;
		*/
	}
	Super::FrameEnd();
}

void ManagerRender_DX12::NamedEventBegin(const zStringHash32& zName)
{
#if !ZEN_RENDERER_DX12
	if( mbProfilerDetected )
	{
		WCHAR zEventName[64];
		mbstowcs_s(nullptr, zEventName, zName.mzName, zenArrayCount(zEventName));
		mDX12pPerf->BeginEvent(zEventName);
	}
#endif
}

void ManagerRender_DX12::NamedEventEnd()
{
#if !ZEN_RENDERER_DX12
	if( mbProfilerDetected )
		mDX12pPerf->EndEvent();
#endif
}

const zEngineRef<DX12QueryDisjoint>& ManagerRender_DX12::GetQueryDisjoint()const
{
	return mrQueryDisjoint;
}

void ManagerRender_DX12::DispatchBarrier(ScopedDrawlist& _Drawlist, bool _bPreDataUpdate)
{
	static zArrayDynamic<D3D12_RESOURCE_BARRIER> aBarriers;
	aBarriers.Reserve(128);
	
	auto aWantedState = _Drawlist.GetBarrierCheck(_bPreDataUpdate);
	if( aWantedState.Count() > 0 )
	{					
		auto pWantedStateCur	= aWantedState.First();
		auto pWantedStateLast	= aWantedState.Last();
		while( pWantedStateCur <= pWantedStateLast )
		{
			if( pWantedStateCur->mpResource->meState != pWantedStateCur->meWantedState )
			{	
				aBarriers.IncCount( 1 );
				D3D12_RESOURCE_BARRIER& BarrierDesc = *aBarriers.Last();
				BarrierDesc.Type					= D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
				BarrierDesc.Flags					= D3D12_RESOURCE_BARRIER_FLAG_NONE;
				BarrierDesc.Transition.pResource	= pWantedStateCur->mpResource->mrResource.Get();
				BarrierDesc.Transition.StateBefore	= pWantedStateCur->mpResource->meState;
				BarrierDesc.Transition.StateAfter	= pWantedStateCur->meWantedState;
				BarrierDesc.Transition.Subresource	= D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
				pWantedStateCur->mpResource->meState= pWantedStateCur->meWantedState;						
			}
			++pWantedStateCur;
		}
	}
				
	if( aBarriers.Count() )
	{
		mGpuContext[0].GetCommandList()->ResourceBarrier((UINT)aBarriers.Count(), aBarriers.First());
		aBarriers.SetCount(0);
		aBarriers.Reserve(128);
	}
}

void ManagerRender_DX12::Render(ScopedDrawlist& _Drawlist)
{			
	bool bBarrierPostUpdate 	= false;
	zcRes::GfxView_HAL* pView	= _Drawlist.GetRenderpass().IsValid() && _Drawlist.GetRenderpass().HAL()->mrStateView.IsValid() ? _Drawlist.GetRenderpass().HAL()->mrStateView.HAL() : nullptr;
	
	if( pView )
	{		
		zcRes::GfxTexture2DRef rRTTexture;		
		for( zUInt idx(0), count(pView->maRTColorConfig.Count()); idx<count; ++idx)
		{
			rRTTexture = pView->maRTColorConfig[idx].mrTargetSurface.IsValid() && pView->maRTColorConfig[idx].mrTargetSurface->GetTexture2D().IsValid() ? pView->maRTColorConfig[idx].mrTargetSurface->GetTexture2D() : nullptr;
			if( rRTTexture.IsValid() )
				_Drawlist.AddBarrierCheck(true, ScopedDrawlist_DX12::BarrierCheck(&rRTTexture.HAL()->mResource, D3D12_RESOURCE_STATE_RENDER_TARGET));
		}
		
		rRTTexture = pView->mRTDepthConfig.mrTargetSurface.IsValid() ? pView->mRTDepthConfig.mrTargetSurface->GetTexture2D() : nullptr;
		if( rRTTexture.IsValid() )
			_Drawlist.AddBarrierCheck(true, ScopedDrawlist_DX12::BarrierCheck(&rRTTexture.HAL()->mResource, D3D12_RESOURCE_STATE_DEPTH_WRITE));
	}
	DispatchBarrier(_Drawlist, true);

	const zEngineRef<zcGfx::Command>* prDrawcall	= _Drawlist.GetCommands().First();
	const zEngineRef<zcGfx::Command>* prDrawcallEnd	= _Drawlist.GetCommands().Last();		
	while( prDrawcall <= prDrawcallEnd )
	{		
		//! @todo 2 optim Find better way of barrier before/after DataUpdate
		if( !bBarrierPostUpdate && (*prDrawcall)->mSortId.Draw.muGPUPipelineMode > keGpuPipe_DataUpdate )
		{			
			DispatchBarrier(_Drawlist, false);
			bBarrierPostUpdate = true;
		}
		(*prDrawcall)->Invoke(mGpuContext[0]);
		++prDrawcall;		
	}

	if( !bBarrierPostUpdate )
	{			
		DispatchBarrier(_Drawlist, false);
		bBarrierPostUpdate = true;
	}
}

}
