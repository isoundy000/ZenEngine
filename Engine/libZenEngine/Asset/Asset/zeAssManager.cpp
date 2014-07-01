#include "libZenEngine.h"
#include <Engine/libZenExternal/libZenExternal.h>

#if ZEN_ENGINETOOL
namespace zeMgr{ zeAss::ManagerAsset Asset; }

namespace zen { namespace zeAss
{
//=================================================================================================
//! @brief		Called by AssetMap, when asset is removed from it
//! @details	Since no destructor is called on item removed from map, need to 
//!				decrement refcount manually, makifn sure there's no resource leak
//-------------------------------------------------------------------------------------------------
//! @return		True if init was successful
//=================================================================================================
void ResetAssetReference( zenAss::zArrayAsset& _dAsset, zenAss::zAssetItem& _rAssetDel)
{
	_rAssetDel = NULL;
}
void ResetPackageReference( zenAss::zArrayPackage& _dPackage, zenAss::zPackage& _rPackageDel)
{
	_rPackageDel = NULL;
}

//=================================================================================================
//! @brief		Constructor
//=================================================================================================
ManagerAsset::ManagerAsset()
: mdPackage(50)
, muPackageNextID(0)
{	
	mdPackage.SetDefaultValue(NULL);
	mdPackage.SetDeleteItemCB( ResetPackageReference );

	zenMem::Zero(maAssetNextID, sizeof(maAssetNextID) );
	for(zUInt idx(0); idx<zenConst::keAssType__Count; ++idx)
	{
		madAsset[idx].Init(1000);
		madAsset[idx].SetDefaultValue(NULL);
		madAsset[idx].SetDeleteItemCB( ResetAssetReference );			
	}
	
}

//=================================================================================================
//! @brief		Load Manager
//! @details	Part of ManagerBase Interface.
//-------------------------------------------------------------------------------------------------
//! @return		True if init was successful
//=================================================================================================
bool ManagerAsset::Load()
{		
	PackageLoad();
	return true;
}

//=================================================================================================
//! @brief		Unload Manager
//! @details	Part of ManagerBase Interface.
//-------------------------------------------------------------------------------------------------
//! @return		True if unload was successful
//=================================================================================================
bool ManagerAsset::Unload()
{	
	return true;
} 

void ManagerAsset::PackageAdd( Package* _pPackage )
{
	mdPackage.Set(_pPackage->GetID(), _pPackage);
	//! @todo Asset: Process adding package
}

void ManagerAsset::PackageLoad()
{
	zxAss::AssetLoaderXml xmlLoader;
	mdPackage.Clear();	
	xmlLoader.LoadPackages();

	zenAss::zArrayPackage::Iterator itPackage;
	mdPackage.GetLast(itPackage);
	muPackageNextID = itPackage.IsValid() ? itPackage.GetKey() + 1 : 1;

	zenAss::zArrayAsset::Iterator itAsset;
	for(zUInt idx(0); idx<zenConst::keAssType__Count; ++idx)
	{
		madAsset[idx].GetLast(itAsset);
		maAssetNextID[idx] = itAsset.IsValid() ? itAsset.GetKey() + 1 : 1;
	}
	/*
	//! @todo Asset : REMOVE THIS TEST
	zenAss::zArrayPackage::Iterator itPackage2;
	mdPackage.GetFirst(itPackage2);
	while( itPackage2.IsValid() )
	{
		PackageSave( itPackage2.GetValue().GetID() );
		++itPackage2;
	}
	//! Asset : REMOVE THIS TEST
	*/
}

bool ManagerAsset::PackageSave( zU32 _uPackageID )
{
	zxAss::AssetLoaderXml Loader;
	zenAss::zPackage rPackage = mdPackage[_uPackageID];
	if( rPackage.IsValid() && Loader.Save(rPackage) )
	{
		rPackage->SetDirty(false);
		return true;
	}
	return false;
}

void ManagerAsset::PackageRemove( zU32 _uPackageID )	
{
	//! @todo Asset: Process removal
	ZENAssert(0);
	zenAss::zPackage rPackage = mdPackage[_uPackageID];
	if( rPackage.IsValid() )
	{		
		mdPackage.Unset(_uPackageID);
	}	
}

const zenAss::zPackage& ManagerAsset::PackageGet( zU32 _uPackageID )
{
	return mdPackage[_uPackageID];
}

const zenAss::zAssetItem& ManagerAsset::AssetGet( zenConst::eAssetType _eType, zU32 _uAssetID )const
{
	static const zenAss::zAssetItem sInvalid;
	if( _eType<zenConst::keAssType__Count )
		return madAsset[_eType][_uAssetID];
	else
		return sInvalid;
}

const zenAss::zArrayAsset& ManagerAsset::AssetGet( zenConst::eAssetType _eType )const
{
	ZENAssert( _eType < zenConst::keAssType__Count );
	return madAsset[_eType];
}

void ManagerAsset::AssetAdd( zeAss::Asset* _pAsset )
{
	ZENAssert( _pAsset && madAsset[_pAsset->GetType()].Exist(_pAsset->GetID().muIndex) == false );
	madAsset[_pAsset->GetType()].Set(_pAsset->GetID().muIndex, _pAsset);
}

void ManagerAsset::AssetRem( zenAss::zAssetID _AssetID )
{
	ZENAssert(_AssetID.meType<zenConst::keAssType__Count); 
	zenAss::zAssetItem rAsset;
	madAsset[_AssetID.meType].Get(_AssetID.muIndex, rAsset);
	if( rAsset.IsValid() )
	{
		rAsset.Get()->SetPackage(NULL);
		madAsset[_AssetID.meType].Unset(_AssetID.muIndex);
	}
}

}} //namespace zen { namespace zeAss

#endif //ZEN_ENGINETOOL
