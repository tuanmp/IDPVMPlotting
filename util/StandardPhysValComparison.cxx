
#include "IDPhysValPlotting/HistoBooking.h"
#include "IDPhysValPlotting/IDPVMHistoPaths.h"
#include "IDPhysValPlotting/IDPVMPlotting.h"
#include "TProfile2D.h"

int main(){

    ///////////////////////////////////////////////////////////
    /// In this first block, we configure what to compare and 
    /// how to format and label our plots. 
    /// 
    /// TODO: If people prefer, I'm happy to provide a json 
    /// or other interface for this. Let me know.
    ////////////////////////////////////////////////////////// 


    /// A 3-color scheme that we used for the CPU PUB note. 
    /// Feel free to use this (or any other colours you like!) 
    Int_t colRef = TColor::GetFreeColorIndex();
    TColor *c1 = new TColor(colRef, 0.42,0.7,0.32);
    Int_t colTest1  = TColor::GetFreeColorIndex();
    TColor *c2 = new TColor(colTest1, 0.12,0.47,0.71);
    Int_t colTest2  = TColor::GetFreeColorIndex();
    TColor *c3 = new TColor(colTest2, 0.65,0.22,0.83);

    /// This steers which entries to plot on the canvases. 
    /// One entry per sample.
    /// The file to read from is provided as the "FileName" argument 

    /// In this example, we configure two entries (this was used to validate the tracking geometry updates). 
    /// Can just as easily do 3,4,... just make sure to give them clear titles, and distinguishable colours.

    /// The first entry is used as reference for all the ratios that will be drawn. 
    /// For the meaning of the various arguments: See NTAU tutorial @ https://gitlab.cern.ch/Atlas-Inner-Tracking/NtupleAnalysisUtils_tutorial 
    /// In particular, check out the SWAN notebooks! 
    std::vector<PlotFormat> formats{ 
        PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("Nominal detector").ExtraDrawOpts("LP").LineWidth(2)
        .CustomString("FileName","/eos/user/g/goblirsc/Tracking/PhysValPlottingExampleFiles/SglMu_master_nominal.IDPVM.root"),  // here you can set the file to load!
        
        PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("No B-layer").ExtraDrawOpts("LP").LineWidth(2)
        .CustomString("FileName","/eos/user/g/goblirsc/Tracking/PhysValPlottingExampleFiles/SglMu_master_nominal.IDPVM.root"), // here you can set the file to load!
	  //PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("No B-layer").ExtraDrawOpts("LP").LineWidth(2)
	  //.CustomString("FileName","/eos/user/g/goblirsc/Tracking/PhysValPlottingExampleFiles/SglMu_master_noBL.IDPVM.root"), // here you can set the file to load!
    }; 
    
    /// Here, you can tune the appearance of the canvas. 
    /// For example, this allows you to override axis ranges (or change how they are detected), manually enforce axis labels, 
    /// steer the appearance of legends or palettes, the ATLAS label, etc. 
    auto myOpts = CanvasOptions().YAxis(AxisConfig().TopPadding(0.8).BottomPadding(0.15)).RatioAxis(AxisConfig().Title("Ratio w.r.t Ref").Symmetric(true).SymmetrisationPoint(1.)).ColorPalette(kBlackBody); 

    /// Here you can choose the file name for the output multi page PDF file. 
    /// This example will generate a "CheckBLayerGone.pdf" in the default location ("$TestArea/../Plots/<date>/") 
    auto multi = PlotUtils::startMultiPagePdfFile("CheckBLayerGone"); 

    /// This is the set of labels to draw on the plot.
    /// Use this to show what you are testing, which process this is, the pileup, etc.
    /// They will be drawn on your canvas one atop the other.
    /// No need to include the ATLAS label, this is handled automatically, as is the lumi/sqrt{s}. 
    /// Both can be changed in the CanvasOptions if desired. 
    std::vector<std::string> labels {"Single #mu"};

    ///////////////////////////////////////////////////////////
    /// Now, we decide which items to actually draw comparisons for. 
    /// By default, we are a bit selective to limit file sizes. 
    /// We could also tell bookThem to start from the "" directory 
    /// of the input file, in which case it would pick up 
    /// *everything* of the right type.
    /// Note that booking does *not* yet cause any overhead.
    /// Histograms are only loaded when actually needed, 
    /// so it is sufficient to comment the drawing command
    /// farther below to suppress certain plots. 
    ////////////////////////////////////////////////////////// 

    /// Perform a look-up of the available histograms based on the first file in our comparison. 
    std::string fileToCheck;
    formats.front().CustomString.get("FileName", fileToCheck); 

    /// Pick up the sets of items to plot.
    /// bookEffs and bookThem will produce vectors of 'PlotContent'
    /// objects, which each encapsulate a plot to be drawn. 
    /// This just defines a workload, nothing is actually run yet. 

    /// Efficiencies
    auto efficiencies = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck,IDPVMHistoPaths::path_Efficiency()),  formats, labels, "EffCheck_",multi,myOpts); 

    /// Hits and holes - selected
    auto hitsHoles_Selected = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck,IDPVMHistoPaths::path_hitsOnTrack_Selected()),  formats, labels, "HitHoleCheck_Selected_",multi,myOpts);

    /// Hits and holes - matched
    auto hitsHoles_Matched = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck,IDPVMHistoPaths::path_hitsOnTrack_Matched()),  formats, labels, "HitHoleCheck_Matched_",multi,myOpts);

    /// Hits and holes - 2D
    auto hitsHoles_Selected2D = HistoBooking::bookThem<TProfile2D>(IDPVMHistoPaths::scanPath<TProfile2D>(fileToCheck,IDPVMHistoPaths::path_hitsOnTrack_Selected()),  formats, labels, "HitHoleCheck_Selected2D_",multi,myOpts);
    
    /// 1D track parameters
    auto params = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(fileToCheck,IDPVMHistoPaths::path_params()),  formats, labels, "ParamCheck_",multi,myOpts); 


    /// find the resolutions that are actually interesting - veto pull projections to limit file size
    auto listOfResos = IDPVMHistoPaths::scanPath<TH1F>(fileToCheck,IDPVMHistoPaths::path_resolutions()); 
    std::vector<std::string> interestingResos; 
    std::copy_if(listOfResos.begin(), listOfResos.end(), std::back_inserter(interestingResos), 
        [](const std::string & histName){
            if (histName.find("resProjection") != std::string::npos) return false; 
            if (histName.find("pullProjection") != std::string::npos) return false;
            return true; 
        }
    ); 
    // now book the reso items we kept 
    auto resos = HistoBooking::bookThem<TH1F>(interestingResos,  formats, labels, "ResoCheck_",multi,myOpts); 


    ///////////////////////////////////////////////////////////
    /// Finally, we draw everything. Note that draw1D and 
    /// draw2DPlots can each take an arbitrarily long set of inputs,
    /// feel free to plug in any extra stuff you like! 
    /// This will lead to the histos being loaded and drawn 
    /// together with the relevant ratios etc. 
    ///
    /// Also note that for certain specialised plots,
    /// it can be useful to write a short custom drawing 
    /// script instead of resorting to the pre-made draw1D. 
    ////////////////////////////////////////////////////////// 

    // Writing this in a form where it is easy to comment undesired entries. 
    IDPVMPlotting::draw1D(
			  efficiencies, 
			  resos,
			  params,
			  hitsHoles_Selected,
			  hitsHoles_Matched
			  ); 
    IDPVMPlotting::draw2DPlots(
			       hitsHoles_Selected2D
			       );
    return 0; 
}
