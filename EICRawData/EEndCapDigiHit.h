

#ifndef _EEndCapDigiHit_h_
#define _EEndCapDigiHit_h_

#include <TObject.h>

// The EEndCapDigiHit class is used as an intermediate form of the data.
// See comments at top of JFactory_EEndCapDigiHit for details.

// n.b. In this version EEndCapDigiHit inherits from ROOT's TObject.
// This could also inherit from JObject, both, or neither.

struct EEndCapDigiHit : public TObject {
    int layer;   // endcap layer (1-4=electron endcap 5-9=hadron endcap)
    int chip;    // chip number on plate
    int pixel;   // id of pixel hit
    uint32_t t;  // time in digitized units


    /// Make it convenient to construct one of these things
    EEndCapDigiHit(int layer, int chip, int pixel, uint32_t t) : layer(layer), chip(chip), pixel(pixel), t(t) {};

ClassDef( EEndCapDigiHit, 1)
};


#endif // _EEndCapDigiHit_h_

