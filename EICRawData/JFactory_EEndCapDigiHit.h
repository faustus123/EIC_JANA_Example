
#ifndef _JFactory_EEndCapDigiHit_h_
#define _JFactory_EEndCapDigiHit_h_

#include <JANA/JFactoryT.h>

#include "EEndCapDigiHit.h"

class JFactory_EEndCapDigiHit : public JFactoryT<EEndCapDigiHit> {

    // Insert any member variables here

public:
    JFactory_EEndCapDigiHit();
    void Init() override;
    void ChangeRun(const std::shared_ptr<const JEvent> &event) override;
    void Process(const std::shared_ptr<const JEvent> &event) override;

};

#endif // _JFactory_EEndCapDigiHit_h_
