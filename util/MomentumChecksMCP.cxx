#include "IDPhysValPlotting/MuonMomentumCalibrationTreeExtended.h"
#include "IDPhysValPlotting/MuonMomentumCalibrationTreeExtended.h"
#include "IDPhysValPlotting/ResoUtils.h"
#include <TVector2.h> 
namespace {
    constexpr double pi_over4 = std::acos(-1) / 4;
}

double phiModPi4(double phi){
    return std::fmod(TVector2::Phi_0_2pi(phi), pi_over4);
}

Selection<MuonMomentumCalibrationTreeExtended> getPtWindow_Pos(double lo, double hi){
    return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (t.Pos_TruthPt() > lo && t.Pos_TruthPt() < hi);}); 
}
Selection<MuonMomentumCalibrationTreeExtended> getPtWindow_Neg(double lo, double hi){
    return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (t.Neg_TruthPt() > lo && t.Neg_TruthPt() < hi);}); 
}

Selection<MuonMomentumCalibrationTreeExtended> getAbsEtaWindow_Pos(double lo, double hi){
    return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (std::abs(t.Pos_TruthEta()) >  lo && std::abs(t.Pos_TruthEta()) < hi);}); 
}
Selection<MuonMomentumCalibrationTreeExtended> getAbsEtaWindow_Neg(double lo, double hi){
    return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (std::abs(t.Neg_TruthEta()) >  lo && std::abs(t.Neg_TruthEta()) < hi);}); 
}

std::shared_ptr<TH2D> normaliseInBin(std::shared_ptr<TH2D> in){
    int ny = in->GetNbinsY(); 
    for (int kx = 1; kx <= in->GetNbinsX(); ++kx){
        double integ = in->Integral(kx,kx,1,ny); 
        double normFact= 0; 
        if (integ !=0) normFact=1/integ; 
        for (int ky = 0; ky < ny+1; ++ky){
            in->SetBinContent(kx,ky,in->GetBinContent(kx,ky)*normFact); 
            in->SetBinError(kx,ky,in->GetBinError(kx,ky)*normFact); 
        }
    }
    return in; 
}
TH1D* getMedian(Plot<TH2D> h2){
    int ny = h2->GetNbinsY(); 
    TH1D* profx = h2->ProjectionX(); 
    for (int kx = 1; kx <= h2->GetNbinsX(); ++kx){
        double integ = h2->Integral(kx,kx,1,ny); 
        double sum = 0; 
        for (int ky = 0; ky < ny+1; ++ky){
            sum += h2->GetBinContent(kx,ky); 
            if (sum >= 0.5 * integ){
                profx->SetBinContent(kx,h2->GetYaxis()->GetBinCenter(ky));
                profx->SetBinError(kx,h2->GetYaxis()->GetBinWidth(ky));  
                break; 
            }
            profx->SetBinContent(kx,h2->GetYaxis()->GetBinCenter(ny));
            profx->SetBinError(kx,h2->GetYaxis()->GetBinWidth(ny));  
        }
    }
    return profx; 


}

void fillMomErrorRel_ID_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_ID_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_ME_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_ME_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_MS_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_MS_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_CB_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()) * 1000., t.weight()); 
}
void fillMomErrorRel_CB_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()) * 1000., t.weight()); 
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
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_ID_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_MS_TrackCov_qoverp() / t.Pos_MS_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_MS_TrackCov_qoverp() / t.Neg_MS_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP() * 1000.,  t.weight()); 
}

void fillMomErrorRel_ID_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_ID_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_MS_TrackCov_qoverp() / t.Pos_MS_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_MS_TrackCov_qoverp() / t.Neg_MS_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP() * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP() * 1000.,  t.weight()); 
}

void fillMomErrorRel_ID_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_ID_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()) * 1000.,  t.weight()); 
}


void fillMomErrorRel_ID_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_ID_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()) * 1000.,  t.weight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()) * 1000.,  t.weight()); 
}
// Custom 2D plotting method, adding a few custom tweaks beyond what the defaults provide 

