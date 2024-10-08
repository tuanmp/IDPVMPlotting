#include "IDPhysValPlotting/IDPVMHistoPaths.h"

namespace IDPVMHistoPaths{

    std::string path_Efficiency(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/Efficiency/"; 
    } 
    std::string path_resolutions(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/Matched/Resolutions/Primary/"; 
    } 
    std::string path_params(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/Selected/Parameters/"; 
    } 
    std::string path_unlinked(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/Unlinked/FakeRate/"; 
    } 
    std::string path_fake(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/FakeRate/"; 
    } 
    std::string path_TRTExtension(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/TRTExtension/"; 
    } 
    std::string path_hitsOnTrack_Selected(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/Selected/HitsOnTracks/"; 
    } 
    std::string path_hitsOnTrack_Matched(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"Tracks/Matched/HitsOnTracks/"; 
    } 
    std::string path_tracksInJets(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"TracksInJets/"; 
    } 
    std::string path_tracksInBJets(bool TightPrimary){
        return std::string("SquirrelPlots/")+std::string(TightPrimary ? "TightPrimary/": "")+"TracksInBJets/"; 
    } 
     
    // loose 
    std::string path_Efficiency_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/Efficiency/"; 
    } 
    std::string path_resolutions_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/Matched/Resolutions/Primary/"; 
    } 
    std::string path_params_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/Selected/Parameters/"; 
    } 
    std::string path_unlinked_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/Unlinked/FakeRate/"; 
    } 
    std::string path_fake_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/FakeRate/"; 
    } 
    std::string path_TRTExtension_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/TRTExtension/"; 
    } 
    std::string path_hitsOnTrack_Selected_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/Selected/HitsOnTracks/"; 
    } 
    std::string path_hitsOnTrack_Matched_Loose () {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"Tracks/Matched/HitsOnTracks/"; 
    } 
    std::string path_tracksInJets_Loose  ( ) {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"TracksInJets/"; 
    } 
    std::string path_tracksInBJets_Loose  ( ) {
        return std::string("SquirrelPlots/")+std::string("Loose/")+"TracksInBJets/"; 
    } 


}
