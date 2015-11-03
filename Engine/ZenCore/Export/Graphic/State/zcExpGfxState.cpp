#include "zcCore.h"

namespace zcExp
{	
	zResID CreateGfxSampler( zenConst::eTextureFiltering _eFilterMin, zenConst::eTextureFiltering _eFilterMag, zenConst::eTextureWrap _eWrapU, zenConst::eTextureWrap _eWrapV, float _fLodBias, const zVec4F& _vBorderColor )
	{
		static zenMem::zAllocatorPool sMemPool("Pool CreateSampler", sizeof(ExportInfoGfxSampler), 1, 5 );
		ExportInfoGfxSampler*	pExportInfo	= zenNew(&sMemPool) ExportInfoGfxSampler;
		pExportInfo->meFilterMin			= _eFilterMin;
		pExportInfo->meFilterMag			= _eFilterMag;
		pExportInfo->meWrapU				= _eWrapU;
		pExportInfo->meWrapV				= _eWrapV;			
		pExportInfo->mfLodBias				= _fLodBias;
		pExportInfo->mvBorderColor			= _vBorderColor;
		return zcMgr::Export.CreateItem( zResID::kePlatformType_GFX, zenConst::keResType_GfxSampler, pExportInfo );
	}

	zResID CreateGfxRasterizer( const zenRes::zGfxStateRasterizer::Config& _RasterConfig )
	{
		static zenMem::zAllocatorPool sMemPool("Pool CreateRasterizer", sizeof(ExportInfoGfxStateRasterizer), 1, 5 );
		ExportInfoGfxStateRasterizer* pExportInfo	= zenNew(&sMemPool) ExportInfoGfxStateRasterizer;
		pExportInfo->mRasterConfig					= _RasterConfig; //! @todo optim prevent copy duplicate for dynamically created element (done right away, no 
		return zcMgr::Export.CreateItem( zResID::kePlatformType_GFX, zenConst::keResType_GfxRasterizer, pExportInfo );
	}

	zResID CreateGfxDepthStencil( const zenRes::zGfxRenderPass::ConfigDepthRT& _DepthStencilConfig )
	{
		static zenMem::zAllocatorPool sMemPool("Pool CreateDepthStencil", sizeof(ExportInfoGfxStateDepthStencil), 1, 5 );
		ExportInfoGfxStateDepthStencil*	pExportInfo	= zenNew(&sMemPool) ExportInfoGfxStateDepthStencil;
		pExportInfo->mpDepthStencilConfig			= &_DepthStencilConfig; 
		return zcMgr::Export.CreateItem( zResID::kePlatformType_GFX, zenConst::keResType_GfxDepthStencil, pExportInfo );
	}

	zResID CreateGfxBlend( const zArrayBase<zenRes::zGfxRenderPass::ConfigColorRT>& _aTargetColorConfig)
	{
		static zenMem::zAllocatorPool sMemPool("Pool CreateBlend", sizeof(ExportInfoGfxStateBlend), 1, 5 );
		ExportInfoGfxStateBlend* pExportInfo		= zenNew(&sMemPool) ExportInfoGfxStateBlend;
		pExportInfo->mpaRenderTargetConfig			= &_aTargetColorConfig;
		return zcMgr::Export.CreateItem( zResID::kePlatformType_GFX, zenConst::keResType_GfxBlend, pExportInfo );
		return zResID();
	}
}