
#include "IDPhysValPlotting/HistoBooking.h"
#include "IDPhysValPlotting/IDPVMHistoPaths.h"
#include "TProfile2D.h"

int main(){
    
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
    // std::vector<PlotFormat> formats{ 
    //     PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("old geometry").ExtraDrawOpts("LP").LineWidth(2)
    //     .CustomString("FileName","/scratch/goblirsc/runDirs/Tracking/TrackingGeoCondData/testDefault/M_output.root"),  // here you can set the file to load!
    //     PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("conditions-alg geometry").ExtraDrawOpts("LP").LineWidth(2)
    //     .CustomString("FileName","/scratch/goblirsc/runDirs/Tracking/TrackingGeoCondData/testCond/M_output.root"), // here you can set the file to load!
    // }; 
    std::vector<PlotFormat> formats{ 
        PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("old geometry").ExtraDrawOpts("LP").LineWidth(2)
        .CustomString("FileName","/home/goblirsc/Code/Tracking/DQHoles/f1138/M_output.root"),  // here you can set the file to load!
        PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("conditions-alg geometry").ExtraDrawOpts("LP").LineWidth(2)
        .CustomString("FileName","/home/goblirsc/Code/Tracking/DQHoles/f1121/M_output.root"), // here you can set the file to load!
    }; 

    // const std::string V5= "/home/goblirsc/Code/Tracking/DQHoles/f1138/M_output.root"; 
    // const std::string V4= "/home/goblirsc/Code/Tracking/DQHoles/f1121/M_output.root"; 

    /// Here, you can fine-tune the appearance of the canvas. Can usually also leave alone 
    auto myOpts = CanvasOptions().YAxis(AxisConfig().TopPadding(0.8).BottomPadding(0.15)).RatioAxis(AxisConfig().Title("Ratio w.r.t Ref").Symmetric(true).SymmetrisationPoint(1.)).ColorPalette(kBlackBody); 

    /// Here you can choose the file name for the output multi page PDF file. 
    /// This example will generate a "CheckTrkGeoAlg.pdf" in the default location ("$TestArea/../Plots/<date>/") 
    auto multi = PlotUtils::startMultiPagePdfFile("CheckTrkGeoAlg"); 

    /// This is the set of labels to draw on the plot.
    /// Use this to show what you are testing, which process this is, the pileup, etc 
    std::vector<std::string> labels {"t#bar{t} events", "Hard-scatter charged particles"};

    /// Now, we book for drawing everything we find inside the file. 
    std::string fileToCheck;
    formats.front().CustomString.get("FileName", fileToCheck); 

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


    /// find the resolutions that are actually interesting - veto pull projections
    auto listOfResos = IDPVMHistoPaths::scanPath<TH1F>(fileToCheck,IDPVMHistoPaths::path_resolutions()); 
    std::vector<std::string> funResos{}; 
    for (auto & reso : listOfResos){
        if (reso.find("resProjection") != std::string::npos) continue; 
        if (reso.find("pullProjection") != std::string::npos) continue;
        funResos.push_back(reso);  
    }
    auto resos = HistoBooking::bookThem<TH1F>(funResos,  formats, labels, "ResoCheck_",multi,myOpts); 

    for (auto & p : efficiencies) DefaultPlotting::draw1D(p); 
    for (auto & p : hitsHoles_Selected) DefaultPlotting::draw1D(p); 
    for (auto & p : hitsHoles_Matched) DefaultPlotting::draw1D(p); 
    for (auto & p : resos) DefaultPlotting::draw1D(p); 
    for (auto & p : params) DefaultPlotting::draw1D(p); 
    for (auto & p : hitsHoles_Selected2D) DefaultPlotting::draw2DPlots(p); 
                                                
    return 0; 
}