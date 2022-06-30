
// This is just a sketch of how one would implement something
// like a geometry service in JANA. This does not actually
// contain any DD4hep code.
//
// A service in JANA is basically a single object held by the
// JApplication whose reference can be requested by any other JANA
// element (e.g. JFactory or JEventProcessor objects). The JService
// base class accomodates for some more complicated scenarios
// that arise when one service relies on using other services.



#include <JANA/JEvent.h>
#include <JANA/Services/JServiceLocator.h>
#include <TVector3.h>
#include <TFile.h>

// Define this here for demonstration purposes.
// It would normally come from a DD4hep header.
namespace dd4hep{
class Assembly;
};


class ExampleDD4HepService: public JService {

public:
    // Constructor 
    ExampleDD4HepService()=default;
       
    // The geometry service needs to be sensitive to the exact data being processed since subtle
	// alignment changes or even significant changes to the detector could appear between one
	// data set and the next. The most versatile system would allow data from multiple different
	// geometry definitions to exist at the same time.
    //
    // For this to return the correct geometry, it needs information from the data stream itself
	// on when it was acquired so it can access the correct DB. I do not try and add that
	// complication here right now. I do demonstrate though that the JEvent reference would be
	// passed in so that the needed info can be extracted. Note that this should not be called for
    // every event, but rather from the ChangeRun method of a factory or processor indicating a
	// new calibration region of the stream has been reached.
    const dd4hep::Assembly* GetDD4hepAssembly(const std::shared_ptr<const JEvent> &event) const {

        // Retrieve the correct Assembly based on when the given
        // JEvent was acquired.
        
        return _assembly;
    }

    // There is a lot of freedom in how this class could be organized. One is to simply provide a
	// reference to the DD4hep Assembly object as above and let all of the algorithms speak "DD4hep".
    // A more practical approach would be to augment that with some dedicated methods that answer
	// common questions about the geometry for specific detectors. Here is an example of this:
    TVector3 GetVTXPixelLocation( int layer, int chip, int pixel ) const {
        
        // This is where the code to extract the location information given the layer,chip, and pixel
		// values would reside. This could either be directly from the dd4hep reference or from some
		// cached value.
        assert( layer>=1 && layer<=9 );
        
        double x = (double)chip*2.7;  // Totally unrealistic. Just for demo 
        double y = (double)pixel*1.2; // Totally unrealistic. Just for demo
        double z = z_layer[layer-1];  // Lookup table (this should actually be close to correct!)
        
        return TVector3( x, y, z);
    }

private:
    dd4hep::Assembly *_assembly = nullptr;
    double z_layer[9] = {-106.0, -79.0, -52.0, -25.0, 25.0, 49.0, 73.0, 106.0, 125.0};

};
