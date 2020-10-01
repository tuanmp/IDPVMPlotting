#include "NtupleAnalysisUtils/DefaultPlotting.h"
#include "NtupleAnalysisUtils/AtlasStyle.h"
#include "NtupleAnalysisUtils/CanvasOptions.h"
#include "NtupleAnalysisUtils/PlotPostProcessor.h"
#include "TEfficiency.h"
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
Plot<TH1D> generateEffPlot (const std::string & plot, const genericPlotDef & genericDef){

    return Plot<TH1D>{
        genericDef.fileName, 
        plot, 
        CommonPostProcessors::effExtractor(),
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
std::vector<PlotContent<TH1D>> bookEff(std::vector<std::string> plots, std::vector<genericPlotDef> defs, const std::vector<std::string> & labels, const std::string & fname_base, const std::string & fname_multiPagePDF, CanvasOptions CanvasOpts){

    // book the output vector 
    std::vector<PlotContent<TH1D>> output; 
    output.reserve(plots.size()); 

    // now add an entry for each plot we are interested in 
    for (auto & plot : plots){
        std::vector<Plot<TH1D>> entries;
        // here we book each of the canvas entries, one for each sample  
        for (auto & entry : defs){ 
            entries.push_back(generateEffPlot(plot,entry)); 
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
        output.push_back(PlotContent<TH1D>{
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
// /SquirrelPlots/TracksInJets/Tracks
    const std::string basePath = "/scratch/goblirsc/runDirs/Tracking/TrackFindingProf_andLRT/";
    const std::string ZPref = basePath+"ZPrimeChecks/ref_2020-09-28/PHYSVAL.ref.root";
    const std::string ZPchanges = basePath+"ZPrimeChecks/AmbiFixes_2020-09-28/PHYSVAL.ref.root";
    const std::string ZPchangesUpdate = basePath+"ZPrimeChecks/AmbiFixes_update1_2020-09-28/PHYSVAL.ref.root";
    const std::string ZPchangesBugfixOnly = basePath+"ZPrimeChecks/AmbiFixes_noROI_enablePix_2020-09-29/PHYSVAL.ref.root";
    const std::string ZPMaxesStuff = basePath+"ZPrimeChecks/ConfirmationTweaks_2020-09-30/PHYSVAL.ref.root";

    const std::string refTT = basePath+"/ref_2020-09-29/M_output.root";
    const std::string modTT = basePath+"/re-timing/CL18ConfUp/M_output.root";


    // plots to draw - one vector for each histogram type 
    const std::string & loc_reso = "SquirrelPlots/Tracks/Matched/Resolutions/Primary/"; 
    const std::string & loc_param = "SquirrelPlots/Tracks/Selected/Parameters/"; 
    // const std::string & loc_resoTP = "SquirrelPlots/TightPrimary/Tracks/Matched/Resolutions/Primary/"; 
    // const std::string & loc_paramTP = "SquirrelPlots/TightPrimary/Tracks/Selected/Parameters/"; 
    const std::string & loc_tracksInJets = "SquirrelPlots/TracksInJets/Tracks/"; 
    const std::string & loc_tracksInBJets = "SquirrelPlots/TracksInBJets/Tracks/"; 

    const std::vector<std::string> plots1F {
        loc_reso+"resolution_vs_eta_d0",
        loc_reso+"resmean_vs_eta_d0",
        loc_reso+"resolution_vs_pt_d0",
        loc_reso+"resmean_vs_pt_d0",
        loc_reso+"pullwidth_vs_eta_d0",
        loc_reso+"pullmean_vs_eta_d0",
        loc_reso+"pullwidth_vs_pt_d0",
        loc_reso+"pullmean_vs_pt_d0",
        loc_reso+"resolution_vs_eta_z0",
        loc_reso+"resmean_vs_eta_z0",
        loc_reso+"resolution_vs_pt_z0",
        loc_reso+"resmean_vs_pt_z0",
        loc_reso+"pullwidth_vs_eta_z0",
        loc_reso+"pullmean_vs_eta_z0",
        loc_reso+"pullwidth_vs_pt_z0",
        loc_reso+"pullmean_vs_pt_z0",
        loc_reso+"resolution_vs_eta_ptqopt",
        loc_reso+"resmean_vs_eta_ptqopt",
        loc_reso+"resolution_vs_pt_ptqopt",
        loc_reso+"resmean_vs_pt_ptqopt",
        loc_reso+"pullwidth_vs_eta_ptqopt",
        loc_reso+"pullmean_vs_eta_ptqopt",
        loc_reso+"pullwidth_vs_pt_ptqopt",
        loc_reso+"pullmean_vs_pt_ptqopt",
        loc_reso+"resolution_vs_eta_theta",
        loc_reso+"resmean_vs_eta_theta",
        loc_reso+"resolution_vs_pt_theta",
        loc_reso+"resmean_vs_pt_theta",
        loc_reso+"pullwidth_vs_eta_theta",
        loc_reso+"pullmean_vs_eta_theta",
        loc_reso+"pullwidth_vs_pt_theta",
        loc_reso+"pullmean_vs_pt_theta",
        loc_reso+"resolution_vs_eta_phi",
        loc_reso+"resmean_vs_eta_phi",
        loc_reso+"resolution_vs_pt_phi",
        loc_reso+"resmean_vs_pt_phi",
        loc_reso+"pullwidth_vs_eta_phi",
        loc_reso+"pullmean_vs_eta_phi",
        loc_reso+"pullwidth_vs_pt_phi",
        loc_reso+"pullmean_vs_pt_phi",
        loc_reso+"resolution_vs_eta_z0sin",
        loc_reso+"resmean_vs_eta_z0sin",
        loc_reso+"resolution_vs_pt_z0sin",
        loc_reso+"resmean_vs_pt_z0sin",
        loc_reso+"pullwidth_vs_eta_z0sin",
        loc_reso+"pullmean_vs_eta_z0sin",
        loc_reso+"pullwidth_vs_pt_z0sin",
        loc_reso+"pullmean_vs_pt_z0sin",

        loc_param+"reco_pt",
        loc_param+"reco_lowpt",
        loc_param+"reco_chi2",
        loc_param+"reco_chi2Overndof",
        loc_param+"reco_eta",
        loc_param+"reco_phi",
        loc_param+"reco_z0sin",
        loc_param+"reco_z0",
        loc_param+"reco_d0",


        // loc_resoTP+"resolution_vs_eta_d0",
        // loc_resoTP+"resmean_vs_eta_d0",
        // loc_resoTP+"resolution_vs_pt_d0",
        // loc_resoTP+"resmean_vs_pt_d0",
        // loc_resoTP+"pullwidth_vs_eta_d0",
        // loc_resoTP+"pullmean_vs_eta_d0",
        // loc_resoTP+"pullwidth_vs_pt_d0",
        // loc_resoTP+"pullmean_vs_pt_d0",
        // loc_resoTP+"resolution_vs_eta_z0",
        // loc_resoTP+"resmean_vs_eta_z0",
        // loc_resoTP+"resolution_vs_pt_z0",
        // loc_resoTP+"resmean_vs_pt_z0",
        // loc_resoTP+"pullwidth_vs_eta_z0",
        // loc_resoTP+"pullmean_vs_eta_z0",
        // loc_resoTP+"pullwidth_vs_pt_z0",
        // loc_resoTP+"pullmean_vs_pt_z0",
        // loc_resoTP+"resolution_vs_eta_ptqopt",
        // loc_resoTP+"resmean_vs_eta_ptqopt",
        // loc_resoTP+"resolution_vs_pt_ptqopt",
        // loc_resoTP+"resmean_vs_pt_ptqopt",
        // loc_resoTP+"pullwidth_vs_eta_ptqopt",
        // loc_resoTP+"pullmean_vs_eta_ptqopt",
        // loc_resoTP+"pullwidth_vs_pt_ptqopt",
        // loc_resoTP+"pullmean_vs_pt_ptqopt",
        // loc_resoTP+"resolution_vs_eta_theta",
        // loc_resoTP+"resmean_vs_eta_theta",
        // loc_resoTP+"resolution_vs_pt_theta",
        // loc_resoTP+"resmean_vs_pt_theta",
        // loc_resoTP+"pullwidth_vs_eta_theta",
        // loc_resoTP+"pullmean_vs_eta_theta",
        // loc_resoTP+"pullwidth_vs_pt_theta",
        // loc_resoTP+"pullmean_vs_pt_theta",
        // loc_resoTP+"resolution_vs_eta_phi",
        // loc_resoTP+"resmean_vs_eta_phi",
        // loc_resoTP+"resolution_vs_pt_phi",
        // loc_resoTP+"resmean_vs_pt_phi",
        // loc_resoTP+"pullwidth_vs_eta_phi",
        // loc_resoTP+"pullmean_vs_eta_phi",
        // loc_resoTP+"pullwidth_vs_pt_phi",
        // loc_resoTP+"pullmean_vs_pt_phi",
        // loc_resoTP+"resolution_vs_eta_z0sin",
        // loc_resoTP+"resmean_vs_eta_z0sin",
        // loc_resoTP+"resolution_vs_pt_z0sin",
        // loc_resoTP+"resmean_vs_pt_z0sin",
        // loc_resoTP+"pullwidth_vs_eta_z0sin",
        // loc_resoTP+"pullmean_vs_eta_z0sin",
        // loc_resoTP+"pullwidth_vs_pt_z0sin",
        // loc_resoTP+"pullmean_vs_pt_z0sin",

        // loc_paramTP+"reco_pt",
        // loc_paramTP+"reco_lowpt",
        // loc_paramTP+"reco_chi2",
        // loc_paramTP+"reco_chi2Overndof",
        // loc_paramTP+"reco_eta",
        // loc_paramTP+"reco_phi",
        // loc_paramTP+"reco_z0sin",
        // loc_paramTP+"reco_z0",
        // loc_paramTP+"reco_d0",

    };

    const std::string & path_Effi = "SquirrelPlots/Tracks/Efficiency/"; 
    // const std::string & path_Effi_TP = "SquirrelPlots/TightPrimary/Tracks/Efficiency/"; 
    const std::string & path_fake = "SquirrelPlots/Tracks/FakeRate/"; 
    // const std::string & path_fake_TP = "SquirrelPlots/TightPrimary/Tracks/FakeRate/"; 
    const std::string & path_unlinked = "SquirrelPlots/Tracks/Unlinked/FakeRate/"; 
    // const std::string & path_unlinked_TP = "SquirrelPlots/TightPrimary/Tracks/Unlinked/FakeRate/"; 
    const std::vector<std::string> plotsTE { 
        path_Effi+"efficiency_vs_eta",
        // path_Effi_TP+"efficiency_vs_eta",
        path_Effi+"efficiency_vs_pt",
        // path_Effi_TP+"efficiency_vs_pt",
        path_Effi+"efficiency_vs_pt_low",
        // path_Effi_TP+"efficiency_vs_pt_low",
        path_Effi+"efficiency_vs_phi",
        // path_Effi_TP+"efficiency_vs_phi",
        path_Effi+"efficiency_vs_d0",
        // path_Effi_TP+"efficiency_vs_d0",
        path_Effi+"efficiency_vs_z0",
        // path_Effi_TP+"efficiency_vs_z0",
        path_Effi+"efficiency_vs_prodR",
        // path_Effi_TP+"efficiency_vs_prodR",
        path_Effi+"efficiency_vs_prodZ",
        // path_Effi_TP+"efficiency_vs_prodZ",

        // path_unlinked_TP+"fakerate_vs_eta",
        // path_unlinked_TP+"fakerate_vs_pt",
        // path_unlinked_TP+"fakerate_vs_phi",
        // path_unlinked_TP+"fakerate_vs_d0",
        // path_unlinked_TP+"fakerate_vs_z0",
        // path_fake_TP+"fakerate_vs_eta",
        // path_fake_TP+"fakerate_vs_pt",
        // path_fake_TP+"fakerate_vs_phi",
        // path_fake_TP+"fakerate_vs_d0",
        // path_fake_TP+"fakerate_vs_z0",

        path_unlinked+"fakerate_vs_eta",
        path_unlinked+"fakerate_vs_pt",
        path_unlinked+"fakerate_vs_phi",
        path_unlinked+"fakerate_vs_d0",
        path_unlinked+"fakerate_vs_z0",
        path_fake+"fakerate_vs_eta",
        path_fake+"fakerate_vs_pt",
        path_fake+"fakerate_vs_phi",
        path_fake+"fakerate_vs_d0",
        path_fake+"fakerate_vs_z0",


    };
    const std::vector<std::string> plotsJetTP {
        loc_tracksInJets+"nInnerMostPixelHits_vs_dR",
        loc_tracksInJets+"nNextToInnerMostPixelHits_vs_dR",
        loc_tracksInJets+"nPixelHits_vs_dR",
        loc_tracksInJets+"nSCTHits_vs_dR",
        loc_tracksInJets+"nTRTHits_vs_dR",
        loc_tracksInJets+"nPixelHoles_vs_dR",
        loc_tracksInJets+"nSCTHoles_vs_dR",
        loc_tracksInJets+"nTRTHighThresholdHits_vs_dR",
        loc_tracksInBJets+"nInnerMostPixelHits_vs_dR",
        loc_tracksInBJets+"nNextToInnerMostPixelHits_vs_dR",
        loc_tracksInBJets+"nPixelHits_vs_dR",
        loc_tracksInBJets+"nSCTHits_vs_dR",
        loc_tracksInBJets+"nTRTHits_vs_dR",
        loc_tracksInBJets+"nPixelHoles_vs_dR",
        loc_tracksInBJets+"nSCTHoles_vs_dR",
        loc_tracksInBJets+"nTRTHighThresholdHits_vs_dR",
        loc_tracksInJets+"reco_d0_vs_dR",
        loc_tracksInJets+"reco_z0_vs_dR",
        loc_tracksInJets+"reco_z0sin_vs_dR",
        loc_tracksInJets+"reco_phi_vs_dR",
        loc_tracksInJets+"reco_theta_vs_dR",
        loc_tracksInJets+"reco_eta_vs_dR",
        loc_tracksInJets+"reco_pt_vs_dR",
        loc_tracksInJets+"reco_lowpt_vs_dR",
        loc_tracksInJets+"reco_chi2Overndof_vs_dR",

        loc_tracksInBJets+"reco_d0_vs_dR",
        loc_tracksInBJets+"reco_z0_vs_dR",
        loc_tracksInBJets+"reco_z0sin_vs_dR",
        loc_tracksInBJets+"reco_phi_vs_dR",
        loc_tracksInBJets+"reco_theta_vs_dR",
        loc_tracksInBJets+"reco_eta_vs_dR",
        loc_tracksInBJets+"reco_pt_vs_dR",
        loc_tracksInBJets+"reco_lowpt_vs_dR",
        loc_tracksInBJets+"reco_chi2Overndof_vs_dR",
    };  
    const std::vector<std::string> plotsJetTE { 
        loc_tracksInJets+"efficiency_vs_dR",
        loc_tracksInJets+"efficiency_vs_smalldR",
        loc_tracksInJets+"efficiency_vs_jetpT",
        loc_tracksInJets+"fakerate_vs_dR",
        loc_tracksInJets+"fakerate_vs_smalldR",
        loc_tracksInJets+"fakerate_vs_jetpT",

        loc_tracksInBJets+"efficiency_vs_dR",
        loc_tracksInBJets+"efficiency_vs_smalldR",
        loc_tracksInBJets+"efficiency_vs_jetpT",
        loc_tracksInBJets+"fakerate_vs_dR",
        loc_tracksInBJets+"fakerate_vs_smalldR",
        loc_tracksInBJets+"fakerate_vs_jetpT",
    };
    const std::string path_hitsOnTrack="SquirrelPlots/Tracks/Selected/HitsOnTracks/"; 


    const std::vector<std::string> plotsTP{
        path_hitsOnTrack+"nPixelHits_vs_eta",
        path_hitsOnTrack+"nSCTHits_vs_eta",
        path_hitsOnTrack+"nTRTHits_vs_eta",
        path_hitsOnTrack+"nPixelHoles_vs_eta",
        path_hitsOnTrack+"nTRTHighThresholdHits_vs_eta",
        path_hitsOnTrack+"nInnerMostPixelHits_vs_phi",
        path_hitsOnTrack+"nNextToInnerMostPixelHits_vs_phi",
        path_hitsOnTrack+"nPixelHits_vs_phi",
        path_hitsOnTrack+"nSCTHits_vs_phi",
        path_hitsOnTrack+"nPixelHoles_vs_phi",
        path_hitsOnTrack+"nTRTHits_vs_phi",
        path_hitsOnTrack+"nTRTHighThresholdHits_vs_phi",



    };

    SetAtlasStyle();

    // here we define the "samples" to include in our plot, and how they should look. 
    // See NtupleAnalysisUtils/PlotFormat.h for available options. 
    std::vector<genericPlotDef> todo_Zprime {
            genericPlotDef{ZPref, "Master","PL", PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kBlack)},
            genericPlotDef{ZPMaxesStuff, "Confirmation tweak","PL", PlotFormat().MarkerStyle(kFullTriangleDown).Color(kBlue)},
            // genericPlotDef{ZPchanges, "!36752, initial","PL", PlotFormat().MarkerStyle(kFullDiamond).Color(kOrange-3)},
            // genericPlotDef{ZPchangesUpdate, "!36752, current","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kRed)},
            // genericPlotDef{ZPchangesBugfixOnly, "!36752, only bug-fixes","PL", PlotFormat().MarkerStyle(kFullTriangleDown).Color(kBlue)},
 
    };


    std::vector<genericPlotDef> todo_ttbar {
            genericPlotDef{refTT, "Master","PL", PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kBlack)},
            genericPlotDef{modTT, "Modified conf.","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kBlue)},
            
 
    };

    // specify the look of our canvas 
    CanvasOptions opts = CanvasOptions().fontSize(10).legendStartX(0.3).ratioAxisTitle("Ratio w.r.t Default").outputFormats({".pdf",".png"}); 
    CanvasOptions optsEff = CanvasOptions().fontSize(10).legendStartX(0.3).ratioAxisTitle("Ratio w.r.t Default").outputFormats({".pdf",".png"}).ratioMax(1.01).ratioMin(0.96); 
    // specify file names 
    const std::string fileNameBase_ZP = "PhysValPlots/AmbiTuning/Zprime/"; 
    const std::string fileNameMultiPage = "PhysValPlots/AmbiTuning/Zprime/AllZprimeChecks"; 
    // specify file names 
    const std::string fileNameBase_tt = "PhysValPlots/AmbiTuning/ttbar/"; 
    const std::string fileNameMultiPage_tt = "PhysValPlots/AmbiTuning/ttbar/AllTtbarChecks"; 
    // and labels... 
    std::vector<std::string> labels_ZP {"Master RDO, Z', <#mu>=0, 100 GeV < jet p_{T} < 1 TeV"};
    std::vector<std::string> labels_tt {"Master RDO, t#bar{t}, <#mu>=60"};





    auto v_plotsTP = bookThem<TProfile>(plotsTP, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, opts); 
    auto v_plotsEff = bookEff(plotsTE, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, optsEff); 
    auto v_plots_1D = bookThem<TH1F>(plots1F, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, opts); 
    auto v_plots_JetTP = bookThem<TProfile>(plotsJetTP, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, opts); 
    auto v_plots_JetEff = bookEff(plotsJetTE, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, optsEff); 


    auto v_plotsTPtt = bookThem<TProfile>(plotsTP, todo_ttbar,labels_tt,fileNameBase_tt, fileNameMultiPage_tt, opts); 
    auto v_plotsEfftt = bookEff(plotsTE, todo_ttbar,labels_tt,fileNameBase_tt, fileNameMultiPage_tt, optsEff); 
    auto v_plots_1Dtt = bookThem<TH1F>(plots1F, todo_ttbar,labels_tt,fileNameBase_tt, fileNameMultiPage_tt, opts); 
    

    // // and plot it
    PlotUtils::startMultiPagePdfFile(fileNameMultiPage); 
    for (auto & p : v_plotsTP){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : v_plotsEff){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : v_plots_1D){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : v_plots_JetTP){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : v_plots_JetEff){
        DefaultPlotting::draw1D(p);
    }
    PlotUtils::endMultiPagePdfFile(fileNameMultiPage); 


    // PlotUtils::startMultiPagePdfFile(fileNameMultiPage_tt); 
    // for (auto & p : v_plotsTPtt){
    //     DefaultPlotting::draw1D(p);
    // }
    // for (auto & p : v_plotsEfftt){
    //     DefaultPlotting::draw1D(p);
    // }
    // for (auto & p : v_plots_1Dtt){
    //     DefaultPlotting::draw1D(p);
    // }
    // PlotUtils::endMultiPagePdfFile(fileNameMultiPage_tt); 

    return 0;
}
