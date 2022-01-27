

#include "NtupleAnalysisUtils/NTAUTopLevelIncludes.h"
template <typename HistType> std::vector<std::string> IDPVMHistoPaths::scanPath(const std::string & fname, const std::string & path){
    auto all = PlotUtils::getAllObjectsFromFile<HistType>(fname);
    std::vector<std::string> found; 
    for (auto& thing : all){
        if (thing.find(path) == 0){
            found.push_back(thing); 
        }
    }
    return found;
}