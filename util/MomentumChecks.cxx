#include "IDPhysValPlotting/TruthRecoNtuple.h"

/// Stolen from IDPVM for consistency. Sorry!
std::pair<double,double> getIterRMS1D(std::shared_ptr<TH1D> input){
// evaluate  mean and RMS using iterative converfgence:
    double mean=input->GetMean();
    double RMS = input->GetRMS();
    
    // iteration parameters:
    // max iteration steps
    unsigned int ntries_max = 100;
    // width of cutting range in [RMS]
    double nRMS_width = 3.0;
    
    // iteration counters and helpers: 
    // min and max range of the histogram:
    double xmin=0.;
    double xmax=0.;
    // min and max bins of the histogram in previous iteration
    // 0-th iteration: range of the original histogram
    int binmin_was = 1;
    int binmax_was = input->GetNbinsX();
    // initial number of iteration steps
    unsigned int ntries = 0;
 
    // iteratively cut tails untill the RMS gets stable about mean
    // RMS stable: when input histogram range after cutting by 
    // +- 3*RMS is same as the range before cutting
    while ( ntries<ntries_max ) {    
      ++ntries;
      RMS = input->GetRMS();
      mean = input->GetMean();
      xmin = -1.0*nRMS_width*RMS + mean;
      xmax = nRMS_width*RMS + mean;
      // find bins corresponding to new range, disregard underflow
      int binmin=std::max(1,input->GetXaxis()->FindFixBin(xmin));
      // find bins corresponding to new range, disregard overflow
      int binmax=std::min(input->GetNbinsX(),input->GetXaxis()->FindFixBin(xmax));
      // end iteration if these are same bins as in prev. iteration
      if ( binmin_was==binmin && binmax_was==binmax ) {
	break;
      }
      else {
	// else set the new range and continue iteration 
	input->GetXaxis()->SetRange(binmin,binmax);
	binmin_was=binmin;
	binmax_was=binmax;
      }
    } // end of ( ntries<ntries_max ) ; iterative convergence loop
    
    // set the iteration results that are accessible to clients: 
    return std::make_pair(RMS, input->GetRMSError());    
}; 

std::shared_ptr<TH1D> getIterRMS(std::shared_ptr<TH2D> input){
    
    std::shared_ptr<TH1D> h1D {input->ProjectionX()}; 
    h1D->Reset(); 
    for (int bin = 1; bin < h1D->GetNbinsX()+1; ++bin){
        std::shared_ptr<TH1D> hY {input->ProjectionY(Form("py_%i",bin),bin,bin)}; 
        auto res = getIterRMS1D(hY); 
        h1D->SetBinContent(bin, res.first); 
        h1D->SetBinError(bin, res.second); 
    }
    return h1D; 
}; 

Selection<TruthRecoNtuple> getPtWindow(double lo, double hi){
    return Selection<TruthRecoNtuple>([hi,lo](TruthRecoNtuple& t){ return (t.truth_pt() > 1000. * lo && t.truth_pt() < 1000.*hi);}); 
}
Selection<TruthRecoNtuple> getAbsEtaWindow(double lo, double hi){
    return Selection<TruthRecoNtuple>([hi,lo](TruthRecoNtuple& t){ return (std::abs(t.truth_eta()) >  lo && std::abs(t.truth_eta()) < hi);}); 
}

