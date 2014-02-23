#pragma once
#ifndef __LibCore_Api_Type_HamtSmall_h__
#define __LibCore_Api_Type_HamtSmall_h__

namespace zen { namespace awtype {

	//=================================================================================================
	//! @class		awHamt
	//-------------------------------------------------------------------------------------------------
	//! @brief		Classes for managing a Hash Array Map Trie.
	//! @details	Inspired by article here : http://altdevblogaday.com/2011/03/22/ideal-hash-tries-an-implementation-in-c/ \n
	//!				and wiki here : http://en.wikipedia.org/wiki/Hash_array_mapped_trie \n
	//!				This class put emphasis on being space efficiency. Each node are of exactly the right size to contain
	//!				the amount of slots it has. The slowdown occurs when adding/removing an entry, we need to recopy each slot 
	//!				into a new node. The copy overhead shouldn't be critical though.
	//!				-# Node : Contains 0 to 'kuSlotCount' slots
	//!				-# Slot : Key + Value of element or Key + Pointer to child Node
	//!				-# Pool : Each node is created from a memory pool. There's 'kuSlotCount+1' memory pool (1 per possible slot count in a node)
	//! @todo		Specify pool size increase	
	//! @tparam TKey		Datatype of Keys used to find/retrieve entries
	//! @tparam TValue		Datatype of Values stored
	//! @tparam TIndex		Datatype bitfield used to store info of each slot in a node. Must be big enough to contain TIndexBits bits.
	//! @tparam TIndexBits	Each node level refer to subsection of TIndexBits bits of the Key entry. More bits means more slot per node, and less tree depth. 
	//=================================================================================================
	template<class TKey, class TValue, class TIndex, int TIndexBits>
	class awHamt
	{
	AWClassDeclareNoParent(awHamt)
	protected:
		//=================================================================================================
		//! @brief		Internal Hamt constants
		//=================================================================================================
		enum eConstant
		{
			kuKeyBits		= sizeof(TKey)*8,							//!< Bits count of the key used to store entries	
			kuTreeMaxDepth	= (kuKeyBits+TIndexBits-1)/TIndexBits,	//!< Maximum depth of tree (based on KeyBits/IndexBits) rounded up
			kuSlotCount		= 1<<TIndexBits,
			kuPoolCount		= kuSlotCount+1,
			kuIndexMask		= kuSlotCount-1,
		};
		
		//=================================================================================================
		//! @class		Node
		//-------------------------------------------------------------------------------------------------
		//! @brief		Contain subset if data stored in the Tree. 
		//! @detail		Used internally bu Hamt
		//=================================================================================================
		struct Node
		{
			struct Slot	{	TKey Key; union { Node* pChildNode; awU8 aValue[sizeof(TValue)]; }; 
							inline TValue& Value(){return *(TValue*)aValue;} };

			awUInt				GetSlotCount() const;						//! @brief Get count of valid Slots in this node
			bool				IsLeafSlot( awUInt _uSlotID ) const;		//! @brief Check if a Node Slot is a leaf (contains value) or point to child node
			bool				IsUsedIndex( awUInt _uNodeIndex ) const;	//! @brief Check if Node Index is being used in this Node 
			awUInt				GetSlotID( awUInt _uNodeIndex ) const;		//! @brief Get in which slot a Node Index is stored
			int					GetFirstUsedSlotID()const;					//! @brief Return first used slotID (-1 if none)			
			int					GetLastUsedSlotID()const;					//! @brief Return last used slotID (-1 if none)

			TIndex				mIndexUsed;									//!< Keep track of Node Index with a valid slot allocated
			TIndex				mSlotLeaf;									//!< Keep track of Slot that are a leaf (otherwise is link to child node)
			Slot*				mpSlots;									//!< Array of slots
		};	  
		
	public:	
		//=================================================================================================
		//! @class		Iterator
		//-------------------------------------------------------------------------------------------------
		//! @brief		Allow tree traversal, element by element
		//=================================================================================================
		class Iterator
		{
		public:
								Iterator();
								Iterator(const Iterator& _Copy);
								Iterator(const awHamt& _Parent );

			
			bool				IsValid();
			TKey				GetKey();
			TValue&				GetValue();
			void				operator++();			
			void				operator--();
			void				operator=(const Iterator& _Copy);
		protected:
			Node*				mpNodeTree[kuTreeMaxDepth];	//!< awPointer to current node parsed in each tree depth 
			awS8				mpSlotID[kuTreeMaxDepth];	//!< Current slot in each node being parsed
			awS8				msDepth;					//!< Current leaf depth level
			friend class		awHamt;
		};
		
		//=================================================================================================
		// Main Class
		//=================================================================================================
								awHamt();
								awHamt( awUInt _uReservePool, CMem::Allocator* _pAllocator=NULL );
								~awHamt();

		
		void					Init( awUInt _uReservePool, CMem::Allocator* _pAllocator=NULL );				//!< @brief Initialize the HashTable
		inline bool				Exist(const TKey _Key)const;															    
		inline bool				IsInit()const;																			    
		inline awUInt			Count() const;																	//!< @brief Number of element (leaf node) stored in hashmap		
																														    
		void					Clear();																				    
		void					SetDefaultValue( const TValue& _Value );										//!< @brief Set value return when no value found

