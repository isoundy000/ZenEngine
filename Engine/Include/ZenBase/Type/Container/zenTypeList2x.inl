
//==================================================================================================
//! @brief		Add new items to the list, sorted by a reference value
//! @note		The value used as a reference for comparison is based on its offset from the item base address. 
//!				This means :
//!				-# Item must inherit from awList2xNode
//!				-# All item most be of same type
//!				-# awPointer to compare data must be a member of the item to add (to be able to use it as an offset)
//!				This avoid using more costly virtual functions.
//--------------------------------------------------------------------------------------------------
//! @param[in]	_pAdd		- awPointer to Item to add
//! @param[in]	_pReference - awPointer to data used to compare
//==================================================================================================
template<class _Type_>
void awList2x::AddSort( awList2xNode* _pAdd,  _Type_* _pReference )
{
	awList2xNode*	pItemCur	= moRoot.LstNext();	// 1st element
	awList2xNode* pItemPrev	= &moRoot;
	awU32 uOffset				= (awU32)_pReference - (awU32)_pAdd;
	while( (pItemCur != GetInvalid() ) && *(_Type_*)((awU32)pItemCur+uOffset) < *_pReference )
	{
		pItemPrev   = pItemCur;
		pItemCur    = pItemCur->LstNext();
	}    
	InsertAfter(_pAdd, pItemPrev);
}

  
