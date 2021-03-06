// File and Version Information:
// $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/src/AcdTileList.cxx,v 1.7 2007/07/26 14:00:17 heather Exp $
// Description:

#include "AcdTileList.h"
#include <iostream>

IGeometry::VisitorRet 
AcdTileList::pushShape(ShapeType /*s*/, const UintVector& idvec, 
                       std::string name, std::string /*material*/, 
                       const DoubleVector& /*params*/, 
                       VolumeType /*type*/, SenseType /*sense*/)
{
    // concatenate the id for this node to current id.
    m_idcount.push_back(idvec.size());
    for( UintVector::const_iterator u=idvec.begin(); u!=idvec.end(); ++u){
        m_idValues.push_back(static_cast<unsigned int>(*u));
    }

    // is this what we want? add to the list if so and abort
    if ( (name.substr(0,7)=="topTile") || (name.substr(0,7)=="tile_f0") ) {
        // Pick up all volumes labelled "topTile" including bent volumes, as they will be
        // checked during application of edge effects
        this->push_back(getId());
        return AbortSubtree;
    } else if (name.substr(0,6)=="tile_f") {  // prepare for upcoming side tile name change for screws
        this->push_back(getId());
        return AbortSubtree;
    } else if (name.substr(0,8)=="sideTile" ) {
        if (name.substr(0,11) == "sideTileRow") return More;
        if (name.substr(0,10) == "sideTileR3") {
            this->push_back(getId());
            return More;  // Not sure it's necessary to return More here, but probably harmless
        }
        this->push_back(getId());
        return AbortSubtree;
    } else if (name.substr(1,9) == "RibbonTop" ) {
        // y top ribbons are not segmented - so we'll just pick up all yRibbonTop
        // all x ribbons top and side are segmented - we'd like to just pick up one instance
        // so we'll use xRibbonTopCent which seem to occur once for each X ribbon
        if (name.substr(0,10) == "yRibbonTop" ) {
            this->push_back(getId());
            return AbortSubtree;
        }
        if (name.substr(0,14) == "xRibbonTopCent") {
            this->push_back(getId());
            return AbortSubtree;
        }
        return AbortSubtree;
    } 

    // otherwise continue
    return More;
}

void AcdTileList::popShape()
{
    unsigned int count = m_idcount.back(); m_idcount.pop_back();
    while(count--){
        m_idValues.pop_back();
    }
}

idents::VolumeIdentifier AcdTileList::getId()const
{
    idents::VolumeIdentifier id(m_prefix);
    for(UintVector::const_iterator i=m_idValues.begin(); i!=m_idValues.end(); ++i) id.append(*i);
    return id;

}
