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
    // const std::string ZPref = basePath+"ZPrimeChecks/ref_2020-09-28/M_output.root";
    // const std::string ZPchanges = basePath+"ZPrimeChecks/AmbiFixes_2020-09-28/PHYSVAL.ref.root";
    // const std::string ZPchangesUpdate = basePath+"ZPrimeChecks/AmbiFixes_update1_2020-09-28/PHYSVAL.ref.root";
    // const std::string ZPchangesBugfixOnly = basePath+"ZPrimeChecks/AmbiFixes_noROI_enablePix_2020-09-29/PHYSVAL.ref.root";
    const std::string ZPMaxNew = basePath+"/ZPrimeChecks/2020-10-1X-fineTuning/DSlope_1.25_2.0//M_output.root";
    const std::string ZPMaxNew2 = basePath+"/ZPrimeChecks/2020-10-1X-fineTuning/DSlope_1.25_2.0_highPtConfUp/M_output.root";

    const std::string ZPref = basePath+"/ZPrimeChecks/HoleSearchChecks/ref_r23/M_output.root";
    const std::string ZPPatHolesOff = basePath+"/ZPrimeChecks/HoleSearchChecks/NoHolesFromPat/M_output.root";
    const std::string ZPPatHolesOn = basePath+"/ZPrimeChecks/HoleSearchChecks/WithHolesFromPat/M_output.root";
    const std::string ZPIGOR = basePath+"/ZPrimeChecks/HoleSearchChecks/HolesIGOR/M_output.root";
    const std::string ZPMAX = basePath+"/ZPrimeChecks/HoleSearchChecks//LatestHoles/M_output.root";

    const std::string refTT = basePath+"/ref_2020-10-20-r19/M_output.root";
    // const std::string modTT = basePath+"/2020-10-1X-FinderFineTuning/DSlope_1.25_2.0/M_output.root";
    // const std::string mod2TT = basePath+"/2020-10-1X-FinderFineTuning/DSlope_1.25_2.0_highPtConfUp/M_output.root";
    const std::string PatHolesOff = basePath+"/HolesInPattern//test5_flag/M_output.root";
    const std::string PatHolesOn = basePath+"/HolesInPattern//test4_fullThing/M_output.root";
    const std::string IGOR = basePath+"/HolesInPattern/test9_tolerance2_IgorsClusterErrors/M_output.root";
    const std::string MAX = basePath+"/HolesInPattern/test10_experiment/M_output.root";
    const std::string Noise = basePath+"/HolesInPattern/test11_noisynoise/M_output.root";
    const std::string C14 = basePath+"/CL14_old/M_output.root";
    const std::string C16 = basePath+"/CL16/M_output.root";

    // const std::string noTRTHoleUpdate = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/2020-11-13-soManyHoles/test_noHoleSearch/M_output.root";
    const std::string holesWithCut = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/2020-11-13-soManyHoles/test_withHoleSearchAndCut/M_output.root";
    const std::string baseR12 = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/2020-11-13-soManyHoles/ref/M_output.root";
    const std::string backToPrecision = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/revertPrecisionHoles/M_output.root";
    const std::string precisionAndGX2Holes = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/revertPrecision_holesInFit/M_output.root";
    const std::string precisionAndGX2HolesAndTRT = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/revertPrecision_holesInFit_alsoTRT/M_output.root";
    const std::string Oct27 = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/profile_r27_Oct2020/M_output.root";
    const std::string Oct23 = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/2020-11-20-timing_October_r23/M_output.root";
    const std::string Aug1 = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/re-timing/CL19/M_output.root";
    const std::string Jan1 = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/CL16_oldRelease/M_output.root";

    const std::string ZP_withCut = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/ZPrimeChecks/2020-11-15-TRTHoleSearch/M_output.root"; 
    const std::string ZP_r13 = "/home/goblirsc/Code/Tracking/TrackFindingProf_andLRT/run/ZPrimeChecks/2020-11-15-r13/M_output.root"; 

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
    const std::string & path_Effi_TP = "SquirrelPlots/TightPrimary/Tracks/Efficiency/"; 
    const std::string & path_fake = "SquirrelPlots/Tracks/FakeRate/"; 
    const std::string & path_fake_TP = "SquirrelPlots/TightPrimary/Tracks/FakeRate/"; 
    const std::string & path_unlinked = "SquirrelPlots/Tracks/Unlinked/FakeRate/"; 
    const std::string & path_unlinked_TP = "SquirrelPlots/TightPrimary/Tracks/Unlinked/FakeRate/"; 
    const std::vector<std::string> plotsTE { 
        path_Effi+"efficiency_vs_eta",
        path_Effi_TP+"efficiency_vs_eta",
        path_Effi+"efficiency_vs_pt",
        path_Effi_TP+"efficiency_vs_pt",
        path_Effi+"efficiency_vs_pt_low",
        path_Effi_TP+"efficiency_vs_pt_low",
        path_Effi+"efficiency_vs_phi",
        // path_Effi_TP+"efficiency_vs_phi",
        // path_Effi+"efficiency_vs_d0",
        // path_Effi_TP+"efficiency_vs_d0",
        // path_Effi+"efficiency_vs_z0",
        // path_Effi_TP+"efficiency_vs_z0",
        path_Effi+"efficiency_vs_prodR",
        path_Effi_TP+"efficiency_vs_prodR",
        // path_Effi+"efficiency_vs_prodZ",
        // path_Effi_TP+"efficiency_vs_prodZ",

        path_unlinked+"fakerate_vs_eta",
        path_unlinked_TP+"fakerate_vs_eta",
        path_unlinked+"fakerate_vs_pt",
        path_unlinked_TP+"fakerate_vs_pt",
        path_unlinked+"fakerate_vs_phi",
        path_unlinked_TP+"fakerate_vs_phi",
        // path_unlinked+"fakerate_vs_d0",
        // path_unlinked_TP+"fakerate_vs_d0",
        // path_unlinked+"fakerate_vs_z0",
        // path_unlinked_TP+"fakerate_vs_z0",
        path_fake+"fakerate_vs_eta",
        path_fake_TP+"fakerate_vs_eta",
        path_fake+"fakerate_vs_pt",
        path_fake_TP+"fakerate_vs_pt",
        path_fake+"fakerate_vs_phi",
        path_fake_TP+"fakerate_vs_phi",
        // path_fake+"fakerate_vs_d0",
        // path_fake_TP+"fakerate_vs_d0",
        // path_fake+"fakerate_vs_z0",
        // path_fake_TP+"fakerate_vs_z0",


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
    const std::string path_hitsOnTrackMatched="SquirrelPlots/Tracks/Matched/HitsOnTracks/"; 
    const std::string path_hitsOnTrackFake="SquirrelPlots/Tracks/Fakes/HitsOnTracks/"; 


    const std::vector<std::string> plotsTP{
        path_hitsOnTrack+"nPixelHits_vs_eta",
        path_hitsOnTrackMatched+"nPixelHits_vs_eta",
        path_hitsOnTrackFake+"nPixelHits_vs_eta",

        path_hitsOnTrack+"nSCTHits_vs_eta",
        path_hitsOnTrackMatched+"nSCTHits_vs_eta",
        path_hitsOnTrackFake+"nSCTHits_vs_eta",

        path_hitsOnTrack+"nTRTHits_vs_eta",
        path_hitsOnTrackMatched+"nTRTHits_vs_eta",
        path_hitsOnTrackFake+"nTRTHits_vs_eta",

        path_hitsOnTrack+"nPixelHoles_vs_eta",
        path_hitsOnTrackMatched+"nPixelHoles_vs_eta",
        path_hitsOnTrackFake+"nPixelHoles_vs_eta",

        path_hitsOnTrack+"nSCTHoles_vs_eta",
        path_hitsOnTrackMatched+"nSCTHoles_vs_eta",
        path_hitsOnTrackFake+"nSCTHoles_vs_eta",

        path_hitsOnTrack+"nTRTHighThresholdHits_vs_eta",
        path_hitsOnTrack+"nInnerMostPixelHits_vs_phi",
        path_hitsOnTrack+"nNextToInnerMostPixelHits_vs_phi",
        path_hitsOnTrack+"nPixelHits_vs_phi",
        path_hitsOnTrack+"nSCTHits_vs_phi",
        path_hitsOnTrack+"nPixelDeadSensors_vs_eta",
        path_hitsOnTrack+"nSCTDeadSensors_vs_eta",
        path_hitsOnTrack+"nPixelDeadSensors_vs_phi",
        path_hitsOnTrack+"nSCTDeadSensors_vs_phi",
        path_hitsOnTrack+"nPixelHoles_vs_phi",
        path_hitsOnTrack+"nTRTHits_vs_phi",
        path_hitsOnTrack+"nTRTHighThresholdHits_vs_phi",



    };

    SetAtlasStyle();

    // here we define the "samples" to include in our plot, and how they should look. 
    // See NtupleAnalysisUtils/PlotFormat.h for available options. 
    // std::vector<genericPlotDef> todo_Zprime {
    //         genericPlotDef{ZPref, "2020-09-28","PL", PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kBlack)},
    //         genericPlotDef{ZPMaxNew, "Test","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kBlue)},
    //         genericPlotDef{ZPMaxNew2, "Test 2","PL", PlotFormat().MarkerStyle(kFullCircle).Color(kRed)},
    //         // genericPlotDef{ZPchanges, "!36752, initial","PL", PlotFormat().MarkerStyle(kFullDiamond).Color(kOrange-3)},
    //         // genericPlotDef{ZPchangesUpdate, "!36752, current","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kRed)},
    //         // genericPlotDef{ZPchangesBugfixOnly, "!36752, only bug-fixes","PL", PlotFormat().MarkerStyle(kFullTriangleDown).Color(kBlue)},
 
    // };

    std::string title_master = "Master (pattern holes)";
    std::string title_patHolesOff = "Old master, before pattern holes";
    std::string title_noTRT = "no TRT ext hole search";
    std::string title_withCut = "Master (patern holes) + Option 2";
    std::string title_Monday = "Pattern holes, Monday";
    std::string title_Today = "Pattern holes, updated";
    std::string title_CL16 = "CL 16";
    std::string title_CL14 = "CL 14";
    std::string title_backToPrecision = "Default (precision) hole search";
    std::string title_backToPrecisionGX2Hole = "GX2 Holes";
    std::string title_backToPrecisionGX2HoleTRT = "GX2 Holes, also in Ext.";
    std::string title_Oct27= "Oct27";
    std::string title_Oct23= "Oct23";
    std::string title_Aug1= "2020-08-01T1202";
    std::string title_Jan1= "2020-01-27T2131(!)";

    PlotFormat pf_master = PlotFormat().MarkerStyle(kFullSquare).MarkerScale(1.2).Color(kBlue-7); 
    PlotFormat pf_patHolesOff = PlotFormat().MarkerStyle(kOpenSquare).MarkerScale(1.2).Color(kGray+1); 
    PlotFormat pf_Monday = PlotFormat().MarkerStyle(kOpenCrossX).Color(kOrange-3); 
    PlotFormat pf_Today = PlotFormat().MarkerStyle(kFullCrossX).Color(kBlack); 
    PlotFormat pf_CL16 = PlotFormat().MarkerStyle(kOpenTriangleUp).Color(kGreen+3); 
    PlotFormat pf_CL14 = PlotFormat().MarkerStyle(kOpenDiamond).Color(kGray+3); 
    PlotFormat pf_Oct27 = PlotFormat().MarkerStyle(kOpenTriangleUp).Color(kGreen+3); 
    PlotFormat pf_Oct23 = PlotFormat().MarkerStyle(kOpenDiamond).Color(kGray+3); 
    PlotFormat pf_Aug1 = PlotFormat().MarkerStyle(kOpenCross).Color(kRed); 
    PlotFormat pf_Jan1 = PlotFormat().MarkerStyle(kOpenDiamondCross).Color(kViolet); 
    PlotFormat pf_backToPrecision = PlotFormat().MarkerStyle(kFullDotLarge).Color(kBlack); 
    PlotFormat pf_backToPrecisionGX2Hole = PlotFormat().MarkerStyle(kFullCross).Color(kRed); 
    PlotFormat pf_backToPrecisionGX2HoleTRT = PlotFormat().MarkerStyle(kOpenDiamond).Color(kBlue-7); 

    std::vector<genericPlotDef> todo_Zprime {
            // genericPlotDef{ZPref, "r23","PL", pf_CL16},
            genericPlotDef{ZP_r13, title_master,"PL", pf_master},
            genericPlotDef{ZP_withCut, title_withCut,"PL", pf_Monday},
    };

    // std::vector<genericPlotDef> todo_ttbar {
    //         genericPlotDef{refTT, title_master,"PL", pf_master},
    //         genericPlotDef{PatHolesOn, title_Monday,"PL", pf_Monday},
    //         genericPlotDef{Noise, title_Today,"PL", pf_Today},
    //         genericPlotDef{C14, title_CL14,"PL", pf_CL14},
    //         genericPlotDef{C16, title_CL16,"PL", pf_CL16},
    // };

    std::vector<genericPlotDef> todo_ttbar {
            // genericPlotDef{PatHolesOff, title_patHolesOff,"PL", pf_patHolesOff},
            genericPlotDef{baseR12, title_master,"PL", pf_patHolesOff},
            // genericPlotDef{holesWithCut, title_withCut,"PL", pf_Monday},
            genericPlotDef{backToPrecision, title_backToPrecision,"PL", pf_backToPrecision},
            // genericPlotDef{precisionAndGX2Holes, title_backToPrecisionGX2Hole,"PL", pf_backToPrecisionGX2Hole},
            genericPlotDef{precisionAndGX2HolesAndTRT, title_backToPrecisionGX2HoleTRT,"PL", pf_backToPrecisionGX2HoleTRT},
            genericPlotDef{Oct27, title_Oct27,"PL", pf_Oct27},
            genericPlotDef{Oct23, title_Oct23,"PL", pf_Oct23},
            genericPlotDef{Aug1, title_Aug1,"PL", pf_Aug1},
            genericPlotDef{Jan1, title_Jan1,"PL", pf_Jan1},
            // genericPlotDef{C16, title_CL16,"PL", pf_CL16},
    };

    // specify the look of our canvas 
    CanvasOptions opts = CanvasOptions().fontSize(10).legendStartX(0.3).ratioAxisTitle("Ratio w.r.t Default").outputFormats({".pdf",".png"}).ratioMax(1.4).ratioMin(0.6); 
    CanvasOptions optsEff = CanvasOptions().fontSize(10).legendStartX(0.3).ratioAxisTitle("Ratio w.r.t Default").outputFormats({".pdf",".png"}).ratioMax(1.04).ratioMin(0.96); 
    // specify file names 
    const std::string fileNameBase_ZP = "PhysValPlots/AmbiTuning/Zprime/"; 
    const std::string fileNameMultiPage = "PhysValPlots/AmbiTuning/Zprime/AllZprimeChecks"; 
    // specify file names 
    const std::string fileNameBase_tt = "PhysValPlots/AmbiTuning/ttbar/"; 
    const std::string fileNameMultiPage_tt = "PhysValPlots/AmbiTuning/ttbar/AllTtbarChecks"; 
    // and labels... 
    std::vector<std::string> labels_ZP {"Master RDO, Z', <#mu>=0, 100 GeV < jet p_{T} < 1 TeV"};
    std::vector<std::string> labels_tt {"Master RDO, t#bar{t}, <#mu>=60","MinBias-like selection: All PU included"};





    auto v_plotsTP = bookThem<TProfile>(plotsTP, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, opts); 
    auto v_plotsEff = bookEff(plotsTE, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, optsEff); 
    auto v_plots_1D = bookThem<TH1F>(plots1F, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, opts); 
    auto v_plots_JetTP = bookThem<TProfile>(plotsJetTP, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, opts); 
    auto v_plots_JetEff = bookEff(plotsJetTE, todo_Zprime,labels_ZP,fileNameBase_ZP, fileNameMultiPage, optsEff); 


    auto v_plotsTPtt = bookThem<TProfile>(plotsTP, todo_ttbar,labels_tt,fileNameBase_tt, fileNameMultiPage_tt, opts); 
    auto v_plotsEfftt = bookEff(plotsTE, todo_ttbar,labels_tt,fileNameBase_tt, fileNameMultiPage_tt, optsEff); 
    auto v_plots_1Dtt = bookThem<TH1F>(plots1F, todo_ttbar,labels_tt,fileNameBase_tt, fileNameMultiPage_tt, opts); 
    

    // // and plot it
    // PlotUtils::startMultiPagePdfFile(fileNameMultiPage); 
    // for (auto & p : v_plotsTP){
    //     DefaultPlotting::draw1D(p);
    // }
    // for (auto & p : v_plotsEff){
    //     DefaultPlotting::draw1D(p);
    // }
    // for (auto & p : v_plots_1D){
    //     DefaultPlotting::draw1D(p);
    // }
    // for (auto & p : v_plots_JetTP){
    //     DefaultPlotting::draw1D(p);
    // }
    // for (auto & p : v_plots_JetEff){
    //     DefaultPlotting::draw1D(p);
    // }
    // PlotUtils::endMultiPagePdfFile(fileNameMultiPage); 


    PlotUtils::startMultiPagePdfFile(fileNameMultiPage_tt); 
    for (auto & p : v_plotsTPtt){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : v_plotsEfftt){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : v_plots_1Dtt){
        DefaultPlotting::draw1D(p);
    }
    PlotUtils::endMultiPagePdfFile(fileNameMultiPage_tt); 

    return 0;
}
