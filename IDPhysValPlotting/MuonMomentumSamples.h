#ifndef IDPVP__MUONMOMENTUMSAMPLES__H
#define IDPVP__MUONMOMENTUMSAMPLES__H

#include "IDPhysValPlotting/MuonMomentumCalibrationTreeExtended.h"

namespace MuonMomentumSamples{
    Sample<MuonMomentumCalibrationTreeExtended> getSample_Zmumu (Selection<MuonMomentumCalibrationTreeExtended> sampleSel, int nFiles=-1); 
    Sample<MuonMomentumCalibrationTreeExtended> getSample_Zmumu_testLatest (Selection<MuonMomentumCalibrationTreeExtended> sampleSel, int nFiles=-1); 
    Sample<MuonMomentumCalibrationTreeExtended> getSample_JPsi (Selection<MuonMomentumCalibrationTreeExtended> sampleSel, int nFiles=-1); 
    Sample<MuonMomentumCalibrationTreeExtended> getSample_Data (Selection<MuonMomentumCalibrationTreeExtended> sampleSel, int nFiles=-1); 
    Sample<MuonMomentumCalibrationTreeExtended> getSample_Data_BPHYS (Selection<MuonMomentumCalibrationTreeExtended> sampleSel, int nFiles=-1); 
    void addFilesToSample (Sample<MuonMomentumCalibrationTreeExtended> & sample, const std::vector<std::string>& files, const std::string & inPath, Selection<MuonMomentumCalibrationTreeExtended> sampleSel = Selection<MuonMomentumCalibrationTreeExtended>(), int nFiles=-1); 
}
#endif // IDPVP__MUONMOMENTUMSAMPLES__H