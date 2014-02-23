#pragma once
#ifndef __LibEngine_Api_ResourceGfxShaderParam_h__
#define __LibEngine_Api_ResourceGfxShaderParam_h__

namespace zen { namespace awres {	

	//=============================================================================================
	//! @class	Used for shader compiling preprocessor
	//=============================================================================================
	class awShaderDefine
	{
	AWClassDeclareNoParent(awShaderDefine)
	public:
		inline		awShaderDefine();
		inline		awShaderDefine(const char* _zName, const char* _zValue);
		inline		awShaderDefine(const awString& _zName, const awString& _zValue);
		awString	mzName;
		awString	mzValue;
	};

	//=============================================================================================
	//! @class	Used when setting the properties of a texture/sampler pair
	//=============================================================================================
	class awShaderTexture
	{
	AWClassDeclareNoParent(awShaderTexture)
	public:
		inline awShaderTexture();
		inline awShaderTexture(awHash32 _hTextureName, awResourceID _TextureID, awResourceID _SamplerID);

		awHash32		mhTextureName;
		awResourceID	mTextureID;
		awResourceID	mSamplerID;
	};

	//=============================================================================================
	//! @class	Base Class used to configure shader parameters. Useful when creating an array
	//!			of various parameters types that can set at once. Child class configure the content
	//!			of this parent
	//=============================================================================================
	class awShaderParameter
	{
	AWClassDeclareNoParent(awShaderParameter)
	public:
		awHash32	mhName;						//!< Parameter name
		awU32		meType			: 4;		//!< eShaderElementType
		awU32		muVectorSize	: 4;		//!< Number of elements in vector
		awU32		muArrayCount	: 10;		//!< Number of elements in array
		awU32		muSizeTotal		: 16;		//!< Total size of the child class
		inline const void* GetData()const {return this + 1;}

	protected:
		inline			awShaderParameter(awHash32 _hName, awconst::eShaderElementType _eType, awU16 _uVectorSize, awU16 _uArrayCount, awU16 _uSizeTotal);
	};

	template <class TType, awconst::eShaderElementType TShaderType>
	class awShaderParamVector1 : public awShaderParameter
	{
	AWClassDeclare(awShaderParamVector1, awShaderParameter)
	public:
		inline		awShaderParamVector1( awHash32 _hName, TType _Value);
		TType		mValue;
	};

	template <class TType, awconst::eShaderElementType TShaderType>
	class awShaderParamVector2 : public awShaderParameter
	{
	AWClassDeclare(awShaderParamVector2, awShaderParameter)
	public:
		inline		awShaderParamVector2( awHash32 _hName, TType _Value1, TType _Value2); 
		inline		awShaderParamVector2( awHash32 _hName, const TType _Values[2]);
		inline		awShaderParamVector2( awHash32 _hName, const awVector2<TType>& _vValue);
		TType		mValue[2];
	};

	template <class TType, awconst::eShaderElementType TShaderType>
	class awShaderParamVector3 : public awShaderParameter
	{
	AWClassDeclare(awShaderParamVector3, awShaderParameter)
	public:
		inline		awShaderParamVector3( awHash32 _hName, TType _Value1, TType _Value2, TType _Value3); 
		inline		awShaderParamVector3( awHash32 _hName, const TType _Values[3]);
		inline		awShaderParamVector3( awHash32 _hName, const awVector3<TType>& _vValue);
		TType		mValue[3];
	};

	template <class TType, awconst::eShaderElementType TShaderType>
	class awShaderParamVector4 : public awShaderParameter
	{
	AWClassDeclare(awShaderParamVector4, awShaderParameter)
	public:
		inline		awShaderParamVector4( awHash32 _hName, TType _Value1, TType _Value2, TType _Value3, TType _Value4);
		inline		awShaderParamVector4( awHash32 _hName, const TType _Values[4]);
		inline		awShaderParamVector4( awHash32 _hName, const awVector4<TType>& _vValues);
		TType		mValue[4];
	};

	typedef awShaderParamVector1<float, awconst::keShaderElemType_Float> awShaderFloat1;
	typedef awShaderParamVector2<float, awconst::keShaderElemType_Float> awShaderFloat2;
	typedef awShaderParamVector3<float, awconst::keShaderElemType_Float> awShaderFloat3;
	typedef awShaderParamVector4<float, awconst::keShaderElemType_Float> awShaderFloat4;

}} // namespace zen, awres

#include "zenResGfxShaderParam.inl"

#endif

