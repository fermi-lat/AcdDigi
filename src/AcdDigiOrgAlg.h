#ifndef _AcdDigi_AcdDigiOrgAlg_H
#define _AcdDigi_AcdDigiOrgAlg_H 1

#include "GaudiKernel/Algorithm.h"
namespace xml { class IFile; }

/** @class AcdDigiOrgAlg
  * @brief Algorithm to convert from hit data into digitization data 
  * for the ACD.
  * 
  * This algorithm does the work of creating the AcdDigi objects and storing 
  * them on the TDS.
  *
  * $Header: /nfs/slac/g/glast/ground/cvs/AcdDigi/src/AcdDigiOrgAlg.h,v 1.2 2002/06/05 13:22:01 heather Exp $
  */

class AcdDigiOrgAlg : public Algorithm {

public:
  AcdDigiOrgAlg(const std::string& name, ISvcLocator* pSvcLocator); 

  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:

    /// Low discrim threshold which activates PHA
    double m_lowThreshold;  
    /// High discrim threshold for CNO
    double m_highThreshold;
    /// Veto discrim threshold for nominal veto signal
    double m_vetoThreshold; 
    /// conversion from energy to ADC channels
    double m_adcChannelsPerMeV;

    /// input XML file containing parameters for Digitization
    std::string	m_xmlFile;

};


#endif // _AcdDigi_AcdDigiOrgAlg_H
