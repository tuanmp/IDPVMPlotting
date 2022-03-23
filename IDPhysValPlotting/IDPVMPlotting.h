#ifndef IDPHYSVALPLOTTING__IDPVMPLOTTING__H
#define IDPHYSVALPLOTTING__IDPVMPLOTTING__H

/// This header declares a set of standardised plotting methods. 
/// Not designed for producing 'final' paper-quality results,
/// but can be useful for quickly drawing stuff 

#include "NtupleAnalysisUtils/NTAUTopLevelIncludes.h"

namespace IDPVMPlotting{

    /// 1D plot with a ratio
    template <class H> void draw1DWithRatio(PlotContent<H> & pc);
    /// 1D plot without a ratio
    template <class H> void draw1DNoRatio(PlotContent<H> & pc);
    /// 1D plot which will automatically draw a ratio if any ratio entries 
    /// are defined in the content
    template <class H> void draw1D(PlotContent<H> & pc){
        if (pc.getRatioEntries().size() != 0) draw1DWithRatio(pc);
        else draw1DNoRatio(pc);
    }
    /// draw a 2D colz plot.
    template<class Histo> void draw2DPlots(PlotContent<Histo>& pc);

    /// vector template for processing multiple plots 
    template<class H> void draw1DNoRatio(std::vector<PlotContent<H>> & pcs);
    template<class H> void draw1DWithRatio(std::vector<PlotContent<H>> & pcs);
    template<class H> void draw1D(std::vector<PlotContent<H>> & pcs);
    template<class H> void draw2DPlots(std::vector<PlotContent<H>> & pcs);

    /// and template recursion for the REALLY lazy! 
    /// ... I'm not judging... ! 
    template<class P, typename... other> void draw1DNoRatio(P & pcs, other... others);
    template<class P, typename... other> void draw1DWithRatio(P & pcs, other... others);
    template<class P, typename... other> void draw1D(P & pcs, other... others);
    template<class P, typename... other> void draw2DPlots(P & pcs, other... others);

}


/// template method implementation
#include "IDPVMPlotting.ixx"

#endif //IDPHYSVALPLOTTING__IDPVMPLOTTING__H
