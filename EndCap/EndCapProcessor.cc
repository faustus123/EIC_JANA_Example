
#include "EndCapProcessor.h"
#include <JANA/JLogger.h>

#include "EEndCapHit.h"


// This is the example process class. The only thing it 
// does in this example is request the calibrated EEndCapHit
// objects. That causes the chain of requests going all the
// way back to the EASIC_hit raw data objects.
//
// The more interesting stuff is done in the JFactory_EEndCapHit
// class.

EndCapProcessor::EndCapProcessor() {
    SetTypeName(NAME_OF_THIS); // Provide JANA with this class's name
}

void EndCapProcessor::Init() {
    LOG << "EndCapProcessor::Init" << LOG_END;
    // Open TFiles, set up TTree branches, etc
}

void EndCapProcessor::Process(const std::shared_ptr<const JEvent> &event) {
    
    /// Do everything we can in parallel
    /// Warning: We are only allowed to use local variables and `event` here

    // The EEndCapHit objects are created by a factory in this
    // same plugin. Those objects are made using EEndCapDigiHit
    // objects that are made by a factory in the EICRawData plugin.
    auto endcaphits = event->Get<EEndCapHit>();

    /// Lock mutex
    std::lock_guard<std::mutex>lock(m_mutex);

    /// Do the rest sequentially
    /// Now we are free to access shared state such as m_heatmap
    //for (const Hit* hit : hits) {
        /// Update shared state
    //}
}

void EndCapProcessor::Finish() {
    // Close any resources
    LOG << "EndCapProcessor::Finish" << LOG_END;
}

