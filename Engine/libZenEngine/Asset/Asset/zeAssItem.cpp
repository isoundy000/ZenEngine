#include "libZenEngine.h"

#if ZEN_ENGINETOOL

namespace zen { namespace zeAss
{

//=================================================================================================
//! @brief		Factory to create a new Asset of specified type
//! @details	
//-------------------------------------------------------------------------------------------------
//! @param		_eAssetType	- Type of asset to create
//! @param		_Owner		- Owner package of the newly create Asset
//! @return					- Created Asset
//=================================================================================================
Asset* Asset::CreateItem( zenConst::eAssetType _eAssetType )
{
	switch( _eAssetType )
	{
	case zenConst::keAssType_TestProperty:	return zenNewDefault TestProperty();
	case zenConst::keAssType_Texture2D:		return zenNewDefault GfxTexture2D();
	case zenConst::keAssType_Mesh:			return zenNewDefault GfxMesh();
	default:								ZENAssertMsg(0, "Unsupported Asset Type");
	}
	return NULL;
}

Asset::Asset()	
: mrPackage(NULL)
, mID(zenConst::keAssType__Invalid, 0)
{
}

Asset::~Asset()	
{
}

void Asset::Init(zenAss::zAssetID _AssetID, const char* _zName, const zenAss::zPackageRef& _rParentPkg)
{	
	ZENAssert( !_AssetID.IsValid() || _AssetID.meType == GetType() );
	mID		= _AssetID.IsValid() ? _AssetID :  zeMgr::Asset.GetAssetNextID( GetType() );
	mzName	= _zName;
	InitDefault();	
	SetPackage( _rParentPkg );
	zeMgr::Asset.AssetAdd(this);
	//! @todo Asset : description init
	//RebuiltDescription();
}

void Asset::SetPackage(const zenAss::zPackageRef& _rParentPkg)
{
	zenAss::zAssetItemRef rAssetThis(this);
	if( mrPackage.IsValid() )
		mrPackage->AssetRem( rAssetThis );
	
	mrPackage = _rParentPkg;
	if( mrPackage.IsValid() )
		mrPackage->AssetAdd( rAssetThis );
}

void Asset::SetName(const char* _zName)
{
	mzName = _zName;
}

bool Asset::UpdatedProperties()
{
	RebuiltDescription();
	return false;
}

//=================================================================================================
//! @brief		Build a string description based on asset property definitions/values
//! @details	Take all flagged properties and make a string description from it. Used for
//!				Asset short description in editor
//-------------------------------------------------------------------------------------------------
//! @return		
//=================================================================================================
void Asset::RebuiltDescription()
{	
	mzDescription = "";
	//! @TODO
	/*
	for(zUInt idx(0), count(maPropertyValueOld.Count()); idx<count; ++idx)
	{
		const PropertyDefBase& propDef = maPropertyValueOld[idx].GetBase()->mParentDef;
		if( propDef.mbShowInAssetDesc )
		{
			char zBuffer[128];			
			char zValue[64];
			maPropertyValueOld[idx].GetBase()->ValueToString( zValue, sizeof(zValue) );
			sprintf(zBuffer, "(%s : %s) ", propDef.mzDisplayName, zValue);
			mzDescription += zBuffer;
		}		
	}
	*/
}

void Asset::InitDefault()
{	
	const zenAss::PropertyDefArray& aProperties = GetProperties();	
	ZENAssertMsg(aProperties.Count() > 0, "An Asset type is missing ::GetProperties() implementation" );
	maPropertyValue.SetCount( aProperties.Count() );
	const zenAss::PropertyDefRef*	prDefinitionCur	= aProperties.First();
	zenAss::PropertyValueRef*		pValueCur		= maPropertyValue.First();
	zenAss::PropertyValueRef*		pValueLast		= maPropertyValue.Last();
	while( pValueCur <= pValueLast )
	{
		*pValueCur = (*prDefinitionCur)->Allocate();
		++pValueCur;
		++prDefinitionCur;
	}

	UpdatedProperties();
}

const zenAss::PropertyDefArray& TestProperty::GetProperties()const
{ 	
 	const zenAss::PropertyEnum::Entry aEnumEntries[]={
 		zenAss::PropertyEnum::Entry(10, "Value A", "Description of 1st Entry"),
 		zenAss::PropertyEnum::Entry(20, "Value B", "Description of 2nd Entry"),
 		zenAss::PropertyEnum::Entry(30, "Value C", "Description of 3rd Entry"),
 		zenAss::PropertyEnum::Entry(40, "Value D", "Description of 4th Entry")};
	
 	static const zenAss::PropertyDefRef aPropertiesStruct[] =	{
		//zenAss::PropertyBool::Create	("StructBool",	"", "Struct Test: Bool",	true,	true, false),
		zenAss::PropertyFloat::Create	("StructFloat",	"", "Struct Test: Float",	true,	true, 1.f, -5.f, 5.f, 0.5f),
		zenAss::PropertyFloat2::Create	("StructFloat2","", "Struct Test: Float2",	true,	true, zVec2F(1.f), zVec2F(-10.f), zVec2F(10.f), zVec2F(0.1f))
	};

	static zenAss::PropertyDefRef rPropertyArrayStruct = zenAss::PropertyStruct::Create("PropertyStruct",	"",	"Test: Struct in Array", true,	true,	aPropertiesStruct, ZENArrayCount(aPropertiesStruct) );
	static zenAss::PropertyDefRef rPropertyArrayFloat2 = zenAss::PropertyFloat2::Create	("ArrayFloat2",	"", "Test: Float2 in Array",	true,	true,	zVec2F(1.f), zVec2F(-10.f), zVec2F(10.f), zVec2F(0.1f));

	static const zenAss::PropertyDefRef aPropertiesAll[] = {
		zenAss::PropertyBool::Create	("Bool",	"", "Def: Bool",					true,	true,	false),
		zenAss::PropertyFloat::Create	("Float",	"", "Def: Float",					true,	true,	0.f, -10.f, 10.f, 0.5f),
		zenAss::PropertyFloat2::Create	("Float2",	"", "Def: Float2",					true,	true,	zVec2F(1.f), zVec2F(-10.f), zVec2F(10.f), zVec2F(0.1f)),
		zenAss::PropertyFloat3::Create	("Float3",	"", "Def: Float3",					true,	true,	zVec3F(1.f), zVec3F(-10.f), zVec3F(10.f), zVec3F(0.1f)),
		zenAss::PropertyFloat4::Create	("Float4",	"", "Def: Float4",					true,	true,	zVec4F(1.f), zVec4F(-10.f), zVec4F(10.f), zVec4F(0.1f)),	
		zenAss::PropertyInt::Create		("Int",		"", "Def: Int",						true,	true,	0, -10, 10, 1),
		zenAss::PropertyInt2::Create	("Int2",	"", "Def: Int2",					true,	true,	zVec2S32(1), zVec2S32(-10), zVec2S32(10), zVec2S32(1)),
		zenAss::PropertyInt3::Create	("Int3",	"", "Def: Int3",					true,	true,	zVec3S32(1), zVec3S32(-10), zVec3S32(10), zVec3S32(1)),
		zenAss::PropertyInt4::Create	("Int4",	"", "Def: Int4",					true,	true,	zVec4S32(1), zVec4S32(-10), zVec4S32(10), zVec4S32(1)),
		zenAss::PropertyEnum::Create	("Enum",	"", "Def: Enum",					true,	true,	10, aEnumEntries, ZENArrayCount(aEnumEntries) ),
		zenAss::PropertyFile::Create	("File",	"", "Def: File",					true,	true,	zenT("test.txt"), zenT("Images|*.bmp;*.png;*.jpeg;*.jpg|BMP(*.bmp)|*.bmp|PNG(*.png)|*.png|JPEG(*.jpg;*.jpeg)|*.jpg;*.jpeg")),
		zenAss::PropertyAsset::Create	("AssetA",	"", "Def: Asset all",				true,	true,	zenAss::zAssetID()),
		zenAss::PropertyAsset::Create	("AssetB",	"", "Def: Asset TestProperty",		true,	true,	zenAss::zAssetID(), zFlagAssetType(zenConst::keAssType_TestProperty)),
		zenAss::PropertyStruct::Create	("Struct",	"",	"Def: Struct",					true,	true,	aPropertiesStruct, ZENArrayCount(aPropertiesStruct) ),
		zenAss::PropertyArray::Create	("Array1",	"", "Def: Array Float2",			true,	true,	rPropertyArrayFloat2, 1),
		zenAss::PropertyArray::Create	("Array2",	"", "Def: Array Struct",			true,	true,	rPropertyArrayStruct, 1),
		zenAss::PropertyInt::Create		("CopyInt",	"", "Def: Used by ReadOnlyInt",		true,	true,	0, -10, 10, 1),
		zenAss::PropertyInt::Create		("ReadOnlyInt",	"", "Def: Read CopyInt value",	true,	false,	0, -10, 10, 1),
		zenAss::PropertyInt2::Create	("ReadOnlyInt2","", "Def: Int2",				true,	false,	zVec2S32(2), zVec2S32(-10), zVec2S32(10), zVec2S32(1)),
	};
	static zenAss::PropertyDefArray		sarProperties( aPropertiesAll, ZENArrayCount(aPropertiesAll) );
	return sarProperties;
}

bool TestProperty::UpdatedProperties()
{
	Super::UpdatedProperties();
	zenAss::PropertyInt::ValueRef rValueSrc			= GetValue("CopyInt");
	zenAss::PropertyInt::ValueRef rValueReadonly	= GetValue("ReadOnlyInt");
	if( rValueSrc.IsValid() && rValueReadonly.IsValid() && rValueSrc.GetValue() != rValueReadonly.GetValue() )
	{
		rValueReadonly = rValueSrc.GetValue();
		return true;
	}
	return false;
}

}} //namespace zen { namespace zeAss

#endif //ZEN_ENGINETOOL