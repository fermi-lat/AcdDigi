#define AcdDigi_AcdDigiOrgAlg_CPP 

#include "AcdDigiOrgAlg.h"

// Gaudi specific include files
#include "GaudiKernel/MsgStream.h"
#include "GaudiKernel/AlgFactory.h"
#include "GaudiKernel/IDataProviderSvc.h"
#include "GaudiKernel/SmartDataPtr.h"

// Glast specific includes
#include "Event/TopLevel/EventModel.h"
#include "Event/TopLevel/Event.h"
#include "GaudiKernel/ObjectVector.h"
#include "Event/Digi/AcdDigi.h"
#include "Event/MonteCarlo/McIntegratingHit.h"

// for min and floor functions
#include <algorithm>
#include <cmath>

// to access an XML containing Digi parameters file
#include "xml/IFile.h"

// Define the factory for this algorithm
static const AlgFactory<AcdDigiOrgAlg>  Factory;
const IAlgFactory& AcdDigiOrgAlgFactory = Factory;

// Algorithm parameters which can be set at run time must be declared.
// This should be done in the constructor.
AcdDigiOrgAlg::AcdDigiOrgAlg(const std::string& name, ISvcLocator* pSvcLocator) :
Algorithm(name, pSvcLocator) {
    
    // Declare the properties that may be set in the job options file
    declareProperty ("xmlFile", m_xmlFile="$(ACDDIGIROOT)/xml/acdDigi.xml");
}


StatusCode AcdDigiOrgAlg::initialize() {
    
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "initialize" << endreq;
    
    // Use the Job options service to set the Algorithm's parameters
    // This will retrieve parameters set in the job options file
    setProperties();
    
    // Read in the parameters from the XML file
    xml::IFile m_ifile(m_xmlFile.c_str());
    m_lowThreshold = m_ifile.getDouble("acd", "lowThreshold");
    m_vetoThreshold = m_ifile.getDouble("acd", "vetoThreshold");
    m_highThreshold = m_ifile.getDouble("acd", "highThreshold");
    m_adcChannelsPerMeV = m_ifile.getDouble("acd", "adcChannelsPerMeV");
    
    return StatusCode::SUCCESS;
}


StatusCode AcdDigiOrgAlg::execute() {
    
    StatusCode  sc = StatusCode::SUCCESS;
    MsgStream   log( msgSvc(), name() );
    
    using namespace Event;
    
    SmartDataPtr<Event::McIntegratingHitCol> allhits(eventSvc(),EventModel::MC::McIntegratingHitCol );
    
    //Take care of insuring that data area has been created
    DataObject* pNode = 0;
    sc = eventSvc()->retrieveObject( EventModel::Digi::Event , pNode);
    
    if (sc.isFailure()) {
        sc = eventSvc()->registerObject(EventModel::Digi::Event ,new DataObject);
        if( sc.isFailure() ) {
            log << MSG::ERROR << "could not register " << EventModel::Digi::Event << endreq;
            return sc;
        }
    }
    
    Event::AcdDigiCol* digiCol = new Event::AcdDigiCol;
    
    // loop over hits, skip if not in ACD, then if below threshold
    for (Event::McIntegratingHitVector::const_iterator it = allhits->begin(); it != allhits->end(); it++) {
        
        idents::VolumeIdentifier volId = ((idents::VolumeIdentifier)(*it)->volumeID());
        if(volId[0] != 1 ) continue; 
        
        double energyDeposited = (*it)->totalEnergy();
        log << MSG::DEBUG << "tile volid found: " << volId.name() << ", energy deposited: "<< energyDeposited<< " MeV" << endreq;
        
        /// check that we're above low threshold, otherwise skip
        if (energyDeposited < m_lowThreshold) continue;

        // unpack from volume id. (Should be put into AcdId) 
        int layer=0, face=volId[1], column=volId[2], row=volId[3];
                
        bool overLow  = true,
             overVeto = energyDeposited > m_vetoThreshold,
             overHigh = energyDeposited > m_highThreshold;
        
        /// using conversion from ROOTWriter for now to get PHA
        unsigned short pha = static_cast<unsigned short>(std::min((float)floor(energyDeposited * m_adcChannelsPerMeV), 4095.0f)) ;

        unsigned short phaArr[2] = { pha, 0 };
        bool vetoArr[2] = { overVeto, false };
        bool lowArr[2] = { overLow, false };
        bool highArr[2] = { overHigh, false };
        
        log << MSG::DEBUG << "AcdId: " << layer << " " << face << " " 
            << row << " " << column <<endreq;

        digiCol->push_back(
            new AcdDigi(
                idents::AcdId(layer, face, row, column), volId,
                energyDeposited, phaArr, 
                vetoArr, lowArr, highArr) );   
        
    }

    return eventSvc()->registerObject(EventModel::Digi::AcdDigiCol, digiCol);
    
}


StatusCode AcdDigiOrgAlg::finalize() {
    
    MsgStream log(msgSvc(), name());
    log << MSG::INFO << "finalize" << endreq;
    
    return StatusCode::SUCCESS;
}





