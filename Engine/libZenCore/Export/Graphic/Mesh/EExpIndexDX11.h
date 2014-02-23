#pragma once
#if !defined(__LibExport_Graphics_SerialGfxIndex_DX11_h__) && AW_EXPORT_OR_RESOURCE_DX11
#define __LibExport_Graphics_SerialGfxIndex_DX11_h__

namespace EExp
{	

class SerialGfxIndex_DX11 : public SerialIndex_Base
{
AWClassDeclare(SerialGfxIndex_DX11, SerialIndex_Base)
//-------------------------------------------------------------------------------------------------
// Serialization and Asset creation support
//-------------------------------------------------------------------------------------------------
public:
	virtual bool				Serialize				( EExp::Serializer_Base& _Serializer );
	struct SerialUseOnly
	{
		zenArrayStatic<zenU8>			maIndices;
	};
	
	SerialUseOnly				mSerial;
	D3D11_PRIMITIVE_TOPOLOGY	mePrimitiveType;	//!< Primitive type (TRIANGLELIST, TRIANGLESTRIP, ...)
	DXGI_FORMAT					meIndiceFormat;		//!< Indice size (DXGI_FORMAT_R16_UINT,DXGI_FORMAT_R32_UINT, ...)
	zenU32							muIndiceCount;		//!< Number of indice in array (maIndices.Count/muIndiceSize)	
	zenU16							muIndiceSize;		//!< Size of each indice (2Bytes, 4Bytes, ...)
	zenU32							muPrimitiveCount;	//!< Number of primitives generated by indices

//-------------------------------------------------------------------------------------------------
// Export support section
//-------------------------------------------------------------------------------------------------
protected:	
	virtual bool				ExportWork(bool _bIsTHRTask);	
};

}

#endif