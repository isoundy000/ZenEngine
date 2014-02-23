#pragma once
#ifndef __LibResource_Graphics_GfxVertex_DX11_h__
#define __LibResource_Graphics_GfxVertex_DX11_h__

namespace ERes
{

class GfxVertex_DX11 : public Resource
{
	struct StreamInfo
	{
		awU8		muElementStartIndex;							//!< Index of first stream element, in maElementDef
		awU8		muElementCount;									//!< stream elements count, in maElementDef
	};
	//! @todo remove instance separation?
	struct InstanceInfo : public EExp::SerialGfxVertex_DX11
	{
		awArrayStatic<ID3D11Buffer*>			maStreamBuffer;	//!< D3D11 Buffer object
		awArrayStatic<UINT>						maStreamStride;	//!< Stride between 2 vertices of a buffer
		awArrayStatic<StreamInfo>				maStreamInfo;	//!< Element infos of stream
		awArrayStatic<D3D11_INPUT_ELEMENT_DESC>	maElementDef;	//!< D3D11 infos on each vertice element contained in all buffer (pos, uv, etc...)
	};
AWResourceDeclare(GfxVertex_DX11, InstanceInfo, awconst::keResType_GfxVertex)
public:
	
	virtual										~GfxVertex_DX11();
	virtual bool								ResourceInit();

//-----------------------------------------------------------------------------
// Common to all Vertex buffer
public:	
	awU8*										Lock();
	void										Unlock();
//-----------------------------------------------------------------------------
};


}

#endif