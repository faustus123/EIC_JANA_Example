
#include <JANA/JEventSource.h>
#include <JANA/Services/JGlobalRootLock.h>

#include "JEventSourcePODIO.h"
#include "MyProcessor.h"
    
extern "C" {
    void InitPlugin(JApplication *app) {
        InitJANAPlugin(app);
        app->Add(new JEventSourceGeneratorT<JEventSourcePODIO>());
        app->Add(new MyProcessor());
    }
}
    
