#pragma once
#ifndef __LibZenEngine_Asset_Gfx_Mesh_h__
#define __LibZenEngine_Asset_Gfx_Mesh_h__

#if AW_ENGINETOOL

namespace zen { namespace zeAss
{
	class GfxMesh : public AssetItem
	{
	ZENClassDeclare(GfxMesh, AssetItem)
	public:
		virtual AssetItem::enumType		GetType()const{return keType_Mesh;}
		virtual PropertyArray&			GetPropertyDef() const;
		virtual zenUInt					GetPropertyDefIndex(zenHash32 _hPropertyName)const;
	protected:
		static zenArrayStatic<zenU32>	saIcon;		//!< All mesh share the same icon
	};
}} //namespace zen { namespace zeAss

#endif
#endif