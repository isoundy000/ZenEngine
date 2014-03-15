#pragma once
#ifndef __zenBase_Memory_Pool_h__
#define __zenBase_Memory_Pool_h__

namespace zen { namespace zenMem
{
//=================================================================================================
//! @class		zAllocatorPool
//-------------------------------------------------------------------------------------------------
//! @brief		Memory pool allocator, return quickly fixed size allocations
//! @details	Very fast allocator without fragmentation
//! @todo Clean: ReAdd support for using particular allocator when allocating more memory
//=================================================================================================
class zAllocatorPool : public zAllocator
{
ZENClassDeclare(zAllocatorPool, zAllocator);
public:								
	virtual void*			Malloc				(size_t _uSize, bool _bIsArray, zU32 _uAlign=zenDefaultAlign);
	virtual	void			Free				(void* _pAlloc, void* _pInfoAlloc);
	virtual zDebugString	GetDescription()	{return zDebugString("Pool");}

public:
							zAllocatorPool		();
							zAllocatorPool		(const zDebugString& _zName, size_t _uItemSize, zU32 _uItemCount, zU32 _uItemIncrease, zU32 _uAlign=zenDefaultAlign );
	virtual					~zAllocatorPool		();
			void			Init				(const zDebugString& _zName, size_t _uItemSize, zU32 _uItemCount, zU32 _uItemIncrease, zU32 _uAlign=zenDefaultAlign );
			void			MemoryIncrease		(zU32 _uItemCount);
			void			ReInit				();
			void			MemoryReleaseUnused	();
			size_t			GetItemSize			()const;
			size_t			GetReservedSize		()const;
			zU32			GetReservedCount	()const;
			zU32			GetIncreaseCount	()const;
			void			SetIncreaseCount	(zU32 _uIncreaseCount);
			void			Clear				();
protected:	
	zU32					mPoolReservedCount;	//!< Number of pool item reserved
	size_t					mPoolItemSize;		//!< Size of each pool item
	zU32					mPoolItemIncrease;	//!< Amount of new item when pool runs out of item (0 for none)
	zU32					mPoolItemAlign;		//!< Each item alignement
	zU32					mPoolItemCountInit; //!< Original pool item reserved
	zList1x					mlstFreeItems;		//!< List of the free pre-allocated items	
	zList1x					mlstAlloc;			//!< List of allocations done from mpAllocator to reserve space in the pool
};

} } //namespace zen { namespace zenMem


#endif
