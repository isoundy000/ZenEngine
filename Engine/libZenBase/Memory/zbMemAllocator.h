#pragma once
#ifndef __LibZenBase_Memory_Allocator_h__
#define __LibZenBase_Memory_Allocator_h__

namespace zbMem
{
	//=================================================================================================
	//! @class		AllocHeader
	//-------------------------------------------------------------------------------------------------
	//! @brief		Informations about a memory allocation
	//! @details	Every allocation has this layout [Optional][AllocHeader][Memory][Footer]
	//!				where... 
	//!					-# Optional : Per allocator type infos (can be empty)
	//!					-# AllocHeader : Infos on the allocation
	//!					-# Memory : User requested memory
	//!					-# Footer : Padding added at the end to detect buffer overrun
	//! @todo Optim:	Reduce memory footprint by packing together infos and removing debug only infos 
	//=================================================================================================
	class AllocHeader
#if AW_MEMORYDEBUG
	: public zList2xNode
	{
	ZENClassDeclare(AllocHeader, zList2xNode);
#else
	{
	ZENClassDeclareNoParent(AllocHeader);
#endif
	public:			
		zenMem::zAllocator*		mpAllocator;
		size_t					muWantedSize;
		zHash32				mhStamp;
		zU32					muOffset : 31;
		zU32					mbIsArray: 1;
		ZENInline bool				IsValid(){return mhStamp==zHash32("ValidAlloc");}
		bool					IsArray(){return mbIsArray;};
		void					Set(zenMem::zAllocator* _pAllocator, zU32 _uAllocOffset, size_t _uAllocSize, bool _bIsArray);
	};			

	AllocHeader*		GetHeader(void* _pAlloc, bool _bIsArray);					
}  

#endif
