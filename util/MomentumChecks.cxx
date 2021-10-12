#include "IDPhysValPlotting/TruthRecoNtuple.h"
#include "IDPhysValPlotting/MuonMomentumCalibrationTreeExtended.h"
#include "IDPhysValPlotting/ResoUtils.h"

Selection<TruthRecoNtuple> getPtWindow(double lo, double hi){
    return Selection<TruthRecoNtuple>([hi,lo](TruthRecoNtuple& t){ return (t.truth_pt() > 1000. * lo && t.truth_pt() < 1000.*hi);}); 
}
Selection<TruthRecoNtuple> getAbsEtaWindow(double lo, double hi){
    return Selection<TruthRecoNtuple>([hi,lo](TruthRecoNtuple& t){ return (std::abs(t.truth_eta()) >  lo && std::abs(t.truth_eta()) < hi);}); 
}

void fillMomErrorRel_ID_1D(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP(), t.EventWeight()); 
    h->Fill(t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP(), t.EventWeight()); 
}
void fillMomErrorRel_ME_1D(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP(), t.EventWeight()); 
    h->Fill(t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP(), t.EventWeight()); 
}
void fillMomErrorRel_CB_1D(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP(), t.EventWeight()); 
    h->Fill(t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP(), t.EventWeight()); 
}

