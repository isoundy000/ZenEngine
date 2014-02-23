#include "libZenCore.h"

namespace EExp
{
	awResourceID SerialMesh_Base::CallbackGetItemID(awconst::eResPlatform _ePlatform, awconst::eResType _eType, awconst::eResSource _eSource, const EExp::ExportInfoBase* _pExportInfo, bool& _bExistOut)
	{
		AWAssert(_eType==awconst::keResType_GfxMesh);
		AWAssert( _pExportInfo );
		const ExportInfo* pExportInfo = static_cast<const ExportInfo*>(_pExportInfo);

		awResourceID::NameHash hName;
		for(awUInt meshStripIdx(0), meshStripCount(pExportInfo->maMeshStripID.Count()); meshStripIdx<meshStripCount; ++meshStripIdx)
			hName.Append( &(pExportInfo->maMeshStripID[meshStripIdx]), sizeof(awResourceID) );

		return EExp::ValidateItemID(_ePlatform, _eType, _eSource, hName, _bExistOut);
	}

	//=================================================================================================
	//! @brief		Create a new Mesh
	//! @details	Tie together all MeshStrips representing a entire Mesh
	//-------------------------------------------------------------------------------------------------
	//! @param _aMeshStripID	- List of MeshStrip this Mesh is made of
	//! @return 				- Created Mesh
	//=================================================================================================
	awResourceID CreateGfxMesh(const awArrayBase<awResourceID>& _aMeshStripID)
	{
		static CMem::PoolAllocator sMemPool("Pool CreateMesh", sizeof(SerialMesh_Base::ExportInfo), 1, 5 );
		SerialMesh_Base::ExportInfo* pExportInfo	= AWNew(&sMemPool) SerialMesh_Base::ExportInfo;
		pExportInfo->maMeshStripID					= _aMeshStripID;	
		return EMgr::Export.CreateItem( awResourceID::kePlatformType_GFX, awconst::keResType_GfxMesh, pExportInfo );
	}

}

