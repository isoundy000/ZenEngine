#include "zcCore.h"

//SF DX12
namespace zcRes
{

bool GfxCBufferDefinition_DX12::Initialize()
{
	return TRUE;
}


//=================================================================================================

GfxCBuffer_DX12::~GfxCBuffer_DX12()
{
	if( mrResource.Get() != nullptr && mpCBufferMapped )
	{
		CD3DX12_RANGE WriteRange(0, 0);	//Nothing to write to gpu
		mrResource->Unmap(0, &WriteRange);
		mpCBufferMapped = nullptr;
	}
}

bool GfxCBuffer_DX12::Initialize()
{	
	mrCBufferParent		= mParentParamDefID;
	if( mrCBufferParent.IsValid() )
	{
		UINT uAlignedSize	= zenMath::RoundUp((UINT)maParameterValues.SizeMem(), UINT(256));
		HRESULT hr			= zcMgr::GfxRender.GetDevice()->CreateCommittedResource(	
								&CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_UPLOAD),
								D3D12_HEAP_FLAG_NONE,
								&CD3DX12_RESOURCE_DESC::Buffer(uAlignedSize),
								D3D12_RESOURCE_STATE_GENERIC_READ,
								nullptr, IID_PPV_ARGS(&mrResource));
		if( SUCCEEDED(hr) )
		{
			zSetGfxResourceName(mrResource, mResID, nullptr);

			// Create constant buffer views to access the upload buffer.
			D3D12_CONSTANT_BUFFER_VIEW_DESC desc;
			mCBufferView		= zcMgr::GfxRender.GetDescriptorSRV(1);		 //! @todo 2 clean, use something like GpuMemoryResStandard? Auto release?
			desc.BufferLocation = mrResource->GetGPUVirtualAddress();
			desc.SizeInBytes	= uAlignedSize;
			zcMgr::GfxRender.GetDevice()->CreateConstantBufferView(&desc, mCBufferView.GetCpu());

			// Map the constant buffers.
			CD3DX12_RANGE readRange(0, 0);		// We do not intend to read from this resource on the CPU.
			hr = mrResource->Map(0, &readRange, reinterpret_cast<void**>(&mpCBufferMapped));
			if( SUCCEEDED(hr) )
			{
				// We don't unmap this until the app closes. Keeping things mapped for the lifetime of the resource is okay.
				zenMem::Copy( mpCBufferMapped, maParameterValues.First(), maParameterValues.SizeMem() );
				return true;
			}
		}
	}
	
	return false;
}

void GfxCBuffer_DX12::Update( const DirectXComRef<ID3D12GraphicsCommandList>& _rCommandList )
{
	if( mbUpdated && mpCBufferMapped )
	{
		zenMem::Copy( mpCBufferMapped, maParameterValues.First(), maParameterValues.SizeMem() );
		mbUpdated = FALSE;
	}
}

void GfxCBuffer_DX12::SetValue(const zcExp::ParameterBase& _Value)
{
	zcExp::GfxCBufferParamInfo ItemInfo;
	if( mrCBufferParent.HAL()->mdParamInfo.Get(_Value.mhName, ItemInfo) )
	{		
		zenMem::Copy( &maParameterValues[ItemInfo.muOffset], static_cast<const zU8*>(_Value.GetData()), zenMath::Min(_Value.muSizeTotal, ItemInfo.muSize) );
		mbUpdated = TRUE;
	}	
}

void GfxCBuffer_DX12::SetValue(const zenRes::zShaderParameter& _Value)
{
	zcExp::GfxCBufferParamInfo ItemInfo;
	if( mrCBufferParent.HAL()->mdParamInfo.Get(_Value.mhName, ItemInfo) )
	{		
		zenMem::Copy( &maParameterValues[ItemInfo.muOffset], static_cast<const zU8*>(_Value.GetData()), zenMath::Min(_Value.muSizeTotal, ItemInfo.muSize) );
		mbUpdated = TRUE;
	}	
}

}
