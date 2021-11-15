#include "IDPhysValPlotting/MuonMomentumSamples.h"
#include "IDPhysValPlotting/MuonMomentumHelpers.h"
#include "IDPhysValPlotting/ResoUtils.h"
#include <TVector2.h> 
#include <TProfile2D.h> 

using namespace MuonMomentumHelpers;
using namespace MuonMomentumSamples;


int main(){

    //////////////////////////////////////////////
    /// Book a few detector regions to make plots for. 
    /// Need a number as the reso depends strongly on pt and geometry... 
    //////////////////////////////////////////////
    std::vector<Region> regions{
        Region{
            "MCP0","0 < |#eta| < 0.4; 40 < p_{T} < 45 GeV", 40.,45.,0.,0.4
        },
        Region{
            "MCP1","0.8 < |#eta| < 1.05; 40 < p_{T} < 45 GeV", 40,45,0.8,1.05
        },
        Region{
            "MCP2","2.1 < |#eta| < 2.3; 40 < p_{T} < 45 GeV", 40.,45.,2.1,2.3
        },
        Region{
            "MCP3","2.3 < |#eta| < 2.5;40 < p_{T} < 45 GeV", 40.,45.,2.3,2.5
        },
        Region{
            "EtaScanm1","0.0 < |#eta| < 0.1;40 < p_{T} < 45 GeV", 40.,45.,0.0,0.1
        },
        Region{
            "EtaScan0","0.0 < |#eta| < 0.2;40 < p_{T} < 45 GeV", 40.,45.,0.0,0.2
        },
        Region{
            "EtaScan1","0.2 < |#eta| < 0.4;40 < p_{T} < 45 GeV", 40.,45.,0.2,0.4
        },
        Region{
            "EtaScan2","0.4 < |#eta| < 0.6;40 < p_{T} < 45 GeV", 40.,45.,0.4,0.6
        },
        Region{
            "EtaScan3","0.6 < |#eta| < 0.8;40 < p_{T} < 45 GeV", 40.,45.,0.6,0.8
        },
        Region{
            "EtaScan4","0.8 < |#eta| < 1.0;40 < p_{T} < 45 GeV", 40.,45.,0.8,1.0
        },
        Region{
            "EtaScan5","1.0 < |#eta| < 1.2;40 < p_{T} < 45 GeV", 40.,45.,1.0,1.2
        },
        Region{
            "EtaScan6","1.2 < |#eta| < 1.4;40 < p_{T} < 45 GeV", 40.,45.,1.2,1.4
        },
        Region{
            "EtaScan7","1.4 < |#eta| < 1.6;40 < p_{T} < 45 GeV", 40.,45.,1.4,1.6
        },
        Region{
            "EtaScan8","1.6 < |#eta| < 1.8;40 < p_{T} < 45 GeV", 40.,45.,1.6,1.8
        },
        Region{
            "EtaScan9","1.8 < |#eta| < 2;40 < p_{T} < 45 GeV", 40.,45.,1.8,2
        },
        Region{
            "EtaScan10","2.0 < |#eta| < 2.2;40 < p_{T} < 45 GeV", 40.,45.,2.0,2.2
        },
        Region{
            "EtaScan11","2.2 < |#eta| < 2.3;40 < p_{T} < 45 GeV", 40.,45.,2.2,2.3
        },
        Region{
            "EtaScan12","2.3 < |#eta| < 2.4;40 < p_{T} < 45 GeV", 40.,45.,2.3,2.4
        },
        Region{
            "EtaScan13","2.4 < |#eta| < 2.5;40 < p_{T} < 45 GeV", 40.,45.,2.4,2.5
        },
    };
    std::vector<Region> ResoRegions_eta{
        Region{
            "EtaScan0","0.0 < |#eta| < 0.2", 0.,999999.,0.0,0.2
        },
        Region{
            "EtaScan1","0.2 < |#eta| < 0.4", 0.,999999.,0.2,0.4
        },
        Region{
            "EtaScan2","0.4 < |#eta| < 0.6", 0.,999999.,0.4,0.6
        },
        Region{
            "EtaScan3","0.6 < |#eta| < 0.8", 0.,999999.,0.6,0.8
        },
        Region{
            "EtaScan4","0.8 < |#eta| < 1.0", 0.,999999.,0.8,1.0
        },
        Region{
            "EtaScan5","1.0 < |#eta| < 1.2", 0.,999999.,1.0,1.2
        },
        Region{
            "EtaScan6","1.2 < |#eta| < 1.4", 0.,999999.,1.2,1.4
        },
        Region{
            "EtaScan7","1.4 < |#eta| < 1.6", 0.,999999.,1.4,1.6
        },
        Region{
            "EtaScan8","1.6 < |#eta| < 1.8", 0.,999999.,1.6,1.8
        },
        Region{
            "EtaScan9","1.8 < |#eta| < 2", 0.,999999.,1.8,2
        },
        Region{
            "EtaScan10","2.0 < |#eta| < 2.2", 0.,999999.,2.0,2.2
        },
        Region{
            "EtaScan11","2.2 < |#eta| < 2.3", 0.,999999.,2.2,2.3
        },
        Region{
            "EtaScan12","2.3 < |#eta| < 2.4", 0.,999999.,2.3,2.4
        },
        Region{
            "EtaScan13","2.4 < |#eta| < 2.5", 0.,999999.,2.4,2.5
        },
    };
    std::vector<Region> ResoRegions_pt{
        Region{
            "PtBin0","5 GeV < p_{T} < 10 GeV", 5.,10.,0,2.5
        },
        Region{
            "PtBin1","10 GeV < p_{T} < 20 GeV", 10.,20.,0,2.5
        },
        Region{
            "PtBin2","20 GeV < p_{T} < 30 GeV", 20.,30.,0,2.5
        },
        Region{
            "PtBin3","30 GeV < p_{T} < 35 GeV", 30.,35.,0,2.5
        },
        Region{
            "PtBin4","35 GeV < p_{T} < 40 GeV", 35.,40.,0,2.5
        },
        Region{
            "PtBin5","40 GeV < p_{T} < 45 GeV", 40.,45.,0,2.5
        },
        Region{
            "PtBin6","45 GeV < p_{T} < 60 GeV", 45.,60.,0,2.5
        },
        Region{
            "PtBin7","60 GeV < p_{T} < 100 GeV", 60.,100.,0,2.5
        },
    };

    //////////////////////////////////////////////
    /// Book the input sample
    //////////////////////////////////////////////

    Selection<MuonMomentumCalibrationTreeExtended> sel_baseline([](MuonMomentumCalibrationTreeExtended &t){
        return (
            t.Pos_TruthPt() > 3 && t.Neg_TruthPt() > 3 && t.Pos_TruthPt()< 120 && t.Neg_TruthPt()< 120 && t.Neg_IsCBMuon()  && t.Pos_IsCBMuon()  && t.Pair_IsOppCharge() && ((t.Pair_CB_Mass() > 60 && t.Pair_CB_Mass() < 120) || (t.Pair_CB_Mass() > 2.9 && t.Pair_CB_Mass() < 3.5))
        );
    });

    // Sample<MuonMomentumCalibrationTreeExtended> MCP = getSample_Zmumu(sel_baseline,2); 
    // MCP.addFilesFrom(getSample_JPsi(sel_baseline, 2)); 

    Sample<MuonMomentumCalibrationTreeExtended> MCP = getSample_Data(sel_baseline, 7); 

    const std::string samplePrefix = "Data"; 
    const std::string sampleLabel = "Data"; 

    // const std::string samplePrefix = "Zmumu"; 
    // const std::string sampleLabel = "Z#rightarrow #mu#mu"; 

    //////////////////////////////////////////////
    /// Define the visuals of the histograms to be drawn. 
    //////////////////////////////////////////////

    PlotFormat pf_nominal = PlotFormat().Color(kBlack).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle(sampleLabel); 
    PlotFormat pf_ID_filled = PlotFormat().Color(kBlue-6).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("ID track"); 
    PlotFormat pf_ME_filled = PlotFormat().Color(kRed).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("ME track"); 
    PlotFormat pf_MS_filled = PlotFormat().Color(kViolet).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("MS track"); 
    PlotFormat pf_CB_filled = PlotFormat().Color(kOrange-3).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("CB track"); 

    PlotFormat pf_ID = PlotFormat().Color(kBlue-6).MarkerStyle(kFullDotLarge).LegendOption("PLHIST").LegendTitle("ID track"); 
    PlotFormat pf_ME = PlotFormat().Color(kRed).MarkerStyle(kFullDotLarge).LegendOption("PLHIST").LegendTitle("ME track"); 
    PlotFormat pf_MS = PlotFormat().Color(kViolet).MarkerStyle(kFullDotLarge).LegendOption("PLHIST").LegendTitle("MS track"); 
    PlotFormat pf_CB = PlotFormat().Color(kOrange-3).MarkerStyle(kFullDotLarge).LegendOption("PLHIST").LegendTitle("CB track"); 

    PlotFormat pf_CB_auxAll = PlotFormat().Color(kBlack).MarkerStyle(kFullDotLarge).FillStyle(1001).FillAlpha(0.4).LegendOption("PL").ExtraDrawOpts("PL").LegendTitle("CB - All Phi"); 
    PlotFormat pf_CB_aux3 = PlotFormat().Color(kViolet).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0").LegendTitle("CB - Phi Region C"); 
    PlotFormat pf_CB_aux2 = PlotFormat().Color(kRed).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0").LegendTitle("CB - Phi Region A"); 
    PlotFormat pf_CB_aux1 = PlotFormat().Color(kBlue).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0").LegendTitle("CB - Phi Region B"); 

    PlotFormat pf_CB_MeanCov = PlotFormat().Color(kOrange-3).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("Mean CB #sigma(q/p)"); 
    PlotFormat pf_ID_MeanCov = PlotFormat().Color(kBlue-6).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("Mean ID #sigma(q/p)"); 
    PlotFormat pf_ME_MeanCov = PlotFormat().Color(kRed).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("Mean ME #sigma(q/p)"); 
    PlotFormat pf_MS_MeanCov = PlotFormat().Color(kViolet).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("Mean MS #sigma(q/p)"); 
    
    PlotFormat pf_CB_Meas = PlotFormat().Color(kOrange-3).MarkerStyle(kFullDotLarge).LegendOption("PL").ExtraDrawOpts("PL)").LegendTitle("Measured CB res."); 
    PlotFormat pf_ID_Meas = PlotFormat().Color(kBlue).MarkerStyle(kFullDotLarge).LegendOption("PL").ExtraDrawOpts("PL").LegendTitle("Measured ID res."); 
    PlotFormat pf_ME_Meas = PlotFormat().Color(kRed+1).MarkerStyle(kFullDotLarge).LegendOption("PL").ExtraDrawOpts("PL").LegendTitle("Measured ME res."); 
    PlotFormat pf_MS_Meas = PlotFormat().Color(kViolet+1).MarkerStyle(kFullDotLarge).LegendOption("PL").ExtraDrawOpts("PL").LegendTitle("Measured MS res."); 


    //////////////////////////////////////////////
    /// Define the canvas-level options for visualisation
    //////////////////////////////////////////////
    CanvasOptions copt_err_1D = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2);
    copt_err_1D.YAxis.modify().Title("arbitrary units").TopPadding(0.42); 

    CanvasOptions copt_reso_1D = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2);
    copt_reso_1D.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.42); 

    CanvasOptions copt_pullWidth_1D = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2);
    copt_pullWidth_1D.YAxis.modify().Title("q/p pull width").Min(0.5).Max(1.8).Fixed(true);

    CanvasOptions copt_1Dcomp_res = CanvasOptions();
    copt_1Dcomp_res.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.32).Min(0); 

    CanvasOptions copt_1Dcomp_ratio = CanvasOptions();
    copt_1Dcomp_ratio.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.32).Min(0);
    copt_1Dcomp_ratio.RatioAxis.modify().Title("Fraction of total").Min(0).Max(1).Fixed(true).Symmetric(false); 

    CanvasOptions copt_err_2D_Eta = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_Eta.ZAxis.modify().Title("#sigma_{q/pT} / (q/p_{T})").Log(false).Min(0);

    CanvasOptions copt_err_2D_EtaPhi = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_EtaPhi.ZAxis.modify().Title("#sigma_{q/pT} / (q/p_{T})").Log(false).Min(0.01).Max(0.18).Fixed(true);

    CanvasOptions copt_err_2D_EtaPhi_CR = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_EtaPhi_CR.ZAxis.modify().Title("Ratio q<0 / q>0").Log(false).Min(0.6).Max(1.4).Fixed(true);

    //////////////////////////////////////////////
    /// Define the binnings of the histograms to be drawn. 
    /// Make sure to reserve sufficient granularity when running RMS evaluations! 
    //////////////////////////////////////////////

    std::vector<double> ptbins {5,15,25,35,40,45,60,100};
    int nptbins = ptbins.size() - 1;  
    std::vector<double> etabins {-2.5, -2, -1.5, -1.05, -0.8, -0.4, 0, 0.4, 0.8, 1.05, 1.5, 2, 2.5}; 
    int netabins = etabins.size() - 1; 

    TH1D href_pt_1D("pt","bla;pT",nptbins,&(ptbins[0])); 
    href_pt_1D.Sumw2();

    TH1D href_pull_1D("check1Dpterr","bla;#sigma_{q/pT} / (q/p_{T})",140,0.0,0.12); 
    href_pull_1D.Sumw2();

    TH1D href_pull_1D_cbOnly("href_pull_1D_cbOnly","bla;#sigma_{q/pT} / (q/p_{T})",120,0.01,0.06); 
    href_pull_1D_cbOnly.Sumw2();

    TH2D href_sigmaRel_2D_Pt("href_sigmaRel_2D_Pt","bla;p_{T} [GeV];#sigma_{q/pT} / (q/p_{T})",nptbins, &(ptbins[0]),400,0.0,0.12); 
    href_sigmaRel_2D_Pt.Sumw2();

    TH2D href_sigmaRel_2D_Eta("href_sigmaRel_2D_Eta","bla;|#eta|;#sigma_{q/pT} / (q/p_{T})",200,0,2.5,400,0.0,0.12); 
    href_sigmaRel_2D_Eta.Sumw2();

    TH2D href_sigmaRel_2D_Phi("href_sigmaRel_2D_Phi","bla;#phi;#sigma_{q/pT} / (q/p_{T})",300,-3.15,3.15,400,0.0,0.12); 
    href_sigmaRel_2D_Phi.Sumw2();

    TH2D href_sigmaRel_2D_PhiMP4("href_sigmaRel_2D_PhiMP4","bla;#phi mod. #pi/4;#sigma_{q/pT} / (q/p_{T})",300,0,pi_over4,400,0.0,0.12); 
    href_sigmaRel_2D_PhiMP4.Sumw2();

    TH2D href_pull_2D_Pt("href_pull_2D_Pt","bla;p_{T} [GeV];pull in q/p ",nptbins, &(ptbins[0]),1000,-5.,5.); 
    href_pull_2D_Pt.Sumw2();

    TH2D href_pull_2D_Eta("check2DpterrEta","bla;|#eta|;pull in q/p ",200,0,2.5,1000,-5.,5.); 
    href_pull_2D_Eta.Sumw2();

    TH2D href_pull_2D_Phi("check2DpterrPhi","bla;#phi;pull in q/p ",300,-3.15,3.15,1000,-5.,5.); 
    href_pull_2D_Phi.Sumw2();

    TH2D href_pull_2D_PhiMP4("check2DpterrPhiMP4","bla;#phi mod. #pi/4;pull in q/p ",300,0,pi_over4,1000,-5.,5.); 
    href_pull_2D_PhiMP4.Sumw2();

    TProfile2D href_prof2D_cov_etaphi("href_prof2D_cov_etaphi","bla;#eta;#phi;#sigma(q/p) / (q/p) ",800,-2.5,2.5,2000,-3.1415926, 3.1415926); 
    href_pull_2D_PhiMP4.Sumw2();

    // TProfile2D href_prof2D_cov_etaphi("href_prof2D_cov_etaphi","bla;#eta;#phi;#sigma(q/p) / (q/p) ",12,-2.5,2.5,12,-3.1415926, 3.1415926); 
    // href_pull_2D_PhiMP4.Sumw2();

    TH2D href_residual_2D_PhiMP4("href_residual_2D_PhiMP4","bla;#phi mod. #pi/4;Residual",200,0,pi_over4,1400,-0.7,0.7); 
    href_residual_2D_PhiMP4.Sumw2();

    TH2D href_residual_2D_Phi("href_residual_2D_Phi","bla;#phi;Residual",200,-3.15,3.15,1400,-0.7,0.7); 
    href_residual_2D_Phi.Sumw2();

    TH2D href_residual_2D_Eta("href_residual_2D_Eta","bla;|#eta|;Residual",200,0,2.5,1400,-0.7,0.7); 
    href_residual_2D_Eta.Sumw2();

    TH2D href_residual_2D_Pt("href_residual_2D_Pt","bla;p_{T} [GeV];Residual",nptbins,&(ptbins[0]),1400,-0.7,0.7); 
    href_residual_2D_Pt.Sumw2();

    TProfile href_residual_TP_PhiMP4("href_residual_TP_PhiMP4","bla;#phi mod. #pi/4;Residual",200,0,pi_over4); 
    href_residual_TP_PhiMP4.Sumw2();

    
    
    /// Book plot content vectors
    std::vector<PlotContent<TH2D>> do2D_Eta;
    std::vector<PlotContent<TH2D>> do2D_Phi;
    std::vector<PlotContent<TH1D>> do1D;
    std::vector<PlotContent<TH1D>> do1DRatio;


    /// Define phi-slices for the chamber-geometry dependence demo 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTest_Pos([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Pos_TruthPhi()) > 0.07 && phiModPi4(t.Pos_TruthPhi()) < 0.71); 
    }); 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTest_Neg([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Neg_TruthPhi()) > 0.07 && phiModPi4(t.Neg_TruthPhi()) < 0.71); 
    }); 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTestB_Pos([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Pos_TruthPhi()) > 0.24 && phiModPi4(t.Pos_TruthPhi()) < 0.54); 
    }); 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTestB_Neg([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Neg_TruthPhi()) > 0.24 && phiModPi4(t.Neg_TruthPhi()) < 0.54); 
    }); 

    ///////////////////////////////////////////////////////////////////////////////
    /// Ok, we have all ingredients - now we can systematically book all our histograms
    ///////////////////////////////////////////////////////////////////////////////

    /// Set up a multi page PDF output file to store everything 
    auto mpc = PlotUtils::startMultiPagePdfFile("MCPMomentumChecks_"+samplePrefix); 

    /// Loop over the eta-pt regions and book histograms 
    // for (auto & region : regions){

    //     /// One selection per leg - needed because the ntuple format is a bit inconvenient... 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_pos =  getPtWindow_Pos(region.ptMin,region.ptMax) && getAbsEtaWindow_Pos(region.etaMin, region.etaMax);  
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_neg =  getPtWindow_Neg(region.ptMin,region.ptMax) && getAbsEtaWindow_Neg(region.etaMin, region.etaMax);  

    //     /// Book 1D plots of the momentum error for each track. 
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D, MCP, sel_pos,
    //                             fillMomErrorRel_ID_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D, MCP, sel_neg,
    //                             fillMomErrorRel_ID_1D_Neg
    //                         },1),
    //                 pf_ID_filled},
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D, MCP, sel_pos,
    //                             fillMomErrorRel_ME_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D, MCP, sel_neg,
    //                             fillMomErrorRel_ME_1D_Neg
    //                         },1),
    //                 pf_ME_filled},
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D, MCP, sel_pos,
    //                             fillMomErrorRel_CB_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D, MCP, sel_neg,
    //                             fillMomErrorRel_CB_1D_Neg
    //                         },1),
    //                 pf_CB_filled},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_"+region.title,mpc, copt_err_1D
    //         }
    //     );
        
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_pos_aux1 = sel_pos && sel_phiAuxTest_Pos && sel_phiAuxTestB_Pos; 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_neg_aux1 = sel_neg && sel_phiAuxTest_Neg && sel_phiAuxTestB_Neg; 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_pos_aux2 = sel_pos && sel_phiAuxTest_Pos && !sel_phiAuxTestB_Pos; 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_neg_aux2 = sel_neg && sel_phiAuxTest_Neg && !sel_phiAuxTestB_Neg; 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_pos_aux3 = sel_pos && !sel_phiAuxTest_Pos; 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_neg_aux3 = sel_neg && !sel_phiAuxTest_Neg; 

    //     /// Book plots showing the composition of the CB error distribution in terms of chamber-level phi-regions
    //     do1DRatio.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP, sel_pos,
    //                             fillMomErrorRel_CB_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP, sel_neg,
    //                             fillMomErrorRel_CB_1D_Neg
    //                         },1),
    //                 pf_CB_auxAll},
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP,  sel_pos_aux1,
    //                             fillMomErrorRel_CB_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP,  sel_neg_aux1,
    //                             fillMomErrorRel_CB_1D_Neg
    //                         },1),
    //                 pf_CB_aux1},
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP,  sel_pos_aux2,
    //                             fillMomErrorRel_CB_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP,  sel_neg_aux2,
    //                             fillMomErrorRel_CB_1D_Neg
    //                         },1),
    //                 pf_CB_aux2},
    //                 Plot<TH1D>{
    //                     LinearCombination<TH1D>(  
    //                         RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP,  sel_pos_aux3,
    //                             fillMomErrorRel_CB_1D_Pos
    //                         }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
    //                             &href_pull_1D_cbOnly, MCP,  sel_neg_aux3,
    //                             fillMomErrorRel_CB_1D_Neg
    //                         },1),
    //                 pf_CB_aux3},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_"+samplePrefix+"_PhiSplitCheck"+region.title,mpc, copt_1Dcomp_ratio
    //         }
    //     );



    //     /// Book plots with the iterative RMS based resolution versus chamber-level phi
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhiMP4_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhiMP4_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhiMP4_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhiMP4_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhiMP4_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhiMP4_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_ResoVsPhiMP4"+region.title,mpc, copt_reso_1D
    //         }
    //     );
    //     /// Book plots with the iterative RMS based resolution versus phi
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Phi, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhi_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Phi, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhi_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Phi, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhi_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Phi, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhi_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Phi, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhi_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Phi, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhi_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_ResoVsPhi"+region.title,mpc, copt_reso_1D
    //         }
    //     );

    //     /// Book plots with the iterative RMS based pull width versus phi
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Phi, MCP, sel_pos,
    //                                 fillMomPullRel_vsPhi_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Phi, MCP, sel_neg,
    //                                 fillMomPullRel_vsPhi_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Phi, MCP, sel_pos,
    //                                 fillMomPullRel_vsPhi_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Phi, MCP, sel_neg,
    //                                 fillMomPullRel_vsPhi_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Phi, MCP, sel_pos,
    //                                 fillMomPullRel_vsPhi_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Phi, MCP, sel_neg,
    //                                 fillMomPullRel_vsPhi_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_PullWidthVsPhi"+region.title,mpc, copt_pullWidth_1D
    //         }
    //     );

    //     /// Book plots with the iterative RMS based pull width versus chamber-level phi
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomPullRel_vsPhiMP4_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomPullRel_vsPhiMP4_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomPullRel_vsPhiMP4_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomPullRel_vsPhiMP4_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomPullRel_vsPhiMP4_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomPullRel_vsPhiMP4_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_PullWidthVsPhiMP4"+region.title,mpc, copt_pullWidth_1D
    //         }
    //     );
        
    //     /// Book plots with comparing the mean q/p covariance error to the actual resolution for the ID track
    //     do1DRatio.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TProfile>(
    //                         LinearCombination<TProfile>(  
    //                             RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_TP_PhiMP4, MCP, sel_pos,
    //                                 fillMomErrorRel_ID_vsPhiMP4_Prof_Pos
    //                             }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_TP_PhiMP4, MCP, sel_neg,
    //                                 fillMomErrorRel_ID_vsPhiMP4_Prof_Neg
    //                             },1), 
    //                         ResoUtils::profToTH1), pf_ID_MeanCov},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhiMP4_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhiMP4_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID_Meas},
    //             },
    //             {sampleLabel, "ID Tracks", region.label}, "CheckMuonPt_"+samplePrefix+"_ID_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
    //         }
    //     );
    //     /// Book plots with comparing the mean q/p covariance error to the actual resolution for the ME track
    //     do1DRatio.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TProfile>(
    //                         LinearCombination<TProfile>(  
    //                             RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_TP_PhiMP4, MCP, sel_pos,
    //                                 fillMomErrorRel_ME_vsPhiMP4_Prof_Pos
    //                             }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_TP_PhiMP4, MCP, sel_neg,
    //                                 fillMomErrorRel_ME_vsPhiMP4_Prof_Neg
    //                             },1), 
    //                         ResoUtils::profToTH1), pf_ME_MeanCov},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhiMP4_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhiMP4_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME_Meas},
    //             },
    //             {sampleLabel, "ME Tracks", region.label}, "CheckMuonPt_"+samplePrefix+"_ME_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
    //         }
    //     );
    //     /// Book plots with comparing the mean q/p covariance error to the actual resolution for the CB track
    //     do1DRatio.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TProfile>(
    //                         LinearCombination<TProfile>(  
    //                             RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_TP_PhiMP4, MCP, sel_pos,
    //                                 fillMomErrorRel_CB_vsPhiMP4_Prof_Pos
    //                             }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_TP_PhiMP4, MCP, sel_neg,
    //                                 fillMomErrorRel_CB_vsPhiMP4_Prof_Neg
    //                             },1), 
    //                         ResoUtils::profToTH1), pf_CB_MeanCov},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPhiMP4_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPhiMP4_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB_Meas},
    //             },
    //             {sampleLabel, "CB Tracks", region.label}, "CheckMuonPt_"+samplePrefix+"_CB_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
    //         }
    //     );

    //     /// Book 2D plots showing the actual distribution of the momentum error in bins of phi 
    //     do2D_Phi.push_back(
    //         PlotContent<TH2D>{
    //             {
    //                 Plot<TH2D>{
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                                 fillMomErrorRel_ID_vsPhi_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                                 fillMomErrorRel_ID_vsPhi_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_ID},
    //                 Plot<TH2D>{
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                                 fillMomErrorRel_ME_vsPhi_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                                 fillMomErrorRel_ME_vsPhi_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_ME},
    //                 // Plot<TH2D>{
    //                 //     GenericPostProcessing<TH2D,TH2D>(
    //                 //         LinearCombination<TH2D>(  
    //                 //             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                 //                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                 //                 fillMomErrorRel_MS_vsPhi_2D_Pos
    //                 //             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                 //                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                 //                 fillMomErrorRel_MS_vsPhi_2D_Neg
    //                 //             },1),normaliseInBin),
    //                 // pf_MS},
    //                 Plot<TH2D>{
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                                 fillMomErrorRel_CB_vsPhi_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                                 fillMomErrorRel_CB_vsPhi_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_Phi2D_"+region.title,mpc, copt_err_2D_Eta
    //         }
    //     );

    //     /// Book 2D plots showing the actual distribution of the momentum error in bins of phi 
    //     do2D_Phi.push_back(
    //         PlotContent<TH2D>{
    //             {
    //                 Plot<TH2D>{
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                                 fillMomErrorRel_ID_vsPhi_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                                 fillMomErrorRel_ID_vsPhi_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_ID},
    //                 Plot<TH2D>{
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                                 fillMomErrorRel_ME_vsPhi_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                                 fillMomErrorRel_ME_vsPhi_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_ME},
    //                 // Plot<TH2D>{
    //                 //     GenericPostProcessing<TH2D,TH2D>(
    //                 //         LinearCombination<TH2D>(  
    //                 //             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                 //                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                 //                 fillMomErrorRel_MS_vsPhi_2D_Pos
    //                 //             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                 //                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                 //                 fillMomErrorRel_MS_vsPhi_2D_Neg
    //                 //             },1),normaliseInBin),
    //                 // pf_MS},
    //                 Plot<TH2D>{
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_pos,
    //                                 fillMomErrorRel_CB_vsPhi_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_Phi, MCP, sel_neg,
    //                                 fillMomErrorRel_CB_vsPhi_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_Phi2D_"+region.title,mpc, copt_err_2D_Eta
    //         }
    //     );
        
    //     /// Book 2D plots showing the actual distribution of the momentum error in bins of chamber-level phi 
    //     do2D_Phi.push_back(
    //         PlotContent<TH2D>{
    //             {
    //                 Plot<TH2D>{
                        
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                             LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomErrorRel_ID_vsPhiMP4_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomErrorRel_ID_vsPhiMP4_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_ID},
    //                 Plot<TH2D>{
                        
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                             LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomErrorRel_ME_vsPhiMP4_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomErrorRel_ME_vsPhiMP4_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_ME},
    //                 // Plot<TH2D>{
                        
    //                 //     GenericPostProcessing<TH2D,TH2D>(
    //                 //             LinearCombination<TH2D>(  
    //                 //             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                 //                 &href_sigmaRel_2D_PhiMP4, MCP, sel_pos,
    //                 //                 fillMomErrorRel_MS_vsPhiMP4_2D_Pos
    //                 //             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                 //                 &href_sigmaRel_2D_PhiMP4, MCP, sel_neg,
    //                 //                 fillMomErrorRel_MS_vsPhiMP4_2D_Neg
    //                 //             },1),normaliseInBin),
    //                 // pf_MS},
    //                 Plot<TH2D>{
                        
    //                     GenericPostProcessing<TH2D,TH2D>(
    //                             LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_PhiMP4, MCP, sel_pos,
    //                                 fillMomErrorRel_CB_vsPhiMP4_2D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_sigmaRel_2D_PhiMP4, MCP, sel_neg,
    //                                 fillMomErrorRel_CB_vsPhiMP4_2D_Neg
    //                             },1),normaliseInBin),
    //                 pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_PhiMP4_2D_"+region.title,mpc, copt_err_2D_Eta
    //         }
    //     );
    // }
    

    /// Loop over our pt bins and book plots versus eta 

    for (auto & region : ResoRegions_pt){

        /// One selection per leg - needed because the ntuple format is a bit inconvenient... 
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos =  getPtWindow_Pos(region.ptMin,region.ptMax);  
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg =  getPtWindow_Neg(region.ptMin,region.ptMax);  
        
        // /// Book plots with the iterative RMS based pull width versus eta
        // do1D.push_back(
        //     PlotContent<TH1D>{
        //         {
        //             Plot<TH1D>{
        //                 GenericPostProcessing<TH1D,TH2D>(
        //                     LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_pull_2D_Eta, MCP, sel_pos,
        //                             fillMomPullRel_vsEta_ID_1D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_pull_2D_Eta, MCP, sel_neg,
        //                             fillMomPullRel_vsEta_ID_1D_Neg
        //                         },1), 
        //                     ResoUtils::getIterRMS), pf_ID},
        //             Plot<TH1D>{
        //                 GenericPostProcessing<TH1D,TH2D>(
        //                     LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_pull_2D_Eta, MCP, sel_pos,
        //                             fillMomPullRel_vsEta_ME_1D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_pull_2D_Eta, MCP, sel_neg,
        //                             fillMomPullRel_vsEta_ME_1D_Neg
        //                         },1), 
        //                     ResoUtils::getIterRMS), pf_ME},
        //             Plot<TH1D>{
        //                 GenericPostProcessing<TH1D,TH2D>(
        //                     LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_pull_2D_Eta, MCP, sel_pos,
        //                             fillMomPullRel_vsEta_CB_1D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_pull_2D_Eta, MCP, sel_neg,
        //                             fillMomPullRel_vsEta_CB_1D_Neg
        //                         },1), 
        //                     ResoUtils::getIterRMS), pf_CB},
        //         },
        //         {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_PullWidthVsEta"+region.title,mpc, copt_pullWidth_1D
        //     }
        // );
        // /// Book plots with the iterative RMS based resolution versus eta
        // do1D.push_back(
        //     PlotContent<TH1D>{
        //         {
        //             Plot<TH1D>{
        //                 GenericPostProcessing<TH1D,TH2D>(
        //                     LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_residual_2D_Eta, MCP, sel_pos,
        //                             fillMomResidualRel_vsEta_ID_1D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_residual_2D_Eta, MCP, sel_neg,
        //                             fillMomResidualRel_vsEta_ID_1D_Neg
        //                         },1), 
        //                     ResoUtils::getIterRMS), pf_ID},
        //             Plot<TH1D>{
        //                 GenericPostProcessing<TH1D,TH2D>(
        //                     LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_residual_2D_Eta, MCP, sel_pos,
        //                             fillMomResidualRel_vsEta_ME_1D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_residual_2D_Eta, MCP, sel_neg,
        //                             fillMomResidualRel_vsEta_ME_1D_Neg
        //                         },1), 
        //                     ResoUtils::getIterRMS), pf_ME},
        //             Plot<TH1D>{
        //                 GenericPostProcessing<TH1D,TH2D>(
        //                     LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_residual_2D_Eta, MCP, sel_pos,
        //                             fillMomResidualRel_vsEta_CB_1D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_residual_2D_Eta, MCP, sel_neg,
        //                             fillMomResidualRel_vsEta_CB_1D_Neg
        //                         },1), 
        //                     ResoUtils::getIterRMS), pf_CB},
        //         },
        //         {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_ResoVsEta"+region.title,mpc, copt_reso_1D
        //     }
        // );


        // /// Book 2D plots showing the actual distribution of the momentum error in bins of eta
        // do2D_Eta.push_back(
        //     PlotContent<TH2D>{  
        //         {
        //             Plot<TH2D>{
                        
        //                     GenericPostProcessing<TH2D,TH2D>(
        //                             LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_sigmaRel_2D_Eta, MCP,sel_pos,
        //                             fillMomErrorRel_ID_vsEta_2D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_sigmaRel_2D_Eta, MCP, sel_neg,
        //                             fillMomErrorRel_ID_vsEta_2D_Neg
        //                     },1),normaliseInBin),
        //             pf_ID},
        //             Plot<TH2D>{
                        
        //                     GenericPostProcessing<TH2D,TH2D>(
        //                             LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_sigmaRel_2D_Eta, MCP,sel_pos,
        //                             fillMomErrorRel_ME_vsEta_2D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_sigmaRel_2D_Eta, MCP, sel_neg,
        //                             fillMomErrorRel_ME_vsEta_2D_Neg
        //                     },1),normaliseInBin),
        //             pf_ME},
        //             Plot<TH2D>{
                        
        //                     GenericPostProcessing<TH2D,TH2D>(
        //                             LinearCombination<TH2D>(  
        //                         RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_sigmaRel_2D_Eta, MCP,sel_pos,
        //                             fillMomErrorRel_CB_vsEta_2D_Pos
        //                         }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
        //                             &href_sigmaRel_2D_Eta, MCP, sel_neg,
        //                             fillMomErrorRel_CB_vsEta_2D_Neg
        //                     },1),normaliseInBin),
        //             pf_CB},
        //         },
        //         {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_vsEta_"+region.title,mpc, copt_err_2D_Eta
        //     }
        // );


        /// Book 2D plots showing the actual distribution of the momentum error in bins of eta
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        
                            GenericPostProcessing<TH2D,TProfile2D>(
                                    LinearCombination<TProfile2D>(  
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP,sel_pos,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP, sel_neg,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Neg
                            },1),ProftoTH2D),
                    pf_ME},
                },
                {sampleLabel, region.label}, "CheckMuonCov_"+samplePrefix+"_vsEtaPhi2D_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP, sel_neg,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Neg
                            },ProftoTH2D),
                    pf_ME},
                },
                {sampleLabel,"q < 0", region.label}, "CheckMuonCov_"+samplePrefix+"_vsEtaPhi2D_muMinus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP, sel_pos,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Pos
                            },ProftoTH2D),
                    pf_ME},
                },
                {sampleLabel,"q > 0", region.label}, "CheckMuonCov_"+samplePrefix+"_vsEtaPhi2D_muPlus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MCP, sel_neg,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Neg
                                },ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MCP, sel_pos,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                },ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ME},
                },
                {sampleLabel,"Reso. Ratio q<0 / q>0", region.label}, "CheckMuonCov_"+samplePrefix+"_vsEtaPhi2D_ChargeRatio_"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );


        /// and for the ID 

        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        
                            GenericPostProcessing<TH2D,TProfile2D>(
                                    LinearCombination<TProfile2D>(  
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP,sel_pos,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP, sel_neg,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Neg
                            },1),ProftoTH2D),
                    pf_ID},
                },
                {sampleLabel, region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP, sel_neg,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Neg
                            },ProftoTH2D),
                    pf_ID},
                },
                {sampleLabel,"q < 0", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_muMinus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MCP, sel_pos,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Pos
                            },ProftoTH2D),
                    pf_ID},
                },
                {sampleLabel,"q > 0", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_muPlus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D_Eta.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MCP, sel_neg,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Neg
                                },ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MCP, sel_pos,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                },ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ID},
                },
                {sampleLabel,"Reso. Ratio q<0 / q>0", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_ChargeRatio_"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );




    }

    
    /// Loop over our eta bins and book plots versus pt 

    // for (auto & region : ResoRegions_eta){

    //     /// One selection per leg - needed because the ntuple format is a bit inconvenient... 
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_pos =  getAbsEtaWindow_Pos(region.etaMin,region.etaMax);  
    //     Selection <MuonMomentumCalibrationTreeExtended> sel_neg =  getAbsEtaWindow_Neg(region.etaMin,region.etaMax);  
        
    //     /// Book plots with the iterative RMS based pull width versus pt
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Pt, MCP, sel_pos,
    //                                 fillMomPullRel_vsPt_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Pt, MCP, sel_neg,
    //                                 fillMomPullRel_vsPt_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Pt, MCP, sel_pos,
    //                                 fillMomPullRel_vsPt_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Pt, MCP, sel_neg,
    //                                 fillMomPullRel_vsPt_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Pt, MCP, sel_pos,
    //                                 fillMomPullRel_vsPt_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_pull_2D_Pt, MCP, sel_neg,
    //                                 fillMomPullRel_vsPt_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_PullWidthVsPt"+region.title,mpc, copt_pullWidth_1D
    //         }
    //     );
    //     /// Book plots with the iterative RMS based resolution versus pt
    //     do1D.push_back(
    //         PlotContent<TH1D>{
    //             {
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Pt, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPt_ID_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Pt, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPt_ID_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ID},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Pt, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPt_ME_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Pt, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPt_ME_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_ME},
    //                 Plot<TH1D>{
    //                     GenericPostProcessing<TH1D,TH2D>(
    //                         LinearCombination<TH2D>(  
    //                             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Pt, MCP, sel_pos,
    //                                 fillMomResidualRel_vsPt_CB_1D_Pos
    //                             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
    //                                 &href_residual_2D_Pt, MCP, sel_neg,
    //                                 fillMomResidualRel_vsPt_CB_1D_Neg
    //                             },1), 
    //                         ResoUtils::getIterRMS), pf_CB},
    //             },
    //             {sampleLabel, region.label}, "CheckMuonPt_"+samplePrefix+"_ResoVsPt"+region.title,mpc, copt_reso_1D
    //         }
    //     );
    // }


    /// Now, fill the histograms and draw them! 

    DefaultPlotting::draw1DNoRatio(do1D); 
    DefaultPlotting::draw1D(do1DRatio); 
    drawReso2D(do2D_Eta, do2D_Phi); 

    return 0;
}