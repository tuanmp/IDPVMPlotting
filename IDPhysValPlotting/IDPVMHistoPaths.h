#ifndef IDPHYSVALPLOTTING__HISTOPATHS__H
#define IDPHYSVALPLOTTING__HISTOPATHS__H

#include <string>
#include <vector>

/// Namespace to provide a few useful histogram lookup paths for convenience
namespace IDPVMHistoPaths
{
    /// Location of the IDPVM efficiency plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_Efficiency(bool TightPrimary = false);

    /// Location of the IDPVM track parameter plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_params(bool TightPrimary = false);

    /// Location of the IDPVM resolution plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_resolutions(bool TightPrimary = false);

    /// Location of the IDPVM unlinked track plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_unlinked(bool TightPrimary = false);

    /// Location of the IDPVM fake track plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_fake(bool TightPrimary = false);

    /// Location of the IDPVM TRT-extension plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_TRTExtension(bool TightPrimary = false);

    /// Location of the IDPVM hit/hole plots for all selected tracks.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_hitsOnTrack_Selected(bool TightPrimary = false);

    /// Location of the IDPVM efficiency hit/hole plots for truth-matched tracks.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_hitsOnTrack_Matched(bool TightPrimary = false);

    /// Location of the IDPVM for track in jet plots
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_tracksInJets(bool TightPrimary = false);

    /// Location of the IDPVM for track in jet plots
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_tracksInBJets(bool TightPrimary = false);

    std::string path_Efficiency_Loose();

    /// Location of the IDPVM track parameter plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_params_Loose();

    /// Location of the IDPVM resolution plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_resolutions_Loose();

    /// Location of the IDPVM unlinked track plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_unlinked_Loose();

    /// Location of the IDPVM fake track plots.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_fake_Loose();

    /// Location of the IDPVM hit/hole plots for all selected tracks.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_hitsOnTrack_Selected_Loose();

    /// Location of the IDPVM efficiency hit/hole plots for truth-matched tracks.
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_hitsOnTrack_Matched_Loose();

    /// Location of the IDPVM for track in jet plots
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_tracksInJets_Loose();

    /// Location of the IDPVM for track in jet plots
    /// @param TightPrimary: If enabled, return the location of the TightPrimary plots
    std::string path_tracksInBJets_Loose();

    /// scan helper. Scans a folder and returns a list of all found
    /// objects of the desired type. Use to draw the entire content
    /// of a given folder.
    template <typename HistType>
    std::vector<std::string> scanPath(const std::string &fname, const std::string &path);

}

/// template method implementation
#include "IDPVMHistoPaths.ixx"

#endif // IDPHYSVALPLOTTING__HISTOPATHS__H
