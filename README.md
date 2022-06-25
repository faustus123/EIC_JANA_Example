# Example of JANA2 and Geometry Service 
This is an example written in response for a request to demonstrate how the JANA2 framework would implement DD4hep geometry to select endcap tracker hits greater than a certain radius. 

The example is in the form of 3 plugins that can be used with the simple `jana` exectuable provided with JANA2. The plugins implement an event source, two levels of factories, an event processor, and a Geometry service. Some extensive comments are in the code and you are encouraged to look there for details.

Simple instructions for testing this are:

## Build JANA
~~~ bash
export JANA_VERSION=v2.0.5                    # Convenient to set this once for specific release
export JANA_HOME=${PWD}/JANA${JANA_VERSION}   # Set full path to install dir

git clone https://github.com/JeffersonLab/JANA2 --branch ${JANA_VERSION} ${JANA_HOME}  # Get JANA2

mkdir build                                   # Set build dir
cd build
cmake3 ${JANA_HOME}                           # Generate makefiles (add -DUSE_ZEROMQ=1 if you have ZeroMQ available) 
make -j8 install                              # Build (using 8 threads) and install

source ${JANA_HOME}/bin/jana-this.sh          # Set PATH (and other envars)
~~~

# Build example
~~~ bash
git clone https://github.com/faustus123/EIC_JANA_Example
cd EIC_JANA_Example
mkdir -p */build
for d in */build ; do
  cmake3 ..
  make -j8 install
done

jana -PPLUGINS=EICRawData,EndCap,ExampleDD4HepService,janacontrol dummy
~~~

If you built JANA2 with ZeroMQ support then, in another terminal do this:
~~~ bash
jana-control.py
~~~

Click the `Debugger` button in the lower right to get the object browser.
