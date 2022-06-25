
#include "JFactory_EEndCapHit.h"

#include <EICRawData/EEndCapDigiHit.h>


#include <JANA/JEvent.h>

// The job of this factory is to create the calibrated EEndCapHit objects
// from the uncalibrated EEndCapDigiHit objects. At the same time, it will
// apply a filter to reject hits that are not within a certain radius of
// the centerline of the detector.

//------------------------
// Constructor
//------------------------
JFactory_EEndCapHit::JFactory_EEndCapHit(){
    SetTag("");
}

//------------------------
// Init
//------------------------
void JFactory_EEndCapHit::Init() {
    auto app = GetApplication();
    
    // Just for fun, create a configuration parameter named
    // EndCap:min_radius so we can set the threshold at run time.
    min_radius = 15.0;
    app->SetDefaultParameter("EndCap:min_radius", min_radius, "The minimum acceptable VTX endcap radius");
    
    /// Acquire geometry service pointer (see ExampleDD4HepService plugin)
    geomservice = app->GetService<ExampleDD4HepService>().get();
}

//------------------------
// ChangeRun
//------------------------
void JFactory_EEndCapHit::ChangeRun(const std::shared_ptr<const JEvent> &event) {
    // Here is where you would get a specific geometry based on the
    // when the data was taken. Skip it here to keep example simple.
}

//------------------------
// Process
//------------------------
void JFactory_EEndCapHit::Process(const std::shared_ptr<const JEvent> &event) {

    /// JFactories are local to a thread, so we are free to access and modify
    /// member variables here. However, be aware that events are _scattered_ to
    /// different JFactory instances, not _broadcast_: this means that JFactory 
    /// instances only see _some_ of the events. 
    
    // The EEndCapDigiHit objects are made by a factory in the EICRawData plugin.
    // That factory uses the low-level EASIC_hit objects coming from the event source
    auto endcapdigihits = event->Get<EEndCapDigiHit>();
    
    // Loop over the EEndCapDigiHit objects and create calibrated hits
    // objects with geometry info.
    std::vector<EEndCapHit *> hits;
    for( auto digihit : endcapdigihits ){
        
        auto pos = geomservice->GetVTXPixelLocation( digihit->layer, digihit->chip, digihit->pixel );
        auto r = pos.Perp();
        if( r > min_radius ){
             
            auto hit = new EEndCapHit();
            hit->x = pos.X();
            hit->y = pos.Y();
            hit->z = pos.Z();
            hit->t = ((double)digihit->t - 125.0)*2.50E-1;  // Here we would apply calibrations read from DB
            hits.push_back(hit);
        }
    }
    
    /// Publish outputs
    Set(hits);

    // n.b. if we created additional types of objects we could also add them to the event using event->Insert() )
}
