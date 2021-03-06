#pragma once

namespace zen { namespace zenType 
{

	//! @brief Default array size increase policy (1.5x needed size)
	//! @todo 1 safety constructor/destructor not called on individual item, just on array resize...
	typedef zUInt(*GrowthPolicyFunction)(zUInt _uCurrentCount, zUInt _uNeededCount, zUInt _uItemSize); 
	zUInt GrowthPolicyOneandHalf( zUInt _uCurrentCount, zUInt _uNeededCount, zUInt _uItemSize);

	template<class TType, GrowthPolicyFunction TGrowthPolicy=GrowthPolicyOneandHalf>
	class zArrayDynamic : public zArrayBase<TType>
	{
	zenClassDeclare(zArrayDynamic, zArrayBase<TType>)
	public:
									zArrayDynamic();
									zArrayDynamic(zU32 _uCount);
									zArrayDynamic(std::initializer_list<TType> _Entries);
									zArrayDynamic(const TType* _pCopy, zUInt _uCount, zUInt _uExtraCount=0);
									zArrayDynamic(const zArrayDynamic& _Copy, zUInt _uExtraCount=0);
		virtual						~zArrayDynamic();
		virtual zUInt				SetCount(zUInt _uCount);
		zUInt						IncCount(zUInt _uCountAddtional);

		void						operator+=( const zArrayBase<TType>& _ArrayAdd );
		void						Push(const TType& _Copy);
		void						Push(const TType* _Copy, zUInt _uCount);
		TType						Pop();

		void						RemoveSwap( zUInt _uIndex );
		void						RemoveSwap( const TType& _Item );

		void						Reset( zUInt _uReserveCount=(zUInt)-1 );
		void						Reserve(zUInt _uCount);		
		zUInt						ReservedCount()const;
		zUInt						ReservedSize()const;
		
	protected:
		zenInline zUInt				AppendInternal(const TType* _pCopy, zUInt _uCount);		
		void						Shrink( );											//!< @brief	Reduce array size when needed
		void						Grow( zUInt _auCountNeeded );						//!< @brief Increase array size when needed
		void						GrowNoConstructor( zUInt _auCountNeeded );			//!< @brief Increase array size without calling TType's constructors
		virtual zUInt				SetCountNoConstructor(zUInt _uCount);				//!< @brief Resize array without calling constructor (usefull for quick memcopy, use carefully)
		zUInt						muCountReserved;									//!< Space currently allocated
		zUInt						muCountReservedMin;									//!< Minimum space we should always have allocated
	public:
		using zArrayBase<TType>::operator=;
	};

} } //namespace zen, Type

#include "zenBaseTypeArrayDynamic.inl"
