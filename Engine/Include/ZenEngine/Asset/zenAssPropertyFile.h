#pragma once
#ifndef __zenEngine_Asset_PropertyFile_h__
#define __zenEngine_Asset_PropertyFile_h__

#if ZEN_ENGINETOOL

namespace zen { namespace zenAss 
{
	
class PropertyFile : public TPropertyDefinition<zenConst::keAssProp_File, PropertyFile, zString>
{
ZENClassDeclare(PropertyFile, TPropertyDefinition);	
public:
						PropertyFile(const char* _zName, const char* _zDisplayName, const char* _zDescription, bool _bShowInAssetDesc, const char* _zDefault, const char* _zFileExt="Any(*.*)|*.*" )
						: TPropertyDefinition(_zName, _zDisplayName, _zDescription, _bShowInAssetDesc)
						, mDefault(_zDefault)
						, mzFileExt(_zFileExt)
						{}
	ValueStorage		mDefault;
	zString				mzFileExt;	//!< List of supported files extensions to display in file dialog
};
	
}} //namespace zen { namespace zenAss

#endif
#endif