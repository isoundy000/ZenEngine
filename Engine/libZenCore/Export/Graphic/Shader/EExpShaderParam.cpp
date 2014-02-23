#include "libZenCore.h"

namespace EExp
{

//=================================================================================================
//! @brief		Create a new Shader Parameter instance
//! @details	
//-------------------------------------------------------------------------------------------------
//! @param _ParentParamDefID	- ResoureeID of the parent Shader ParamDefinition instantiate
//! @param _aParamValues		- Values assigned to instance (overriding default values)
//! @return 					- Unique awResourceID of created Resource
//=================================================================================================
awResourceID CreateGfxShaderParam(awResourceID _ParentParamDefID, const awArrayBase<const EExp::ParameterBase*>& _aParamValues)
{
	AWAssert( _ParentParamDefID.Type() == awconst::keResType_GfxShaderParamDef );	
	static CMem::PoolAllocator sMemPool("Pool CreateShaderParam", sizeof(SerialShaderParam_Base::ExportInfo), 1, 5 );
	SerialShaderParam_Base::ExportInfo*	pExportInfo = AWNew(&sMemPool) SerialShaderParam_Base::ExportInfo;
	pExportInfo->maParamValues						= _aParamValues;
	pExportInfo->mParentParamDefID					= _ParentParamDefID;
	return EMgr::Export.CreateItem( awResourceID::kePlatformType_GFX, awconst::keResType_GfxShaderParam, pExportInfo );
}

//=================================================================================================
//! @brief		Create a new Constant Buffer
//! @details	Create a temporary SerialItem, used for creating a new Resource and then deleted.
//!				The temporary SerialItem and Asset created, will be for engine default renderer type
//-------------------------------------------------------------------------------------------------
//! @param _ParentShaderID		- Shader resource which contains the ShaderParamDef
//! @param _eShaderParamIndex	- Which one of the ShaderParamDef to use to create an instance
//! @param _aParamValues		- Values assigned to instance (overriding default values)
//! @return 					- Unique awResourceID of created Resource
//=================================================================================================
awResourceID CreateGfxShaderParam(awResourceID _ParentShaderID, EExp::eShaderParamFreq _eShaderParamIndex, const awArrayBase<const EExp::ParameterBase*>& _aParamValues)
{
	AWAssert( awconst::kFlagResShaders.Any(_ParentShaderID.Type()) );
	SerialShader_Base* pParentShader = EMgr::SerialItems.GetItem<SerialShader_Base>(_ParentShaderID);
	if( pParentShader && pParentShader->maParamDefID[_eShaderParamIndex].IsValid() )
		return CreateGfxShaderParam( pParentShader->maParamDefID[_eShaderParamIndex], _aParamValues);	
	return awResourceID();
}

}
