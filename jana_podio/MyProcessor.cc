//
// This is a trivial JEventProcessor that just grabs the
// ExampleCluster objects that were read from the PODIO
// file. It does this through the JANA framework and this
// code actually has no idea where the objects came from
// (PODIO or otherwise).
//


#include "MyProcessor.h"
#include <JANA/JLogger.h>

#include "datamodel/ExampleCluster.h"

MyProcessor::MyProcessor() {
    SetTypeName(NAME_OF_THIS); // Provide JANA with this class's name
}

void MyProcessor::Init() {
    LOG << "MyProcessor::Init" << LOG_END;
    // Open TFiles, set up TTree branches, etc
}

void MyProcessor::Process(const std::shared_ptr<const JEvent> &event) {
    
	// Get pointers to the ExampleCluster objects created by PODIO event source
	auto clusters = event->Get<ExampleCluster>();
}

void MyProcessor::Finish() {
    // Close any resources
    LOG << "MyProcessor::Finish" << LOG_END;
}

