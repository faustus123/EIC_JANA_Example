
#include "JFactory_EEndCapDigiHit.h"
#include "EASIC_hit.h"

#include <JANA/JEvent.h>


// This factory's job is to grab all of the EASIC_hit objects
// and filter out the ones not belonging to the tracker 
// endcaps. At the same time, translate them from the natural DAQ
// coordinates of crate,slot,channel into the natural coordinates
// of the detector: layer, chip, pixel. (n.b. IDK the actual natural
// coordinates of the detector, but this gives the idea.)
//
// This example is not entirely realistic. In a real implmentation,
// it would only make sense to go through the EASIC_hit objects
// once and convert them for all detectors at once rather than have
// each detector go through the enitre list itself.


//------------------------
// Constructor
//------------------------
JFactory_EEndCapDigiHit::JFactory_EEndCapDigiHit(){
    SetTag("");
}

//------------------------
// Init
//------------------------
void JFactory_EEndCapDigiHit::Init() {

    // Here is where you would normally grab any configuration
    // parameters needed and store them in data members to
    // be used later. Also any calibration constants, though
    // we don't use those here.
}

//------------------------
// ChangeRun
//------------------------
void JFactory_EEndCapDigiHit::ChangeRun(const std::shared_ptr<const JEvent> &event) {

    // This is called when there is a change in the stream that could
    // require a new set of calibration constants to be read. This will
    // always be called at least once, when the first event this factory
    // sees is processed. 
    // Normally, the constants would be read and stored in data members 
    // for use in the Process callback.

    /// This is automatically run before Process, when there's a change
    /// in the stream that could require a new set of calibration constants
    /// to be read. This would be done by asking a JService to give us
    /// the relevant calibrations for this data.
    
    // auto run_nr = event->GetRunNumber();
    // m_calibration = m_service->GetCalibrationsForRun(run_nr);
}

//------------------------
// Process
//------------------------
void JFactory_EEndCapDigiHit::Process(const std::shared_ptr<const JEvent> &event) {

    /// JFactories are local to a thread, so we are free to access and modify
    /// member variables here. However, be aware that events are _scattered_ to
    /// different JFactory instances, not _broadcast_: this means that JFactory 
    /// instances only see _some_ of the events. 
    
    /// Acquire inputs (This may recursively call other JFactories)
    auto asic_hits = event->Get<EASIC_hit>();  // asic_hits is of type: std::vector<const EASIC_hit*>

    /// Loop over all ASIC hits, grabbing the ones from the Tracker endcaps
    /// and creating EEndCapDigiHit objects from them.
    std::vector<EEndCapDigiHit*> endcapdigihits;
    
    for( auto asic_hit : asic_hits ){

        // At this point we would want to access a translation table to
        // to convert from the DAQ coordinates to detector coordinates.
        // That is beyond the scope of this example so just fake it.
        
        if( asic_hit->crate!=16 ) continue;  // only interested in hits from crate 16
        if( asic_hit->slot > 8  ) continue;  // only interested in hits from slots 0-8

        auto layer = 1 + asic_hit->slot;    // faking translation table. layer should be
                                            // 1-9 with 1-4 being electron endcap and 
                                            // 5-9 hadron endcap 
        
        auto chip  = asic_hit->chan>>4;     // faking translation table.
        auto pixel = asic_hit->chan&(0x0F); // faking translation table.

        auto endcapdigihit = new EEndCapDigiHit(layer, chip, pixel, asic_hit->t);
        //endcapdigihit->AddAssociatedObject( asic_hit ); // optional: Record object(s) this came from -- disabled for TObject
        endcapdigihits.push_back( endcapdigihit );
    }
    
    /// Publish outputs
    Set( endcapdigihits );
}
