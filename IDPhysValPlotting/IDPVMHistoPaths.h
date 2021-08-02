#ifndef IDPHYSVALPLOTTING__HISTOPATHS__H
#define IDPHYSVALPLOTTING__HISTOPATHS__H

#include <string> 
#include <vector> 

namespace IDPVMHistoPaths{

    std::string path_Efficiency(bool TightPrimary=false); 
    std::string path_params(bool TightPrimary=false); 
    std::string path_resolutions(bool TightPrimary=false); 
    std::string path_unlinked(bool TightPrimary=false); 
    std::string path_fake(bool TightPrimary=false); 
    std::string path_TRTExtension(bool TightPrimary=false); 
    std::string path_hitsOnTrack_Selected(bool TightPrimary=false); 
    std::string path_hitsOnTrack_Matched(bool TightPrimary=false); 

    /// scan helper. Scans a folder and returns a list of all found 
    /// objects of the desired type. Use to draw the entire content 
    /// of a given folder. 
    template <typename HistType> std::vector<std::string> scanPath(const std::string & fname, const std::string & path);

}

/// template method implementation
#include "IDPVMHistoPaths.ixx"

#endif // IDPHYSVALPLOTTING__HISTOPATHS__H