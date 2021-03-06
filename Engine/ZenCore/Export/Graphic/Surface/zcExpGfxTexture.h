#pragma once

namespace zcExp
{
	struct TextureBlockInfo
	{
		zU8		muWidth;		// Width of a block
		zU8		muHeight;		// Height of a block
		zU16	muSize;			// Bytes size of a block
	};

	//! @todo find better location for class
	struct MipInfo
	{
		MipInfo()
		: mvDim(0,0)
		, muStride(0)
		{}
			
		zArrayStatic<zU8>		maData;
		zVec2U16				mvDim;
		zU32					muStride;			
	};

	struct ExportInfoGfxTexture2D : public ExportInfoBase
	{	
		zArrayStatic<MipInfo>		maMipData;
		zenConst::eTextureFormat	meFormatInput;	
		zenConst::eTextureFormat	meFormatOutput;
		zFlagResTexUse				mCreationFlags;
		zU8							mbGenerateMip;
	};

	class ExportGfxTexture2D : public zenRes::zExportData
	{
	zenClassDeclare(ExportGfxTexture2D, zenRes::zExportData)
	public:
		zArrayStatic<MipInfo>		maMipData;
		zenConst::eTextureFormat	meFormat;
		zFlagResTexUse				mCreationFlags;
	};

	const TextureBlockInfo& GetTextureBlockInfo( zenConst::eTextureFormat _eFormat );	
	zResID CreateGfxTexture2D( zenConst::eTextureFormat _eFormat, zFlagResTexUse _CreationFlags, zVec2U16 _vDim, const zArrayBase<zU8>& _aRawData=zArrayStatic<zU8>(zUInt(0)) );

}
