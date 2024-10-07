This is a set of helper scripts to easily plot & compare IDPVM outputs

Build on `NtupleAnalysisUtils` for most of the heavy lifting. 

# Getting set up: 

This is a standard ATLAS CMake package, and can be compiled with the usual ATLAS workflow. 

I recommend a recent Athena or Analysis release (only dependency is g++ / ROOT, so it's not very picky). 
The code was tested to work with gcc 8-11. Your mileage may vary on gcc6. 

The project comes with a pre-made project CMakeLists file, in case you need one. See below for a setup example: 
```
mkdir source; cd source/; 
git clone --recursive https://gitlab.cern.ch/Atlas-Inner-Tracking/IDPhysValPlotting.git IDPhysValPlotting
cp IDPhysValPlotting/CMakeLists.forTopLevel.txt ./CMakeLists.txt
cd ..
mkdir build; cd build
asetup Athena,master,latest 
cmake ../source 
make 
source x*/setup.sh
```

# How to use? 

The program intended for "general use" is  [util/StandardPhysValComparison.cxx](https://gitlab.cern.ch/goblirsc/idphysvalplotting/-/blob/master/util/StandardPhysValComparison.cxx)

It will auto-discover most interesting plots in the IDPVM output and plot them all into a (large) multi page PDF as well as individual PDF files. Histo ranges etc are autodetected. 
Ratios are also auto-computed. 

The file to edit on a day-to-day basis is `source/IDPhysValPlotting/example.json`, make a clone anywhere you like. It must contain an `idpvm` key whose value is a list of IDPVM outputs to plot. The first element of the most is the reference, to which the ratio of subsequent elements are evaluated and plotted.
```
    {
        "file": "PATH/TO/FIRST/FILE/M_output_6clusters.root",
        "MakerStyle": 3,
        "LegendTitle": "REFERENCE LEGEND",
        "LineWidth": 2,
        "Color": 46
    }
```
Each element must contain all keys in this example element. The color number currently follows the numbering scheme found in [this link](https://root.cern.ch/doc/master/classTColor.html) for simplicity. Similarly, the marker style follows [this scheme](https://root.cern.ch/doc/master/classTAttMarker.html). The `idpvm` list can contain any number of entries, as long as they follow the same format. The user is free to change the style as desired, without recompiling the code.