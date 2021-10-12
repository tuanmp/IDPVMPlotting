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

void fillMomErrorRel_ID_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_ID_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_ME_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_ME_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_MS_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_MS_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_CB_1D_Pos(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()) * 1000., t.EventWeight()); 
}
void fillMomErrorRel_CB_1D_Neg(TH1D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()) * 1000., t.EventWeight()); 
}


void fillMomResidualRel_vsPhiMP4_ID_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_ID_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_ID_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_ID_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_ME_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_ME_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_ME_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_ME_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_MS_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_MS_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_MS_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_MS_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_CB_1D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),(t.Pos_CB_QoverP() - t.Pos_Truth_qoverp())/ t.Pos_Truth_qoverp(), t.EventWeight()); 
}
void fillMomResidualRel_vsPhiMP4_CB_1D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),(t.Neg_CB_QoverP() - t.Neg_Truth_qoverp())/ t.Neg_Truth_qoverp(), t.EventWeight()); 
}

void fillMomErrorRel_ID_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ID_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_MS_TrackCov_qoverp() / t.Pos_MS_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_MS_TrackCov_qoverp() / t.Neg_MS_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsEta_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Pos_TruthEta()),t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsEta_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(std::abs(t.Neg_TruthEta()),t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP() * 1000.,  t.EventWeight()); 
}

void fillMomErrorRel_ID_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_ID_TrackCov_qoverp() / t.Pos_ID_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ID_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_ID_TrackCov_qoverp() / t.Neg_ID_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_ME_TrackCov_qoverp() / t.Pos_ME_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_ME_TrackCov_qoverp() / t.Neg_ME_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_MS_TrackCov_qoverp() / t.Pos_MS_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_MS_TrackCov_qoverp() / t.Neg_MS_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsPhi_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Pos_TruthPhi(),t.Pos_CB_TrackCov_qoverp() / t.Pos_CB_QoverP() * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsPhi_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(t.Neg_TruthPhi(),t.Neg_CB_TrackCov_qoverp() / t.Neg_CB_QoverP() * 1000.,  t.EventWeight()); 
}

void fillMomErrorRel_ID_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ID_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_2D_Pos(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_2D_Neg(TH2D* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()) * 1000.,  t.EventWeight()); 
}


