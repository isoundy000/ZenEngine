#pragma once
#ifndef __LibExport_Graphics_Surface_Sampler_h__
#define __LibExport_Graphics_Surface_Sampler_h__

namespace EExp
{
	class SerialSampler_Base : public EExp::ExportItem
	{
	ZENClassDeclare(SerialSampler_Base, EExp::ExportItem)
	public:
		struct ExportInfo : public EExp::ExportInfoBase
		{			
			zenConst::eTextureFiltering	meFilterMin;
			zenConst::eTextureFiltering	meFilterMag;
			zenConst::eTextureWrap		meWrapU;
			zenConst::eTextureWrap		meWrapV;
			float						mfLodBias;
			zVec4F						mvBorderColor;
		};
	};

	class SerialBlend_Base : public EExp::ExportItem
	{
	ZENClassDeclare(SerialBlend_Base, EExp::ExportItem)
	public:
		struct ExportInfo : public EExp::ExportInfoBase
		{
			zenType::awBlendDesc	mxBlendDesc;
		};
	};

	class SerialDepthStencil_Base : public EExp::ExportItem
	{
	ZENClassDeclare(SerialDepthStencil_Base, EExp::ExportItem)
	public:

		struct ExportInfo : public EExp::ExportInfoBase
		{
			zenType::awDepthStencilDesc	mxDepthStencilDesc;
		};
	};

	class SerialRasterizer_Base : public EExp::ExportItem
	{
		ZENClassDeclare(SerialRasterizer_Base, EExp::ExportItem)
	public:
		struct ExportInfo : public EExp::ExportInfoBase
		{			
			bool				mbFrontCounterClockwise;
			bool				mbDepthClipEnable;
			bool				mbScissorEnable;
			bool				mbMultisampleEnable;
			bool				mbAntialiasedLineEnable;
			bool				mbWireFrame;
			zenConst::eCullMode	meCullMode;
			zI32				miDepthBias;
			float				mfDepthBiasClamp;
			float				mfSlopeScaledDepthBias;
		};
	};

	zResID CreateGfxSampler( zenConst::eTextureFiltering _eFilterMin=zenConst::keTexFilter_Bilinear, zenConst::eTextureFiltering _eFilterMag=zenConst::keTexFilter_Bilinear, zenConst::eTextureWrap _eWrapU=zenConst::keTexWrap_Repeat, zenConst::eTextureWrap _eWrapV=zenConst::keTexWrap_Repeat, float _fLodBias=0, const zVec4F& _vBorderColor=zVec4F(0,0,0,1) );
	zResID CreateGfxBlend( zenType::awBlendDesc::awRTBlendDesc* _pxBlendDesc=nullptr, zU8 _uRenderTargets = 0, bool _bAlphaToCoverageEnable = false, bool _bIndependentBlendEnable = false );
	zResID CreateGfxDepthStencil( bool _bDepthEnable = false, bool _bDepthWrite = false, bool _bStencilEnable = false, zU8 _uStencilReadMask = 0xFF, zU8 _uStencilWriteMask = 0xFF, zenConst::eComparisonFunc _eDepthFunc = zenConst::keComparisonFunc_Always, zenType::awDepthStencilDesc::DepthStencilOp _xFrontFace = zenType::awDepthStencilDesc::DepthStencilOp(), zenType::awDepthStencilDesc::DepthStencilOp _xBackFace = zenType::awDepthStencilDesc::DepthStencilOp() );
	zResID CreateGfxRasterizer( bool _bFrontCounterClockwise = false, bool _bDepthClipEnable = false, bool _bScissorEnable = false, bool _bMultisampleEnable = false, bool _bAntialiasedLineEnable = false, bool _bWireFrame = false, zenConst::eCullMode _eCullMode = zenConst::keCullMode_None, zI32 _iDepthBias = 0, float _fDepthBiasClamp = 0.0f, float _fSlopeScaledDepthBias = 0.0f );
}

#include "EExpStateDX11.h"

#endif