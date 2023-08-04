
// This is a simple example of how to draw things with the PlotContent and CanvasOptions classes

template <class H> void IDPVMPlotting::draw1DWithRatio(PlotContent<H> & pc){
    SetAtlasStyle();
    // first, fill the histos we want.
    // This manual call is not strictly needed,
    // but having it here is tidyer for debugging
    pc.populateAll();
    // now, we can get the filled content
    std::vector<Plot<H>> plots = pc.getPlots();
    std::vector<Plot<ratioType<H>>> ratios = pc.getRatios();

    //getting the chi2 and KS quality test results
    std::vector<float> chi2probs = pc.getQualityTests("chi2"); 	   
    std::vector<float> ksprobs = pc.getQualityTests("KS"); 	   

    // read the options - they determine the details of what we will draw
    CanvasOptions canvasOpts = pc.getCanvasOptions();

    // now we can book our canvas with its sub-pads
    MultiPadCanvas mpc = PlotUtils::prepareTwoPadCanvas(canvasOpts); 

    // start to populate the top pad
    mpc.getPad(0)->cd();

    // first, draw an empty frame, with the appropriate range and 
    // axis labels 
    PlotUtils::drawTopFrame(plots,canvasOpts);

    /// Draw legend and labels 
    std::shared_ptr<TLegend>  leg {PlotUtils::drawLegend(plots, canvasOpts)};
    if (plots.size() > 5) leg->SetNColumns(2);

    PlotUtils::drawLabels(pc.getLabels(), canvasOpts);

    //Draw text for quality tests
    auto latexformat = DrawObjectFormat().Color(kBlack).Font(43).Size(17);    
    if(chi2probs[0] < 0.1) latexformat.Color(kRed+1);
    else latexformat.Color(kGreen+2);
    std::string chi2text = "Chi2 p-value = " + std::to_string(chi2probs[0]); 
    PlotUtils::drawTLatex(0.15, 0.65, chi2text, latexformat);
    if(ksprobs[0] < 0.1) latexformat.Color(kRed+1);
    else latexformat.Color(kGreen+2);
    std::string kstext = "KS p-value = " + std::to_string(ksprobs[0]); 
    PlotUtils::drawTLatex(0.15, 0.57, kstext, latexformat);

    // now draw the plots 
    for (auto & plot : plots){
        plot->Draw(std::string ("SAME" + plot.plotFormat().ExtraDrawOpts()).c_str());
    }
    // redraw the axis in case we overlap with it 
    gPad->RedrawAxis();

    // on to the ratios! 
    mpc.getPad(1)->cd();
    PlotUtils::drawRatioFrame(ratios,canvasOpts);
    for (auto & r : ratios){
        r->Draw(std::string ("SAME" + r.plotFormat().ExtraDrawOpts()).c_str());
    }
    // aaaand save. Done! 
    PlotUtils::saveCanvas(mpc.getCanvas(), pc.getFileName(), canvasOpts);
    if (pc.getMultiPagePdfHandle()) pc.getMultiPagePdfHandle()->saveCanvas(mpc.getCanvas()); 
}

template <class H> void IDPVMPlotting::draw1DNoRatio(PlotContent<H> & pc){
    SetAtlasStyle();
    // first, fill the histos we want 
    pc.populateAll();
    // now, we can get the filled content
    std::vector<Plot<H>> plots = pc.getPlots();

    // read the options - they will do a lot for us 
    CanvasOptions canvasOpts = pc.getCanvasOptions();

    std::shared_ptr<TCanvas> can = PlotUtils::prepareCanvas(canvasOpts);

    // start to populate the top pad
    can->cd();
    // first, draw an empty frame, with the appropriate range and 
    // axis labels 
    PlotUtils::drawTopFrame(plots,canvasOpts);

    /// Draw legend and labels 
    std::shared_ptr<TLegend>  leg {PlotUtils::drawLegend(plots,canvasOpts)};
    if (plots.size() > 5) leg->SetNColumns(2);

    PlotUtils::drawLabels(pc.getLabels(),canvasOpts);

    // now draw the plots 
    for (auto & plot : plots){
        plot->Draw(std::string ("SAME" + plot.plotFormat().ExtraDrawOpts()).c_str());
    }
    // redraw the axis in case we overlap with it 
    gPad->RedrawAxis();

    // aaaand save. Done! 
    PlotUtils::saveCanvas(can, pc.getFileName(), canvasOpts);
    if (pc.getMultiPagePdfHandle()) pc.getMultiPagePdfHandle()->saveCanvas(can); 
}


