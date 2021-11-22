 #pragma once
#include "MASTER.h"
#include "GLOBAL.h"
#include "SzlFileLoader.h"
#include "fileStuff.h"
#include "importSzPltFile.h"
#include "RawArray.h"
#include "readValueArray.h"
namespace tecplot { namespace ___3933 { class MinMaxTree { UNCOPYABLE_CLASS(MinMaxTree) public: typedef uint32_t EntryIndex_t; private: static EntryIndex_t const CHILDREN_BITS_PER_PARENT = 6; static EntryIndex_t const NUM_CHILDREN_PER_PARENT = (1<<CHILDREN_BITS_PER_PARENT); static EntryIndex_t const MAX_DEPTH = (24+CHILDREN_BITS_PER_PARENT-1)/CHILDREN_BITS_PER_PARENT; static size_t const MIN_ENTRIES_TO_ALLOCATE = 32; static size_t const ALLOCATION_EXPANSION_FACTOR = 2; ___2240<___2481> m_minMaxArraysByDepth;
 #ifndef NO_ASSERTS
EntryIndex_t m_size;
 #endif
public: MinMaxTree() {
 #ifndef NO_ASSERTS
m_size = 0;
 #endif
} ~MinMaxTree() {} inline void swap(MinMaxTree& ___2888) { ASSERT_ONLY( ___372 const thisWasEmpty = this->empty(); ) ASSERT_ONLY( ___372 const thisWasValidlyPopulated = this->isValidlyPopulated(EntryIndex_t(this->size())); ) ASSERT_ONLY( ___372 const otherWasEmpty = ___2888.empty(); ) ASSERT_ONLY( ___372 const otherWasValidlyPopulated = ___2888.isValidlyPopulated(EntryIndex_t(___2888.size())); ) m_minMaxArraysByDepth.swap(___2888.m_minMaxArraysByDepth);
 #ifndef NO_ASSERTS
using std::swap; swap(m_size, ___2888.m_size);
 #endif
ENSURE(EQUIVALENCE(thisWasEmpty, ___2888.empty())); ENSURE(EQUIVALENCE(thisWasValidlyPopulated, ___2888.isValidlyPopulated(EntryIndex_t(___2888.size())))); ENSURE(EQUIVALENCE(otherWasEmpty, this->empty())); ENSURE(EQUIVALENCE(otherWasValidlyPopulated, this->isValidlyPopulated(EntryIndex_t(this->size())))); } static EntryIndex_t getNumEntriesAtDepth( EntryIndex_t ___2795, EntryIndex_t depth) { REQUIRE(___2795 > 0); REQUIRE(depth <= MAX_DEPTH); EntryIndex_t const shift = depth*CHILDREN_BITS_PER_PARENT; EntryIndex_t const ___3358 = ( (___2795 - 1) >> shift ) + 1; return ___3358; } ___372 empty() const { ___372 const isEmpty = m_minMaxArraysByDepth.empty(); ENSURE(VALID_BOOLEAN(isEmpty)); ENSURE(EQUIVALENCE(isEmpty,m_size==0)); return isEmpty; } ___372 isPopulated() const { return !empty() && m_minMaxArraysByDepth[MAX_DEPTH-1][0].___2067(); }
 #ifndef NO_ASSERTS
size_t size() const { REQUIRE(EQUIVALENCE(m_size==0, m_minMaxArraysByDepth.empty())); REQUIRE(IMPLICATION(m_size>0, m_size==m_minMaxArraysByDepth[0].size())); return m_size; } ___372 isValidlyPopulated(EntryIndex_t ___2795) const { REQUIRE(___2795 == m_size); return m_minMaxArraysByDepth.size() == MAX_DEPTH && m_minMaxArraysByDepth[0].size() == ___2795 && m_minMaxArraysByDepth[0][0].___2067() && m_minMaxArraysByDepth[0][___2795/2].___2067() && m_minMaxArraysByDepth[0][___2795-1].___2067() && m_minMaxArraysByDepth[MAX_DEPTH/2].size() == getNumEntriesAtDepth(___2795,MAX_DEPTH/2) && m_minMaxArraysByDepth[MAX_DEPTH/2][0].___2067() && m_minMaxArraysByDepth[MAX_DEPTH/2][getNumEntriesAtDepth(___2795,MAX_DEPTH/2)/2].___2067() && m_minMaxArraysByDepth[MAX_DEPTH/2][getNumEntriesAtDepth(___2795,MAX_DEPTH/2)-1].___2067() && m_minMaxArraysByDepth[MAX_DEPTH-1].size() == getNumEntriesAtDepth(___2795,MAX_DEPTH-1) && m_minMaxArraysByDepth[MAX_DEPTH-1][0].___2067() && m_minMaxArraysByDepth[MAX_DEPTH-1][getNumEntriesAtDepth(___2795,MAX_DEPTH-1)/2].___2067() && m_minMaxArraysByDepth[MAX_DEPTH-1][getNumEntriesAtDepth(___2795,MAX_DEPTH-1)-1].___2067(); }
 #endif
public: uint64_t numBytesAllocated(uint64_t ___2795) const { REQUIRE(___2795 == m_size); uint64_t ___2779 = m_minMaxArraysByDepth.numBytesAllocated(MAX_DEPTH); if ( !m_minMaxArraysByDepth.empty() ) { for ( EntryIndex_t depth = 0; depth < MAX_DEPTH; depth++ ) { EntryIndex_t const numEntriesAtDepth = getNumEntriesAtDepth(EntryIndex_t(___2795), depth); ___2779 += m_minMaxArraysByDepth[depth].numBytesAllocated(numEntriesAtDepth); } } return ___2779; } ___372 allocUninitialized(EntryIndex_t ___2795) { REQUIRE(___2795>0);
 #ifndef NO_ASSERTS
m_size = ___2795;
 #endif
___372 ___2039 = m_minMaxArraysByDepth.alloc(MAX_DEPTH); for ( EntryIndex_t depth = 0; ___2039 && depth < MAX_DEPTH; ++depth ) { EntryIndex_t const numEntiresAtDepth = getNumEntriesAtDepth(___2795, depth); ___2039 = m_minMaxArraysByDepth[depth].alloc(numEntiresAtDepth); } if ( !___2039 ) ___937(); ENSURE(VALID_BOOLEAN(___2039)); ENSURE(EQUIVALENCE(___2039, !m_minMaxArraysByDepth.empty())); ENSURE(IMPLICATION(___2039, !m_minMaxArraysByDepth[0].empty())); return ___2039; } void initializeWithInvalidMinMaxes(EntryIndex_t ___2795) { REQUIRE(___2795>0 && ___2795 == m_size); REQUIRE(m_minMaxArraysByDepth.size()==MAX_DEPTH); ___478(___2795 == getNumEntriesAtDepth(___2795, 0)); for ( EntryIndex_t depth = 0; depth < MAX_DEPTH; ++depth ) { EntryIndex_t const numEntiresAtDepth = getNumEntriesAtDepth(___2795, depth); ___2481& ___2480 = m_minMaxArraysByDepth[depth]; for ( EntryIndex_t entry = 0; entry < numEntiresAtDepth; entry++ ) ___2480[entry].invalidate(); } ENSURE( !m_minMaxArraysByDepth[0][0].___2067() && !m_minMaxArraysByDepth[0][___2795/2].___2067() && !m_minMaxArraysByDepth[0][___2795-1].___2067() && !m_minMaxArraysByDepth[MAX_DEPTH-1][0].___2067() ); ENSURE( !isPopulated() ); } void ___937() { m_minMaxArraysByDepth.___937();
 #ifndef NO_ASSERTS
m_size = 0;
 #endif
} void getChildRangeUsingNumEntries( EntryIndex_t  parentPos, EntryIndex_t  numEntriesAtChildDepth, EntryIndex_t& childStart, EntryIndex_t& childEnd) const { REQUIRE(numEntriesAtChildDepth>0); REQUIRE(parentPos<numEntriesAtChildDepth*NUM_CHILDREN_PER_PARENT); childStart = parentPos<<CHILDREN_BITS_PER_PARENT; ___478(childStart == parentPos*NUM_CHILDREN_PER_PARENT); childEnd = std::min(childStart+NUM_CHILDREN_PER_PARENT, numEntriesAtChildDepth); ENSURE(childStart < childEnd); ENSURE(childEnd <= numEntriesAtChildDepth); } void getChildRange( EntryIndex_t  ___2795, EntryIndex_t  parentDepth, EntryIndex_t  parentPos, EntryIndex_t& childStart, EntryIndex_t& childEnd) const { REQUIRE(___2795 == m_size); REQUIRE(isValidlyPopulated(___2795)); REQUIRE(parentDepth>0); REQUIRE(parentDepth<=MAX_DEPTH); REQUIRE(parentPos<getNumEntriesAtDepth(___2795,parentDepth)); EntryIndex_t const childDepth = parentDepth-1; EntryIndex_t const numEntriesAtChildDepth = getNumEntriesAtDepth(___2795,childDepth); getChildRangeUsingNumEntries(parentPos, numEntriesAtChildDepth, childStart, childEnd); ENSURE(childStart < childEnd); ENSURE(childEnd <= getNumEntriesAtDepth(___2795,childDepth)); } ___2479 const& getMinMaxAtDepth(EntryIndex_t depth, EntryIndex_t pos) const { REQUIRE(depth < MAX_DEPTH); REQUIRE(pos < m_minMaxArraysByDepth[depth].size()); REQUIRE(!m_minMaxArraysByDepth[depth].empty()); ___2479 const& minMax = m_minMaxArraysByDepth[depth][pos]; ENSURE(minMax.___2067()); return minMax; } bool minMaxIsValidForEntry(EntryIndex_t entry) const { REQUIRE(entry < size()); bool const ___2067 = m_minMaxArraysByDepth[0][entry].___2067(); return ___2067; } ___2479 const& ___1759(EntryIndex_t entry) const { REQUIRE(entry < size()); ___2479 const& minMax = m_minMaxArraysByDepth[0][entry]; ENSURE(minMax.___2067()); return minMax; } void ___3499( EntryIndex_t entry, double       minVal, double       maxVal) { REQUIRE(entry < size()); REQUIRE(minVal <= maxVal); m_minMaxArraysByDepth[0][entry].___3499(minVal, maxVal); ENSURE(m_minMaxArraysByDepth[0][entry].___2067()); } void ___3499( EntryIndex_t  entry, ___2479 const& minMax) { REQUIRE(entry < size()); REQUIRE(minMax.___2067()); m_minMaxArraysByDepth[0][entry].___3499(minMax); ENSURE(m_minMaxArraysByDepth[0][entry].___2067()); } void populateTree(EntryIndex_t ___2795); ___372 populateTreeFromMinMax( ___2479 const& minMax) { ___372 ___2039 = allocUninitialized(1); if ( ___2039 ) { m_minMaxArraysByDepth[0][0] = minMax; populateTree(1); } else ___937(); ENSURE(IMPLICATION(___2039,isValidlyPopulated(1))); ENSURE(IMPLICATION(___2039,isPopulated())); ENSURE(IMPLICATION(!___2039,empty())); return ___2039; } ___372 populateTreeFromFile( ___1399& file, FieldDataType_e      ___1363, EntryIndex_t         ___2795, IODescription const& ___972) { REQUIRE(___2795>0); ___372 ___2039 = allocUninitialized(___2795); switch (___1363) { case FieldDataType_Float: ___2039 = ___2039 && readMinMaxArray<float>(file, 0, ___2795, m_minMaxArraysByDepth[0], ___972); break; case FieldDataType_Double: ___2039 = ___2039 && readMinMaxArray<double>(file, 0, ___2795, m_minMaxArraysByDepth[0], ___972); break; case FieldDataType_Int32: ___2039 = ___2039 && readMinMaxArray<int32_t>(file, 0, ___2795, m_minMaxArraysByDepth[0], ___972); break; case FieldDataType_Int16: ___2039 = ___2039 && readMinMaxArray<int16_t>(file, 0, ___2795, m_minMaxArraysByDepth[0], ___972); break; case FieldDataType_Byte: case ___1365: ___2039 = ___2039 && readMinMaxArray<uint8_t>(file, 0, ___2795, m_minMaxArraysByDepth[0], ___972); break; default: ___478(___1305); ___2039 = ___1305; break; } if ( ___2039 ) populateTree(___2795); else ___937(); ENSURE(IMPLICATION(___2039,isValidlyPopulated(___2795))); ENSURE(IMPLICATION(___2039,isPopulated())); ENSURE(IMPLICATION(!___2039,empty())); return ___2039; } static void findEntriesContainingNVarValues( ___3269<MinMaxTree const*> const&     minMaxTrees, ___3269<double> const&                vals, EntryIndex_t                           ___2795, ___2090::___2980               ___2977, ___3269<___2090::SubzoneAddress>& entryAddresses) { size_t const numTrees = minMaxTrees.size(); REQUIRE(!minMaxTrees.empty()); REQUIRE(VALID_REF(minMaxTrees[0]) && minMaxTrees[0]->isValidlyPopulated(___2795)); REQUIRE(VALID_REF(minMaxTrees[numTrees/2]) && minMaxTrees[numTrees/2]->isValidlyPopulated(___2795)); REQUIRE(VALID_REF(minMaxTrees[numTrees-1]) && minMaxTrees[numTrees-1]->isValidlyPopulated(___2795)); REQUIRE(minMaxTrees.size() == vals.size()); REQUIRE(___2795 == minMaxTrees[0]->size() && ___2795 == minMaxTrees[numTrees/2]->size() && ___2795 == minMaxTrees[numTrees-1]->size()); if ( numTrees == 3 ) { MinMaxTree::findEntriesContaining3VarValues( *minMaxTrees[0], *minMaxTrees[1], *minMaxTrees[2], vals[0], vals[1], vals[2], ___2977, ___2795, entryAddresses); } else { EntryIndex_t startPos; EntryIndex_t endPos; minMaxTrees[0]->getChildRange(___2795, MinMaxTree::MAX_DEPTH, 0, startPos, endPos);
MinMaxTree::recursivelyFindEntriesContainingNVarValues( minMaxTrees, vals, MinMaxTree::MAX_DEPTH-1, startPos, endPos, ___2795, ___2977, entryAddresses); } } static void findEntriesContaining3VarValues( MinMaxTree const&                      xMinMaxTree, MinMaxTree const&                      yMinMaxTree, MinMaxTree const&                      zMinMaxTree, double                                 xVal, double                                 yVal, double                                 zVal, ___2090::___2980               ___2977, EntryIndex_t                           ___2795, ___3269<___2090::SubzoneAddress>& entryAddresses) { REQUIRE(xMinMaxTree.isValidlyPopulated(___2795)); REQUIRE(yMinMaxTree.isValidlyPopulated(___2795)); REQUIRE(zMinMaxTree.isValidlyPopulated(___2795)); REQUIRE(MAX_DEPTH==4); EntryIndex_t const numEntriesAtDepth0 = ___2795;; ___478(numEntriesAtDepth0==getNumEntriesAtDepth(___2795,0)); EntryIndex_t const numEntriesAtDepth1 = getNumEntriesAtDepth(___2795,1); EntryIndex_t const numEntriesAtDepth2 = getNumEntriesAtDepth(___2795,2); EntryIndex_t const numEntriesAtDepth3 = getNumEntriesAtDepth(___2795,3); EntryIndex_t depth3Start; EntryIndex_t depth3End; xMinMaxTree.getChildRangeUsingNumEntries(0, numEntriesAtDepth3, depth3Start, depth3End); for (EntryIndex_t depth3Pos = depth3Start; depth3Pos < depth3End; ++depth3Pos) { if ( xMinMaxTree.getMinMaxAtDepth(3,depth3Pos).containsValue(xVal) && yMinMaxTree.getMinMaxAtDepth(3,depth3Pos).containsValue(yVal) && zMinMaxTree.getMinMaxAtDepth(3,depth3Pos).containsValue(zVal) ) { EntryIndex_t depth2Start; EntryIndex_t depth2End; xMinMaxTree.getChildRangeUsingNumEntries(depth3Pos, numEntriesAtDepth2, depth2Start, depth2End); for (EntryIndex_t depth2Pos = depth2Start; depth2Pos < depth2End; ++depth2Pos) { if ( xMinMaxTree.getMinMaxAtDepth(2,depth2Pos).containsValue(xVal) && yMinMaxTree.getMinMaxAtDepth(2,depth2Pos).containsValue(yVal) && zMinMaxTree.getMinMaxAtDepth(2,depth2Pos).containsValue(zVal) ) { EntryIndex_t depth1Start; EntryIndex_t depth1End; xMinMaxTree.getChildRangeUsingNumEntries(depth2Pos, numEntriesAtDepth1, depth1Start, depth1End); for (EntryIndex_t depth1Pos = depth1Start; depth1Pos < depth1End; ++depth1Pos) { if ( xMinMaxTree.getMinMaxAtDepth(1,depth1Pos).containsValue(xVal) && yMinMaxTree.getMinMaxAtDepth(1,depth1Pos).containsValue(yVal) && zMinMaxTree.getMinMaxAtDepth(1,depth1Pos).containsValue(zVal) ) { EntryIndex_t depth0Start; EntryIndex_t depth0End; xMinMaxTree.getChildRangeUsingNumEntries(depth1Pos, numEntriesAtDepth0, depth0Start, depth0End); for (EntryIndex_t depth0Pos = depth0Start; depth0Pos < depth0End; ++depth0Pos) { if ( xMinMaxTree.getMinMaxAtDepth(0,depth0Pos).containsValue(xVal) && yMinMaxTree.getMinMaxAtDepth(0,depth0Pos).containsValue(yVal) && zMinMaxTree.getMinMaxAtDepth(0,depth0Pos).containsValue(zVal) ) { if (entryAddresses.empty()) entryAddresses.reserve(MIN_ENTRIES_TO_ALLOCATE); else if (entryAddresses.size() >= entryAddresses.capacity()) entryAddresses.reserve(entryAddresses.size() * ALLOCATION_EXPANSION_FACTOR); entryAddresses.append(___2090::SubzoneAddress(___2977, depth0Pos)); } } } } } } } } } private: static void recursivelyFindEntriesContainingNVarValues( ___3269<MinMaxTree const*> const&     minMaxTrees, ___3269<double> const&                vals, EntryIndex_t                           depth, EntryIndex_t                           startPos, EntryIndex_t                           endPos, EntryIndex_t                           ___2795, ___2090::___2980               ___2977, ___3269<___2090::SubzoneAddress>& entryAddresses); }; typedef ___2240<MinMaxTree>        MinMaxTreeArray; typedef ___2240<MinMaxTreeArray>   MinMaxTree2DArray; typedef ___2240<MinMaxTree2DArray> MinMaxTree3DArray; }}
