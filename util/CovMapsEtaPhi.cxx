#include "IDPhysValPlotting/MuonMomentumSamples.h"
#include "IDPhysValPlotting/MuonMomentumHelpers.h"
#include "IDPhysValPlotting/ResoUtils.h"
#include <TVector2.h> 
#include <TProfile2D.h> 

using namespace MuonMomentumHelpers;
using namespace MuonMomentumSamples;


int main(){

   
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
            t.Pos_CB_Pt() > 3 && t.Neg_CB_Pt() > 3 && t.Pos_CB_Pt()< 120 && t.Neg_CB_Pt()< 120 && t.Neg_IsCBMuon()  && t.Pos_IsCBMuon()  && t.Pair_IsOppCharge() && ((t.Pair_CB_Mass() > 60 && t.Pair_CB_Mass() < 120) || (t.Pair_CB_Mass() > 2.9 && t.Pair_CB_Mass() < 3.5))
        );
    });

    Sample<MuonMomentumCalibrationTreeExtended> MC = getSample_Zmumu(sel_baseline,-1); 
    MC.addFilesFrom(getSample_JPsi(sel_baseline, -1)); 

    Sample<MuonMomentumCalibrationTreeExtended> Data = getSample_Data(sel_baseline, -1); 
    Data.addFilesFrom(getSample_Data_BPHYS(sel_baseline, -1)); 

    // const std::string samplePrefix = "Zmumu"; 
    // const std::string "MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)" = "Z#rightarrow #mu#mu"; 

    //////////////////////////////////////////////
    /// Define the visuals of the histograms to be drawn. 
    //////////////////////////////////////////////

    PlotFormat pf_nominal = PlotFormat().Color(kBlack).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)"); 

    PlotFormat pf_ID = PlotFormat().Color(kBlue-6).MarkerStyle(kFullDotLarge).LegendOption("PLHIST").LegendTitle("ID track"); 
    PlotFormat pf_ME = PlotFormat().Color(kRed).MarkerStyle(kFullDotLarge).LegendOption("PLHIST").LegendTitle("ME track"); 

    //////////////////////////////////////////////
    /// Define the canvas-level options for visualisation
    //////////////////////////////////////////////
  
    CanvasOptions copt_err_2D_EtaPhi = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_EtaPhi.ZAxis.modify().Title("#sigma_{q/pT} / (q/p_{T})").Log(false).Min(0.01).Max(0.18).Fixed(true);

    CanvasOptions copt_err_2D_EtaPhi_CR = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_EtaPhi_CR.ZAxis.modify().Title("Ratio q<0 / q>0").Log(false).Min(0.6).Max(1.4).Fixed(true);

    //////////////////////////////////////////////
    /// Define the binnings of the histograms to be drawn. 
    /// Make sure to reserve sufficient granularity when running RMS evaluations! 
    //////////////////////////////////////////////


    TProfile2D href_prof2D_cov_etaphi("href_prof2D_cov_etaphi","bla;#eta;#phi;#sigma(q/p) / (q/p) ",800,-2.5,2.5,2000,-3.1415926, 3.1415926); 
    href_prof2D_cov_etaphi.Sumw2();

    /// Book plot content vectors
    std::vector<PlotContent<TH2D>> do2D;

    ///////////////////////////////////////////////////////////////////////////////
    /// Ok, we have all ingredients - now we can systematically book all our histograms
    ///////////////////////////////////////////////////////////////////////////////

    /// Set up a multi page PDF output file to store everything 
    auto mpc = PlotUtils::startMultiPagePdfFile("MCPMomentumChecks_CovChecksEtaPhi"); 

    /// Loop over our pt bins and book plots versus eta 

    for (auto & region : ResoRegions_pt){

        /// One selection per leg - needed because the ntuple format is a bit inconvenient... 
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos =  getPtWindow_Pos(region.ptMin,region.ptMax);  
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg =  getPtWindow_Neg(region.ptMin,region.ptMax);  
       
        /// Book 2D plots showing the actual distribution of the momentum error in bins of eta
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        
                            GenericPostProcessing<TH2D,TProfile2D>(
                                    LinearCombination<TProfile2D>(  
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC,sel_pos,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC, sel_neg,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Neg
                            },1),ProftoTH2D),
                    pf_ME},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)", region.label}, "CheckMuonCov_MC_vsEtaPhi2D_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC, sel_neg,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Neg
                            },ProftoTH2D),
                    pf_ME},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)","q < 0", region.label}, "CheckMuonCov_MC_vsEtaPhi2D_muMinus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC, sel_pos,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Pos
                            },ProftoTH2D),
                    pf_ME},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)","q > 0", region.label}, "CheckMuonCov_MC_vsEtaPhi2D_muPlus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC, sel_neg,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Neg
                                },ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC, sel_pos,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                },ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ME},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)","Reso. Ratio q<0 / q>0", region.label}, "CheckMuonCov_MC_vsEtaPhi2D_ChargeRatio_"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );


        /// and for the ID 

        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        
                            GenericPostProcessing<TH2D,TProfile2D>(
                                    LinearCombination<TProfile2D>(  
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC,sel_pos,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC, sel_neg,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Neg
                            },1),ProftoTH2D),
                    pf_ID},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC, sel_neg,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Neg
                            },ProftoTH2D),
                    pf_ID},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)","q < 0", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_muMinus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, MC, sel_pos,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Pos
                            },ProftoTH2D),
                    pf_ID},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)","q > 0", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_muPlus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC, sel_neg,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Neg
                                },ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC, sel_pos,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                },ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ID},
                },
                {"MC (Z#rightarrow #mu#mu, J/#Psi #rightarrow #mu#mu)","Reso. Ratio q<0 / q>0", region.label}, "CheckMuonCov_IDtrk_vsEtaPhi2D_ChargeRatio_"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );


        
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        
                            GenericPostProcessing<TH2D,TProfile2D>(
                                    LinearCombination<TProfile2D>(  
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data,sel_pos,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data, sel_neg,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Neg
                            },1),ProftoTH2D),
                    pf_ME},
                },
                {"Data", region.label}, "CheckMuonCov_Data_vsEtaPhi2D_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data, sel_neg,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Neg
                            },ProftoTH2D),
                    pf_ME},
                },
                {"Data","q < 0", region.label}, "CheckMuonCov_Data_vsEtaPhi2D_muMinus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data, sel_pos,
                                    fillMomErrorRel_ME_vsEtaPhi2D_Pos
                            },ProftoTH2D),
                    pf_ME},
                },
                {"Data","q > 0", region.label}, "CheckMuonCov_Data_vsEtaPhi2D_muPlus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data, sel_neg,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Neg
                                },ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data, sel_pos,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                },ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ME},
                },
                {"Data","Reso. Ratio q<0 / q>0", region.label}, "CheckMuonCov_Data_vsEtaPhi2D_ChargeRatio_"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );





        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                LinearCombination<TProfile2D>(  
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data,sel_pos,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                    }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data, sel_neg,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Neg
                                },1),ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                LinearCombination<TProfile2D>(  
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC,sel_pos,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Pos
                                    }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC, sel_neg,
                                        fillMomErrorRel_ME_vsEtaPhi2D_Neg
                                },1),ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ME},
                },
                {"ME resolution","Data/MC Reso Ratio", region.label}, "CheckMuonCov_DataMCResoRatio_vsEtaPhi2D"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );



        


        
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        
                            GenericPostProcessing<TH2D,TProfile2D>(
                                    LinearCombination<TProfile2D>(  
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data,sel_pos,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data, sel_neg,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Neg
                            },1),ProftoTH2D),
                    pf_ID},
                },
                {"Data", region.label}, "CheckMuonCov_ID_Data_vsEtaPhi2D_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data, sel_neg,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Neg
                            },ProftoTH2D),
                    pf_ID},
                },
                {"Data","q < 0", region.label}, "CheckMuonCov_ID_Data_vsEtaPhi2D_muMinus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                            GenericPostProcessing<TH2D,TProfile2D>(
                                RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_prof2D_cov_etaphi, Data, sel_pos,
                                    fillMomErrorRel_ID_vsEtaPhi2D_Pos
                            },ProftoTH2D),
                    pf_ID},
                },
                {"Data","q > 0", region.label}, "CheckMuonCov_ID_Data_vsEtaPhi2D_muPlus_"+region.title,mpc, copt_err_2D_EtaPhi
            }
        );
        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data, sel_neg,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Neg
                                },ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data, sel_pos,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                },ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ID},
                },
                {"Data","Reso. Ratio q<0 / q>0", region.label}, "CheckMuonCov_ID_Data_vsEtaPhi2D_ChargeRatio_"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );





        do2D.push_back(
            PlotContent<TH2D>{  
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH1>{
                            CalculateRatio<TH2D>(
                                GenericPostProcessing<TH2D,TProfile2D>(
                                LinearCombination<TProfile2D>(  
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data,sel_pos,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                    }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, Data, sel_neg,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Neg
                                },1),ProftoTH2D),
                                GenericPostProcessing<TH2D,TProfile2D>(
                                LinearCombination<TProfile2D>(  
                                    RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC,sel_pos,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Pos
                                    }, RunHistoFiller<TProfile2D, MuonMomentumCalibrationTreeExtended>{ 
                                        &href_prof2D_cov_etaphi, MC, sel_neg,
                                        fillMomErrorRel_ID_vsEtaPhi2D_Neg
                                },1),ProftoTH2D),PlotUtils::EfficiencyMode::defaultErrors
                            ),[](std::shared_ptr<TH1> h1){return std::dynamic_pointer_cast<TH2D>(h1);}},
                    pf_ID},
                },
                {"ID resolution","Data/MC Reso Ratio", region.label}, "CheckMuonCov_DataMCResoRatio_ID_vsEtaPhi2D"+region.title,mpc, copt_err_2D_EtaPhi_CR
            }
        );




    }
    /// Now, fill the histograms and draw them! 

    drawReso2D(do2D); 

    TFile* fout = new TFile("HistoDumps.root","RECREATE"); 
    for (auto & it : do2D){
        it.populateAll();
        auto theHist = it.getPlot(0); 
        fout->WriteTObject(theHist.getHisto(), it.getFileName().c_str());  
    }
    fout->Close(); 

    return 0;
}