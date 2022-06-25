

#ifndef _EEndCapHit_h_
#define _EEndCapHit_h_

#include <JANA/JObject.h>

/// This class represents a calibrated endcap tracker hit.
/// See JFactory_EEndCapHit.cc for details


struct EEndCapHit : public JObject {
    double x;  // X Pixel coordinate in cm
    double y;  // Y Pixel coordinate in cm
    double z;  // Z Pixel coordinate in cm
    double t;  // Time in ns relative to beam crossing

    /// Make it convenient to construct one of these things
    EEndCapHit(){};
    EEndCapHit(double x, double y, double z, double t) : x(x), y(y), z(z), t(t) {};

    /// Override className to tell JANA to store the exact name of this class where we can
    /// access it at runtime. JANA provides a NAME_OF_THIS macro so that this will return the correct value
    /// even if you rename the class using automatic refactoring tools.
    const std::string className() const override {
        return NAME_OF_THIS;
    }

    /// Override Summarize to tell JANA how to produce a convenient string representation for our JObject.
    /// This can be called from user code, but also lets JANA automatically inspect its own data. For instance,
    /// adding JCsvWriter<Hit> will automatically generate a CSV file containing each hit. Warning: This is obviously
    /// slow, so use this for debugging and monitoring but not inside the performance critical code paths.
    void Summarize(JObjectSummary& summary) const override {
        summary.add(x, NAME_OF(x), "%f", "X(cm)");
        summary.add(y, NAME_OF(y), "%f", "Y(cm)");
        summary.add(z, NAME_OF(z), "%f", "Z(cm)");
        summary.add(t, NAME_OF(t), "%f", "Time(ns)");
    }
};


#endif // _EEndCapHit_h_

