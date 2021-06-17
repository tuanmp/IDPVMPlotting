/// Check the r-tags for our June 2021 MC request 

#include "IDPhysValPlotting/HistoBooking.h"
#include "IDPhysValPlotting/IDPVMHistoPaths.h"

int main(){

    const std::string inPath{"/home/goblirsc/Datasets/Datasets/Tracking/PhysVal/"}; 
    const std::string inFile19 = inPath + "/ReleaseVal/out.r12719.HS.root"; 
    const std::string inFile20 = inPath + "/ReleaseVal/out.r12720.HS.root"; 
    const std::string refFile = inPath + "/ReleaseVal/out.r12627.HS.root"; 
    // const std::string inFile = inPath + "M_output.root"; 

    Int_t colRef = TColor::GetFreeColorIndex();
    TColor *c1 = new TColor(colRef, 0.42,0.7,0.32);
    Int_t colTest1  = TColor::GetFreeColorIndex();
    TColor *c2 = new TColor(colTest1, 0.12,0.47,0.71);
    Int_t colTest2  = TColor::GetFreeColorIndex();
    TColor *c3 = new TColor(colTest2, 0.65,0.22,0.83);


    std::vector<PlotFormat> formats{ 
        PlotFormat().Color(colRef).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("PHYSVAL, r12627 mc16e").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",refFile), 
        PlotFormat().Color(colTest1).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("r12719, custom <#mu>").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",inFile19), 
        PlotFormat().Color(colTest2).MarkerStyle(kFullDiamond).LegendOption("PL").LegendTitle("r12720, custom <#mu>").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName",inFile20)
    }; 

    auto multi = PlotUtils::startMultiPagePdfFile("CheckNewRtags"); 
    auto efficiencies = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(refFile,IDPVMHistoPaths::path_Efficiency()),  formats, {"t#bar{t} events", "Hard-scatter charged particles","Note: Pileup differs between reference and test"}, "EffCheck_",multi); 

    for (auto & p : efficiencies) DefaultPlotting::draw1D(p); 
                                                
    return 0; 
}