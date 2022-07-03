
#ifndef _MyProcessor_h_
#define _MyProcessor_h_

#include <JANA/JEventProcessor.h>

class MyProcessor : public JEventProcessor {

    // Shared state (e.g. histograms, TTrees, TFiles) live
    std::mutex m_mutex;
    
public:

    MyProcessor();
    virtual ~MyProcessor() = default;

    void Init() override;
    void Process(const std::shared_ptr<const JEvent>& event) override;
    void Finish() override;

};


#endif // _MyProcessor_h_

