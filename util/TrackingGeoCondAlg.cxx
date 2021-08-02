/// Check the r-tags for our June 2021 MC request 

#include "IDPhysValPlotting/HistoBooking.h"
#include "IDPhysValPlotting/IDPVMHistoPaths.h"

int main(){
    

    const std::string ref = "/scratch/goblirsc/runDirs/Tracking/TrackingGeoCondData/testDefault/M_output.root"; 
    const std::string test= "/scratch/goblirsc/runDirs/Tracking/TrackingGeoCondData/testCond/M_output.root"; 
    // const std::string inFile = inPath + "M_output.root"; 

    const std::string dataRef = "/home/goblirsc/Code/Tracking/TrackingGeoCondData/run/qtest/ref/M_output.root"; 
    const std::string dataTest = "/home/goblirsc/Code/Tracking/TrackingGeoCondData/run/qtest/test/M_output.root"; 

    Int_t colRef = TColor::GetFreeColorIndex();
    TColor *c1 = new TColor(colRef, 0.42,0.7,0.32);
    Int_t colTest1  = TColor::GetFreeColorIndex();
    TColor *c2 = new TColor(colTest1, 0.12,0.47,0.71);
    Int_t colTest2  = TColor::GetFreeColorIndex();
    TColor *c3 = new TColor(colTest2, 0.65,0.22,0.83);


    std::vector<PlotFormat> formats{ 
        PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("old geometry").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",ref), 
        PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("conditions-alg geometry").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",test), 
    }; 

    std::vector<PlotFormat> formatData{ 
        PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("old geometry").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",dataRef), 
        PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("conditions-alg geometry").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",dataTest), 
    }; 

    auto myOpts = CanvasOptions().YAxis(AxisConfig().TopPadding(0.8).BottomPadding(0.15)).RatioAxis(AxisConfig().Title("Ratio w.r.t Ref").Symmetric(true).SymmetrisationPoint(1.)); 

    auto multi = PlotUtils::startMultiPagePdfFile("CheckTrkGeoAlg"); 
    auto multiData = PlotUtils::startMultiPagePdfFile("CheckTrkGeoAlg_q431"); 

    auto efficiencies = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(ref,IDPVMHistoPaths::path_Efficiency()),  formats, {"t#bar{t} events", "Hard-scatter charged particles"}, "EffCheck_",multi,myOpts); 

    auto hitsHoles = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(ref,IDPVMHistoPaths::path_hitsOnTrack_Matched()),  formats, {"t#bar{t} events", "Hard-scatter charged particles"}, "HitHoleCheck_",multi,myOpts);
    
    auto hitsHolesData = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(dataRef,IDPVMHistoPaths::path_hitsOnTrack_Selected()),  formats, {"q431 data"}, "HitHoleCheck_q431_",multiData,myOpts); 

    auto params = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(ref,IDPVMHistoPaths::path_params()),  formats, {"t#bar{t} events", "Hard-scatter charged particles"}, "ParamCheck_",multi,myOpts); 

    auto paramsData = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(dataRef,IDPVMHistoPaths::path_params()),  formats, {"q431 data"}, "ParamCheck_q431_",multiData,myOpts); 

    // find the resolutions that are actually interesting - veto pull projections
    auto listOfResos = IDPVMHistoPaths::scanPath<TH1F>(ref,IDPVMHistoPaths::path_resolutions()); 
    std::vector<std::string> funResos{}; 
    for (auto & reso : listOfResos){
        if (reso.find("resProjection") != std::string::npos) continue; 
        if (reso.find("pullProjection") != std::string::npos) continue;
        funResos.push_back(reso);  
    }
    auto resos = HistoBooking::bookThem<TH1F>(funResos,  formats, {"t#bar{t} events", "Hard-scatter charged particles","Note: Pileup differs between reference and test"}, "ResoCheck_",multi,myOpts); 

    for (auto & p : efficiencies) DefaultPlotting::draw1D(p); 
    for (auto & p : hitsHoles) DefaultPlotting::draw1D(p); 
    for (auto & p : resos) DefaultPlotting::draw1D(p); 
    for (auto & p : params) DefaultPlotting::draw1D(p); 
    for (auto & p : paramsData) DefaultPlotting::draw1D(p); 
    for (auto & p : hitsHolesData) DefaultPlotting::draw1D(p); 
                                                
    return 0; 
}