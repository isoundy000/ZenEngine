#pragma once
#ifndef __zenCore_ResourceGfxBinding_h__
#define __zenCore_ResourceGfxBinding_h__

namespace zen { namespace zenRes {	

	AWClassResourceRefDeclare(zGfxSampler, zenConst::keResType_GfxSampler)
	public:
		static zGfxSampler			Create( zenConst::eTextureFiltering _eFilterMin=zenConst::keTexFilter_Bilinear, zenConst::eTextureFiltering _eFilterMag=zenConst::keTexFilter_Bilinear, zenConst::eTextureWrap _eWrapU=zenConst::keTexWrap_Repeat, zenConst::eTextureWrap _eWrapV=zenConst::keTexWrap_Repeat, float _fLodBias=0, const zVec4F& _vBorderColor=zVec4F(0,0,0,1) );
	};

	AWClassResourceRefDeclare(zGfxBlend, zenConst::keResType_GfxBlend)
	public:
		static zGfxBlend			Create( zenType::awBlendDesc::awRTBlendDesc* _pxBlendDesc=nullptr, zU8 _uRenderTargets = 0, bool _bAlphaToCoverageEnable = false, bool _bIndependentBlendEnable = false );
	};

	AWClassResourceRefDeclare(zGfxDepthStencil, zenConst::keResType_GfxDepthStencil)
	public:
		static zGfxDepthStencil	Create( bool _bDepthEnable = false, bool _bDepthWrite = false, bool _bStencilEnable = false, zU8 _uStencilReadMask = 0xFF, zU8 _uStencilWriteMask = 0xFF, zenConst::eComparisonFunc _eDepthFunc = zenConst::keComparisonFunc_Always, zenType::awDepthStencilDesc::DepthStencilOp _xFrontFace = zenType::awDepthStencilDesc::DepthStencilOp(), zenType::awDepthStencilDesc::DepthStencilOp _xBackFace = zenType::awDepthStencilDesc::DepthStencilOp() );
	};

	AWClassResourceRefDeclare(zGfxRasterizer, zenConst::keResType_GfxRasterizer)
	public:
		static zGfxRasterizer		Create( bool _bFrontCounterClockwise = false, bool _bDepthClipEnable = false, bool _bScissorEnable = false, bool _bMultisampleEnable = false, bool _bAntialiasedLineEnable = false, bool _bWireFrame = false, zenConst::eCullMode _eCullMode = zenConst::keCullMode_None, zI32 _iDepthBias = 0, float _fDepthBiasClamp = 0.0f, float _fSlopeScaledDepthBias = 0.0f );
	};

	AWClassResourceRefDeclare(zGfxShaderBinding, zenConst::keResType_GfxShaderBinding)
	public:		
		static zGfxShaderBinding	Create(const zArrayBase<zenRes::zGfxShader>& _aShader);
		static zGfxShaderBinding	Create(const zenRes::zGfxShader* _pShaders, zUInt _uCount);
	};

	//! @todo Clean: remove this from api
	AWClassResourceRefDeclare(zGfxInputStream, zenConst::keResType_GfxInputStream) };

	AWClassResourceRefDeclare(zGfxMeshStrip, zenConst::keResType_GfxMeshStrip)
	public:
		void						RenderMeshStrip();
		void						SetValue(const zShaderParameter& _Value);			
		void						SetValue(const zArrayBase<const zShaderParameter*>& _aValues);	
		void						SetValue(const zHash32& _hParamName, const float& _fValue);
		void						SetValue(const zHash32& _hParamName, const zVec2F& _vValue);
		void						SetValue(const zHash32& _hParamName, const zVec3F& _vValue);
		void						SetValue(const zHash32& _hParamName, const zVec4F& _vValue);
		void						SetValue(const zHash32& _hParamName, const zenMath::Matrix& _matValue);
		void						SetValue(const zHash32& _hTextureName, zGfxTexture2D _rTexture );
		void						SetValue(const zHash32& _hTextureName, zGfxSampler _rSampler );
		void						SetValue(const zHash32& _hTextureName, zGfxTexture2D _rTexture, zGfxSampler _rSampler );
		
		static zGfxMeshStrip		Create(const zGfxVertex& _VertexBuffer, const zGfxIndex& _IndexBuffer, const zGfxShaderBinding& _rShaderBinding, const zArrayBase<zResID>& _aShaderParamID, const zArrayBase<zShaderTexture>& _aTexture, zU32 _uIndexFirst=0, zU32 _uIndexCount=0xFFFFFFFF);
		static zGfxMeshStrip		Create(const zGfxVertex& _VertexBuffer, const zGfxIndex& _IndexBuffer, const zGfxShaderBinding& _rShaderBinding, const zArrayBase<zResID>& _aShaderParamID, zU32 _uIndexFirst=0, zU32 _uIndexCount=0xFFFFFFFF);
		static zGfxMeshStrip		Create(const zGfxVertex& _VertexBuffer, const zGfxIndex& _IndexBuffer, const zGfxShaderBinding& _rShaderBinding, zU32 _uIndexFirst=0, zU32 _uIndexCount=0xFFFFFFFF);
	};

	AWClassResourceRefDeclare(zGfxMesh, zenConst::keResType_GfxMesh)
	public:
		void						RenderMesh();
		void						SetValue(const zShaderParameter& _Value);			
		void						SetValue(const zArrayBase<const zShaderParameter*>& _aValues);	
		void						SetValue(const zHash32& _hParamName, const float& _fValue);
		void						SetValue(const zHash32& _hParamName, const zVec2F& _vValue);
		void						SetValue(const zHash32& _hParamName, const zVec3F& _vValue);
		void						SetValue(const zHash32& _hParamName, const zVec4F& _vValue);
		void						SetValue(const zHash32& _hParamName, const zenMath::Matrix& _matValue);
		void						SetValue(const zHash32& _hTextureName, zGfxTexture2D _rTexture );
		void						SetValue(const zHash32& _hTextureName, zGfxSampler _rSampler );
		void						SetValue(const zHash32& _hTextureName, zGfxTexture2D _rTexture, zGfxSampler _rSampler );
		
		static zGfxMesh				Create(const zArrayBase<zGfxMeshStrip>& _aMeshStrip);
		static zGfxMesh				Create(const zGfxMeshStrip* _aMeshStrip, zUInt _uMeshStripCount);
	};

	AWClassResourceRefDeclare(zGfxView, zenConst::keResType_GfxView)
	public:
		void						ActivateView();
		void						Clear( bool _bClearColor, const zVec4F& _vRGBA, bool _bClearDepth=true, float _fDepth=1, bool _bClearStencil=false, zU8 _uStencil=0 );
		zVec2U16					GetDim()const;
		
		static zGfxView			Create( const zGfxRenderTarget& _RTColor, const zGfxRenderTarget& _RTDepth, const zVec2U16& _vDim=zVec2U16(9999,9999), const zVec2U16& _vOrigin=zVec2U16(0,0) );
		static zGfxView			Create( const zArrayBase<zGfxRenderTarget>& _aRTColor, const zGfxRenderTarget& _RTDepth, const zVec2U16& _vDim=zVec2U16(9999,9999), const zVec2U16& _vOrigin=zVec2U16(0,0) );
	};

	AWClassResourceRefDeclare(zGfxWindow, zenConst::keResType_GfxWindow)
	public:
		void						FrameBegin();
		void						FrameEnd();
		zGfxView					GetBackbuffer();
		void						Resize(const zVec2U16& _vSize);

		static zGfxWindow			Create( HWND _WindowHandle );
	};

}} // namespace zen, zenRes

#endif

