#include "NtupleAnalysisUtils/NTAUTopLevelIncludes.h"
#include <algorithm>

int main(int, char**){

    const std::string f1 = "/home/goblirsc/Code/Tracking/IDPVMDev/run/unmodified/PhysVal.root"; 
    const std::string f2 = "/home/goblirsc/Code/Tracking/IDPVMDev/run/modified/PhysVal.root"; 

    auto found1 = PlotUtils::getAllObjectsFromFile<TNamed>(f1);
    auto found2 = PlotUtils::getAllObjectsFromFile<TNamed>(f2);

    std::vector<std::string> inBoth{}; 
    std::vector<std::string> in1{}; 
    std::vector<std::string> in2{}; 

    std::copy_if(found1.begin(), found1.end(), std::back_inserter(inBoth), [&found2](const std::string & s1){
        return (std::find(found2.begin(),found2.end(),s1) != found2.end()); 
    }); 
    std::copy_if(found1.begin(), found1.end(), std::back_inserter(in1), [&found2](const std::string & s1){
        return (std::find(found2.begin(),found2.end(),s1) == found2.end()); 
    }); 
    std::copy_if(found2.begin(), found2.end(), std::back_inserter(in2), [&found1](const std::string & s1){
        return (std::find(found1.begin(),found1.end(),s1) == found1.end()); 
    }); 
    size_t nTotal = inBoth.size() + in1.size()+in2.size(); 

    std::cout << "====== Found in BOTH: "<<inBoth.size()<<" / "<<nTotal<<" ================="<<std::endl;
    for (auto & s : inBoth){
        std::cout << "      "<<s<<std::endl; 
    }
    std::cout << "====== Found ONLY IN non-mod: "<<in1.size()<<" / "<<nTotal<<" ================="<<std::endl;
    for (auto & s : in1){
        std::cout << "      "<<s<<std::endl; 
    }
    std::cout << "====== Found ONLY IN mod: "<<in2.size()<<" / "<<nTotal<<" ================="<<std::endl;
    for (auto & s : in2){
        std::cout << "      "<<s<<std::endl; 
    }

    return 0; 
}