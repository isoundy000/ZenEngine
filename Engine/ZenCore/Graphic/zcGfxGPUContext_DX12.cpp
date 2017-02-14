#include "zcCore.h"

namespace zcGfx 
{

void GPUContext_DX12::Reset(const DirectXComRef<ID3D12Device>& _rDevice, const DirectXComRef<ID3D12GraphicsCommandList>& _rCommandList )
{	
	Super::Reset();
		
	zenAssert(_rDevice.Get());
	zenAssert(_rCommandList.Get());
	mrDevice		= _rDevice;
	mrCommandList	= _rCommandList;
	mRootSignature	= RootSignature();
	mrPSO			= nullptr;
	mePrimitive		= D3D_PRIMITIVE_TOPOLOGY_UNDEFINED;

#if !ZEN_RENDERER_DX12
	zenMem::Zero(mahShaderInputStamp);	
	zenMem::Zero(maShaderInputSlotCount);
	zenMem::Zero(maResourceView);
	zenMem::Zero(maResourceType);

	// Useful for debugging/tracking but not needed
	for( zUInt stageIdx(0); stageIdx<keShaderStage__Count; ++stageIdx)
	{
		marShader[stageIdx] = nullptr;
		for(zUInt samplerIdx(0); samplerIdx<zcExp::kuDX11_SamplerPerStageMax; ++samplerIdx)
			marSampler[stageIdx][samplerIdx] = nullptr;
		for(zUInt cbufferIdx(0); cbufferIdx<zcExp::kuDX11_CBufferPerStageMax; ++cbufferIdx)
			marCBuffer[stageIdx][cbufferIdx] = nullptr;
		for(zUInt resIdx(0); resIdx<zcExp::kuDX11_ResourcesPerStageMax; ++resIdx)
			marResource[stageIdx][resIdx];		
	}
#endif
	
}

//==================================================================================================
//! @details Compare current bound samplers with wanted one and update their binding if different
//==================================================================================================
void GPUContext_DX12::UpdateShaderState_Samplers( const zcGfx::CommandDraw_HAL& _Drawcall, eShaderStage _eShaderStage )
{	
#if !ZEN_RENDERER_DX12
	ID3D11SamplerState*	aResourceView[zcExp::kuDX11_SamplerPerStageMax];
	const eShaderResource kShaderRes							= keShaderRes_Sampler;	
	const zArrayStatic<zcRes::GfxShaderResourceRef>& arResource	= _Drawcall.mrMeshStrip.HAL()->marShaderResources[_eShaderStage][kShaderRes];
	
	// Retrieve samplers new slots assignment
	zU16 uChangedFirst(0xFFFF), uChangedLast(0), uValidCount(0), uResCount(static_cast<zU16>(arResource.Count()));
	zU16 uAssignCount = zenMath::Max(uResCount, maShaderInputSlotCount[_eShaderStage][kShaderRes]);
	for( zU16 slotIdx(0); slotIdx<uAssignCount; ++slotIdx )
	{
		marSampler[_eShaderStage][slotIdx]	= slotIdx < uResCount ? arResource[slotIdx] : nullptr;
		zcRes::GfxStateSamplerRef& rResource				= marSampler[_eShaderStage][slotIdx];
		ID3D11SamplerState* pDXView					= rResource.IsValid() ? rResource.HAL()->mpSamplerState	: nullptr;		
		uChangedFirst								= pDXView != aResourceView[slotIdx]	? zenMath::Min(uChangedFirst, slotIdx)	: uChangedFirst;
		uChangedLast								= pDXView != aResourceView[slotIdx]	? slotIdx								: uChangedLast;
		uValidCount									= pDXView							? slotIdx+1								: uValidCount;
		aResourceView[slotIdx]						= pDXView;
	}

	// Send it to API
	maShaderInputSlotCount[_eShaderStage][kShaderRes] = uValidCount;
	if( uChangedLast >= uChangedFirst )
	{
		switch( _eShaderStage )
		{
		case keShaderStage_Vertex:	mpDeviceContext->VSSetSamplers( uChangedFirst, uChangedLast-uChangedFirst+1, &aResourceView[uChangedFirst] ); break;
		case keShaderStage_Pixel:	mpDeviceContext->PSSetSamplers( uChangedFirst, uChangedLast-uChangedFirst+1, &aResourceView[uChangedFirst] ); break;
		default: break;
		}
	}
#endif
}

//==================================================================================================
//! @details Compare current bound Constant Buffers with wanted one and update their binding if different
//==================================================================================================
void GPUContext_DX12::UpdateShaderState_ConstantBuffers( const zcGfx::CommandDraw_HAL& _Drawcall, eShaderStage _eShaderStage )
{	
#if !ZEN_RENDERER_DX12
	ID3D11Buffer* aResourceView[zcExp::kuDX11_CBufferPerStageMax];
	const eShaderResource kShaderRes							= keShaderRes_CBuffer;	
	const zArrayStatic<zcRes::GfxShaderResourceRef>& arResource	= _Drawcall.mrMeshStrip.HAL()->marShaderResources[_eShaderStage][kShaderRes];
	
	// Retrieve samplers new slots assignment
	zU16 uChangedFirst(0xFFFF), uChangedLast(0), uValidCount(0), uSlotCount(static_cast<zU16>(arResource.Count()));
	zU16 uAssignCount = zenMath::Max(uSlotCount, maShaderInputSlotCount[_eShaderStage][kShaderRes]);
	for( zU16 slotIdx(0); slotIdx<uAssignCount; ++slotIdx )
	{
		marCBuffer[_eShaderStage][slotIdx]	= slotIdx < uSlotCount ? arResource[slotIdx] : nullptr;
		zcRes::GfxCBufferRef& rResource				= marCBuffer[_eShaderStage][slotIdx];
		ID3D11Buffer* pDXView						= rResource.IsValid() ? rResource.HAL()->mpBufferBinding : nullptr;		
		uChangedFirst								= pDXView != aResourceView[slotIdx]	? zenMath::Min(uChangedFirst, slotIdx)	: uChangedFirst;
		uChangedLast								= pDXView != aResourceView[slotIdx]	? slotIdx								: uChangedLast;
		uValidCount									= pDXView							? slotIdx+1								: uValidCount;
		aResourceView[slotIdx]						= pDXView;
		
		//Must update CBuffer constant value if updated
		if( rResource.IsValid() )
			rResource.HAL()->Update( *mpDeviceContext ); 
	}

	// Send it to API
	maShaderInputSlotCount[_eShaderStage][kShaderRes] = uValidCount;
	if( uChangedLast >= uChangedFirst )
	{
		switch( _eShaderStage )
		{
			case keShaderStage_Vertex:	mpDeviceContext->VSSetConstantBuffers( uChangedFirst, uChangedLast-uChangedFirst+1, &aResourceView[uChangedFirst] );	break;
			case keShaderStage_Pixel:	mpDeviceContext->PSSetConstantBuffers( uChangedFirst, uChangedLast-uChangedFirst+1, &aResourceView[uChangedFirst] );	break;		
			default: break;
		}
	}
#endif
}

//==================================================================================================
//! @details Compare current bound textures with wanted one and update their binding if different
//==================================================================================================
void GPUContext_DX12::UpdateShaderState_Textures( zU16& Out_ChangedFirst, zU16& Out_ChangedLast, const zcGfx::CommandDraw_HAL& _Drawcall, eShaderStage _eShaderStage)
{	
#if !ZEN_RENDERER_DX12
	const eShaderResource kShaderRes							= keShaderRes_Texture;
	const zArrayStatic<zcRes::GfxShaderResourceRef>& arResource = _Drawcall.mrMeshStrip.HAL()->marShaderResources[_eShaderStage][kShaderRes];
	zU16 uValidCount											= 0;
	const zU16 uSlotCount										= static_cast<zU16>(arResource.Count());
	const zU16 uAssignCount										= zenMath::Max(uSlotCount, maShaderInputSlotCount[_eShaderStage][kShaderRes]);	
	for( zU16 slotIdx(0); slotIdx<uAssignCount; ++slotIdx )
	{
		zcRes::GfxTexture2DRef rResource	= slotIdx < uSlotCount	? arResource[slotIdx]			: nullptr;
		ID3D11ShaderResourceView* pDXView	= rResource.IsValid()	? rResource.HAL()->mpTextureView : nullptr;
		if( pDXView || maResourceType[_eShaderStage][slotIdx] == kShaderRes )
		{
			Out_ChangedFirst						= pDXView && pDXView != maResourceView[_eShaderStage][slotIdx] ? zenMath::Min(Out_ChangedFirst, slotIdx)	: Out_ChangedFirst;
			Out_ChangedLast							= pDXView && pDXView != maResourceView[_eShaderStage][slotIdx] ? zenMath::Max(Out_ChangedLast, slotIdx)	: Out_ChangedLast;
			uValidCount								= pDXView	? slotIdx+1	: uValidCount;
			maResourceType[_eShaderStage][slotIdx]	= pDXView	? kShaderRes : keShaderRes__Invalid;
			maResourceView[_eShaderStage][slotIdx]	= pDXView;			
			marResource[_eShaderStage][slotIdx]		= rResource;
		}		
	}
	maShaderInputSlotCount[_eShaderStage][kShaderRes] = uValidCount;
#endif
}

//==================================================================================================
//! @details Compare current bound textures with wanted one and update their binding if different
//==================================================================================================
void GPUContext_DX12::UpdateShaderState_StructBuffers( zU16& Out_ChangedFirst, zU16& Out_ChangedLast, const zcGfx::CommandDraw_HAL& _Drawcall, eShaderStage _eShaderStage)
{	
#if !ZEN_RENDERER_DX12
	const eShaderResource kShaderRes							= keShaderRes_Buffer;
	const zArrayStatic<zcRes::GfxShaderResourceRef>& arResource = _Drawcall.mrMeshStrip.HAL()->marShaderResources[_eShaderStage][kShaderRes];
	zU16 uValidCount											= 0;
	const zU16 uSlotCount										= static_cast<zU16>(arResource.Count());
	const zU16 uAssignCount										= zenMath::Max(uSlotCount, maShaderInputSlotCount[_eShaderStage][kShaderRes]);
	
	for( zU16 slotIdx(0); slotIdx<uAssignCount; ++slotIdx )
	{
		zcRes::GfxBufferRef rResource						= slotIdx < uSlotCount	? arResource[slotIdx]		: nullptr;
		ID3D11ShaderResourceView* pDXView					= rResource.IsValid()	? rResource.HAL()->mpSRV	: nullptr;
		if( pDXView || maResourceType[_eShaderStage][slotIdx] == kShaderRes )
		{
			Out_ChangedFirst								= pDXView && pDXView != maResourceView[_eShaderStage][slotIdx] ? zenMath::Min(Out_ChangedFirst, slotIdx)	: Out_ChangedFirst;
			Out_ChangedLast									= pDXView && pDXView != maResourceView[_eShaderStage][slotIdx] ? zenMath::Max(Out_ChangedLast, slotIdx)	: Out_ChangedLast;
			uValidCount										= pDXView	? slotIdx+1	: uValidCount;
			maResourceType[_eShaderStage][slotIdx]	= pDXView	? kShaderRes : keShaderRes__Invalid;
			maResourceView[_eShaderStage][slotIdx]	= pDXView;			
			marResource[_eShaderStage][slotIdx]	= rResource;
		}		
	}
	maShaderInputSlotCount[_eShaderStage][kShaderRes] = uValidCount;
#endif
}

//==================================================================================================
//! @details 
//==================================================================================================
void GPUContext_DX12::UpdateStateRenderpass(const zcGfx::CommandDraw_HAL& _Drawcall)
{	
	if( mrRenderpass != _Drawcall.mrRenderPass )
	{
		mrRenderpass		= _Drawcall.mrRenderPass;
		auto rRenderpassHAL	= _Drawcall.mrRenderPass.HAL();
		
		if( mrStateView != mrRenderpass.HAL()->mrStateView )
		{	
			mrStateView								= mrRenderpass.HAL()->mrStateView;
			const zcRes::GfxView_HAL* const ViewHAL	= mrStateView.HAL();
			
			//! @todo 0 supports descriptor heap properly						
			zUInt						uTargetCount(ViewHAL->maRTColorConfig.Count());
			D3D12_CPU_DESCRIPTOR_HANDLE aCpuHandles[D3D12_SIMULTANEOUS_RENDER_TARGET_COUNT];			
			for(zUInt idxTarget(0); idxTarget<uTargetCount; ++idxTarget )
			{
				zcRes::GfxTarget2DRef rTarget	= ViewHAL->maRTColorConfig[idxTarget].mrTargetSurface;
				if( rTarget.IsValid() )
					aCpuHandles[idxTarget]		= rTarget.HAL()->mTargetColorView.GetCpuHandle();
			}

			D3D12_CPU_DESCRIPTOR_HANDLE* pDepthHandle(nullptr);
			D3D12_CPU_DESCRIPTOR_HANDLE DepthHandle;
			zcRes::GfxTarget2DRef rDepthTarget	= ViewHAL->mRTDepthConfig.mrTargetSurface;
			if( rDepthTarget.IsValid() )
			{
				pDepthHandle	= &DepthHandle;
				DepthHandle		= rDepthTarget.HAL()->mTargetDepthView.GetCpuHandle();
				mrCommandList->OMSetStencilRef( mrRenderpass.HAL()->mrStateDepthStencil.HAL()->muStencilValue );
			}
			
			mrCommandList->OMSetRenderTargets((UINT)uTargetCount, aCpuHandles, false, pDepthHandle);			
			mrCommandList->RSSetViewports(1, &ViewHAL->mViewport);
		}		
	}
}

//==================================================================================================
//! @details Check all GPU states, and update the one that differ from current Drawcall
//==================================================================================================
void GPUContext_DX12::UpdateState(const CommandDraw_HAL& _Drawcall)
{
	const zcRes::GfxMeshStripRef& rMeshStrip		= _Drawcall.mrMeshStrip;
	const zcRes::GfxIndexRef& rIndex				= rMeshStrip.HAL()->mrIndexBuffer;
	const zcRes::GfxShaderBindingRef& rShaderBind	= rMeshStrip.HAL()->mrShaderBinding;			
	const zcRes::GfxViewRef& rView					= mrStateView;
	
	//SF @todo 0 support this
	//----------------------------------------------------------------------------------------------
	// Root Signature
	//----------------------------------------------------------------------------------------------
	if( mRootSignature != zcMgr::GfxRender.mRootSignatureDefault )
	{
		mRootSignature = zcMgr::GfxRender.mRootSignatureDefault;
		mrPSO			= nullptr;
		mrCommandList->SetGraphicsRootSignature( mRootSignature.Get() );
	}

	//----------------------------------------------------------------------------------------------
	// Pipeline State Object
	//----------------------------------------------------------------------------------------------
	if( mrPSO != _Drawcall.mrPSO )
	{
		mrPSO = _Drawcall.mrPSO;
		mrCommandList->SetPipelineState( mrPSO->GetPSO() );		
	}

	//----------------------------------------------------------------------------------------------
	// ...
	//----------------------------------------------------------------------------------------------
	UpdateStateRenderpass(_Drawcall);

	//----------------------------------------------------------------------------------------------
	// Primitive Topology (point, triangle strip, line list, ...)
	//----------------------------------------------------------------------------------------------
	if( mePrimitive != rIndex.HAL()->mePrimitive )
	{
		mePrimitive = rIndex.HAL()->mePrimitive;
		mrCommandList->IASetPrimitiveTopology( mePrimitive );
	}
	
	mrCommandList->IASetVertexBuffers(0, 1, &zcMgr::GfxRender.mTmpVertexBufferView); //! @todo 0 

	//----------------------------------------------------------------------------------------------
	// Per drawcall scissor setting
	//----------------------------------------------------------------------------------------------
	zVec4U16 vScreenScissor = _Drawcall.mvScreenScissor;
	vScreenScissor.z		= zenMath::Min<zU16>(vScreenScissor.z, (zU16)rView.HAL()->mViewport.Width + vScreenScissor.x);
	vScreenScissor.w		= zenMath::Min<zU16>(vScreenScissor.w, (zU16)rView.HAL()->mViewport.Height + vScreenScissor.y);
	if( mvScreenScissor != vScreenScissor )
	{
		D3D12_RECT ScissorRect	= {vScreenScissor.x, vScreenScissor.y, vScreenScissor.z, vScreenScissor.w};
		mrCommandList->RSSetScissorRects(1, &ScissorRect);
	}


#if !ZEN_RENDERER_DX12
	UINT UnusedOffset = 0;
	const zcRes::GfxMeshStripRef&		rMeshStrip	= _Drawcall.mrMeshStrip;
	const zcRes::GfxIndexRef&			rIndex		= rMeshStrip.HAL()->mrIndexBuffer;
	const zcRes::GfxShaderBindingRef&	rShaderBind	= rMeshStrip.HAL()->mrShaderBinding;			
	const zcRes::GfxViewRef&			rView		= mrStateView;
	
	UpdateStateRenderpass(_Drawcall);
	if( mePrimitiveType != rIndex.HAL()->mePrimitiveType )
	{
		mePrimitiveType = rIndex.HAL()->mePrimitiveType;
		mpDeviceContext->IASetPrimitiveTopology( rIndex.HAL()->mePrimitiveType );
	}
	
	if( marShader[zenConst::keShaderStage_Vertex] != rShaderBind.HAL()->marShader[zenConst::keShaderStage_Vertex] )
	{
		marShader[zenConst::keShaderStage_Vertex]	= rShaderBind.HAL()->marShader[zenConst::keShaderStage_Vertex];
		zcRes::GfxShaderVertexRef rShaderVertex				= marShader[zenConst::keShaderStage_Vertex];
		mpDeviceContext->VSSetShader( rShaderVertex.HAL()->mpVertexShader, nullptr, 0 );
	}
	
	if( marShader[zenConst::keShaderStage_Pixel]!= rShaderBind.HAL()->marShader[zenConst::keShaderStage_Pixel] )
	{
		marShader[zenConst::keShaderStage_Pixel]	= rShaderBind.HAL()->marShader[zenConst::keShaderStage_Pixel];
		zcRes::GfxShaderPixelRef rShaderPixel				= marShader[zenConst::keShaderStage_Pixel];
		mpDeviceContext->PSSetShader( rShaderPixel.HAL()->mpPixelShader, nullptr, 0 );
	}
	
	if(mbScreenScissorOn || mvScreenScissor != _Drawcall.mvScreenScissor )
	{
		D3D11_RECT ScissorRect;
		mvScreenScissor				= _Drawcall.mvScreenScissor;		
		ScissorRect.left			= _Drawcall.mvScreenScissor.x;
		ScissorRect.top				= _Drawcall.mvScreenScissor.y;
		ScissorRect.right			= zenMath::Min<zU16>(_Drawcall.mvScreenScissor.z, (zU16)rView.HAL()->mViewport.Width);
		ScissorRect.bottom			= zenMath::Min<zU16>(_Drawcall.mvScreenScissor.w, (zU16)rView.HAL()->mViewport.Height);
		mpDeviceContext->RSSetScissorRects(1, &ScissorRect);
	}
	
	mpDeviceContext->IASetIndexBuffer	( rIndex.HAL()->mpIndiceBuffer, rIndex.HAL()->meIndiceFormat, 0 );	

	//----------------------------------------------------------------------------------------------
	// Assign Shader input resources for each stage
	//----------------------------------------------------------------------------------------------
	for(zUInt stageIdx(0); stageIdx<keShaderStage__Count; ++stageIdx)
	{						
		// Check resource setup stamp to detect if there was a change
		const eShaderStage eStageIdx = (eShaderStage)stageIdx;
		bool bUpdated[keShaderRes__Count];
		for(zUInt resTypeIdx(0);resTypeIdx<keShaderRes__Count; ++resTypeIdx)
		{
			const zArrayStatic<zcRes::GfxShaderResourceRef>& arResources	= rMeshStrip.HAL()->marShaderResources[stageIdx][resTypeIdx];
			zHash32 zMeshStripResStamp										= rMeshStrip.HAL()->mhShaderResourceStamp[stageIdx][resTypeIdx];

			if( (zU32)zMeshStripResStamp == 0 )
			{
				zMeshStripResStamp = zHash32();
				for(zUInt resIdx(0), resCount(arResources.Count()); resIdx<resCount; ++resIdx)
					zMeshStripResStamp.Append( arResources[resIdx].IsValid() ? (void*)&arResources[resIdx]->mResID : (void*)&zResID(), sizeof(zResID) );
				rMeshStrip.HAL()->mhShaderResourceStamp[stageIdx][resTypeIdx] = zMeshStripResStamp;
			}

			bUpdated[resTypeIdx]								= mahShaderInputStamp[stageIdx][resTypeIdx] != zMeshStripResStamp;
			mahShaderInputStamp[stageIdx][resTypeIdx]	= zMeshStripResStamp;
		}
		
		// Special case shader resources update
		if( bUpdated[keShaderRes_Sampler] )
			UpdateShaderState_Samplers(_Drawcall, eStageIdx);
		if( bUpdated[keShaderRes_CBuffer] )
			UpdateShaderState_ConstantBuffers(_Drawcall, eStageIdx);
		
		// Generic shader resources update
		zU16 uResChangeStart(0xFFFF), uResChangeEnd(0);
		if( bUpdated[keShaderRes_Buffer] )
			UpdateShaderState_StructBuffers(uResChangeStart, uResChangeEnd, _Drawcall, eStageIdx);
		
		if( bUpdated[keShaderRes_Texture] )
			UpdateShaderState_Textures(uResChangeStart, uResChangeEnd, _Drawcall, eStageIdx);
		
		if( uResChangeEnd >= uResChangeStart )
		{
			switch( eStageIdx )
			{
			case keShaderStage_Vertex:	mpDeviceContext->VSSetShaderResources( uResChangeStart, uResChangeEnd-uResChangeStart+1, &maResourceView[stageIdx][uResChangeStart] );	break;
			case keShaderStage_Pixel:	mpDeviceContext->PSSetShaderResources( uResChangeStart, uResChangeEnd-uResChangeStart+1, &maResourceView[stageIdx][uResChangeStart] );	break;
			default: break;
			}
		}
	}
#endif
}

} 
