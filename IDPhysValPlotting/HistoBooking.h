#ifndef IDPHYSVALPLOTTING__HISTOBOOKING__H
#define IDPHYSVALPLOTTING__HISTOBOOKING__H

/// Helpers for booking large sets of histograms in one go. Useful
/// for PhysVal-style workloads.

#include "NtupleAnalysisUtils/NTAUTopLevelIncludes.h"


namespace HistoBooking{ 
    /// book a vector of plots in one go.
    /// For each PlotFormat, we will look for a custom string called 
    /// "FileName" to determine where to read from. 
    ///
    /// Behaviour is tuned to give a good result in IDPVM
    template <class HistType> std::vector <PlotContent<HistType> > bookThem( 
        const std::vector<std::string> & itemsToDraw, 
        const std::vector<PlotFormat> & entries, 
        const std::vector<std::string> & labels={}, 
        const std::string & outFileName_base="", 
        std::shared_ptr<MultiPagePdfHandle> multiPage=nullptr,
        CanvasOptions opts=CanvasOptions{}); 

    std::vector <PlotContent<TProfile2D> > bookProfs( 
        const std::vector<std::string> & itemsToDraw, 
        const std::vector<PlotFormat> & entries, 
        const std::vector<std::string> & labels={}, 
        const std::string & outFileName_base="", 
        std::shared_ptr<MultiPagePdfHandle> multiPage=nullptr,
        CanvasOptions opts=CanvasOptions{}); 


    /// As above, but will extract efficiencies from an input TEfficiency 
    /// in a TH1D format 
    std::vector <PlotContent<TH1D> > bookEffs( 
        const std::vector<std::string> & itemsToDraw, 
        const std::vector<PlotFormat> & entries, 
        const std::vector<std::string> & labels={}, 
        const std::string & outFileName_base="", 
        std::shared_ptr<MultiPagePdfHandle> multiPage=nullptr,
        CanvasOptions opts=CanvasOptions{}); 

}

/// template method implementation
#include "HistoBooking.ixx"

#endif //IDPHYSVALPLOTTING__HISTOBOOKING__H
