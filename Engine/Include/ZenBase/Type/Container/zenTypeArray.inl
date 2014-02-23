namespace zen { namespace awtype {

template<class TType>
awArrayBase<TType>::awArrayBase(CMem::Allocator* _pAllocator=NULL)
: mpAllocator(_pAllocator)
, mpData(NULL)
, muCount(0)
{
}

template<class TType>
void awArrayBase<TType>::Sort()
{
	CAlg::Quicksort<TType>(mpData, &mpData[muCount-1]);	
}

template<class TType>
void awArrayBase<TType>::Clear()
{
	SetCount(0);
}

template<class TType>
TType* awArrayBase<TType>::First()
{
	return mpData;
}

template<class TType>
const TType* awArrayBase<TType>::First()const
{
	return mpData;
}

template<class TType>
TType* awArrayBase<TType>::Last()
{
	return muCount ? (mpData + muCount - 1) : NULL;
}

template<class TType>
const TType* awArrayBase<TType>::Last()const	
{
	return muCount ? (mpData + muCount - 1) : NULL;
}

template<class TType>
awUInt awArrayBase<TType>::Count()const
{
	return muCount;
}

template<class TType>
awUInt awArrayBase<TType>::Size()const
{
	return muCount*sizeof(TType);
}	

template<class TType>
awUInt awArrayBase<TType>::SizeElement()const			
{
	return sizeof(TType);
}

template<class TType>
void awArrayBase<TType>::SetAll(const TType& _Value) 
{
	SetRange(_Value);
}

template<class TType>
TType& awArrayBase<TType>::operator[](awUInt _uIndex)
{
	AWAssert(_uIndex<muCount);
	return mpData[_uIndex];
}

template<class TType>
const TType& awArrayBase<TType>::operator[](awUInt _uIndex)const
{
	AWAssert(_uIndex<muCount);
	return mpData[_uIndex];
}

//==================================================================================================
//! @brief		Search for a value inside array
//! @details	
//--------------------------------------------------------------------------------------------------
//! @param _Value	- Element to look for
//! @return			- Index of element (or -1 if not found)
//==================================================================================================
template<class TType>
int awArrayBase<TType>::Find(const TType& _Value)
{
	TType* pItemCur	= mpData;
	TType* pItemEnd	= mpData+muCount;
	while( pItemCur < pItemEnd )
	{
		if( *pItemCur == _Value )	return int(pItemCur-mpData);
		else						++pItemCur;
	}
	return -1;
}

//==================================================================================================
//! @brief		Copy array value to this array
//! @details	
//--------------------------------------------------------------------------------------------------
//! @param _aCopy	- Array to copy
//! @return			- This object
//==================================================================================================
template<class TType>
awArrayBase<TType>& awArrayBase<TType>::operator=( const awArrayBase<TType>& _aCopy )
{
	Copy(_aCopy.First(), _aCopy.Count() );
	return *this;
}

//==================================================================================================
//! @details	Copy an array of item into this object
//!				If the array template type supports a straight memcopy, will use this instead of 
//!				more costly one by one elements copy. But for non basic type, we do need to copy 
//!				each element individually, since their operator= might be doing some internal work
//--------------------------------------------------------------------------------------------------
//! @param _pCopy	- 1st element to copy		
//! @param _uCount	- Number of element to copy
//! @return			- Number of element after copy
//==================================================================================================
template<class TType>
awUInt awArrayBase<TType>::Copy(const TType* _pCopy, awUInt _uCount)
{	
	Clear();
	SetCount(_uCount);
	if( AWSupportsMemCopy<TType>::value )
	{
		zenMem::Copy(mpData, _pCopy, sizeof(TType)*_uCount);
	}	
	else
	{
		TType* pItemCur	= mpData;
		TType* pItemEnd	= mpData+muCount;
		while( pItemCur < pItemEnd )
			*pItemCur++ = *_pCopy++;		
	}
	return muCount;
}		

//==================================================================================================
//! @details	Allow to copy from another array of different type, as long as the type support
//!				equal assignment
//--------------------------------------------------------------------------------------------------
//! @param		_ImportArray	- Pointer to elements to copy
//! @param		_uCount			- Number of element to copy
//! @return						- Number of element after copy
//==================================================================================================
template<class TType> template<class TTypeImport>
awUInt awArrayBase<TType>::Copy(const TTypeImport* _ImportArray, awUInt _uCount )
{
	Clear();
	SetCount(_uCount);
	TType*				pDataDest	= mpData;
	TType*				pDataEnd	= &mpData[_uCount];
	const TTypeImport*	pDataSrc	= _ImportArray;
	while( pDataDest < pDataEnd )
		*pDataDest++ = *pDataSrc++;

	return muCount;
}

//==================================================================================================
//! @details	Allow to copy from another array of different type, as long as the type support
//!				equal assignment
//--------------------------------------------------------------------------------------------------
//! @param		_ImportArray	- Array to copy
//! @return						- Number of element after copy
//==================================================================================================
template<class TType> template<class TTypeImport>
awUInt awArrayBase<TType>::Copy( const awArrayBase<TTypeImport>& _ImportArray )
{
	Clear();
	SetCount(_ImportArray.Count());
	TType*				pDataDest	= mpData;
	TType*				pDataEnd	= &mpData[muCount];
	const TTypeImport*	pDataSrc	= _ImportArray.First();
	while( pDataDest < pDataEnd )
		*pDataDest++ = *pDataSrc++;

	return muCount;
}

//==================================================================================================
//! @details	
//--------------------------------------------------------------------------------------------------
//! @param _Value	- Value to assign
//! @param _uFirst	- First index to set
//! @param _uLast	- Last index to set (clamped to array size)
//! @return			- 
//==================================================================================================
template<class TType>
void awArrayBase<TType>::SetRange(const TType& _Value, awUInt _uFirst=0, awUInt _uLast=0xFFFFFFFF)
{
	TType*				pDataDest	= mpData;
	TType*				pDataEnd	= &mpData[_uLast>muCount ? muCount : _uLast];
	while( pDataDest < pDataEnd )
		*pDataDest++ = _Value;
}

} } //namespace zen, Type