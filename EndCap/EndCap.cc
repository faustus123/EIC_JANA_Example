
#include <JANA/JEventProcessor.h>
#include <JANA/Services/JGlobalRootLock.h>
#include <JANA/JFactoryGenerator.h>
#include <TH1D.h>
#include <TFile.h>

#include "JFactory_EEndCapHit.h"
#include "EndCapProcessor.h"

// This plugin provides the EEndCapHit factory and
// a JEventProcessor: EndCapProcessor. 
// Note that multiple instances of the factory object
// are created so that they may be run in parallel
// while only a single instance of the processor object
// is created since it needs to run on every event.


extern "C" {
    void InitPlugin(JApplication *app) {
        InitJANAPlugin(app);
        app->Add( new JFactoryGeneratorT<JFactory_EEndCapHit>() );
        app->Add( new EndCapProcessor );
    }
}
    
