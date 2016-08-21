#pragma once
#ifndef __zenApi_Core_ResGfxBuffer_h__
#define __zenApi_Core_ResGfxBuffer_h__

namespace zen { namespace zenRes 
{	
	class zGfxVertex : public zcRes::GfxVertexRef
	{
	ZENClassDeclare(zGfxVertex, zcRes::GfxVertexRef);
	public:
		using Super::Super;
		using Super::operator=;

		struct Element
		{
		public:
			Element(){};
			Element(zenConst::eShaderElementType _eType, zU8 _ElementCount, zenConst::eShaderSemantic _eSemantic, zU8 _Offset )
			: meType(_eType)
			, meSemantic(_eSemantic)
			, muVectorSize(_ElementCount)
			, muOffset(_Offset)
			{}

			zenConst::eShaderElementType	meType;
			zenConst::eShaderSemantic		meSemantic;
			zU8								muVectorSize;
			zU8								muOffset;		
		};

		struct Stream
		{
		public:
			zArrayStatic<zU8>				maData;
			zArrayStatic<Element>			maElements;
			zU8								muStride;
			Stream& operator=(const Stream& _Copy)
			{
				maData		= _Copy.maData;
				maElements	= _Copy.maElements;
				muStride	= _Copy.muStride;
				return *this;
			}
		};
	public:		
		zU8*					Lock();
		void					Unlock(const zenGfx::zContext& rContext);
		
		static zGfxVertex		Create(const zArrayBase<zGfxVertex::Stream>& _aStreams, zFlagResUse _ResourceUse);
	};

	class zGfxIndex : public zcRes::GfxIndexRef
	{
	ZENClassDeclare(zGfxIndex, zcRes::GfxIndexRef);
	public:
		using Super::Super;
		using Super::operator=;	

		zU8*					Lock();
		void					Unlock(const zenGfx::zContext& rContext);

		static zGfxIndex		Create(const zArrayBase<zU16>& _Indices, zenConst::ePrimitiveType _ePrimitiveType);
		static zGfxIndex		Create(const zArrayBase<zU32>& _Indices, zenConst::ePrimitiveType _ePrimitiveType);
	};

	class zGfxTexture2d : public zcRes::GfxTexture2dRef
	{
	ZENClassDeclare(zGfxTexture2d, zcRes::GfxTexture2dRef);
	public:
		using Super::Super;
		using Super::operator=;
		
		const zVec2U16&			GetDim();
		static zGfxTexture2d	Create(zenConst::eTextureFormat _eFormat, zVec2U16 _vDim, zFlagResTexUse _CreationFlags=zFlagResTexUse());		
		static zGfxTexture2d	Create(zenConst::eTextureFormat _eFormat, zVec2U16 _vDim, const zArrayBase<zU8>& _aRawData, zFlagResTexUse _CreationFlags=zFlagResTexUse());
	};

	class zGfxTarget2D : public zcRes::GfxTarget2DRef
	{
	ZENClassDeclare(zGfxTarget2D, zcRes::GfxTarget2DRef);
	public:		
		using Super::Super;
		using Super::operator=;

		bool						IsDepth()const;
		const zVec2U16&				GetDim()const;
		zGfxTexture2d				GetTexture2D();
		
		static zGfxTarget2D			Create(zenConst::eTextureFormat _eFormat, zVec2U16 _vDim, bool _bSrgb=true);
	};

}} // namespace zen, zenRes

#endif

