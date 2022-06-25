
#ifndef _JFactory_EEndCapHit_h_
#define _JFactory_EEndCapHit_h_

#include <JANA/JFactoryT.h>
#include <ExampleDD4HepService/ExampleDD4HepService.h>
#include "EEndCapHit.h"

class JFactory_EEndCapHit : public JFactoryT<EEndCapHit> {

    // Insert any member variables here

public:
    JFactory_EEndCapHit();
    void Init() override;
    void ChangeRun(const std::shared_ptr<const JEvent> &event) override;
    void Process(const std::shared_ptr<const JEvent> &event) override;

protected:
    double min_radius;

    const ExampleDD4HepService *geomservice=nullptr;

};

#endif // _JFactory_EEndCapHit_h_
