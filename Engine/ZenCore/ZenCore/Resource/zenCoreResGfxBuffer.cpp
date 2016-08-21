#include "zcCore.h"

namespace zen { namespace zenRes {

//=================================================================================================
// CREATES
//=================================================================================================
zGfxTexture2d zGfxTexture2d::Create(zenConst::eTextureFormat _eFormat, zVec2U16 _vDim, zFlagResTexUse _CreationFlags)
{
	static zArrayStatic<zU8> aEmpty(zUInt(0));
	return zcExp::CreateGfxTexture2D(_eFormat, _CreationFlags, _vDim, aEmpty);
}

zGfxTexture2d zGfxTexture2d::Create(zenConst::eTextureFormat _eFormat, zVec2U16 _vDim, const zArrayBase<zU8>& _aRawData, zFlagResTexUse _CreationFlags)
{
	return zcExp::CreateGfxTexture2D(_eFormat, _CreationFlags, _vDim, _aRawData);
}

zGfxTarget2D zGfxTarget2D::Create(zenConst::eTextureFormat _eFormat, zVec2U16 _vDim, bool _bSrgb)
{
	return zcExp::CreateGfxRenderTarget(_eFormat, _vDim, _bSrgb);
}

zGfxVertex zGfxVertex::Create(const zArrayBase<zGfxVertex::Stream>& _aStreams, zFlagResUse _ResourceUse)
{
	return zcExp::CreateGfxVertex(_aStreams, _ResourceUse);
}

zGfxIndex zGfxIndex::Create(const zArrayBase<zU16>& _Indices, zenConst::ePrimitiveType _ePrimitiveType)
{
	return zcExp::CreateGfxIndexBuffer(_Indices, _ePrimitiveType);
}

zGfxIndex zGfxIndex::Create(const zArrayBase<zU32>& _Indices, zenConst::ePrimitiveType _ePrimitiveType)
{
	return zcExp::CreateGfxIndexBuffer(_Indices, _ePrimitiveType);
}

//=================================================================================================
// GFX VERTEX
//=================================================================================================
zU8* zGfxVertex::Lock()
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	return mpResource->Lock();
}
	
void zGfxVertex::Unlock(const zenGfx::zContext& rContext)
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	return mpResource->Unlock(rContext);
}

//=================================================================================================
// GFX INDEX
//=================================================================================================
zU8* zGfxIndex::Lock()
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	return mpResource->Lock();
}

void zGfxIndex::Unlock(const zenGfx::zContext& rContext)
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	mpResource->Unlock(rContext);
}

//=================================================================================================
// GFX TEXTURE2D
//=================================================================================================
const zVec2U16& zGfxTexture2d::GetDim()
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	zcRes::GfxTexture2d* pTexture = static_cast<zcRes::GfxTexture2d*>(mpResource);
	return pTexture->GetDim();
}

//=================================================================================================
// GFX RENDER TARGET
//=================================================================================================
bool zGfxTarget2D::IsDepth() const
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	return mpResource->IsDepth();
}

const zVec2U16& zGfxTarget2D::GetDim() const
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	return mpResource->GetDim();
}

zGfxTexture2d zGfxTarget2D::GetTexture2D()
{
	zenAssertMsg(mpResource, "No valid resource assigned");
	return mpResource->GetTexture2D();
}

} } // namespace zen, zenRes

