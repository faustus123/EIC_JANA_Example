# Example of JANA2 PODIO Event Source 
This is an example of implementing an event source in JANA that uses PODIO to read events from a ROOT file created by the PODIO tests/write program.

There are two other examples placed into separate branches on this repository:<br>
[Example of tracker radial cut](https://github.com/faustus123/EIC_JANA_Example)<br>
[Example of tracker radial cut with TObject](https://github.com/faustus123/EIC_JANA_Example/tree/TObject_example)

This example is in the form of a single plugin, _jana_podio_, that implements the event source and a minimal event processor that requests one of the 3 types of objects the event source provides.

![Conceptual diagram](docs/diagram.png?raw=true "Conceptual Diagram of Example")

Instructions for testing this are below. These include instructions for building ROOT using the C++17 standard since PODIO requires this.


## Work directory and Python environment
PODIO requires the _pyyaml_ and _jinja2_ packages be installed. These were not installed by default on my system so I installed them in a virtual Python environment. Do this first to ensure ROOT uses the same Python environment that PODIO uses.

~~~ bash
export WORKDIR=${PWD}        # make it easy to get back to this directory

python3 -m venv venv
source venv/bin/activate
pip install pyyaml jinja2
~~~

## Build ROOT
PODIO requires ROOT built with C++17 standard.
~~~ bash
mkdir ${WORKDIR}/root
cd ${WORKDIR}/root
wget https://root.cern/download/root_v6.26.04.source.tar.gz
tar xzf root_v6.26.04.source.tar.gz
mv root-6.26.04 root-6.26.04.src
mkdir root-6.26.04.build root-6.26.04
cd root-6.26.04.build
cmake -DCMAKE_CXX_STANDARD=17 -DCMAKE_INSTALL_PREFIX=../root-6.26.04 -Dbuiltin_glew=ON ../root-6.26.04.src
make -j8 install
source ../root-6.26.04/bin/thisroot.sh
~~~

## Build JANA
~~~ bash
export JANA_VERSION=v2.0.5                    # Convenient to set this once for specific release
export JANA_HOME=${PWD}/JANA${JANA_VERSION}   # Set full path to install dir

git clone https://github.com/JeffersonLab/JANA2 --branch ${JANA_VERSION} ${JANA_HOME}  # Get JANA2

mkdir build                                   # Set build dir
cd build
cmake -DCMAKE_CXX_STANDARD=17 -DUSE_ROOT=1 ${JANA_HOME} # Generate makefiles (add -DUSE_ZEROMQ=1 if you have ZeroMQ available) 
make -j8 install                              # Build (using 8 threads) and install

source ${JANA_HOME}/bin/jana-this.sh          # Set PATH (and other envars)
~~~

## Build PODIO
~~~ bash
cd ${WORKDIR}
git clone https://github.com/AIDASoft/podio -b v00-14-03 PODIO_v00-14-03
mkdir PODIO_v00-14-03/build PODIO_v00-14-03/install
cd PODIO_v00-14-03
source init.sh
cd build
cmake -DCMAKE_INSTALL_PREFIX=../install -DUSE_EXTERNAL_CATCH2=OFF ../
make -j8 install

tests/write            # Create example.root file using PODIO
~~~

## Build example
~~~ bash
cd ${WORKDIR}
git clone https://github.com/faustus123/EIC_JANA_Example --branch PODIO_example
mkdir -p EIC_JANA_Example/jana_podio/build
cd EIC_JANA_Example/jana_podio/build
cmake ..
make -j8 install
~~~

## Run example
~~~ bash
jana -PPLUGINS=jana_podio ${WORKDIR}/PODIO_v00-14-03/build/example.root
~~~
This should run pretty fast as there are only 2000 events and nothing is really being done with them.

If you built JANA2 with ZeroMQ support then, you can run it with the `janacontrol` plugin and
then open the jana-control.py browser in another terminal. Here, you'll want to set the config.
parameter _PODIO:run_forever_ to "1" so that it continuously recycles events. Otherwise, it
will end before you can get the _jana-control.py_ window open.
~~~ bash
# In terminal 1:
jana -PPLUGINS=jana_podio,janacontrol -PPODIO:run_forever=1 ${WORKDIR}/PODIO_v00-14-03/build/example.root

# In terminal 2:
jana-control.py
~~~

Click the `Debugger` button in the lower right to get the object browser (_Debugger_).

![jana-control.py GUI](docs/jana-control.png?raw=true "jana-control.py GUI")
![jana-control.py GUI Debugger](docs/jana-control_debugger.png?raw=true "jana-control.py GUI")
