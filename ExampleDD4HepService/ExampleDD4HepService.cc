
// This is just a sketch of how one would implement something
// like a geometry service in JANA. This does not actually
// contain any DD4hep code.
//
// A service in JANA is basically a single object held by the
// JApplication that can be requested by any other JANA
// element (e.g. JFactory or JEventProcessor objects). The JService
// base class accomodates for some more complicated dependencies
// that arise when one services relies on using other services.



#include <JANA/JEvent.h>
#include <JANA/Services/JServiceLocator.h>
#include <TVector3.h>
#include <TFile.h>

#include "ExampleDD4HepService.h"
    
extern "C" {
    void InitPlugin(JApplication *app) {
        InitJANAPlugin(app);
        app->ProvideService( std::make_shared<ExampleDD4HepService>() );        
    }
}
    
