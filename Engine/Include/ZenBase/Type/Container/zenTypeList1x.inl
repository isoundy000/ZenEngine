
//==================================================================================================
//! @brief		Add new items to the list, sorted by a reference value
//! @note		The value used as a reference for comparison is based on its offset from the item base address. 
//!				This means :
//!				-# Item must inherit from zenList1xNode
//!				-# All item most be of same type
//!				-# zenPointer to compare data must be a member of the item to add (to be able to use it as an offset)
//!				This avoid using more costly virtual functions.
//--------------------------------------------------------------------------------------------------
//! @param[in]	_pAdd		- zenPointer to Item to add
//! @param[in]	_pReference - zenPointer to data used to compare
//==================================================================================================
template<class _Type_>
void zenList1x::AddSort( zenList1xNode* _pAdd,  _Type_* _pReference )
{
	zenList1xNode*	pItemCur	= moFirst.LstNext();	// 1st element
	zenList1xNode* pItemPrev	= &moFirst;
	zenU32 uOffset				= (zenU32)_pReference - (zenU32)_pAdd;
	while( (pItemCur != GetInvalid() ) && *(_Type_*)((zenU32)pItemCur+uOffset) < *_pReference )
	{
		pItemPrev   = pItemCur;
		pItemCur    = pItemCur->LstNext();
	}    
	InsertAfter(_pAdd, pItemPrev);
}

  

