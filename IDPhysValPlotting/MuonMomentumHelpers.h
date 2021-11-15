#ifndef IDPVP__MUONMOMENTUMHELPERS__H
#define  IDPVP__MUONMOMENTUMHELPERS__H

#include <memory> 

#include "IDPhysValPlotting/MuonMomentumCalibrationTreeExtended.h"

#include <TH1D.h> 
#include <TH2D.h> 
#include <TH3D.h> 
#include <TVector2.h> 
#include <TProfile.h> 
#include <TProfile2D.h> 

namespace MuonMomentumHelpers{

    constexpr double pi_over4 = std::acos(-1) / 4;

    void drawReso2D(PlotContent<TH2D>& pc); 
    /// fast vector processing
    void drawReso2D(std::vector<PlotContent<TH2D>>& pcs){
        for (auto & pc : pcs) drawReso2D(pc); 
    }
    /// not really needed, but fun! 
    template <typename P, typename... others> void drawReso2D(P& p, others... other){
        drawReso2D(p); 
        drawReso2D(other...); 
    }

    double phiModPi4(double phi){
        return std::fmod(TVector2::Phi_0_2pi(phi), pi_over4);
    }


    /// define a kinematic region 
    struct Region{
        std::string title{""}; 
        std::string label{""}; 
        double ptMin{0.};
        double ptMax{0.};
        double etaMin{0.};
        double etaMax{0.};
    };


    Selection<MuonMomentumCalibrationTreeExtended> getPtWindow_Pos(double lo, double hi);
    Selection<MuonMomentumCalibrationTreeExtended> getPtWindow_Neg(double lo, double hi);

    Selection<MuonMomentumCalibrationTreeExtended> getAbsEtaWindow_Pos(double lo, double hi);
    Selection<MuonMomentumCalibrationTreeExtended> getAbsEtaWindow_Neg(double lo, double hi);
    

    std::shared_ptr<TH2D> normaliseInBin(std::shared_ptr<TH2D> in);

    TH1D* getMedian(Plot<TH2D> h2);

    std::shared_ptr<TH2D> ProftoTH2D(std::shared_ptr<TProfile2D> in); 


    void fillMomErrorRel_ID_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_ID_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_ME_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_ME_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_MS_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_MS_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_CB_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_CB_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()), t.weight()); 
    }


    void fillMomResidualRel_vsPt_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPt(),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPt(),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPt(),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPt(),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPt(),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPt(),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPt(),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPt_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPt(),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }

    void fillMomResidualRel_vsEta_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsEta_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }

    void fillMomResidualRel_vsPhi_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhi_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }


    void fillMomResidualRel_vsPhiMP4_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.weight()); 
    }
    void fillMomResidualRel_vsPhiMP4_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.weight()); 
    }


    void fillMomPullRel_vsEta_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthEta()),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_CB_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsEta_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthEta()),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_CB_TrackCov_qoverp(), t.weight()); 
    }


    void fillMomPullRel_vsPt_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthPt()),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthPt()),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthPt()),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthPt()),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthPt()),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthPt()),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_TruthPt()),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_CB_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPt_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_TruthPt()),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_CB_TrackCov_qoverp(), t.weight()); 
    }


    void fillMomPullRel_vsPhiMP4_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_CB_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhiMP4_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_CB_TrackCov_qoverp(), t.weight()); 
    }

    void fillMomPullRel_vsPhi_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ID_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_ME_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_MS_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_TruthPhi(),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_CB_TrackCov_qoverp(), t.weight()); 
    }
    void fillMomPullRel_vsPhi_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_TruthPhi(),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_CB_TrackCov_qoverp(), t.weight()); 
    }

    void fillMomErrorRel_ID_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_ID_Eta()),t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_ID_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_ID_Eta()),t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_ME_Eta()),t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_ME_Eta()),t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_MS_Eta()),t.Pos_MS_TrackCov_qoverp() / t.Pos_MS_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_MS_Eta()),t.Neg_MS_TrackCov_qoverp() / t.Neg_MS_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Pos_CB_Eta()),t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(std::abs(t.Neg_CB_Eta()),t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP(),  t.weight()); 
    }

    void fillMomErrorRel_ID_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_ID_Phi(),t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_ID_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_ID_Phi(),t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_ME_Phi(),t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_ME_Phi(),t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_MS_Phi(),t.Pos_MS_TrackCov_qoverp() / t.Pos_MS_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_MS_Phi(),t.Neg_MS_TrackCov_qoverp() / t.Neg_MS_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_CB_Phi(),t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP(),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_CB_Phi(),t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP(),  t.weight()); 
    }

    void fillMomErrorRel_ID_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_ID_Phi()),t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_ID_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_ID_Phi()),t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_ME_Phi()),t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_ME_Phi()),t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_MS_Phi()),t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_MS_Phi()),t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_CB_Phi()),t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_CB_Phi()),t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()),  t.weight()); 
    }


    void fillMomErrorRel_ID_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_ID_Phi()),t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_ID_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_ID_Phi()),t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_ME_Phi()),t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_ME_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_ME_Phi()),t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_MS_Phi()),t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_MS_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_MS_Phi()),t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Pos_CB_Phi()),t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()),  t.weight()); 
    }
    void fillMomErrorRel_CB_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(phiModPi4(t.Neg_CB_Phi()),t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()),  t.weight()); 
    }

    void fillMomErrorRel_ME_vsEtaPhi2D_Pos(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_ME_Eta(), t.Pos_ME_Phi(), t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_ME_vsEtaPhi2D_Neg(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_ME_Eta(), t.Neg_ME_Phi(), t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()), t.weight()); 
    }

    void fillMomErrorRel_ID_vsEtaPhi2D_Pos(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_ID_Eta(), t.Pos_ID_Phi(), t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()), t.weight()); 
    }
    void fillMomErrorRel_ID_vsEtaPhi2D_Neg(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_ID_Eta(), t.Neg_ID_Phi(), t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()), t.weight()); 
    }

    void fill_goodPrecisionLayers_vsEtaPhi2D_Pos(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_CB_Eta(), t.Pos_CB_Phi(), t.Pos_NumberOfGoodPrecisionLayers(), t.weight()); 
    }
    void fill_goodPrecisionLayers_vsEtaPhi2D_Neg(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_CB_Eta(), t.Neg_CB_Phi(), t.Neg_NumberOfGoodPrecisionLayers(), t.weight()); 
    }

    void fill_primarySector_vsEtaPhi2D_Pos(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Pos_CB_Eta(), t.Pos_CB_Phi(), t.Pos_PrimarySector(), t.weight()); 
    }
    void fill_primarySector_vsEtaPhi2D_Neg(TProfile2D* h, MuonMomentumCalibrationTreeExtended &t){
        h->Fill(t.Neg_CB_Eta(), t.Neg_CB_Phi(), t.Neg_PrimarySector(), t.weight()); 
    }
}

#endif // IDPVP__MUONMOMENTUMHELPERS__H