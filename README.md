This is a set of helper scripts to easily plot & compare IDPVM outputs

Build on `NtupleAnalysisUtils` for most of the heavy lifting. 

# Getting set up: 

This is a standard ATLAS CMake package, and can be compiled with the usual ATLAS workflow. 

I recommend a recent Athena or Analysis release (only dependency is g++ / ROOT, so it's not very picky). 
The code was tested to work with gcc 8-11. Your mileage may vary on gcc6. 

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

The program intended for "general use" is  [util/StandardPhysValComparison.cxx](https://gitlab.cern.ch/goblirsc/idphysvalplotting/-/blob/master/util/StandardPhysValComparison.cxx)

It will auto-discover most interesting plots in the IDPVM output and plot them all into a (large) multi page PDF as well as individual PDF files. Histo ranges etc are autodetected. 
Ratios are also auto-computed. 

The block to edit in day-to-day work is lines 36-42, where we set the files to compare: 
```
    std::vector<PlotFormat> formats{ 
        PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("old geometry").ExtraDrawOpts("LP").LineWidth(2)
        .CustomString("FileName","/home/goblirsc/Code/Tracking/DQHoles/f1138/M_output.root"),  // here you can set the file to load!
        
        PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("conditions-alg geometry").ExtraDrawOpts("LP").LineWidth(2)
        .CustomString("FileName","/home/goblirsc/Code/Tracking/DQHoles/f1121/M_output.root"), // here you can set the file to load!
    }; 
```
The vector can contain an arbitrary number of entries, so you are not limited to comparing just two setups at a time. 
The first element is considered the "reference", and ratios are automatically prepared comparing each other setup to the reference. 

When making changes, the shorthand `cmake --build $TestArea && StandardPhysValComparison` can be useful to rebuild and update the results 

Farther below, you can configure plot labels, canvas appearance & labeling, file names, etc. You can also select which items to include 
in the set of drawn comparisons. 

# Learning more 

To learn more about how you can change the appearance of the plots, etc, please refer to the `NtupleAnalysisUtils` documentation.
There is an [interactive tutorial](https://gitlab.cern.ch/goblirsc/NtupleAnalysisUtils_tutorial) - im particular try the notebook on SWAN! 
