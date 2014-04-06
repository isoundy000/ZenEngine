#pragma once
#ifndef __LibZenEngine_Asset_Loader_h__
#define __LibZenEngine_Asset_Loader_h__

#if ZEN_ENGINETOOL
namespace zen { namespace zeAss
{	

class AssetLoader
{
ZENClassDeclareNoParent(AssetLoader)
public:
	virtual bool	Load()=0;
	virtual bool	Save()=0;

protected:
	void			AddPackage(zeAss::Package* _pPackage);
	void			AddAsset(zeAss::Asset* _pAsset);
};

}} //namespace zen { namespace zeAss


#endif
#endif