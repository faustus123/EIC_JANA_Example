

#ifndef _ERawDataSource_h_
#define  _ERawDataSource_h_

#include <JANA/JEventSource.h>
#include <JANA/JEventSourceGeneratorT.h>

#include <random>


class ERawDataSource : public JEventSource {

    /// Add member variables here

public:
    ERawDataSource(std::string resource_name, JApplication* app);

    virtual ~ERawDataSource() = default;

    void Open() override;

    void GetEvent(std::shared_ptr<JEvent>) override;
    
    static std::string GetDescription();

private:
    std::default_random_engine generator;

};

template <>
double JEventSourceGeneratorT<ERawDataSource>::CheckOpenable(std::string);

#endif // _ERawDataSource_h_