int main(){

    Selection<TruthRecoNtuple> forMomentum(
        [](TruthRecoNtuple & t){
            return t.hasTrack() && t.hasTruth() && t.track_truthMatchProb() > 0.5 && t.track_truthMatchRanking() == 0; 
        }
    );

    // Selection<TruthRecoNtuple> noExt(
    //     [](TruthRecoNtuple &t){
    //         return (t.hasTrack() && !(t.track_patternInfo() & (0x1 << 3))); 
    //     }
    // ); 

    Selection<TruthRecoNtuple> ptWindow_3_15 = getPtWindow(3,15); 
    Selection<TruthRecoNtuple> ptWindow_10_25 = getPtWindow(10,25);
    Selection<TruthRecoNtuple> ptWindow_15_25 = getPtWindow(15,25);
    Selection<TruthRecoNtuple> ptWindow_25_35 = getPtWindow(25,35);  
    Selection<TruthRecoNtuple> ptWindow_30_45 = getPtWindow(30,45);  
    Selection<TruthRecoNtuple> ptWindow_35_40 = getPtWindow(35,40);  
    Selection<TruthRecoNtuple> ptWindow_35_45 = getPtWindow(35,45);  
    Selection<TruthRecoNtuple> ptWindow_45_55 = getPtWindow(45,55);
    Selection<TruthRecoNtuple> ptWindow_55_65 = getPtWindow(55,65);
    Selection<TruthRecoNtuple> ptWindow_50_60 = getPtWindow(50,60); 


    Selection<TruthRecoNtuple> etaCrack1 = getAbsEtaWindow(0,0.1); 
    Selection<TruthRecoNtuple> etaCrack2 = getAbsEtaWindow(0.1,0.3); 
    Selection<TruthRecoNtuple> etaCentral = getAbsEtaWindow(0,0.7); 
    Selection<TruthRecoNtuple> etaTrans = getAbsEtaWindow(0.7,1.6); 
    Selection<TruthRecoNtuple> etaEC = getAbsEtaWindow(1.6,2); 
    Selection<TruthRecoNtuple> etaPostTRT = getAbsEtaWindow(2,2.5); 

    Selection<TruthRecoNtuple> chkEtaMCP_0 = getAbsEtaWindow(0,0.4);
    Selection<TruthRecoNtuple> chkEtaMCP_1 = getAbsEtaWindow(0.8,1.05);
    Selection<TruthRecoNtuple> chkEtaMCP_2 = getAbsEtaWindow(2.1,2.3);
    Selection<TruthRecoNtuple> chkEtaMCP_3 = getAbsEtaWindow(2.3,2.5);
    Selection<TruthRecoNtuple> chkEta = getAbsEtaWindow(2.1,2.3);


    Sample<TruthRecoNtuple> R20 {"/scratch/Datasets/Tracking/IDPVM/SglMu_20_nominal_pt20.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco",ptWindow_15_25}; 
    Sample<TruthRecoNtuple> withTRT {"/scratch/Datasets/Tracking/IDPVM/SglMu_21_nominal.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 
    Sample<TruthRecoNtuple> withTRT_master {"/scratch/Datasets/Tracking/IDPVM/SglMu_master_nominal.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 
    Sample<TruthRecoNtuple> noTRT {"/scratch/Datasets/Tracking/IDPVM/SglMu_21_noTRT.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 
    Sample<TruthRecoNtuple> noBL_master {"/scratch/Datasets/Tracking/IDPVM/SglMu_master_noBL.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 


    Sample<TruthRecoNtuple> noBL_ttbar_master {"/scratch/Datasets/Tracking/IDPVM/BLayerOff/ttbar_mu0/IDPVM.master.noDeadBL.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 
    Sample<TruthRecoNtuple> nominal_ttbar_master {"/scratch/Datasets/Tracking/IDPVM/BLayerOff/ttbar_mu0/IDPVM.master.withDeadBL.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 

    PlotFormat pf_R20 = PlotFormat().Color(kGreen+2).MarkerStyle(kOpenCrossX).LegendOption("PL").LegendTitle("Release 20.7, p_{T}==20 GeV"); 
    PlotFormat pf_withTRT = PlotFormat().Color(kGray+3).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("Nominal, with TRT"); 
    // PlotFormat pf_noExt = PlotFormat().Color(kRed).MarkerStyle(kOpenCircle).LegendOption("PL").LegendTitle("Nominal - non-extended"); 
    PlotFormat pf_noTRT = PlotFormat().Color(kBlue).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("TRT ext. disabled"); 
    PlotFormat pf_master = PlotFormat().Color(kViolet+2).MarkerStyle(kOpenDoubleDiamond).LegendOption("PL").LegendTitle("Release 22, nominal"); 

    // std::vector<double> truthBins{5,10,15,20,25,9,12,15,
    PlotFillInstructionWithRef<TH2D,TruthRecoNtuple> fill_pullWidth_vs_pt ([](TH2D* h, TruthRecoNtuple &t){h->Fill(t.track_pt()/1000., (t.track_qOverPt() - t.truth_qOverPt())/t.trackErr_qOverPt());}, "check2D", "check2D;p_{T} [GeV];pull",19,5,100,2000,-8,8);

    PlotFillInstructionWithRef<TH2D,TruthRecoNtuple> fill_pullWidth_vs_eta ([](TH2D* h, TruthRecoNtuple &t){h->Fill(std::abs(t.track_eta()), (t.track_qOverPt() - t.truth_qOverPt())/t.trackErr_qOverPt());}, "check2D2", "check2D;|#eta|;pull",40,0,2.5,2000,-8,8);

    PlotFillInstructionWithRef<TH2D,TruthRecoNtuple> fill_pullWidth_vs_phi ([](TH2D* h, TruthRecoNtuple &t){h->Fill(t.track_phi(), (t.track_qOverPt() - t.truth_qOverPt())/t.trackErr_qOverPt());}, "check2D3", "check2D;#phi;pull",64,-3.142,3.142,2000,-8,8);

    std::vector<double> ptbins {5,15,25,35,45,60,80,100};
    int nptbins = ptbins.size() - 1;  
    std::vector<double> etabins {-2.5, -2, -1.5, -1.05, -0.8, -0.4, 0, 0.4, 0.8, 1.05, 1.5, 2, 2.5}; 
    int netabins = etabins.size() - 1; 
    std::vector<double> resobins = PlotUtils::getLinearBinning(-2,2,20000); 
    int nresobins = resobins.size() - 1; 
    std::vector<double> resobinsD0 = PlotUtils::getLinearBinning(-40,40,400000); 
    int nresobinsD0 = resobinsD0.size() - 1; 
    PlotFillInstructionWithRef<TH3D,TruthRecoNtuple> fill_Reso_vs_etaPt ([](TH3D* h, TruthRecoNtuple &t){h->Fill(0.001* t.truth_pt(), t.truth_eta(), (t.track_qOverPt() - t.truth_qOverPt()) /t.truth_charge() * t.truth_pt());}, "check2Detapt", "check3D;p_{T, true} [GeV]; |#eta_{true}|;Resolution",nptbins, &(ptbins[0]),netabins,&(etabins[0]),nresobins,&(resobins[0]));
    PlotFillInstructionWithRef<TH3D,TruthRecoNtuple> fill_D0Reso_vs_etaPt ([](TH3D* h, TruthRecoNtuple &t){h->Fill(0.001* t.truth_pt(), t.truth_eta(), t.track_d0() - t.truth_d0());}, "check2DetaptD0", "check3D;p_{T, true} [GeV]; |#eta_{true}|;Resolution",nptbins, &(ptbins[0]),netabins,&(etabins[0]),nresobinsD0,&(resobinsD0[0]));
    PlotFillInstructionWithRef<TH3D,TruthRecoNtuple> fill_Z0Reso_vs_etaPt ([](TH3D* h, TruthRecoNtuple &t){h->Fill(0.001* t.truth_pt(), t.truth_eta(), t.track_z0() - t.truth_z0());}, "check2DetaptZ0", "check3D;p_{T, true} [GeV]; |#eta_{true}|;Resolution",nptbins, &(ptbins[0]),netabins,&(etabins[0]),nresobinsD0,&(resobinsD0[0]));

    PlotFillInstructionWithRef<TH2D, TruthRecoNtuple> fill_err_vs_pt([](TH2D* h, TruthRecoNtuple & t){
        h->Fill(t.truth_pt()*0.001, t.trackErr_qOverPt()/t.truth_qOverPt()); 
    }, "check2Dpterrpt","bla;p_{T} [GeV];#sigma_{q/pT} / (q/p_{T})",40,5,100,400,0,0.10); 

    PlotFillInstructionWithRef<TH2D, TruthRecoNtuple> fill_err_vs_eta([](TH2D* h, TruthRecoNtuple & t){
        h->Fill(std::abs(t.truth_eta()), t.trackErr_qOverPt()/t.truth_qOverPt()); 
    }, "check2Dpterreta","bla;|#eta|;#sigma_{q/pT} / (q/p_{T})",40,0,2.5,400,0,0.10); 

    PlotFillInstructionWithRef<TH2D, TruthRecoNtuple> fill_err_vs_phi([](TH2D* h, TruthRecoNtuple & t){
        h->Fill(t.truth_phi(), t.trackErr_qOverPt()/t.truth_qOverPt()); 
    }, "check2Dpterrphi","bla;#phi;#sigma_{q/pT} / (q/p_{T})",40,-3.142,3.142,400,0,0.10); 

    TH1D href_pull_1D("check1Dpterr","bla;#sigma_{q/pT} / (q/p_{T})",70,0.0,0.15); 
    href_pull_1D.Sumw2();
    PlotFillInstructionWithRef<TH1D, TruthRecoNtuple> fill_err_1D([](TH1D* h, TruthRecoNtuple & t){
        h->Fill(t.trackErr_qOverPt() / t.track_qOverPt(),1.00f); 
    }, &href_pull_1D) ; 
    
    CanvasOptions canOpt_1D = CanvasOptions(); 
    canOpt_1D.YAxis.modify().TopPadding(0.5).Symmetric(true).SymmetrisationPoint(1.0).Title("q/p_{T} pull width"); 
    canOpt_1D.RatioAxis.modify().TopPadding(0.2).Max(1).BottomPadding(0.2).Symmetric(false).Title("ratio w.r.t nominal"); 

    auto mpc = PlotUtils::startMultiPagePdfFile("SingleMuonResoChecks");

    PlotFormat pf_all = PlotFormat().Color(kBlack).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("Full detector"); 
    PlotFormat pf_Central = PlotFormat().Color(kBlue-3).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.3).LineWidth(2).LegendOption("FL").LegendTitle("|#eta| < 0.7").ExtraDrawOpts("HISTE0"); 
    PlotFormat pf_Trans = PlotFormat().Color(kRed).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.3).LineWidth(2).LegendOption("FL").LegendTitle("0.7 < |#eta| < 1.6").ExtraDrawOpts("HISTE0"); 
    PlotFormat pf_EC = PlotFormat().Color(kOrange-3).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.3).LineWidth(2).LegendOption("FL").LegendTitle("1.6 < |#eta| < 2 ").ExtraDrawOpts("HISTE0"); 
    PlotFormat pf_PostTRT = PlotFormat().Color(kViolet+1).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.3).LineWidth(2).LegendOption("FL").LegendTitle("2.0 < |#eta|").ExtraDrawOpts("HISTE0"); 

    CanvasOptions copt_oneDimCov = canOpt_1D; 
    copt_oneDimCov.YAxis.modify().Symmetric(false).Min(0).TopPadding(0.5).Title("arbitrary units");
    copt_oneDimCov.RatioAxis.modify().Title("Fraction of total").Max(1.00).Min(0.).Fixed(true); 

    PlotFormat pf_noTRT_aux = PlotFormat().Color(kBlue).MarkerStyle(kDot).LineStyle(kDotted).LegendOption("L").ExtraDrawOpts("HISTE0").LegendTitle("TRT ext. disabled"); 

    CanvasOptions copt_oneDimCov_singleplot = copt_oneDimCov; 
    copt_oneDimCov_singleplot.YAxis.modify().Symmetric(false).Min(0).TopPadding(0.7).Title("arbitrary units");
    copt_oneDimCov_singleplot.LegendStartY(-0.12).OtherLabelStepY(0.03).OtherLabelStartY(-0.1);


    std::vector<PlotContent<TH1D>> oneDimCov{
        
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_45, fill_err_1D), pf_all), 
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_45 && etaCentral, fill_err_1D), pf_Central), 
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_45 && etaTrans, fill_err_1D), pf_Trans), 
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_45 && (etaEC ), fill_err_1D), pf_EC), 
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_45 && etaPostTRT, fill_err_1D), pf_PostTRT), 

                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noExt), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noTRT), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 30...45 GeV, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices",mpc,copt_oneDimCov
        },

    };
    // Selection<TruthRecoNtuple> chkEtaMCP_0 = getAbsEtaWindow(0,0.4);
    // Selection<TruthRecoNtuple> chkEtaMCP_1 = getAbsEtaWindow(0.8,1.05);
    // Selection<TruthRecoNtuple> chkEtaMCP_2 = getAbsEtaWindow(2.1,2.3);
    // Selection<TruthRecoNtuple> chkEtaMCP_3 = getAbsEtaWindow(2.3,2.5);

    std::vector<PlotContent<TH1D>> oneDimCovSplit{
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_50_60 && chkEtaMCP_0, fill_err_1D), pf_withTRT),   
            },
            {"Single #mu, p_{T} #in 50...60 GeV, 0 < |#eta|<0.4, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP1",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_50_60 && chkEtaMCP_0, fill_err_1D), pf_withTRT),  
                Plot<TH1D>(RunHistoFiller(noTRT, forMomentum && ptWindow_50_60 && chkEtaMCP_0, fill_err_1D), pf_noTRT_aux),  
            },
            {"Single #mu, p_{T} #in 50...60 GeV, 0 < |#eta|<0.4, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP1",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_40 && chkEtaMCP_1, fill_err_1D), pf_withTRT),  
            },
            {"Single #mu, p_{T} #in 35...40 GeV, 0.8 < |#eta|<1.05, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP2",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_40 && chkEtaMCP_1, fill_err_1D), pf_withTRT),  
                Plot<TH1D>(RunHistoFiller(noTRT, forMomentum && ptWindow_35_40 && chkEtaMCP_1, fill_err_1D), pf_noTRT_aux),  
            },
            {"Single #mu, p_{T} #in 35...40 GeV, 0.8 < |#eta|<1.05, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP2",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_10_25 && chkEtaMCP_2, fill_err_1D), pf_withTRT),  
            },
            {"Single #mu, p_{T} #in 10...25 GeV, 2.1 < |#eta|<2.3, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP3",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_10_25 && chkEtaMCP_2, fill_err_1D), pf_withTRT), 
                Plot<TH1D>(RunHistoFiller(noTRT, forMomentum && ptWindow_10_25 && chkEtaMCP_2, fill_err_1D), pf_noTRT_aux),  
            },
            {"Single #mu, p_{T} #in 10...25 GeV, 2.1 < |#eta|<2.3, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP3",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_40 && chkEtaMCP_3, fill_err_1D), pf_withTRT),  
            },
            {"Single #mu, p_{T} #in 35...40 GeV, 2.3 < |#eta|<2.5, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP4",mpc,copt_oneDimCov_singleplot
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_40 && chkEtaMCP_3, fill_err_1D), pf_withTRT),  
                Plot<TH1D>(RunHistoFiller(noTRT, forMomentum && ptWindow_35_40 && chkEtaMCP_3, fill_err_1D), pf_noTRT_aux),  
            },
            {"Single #mu, p_{T} #in 35...40 GeV, 2.3 < |#eta|<2.5, <#mu>=0","21.0.77", "Inner Detector resolution" },"CheckMomErr_etaSlices_MCP4",mpc,copt_oneDimCov_singleplot
        },

    };

    std::vector<PlotContent<TH1D>> testIt{ 
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack1, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && etaCrack1, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack1, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCrack1, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && etaCrack1, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, |#eta| < 0.1, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_Crack1",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack2, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && etaCrack2, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack2, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCrack2, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && etaCrack2, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 0.1 < |#eta| < 0.3, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_Crack2",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaCentral, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && etaCentral, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaCentral, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCentral, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && etaCentral, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, |#eta| < 0.7, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_central",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaTrans, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && etaTrans, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaTrans, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaTrans, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && etaTrans, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 0.7 < |#eta| < 1.6, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_trans",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaEC, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && etaEC, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaEC, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaEC, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && etaEC, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 1.6 < |#eta| < 2.0, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_EC",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaPostTRT, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && etaPostTRT, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaPostTRT, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaPostTRT, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_master), 
                // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && etaPostTRT, fill_pullWidth_vs_pt),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 2.0 < |#eta| < 2.5, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_postTRT",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_3_15, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_3_15, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_3_15, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_3_15, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 3...15 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_3_15",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_15_25, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_15_25, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_15_25, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_15_25, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_master), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && ptWindow_15_25, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 15...25 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_15_25",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_25_35, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_25_35, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_25_35, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_25_35, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 25...35 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_25_35",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_45, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_35_45, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_35_45, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_35_45, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 35...45 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_35_45",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_45_55, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_45_55, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_45_55, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_45_55, fill_pullWidth_vs_eta),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 45...55 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_45_55",mpc,canOpt_1D
        },

        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_3_15, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_3_15, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_3_15, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_3_15, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 3...15 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_3_15",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_15_25, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_15_25, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_15_25, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_15_25, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_master), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(R20, forMomentum && ptWindow_15_25, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_R20), 
            },
            {"Single #mu, p_{T} #in 15...25 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_15_25",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_25_35, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_25_35, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_25_35, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_25_35, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 25...35 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_25_35",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_45, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_35_45, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_35_45, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_35_45, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 35...45 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_35_45",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_withTRT), 
                // // Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && noExt && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noExt), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_noTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_45_55, fill_pullWidth_vs_phi),ResoUtils::getIterRMS), pf_master), 
            },
            {"Single #mu, p_{T} #in 45...55 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_45_55",mpc,canOpt_1D
        },
    };


    CanvasOptions canOpt_2D = CanvasOptions(); 
    canOpt_2D.ColorPalette(kBird).ZAxis.modify().BottomPadding(0.2).TopPadding(0.2); 
    std::vector<PlotContent<TH2D>> testIt2D{ 
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsPt",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaCentral , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCentral , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCentral , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," |#eta| < 0.7 ","21.0.77"},"CheckPtErrVsPt_etaCentral",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaTrans , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaTrans , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaTrans , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 0.7 < |#eta| < 1.6 ","21.0.77"},"CheckPtErrVs_PtetaTrans",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaEC , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaEC , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaEC , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 1.6 < |#eta| < 2","21.0.77"},"CheckPtEr_rVsPtetaEC",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaPostTRT , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaPostTRT , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaPostTRT , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 2 < |#eta| < 2.5 ","21.0.77"},"CheckPtErrVsPt_etaPostTRT",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack1 , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack1 , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCrack1 , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 0 < |#eta| < 0.1 ","21.0.77"},"CheckPtErrVsPt_etaCrack1",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack2 , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack2 , fill_err_vs_pt), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCrack2 , fill_err_vs_pt), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 0.1 < |#eta| < 0.3 ","21.0.77"},"CheckPtErrVsPt_etaCrack2",mpc,canOpt_2D
        },

        // versus eta
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta",mpc,canOpt_2D
        },

        // versus eta, in pt windows
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_3_15 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_3_15 , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_3_15 , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...15 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_3_15",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_15_25 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_15_25 , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_15_25 , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 15...25 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_15_25",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_25_35 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_25_35 , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_25_35 , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 25...35 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_25_35",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_35_45 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_35_45 , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_35_45 , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 35...45 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_35_45",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_45_55 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_45_55 , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_45_55 , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 45...55 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_45_55",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_55_65 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_55_65 , fill_err_vs_eta), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && ptWindow_55_65 , fill_err_vs_eta), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 55...65 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_55_65",mpc,canOpt_2D
        },


        // versus phi, in eta - pt windows
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum &&  etaCrack1 , fill_err_vs_phi), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack1, fill_err_vs_phi), pf_noTRT), 
                Plot<TH2D>(RunHistoFiller(withTRT_master, forMomentum && etaCrack1, fill_err_vs_phi), pf_master), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, |#eta|<0.1 <#mu>=0","21.0.77"},"CheckPtErrVsPhi_Crack1_Pt_3_150",mpc,canOpt_2D
        },

    };

    CanvasOptions opts_reso = canOpt_2D; 
    opts_reso.ColorPalette(kLightTemperature).RatioAxis.modify().Min(0.85).Max(1.15).Fixed(true).Title("Release 22 / Release 21");
    CanvasOptions opts_resoD0 = canOpt_2D; 
    opts_resoD0.ColorPalette(kLightTemperature).RatioAxis.modify().Min(0.7).Max(1.3).Fixed(true).Title("no BL vs BL");
    // opts_resoD0.TopMargin(0.25);


    std::vector<PlotContent<TH2D>> forReso2D{
        PlotContent<TH2D>{
            {
                Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(withTRT, forMomentum , fill_Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_withTRT), 
                Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(withTRT_master, forMomentum , fill_Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_master), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0", "q/p_{T} resolution"},"CheckPtReso_singleMu",mpc,opts_reso

        },
        // PlotContent<TH2D>{
        //     {
        //         Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(withTRT_master, forMomentum , fill_Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_master), 
        //         Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(noBL_master, forMomentum , fill_Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_noTRT), 
        //     },
        //     {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0", "q/p_{T} resolution"},"CheckPtReso_singleMu",mpc,opts_resoD0

        // },
        // PlotContent<TH2D>{
        //     {
        //         Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(withTRT_master, forMomentum , fill_D0Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_master),
        //         Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(noBL_master, forMomentum , fill_D0Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_noTRT),  
        //     },
        //     {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0", "d_{0} resolution"},"CheckD0Reso_singleMu",mpc,opts_resoD0

        // },
        // PlotContent<TH2D>{
        //     {
        //         Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(withTRT_master, forMomentum , fill_Z0Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_master),
        //         Plot<TH2D>(GenericPostProcessing<TH2D, TH3D>(RunHistoFiller(noBL_master, forMomentum , fill_Z0Reso_vs_etaPt),ResoUtils::getIterRMS2D), pf_noTRT),  
        //     },
        //     {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0", "z_{0} resolution"},"CheckZ0Reso_singleMu",mpc,opts_resoD0

        // },
    };

    for (auto & it : oneDimCov) DefaultPlotting::draw1D(it); 
    for (auto & it : oneDimCovSplit) DefaultPlotting::draw1DNoRatio(it); 
    for (auto & it : testIt) DefaultPlotting::draw1D(it); 

    // for (auto & it : testIt2D) DefaultPlotting::draw2DPlots(it); 
    // for (auto & it : forReso2D) DefaultPlotting::draw2DPlots(it); 
    
    return 0;
}