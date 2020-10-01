#include "NtupleAnalysisUtils/DefaultPlotting.h"
#include "NtupleAnalysisUtils/AtlasStyle.h"
#include "NtupleAnalysisUtils/CanvasOptions.h"

// helper to quickly book plots 


// define one entry in the final plot
// this allows us to be decoupled of the histogram type 
struct genericPlotDef{
    std::string fileName;   // where to read from
    std::string legendTitle;    // how to label
    std::string legendStyle;    // how to render in legend
    PlotFormat format;  // desired format 
};

// See for example NtupleAnalysisUtils/PlotPostProcessor.h for inspiration :-) 
template <class Htype> Plot<Htype> generatePlot (const std::string & plot, const genericPlotDef & genericDef){

    return Plot<Htype>{
        genericDef.fileName, 
        plot, 
        genericDef.legendTitle, 
        genericDef.legendStyle,
        genericDef.format
    };
}

// this methid composes a "PlotContent" (= one canvas) for each element of the vector "plots". 
// "plots" should be a list of plot locations within the files. 
// "defs" describes the entries to put in each canvas (input files and related formatting) 
// "labels" is a set of labels that should be put on the canvas
// "fname_base" is a common prefix for all output files, this can include a directory structure 
// "finame_multiPagePDF" is the name of a multi-page PDF where all plots will additionally be inserted to. Again may include directory structure 
// CanvasOpts is a CanvasOptions objecty (see NtupleAnalysisUtils/CanvasOptions.h) which steers how the canvas will look. 
template <class Htype> std::vector<PlotContent<Htype>> bookThem(std::vector<std::string> plots, std::vector<genericPlotDef> defs, const std::vector<std::string> & labels, const std::string & fname_base, const std::string & fname_multiPagePDF, CanvasOptions CanvasOpts){

    // book the output vector 
    std::vector<PlotContent<Htype>> output; 
    output.reserve(plots.size()); 

    // now add an entry for each plot we are interested in 
    for (auto & plot : plots){
        std::vector<Plot<Htype>> entries;
        // here we book each of the canvas entries, one for each sample  
        for (auto & entry : defs){ 
            entries.push_back(generatePlot<Htype>(plot,entry)); 
        }
        // add the plot name to the list of labels on the pad 
        // use a deep copy to avoid adding the label to *all* plots :-)
        std::vector<std::string> myLabels { labels}; 
        myLabels.push_back(plot); 

        // generate a file name for the plot 
        TString forFname = plot;
        forFname = forFname.ReplaceAll("/","_"); 
        forFname = forFname.ReplaceAll(" ","_"); 
        forFname = forFname.ReplaceAll(":","_"); 
        forFname = TString(fname_base) + forFname; 

        // now put everything together
        output.push_back(PlotContent<Htype>{
            entries, 
            myLabels, 
            std::string(forFname), 
            fname_multiPagePDF, 
            CanvasOpts
        }); 
    }
    return output;
}