void drawReso2D(PlotContent<TH2D>& pc){
    SetAtlasStyle();
    pc.populateAll();
    CanvasOptions canvasOpts = pc.getCanvasOptions();
    // gStyle->SetPalette(kInvertedDarkBodyRadiator);
    // TColor::InvertPalette(); 


    gStyle->SetPalette(canvasOpts.ColorPalette());
    static Int_t  colors[2000];
    static Bool_t initialized = kFALSE;

    Double_t Red[7]    = { 1.00, 0.85, 0.6, 0.9, 0.8, 0.5, 0.2    };
    Double_t Green[7]  = { 1.00, 0.85, 0.2, 0.3, 0.7, 0.7, 0.8      };
    Double_t Blue[7]   = { 1.00, 1.00, 0.8, 0.3, 0.2, 0.2, 0.1    };
    Double_t Length[7] = { 0.00, 0.05, 0.2, 0.4, 0.6, 0.8, 1.0     };

    if(!initialized){
        Int_t FI = TColor::CreateGradientColorTable(7,Length,Red,Green,Blue,2000);
        for (int i=0; i<2000; i++) colors[i] = FI+i;
        initialized = kTRUE;
    //   return ;
    }
    gStyle->SetPalette(2000,colors);

    std::shared_ptr<TCanvas> can = PlotUtils::prepareCanvas(canvasOpts);
    
    auto plots = pc.getPlots();

    std::vector<TLatex*> LegLabels; 
    auto first = plots.front(); 
    size_t iter = 0; 
    for (auto& plot : plots){
        ++iter; 
        // plot->Set
        std::vector<Plot<TH2D>> forRange {plot}; 
        auto theFrame = PlotUtils::drawTopFrame(forRange, canvasOpts); 
        auto range = PlotUtils::getZRange(forRange,canvasOpts);
        LegLabels.push_back(PlotUtils::drawTLatex(canvasOpts.LegendStartX(),canvasOpts.LegendStartY(), plot.plotFormat().LegendTitle()));
        plot->SetMinimum(0); 
        // if (range.first < canvasOpts.ZAxis().Min()) plot->SetMinimum(canvasOpts.ZAxis().Min()); 
        plot->SetMaximum(range.second); 
        plot->SetContour(2000);
        // if (plot->GetMinimum() > 0) gPad->SetLogz(); 
        plot->Draw("colz");        
        // Plot<TH1D> profx{CopyExisting<TH1D>(plot->ProfileX()), PlotFormat().MarkerStyle(kOpenCircle).MarkerColor(kGray+2).LegendOption("PL").LegendTitle("Mean value").MarkerSize(0.4)}; 
        // Plot<TH1D> medx{CopyExisting<TH1D>(getMedian(plot)), PlotFormat().MarkerStyle(kOpenSquare).MarkerColor(kGray+2).LegendOption("PL").LegendTitle("Median value").MarkerSize(0.4)}; 
        // profx->Draw("SAMEPL"); 
        // medx->Draw("SAMEPL"); 
        if (plot->GetNbinsX() < 15 && plot->GetNbinsY() < 15){
            gStyle->SetPaintTextFormat(".2f");  
            plot->SetMarkerColor(kGray+2); 
            plot->Draw("SAMETEXT");      
        }
        // PlotUtils::drawLegend(std::vector<Plot<TH1D>>{profx,medx}, canvasOpts); 
        gPad->SetRightMargin(0.17);
        auto labelsToDraw = pc.getLabels(); 
        labelsToDraw.push_back(plot.plotFormat().LegendTitle()); 
        PlotUtils::drawLabels(labelsToDraw, canvasOpts); 
        PlotUtils::saveCanvas (can, pc.getFileName()+"_"+std::to_string(iter), canvasOpts);
        if (pc.getMultiPagePdfHandle()) pc.getMultiPagePdfHandle()->saveCanvas(can); 
    }
    PlotUtils::drawLabels(pc.getLabels(),canvasOpts);
}

