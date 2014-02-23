#include "libZenCore.h"

namespace EExp
{
	awResourceID SerialShader_Base::CallbackGetItemID(awconst::eResPlatform _ePlatform, awconst::eResType _eType, awconst::eResSource _eSource, const EExp::ExportInfoBase* _pExportInfo, bool& _bExistOut)
	{
		AWAssert( awconst::kFlagResShaders.Any(_eType) );
		AWAssert( _pExportInfo );
		const ExportInfo* pExportInfo		= static_cast<const ExportInfo*>(_pExportInfo);
		const awres::awShaderDefine* pEntry	= pExportInfo->maDefines.First();

		awResourceID::NameHash hName;
		hName.Append( pExportInfo->mzFilename );
		hName.Append( pExportInfo->mzEntryname );
		for(awUInt idx(0), count(pExportInfo->maDefines.Count()); idx<count; ++idx, ++pEntry)
		{
			hName.Append(pEntry->mzName);
			hName.Append(pEntry->mzValue);
		}

		return EExp::ValidateItemID(_ePlatform, _eType, _eSource, hName, _bExistOut);
	}

	static awArrayStatic<awres::awShaderDefine> saEmptyDefines(awUInt(0));
	awResourceID CreateGfxShaderVertex( const char* _zFilename, const char* _zEntryname  )
	{
		return CreateGfxShaderVertex( _zFilename, _zEntryname, saEmptyDefines );		
	}
	awResourceID CreateGfxShaderPixel( const char* _zFilename, const char* _zEntryname )
	{
		return CreateGfxShaderPixel( _zFilename, _zEntryname, saEmptyDefines );
	}

	//=================================================================================================
	//! @brief		Create a new Vertex Shader
	//! @details	
	//! @todo		Add support for defines
	//-------------------------------------------------------------------------------------------------
	//! @param _zFilename	- Filename with code content
	//! @param _zEntryname	- Name of entry function
	//! @return 			- Resource created
	//=================================================================================================
	awResourceID CreateGfxShaderVertex( const char* _zFilename, const char* _zEntryname, const awArrayBase<awres::awShaderDefine>& _aDefines  )
	{
		static CMem::PoolAllocator sMemPool("Pool CreateShaderVertex", sizeof(SerialShader_Base::ExportInfo), 1, 5 );
		SerialShader_Base::ExportInfo* pExportInfo	= AWNew(&sMemPool) SerialShader_Base::ExportInfo;
		pExportInfo->mzFilename						= _zFilename;
		pExportInfo->mzEntryname					= _zEntryname;
		pExportInfo->maDefines						= _aDefines;
		pExportInfo->meShaderStage					= EExp::keShaderStage_Vertex;
		return EMgr::Export.CreateItem( awResourceID::kePlatformType_GFX, awconst::keResType_GfxShaderVertex, pExportInfo );
	}

	//=================================================================================================
	//! @brief		Create a new Pixel Shader
	//! @details	
	//! @todo		Add support for defines
	//-------------------------------------------------------------------------------------------------
	//! @param _zFilename	- Filename with code content
	//! @param _zEntryname	- Name of entry function
	//! @return 			- Resource created
	//=================================================================================================
	awResourceID CreateGfxShaderPixel( const char* _zFilename, const char* _zEntryname, const awArrayBase<awres::awShaderDefine>& _aDefines )
	{
		static CMem::PoolAllocator sMemPool("Pool CreateShaderPixel", sizeof(SerialShader_Base::ExportInfo), 1, 5 );
		SerialShader_Base::ExportInfo* pExportInfo	= AWNew(&sMemPool) SerialShader_Base::ExportInfo;
		pExportInfo->mzFilename						= _zFilename;
		pExportInfo->mzEntryname					= _zEntryname;
		pExportInfo->maDefines						= _aDefines;
		pExportInfo->meShaderStage					= EExp::keShaderStage_Pixel;
		return EMgr::Export.CreateItem( awResourceID::kePlatformType_GFX, awconst::keResType_GfxShaderPixel, pExportInfo );
	}

	
}