int main(){

    Selection<TruthRecoNtuple> forMomentum(
        [](TruthRecoNtuple & t){
            return t.hasTrack() && t.hasTruth() && t.track_truthMatchProb() > 0.5; 
        }
    );

    Selection<TruthRecoNtuple> ptWindow_3_10 = getPtWindow(3,10); 
    Selection<TruthRecoNtuple> ptWindow_10_20 = getPtWindow(10,20);
    Selection<TruthRecoNtuple> ptWindow_20_30 = getPtWindow(20,30);  
    Selection<TruthRecoNtuple> ptWindow_30_40 = getPtWindow(30,40);  
    Selection<TruthRecoNtuple> ptWindow_40_50 = getPtWindow(40,50);
    Selection<TruthRecoNtuple> ptWindow_50_60 = getPtWindow(50,60); 


    Selection<TruthRecoNtuple> etaCrack1 = getAbsEtaWindow(0,0.1); 
    Selection<TruthRecoNtuple> etaCrack2 = getAbsEtaWindow(0.1,0.3); 
    Selection<TruthRecoNtuple> etaCentral = getAbsEtaWindow(0,0.7); 
    Selection<TruthRecoNtuple> etaTrans = getAbsEtaWindow(0.7,1.6); 
    Selection<TruthRecoNtuple> etaEC = getAbsEtaWindow(1.6,2); 
    Selection<TruthRecoNtuple> etaPostTRT = getAbsEtaWindow(2,2.5); 



    Sample<TruthRecoNtuple> withTRT {"/scratch/Datasets/Tracking/IDPVM/noTRT/singleMuFlat/Nominal.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 
    Sample<TruthRecoNtuple> noTRT {"/scratch/Datasets/Tracking/IDPVM/noTRT/singleMuFlat/noTRT.IDPVM.root","SquirrelPlots/Ntuples/SquirrelPlots_NtuplesTruthToReco"}; 

    PlotFormat pf_withTRT = PlotFormat().Color(kGray+3).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("Nominal, with TRT"); 
    PlotFormat pf_noTRT = PlotFormat().Color(kBlue).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("TRT ext. disabled"); 

    // std::vector<double> truthBins{5,10,15,20,25,9,12,15,
    PlotFillInstructionWithRef<TH2D,TruthRecoNtuple> fill_pullWidth_vs_pt ([](TH2D* h, TruthRecoNtuple &t){h->Fill(t.track_pt()/1000., (t.track_qOverPt() - t.truth_qOverPt())/t.trackErr_qOverPt());}, "check2D", "check2D;p_{T} [GeV];pull",19,5,100,2000,-8,8);

    PlotFillInstructionWithRef<TH2D,TruthRecoNtuple> fill_pullWidth_vs_eta ([](TH2D* h, TruthRecoNtuple &t){h->Fill(std::abs(t.track_eta()), (t.track_qOverPt() - t.truth_qOverPt())/t.trackErr_qOverPt());}, "check2D2", "check2D;|#eta|;pull",40,0,2.5,2000,-8,8);

    PlotFillInstructionWithRef<TH2D,TruthRecoNtuple> fill_pullWidth_vs_phi ([](TH2D* h, TruthRecoNtuple &t){h->Fill(t.track_phi(), (t.track_qOverPt() - t.truth_qOverPt())/t.trackErr_qOverPt());}, "check2D3", "check2D;#phi;pull",64,-3.142,3.142,2000,-8,8);

    PlotFillInstructionWithRef<TH2D, TruthRecoNtuple> fill_err_vs_pt([](TH2D* h, TruthRecoNtuple & t){
        h->Fill(t.truth_pt()*0.001, t.trackErr_qOverPt()/t.truth_qOverPt()); 
    }, "check2Dpterr","bla;p_{T} [GeV];#sigma_{q/pT} / (q/p_{T})",40,5,100,400,0,0.10); 

    PlotFillInstructionWithRef<TH2D, TruthRecoNtuple> fill_err_vs_eta([](TH2D* h, TruthRecoNtuple & t){
        h->Fill(std::abs(t.truth_eta()), t.trackErr_qOverPt()/t.truth_qOverPt()); 
    }, "check2Dpterr","bla;|#eta|;#sigma_{q/pT} / (q/p_{T})",40,0,2.5,400,0,0.10); 

    PlotFillInstructionWithRef<TH2D, TruthRecoNtuple> fill_err_vs_phi([](TH2D* h, TruthRecoNtuple & t){
        h->Fill(t.truth_phi(), t.trackErr_qOverPt()/t.truth_qOverPt()); 
    }, "check2Dpterr","bla;#phi;#sigma_{q/pT} / (q/p_{T})",40,-3.142,3.142,400,0,0.10); 
    
    CanvasOptions canOpt_1D = CanvasOptions(); 
    canOpt_1D.YAxis.modify().TopPadding(0.5).Symmetric(true).SymmetrisationPoint(1.0).Title("q/p_{T} pull width"); 
    canOpt_1D.RatioAxis.modify().TopPadding(0.2).Max(1).BottomPadding(0.2).Symmetric(false).Title("ratio w.r.t nominal"); 

    auto mpc = PlotUtils::startMultiPagePdfFile("SingleMuonResoChecks");
    std::vector<PlotContent<TH1D>> testIt{ 
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack1, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack1, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, |#eta| < 0.1, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_Crack1",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack2, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack2, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 0.1 < |#eta| < 0.3, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_Crack2",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaCentral, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaCentral, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, |#eta| < 0.7, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_central",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaTrans, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaTrans, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 0.7 < |#eta| < 1.6, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_trans",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaEC, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaEC, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 1.6 < |#eta| < 2.0, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_EC",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && etaPostTRT, fill_pullWidth_vs_pt),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && etaPostTRT, fill_pullWidth_vs_pt),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...100 GeV, 2.0 < |#eta| < 2.5, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_pt_postTRT",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_3_10, fill_pullWidth_vs_eta),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_3_10, fill_pullWidth_vs_eta),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...10 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_3_10",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_10_20, fill_pullWidth_vs_eta),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_10_20, fill_pullWidth_vs_eta),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 10...20 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_10_20",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_20_30, fill_pullWidth_vs_eta),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_20_30, fill_pullWidth_vs_eta),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 20...30 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_20_30",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_40, fill_pullWidth_vs_eta),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_30_40, fill_pullWidth_vs_eta),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 30...40 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_30_40",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_40_50, fill_pullWidth_vs_eta),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_40_50, fill_pullWidth_vs_eta),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 40...50 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_eta_pt_40_50",mpc,canOpt_1D
        },

        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_3_10, fill_pullWidth_vs_phi),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_3_10, fill_pullWidth_vs_phi),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 3...10 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_3_10",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_10_20, fill_pullWidth_vs_phi),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_10_20, fill_pullWidth_vs_phi),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 10...20 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_10_20",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_20_30, fill_pullWidth_vs_phi),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_20_30, fill_pullWidth_vs_phi),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 20...30 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_20_30",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_40, fill_pullWidth_vs_phi),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_30_40, fill_pullWidth_vs_phi),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 30...40 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_30_40",mpc,canOpt_1D
        },
        PlotContent<TH1D>{
            {
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_40_50, fill_pullWidth_vs_phi),getIterRMS), pf_withTRT), 
                Plot<TH1D>(GenericPostProcessing<TH1D, TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_40_50, fill_pullWidth_vs_phi),getIterRMS), pf_noTRT), 
            },
            {"Single #mu, p_{T} #in 40...50 GeV, <#mu>=0","21.0.77"},"CheckPullWidth_TRT_phi_pt_40_50",mpc,canOpt_1D
        },
    };


    CanvasOptions canOpt_2D = CanvasOptions(); 
    canOpt_2D.ColorPalette(kBird).ZAxis.modify().BottomPadding(0.2).TopPadding(0.2); 
    std::vector<PlotContent<TH2D>> testIt2D{ 
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsPt",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaCentral , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCentral , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," |#eta| < 0.7 ","21.0.77"},"CheckPtErrVsPt_etaCentral",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaTrans , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaTrans , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 0.7 < |#eta| < 1.6 ","21.0.77"},"CheckPtErrVs_PtetaTrans",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaEC , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaEC , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 1.6 < |#eta| < 2","21.0.77"},"CheckPtEr_rVsPtetaEC",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaPostTRT , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaPostTRT , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 2 < |#eta| < 2.5 ","21.0.77"},"CheckPtErrVsPt_etaPostTRT",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack1 , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack1 , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 0 < |#eta| < 0.1 ","21.0.77"},"CheckPtErrVsPt_etaCrack1",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && etaCrack2 , fill_err_vs_pt), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack2 , fill_err_vs_pt), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0"," 0.1 < |#eta| < 0.3 ","21.0.77"},"CheckPtErrVsPt_etaCrack2",mpc,canOpt_2D
        },

        // versus eta
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta",mpc,canOpt_2D
        },

        // versus eta, in pt windows
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_3_10 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_3_10 , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...10 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_3_10",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_10_20 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_10_20 , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 10...20 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_10_20",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_20_30 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_20_30 , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 20...30 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_20_30",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_30_40 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_30_40 , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 30...40 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_30_40",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_40_50 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_40_50 , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 40...50 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_40_50",mpc,canOpt_2D
        },
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum && ptWindow_50_60 , fill_err_vs_eta), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && ptWindow_50_60 , fill_err_vs_eta), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 50...60 GeV, <#mu>=0","21.0.77"},"CheckPtErrVsEta_Pt_50_60",mpc,canOpt_2D
        },


        // versus phi, in eta - pt windows
        PlotContent<TH2D>{
            {
                Plot<TH2D>(RunHistoFiller(withTRT, forMomentum &&  etaCrack1 , fill_err_vs_phi), pf_withTRT), 
                Plot<TH2D>(RunHistoFiller(noTRT, forMomentum && etaCrack1, fill_err_vs_phi), pf_noTRT), 
            }, 
            {"Single #mu, p_{T} #in 3...100 GeV, |#eta|<0.1 <#mu>=0","21.0.77"},"CheckPtErrVsPhi_Crack1_Pt_3_100",mpc,canOpt_2D
        },

    };

    for (auto & it : testIt) DefaultPlotting::draw1D(it); 

    for (auto & it : testIt2D) DefaultPlotting::draw2DPlots(it); 
    
    return 0;
}