int main (int argc, char** argv){

    // input files to use - feel free to make this dynamic using e.g a config file or argv/argc
    const std::string sampleLoc = "/home/goblirsc/Code/Tracking/IDPVM_Devel/run/"; 
    const std::string full_original = sampleLoc+"/OriginalIDPVM/PHYSVAL.fullStats.originalIDPVM.root";
    const std::string split_original = sampleLoc+"/OriginalIDPVM/PHYSVAL.splitRuns.originalIDPVM.root";
    const std::string guineaPig = sampleLoc+"/guineaPig.root";

    const std::string full = sampleLoc+"/PHYSVAL.allEvents.root";
    const std::string hadd = sampleLoc+"/PHYSVAL.rawHadd.root";
    const std::string PP = sampleLoc+"/PHYSVAL.PP.root";


    const std::string sglmu1_default = sampleLoc+"PHYSVAL.KeLi.sglmu1.root";
    const std::string sglmu1_more = sampleLoc+"PHYSVAL.KeLi.sglmu1.moreBins.root";
    const std::string sglmu100_default = sampleLoc+"PHYSVAL.KeLi.sglmu100.root";
    const std::string sglmu100_more = sampleLoc+"PHYSVAL.KeLi.sglmu100.moreBins.root";

    // plots to draw - one vector for each histogram type 
    const std::vector<std::string> plots1F {
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pull_d0",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/res_d0",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_eta_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_eta_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_pt_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_pt_d0",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_d0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_d0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_d0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_d0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_d0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_d0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_d0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_d0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pull_z0",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/res_z0",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_eta_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_eta_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_pt_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_pt_z0",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_z0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_z0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_z0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_z0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_z0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_z0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_z0_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_z0_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pull_ptqopt",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/res_ptqopt",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_eta_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_eta_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_pt_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_pt_ptqopt",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_ptqopt_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_ptqopt_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_ptqopt_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_ptqopt_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_ptqopt_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_ptqopt_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_ptqopt_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_ptqopt_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pull_theta",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/res_theta",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_eta_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_eta_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_pt_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_pt_theta",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_theta_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_theta_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_theta_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_theta_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_theta_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_theta_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_theta_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_theta_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pull_phi",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/res_phi",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_eta_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_eta_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_pt_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_pt_phi",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_phi_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_phi_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_phi_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_phi_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_phi_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_phi_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_phi_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_phi_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pull_z0sin",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/res_z0sin",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_eta_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_eta_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullwidth_vs_pt_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/pullmean_vs_pt_z0sin",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_z0sin_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_eta_z0sin_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_z0sin_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_eta_z0sin_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_z0sin_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resolution_vs_pt_z0sin_negQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_z0sin_posQ",
        // "SqurrielPlots/Tracks/Matched/Resolutions/Primary/resmean_vs_pt_z0sin_negQ",
    };

    const std::vector<std::string> plotsTP {   
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_eta_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_pt_d0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_eta_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_pt_z0",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_eta_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_pt_ptqopt",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_eta_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_pt_theta",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_eta_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_pt_phi",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_eta_z0sin",
        "SqurrielPlots/Tracks/Matched/Resolutions/Primary/sigma_vs_pt_z0sin",
    };
    SetAtlasStyle();

    // here we define the "samples" to include in our plot, and how they should look. 
    // See NtupleAnalysisUtils/PlotFormat.h for available options. 
    std::vector<genericPlotDef> todo {
            genericPlotDef{full, "Single run","PL", PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kRed+1)},
            genericPlotDef{hadd, "2 runs + hadd","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kBlue-3)},
            genericPlotDef{PP, "2 runs + hadd + PP","PL", PlotFormat().MarkerStyle(kOpenCircle).Color(kOrange-3)},
    };

    std::vector<genericPlotDef> todo_Binning_1 {
            genericPlotDef{sglmu1_default, "Default bins","PL", PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kRed+1)},
            genericPlotDef{sglmu1_more, "add more bins","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kBlue-3)},
    };

    std::vector<genericPlotDef> todo_Binning_100 {
            genericPlotDef{sglmu100_default, "Default bins","PL", PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kRed+1)},
            genericPlotDef{sglmu100_more, "add more bins","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kBlue-3)},
    };

    // specify the look of our canvas 
    CanvasOptions opts = CanvasOptions().fontSize(10).legendStartX(0.3).ratioAxisTitle("Ratio"); 
    // specify file names 
    const std::string fileNameBase = "PhysValPlots/PlotOverlay_"; 
    const std::string fileNameMultiPage = "PhysValPlots/AllPhysValPlots"; 
    // and labels... 
    std::vector<std::string> labels {""};
    std::vector<std::string> labelsKL1 {"1 GeV single mu"}; 
    std::vector<std::string> labelsKL100 {"100 GeV single mu"}; 
    // now book everything
    auto plots_1D = bookThem<TH1F>(plots1F, todo,labels,fileNameBase, fileNameMultiPage, opts); 
    auto plots_1D_resBin_1 = bookThem<TH1F>(plots1F, todo_Binning_1,labelsKL1,fileNameBase+"binCheck1GeV_", fileNameMultiPage, opts); 
    auto plots_1D_resBin_100 = bookThem<TH1F>(plots1F, todo_Binning_100,labelsKL100,fileNameBase+"binCheck100GeV_", fileNameMultiPage, opts); 
    auto plots_TP = bookThem<TProfile>(plotsTP, todo,labels,fileNameBase, fileNameMultiPage, opts); 

    // and plot it
    PlotUtils::startMultiPagePdfFile(fileNameMultiPage); 
    for (auto & p : plots_1D){
        // DefaultPlotting::draw1D(p);
    }
    for (auto & p : plots_1D_resBin_1){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : plots_1D_resBin_100){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : plots_TP){
        // DefaultPlotting::draw1D(p);
    }
    PlotUtils::endMultiPagePdfFile(fileNameMultiPage); 

    return 0;
}
