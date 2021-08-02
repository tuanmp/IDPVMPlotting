This is a set of helper scripts to easily plot & compare IDPVM outputs

Build on `NtupleAnalysisUtils` for most of the heavy lifting. 

# Getting set up: 

This is a standard ATLAS CMake package, and can be compiled with the usual workflow. 

I recommend a recent Athena or AthAnalysis release (only dependency is g++ / ROOT, so it's not very picky). 

The project comes with a pre-made project CMakeLists file, in case you need one. See below for a setup example: 
```
mkdir source; cd source/; 
git clone --recursive https://:@gitlab.cern.ch:8443/goblirsc/idphysvalplotting.git IDPhysValPlotting
cp IDPhysValPlotting/CMakeLists.forTopLevel.txt ./CMakeLists.txt
cd ..
mkdir build; cd build
asetup Athena,master,latest 
cmake ../source 
make 
source x*.setup.sh
```

# How to use? 

The program intended for "general use" is  [util/StandardPhysValComparison.cxx][https://gitlab.cern.ch/goblirsc/idphysvalplotting/-/blob/master/util/StandardPhysValComparison.cxx]

It will auto-discover most interesting plots in the IDPVM output and plot them all into a (large) multi page PDF as well as individual PDF files. Histo ranges etc are autodetected. 
Ratios are also auto-computed. 

The block to edit in day-to-day work is lines 32-36, where we set the files to compare. This can be an arbitrary number, and each can be given its own labels / formatting. The provided example compares two setups. 

When making changes, the shortcut `cmake --build $TestArea && StandardPhysValComparison` can be useful to rebuild and update the results 

