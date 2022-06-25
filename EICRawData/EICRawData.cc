
#include <JANA/Services/JGlobalRootLock.h>
#include <TH1D.h>
#include <TFile.h>

#include <JANA/JFactoryGenerator.h>

#include "ERawDataSource.h"
#include "JFactory_EEndCapDigiHit.h"


// This code is the entry point for the plugin.
// It's primary job is to add any JANA objects/classes
// this plugin provides to the JApplication. 
//
// In this case, the JEventSource and one JFactory
// are added. What is actually added are generator classes
// so the framework can instantiate as many objects of
// the specified types as needed for the job.
    
extern "C" {
    void InitPlugin(JApplication *app) {
        InitJANAPlugin(app);
        app->Add(new JEventSourceGeneratorT<ERawDataSource>());
        app->Add(new JFactoryGeneratorT<JFactory_EEndCapDigiHit>());
    }
}
    
