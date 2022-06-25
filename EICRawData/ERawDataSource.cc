

#include "ERawDataSource.h"
#include "EASIC_hit.h"

#include <JANA/JApplication.h>
#include <JANA/JEvent.h>

/// This is the event source. This would be where one would open a file
/// and read its contents, creating objects from them for use by the
/// factories and processors. JANA supports having multiple data source
/// classes in the program so a single executable can read from multiple
/// file types and/or newtowrk streams.
///
/// For this example, it is fakes the events by generating just one type
/// of object: EASIC_hit. It does this using random numbers.
///
/// There are two different ways of instantiating JEventSources
/// 1. Creating them manually and registering them with the JApplication
/// 2. Creating a corresponding JEventSourceGenerator and registering that instead
///    If you have a list of files as command line args, JANA will use the JEventSourceGenerator
///    to find the most appropriate JEventSource corresponding to that filename, instantiate and register it.
///    For this to work, the JEventSource constructor has to have the following constructor arguments:

ERawDataSource::ERawDataSource(std::string resource_name, JApplication* app) : JEventSource(resource_name, app) {
    SetTypeName(NAME_OF_THIS); // Provide JANA with class name
}

void ERawDataSource::Open() {

    /// Open is called exactly once when processing begins.
    /// If multiple files are given on the command line, then each will have
    /// its own ERawDataSource object instantiated.
    
    /// For opening a file, get the filename via:
    // std::string resource_name = GetResourceName();
    /// Open the file here!
}

void ERawDataSource::GetEvent(std::shared_ptr <JEvent> event) {

    /// Calls to GetEvent are synchronized with each other, which means they can
    /// read and write state on the JEventSource without causing race conditions.
    
    /// Configure event and run numbers
    static size_t current_event_number = 1;
    event->SetEventNumber(current_event_number++);
    event->SetRunNumber(22);

    /// Insert whatever data was read into the event
    /// Here, randomly sample a number of hits and
    /// then randomly sample the DAQ coordinates of the hits
    std::vector<EASIC_hit*> hits;

    std::normal_distribution<double>        Nhits_distribution(200.0,5.0);
    std::uniform_int_distribution<uint32_t> crate_distribution(14,19);
    std::uniform_int_distribution<uint32_t> slot_distribution(0,14);
    std::uniform_int_distribution<uint32_t> chan_distribution(0,127);
    std::normal_distribution<double>        t_distribution(125,10.0);

    auto Nhits = Nhits_distribution( generator );
    while( hits.size() < Nhits ){
        auto crate = crate_distribution( generator );
        auto slot  = slot_distribution(  generator );
        auto chan  = chan_distribution(  generator );
        auto t     = t_distribution(     generator );
        hits.push_back(new EASIC_hit(crate, slot, chan, t));
   }
    event->Insert(hits);

    /// If you are reading a file of events and have reached the end, terminate the stream like this:
    // // Close file pointer!
    // throw RETURN_STATUS::kNO_MORE_EVENTS;

    /// If you are streaming events and there are no new events in the message queue,
    /// tell JANA that GetEvent() was temporarily unsuccessful like this:
    // throw RETURN_STATUS::kBUSY;
}

std::string ERawDataSource::GetDescription() {

    /// GetDescription() helps JANA explain to the user what is going on
    return "Fake source of endcap track events";
}


template <>
double JEventSourceGeneratorT<ERawDataSource>::CheckOpenable(std::string resource_name) {

    /// CheckOpenable() decides how confident we are that this EventSource can handle this resource.
    ///    0.0        -> 'Cannot handle'
    ///    (0.0, 1.0] -> 'Can handle, with this confidence level'
    
    /// To determine confidence level, feel free to open up the file and check for magic bytes or metadata.
    /// Returning a confidence <- {0.0, 1.0} is perfectly OK!
    
    return 1.0; // We claim to handle all sources just for the purposes of this example.
}