/// fast vector processing
void drawReso2D(std::vector<PlotContent<TH2D>>& pcs){
    for (auto & pc : pcs) drawReso2D(pc); 
}
/// not really needed, but fun! 
template <typename P, typename... others> void drawReso2D(P& p, others... other){
    drawReso2D(p); 
    drawReso2D(other...); 
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
            "EtaScam1","0.0 < |#eta| < 0.1;40 < p_{T} < 45 GeV", 40.,45.,0.0,0.1
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

    // use the commented one if you have no local copy on hand 
    // const std::string & eosPrefix = "root://eosatlas.cern.ch//eos/atlas/atlascerngroupdisk/perf-muon/MuonMomentumCalibration/muonptcalib_v05/raw/group.perf-muons.mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.NTUP_MCP.r10724_p4145_muonptcalib_v05mcfix_EXT0/"; 
    const std::string & eosPrefix = "/scratch/Datasets/MCP/NTUP_MUONRES/group.perf-muons.mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.NTUP_MCP.r10724_p4145_muonptcalib_v05mcfix_EXT0/"; 


    Selection<MuonMomentumCalibrationTreeExtended> sel_baseline([](MuonMomentumCalibrationTreeExtended &t){
        return (
            t.Pos_TruthPt() > 10 && t.Neg_TruthPt() > 10 && t.Pos_TruthPt()< 120 && t.Neg_TruthPt()< 120 && t.Neg_IsCBMuon()  && t.Pos_IsCBMuon()  && t.Pair_IsOppCharge() && t.Pair_CB_Mass() > 60 && t.Pair_CB_Mass() < 120
        );
    });

    Sample<MuonMomentumCalibrationTreeExtended> MCP;
    MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000001.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000002.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000003.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000004.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000005.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000006.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000007.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000008.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000009.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000010.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000011.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000012.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000013.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000014.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000015.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000016.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000017.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000018.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000019.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000020.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000021.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000022.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000023.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000024.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000025.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000026.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000027.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000028.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000029.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000030.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000031.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000032.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000033.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000034.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000035.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000036.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000037.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000038.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000039.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000040.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000041.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000042.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000043.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000044.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000045.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000046.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000047.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000048.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000049.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000050.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000051.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000052.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000053.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000054.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000055.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000056.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000057.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000058.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000059.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000060.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000061.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000062.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000063.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000065.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000066.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000067.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000068.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000069.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000070.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000072.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000073.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000074.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000075.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000076.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000077.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000079.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000080.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000082.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000083.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000084.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000085.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000086.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000088.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000089.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000090.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000091.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000092.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000093.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000094.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000095.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000096.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000097.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000098.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000099.NTUP_MCScale.root","MuonMomentumCalibrationTree",sel_baseline); 



    //////////////////////////////////////////////
    /// Define the visuals of the histograms to be drawn. 
    //////////////////////////////////////////////

    PlotFormat pf_nominal = PlotFormat().Color(kBlack).MarkerStyle(kFullDotLarge).LegendOption("PL").LegendTitle("Z#rightarrow #mu#mu"); 
    PlotFormat pf_ID = PlotFormat().Color(kBlue-6).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("ID track"); 
    PlotFormat pf_ME = PlotFormat().Color(kRed).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("ME track"); 
    PlotFormat pf_MS = PlotFormat().Color(kViolet).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("MS track"); 
    PlotFormat pf_CB = PlotFormat().Color(kOrange-3).MarkerStyle(kDot).FillStyle(1001).FillAlpha(0.4).LegendOption("FL").ExtraDrawOpts("HISTE0)").LegendTitle("CB track"); 
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
    copt_pullWidth_1D.YAxis.modify().Title("q/p pull width").TopPadding(0.42); 

    CanvasOptions copt_1Dcomp_res = CanvasOptions();
    copt_1Dcomp_res.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.32).Min(0); 

    CanvasOptions copt_1Dcomp_ratio = CanvasOptions();
    copt_1Dcomp_ratio.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.32).Min(0);
    copt_1Dcomp_ratio.RatioAxis.modify().Title("Fraction of total").Min(0).Max(1).Fixed(true).Symmetric(false); 

    CanvasOptions copt_err_2D_Eta = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_Eta.ZAxis.modify().Title("#sigma_{q/pT} / (q/p_{T})").Log(false).Min(0);

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

    TH2D href_pull_2D_Eta("check2DpterrEta","bla;|#eta|;#sigma_{q/pT} / (q/p_{T})",200,0,2.5,400,0.0,0.12); 
    href_pull_2D_Eta.Sumw2();

    TH2D href_pull_2D_Phi("check2DpterrPhi","bla;#phi;#sigma_{q/pT} / (q/p_{T})",300,-3.15,3.15,400,0.0,0.12); 
    href_pull_2D_Phi.Sumw2();

    TH2D href_pull_2D_PhiMP4("check2DpterrPhiMP4","bla;#phi mod. #pi/4;#sigma_{q/pT} / (q/p_{T})",300,0,pi_over4,400,0.0,0.12); 
    href_pull_2D_Phi.Sumw2();

    TH2D href_momres_2D_Pt("href_momres_2D_Pt","bla;p_{T} [GeV];pull width on q/p",nptbins,&(ptbins[0]),400,-1,1); 
    href_momres_2D_Pt.Sumw2();

    TH2D href_momres_2D_Eta("href_momres_2D_Eta","bla;|#eta|;pull width on q/p",50,0,2.5,400,-1,1); 
    href_momres_2D_Eta.Sumw2();

    TH2D href_momres_2D_Phi("href_momres_2D_Phi","bla;#phi;pull width on q/p",50,-3.15,3.15,400,-1,1); 
    href_momres_2D_Phi.Sumw2();

    TH2D href_momres_2D_PhiMP4("href_momres_2D_PhiMP4","bla;#phi mod. #pi/4;pull width on q/p",50,0,pi_over4,400,-1,1); 
    href_momres_2D_PhiMP4.Sumw2();

    TH2D href_residual_2D_PhiMP4("href_residual_2D_PhiMP4","bla;#phi mod. #pi/4;Residual",200,0,pi_over4,1400,-0.7,0.7); 
    href_residual_2D_PhiMP4.Sumw2();
    href_pull_2D_Phi.Sumw2();

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
    auto mpc = PlotUtils::startMultiPagePdfFile("MCPMomentumChecks"); 

    /// Loop over the eta-pt regions and book histograms 
    for (auto & region : regions){

        /// One selection per leg - needed because the ntuple format is a bit inconvenient... 
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos =  getPtWindow_Pos(region.ptMin,region.ptMax) && getAbsEtaWindow_Pos(region.etaMin, region.etaMax);  
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg =  getPtWindow_Neg(region.ptMin,region.ptMax) && getAbsEtaWindow_Neg(region.etaMin, region.etaMax);  

        /// Book 1D plots of the momentum error for each track. 
        do1D.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                fillMomErrorRel_ID_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                fillMomErrorRel_ID_1D_Neg
                            },1),
                    pf_ID},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                fillMomErrorRel_ME_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                fillMomErrorRel_ME_1D_Neg
                            },1),
                    pf_ME},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                fillMomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                fillMomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_"+region.title,mpc, copt_err_1D
            }
        );
        
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos_aux1 = sel_pos && sel_phiAuxTest_Pos && sel_phiAuxTestB_Pos; 
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg_aux1 = sel_neg && sel_phiAuxTest_Neg && sel_phiAuxTestB_Neg; 
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos_aux2 = sel_pos && sel_phiAuxTest_Pos && !sel_phiAuxTestB_Pos; 
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg_aux2 = sel_neg && sel_phiAuxTest_Neg && !sel_phiAuxTestB_Neg; 
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos_aux3 = sel_pos && !sel_phiAuxTest_Pos; 
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg_aux3 = sel_neg && !sel_phiAuxTest_Neg; 

        /// Book plots showing the composition of the CB error distribution in terms of chamber-level phi-regions
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                fillMomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                fillMomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_auxAll},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_pos_aux1,
                                fillMomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_neg_aux1,
                                fillMomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_aux1},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_pos_aux2,
                                fillMomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_neg_aux2,
                                fillMomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_aux2},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_pos_aux3,
                                fillMomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_neg_aux3,
                                fillMomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_aux3},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_PhiSplitCheck"+region.title,mpc, copt_1Dcomp_ratio
            }
        );



        /// Book plots with the iterative RMS based resolution versus chamber-level phi
        do1D.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    fillMomResidualRel_vsPhiMP4_ID_1D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    fillMomResidualRel_vsPhiMP4_ID_1D_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ID},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    fillMomResidualRel_vsPhiMP4_ME_1D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    fillMomResidualRel_vsPhiMP4_ME_1D_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ME},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    fillMomResidualRel_vsPhiMP4_CB_1D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    fillMomResidualRel_vsPhiMP4_CB_1D_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_ResoVsPhiMP4"+region.title,mpc, copt_reso_1D
            }
        );

        
        /// Book plots with comparing the mean q/p covariance error to the actual resolution for the ID track
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TProfile>(
                            LinearCombination<TProfile>(  
                                RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_pos,
                                    fillMomErrorRel_ID_vsPhiMP4_Prof_Pos
                                }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_neg,
                                    fillMomErrorRel_ID_vsPhiMP4_Prof_Neg
                                },1), 
                            ResoUtils::profToTH1), pf_ID_MeanCov},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    fillMomResidualRel_vsPhiMP4_ID_1D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    fillMomResidualRel_vsPhiMP4_ID_1D_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ID_Meas},
                },
                {"Z#rightarrow #mu#mu", "ID Tracks", region.label}, "CheckMuonPt_ID_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
            }
        );
        /// Book plots with comparing the mean q/p covariance error to the actual resolution for the ME track
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TProfile>(
                            LinearCombination<TProfile>(  
                                RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_pos,
                                    fillMomErrorRel_ME_vsPhiMP4_Prof_Pos
                                }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_neg,
                                    fillMomErrorRel_ME_vsPhiMP4_Prof_Neg
                                },1), 
                            ResoUtils::profToTH1), pf_ME_MeanCov},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    fillMomResidualRel_vsPhiMP4_ME_1D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    fillMomResidualRel_vsPhiMP4_ME_1D_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ME_Meas},
                },
                {"Z#rightarrow #mu#mu", "ME Tracks", region.label}, "CheckMuonPt_ME_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
            }
        );
        /// Book plots with comparing the mean q/p covariance error to the actual resolution for the CB track
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TProfile>(
                            LinearCombination<TProfile>(  
                                RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_pos,
                                    fillMomErrorRel_CB_vsPhiMP4_Prof_Pos
                                }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_neg,
                                    fillMomErrorRel_CB_vsPhiMP4_Prof_Neg
                                },1), 
                            ResoUtils::profToTH1), pf_CB_MeanCov},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    fillMomResidualRel_vsPhiMP4_CB_1D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    fillMomResidualRel_vsPhiMP4_CB_1D_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_CB_Meas},
                },
                {"Z#rightarrow #mu#mu", "CB Tracks", region.label}, "CheckMuonPt_CB_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
            }
        );

        /// Book 2D plots showing the actual distribution of the momentum error in bins of phi 
        do2D_Phi.push_back(
            PlotContent<TH2D>{
                {
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_Phi, MCP, sel_pos,
                                    fillMomErrorRel_ID_vsPhi_2D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_Phi, MCP, sel_neg,
                                    fillMomErrorRel_ID_vsPhi_2D_Neg
                                },1),normaliseInBin),
                    pf_ID},
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_Phi, MCP, sel_pos,
                                    fillMomErrorRel_ME_vsPhi_2D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_Phi, MCP, sel_neg,
                                    fillMomErrorRel_ME_vsPhi_2D_Neg
                                },1),normaliseInBin),
                    pf_ME},
                    // Plot<TH2D>{
                    //     GenericPostProcessing<TH2D,TH2D>(
                    //         LinearCombination<TH2D>(  
                    //             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                    //                 &href_pull_2D_Phi, MCP, sel_pos,
                    //                 fillMomErrorRel_MS_vsPhi_2D_Pos
                    //             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                    //                 &href_pull_2D_Phi, MCP, sel_neg,
                    //                 fillMomErrorRel_MS_vsPhi_2D_Neg
                    //             },1),normaliseInBin),
                    // pf_MS},
                    Plot<TH2D>{
                        GenericPostProcessing<TH2D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_Phi, MCP, sel_pos,
                                    fillMomErrorRel_CB_vsPhi_2D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_Phi, MCP, sel_neg,
                                    fillMomErrorRel_CB_vsPhi_2D_Neg
                                },1),normaliseInBin),
                    pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_Phi2D_"+region.title,mpc, copt_err_2D_Eta
            }
        );

        /// Book 2D plots showing the actual distribution of the momentum error in bins of chamber-level phi 
        do2D_Phi.push_back(
            PlotContent<TH2D>{
                {
                    Plot<TH2D>{
                        
                        GenericPostProcessing<TH2D,TH2D>(
                                LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_PhiMP4, MCP, sel_pos,
                                    fillMomErrorRel_ID_vsPhiMP4_2D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_PhiMP4, MCP, sel_neg,
                                    fillMomErrorRel_ID_vsPhiMP4_2D_Neg
                                },1),normaliseInBin),
                    pf_ID},
                    Plot<TH2D>{
                        
                        GenericPostProcessing<TH2D,TH2D>(
                                LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_PhiMP4, MCP, sel_pos,
                                    fillMomErrorRel_ME_vsPhiMP4_2D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_PhiMP4, MCP, sel_neg,
                                    fillMomErrorRel_ME_vsPhiMP4_2D_Neg
                                },1),normaliseInBin),
                    pf_ME},
                    // Plot<TH2D>{
                        
                    //     GenericPostProcessing<TH2D,TH2D>(
                    //             LinearCombination<TH2D>(  
                    //             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                    //                 &href_pull_2D_PhiMP4, MCP, sel_pos,
                    //                 fillMomErrorRel_MS_vsPhiMP4_2D_Pos
                    //             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                    //                 &href_pull_2D_PhiMP4, MCP, sel_neg,
                    //                 fillMomErrorRel_MS_vsPhiMP4_2D_Neg
                    //             },1),normaliseInBin),
                    // pf_MS},
                    Plot<TH2D>{
                        
                        GenericPostProcessing<TH2D,TH2D>(
                                LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_PhiMP4, MCP, sel_pos,
                                    fillMomErrorRel_CB_vsPhiMP4_2D_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_pull_2D_PhiMP4, MCP, sel_neg,
                                    fillMomErrorRel_CB_vsPhiMP4_2D_Neg
                                },1),normaliseInBin),
                    pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_PhiMP4_2D_"+region.title,mpc, copt_err_2D_Eta
            }
        );
    }
    

    auto sel_common_vsEta_Pos =  getPtWindow_Pos(40,45); 
    auto sel_common_vsEta_Neg =  getPtWindow_Neg(40,45); 

    do2D_Eta.push_back(
        /// Book 2D plots showing the actual distribution of the momentum error in bins of eta
        PlotContent<TH2D>{
            {
                Plot<TH2D>{
                    
                        GenericPostProcessing<TH2D,TH2D>(
                                LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                                fillMomErrorRel_ID_vsEta_2D_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                                fillMomErrorRel_ID_vsEta_2D_Neg
                        },1),normaliseInBin),
                pf_ID},
                Plot<TH2D>{
                    
                        GenericPostProcessing<TH2D,TH2D>(
                                LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                                fillMomErrorRel_ME_vsEta_2D_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                                fillMomErrorRel_ME_vsEta_2D_Neg
                        },1),normaliseInBin),
                pf_ME},
                // Plot<TH2D>{
                    
                //         GenericPostProcessing<TH2D,TH2D>(
                //                 LinearCombination<TH2D>(  
                //             RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                //                 &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                //                 fillMomErrorRel_MS_vsEta_2D_Pos
                //             }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                //                 &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                //                 fillMomErrorRel_MS_vsEta_2D_Neg
                //         },1),normaliseInBin),
                // pf_MS},
                Plot<TH2D>{
                    
                        GenericPostProcessing<TH2D,TH2D>(
                                LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                                fillMomErrorRel_CB_vsEta_2D_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                                fillMomErrorRel_CB_vsEta_2D_Neg
                        },1),normaliseInBin),
                pf_CB},
            },
            {"Z#rightarrow #mu#mu", "40 < p_{T} < 45 GeV"}, "CheckMuonPt_vsEta_40to45",mpc, copt_err_2D_Eta
        }
    );

    DefaultPlotting::draw1DNoRatio(do1D); 
    DefaultPlotting::draw1D(do1DRatio); 
    drawReso2D(do2D_Eta, do2D_Phi); 

    return 0;
}