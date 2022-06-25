

#ifndef _EASIC_hit_h_
#define _EASIC_hit_h_

#include <JANA/JObject.h>

/// JObjects are plain-old data containers for inputs, intermediate results, and outputs.
/// They have member functions for introspection and maintaining associations with other JObjects, but
/// all of the numerical code which goes into their creation should live in a JFactory instead.
/// You are allowed to include STL containers and pointers to non-POD datatypes inside your JObjects,
/// however, it is highly encouraged to keep them flat and include only primitive datatypes if possible.
/// Think of a JObject as being a row in a database table, with event number as an implicit foreign key.
///
/// For this example, the EASIC_hit class is a raw data class from the DAQ system. The expectation
/// is that there may be multiple detectors using the same ASICs and so the DAQ will present all
/// of them in this form. A translation table will need to be applied to determine which detector
/// and which element of that detector the hit corresponds to. That is done later. The EASIC_hit
/// objects are all created by the ERawDataSource object (i.e. they would come from a file or the DAQ
/// stream).



struct EASIC_hit : public JObject {
    uint32_t crate; // <--|
    uint32_t slot;  //    |- DAQ coordinates
    uint32_t chan;  // <--|
    uint32_t t;     // Time in digitized units


    /// Make it convenient to construct one of these things
    EASIC_hit(uint32_t crate, uint32_t slot, uint32_t chan, uint32_t t) : crate(crate), slot(slot), chan(chan), t(t) {};


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
        summary.add(crate, NAME_OF(crate), "%d", "crate");
        summary.add(slot,  NAME_OF(slot),  "%d", "slot" );
        summary.add(chan,  NAME_OF(chan),  "%d", "chan" );
        summary.add(t,     NAME_OF(t),     "%d", "t"    );
    }
};


#endif // _EASIC_hit_h_

