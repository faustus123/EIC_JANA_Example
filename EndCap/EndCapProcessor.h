
#ifndef _EndCapProcessor_h_
#define _EndCapProcessor_h_

#include <JANA/JEventProcessor.h>

class EndCapProcessor : public JEventProcessor {

    // Shared state (e.g. histograms, TTrees, TFiles) live
    std::mutex m_mutex;
    
public:

    EndCapProcessor();
    virtual ~EndCapProcessor() = default;

    void Init() override;
    void Process(const std::shared_ptr<const JEvent>& event) override;
    void Finish() override;

};


#endif // _EndCapProcessor_h_

