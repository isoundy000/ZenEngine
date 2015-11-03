#pragma once
#ifndef __zCore_Res_Gfx_Binding_h__
#define __zCore_Res_Gfx_Binding_h__

namespace zcRes
{
	//=============================================================================================
	//! @class	Binding between a vertex shader and a VertexBuffer.
	//!			Needed for proper mapping of vertex stream into Shader.	
	//=============================================================================================
	class GfxInputStream : public TResource<GfxInputStream, GfxInputStreamResData, GfxInputStreamProxy, GfxInputStreamExporterRuntime>
	{
	ZENClassDeclare(GfxInputStream, TResource)
	};

	//=============================================================================================
	//! @class	Binding geometry to shader
	//=============================================================================================
	class GfxMeshStrip : public TResource<GfxMeshStrip, GfxMeshStripResData, GfxMeshStripProxy, GfxMeshStripExporterRuntime>
	{
	ZENClassDeclare(GfxMeshStrip, TResource)
	public:

		//! @todo urgent implement this properly (tread safe coms with proxy)
		void			SetValue(const zArrayBase<const zenRes::zShaderParameter*>& _aValues){ mrProxy->SetValue(_aValues); }	
		void			SetValue(const zenRes::zShaderParameter& _Value){mrProxy->SetValue(_Value);}
		void			SetValue(const zHash32& _hParamName, const float& _fValue){mrProxy->SetValue(_hParamName, _fValue);}
		void			SetValue(const zHash32& _hParamName, const zVec2F& _vValue){mrProxy->SetValue(_hParamName, _vValue);}
		void			SetValue(const zHash32& _hParamName, const zVec3F& _vValue){mrProxy->SetValue(_hParamName, _vValue);}
		void			SetValue(const zHash32& _hParamName, const zVec4F& _vValue){mrProxy->SetValue(_hParamName, _vValue);}
		void			SetValue(const zHash32& _hParamName, const zenMath::Matrix& _matValue){mrProxy->SetValue(_hParamName, _matValue);}
		void			SetValue(const zHash32& _hTextureName, GfxTexture2dRef _rTexture ){mrProxy->SetValue(_hTextureName, _rTexture->GetProxy());}
		void			SetValue(const zHash32& _hTextureName, GfxSamplerRef _rSampler ){mrProxy->SetValue(_hTextureName, _rSampler->GetProxy());}
		void			SetValue(const zHash32& _hTextureName, GfxTexture2dRef _rTexture, GfxSamplerRef _rSampler ){mrProxy->SetValue(_hTextureName, _rTexture->GetProxy(), _rSampler->GetProxy());}
	};

	//=============================================================================================
	//! @class	List of MeshStrip resource to generate entire mesh
	//=============================================================================================
	class GfxMesh : public TResource<GfxMesh, GfxMeshResData, GfxMeshProxy, GfxMeshExporterRuntime>
	{
	ZENClassDeclare(GfxMesh, TResource)
	public:
		//! @todo urgent implement this properly (tread safe coms with proxy)												
		void									SetValue(const zArrayBase<const zenRes::zShaderParameter*>& _aValues){ mrProxy->SetValue(_aValues); }	
		void									SetValue(const zenRes::zShaderParameter& _Value){mrProxy->SetValue(_Value);}
		void									SetValue(const zHash32& _hParamName, const float& _fValue){mrProxy->SetValue(_hParamName, _fValue);}
		void									SetValue(const zHash32& _hParamName, const zVec2F& _vValue){mrProxy->SetValue(_hParamName, _vValue);}
		void									SetValue(const zHash32& _hParamName, const zVec3F& _vValue){mrProxy->SetValue(_hParamName, _vValue);}
		void									SetValue(const zHash32& _hParamName, const zVec4F& _vValue){mrProxy->SetValue(_hParamName, _vValue);}
		void									SetValue(const zHash32& _hParamName, const zenMath::Matrix& _matValue){mrProxy->SetValue(_hParamName, _matValue);}
		void									SetValue(const zHash32& _hTextureName, GfxTexture2dRef _rTexture ){mrProxy->SetValue(_hTextureName, _rTexture->GetProxy());}
		void									SetValue(const zHash32& _hTextureName, GfxSamplerRef _rSampler ){mrProxy->SetValue(_hTextureName, _rSampler->GetProxy());}
		void									SetValue(const zHash32& _hTextureName, GfxTexture2dRef _rTexture, GfxSamplerRef _rSampler ){mrProxy->SetValue(_hTextureName, _rTexture->GetProxy(), _rSampler->GetProxy());}
		const zArrayStatic<GfxMeshStripRef>&	GetMeshStrips()const;

		zArrayStatic<GfxMeshStripRef>			marGfxMeshStrip;	//! @todo clean remove public access, temp workaround
	};

	class GfxShaderBinding : public TResource<GfxShaderBinding, GfxShaderBindingResData, GfxShaderBindingProxy, GfxShaderBindingExporterRuntime>
	{
	ZENClassDeclare(GfxShaderBinding, TResource)
	public:
						GfxShaderBinding();
		ZENInline zU32	GetRenderPassID(){return muRenderPassID;}
	protected:
		zU32			muRenderPassID;
	};
}

#endif