void fillMomErrorRel_ID_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ID_TrackCov_qoverp() / std::abs(t.Pos_ID_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ID_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ID_TrackCov_qoverp() / std::abs(t.Neg_ID_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_ME_TrackCov_qoverp() / std::abs(t.Pos_ME_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_ME_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_ME_TrackCov_qoverp() / std::abs(t.Neg_ME_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_MS_TrackCov_qoverp() / std::abs(t.Pos_MS_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_MS_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_MS_TrackCov_qoverp() / std::abs(t.Neg_MS_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_Prof_Pos(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Pos_TruthPhi()),t.Pos_CB_TrackCov_qoverp() / std::abs(t.Pos_CB_QoverP()) * 1000.,  t.EventWeight()); 
}
void fillMomErrorRel_CB_vsPhiMP4_Prof_Neg(TProfile* h, MuonMomentumCalibrationTreeExtended &t){
    h->Fill(phiModPi4(t.Neg_TruthPhi()),t.Neg_CB_TrackCov_qoverp() / std::abs(t.Neg_CB_QoverP()) * 1000.,  t.EventWeight()); 
}

struct Region{
    std::string title{""}; 
    std::string label{""}; 
    double ptMin{0.};
    double ptMax{0.};
    double etaMin{0.};
    double etaMax{0.};
};

// std::vector<Plot<TH1D>> genPlotVec(TH1D* ref, Sample<MuonMomentumCalibrationTreeExtended> sample, Selection<MuonMomentumCalibrationTreeExtended> sel_base, 
//                                    double ptMin, double ptMax, double etaMin, double etaMax,

int main(){

    std::vector<Region> regions{
        Region{
            "MCP0","0 < |#eta| < 0.4; 50 < p_{T} < 60 GeV", 50.,60.,0.,0.4
        },
        Region{
            "MCP1","0.8 < |#eta| < 1.05; 35 < p_{T} < 40 GeV", 35.,40.,0.8,1.05
        },
        Region{
            "MCP2","2.1 < |#eta| < 2.3; 50 < p_{T} < 60 GeV", 50.,60.,2.1,2.3
        },
        // Region{
        //     "MCP3","2.3 < |#eta| < 2.5; 35 < p_{T} < 40 GeV", 35.,40.,2.3,2.5
        // },
        Region{
            "EtaScan0","0.0 < |#eta| < 0.2; 35 < p_{T} < 40 GeV", 35.,40.,0.0,0.2
        },
        Region{
            "EtaScan1","0.2 < |#eta| < 0.4; 35 < p_{T} < 40 GeV", 35.,40.,0.2,0.4
        },
        Region{
            "EtaScan2","0.4 < |#eta| < 0.6; 35 < p_{T} < 40 GeV", 35.,40.,0.4,0.6
        },
        Region{
            "EtaScan3","0.6 < |#eta| < 0.8; 35 < p_{T} < 40 GeV", 35.,40.,0.6,0.8
        },
        Region{
            "EtaScan4","0.8 < |#eta| < 1.0; 35 < p_{T} < 40 GeV", 35.,40.,0.8,1.0
        },
        Region{
            "EtaScan5","1.0 < |#eta| < 1.2; 35 < p_{T} < 40 GeV", 35.,40.,1.0,1.2
        },
        Region{
            "EtaScan6","1.2 < |#eta| < 1.4; 35 < p_{T} < 40 GeV", 35.,40.,1.2,1.4
        },
        Region{
            "EtaScan7","1.4 < |#eta| < 1.6; 35 < p_{T} < 40 GeV", 35.,40.,1.4,1.6
        },
        Region{
            "EtaScan8","1.6 < |#eta| < 1.8; 35 < p_{T} < 40 GeV", 35.,40.,1.6,1.8
        },
        Region{
            "EtaScan9","1.8 < |#eta| < 2; 35 < p_{T} < 40 GeV", 35.,40.,1.8,2
        },
        Region{
            "EtaScan10","2.0 < |#eta| < 2.2; 35 < p_{T} < 40 GeV", 35.,40.,2.0,2.2
        },
        Region{
            "EtaScan11","2.2 < |#eta| < 2.3; 35 < p_{T} < 40 GeV", 35.,40.,2.2,2.3
        },
    };

    const std::string & eosPrefix = "/eos/atlas/atlascerngroupdisk/perf-muon/MuonMomentumCalibration/muonptcalib_v05/raw/group.perf-muons.mc16_13TeV.361107.PowhegPythia8EvtGen_AZNLOCTEQ6L1_Zmumu.NTUP_MCP.r10724_p4145_muonptcalib_v05mcfix_EXT0/"; 
    Sample<MuonMomentumCalibrationTreeExtended> MCP;
    MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000001.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000002.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000003.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000004.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000005.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000006.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000007.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000008.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000009.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000010.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000011.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000012.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000013.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000014.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000015.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 
    // MCP.addFile(eosPrefix+"group.perf-muons.23950124.EXT0._000016.NTUP_MCScale.root","MuonMomentumCalibrationTree"); 

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


    Selection<MuonMomentumCalibrationTreeExtended> sel_baseline([](MuonMomentumCalibrationTreeExtended &t){
        return (
            t.Neg_Author() == 1 && t.Pos_Author() == 1 && t.Pair_IsOppCharge() && t.Pair_CB_Mass() > 70 && t.Pair_CB_Mass() < 110
        );
    });


    std::vector<double> ptbins {5,15,25,35,45,60,80,100};
    int nptbins = ptbins.size() - 1;  
    std::vector<double> etabins {-2.5, -2, -1.5, -1.05, -0.8, -0.4, 0, 0.4, 0.8, 1.05, 1.5, 2, 2.5}; 
    int netabins = etabins.size() - 1; 
    std::vector<double> resobins = PlotUtils::getLinearBinning(-2,2,20000); 
    int nresobins = resobins.size() - 1; 
    std::vector<double> resobinsD0 = PlotUtils::getLinearBinning(-40,40,400000); 
    int nresobinsD0 = resobinsD0.size() - 1; 

    TH1D href_pull_1D("check1Dpterr","bla;#sigma_{q/pT} / (q/p_{T})",140,0.0,0.12); 
    href_pull_1D.Sumw2();

    TH2D href_pull_2D_Eta("check2DpterrEta","bla;|#eta|;#sigma_{q/pT} / (q/p_{T})",25,0,2.5,140,0.0,0.12); 
    href_pull_2D_Eta.Sumw2();

    TH2D href_pull_2D_Phi("check2DpterrPhi","bla;#phi;#sigma_{q/pT} / (q/p_{T})",100,-3.15,3.15,200,0.0,0.12); 
    href_pull_2D_Phi.Sumw2();

    TH2D href_pull_2D_PhiMP4("check2DpterrPhiMP4","bla;#phi mod. #pi/4;#sigma_{q/pT} / (q/p_{T})",100,0,pi_over4,200,0.0,0.12); 
    href_pull_2D_Phi.Sumw2();

    TH2D href_residual_2D_PhiMP4("href_residual_2D_PhiMP4","bla;#phi mod. #pi/4;Residual",100,0,pi_over4,20000,-1.0,1.0); 
    href_residual_2D_PhiMP4.Sumw2();
    href_pull_2D_Phi.Sumw2();

    TProfile href_residual_TP_PhiMP4("href_residual_TP_PhiMP4","bla;#phi mod. #pi/4;Residual",100,0,pi_over4); 
    href_residual_TP_PhiMP4.Sumw2();

    auto mpc = PlotUtils::startMultiPagePdfFile("MCPMomentumChecks"); 

    PlotFillInstructionWithRef<TH1D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_1D_Pos{fillMomErrorRel_ID_1D_Pos,href_pull_1D}; 
    PlotFillInstructionWithRef<TH1D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_1D_Neg{fillMomErrorRel_ID_1D_Neg,href_pull_1D}; 
    PlotFillInstructionWithRef<TH1D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_1D_Pos{fillMomErrorRel_ME_1D_Pos,href_pull_1D}; 
    PlotFillInstructionWithRef<TH1D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_1D_Neg{fillMomErrorRel_ME_1D_Neg,href_pull_1D}; 
    PlotFillInstructionWithRef<TH1D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_1D_Pos{fillMomErrorRel_CB_1D_Pos,href_pull_1D}; 
    PlotFillInstructionWithRef<TH1D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_1D_Neg{fillMomErrorRel_CB_1D_Neg,href_pull_1D}; 


    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_2D_Eta_Pos{fillMomErrorRel_ID_vsEta_2D_Pos,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_2D_Eta_Neg{fillMomErrorRel_ID_vsEta_2D_Neg,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_2D_Eta_Pos{fillMomErrorRel_ME_vsEta_2D_Pos,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_2D_Eta_Neg{fillMomErrorRel_ME_vsEta_2D_Neg,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_2D_Eta_Pos{fillMomErrorRel_MS_vsEta_2D_Pos,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_2D_Eta_Neg{fillMomErrorRel_MS_vsEta_2D_Neg,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_2D_Eta_Pos{fillMomErrorRel_CB_vsEta_2D_Pos,href_pull_2D_Eta}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_2D_Eta_Neg{fillMomErrorRel_CB_vsEta_2D_Neg,href_pull_2D_Eta}; 


    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_2D_Phi_Pos{fillMomErrorRel_ID_vsPhi_2D_Pos,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_2D_Phi_Neg{fillMomErrorRel_ID_vsPhi_2D_Neg,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_2D_Phi_Pos{fillMomErrorRel_ME_vsPhi_2D_Pos,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_2D_Phi_Neg{fillMomErrorRel_ME_vsPhi_2D_Neg,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_2D_Phi_Pos{fillMomErrorRel_MS_vsPhi_2D_Pos,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_2D_Phi_Neg{fillMomErrorRel_MS_vsPhi_2D_Neg,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_2D_Phi_Pos{fillMomErrorRel_CB_vsPhi_2D_Pos,href_pull_2D_Phi}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_2D_Phi_Neg{fillMomErrorRel_CB_vsPhi_2D_Neg,href_pull_2D_Phi}; 


    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_2D_PhiMP4_Pos{fillMomErrorRel_ID_vsPhiMP4_2D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_2D_PhiMP4_Neg{fillMomErrorRel_ID_vsPhiMP4_2D_Neg,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_2D_PhiMP4_Pos{fillMomErrorRel_ME_vsPhiMP4_2D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_2D_PhiMP4_Neg{fillMomErrorRel_ME_vsPhiMP4_2D_Neg,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_2D_PhiMP4_Pos{fillMomErrorRel_MS_vsPhiMP4_2D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_2D_PhiMP4_Neg{fillMomErrorRel_MS_vsPhiMP4_2D_Neg,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_2D_PhiMP4_Pos{fillMomErrorRel_CB_vsPhiMP4_2D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_2D_PhiMP4_Neg{fillMomErrorRel_CB_vsPhiMP4_2D_Neg,href_pull_2D_PhiMP4}; 

    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_ID_2D_PhiMP4_Pos{fillMomResidualRel_vsPhiMP4_ID_1D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_ID_2D_PhiMP4_Neg{fillMomResidualRel_vsPhiMP4_ID_1D_Neg,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_ME_2D_PhiMP4_Pos{fillMomResidualRel_vsPhiMP4_ME_1D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_ME_2D_PhiMP4_Neg{fillMomResidualRel_vsPhiMP4_ME_1D_Neg,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_MS_2D_PhiMP4_Pos{fillMomResidualRel_vsPhiMP4_MS_1D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_MS_2D_PhiMP4_Neg{fillMomResidualRel_vsPhiMP4_MS_1D_Neg,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_CB_2D_PhiMP4_Pos{fillMomResidualRel_vsPhiMP4_CB_1D_Pos,href_pull_2D_PhiMP4}; 
    PlotFillInstructionWithRef<TH2D,MuonMomentumCalibrationTreeExtended> pfi_MomResidualRel_CB_2D_PhiMP4_Neg{fillMomResidualRel_vsPhiMP4_CB_1D_Neg,href_pull_2D_PhiMP4}; 

    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_TP_PhiMP4_Pos{fillMomErrorRel_ID_vsPhiMP4_Prof_Pos,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ID_TP_PhiMP4_Neg{fillMomErrorRel_ID_vsPhiMP4_Prof_Neg,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_TP_PhiMP4_Pos{fillMomErrorRel_ME_vsPhiMP4_Prof_Pos,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_ME_TP_PhiMP4_Neg{fillMomErrorRel_ME_vsPhiMP4_Prof_Neg,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_TP_PhiMP4_Pos{fillMomErrorRel_MS_vsPhiMP4_Prof_Pos,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_MS_TP_PhiMP4_Neg{fillMomErrorRel_MS_vsPhiMP4_Prof_Neg,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_TP_PhiMP4_Pos{fillMomErrorRel_CB_vsPhiMP4_Prof_Pos,href_residual_TP_PhiMP4}; 
    PlotFillInstructionWithRef<TProfile,MuonMomentumCalibrationTreeExtended> pfi_MomErrorRel_CB_TP_PhiMP4_Neg{fillMomErrorRel_CB_vsPhiMP4_Prof_Neg,href_residual_TP_PhiMP4}; 

    CanvasOptions copt_err_1D = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2);
    copt_err_1D.YAxis.modify().Title("arbitrary units").TopPadding(0.42); 

    CanvasOptions copy_reso_1D = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2);
    copy_reso_1D.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.42); 

    CanvasOptions copt_1Dcomp_res = CanvasOptions();
    copt_1Dcomp_res.YAxis.modify().Title("Rel. q/p resolution").TopPadding(0.32).Min(0); 


    CanvasOptions copt_err_2D_Eta = CanvasOptions().OtherLabelStepY(0.03).OtherLabelStartY(-0.1).LegendStartY(-0.01).LegendEndY(-0.2).RightMargin(0.2);
    copt_err_2D_Eta.ZAxis.modify().Title("#sigma_{q/pT} / (q/p_{T})").Min(10);
    
    

    std::vector<PlotContent<TH2D>> do2D_Eta;
    std::vector<PlotContent<TH2D>> do2D_Phi;

    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTest_Pos([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Pos_TruthPhi()) > 0.07 && phiModPi4(t.Pos_TruthPhi()) < 0.72); 
    }); 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTest_Neg([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Neg_TruthPhi()) > 0.07 && phiModPi4(t.Neg_TruthPhi()) < 0.72); 
    }); 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTestB_Pos([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Pos_TruthPhi()) > 0.28 && phiModPi4(t.Pos_TruthPhi()) < 0.52); 
    }); 
    Selection<MuonMomentumCalibrationTreeExtended> sel_phiAuxTestB_Neg([](MuonMomentumCalibrationTreeExtended &t){
        return (phiModPi4(t.Neg_TruthPhi()) > 0.28 && phiModPi4(t.Neg_TruthPhi()) < 0.52); 
    }); 


    std::vector<PlotContent<TH1D>> do1D;
    std::vector<PlotContent<TH1D>> do1DRatio;
    
    for (auto & region : regions){
        Selection <MuonMomentumCalibrationTreeExtended> sel_pos = sel_baseline && getPtWindow_Pos(region.ptMin,region.ptMax) && getAbsEtaWindow_Pos(region.etaMin, region.etaMax);  
        Selection <MuonMomentumCalibrationTreeExtended> sel_neg = sel_baseline && getPtWindow_Neg(region.ptMin,region.ptMax) && getAbsEtaWindow_Neg(region.etaMin, region.etaMax);  

        do1D.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                pfi_MomErrorRel_ID_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                pfi_MomErrorRel_ID_1D_Neg
                            },1),
                    pf_ID},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                pfi_MomErrorRel_ME_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                pfi_MomErrorRel_ME_1D_Neg
                            },1),
                    pf_ME},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                pfi_MomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                pfi_MomErrorRel_CB_1D_Neg
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

        do1D.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_pos,
                                pfi_MomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP, sel_neg,
                                pfi_MomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_auxAll},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_pos_aux1,
                                pfi_MomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_neg_aux1,
                                pfi_MomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_aux1},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_pos_aux2,
                                pfi_MomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_neg_aux2,
                                pfi_MomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_aux2},
                    Plot<TH1D>{
                        LinearCombination<TH1D>(  
                            RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_pos_aux3,
                                pfi_MomErrorRel_CB_1D_Pos
                            }, RunHistoFiller<TH1D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_1D, MCP,  sel_neg_aux3,
                                pfi_MomErrorRel_CB_1D_Neg
                            },1),
                    pf_CB_aux3},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_PhiSplitCheck"+region.title,mpc, copt_err_1D
            }
        );



        do1D.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    pfi_MomResidualRel_ID_2D_PhiMP4_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    pfi_MomResidualRel_ID_2D_PhiMP4_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ID},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    pfi_MomResidualRel_ME_2D_PhiMP4_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    pfi_MomResidualRel_ME_2D_PhiMP4_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ME},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    pfi_MomResidualRel_CB_2D_PhiMP4_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    pfi_MomResidualRel_CB_2D_PhiMP4_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_ResoVsPhiMP4"+region.title,mpc, copy_reso_1D
            }
        );
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TProfile>(
                            LinearCombination<TProfile>(  
                                RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_pos,
                                    pfi_MomErrorRel_ID_TP_PhiMP4_Pos
                                }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_neg,
                                    pfi_MomErrorRel_ID_TP_PhiMP4_Neg
                                },1), 
                            ResoUtils::profToTH1), pf_ID_MeanCov},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    pfi_MomResidualRel_ID_2D_PhiMP4_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    pfi_MomResidualRel_ID_2D_PhiMP4_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ID_Meas},
                },
                {"Z#rightarrow #mu#mu", "ID Tracks", region.label}, "CheckMuonPt_ID_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
            }
        );
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TProfile>(
                            LinearCombination<TProfile>(  
                                RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_pos,
                                    pfi_MomErrorRel_ME_TP_PhiMP4_Pos
                                }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_neg,
                                    pfi_MomErrorRel_ME_TP_PhiMP4_Neg
                                },1), 
                            ResoUtils::profToTH1), pf_ME_MeanCov},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    pfi_MomResidualRel_ME_2D_PhiMP4_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    pfi_MomResidualRel_ME_2D_PhiMP4_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_ME_Meas},
                },
                {"Z#rightarrow #mu#mu", "ME Tracks", region.label}, "CheckMuonPt_ME_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
            }
        );
        do1DRatio.push_back(
            PlotContent<TH1D>{
                {
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TProfile>(
                            LinearCombination<TProfile>(  
                                RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_pos,
                                    pfi_MomErrorRel_CB_TP_PhiMP4_Pos
                                }, RunHistoFiller<TProfile, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_TP_PhiMP4, MCP, sel_neg,
                                    pfi_MomErrorRel_CB_TP_PhiMP4_Neg
                                },1), 
                            ResoUtils::profToTH1), pf_CB_MeanCov},
                    Plot<TH1D>{
                        GenericPostProcessing<TH1D,TH2D>(
                            LinearCombination<TH2D>(  
                                RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_pos,
                                    pfi_MomResidualRel_CB_2D_PhiMP4_Pos
                                }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                    &href_residual_2D_PhiMP4, MCP, sel_neg,
                                    pfi_MomResidualRel_CB_2D_PhiMP4_Neg
                                },1), 
                            ResoUtils::getIterRMS), pf_CB_Meas},
                },
                {"Z#rightarrow #mu#mu", "CB Tracks", region.label}, "CheckMuonPt_CB_ResoExpVsObs_VsPhiMP4"+region.title,mpc, copt_1Dcomp_res
            }
        );

        do2D_Phi.push_back(
            PlotContent<TH2D>{
                {
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_pos,
                                pfi_MomErrorRel_ID_2D_Phi_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_neg,
                                pfi_MomErrorRel_ID_2D_Phi_Neg
                            },1),
                    pf_ID},
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_pos,
                                pfi_MomErrorRel_ME_2D_Phi_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_neg,
                                pfi_MomErrorRel_ME_2D_Phi_Neg
                            },1),
                    pf_ME},
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_pos,
                                pfi_MomErrorRel_MS_2D_Phi_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_neg,
                                pfi_MomErrorRel_MS_2D_Phi_Neg
                            },1),
                    pf_MS},
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_pos,
                                pfi_MomErrorRel_CB_2D_Phi_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_Phi, MCP, sel_neg,
                                pfi_MomErrorRel_CB_2D_Phi_Neg
                            },1),
                    pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_Phi2D_"+region.title,mpc, copt_err_2D_Eta
            }
        );
        do2D_Phi.push_back(
            PlotContent<TH2D>{
                {
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_pos,
                                pfi_MomErrorRel_ID_2D_PhiMP4_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_neg,
                                pfi_MomErrorRel_ID_2D_PhiMP4_Neg
                            },1),
                    pf_ID},
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_pos,
                                pfi_MomErrorRel_ME_2D_PhiMP4_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_neg,
                                pfi_MomErrorRel_ME_2D_PhiMP4_Neg
                            },1),
                    pf_ME},
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_pos,
                                pfi_MomErrorRel_MS_2D_PhiMP4_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_neg,
                                pfi_MomErrorRel_MS_2D_PhiMP4_Neg
                            },1),
                    pf_MS},
                    Plot<TH2D>{
                        LinearCombination<TH2D>(  
                            RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_pos,
                                pfi_MomErrorRel_CB_2D_PhiMP4_Pos
                            }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                                &href_pull_2D_PhiMP4, MCP, sel_neg,
                                pfi_MomErrorRel_CB_2D_PhiMP4_Neg
                            },1),
                    pf_CB},
                },
                {"Z#rightarrow #mu#mu", region.label}, "CheckMuonPt_PhiMP4_2D_"+region.title,mpc, copt_err_2D_Eta
            }
        );
    }
    

    auto sel_common_vsEta_Pos = sel_baseline && getPtWindow_Pos(35,40); 
    auto sel_common_vsEta_Neg = sel_baseline && getPtWindow_Neg(35,40); 

    do2D_Eta.push_back(
        PlotContent<TH2D>{
            {
                Plot<TH2D>{
                    LinearCombination<TH2D>(  
                        RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                            pfi_MomErrorRel_ID_2D_Eta_Pos
                        }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                            pfi_MomErrorRel_ID_2D_Eta_Neg
                        },1),
                pf_ID},
                Plot<TH2D>{
                    LinearCombination<TH2D>(  
                        RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                            pfi_MomErrorRel_ME_2D_Eta_Pos
                        }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                            pfi_MomErrorRel_ME_2D_Eta_Neg
                        },1),
                pf_ME},
                Plot<TH2D>{
                    LinearCombination<TH2D>(  
                        RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                            pfi_MomErrorRel_MS_2D_Eta_Pos
                        }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                            pfi_MomErrorRel_MS_2D_Eta_Neg
                        },1),
                pf_MS},
                Plot<TH2D>{
                    LinearCombination<TH2D>(  
                        RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP,sel_common_vsEta_Pos,
                            pfi_MomErrorRel_CB_2D_Eta_Pos
                        }, RunHistoFiller<TH2D, MuonMomentumCalibrationTreeExtended>{ 
                            &href_pull_2D_Eta, MCP, sel_common_vsEta_Neg,
                            pfi_MomErrorRel_CB_2D_Eta_Neg
                        },1),
                pf_CB},
            },
            {"Z#rightarrow #mu#mu", "35 < p_{T} < 40 GeV"}, "CheckMuonPt_vsEta_35to40",mpc, copt_err_2D_Eta
        }
    );

    for (auto & item : do1D){
        DefaultPlotting::draw1DNoRatio(item); 
    }
    for (auto & item : do1DRatio){
        DefaultPlotting::draw1D(item); 
    }
    for (auto & item : do2D_Eta){
        DefaultPlotting::draw2DPlots(item); 
    }
    for (auto & item : do2D_Phi){
        DefaultPlotting::draw2DPlots(item); 
    }


    return 0;
}