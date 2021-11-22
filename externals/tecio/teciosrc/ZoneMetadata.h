 #pragma once
#include "ThirdPartyHeadersBegin.h"
#include <algorithm>
#include <string>
#include <vector>
#include "ThirdPartyHeadersEnd.h"
#include "basicTypes.h"
#include "IJK.h"
#include "IJKPartitionTree.h"
#include "IJKZoneInfo.h"
#include "FEZoneInfo.h"
#include "MinMaxTree.h"
#include "zoneUtil.h"
#include "ClassicZoneFileLocations.h"
#include "PartitionMetadata.h"
#include "writeValueArray.h"
namespace tecplot { namespace ___3933 { template<typename T> ___2090::SubzoneOffset_t getNumSzFromNumItems(T ___2812) { REQUIRE(___2812>0); ___2090::SubzoneOffset_t ___3358 = static_cast<___2090::SubzoneOffset_t>((___2812 + 0xFF) >> 8); ENSURE(___3358>0); return ___3358; } class ZoneMetadata { private: UNCOPYABLE_CLASS(ZoneMetadata); private: ___4636        ___2677; ZoneType_e         ___2684; bool               m_isSZL; ___1844                m_zoneIJK; std::string        ___2495; FaceNeighborMode_e ___2458; double             ___2621; ___1172         ___2622; ___4636        ___2614; ___2090::___2980 m_numPartitions; ___1863 m_partitionTree; public: ___2240<___1881> m_ijkZoneInfos; ___2240<___465> m_ptnNumCells; ___2240<___2718> m_ptnNumNodes; ___2240<___465> m_ptnFirstCell; ___2240<___2718> m_ptnFirstNode; ___2240<___1844>         m_ptnNodeMinIJKs; ___2240<___1844>         m_ptnNodeMaxIJKs; ___2240<___2090::SubzoneOffset_t> m_ptnNumCszs; ___2240<___2090::SubzoneOffset_t> m_ptnNumNszs; ___2240<___2090::___2980> m_ptnFileNums; ___2240<___1393>                m_ptnHeaderFileLocs; ___2240<___1393>                m_varPtnMinMaxFileLocs; ___2240<MinMaxTree>               m_varPtnMinMaxTrees; ___2240<PartitionMetadata> m_ptnMetadata; ClassicZoneFileLocations             m_classicZoneFileLocations; public: ZoneMetadata() : ___2677(-1) , ___2684(___4703) , m_isSZL(false) , m_zoneIJK() , ___2495() , ___2458(___1290) , ___2621(0.0) , ___2622(___3788) , ___2614(-1) , m_numPartitions(0) { } inline void swap(ZoneMetadata& ___2888) { using std::swap; swap(___2677, ___2888.___2677); swap(___2684, ___2888.___2684); swap(m_isSZL, ___2888.m_isSZL); swap(m_zoneIJK, ___2888.m_zoneIJK); swap(___2495, ___2888.___2495); swap(___2458, ___2888.___2458); swap(___2621, ___2888.___2621); swap(___2622, ___2888.___2622); swap(___2614, ___2888.___2614); swap(m_numPartitions, ___2888.m_numPartitions); } inline ___4636 zone() const { ENSURE(___2677>=0 && ___2677<MAX_NUM_ZONES); return ___2677; } inline ZoneType_e getZoneType() const { ENSURE(VALID_ENUM(___2684,ZoneType_e)); return ___2684; } inline bool isSZL() const { return m_isSZL; } inline ___1844 const& getZoneIJK() const { ENSURE(m_zoneIJK.___2067()); return m_zoneIJK; } inline ___465 ___1766() const { REQUIRE(___2684 != ___4698 && ___2684 != ___4699); if ( ___2684 == ___4704 ) return m_zoneIJK.getNumContiguousCells(); else return m_zoneIJK.___1668(); } inline ___2718 ___1768() const { REQUIRE(___2684 != ___4698 && ___2684 != ___4699); if ( ___2684 == ___4704 ) return m_zoneIJK.___1768(); else return m_zoneIJK.___1670(); } inline ___682 ___1669() const { REQUIRE(___2684 != ___4704 && ___2684 != ___4698 && ___2684 != ___4699); return m_zoneIJK.___1669(); } inline ___682 ___1767() const { REQUIRE(___2684 != ___4698 && ___2684 != ___4699); if ( ___2684 == ___4704 ) return 8; else return ___1669(); } inline std::string getName() const { return ___2495; } inline FaceNeighborMode_e getFaceNeighborMode() const { ENSURE(VALID_ENUM(___2458, FaceNeighborMode_e) || ___2458 == ___1288); return ___2458; } inline double getSolutionTime() const { return ___2621; } inline ___1172 getStrandID() const { REQUIRE(___2622==___3788 || ___4312(___2622)); return ___2622; } inline ___4636 getParentZone() const { REQUIRE(___2614==-1 || (___2614 >= 0 && ___2614 < MAX_NUM_ZONES)); return ___2614; } void setZone(___4636 zone) { REQUIRE(zone >= 0 && zone < MAX_NUM_ZONES); ___2677 = zone; } void setZoneType(ZoneType_e ___4692) { REQUIRE(VALID_ENUM(___4692, ZoneType_e)); ___2684 = ___4692; } inline void setIsSZL(bool isSZL) { m_isSZL = isSZL; } inline void setIJKMax(___1844 const& ijkDim) { REQUIRE(___2684==___4704); m_zoneIJK = ijkDim; } inline void setFEDescription( ___465 ___2781, ___682 ___2789, ___2718 ___2821) { REQUIRE(___2684 != ___4704 && ___2684 != ___4698 && ___2684 != ___4699); REQUIRE(___2781>0 && ___2781 <= MAX_NUM_CELLS); REQUIRE(___2821>0 && ___2821 <= MAX_NUM_NODES); REQUIRE(___2789>0 && ___2789<=MAX_NUM_CELL_CORNERS); m_zoneIJK = ___1844(___2821, ___2781, ___2789); } inline void setName(std::string const& ___2685) { ___2495 = ___2685; } inline void setFaceNeighborMode(FaceNeighborMode_e ___1284) { REQUIRE(VALID_ENUM(___1284, FaceNeighborMode_e) || ___1284 == ___1288);
___2458 = ___1284; } inline void setSolutionTime(double ___3640) { ___2621 = ___3640; } inline void setStrandID(___1172 ___3785) { ___2622 = ___3785; } inline void setParentZone(___4636 ___2974) { REQUIRE(___2974==-1 || (___2974 >= 0 && ___2974 < MAX_NUM_ZONES)); ___2614 = ___2974; } inline ___2090::___2980 getNumPartitions() const { REQUIRE(m_isSZL); ENSURE(VALID_ITEM_ADDRESS_PARTITION(m_numPartitions-1)); return m_numPartitions; } inline ___2090::SubzoneOffset_t getNumCszsInPartition(___2090::___2980 ___2977) const { REQUIRE(m_isSZL); REQUIRE(___2977<m_numPartitions); ___2090::SubzoneOffset_t const numCszs = m_ptnNumCszs[___2977]; ENSURE(IMPLICATION(___2684==___4704, VALID_ITEM_ADDRESS_SUBZONE_OFFSET(numCszs-1))); ENSURE(IMPLICATION(___2684!=___4704, numCszs == getNumSzFromNumItems(m_ptnNumCells[___2977]))); ENSURE(numCszs > 0); return numCszs; } inline ___2090::SubzoneOffset_t getNumNszsInPartition(___2090::___2980 ___2977) const { REQUIRE(m_isSZL); REQUIRE(___2977<m_numPartitions); ___2090::SubzoneOffset_t const numNszs = m_ptnNumNszs[___2977]; ENSURE(IMPLICATION(___2684==___4704, VALID_ITEM_ADDRESS_SUBZONE_OFFSET(numNszs-1))); ENSURE(IMPLICATION(___2684!=___4704, numNszs == getNumSzFromNumItems(m_ptnNumNodes[___2977]))); ENSURE(numNszs > 0); return numNszs; } inline void setNumPartitions(___2090::___2980 numPartitions) { REQUIRE(numPartitions >= 1 && (m_isSZL ? VALID_ITEM_ADDRESS_PARTITION(numPartitions-1) : numPartitions == 1)); m_numPartitions = numPartitions; ENSURE(VALID_ITEM_ADDRESS_PARTITION(m_numPartitions-1)); } inline void addPartitionTreeItem(___2090::___2980 ___2977, ___1844 const& ___2474, ___1844 const& ___2364) { m_partitionTree.___13(___2977, ___2474, ___2364); } inline ___2090::___2980 getPartitionForIJK(___1844 const& ___1843) const { if (m_numPartitions == 1) { return 0; } else { ___1853 ___2478(___1843.i(), ___1843.___2105(), ___1843.___2134()); ___1853 ___2372(___1843.i(), ___1843.___2105(), ___1843.___2134()); std::vector<___1864> ___2099; m_partitionTree.query(boost::geometry::index::intersects(___1855(___2478, ___2372)), std::back_inserter(___2099)); return (___2099.empty() ? ___2090::INVALID_PARTITION : ___2099[0].second); } } inline std::vector<___2090::___2980> getPartitionsForIJKRange(___1844 const& ijkMin, ___1844 const& ___1861) const { if (m_numPartitions == 1) { return std::vector<___2090::___2980>(1, 0); } else { ___1853 ___2478(ijkMin.i(), ijkMin.___2105(), ijkMin.___2134()); ___1853 ___2372(___1861.i(), ___1861.___2105(), ___1861.___2134()); std::vector<___1864> ___2099; m_partitionTree.query(boost::geometry::index::intersects(___1855(___2478, ___2372)), std::back_inserter(___2099)); std::vector<___2090::___2980> ___3358; ___3358.reserve(___2099.size()); for (std::vector<___1864>::const_iterator it = ___2099.begin(); it != ___2099.end(); ++it) ___3358.push_back(it->second); std::sort(___3358.begin(), ___3358.end()); return ___3358; } } inline std::vector<___2090::___2980> getPartitionsForIndexPlane(IJKPlanes_e whichPlane, ___2718 planeIndex) const { if (m_numPartitions == 1) { return std::vector<___2090::___2980>(1, 0); } else { ___1844 planeMin(0, 0, 0); ___1844 planeMax(getZoneIJK() - 1); switch (whichPlane) { case ___1867: planeMin.setI(planeIndex); planeMax.setI(planeIndex); break; case ___1872: planeMin.setJ(planeIndex); planeMax.setJ(planeIndex); break; case ___1874: planeMin.___3497(planeIndex); planeMax.___3497(planeIndex); break; default: ___478(___1305); break; } ___1853 ___2478(planeMin.i(), planeMin.___2105(), planeMin.___2134()); ___1853 ___2372(planeMax.i(), planeMax.___2105(), planeMax.___2134()); std::vector<___1864> ___2099; m_partitionTree.query(boost::geometry::index::intersects(___1855(___2478, ___2372)), std::back_inserter(___2099)); std::vector<___2090::___2980> ___3358; ___3358.reserve(___2099.size()); for (std::vector<___1864>::const_iterator it = ___2099.begin(); it != ___2099.end(); ++it) ___3358.push_back(it->second); std::sort(___3358.begin(), ___3358.end()); return ___3358; } } inline std::vector<___2090::___2980> getPartitionsForIndexLine(IJKLines_e whichLine, ___2718 mIndex, ___2718 nIndex) const { if (m_numPartitions == 1) { return std::vector<___2090::___2980>(1, 0); } else { ___1844 lineMin(0, 0, 0); ___1844 lineMax(getZoneIJK() - 1); switch (whichLine) { case ___1857: lineMin.setJ(mIndex); lineMin.___3497(nIndex); lineMax.setJ(mIndex); lineMax.___3497(nIndex); break; case ___1859: lineMin.setI(mIndex); lineMin.___3497(nIndex); lineMax.setI(mIndex); lineMax.___3497(nIndex); break; case ___1860: lineMin.setI(mIndex); lineMin.setJ(nIndex); lineMax.setI(mIndex); lineMax.setJ(nIndex); break; default: ___478(___1305); break; } ___1853 ___2478(lineMin.i(), lineMin.___2105(), lineMin.___2134()); ___1853 ___2372(lineMax.i(), lineMax.___2105(), lineMax.___2134());
std::vector<___1864> ___2099; m_partitionTree.query(boost::geometry::index::intersects(___1855(___2478, ___2372)), std::back_inserter(___2099)); std::vector<___2090::___2980> ___3358; ___3358.reserve(___2099.size()); for (std::vector<___1864>::const_iterator it = ___2099.begin(); it != ___2099.end(); ++it) ___3358.push_back(it->second); std::sort(___3358.begin(), ___3358.end()); return ___3358; } } inline bool ijkPartitionMetadataIsLoaded(___2090::___2980 ___2977) const { return ___2977 < m_ijkZoneInfos.size() && m_ijkZoneInfos[___2977].___2067(); } inline ___2090 cellAddressAtIJKPaddedCellIndex(___465 paddedCellIndex) const { REQUIRE(paddedCellIndex < getZoneIJK().getNumPaddedCells()); ___2090 ___451; if (getNumPartitions() == 1) { ___451 = m_ijkZoneInfos[0].cellAddressAtPaddedCellIndex(paddedCellIndex); } else { ___1844 const ___4632 = getZoneIJK().ijkAtOffset(paddedCellIndex); ___2090::___2980 const ___2977 = getPartitionForIJK(___4632); ___478(ijkPartitionMetadataIsLoaded(___2977)); ___1844 partitionIJK = ___4632 - m_ptnNodeMinIJKs[___2977]; if (partitionIJK.i() == m_ijkZoneInfos[___2977].___2895().i() - 1) partitionIJK.setI(partitionIJK.i() - 1); if (partitionIJK.___2105() == m_ijkZoneInfos[___2977].___2895().___2105() - 1) partitionIJK.setJ(partitionIJK.___2105() - 1); ___451 = m_ijkZoneInfos[___2977].cellAddressAtCellIJK(partitionIJK); ENSURE(___451.___2977() == ___2977); } return ___451; } inline ___2090 nodeAddressAtIJKNodeIndex(___2718 ___2716) const { ___2090 nodeAddress; if (getNumPartitions() == 1) { nodeAddress = m_ijkZoneInfos[0].nodeAddressAtNodeIndex(___2716); } else { ___1844 const ___4632 = getZoneIJK().ijkAtOffset(___2716); ___2090::___2980 const ___2977 = getPartitionForIJK(___4632); ___478(ijkPartitionMetadataIsLoaded(___2977)); ___1844 const partitionIJK = ___4632 - m_ptnNodeMinIJKs[___2977]; nodeAddress = m_ijkZoneInfos[___2977].nodeAddressAtNodeIJK(partitionIJK); ENSURE(nodeAddress.___2977() == ___2977); } return nodeAddress; } inline void findPartitionContainingIndex( ___81&                          ptnItemIndex, ___2090::___2980&            ___2977, ___2240<___81> const& ptnNumItems) const { ___2090::___2980 numPartitions = getNumPartitions(); if ( numPartitions > 1 ) { while (true) { ___2718 const numPtnItems = ptnNumItems[___2977]; if ( ptnItemIndex < numPtnItems ) break; ptnItemIndex -= numPtnItems; ++___2977; ___478(___2977 < numPartitions); } } } inline ___2090 itemAddressAtFEIndex( ___81                           itemIndex, ___2240<___81> const& ptnNumItems) const { ___81 ptnItemIndex = itemIndex; ___2090::___2980 ___2977 = 0; findPartitionContainingIndex(ptnItemIndex, ___2977, ptnNumItems); ___2090::SubzoneOffset_t  const ___2763 = ___2090::SubzoneOffset_t(ptnItemIndex >> ___2090::ItemOffsetBitSize); ___2090::ItemOffset_t const itemOffset = ___2090::ItemOffset_t(ptnItemIndex & ___2090::MAX_ITEM_OFFSET); return ___2090(___2977, ___2763, itemOffset); } inline ___81 indexAtFEItemAddress( ___2090                          ___2089, ___2240<___81> const& ptnNumItems) const { ___81 itemIndex = (___81(___2089.subzoneOffset())<<___2090::ItemOffsetBitSize) | ___2089.itemOffset(); ___2090::___2980 ___2977 = ___2089.___2977(); while ( ___2977 > 0 ) { --___2977; itemIndex += ptnNumItems[___2977]; } return itemIndex; } ___2090 cellAddressAtFECellIndex(___465 zoneCellIndex) const { REQUIRE(zoneCellIndex < ___1766()); return itemAddressAtFEIndex(zoneCellIndex, m_ptnNumCells); } ___465 cellIndexAtFECellAddress(___2090 ___451) const { REQUIRE(VALID_ITEM_ADDRESS(___451)); return indexAtFEItemAddress(___451, m_ptnNumCells); } ___2090 nodeAddressAtFENodeIndex(___2718 zoneNodeIndex) const { REQUIRE(zoneNodeIndex < ___1768()); return itemAddressAtFEIndex(zoneNodeIndex, m_ptnNumNodes); } ___2718 nodeIndexAtFENodeAddress(___2090 nodeAddress) const { REQUIRE(m_isSZL); REQUIRE(VALID_ITEM_ADDRESS(nodeAddress)); return indexAtFEItemAddress(nodeAddress, m_ptnNumNodes); } ___465 paddedCellIndexAtIJKCellAddress(___2090 ___451) const { ___465 paddedCellIndex; if (getNumPartitions() == 1) { paddedCellIndex = m_ijkZoneInfos[0].paddedCellIndexAtCellAddress(___451); } else { ___2090::___2980 const ___2977 = ___451.___2977(); ___478(ijkPartitionMetadataIsLoaded(___2977)); ___1844 const cellIJK = m_ptnNodeMinIJKs[___2977] + m_ijkZoneInfos[___2977].cellIJKAtCellAddress(___451); paddedCellIndex = getZoneIJK().offsetAtIJK(cellIJK); } ENSURE(paddedCellIndex < getZoneIJK().getNumPaddedCells()); return paddedCellIndex; } ___2718 nodeIndexAtIJKNodeAddress(___2090 nodeAddress) const { REQUIRE(getZoneType() == ___4704);
___2718 ___2716; if (getNumPartitions() == 1) { ___2716 = m_ijkZoneInfos[0].nodeIndexAtNodeAddress(nodeAddress); } else { ___2090::___2980 const ___2977 = nodeAddress.___2977(); ___478(ijkPartitionMetadataIsLoaded(___2977)); ___1844 const nodeIJK = m_ptnNodeMinIJKs[___2977] + m_ijkZoneInfos[___2977].nodeIJKAtNodeAddress(nodeAddress); ___2716 = getZoneIJK().offsetAtIJK(nodeIJK); } ENSURE(___2716 < ___1768()); return ___2716; } ___465 getNumIJKFaceNeighbors( ___2090 ___451, FaceIndex_t ___457) const { REQUIRE(m_isSZL); REQUIRE(___457 < NUM_IJK_CELL_FACES); ___2090::___2980 const ___2977 = ___451.___2977(); ___478(ijkPartitionMetadataIsLoaded(___2977)); return m_ijkZoneInfos[___2977].getNumIJKFaceNeighbors(___451, ___457); } void getIJKFaceNeighbor( ___2090  ___451, FaceIndex_t  ___457, ___465  neighborOffset, ___2090& fnCoord, ___4636& fnZone) const { REQUIRE(___451.isSzlItem()); REQUIRE(m_isSZL); REQUIRE(___457 < NUM_IJK_CELL_FACES); REQUIRE(neighborOffset < getNumIJKFaceNeighbors(___451, ___457)); ___2090::___2980 const ___2977 = ___451.___2977(); ___478(ijkPartitionMetadataIsLoaded(___2977)); m_ijkZoneInfos[___2977].getIJKFaceNeighbor(___451, ___457, neighborOffset, fnCoord, fnZone); if (fnCoord == ___2090(___2749) && getNumPartitions() > 1) { ___1844 neighborCellIJK = m_ijkZoneInfos[___2977].cellIJKAtCellAddress(___451) + m_ptnNodeMinIJKs[___2977] + ___1881::ijkFaceNeighborOffset[___457]; if (0 <= neighborCellIJK && neighborCellIJK < getZoneIJK()) { ___2090::___2980 neighborPartition = getPartitionForIJK(neighborCellIJK); neighborCellIJK -= m_ptnNodeMinIJKs[neighborPartition]; if (neighborCellIJK <= m_ijkZoneInfos[neighborPartition].___2198()) fnCoord = m_ijkZoneInfos[neighborPartition].cellAddressAtCellIJK(neighborCellIJK); } } } void getIJKFaceNeighbors( ___2090            ___451, FaceIndex_t            ___457, ___3269<___2090>& cellNeighbors, ___3269<___4636>& zoneNeighbors, bool&                  isFaceCompletelyObscured) const { REQUIRE(VALID_ITEM_ADDRESS(___451)); REQUIRE(___457 < NUM_IJK_CELL_FACES); REQUIRE(cellNeighbors.empty()); REQUIRE(zoneNeighbors.empty()); ___2090 szlCellAddr; bool const isCellAddressUniform = ___451.___2065(); if (isCellAddressUniform) { ___465 const paddedCellIndex = ___465(___451.___4258()); szlCellAddr = cellAddressAtIJKPaddedCellIndex(paddedCellIndex); } else { szlCellAddr = ___451; } ___465 const numNeighbors = getNumIJKFaceNeighbors(szlCellAddr, ___457); ___478(numNeighbors != 0); isFaceCompletelyObscured = true; cellNeighbors.reserve(numNeighbors); cellNeighbors.___3503(numNeighbors); zoneNeighbors.reserve(numNeighbors); zoneNeighbors.___3503(numNeighbors); for (___465 n = 0; n < numNeighbors; ++n) { ___2090 fnCoord; ___4636 fnZone; getIJKFaceNeighbor(szlCellAddr, ___457, n, fnCoord, fnZone); if (fnCoord.___2065() && fnCoord.___4258() == ___2749) { ___478(fnZone == ___2750); cellNeighbors[n] = ___2090(___2749); zoneNeighbors[n] = ___2750; } else if (isCellAddressUniform) { cellNeighbors[n] = ___2090(paddedCellIndexAtIJKCellAddress(fnCoord)); zoneNeighbors[n] = fnZone; } else { cellNeighbors[n] = fnCoord; zoneNeighbors[n] = fnZone; } } ENSURE(!cellNeighbors.empty()); ENSURE(cellNeighbors.size() == zoneNeighbors.size()); } }; }}