template <class Histo> void IDPVMPlotting::draw2DPlots(PlotContent<Histo>& pc){
    SetAtlasStyle();
    pc.populateAll();
    CanvasOptions canvasOpts = pc.getCanvasOptions();   

    std::shared_ptr<TCanvas> can = PlotUtils::prepareCanvas(canvasOpts);
    
    auto plots = pc.getPlots();

    std::vector<TLatex*> LegLabels; 
    auto first = plots.front(); 
    size_t iter = 0; 
    for (auto& plot : plots){
        ++iter; 
        // plot->Set
        std::vector<Plot<Histo>> forRange {plot}; 
        PlotUtils::drawTopFrame(forRange, canvasOpts); 
        auto range = PlotUtils::getZRange(forRange,canvasOpts);
        PlotFormat& fmt = plot.plotFormat();
        LegLabels.push_back(PlotUtils::drawTLatex(canvasOpts.LegendStartX(),canvasOpts.LegendStartY(), fmt.LegendTitle()));
        
        plot->SetMinimum(range.first); 
        plot->SetMaximum(range.second);
        if (fmt.paletteFor2DPlotting().isValid()){
            fmt.paletteFor2DPlotting.modify().setPalette();
            plot->SetContour(fmt.paletteFor2DPlotting().getContour());
        } else plot->SetContour(2000);
        
        std::string theOpts = "colz"; 
        if (fmt.ExtraDrawOpts.isUserSet()) theOpts = fmt.ExtraDrawOpts(); 
        plot->Draw(theOpts.c_str());        
        gPad->SetRightMargin(0.17);
        auto labelsToDraw = pc.getLabels(); 
        labelsToDraw.push_back(fmt.LegendTitle()); 
        PlotUtils::drawLabels(labelsToDraw, canvasOpts); 
        PlotUtils::saveCanvas (can, pc.getFileName()+"_"+std::to_string(iter), canvasOpts);
        if (pc.getMultiPagePdfHandle()) pc.getMultiPagePdfHandle()->saveCanvas(can); 
        if (iter > 1){
            // ugly workaround while I fix NTAU's insistence on a TH1 return type... 
            Plot<Histo> ratio {CopyExisting(plot), fmt};
            ratio->Divide(first());
            std::vector<Plot<Histo>> forRatioRange {ratio}; 
            auto ratioOpts = canvasOpts; 
            ratioOpts.ZAxis.modify().Symmetric(true).SymmetrisationPoint(1.); 
            PlotUtils::drawTopFrame(forRange, ratioOpts); 
            auto RatioRange = PlotUtils::getRatioRange(forRange,ratioOpts);
            ratio->SetMinimum(RatioRange.first); 
            ratio->SetMaximum(RatioRange.second); 
           if (fmt.paletteFor2DPlotting().isValid()) {
                fmt.paletteFor2DPlotting.modify().setPalette();
                ratio->SetContour(fmt.paletteFor2DPlotting().getContour());
            } else ratio->SetContour(2000);
            ratio->Draw("colz");      
            ratio->GetZaxis()->SetTitle(canvasOpts.RatioAxis().Title().c_str()); 
            ratio->GetZaxis()->SetTitleOffset(1.2 * ratio->GetZaxis()->GetTitleOffset()); 
            gPad->SetRightMargin(0.17); 
            auto labels = pc.getLabels(); 
            labels.push_back("Ratio " + fmt.LegendTitle()+" versus " + first.plotFormat().LegendTitle()); 
            PlotUtils::drawLabels(labels, canvasOpts); 
            PlotUtils::saveCanvas (can, pc.getFileName()+"_"+std::to_string(iter)+"_Ratio", canvasOpts);
            if (pc.getMultiPagePdfHandle()) pc.getMultiPagePdfHandle()->saveCanvas(can);   
        } 
    }
    PlotUtils::drawLabels(pc.getLabels(), canvasOpts);
}


template<class H> void IDPVMPlotting::draw1DNoRatio(std::vector<PlotContent<H>> & pcs){
    for (auto & pc : pcs) draw1DNoRatio(pc); 
}
template<class H> void IDPVMPlotting::draw1DWithRatio(std::vector<PlotContent<H>> & pcs){
    for (auto & pc : pcs) draw1DWithRatio(pc);     
}
template<class H> void IDPVMPlotting::draw1D(std::vector<PlotContent<H>> & pcs){
    for (auto & pc : pcs) draw1D(pc);     
}
template<class H> void IDPVMPlotting::draw2DPlots(std::vector<PlotContent<H>> & pcs){
    for (auto & pc : pcs) draw2DPlots(pc);     
}

/// and template recursion for the REALLY lazy! 
/// ... I'm not judging... ! 
template<class P, typename... other> void IDPVMPlotting::draw1DNoRatio(P & pcs, other... others){
    draw1DNoRatio(pcs); 
    draw1DNoRatio(others...); 
}
template<class P, typename... other> void IDPVMPlotting::draw1DWithRatio(P & pcs, other... others){
    draw1DWithRatio(pcs); 
    draw1DWithRatio(others...); 
}
template<class P, typename... other> void IDPVMPlotting::draw1D(P & pcs, other... others){
    draw1D(pcs); 
    draw1D(others...); 
}
template<class P, typename... other> void IDPVMPlotting::draw2DPlots(P & pcs, other... others){
    draw2DPlots(pcs); 
    draw2DPlots(others...); 
}


