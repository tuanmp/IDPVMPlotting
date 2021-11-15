#include "IDPhysValPlotting/MuonMomentumSamples.h"
#include "IDPhysValPlotting/MuonMomentumHelpers.h"
#include "IDPhysValPlotting/ResoUtils.h"
#include <TVector2.h> 
#include <TProfile2D.h> 

using namespace MuonMomentumHelpers;
using namespace MuonMomentumSamples;


int main(){

   

    //////////////////////////////////////////////
    /// Book the input sample
    //////////////////////////////////////////////

    Selection<MuonMomentumCalibrationTreeExtended> sel_baseline([](MuonMomentumCalibrationTreeExtended &t){
        return (
            t.Pos_CB_Pt() > 3 && t.Neg_CB_Pt() > 3 && t.Pos_CB_Pt()< 120 && t.Neg_CB_Pt()< 120 && t.Neg_IsCBMuon()  && t.Pos_IsCBMuon()  && t.Pair_IsOppCharge() && ((t.Pair_CB_Mass() > 60 && t.Pair_CB_Mass() < 120) || (t.Pair_CB_Mass() > 2.8 && t.Pair_CB_Mass() < 3.5))
        );
    });

    Sample<MuonMomentumCalibrationTreeExtended> MC = getSample_Zmumu(sel_baseline,40); 
    MC.addFilesFrom(getSample_JPsi(sel_baseline, 30)); 

    Sample<MuonMomentumCalibrationTreeExtended> Data = getSample_Data(sel_baseline, 40); 
    Data.addFilesFrom(getSample_Data_BPHYS(sel_baseline, 30)); 

    // const std::string samplePrefix = "Zmumu"; 
    // const std::string "MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)" = "Z#rightarrow #mu#mu"; 

    //////////////////////////////////////////////
    /// Define the visuals of the histograms to be drawn. 
    //////////////////////////////////////////////

    PlotFormat pf_nominal = PlotFormat().Color(kBlack).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)"); 

    PlotFormat pf_Stripe_MC = PlotFormat().Color(kBlue-6).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("MC - Stripe"); 
    PlotFormat pf_Aside_MC  = PlotFormat().Color(kOrange-3).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("MC - outside Stripe"); 
    PlotFormat pf_Stripe_Data = PlotFormat().Color(kBlue).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("Data - Stripe"); 
    PlotFormat pf_Aside_Data  = PlotFormat().Color(kRed).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("Data - outside Stripe"); 

    //////////////////////////////////////////////
    /// Define the canvas-level options for visualisation
    //////////////////////////////////////////////
  
    CanvasOptions copt_err_2D_EtaPhi = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_EtaPhi.ZAxis.modify().Title("#sigma_{q/pT} / (q/p_{T})").Log(false).Min(0.01).Max(0.18).Fixed(true);

    CanvasOptions copt_err_2D_EtaPhi_CR = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_EtaPhi_CR.ZAxis.modify().Title("Ratio q<0 / q>0").Log(false).Min(0.6).Max(1.4).Fixed(true);

    CanvasOptions copt_cov_vs_pt_1D = CanvasOptions().LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_cov_vs_pt_1D.RatioAxis.modify().Title("Data / MC").Log(false).Min(0.2).Max(1.8).Fixed(true);
    copt_cov_vs_pt_1D.YAxis.modify().Min(0.01).Max(0.12).Fixed(true);

    //////////////////////////////////////////////
    /// Define the binnings of the histograms to be drawn. 
    /// Make sure to reserve sufficient granularity when running RMS evaluations! 
    //////////////////////////////////////////////

    std::vector<double> ptBins{3,5,8,11,15,20,25,30,35,40,45,50,55,60,70,85,100,120}; 
    TProfile href_prof_cov_pt ("href_prof_cov_pt", "bla;#p_{T} [GeV]; #sigma(q/p) / (q/p) ", ptBins.size()-1, &(ptBins[0])); 

    // TProfile2D href_prof2D_cov_etaphi("href_prof2D_cov_etaphi","bla;#eta;#phi;#sigma(q/p) / (q/p) ",800,-2.5,2.5,2000,-3.1415926, 3.1415926); 
    // href_prof2D_cov_etaphi.Sumw2();

    /// Book plot content vectors
    std::vector<PlotContent<TH2D>> do2D;
    std::vector<PlotContent<TProfile>> do1D;

    Selection<MuonMomentumCalibrationTreeExtended> sel_stripes_pos{[](MuonMomentumCalibrationTreeExtended &t){
        double p = phiModPi4(t.Pos_ME_Phi()); 
        return p < 0.07 || p > 0.72; }
    }; 
    Selection<MuonMomentumCalibrationTreeExtended> sel_stripes_neg{[](MuonMomentumCalibrationTreeExtended &t){
        double p = phiModPi4(t.Neg_ME_Phi()); 
        return p < 0.07 || p > 0.72; }
    }; 
    Selection<MuonMomentumCalibrationTreeExtended> sel_remaining_pos = !sel_stripes_pos; 
    Selection<MuonMomentumCalibrationTreeExtended> sel_remaining_neg = !sel_stripes_neg; 

    Selection<MuonMomentumCalibrationTreeExtended> sel_forward_pos{ [](MuonMomentumCalibrationTreeExtended &t){
        return std::abs(t.Pos_ME_Eta()) > 2.3; }
    };
    Selection<MuonMomentumCalibrationTreeExtended> sel_forward_neg{ [](MuonMomentumCalibrationTreeExtended &t){
        return std::abs(t.Neg_ME_Eta()) > 2.3; }
    };

    PlotFillInstruction<TProfile, MuonMomentumCalibrationTreeExtended> fill_momErrRel_vs_pt_pos{
        [](TProfile* h, MuonMomentumCalibrationTreeExtended &t){
            h->Fill(t.Pos_ME_Pt(), std::abs(t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP()), t.weight()); 
        }
    }; 
    PlotFillInstruction<TProfile, MuonMomentumCalibrationTreeExtended> fill_momErrRel_vs_pt_neg{
        [](TProfile* h, MuonMomentumCalibrationTreeExtended &t){
            h->Fill(t.Neg_ME_Pt(), std::abs(t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP()), t.weight()); 
        }
    }; 

    ///////////////////////////////////////////////////////////////////////////////
    /// Ok, we have all ingredients - now we can systematically book all our histograms
    ///////////////////////////////////////////////////////////////////////////////

    /// Set up a multi page PDF output file to store everything 
    auto mpc = PlotUtils::startMultiPagePdfFile("MCPMomentumChecks_StripesForward"); 

    /// Loop over our pt bins and book plots versus eta 

    do1D.push_back(PlotContent<TProfile>{
        {
            Plot<TProfile>{
                LinearCombination<TProfile>{
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, MC, sel_forward_pos && sel_stripes_pos, fill_momErrRel_vs_pt_pos),
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, MC, sel_forward_neg && sel_stripes_neg, fill_momErrRel_vs_pt_neg)
                ,1}
                ,pf_Stripe_MC
            },
            Plot<TProfile>{
                LinearCombination<TProfile>{
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, MC, sel_forward_pos && !sel_stripes_pos, fill_momErrRel_vs_pt_pos),
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, MC, sel_forward_neg && !sel_stripes_neg, fill_momErrRel_vs_pt_neg)
                ,1}
                ,pf_Aside_MC
            },
            Plot<TProfile>{
                LinearCombination<TProfile>{
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, Data, sel_forward_pos && sel_stripes_pos, fill_momErrRel_vs_pt_pos),
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, Data, sel_forward_neg && sel_stripes_neg, fill_momErrRel_vs_pt_neg)
                ,1}
                ,pf_Stripe_Data
            },
            Plot<TProfile>{
                LinearCombination<TProfile>{
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, Data, sel_forward_pos && !sel_stripes_pos, fill_momErrRel_vs_pt_pos),
                    RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended> (&href_prof_cov_pt, Data, sel_forward_neg && !sel_stripes_neg, fill_momErrRel_vs_pt_neg)
                ,1}
                ,pf_Aside_Data
            },
        }, 
        { RatioEntry(2,0), RatioEntry(3,1)}, 
        {"|#eta| > 2.3", "ME tracks"}, 
        "MCPMomentumChecks_StripesForward/Reso_versus_pt", 
        mpc, 
        copt_cov_vs_pt_1D
    }); 

    /// Now, fill the histograms and draw them! 

    DefaultPlotting::draw1D(do1D); 
    TFile* fout = new TFile("EndcapResoVsPt.root","RECREATE"); 
    for (auto & it : do1D){
        int iplot = 0; 
        it.populateAll();
        for (auto & theHist : it.getPlots()){
            fout->WriteTObject(theHist.getHisto(), (it.getFileName()+"_"+std::to_string(++iplot)).c_str());  
        }
    }
    fout->Close(); 

    return 0;
}