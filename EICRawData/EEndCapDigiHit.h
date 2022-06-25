

#ifndef _EEndCapDigiHit_h_
#define _EEndCapDigiHit_h_

#include <JANA/JObject.h>

// The EEndCapDigiHit class is used as an intermediate form of the data.
// See comments at top of JFactory_EEndCapDigiHit for details.

struct EEndCapDigiHit : public JObject {
    int layer;   // endcap layer (1-4=electron endcap 5-9=hadron endcap)
    int chip;    // chip number on plate
    int pixel;   // id of pixel hit
    uint32_t t;  // time in digitized units


    /// Make it convenient to construct one of these things
    EEndCapDigiHit(int layer, int chip, int pixel, uint32_t t) : layer(layer), chip(chip), pixel(pixel), t(t) {};


    /// Override className to tell JANA to store the exact name of this class where we can
    /// access it at runtime. JANA provides a NAME_OF_THIS macro so that this will return the correct value
    /// even if you rename the class using automatic refactoring tools.

    const std::string className() const override {
        return NAME_OF_THIS;
    }

    /// Override Summarize to tell JANA how to produce a convenient string representation for our JObject.
    /// This can be used called from user code, but also lets JANA automatically inspect its own data. For instance,
    /// adding JCsvWriter<Hit> will automatically generate a CSV file containing each hit. Warning: This is obviously
    /// slow, so use this for debugging and monitoring but not inside the performance critical code paths.

    void Summarize(JObjectSummary& summary) const override {
        summary.add(layer, NAME_OF(layer), "%d", "endcap layer");
        summary.add(chip,  NAME_OF(chip),  "%d", "chip number on plate");
        summary.add(pixel, NAME_OF(pixel), "%d", "id of pixel hit");
        summary.add(t,     NAME_OF(t),     "%d", "time in digitized units");
    }
};


#endif // _EEndCapDigiHit_h_

