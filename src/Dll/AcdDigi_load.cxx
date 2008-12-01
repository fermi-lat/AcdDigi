/** 
* @file AcdDigi_load.cxx
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/src/Dll/AcdDigi_load.cxx,v 1.7 2008/10/15 15:45:40 usher Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(AcdDigi) {
    DECLARE_ALGORITHM( AcdDigiAlg );
    DECLARE_ALGORITHM( AcdDigiOrgAlg );
    DECLARE_TOOL( AcdDigiRandom );
} 

