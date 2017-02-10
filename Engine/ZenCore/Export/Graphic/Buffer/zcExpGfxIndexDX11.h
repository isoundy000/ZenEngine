#pragma once
#ifndef __zCore_Exp_Gfx_SerialGfxIndex_DX11_h__
#define __zCore_Exp_Gfx_SerialGfxIndex_DX11_h__

namespace zcExp
{	

class ExportGfxIndexDX11 : public ExportGfxIndex
{
zenClassDeclare(ExportGfxIndexDX11, ExportGfxIndex)
public:
	D3D11_PRIMITIVE_TOPOLOGY	mePrimitiveType;	//!< Primitive type (TRIANGLELIST, TRIANGLESTRIP, ...)
	DXGI_FORMAT					meIndiceFormat;		//!< Indice size (DXGI_FORMAT_R16_UINT,DXGI_FORMAT_R32_UINT, ...)
};

}

#endif