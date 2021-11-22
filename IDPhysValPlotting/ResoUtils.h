#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TProfile.h>
#include <memory> 
namespace ResoUtils{
    /// Stolen from IDPVM for consistency. Sorry!

    /// Returns a single-bin iterative RMS. 
    /// The input histogram represents the distribution of pulls / residuals within a given bin. 
    std::pair<double,double> getIterRMS1D(std::shared_ptr<TH1D> input); 

    /// returns a 1D width histogram using iterative RMS. 
    /// The input histogram's x axis is retained, the y axis is assumed to contain the pulls / residuals 
    std::shared_ptr<TH1D> getIterRMS(std::shared_ptr<TH2D> input); 

    /// returns a 2D width histogram using iterative RMS. 
    /// The input histogram's x and y axes are retained, the z axis is assumed to contain the pulls / residuals 
    std::shared_ptr<TH2D> getIterRMS2D(std::shared_ptr<TH3D> input); 

    /// simple profile to histo conversion
    std::shared_ptr<TH1D> profToTH1(std::shared_ptr<TProfile> input); 
}