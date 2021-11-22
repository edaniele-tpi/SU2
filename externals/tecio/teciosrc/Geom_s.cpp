#include "MASTER.h"
#include "GLOBAL.h"
___1632::___1632() : ___4263(0) , ___1652((GeomType_e)0) , ___3167((CoordSys_e)0) , position(*this) , ___227(0) , ___4600(0) , ___351(0) , ___2023(0) , ___1410(0) , ___2264((LinePattern_e)0) , ___2987(0.0) , ___2290(0.0) , ___3443((Scope_e)0) , ___1113((DrawOrder_e)0) , ___496((Clipping_e)0) , ___907((FieldDataType_e)0) , ___2331(NULL) , ___188((ArrowheadStyle_e)0) , ___176((ArrowheadAttachment_e)0) , ___187(0.0) , ___171(0.0) , ___2794(0) , ___1884(NULL) , WorldFileName(NULL) , EmbeddedLpkImageNumber(0) , ___2333(0) , ___3089(0.0) , ___2836(0) , ___1890((ImageResizeFilter_e)0) , ___1882(NULL) , ___2704(NULL) , ___3176(NULL) , _WorldFileAssignedWidth(0.0) , _WorldFileAssignedHeight(0.0) , _WorldFileAssignedXPos(0.0) , _WorldFileAssignedYPos(0.0) { memset(___2838, 0, sizeof(___2838)); memset(&___1573, 0, sizeof(___1573)); } ___1632::GeomAnchor::GeomAnchor(___1632& outer) : m_outer(outer) , m_XOrTheta(0.0) , m_YOrR(0.0) , m_Z(0.0) , m_zPosHasBeenAssigned(false) {} double ___1632::GeomAnchor::XOrTheta() const { return m_XOrTheta; } void ___1632::GeomAnchor::setXOrTheta(double ___4314) { m_XOrTheta = ___4314; } double ___1632::GeomAnchor::YOrR() const { return m_YOrR; } void ___1632::GeomAnchor::setYOrR(double ___4314) { m_YOrR = ___4314; } ___54 ___1632::GeomAnchor::anchorPosition() const { ___54 position; position.___1548.___4292 = m_XOrTheta; position.___1548.___4294 = m_YOrR; position.___1548.___4296 = Z(); return position; } double ___1632::GeomAnchor::Z() const { return m_Z; } void ___1632::GeomAnchor::setZ(double ___4314) { m_Z = ___4314; m_zPosHasBeenAssigned = true; } bool ___1632::GeomAnchor::operator==(GeomAnchor const& ___2888) const { return m_XOrTheta == ___2888.m_XOrTheta && m_YOrR     == ___2888.m_YOrR && Z()        == ___2888.Z(); } bool ___1632::GeomAnchor::operator!=(GeomAnchor const& ___2888) const { return !(*this == ___2888); } ___1632::GeomAnchor& ___1632::GeomAnchor::operator=(GeomAnchor const& ___3392) { if (this != &___3392) { m_XOrTheta =  ___3392.m_XOrTheta; m_YOrR = ___3392.m_YOrR; m_Z = ___3392.m_Z; m_zPosHasBeenAssigned = ___3392.m_zPosHasBeenAssigned; } return *this; }
