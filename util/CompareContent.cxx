#include "NtupleAnalysisUtils/NTAUTopLevelIncludes.h"
#include <algorithm>

/// Compare the file-content of two ROOT files. 
/// Checks only for object existence, not for equality of the object content. 

int main(int argc, char* argv[]){

    if (argc != 3){
        std::cerr << "Usage: \n\
                      CompareContent <name of first file> <name of second file>"<<std::endl; 
        return 1; 
    }

    /// read filenames from command line 
    const std::string f1 = argv[1]; 
    const std::string f2 = argv[2]; 

    /// Get list of contents of the two files
    auto found1 = PlotUtils::getAllObjectsFromFile<TNamed>(f1);
    auto found2 = PlotUtils::getAllObjectsFromFile<TNamed>(f2);

    /// store for classified output objects
    std::vector<std::string> inBoth{}; 
    std::vector<std::string> in1{}; 
    std::vector<std::string> in2{}; 

    /// copy elements found in both files
    std::copy_if(found1.begin(), found1.end(), std::back_inserter(inBoth), [&found2](const std::string & s1){
        return (std::find(found2.begin(),found2.end(),s1) != found2.end()); 
    }); 
    /// copy elements found only in the first file
    std::copy_if(found1.begin(), found1.end(), std::back_inserter(in1), [&found2](const std::string & s1){
        return (std::find(found2.begin(),found2.end(),s1) == found2.end()); 
    }); 
    /// copy elements found only in the second file 
    std::copy_if(found2.begin(), found2.end(), std::back_inserter(in2), [&found1](const std::string & s1){
        return (std::find(found1.begin(),found1.end(),s1) == found1.end()); 
    }); 
    /// some counters
    size_t nTotal = inBoth.size() + in1.size()+in2.size(); 

    /// report results
    std::cout << "====== Found in BOTH: "<<inBoth.size()<<" / "<<nTotal<<" ================="<<std::endl;
    for (auto & s : inBoth){
        std::cout << "      "<<s<<std::endl; 
    }
    std::cout << "====== Found ONLY IN "<<f1<<": "<<in1.size()<<" / "<<nTotal<<" ================="<<std::endl;
    for (auto & s : in1){
        std::cout << "      "<<s<<std::endl; 
    }
    std::cout << "====== Found ONLY IN "<<f2<<": "<<in2.size()<<" / "<<nTotal<<" ================="<<std::endl;
    for (auto & s : in2){
        std::cout << "      "<<s<<std::endl; 
    }

    return 0; 
}