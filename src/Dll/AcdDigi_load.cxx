/** 
* @file AcdDigi_load.cxx
* @brief This is needed for forcing the linker to load all components
* of the library.
*
*  $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/src/Dll/AcdDigi_load.cxx,v 1.4 2002/09/09 16:43:05 heather Exp $
*/

#include "GaudiKernel/DeclareFactoryEntries.h"

DECLARE_FACTORY_ENTRIES(AcdDigi) {
    DECLARE_ALGORITHM( AcdDigiAlg );
    DECLARE_ALGORITHM( AcdDigiMcIntHitAlg );
    DECLARE_ALGORITHM( AcdDigiOrgAlg );
    DECLARE_TOOL( AcdDigiRandom );
} 

