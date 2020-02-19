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

// template-specialise this in case we need special treatment for certain plot types (e.g TH2F projection into 1D). 
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
    const std::string sampleLoc = "/home/goblirsc/Datasets/Tracking/HIST/"; 
    const std::string ref = sampleLoc+"356124_LB245_10feb20_HIST";
    const std::string test_buggy = sampleLoc+"356124_LB245_IDcutVtx_10feb20_HIST";
    const std::string test_n207 = sampleLoc+"356124_LB245_IDcutVtx_n0207_12feb20_HIST";
    const std::string test_n210 = sampleLoc+"356124_LB245_IDcutVtx_n0210_12feb20_HIST";

    // plots to draw - one vector for each histogram type 
    const std::vector<std::string> plots1F {
        "run_356124/InDetGlobal/Pixel/m_Pixel_track_chi2",     
        "run_356124/InDetGlobal/Pixel/m_Pixel_track_d0",     
        "run_356124/InDetGlobal/Pixel/m_Pixel_track_eta",    
        "run_356124/InDetGlobal/Pixel/m_Pixel_track_phi0",      
        "run_356124/InDetGlobal/Pixel/m_Pixel_track_z0",      
        "run_356124/InDetGlobal/PrimaryVertex/pvX",      
        "run_356124/InDetGlobal/PrimaryVertex/pvY",    
        "run_356124/InDetGlobal/PrimaryVertex/pvZ",        
        "run_356124/InDetGlobal/PrimaryVertex/pvTrackPt",        
        "run_356124/InDetGlobal/PrimaryVertex/pvTrackEta",     
        "run_356124/InDetGlobal/PrimaryVertex/pvNTracks",     
        "run_356124/InDetGlobal/PrimaryVertex/pvNPriVtx",        
        "run_356124/InDetGlobal/PrimaryVertex/pvNPileupVtx",        
        "run_356124/InDetGlobal/PrimaryVertex/pvN",         
        "run_356124/InDetGlobal/PrimaryVertex/pvErrX",        
        "run_356124/InDetGlobal/PrimaryVertex/pvErrY",       
        "run_356124/InDetGlobal/PrimaryVertex/pvErrZ",        
        "run_356124/InDetGlobal/PrimaryVertex/pvChiSqDof",          
        "run_356124/InDetGlobal/BeamSpot/trkNPt",             
        "run_356124/InDetGlobal/BeamSpot/trkPt",            
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/pT",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/eta",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/phi",   
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/z0",    
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/d0",                  
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Npixhits_per_track",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Nscthits_per_track",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Ntrthits_per_track",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Npixhits_per_track_eca",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Npixhits_per_track_barrel",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Nhits_per_track",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Npixhits_per_track_barrel",        
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Npixhits_per_track_eca",             
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Npixhits_per_track_ecc",           
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Nscthits_per_track_barrel",           
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Nscthits_per_track_eca",           
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Nscthits_per_track_ecc",       
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Ntrthits_per_track_barrel",       
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Ntrthits_per_track_eca",       
        "run_356124/IDAlignMon/ExtendedTracks_NoTriggerSelection/GenericTracks/Ntrthits_per_track_ecc",   
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NPixelHits",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NPixelHoles",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NSCTHits",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NSCTHoles",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NTRTHighThresholdHits",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NTRTHits",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_d0_small",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_d0",    
        "run_356124/MuonPhysics/TracksID/CBMuons/TracksID_CBMuons_HitContent_NPixelHits", 
        "run_356124/SCT/GENERAL/tracks/trk_N",                      
        "run_356124/SCT/GENERAL/tracks/trk_d0",                      
        "run_356124/SCT/GENERAL/tracks/trk_z0",                      
        "run_356124/SCT/GENERAL/tracks/trk_sct_hits",                      
        "run_356124/SCT/GENERAL/tracks/trk_pt",                      
    };

    const std::vector<std::string> plotsTP {       
        "run_356124/InDetGlobal/Track/trk_nIBLhits_LB",       
        "run_356124/InDetGlobal/Track/trk_nPIXhits_LB",       
        "run_356124/InDetGlobal/Track/trk_nSCThits_LB",       
        "run_356124/InDetGlobal/Track/trk_nTRThits_LB",       
        "run_356124/InDetGlobal/Track/Trk_noTRText_frac_LB",       
        "run_356124/InDetGlobal/Track/Trk_noTRText_LB",       
        "run_356124/InDetGlobal/Track/Trk_noIBLhits_LB",       
        "run_356124/InDetGlobal/Track/Trk_noIBLhits_frac_LB",       
        "run_356124/InDetGlobal/Track/Trk_noBLhits_frac_LB",       
        "run_356124/InDetGlobal/Track/Trk_noBLhits_LB",       

        "run_356124/InDetGlobal/Track/Trk_nBase_LB",       
        "run_356124/InDetGlobal/PrimaryVertex/pvN_LB",    
        "run_356124/Pixel/Clusters/Clusters_per_lumi",        
        "run_356124/Pixel/Clusters/Clusters_per_lumi_B0",        
        "run_356124/Pixel/Clusters/Clusters_per_lumi_B1",        
        "run_356124/Pixel/Clusters/Clusters_per_lumi_B2",        
        "run_356124/Pixel/Clusters/Clusters_per_lumi_ECA",        
        "run_356124/Pixel/Clusters/Clusters_per_lumi_ECC",        
        "run_356124/Pixel/Clusters/Clusters_per_lumi_IBL",    



        "run_356124/Pixel/ClustersOnTrack/num_clusters_per_track_per_lumi_IBL",        
        "run_356124/Pixel/ClustersOnTrack/num_clusters_per_track_per_lumi_ECC",        
        "run_356124/Pixel/ClustersOnTrack/num_clusters_per_track_per_lumi_ECA",        
        "run_356124/Pixel/ClustersOnTrack/num_clusters_per_track_per_lumi_B0",        
        "run_356124/Pixel/ClustersOnTrack/num_clusters_per_track_per_lumi_B1",        
        "run_356124/Pixel/ClustersOnTrack/num_clusters_per_track_per_lumi_B2",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack_B0",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack_B1",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack_B2",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack_ECA",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack_ECC",        
        "run_356124/Pixel/ClustersOnTrack/Clusters_per_lumi_OnTrack_IBL",       
        "run_356124/Pixel/TrackOnTrack/HitEff_all_B0",            
        "run_356124/Pixel/TrackOnTrack/HitEff_all_B1",            
        "run_356124/Pixel/TrackOnTrack/HitEff_all_B2",            
        "run_356124/Pixel/TrackOnTrack/HitEff_all_ECA",            
        "run_356124/Pixel/TrackOnTrack/HitEff_all_ECC",            
        "run_356124/Pixel/TrackOnTrack/HitEff_all_IBL",     

    };
    SetAtlasStyle();

    // here we define the "samples" to include in our plot, and how they should look. 
    // See NtupleAnalysisUtils/PlotFormat.h for available options. 
    std::vector<genericPlotDef> todo {
            genericPlotDef{ref, "Reference","PL", PlotFormat().MarkerStyle(kFullDotLarge).Color(kRed+1)},
            genericPlotDef{test_buggy, "Tuesday (broken IBL alignment)","PL", PlotFormat().MarkerStyle(kOpenTriangleDown).Color(kGreen-3)},
            genericPlotDef{test_n207, "Feb 07","PL", PlotFormat().MarkerStyle(kFullSquare).Color(kOrange-3)},
            genericPlotDef{test_n210, "Feb 10","PL", PlotFormat().MarkerStyle(kFullDiamond).Color(kBlue+1)},
    };

    // specify the look of our canvas 
    CanvasOptions opts = CanvasOptions().fontSize(10).legendStartX(0.3).ratioAxisTitle("Ratio"); 
    // specify file names 
    const std::string fileNameBase = "PhysValPlots/PlotOverlay_"; 
    const std::string fileNameMultiPage = "PhysValPlots/AllPhysValPlots"; 
    // and labels... 
    std::vector<std::string> labels {"Cookies"}; 
    // now book everything
    auto plots_1D = bookThem<TH1F>(plots1F, todo,labels,fileNameBase, fileNameMultiPage, opts); 
    auto plots_Prof = bookThem<TProfile>(plotsTP, todo,labels,fileNameBase, fileNameMultiPage, opts); 

    // and plot it
    PlotUtils::startMultiPagePdfFile(fileNameMultiPage); 
    for (auto & p : plots_1D){
        DefaultPlotting::draw1D(p);
    }
    for (auto & p : plots_Prof){
        DefaultPlotting::draw1D(p);
    }
    PlotUtils::endMultiPagePdfFile(fileNameMultiPage); 

    return 0;
}