		const TValue&			Get( const TKey _Key ) const;													//!< @brief Return value stored at a key entry
		bool					Get(const TKey _Key, TValue& _ValueOut) const;									//!< @brief Return value stored at a key entry
		bool					Get(const TKey _Key, TValue* _pValueOut) const;									//!< @brief Return value stored at a key entry
		inline const TValue&	operator[](const TKey _Key)const;												//!< @brief Return value stored at that key entry																											    
		TValue&					GetAdd(const TKey _Key);														//!< @brief Return value stored at that key entry
		bool					Unset(const TKey _Key);															//!< @brief Remove the value stored at that key entry
																														    																														    
		void					SetAll( const TValue& _Value );													//!< @brief Set all value in table, to specified value
		void					Set(const TKey _Key, const TValue& _Value);										//!< @brief Assign value at a certain key entry
		bool					SetReplace(const TKey _Key, const TValue& _Value, TValue& _OldValueOut);		//!< @brief Assign value at a certain key entry		
		void					Export( awArrayBase<TKey>& _aKey, awArrayBase<TValue>& _aValue ) const;			//!< @brief Copy the content key/value of this hamt to carrays
		void					Import( const awArrayBase<TKey>& _aKey, const awArrayBase<TValue>& _aValue );	//!< @brief Copy the content key/value from arrays to this hamt
		const awHamt&			operator=(const awHamt& _Copy);													//!< @brief Copy the content of another Hamt
																														    																														    
		void					GetFirst(Iterator& _It) const;													//!< @brief Initialize iteator to first element of the hamt
		void					GetLast(Iterator& _It) const;													//!< @brief Initialize iterator to last element of the hamt
																														    
		void					DebugPrint(const TKey _First, TKey _Last) const;								//!< @brief Print structure of the tree
		size_t					GetMemoryFootprint();															//!< @brief Return the amount of memory used by this structure		

	protected:
		
		Node*					CreateNodeCopy( const Node* _pNodeCopy );										//!< @brief	Create a copy of a node
		awUInt					GetNodeIndex( const TKey _uKey, awUInt _uDepth ) const;							//!< @brief	Return the key NodeIndex at a certain tree depth
		Node*					CreateEmptyNode(awU32 _uSlotCount);												//!< @brief	Return a new empty node with requested number of slots
		void					ClearNode( Node* _pNode );														//!< @brief	Remove every child node of this node
		TValue*					SetSlotValue(TKey _Key, const TValue& _Value, Node** _ppParentNode, awUInt _uNodeIndex, awUInt _uSlotID, awUInt _uDepth);	//!< @brief		Get the slot in a node associated to a Key. 
		bool					GetNode(TKey _Key, const Node**& _pParentSlot, awU32& _uNodeIndex, awU32& _uSlotID, awU32& _uDepth) const;	//!< @brief Find the Node(and relevant infos) associated to a Key entry
		bool					GetNode(TKey _Key, Node**& _pParentSlot, awU32& _uNodeIndex, awU32& _uSlotID, awU32& _uDepth);	//!< @brief	Find the Node(and relevant infos) associated to a Key entry		
				
		Node*					mpRootNode;				//!< First accessible node
		awU32					muCount;				//!< Keep track of element count in the table, for debug purposes
		TValue					mDefault;				//!< Default value to assign when accessing a non-existing entry
		CMem::PoolAllocator		mPools[kuPoolCount];	//!< PreAllocated memory pools, to contain our nodes	
		friend class Iterator;
	};


	//=================================================================================================
	//! @class		Hashmap
	//-------------------------------------------------------------------------------------------------
	//! @brief				PreConfigured Hamt for use as a Hashmap
	//! @tparam _Data_		Datatype of Values stored
	//! @tparam _Null_		Value to return when a Key entry isn't found
	//=================================================================================================
	template<class _Value_>
	struct Hashmap
	{
		typedef awHamt<awU16, _Value_, awU16, 4> Key16;		//!< Hashmap with 16bits Keys with node of 16 entries each (maximum tree depth of 4)
		typedef awHamt<awHash32, _Value_, awU32, 5> Key32;	//!< Size optimized hamt, 32bits Keys with node of 32 entries each (maximum tree depth of 7)
		typedef awHamt<awHash64, _Value_, awU64, 6> Key64;	//!< Size optimized hamt, 64bits Keys with node of 64 entries each (maximum tree depth of 11)
	};

	//=================================================================================================
	//! @class		SparseArray
	//-------------------------------------------------------------------------------------------------
	//! @brief				PreConfigured Hamt for use as a Hashmap
	//! @tparam _Data_		Datatype of Values stored
	//! @tparam _Null_		Value to return when a Key entry isn't found
	//=================================================================================================
	template<class _Value_>
	struct SparseArray
	{
		typedef awHamt<awU16, _Value_, awU16, 4 >Key16;		//!< Size optimized hamt, 16bits Keys with node of 16 entries each (maximum tree depth of 4)
		typedef awHamt<awU32, _Value_, awU32, 5> Key32;		//!< Size optimized hamt, 32bits Keys with node of 32 entries each (maximum tree depth of 7)
	};

} } //namespace zen, Type

#include "zenTypeHamtSmall.inl"

#endif	
