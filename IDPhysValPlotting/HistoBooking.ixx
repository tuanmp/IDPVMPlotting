
template <class HistType> std::vector <PlotContent<HistType> > HistoBooking::bookThem( 
    const std::vector<std::string> & itemsToDraw, 
    const std::vector<PlotFormat> & entries, 
    const std::vector<std::string> & labels, 
    const std::string & outFileName_base, 
    std::shared_ptr<MultiPagePdfHandle> multiPage,
    CanvasOptions opts){

    /// Prepare the output vector
    std::vector<PlotContent<HistType>> myBooking; 
    myBooking.reserve(itemsToDraw.size()); 

    /// now, loop over every histogram to include, and add each to our task list 
    for (auto & item : itemsToDraw){

        /// First, we identify the output file name, based on the name of the plot
        TString forFname = item;
        forFname = forFname.ReplaceAll("/","_"); 
        forFname = forFname.ReplaceAll(" ","_"); 
        forFname = forFname.ReplaceAll(":","_"); 
        std::string outName = outFileName_base+std::string(forFname);

        // Local copy of the canvas options - used to fine-tune behaviour
        auto LocalOpts = opts; 

        if (forFname.Contains("vs_pt")){
            // draw pt with a log-x
            LocalOpts.XAxis(AxisConfig().ExtraTitleOffset(0.7).Log(true));
        }

        std::vector<Plot<HistType>> thePlots; 
        for (auto & theFormat : entries){
            std::string fname =""; 
            if (!theFormat.CustomString.get("FileName",fname)){
                std::cerr << "Please provide a \"FileName\" extra string with your PlotFormat to ensure drawing. Skipping an entry."<<std::endl;
                continue; 
            }
            thePlots.push_back(Plot<HistType>(LoadFromFile<HistType>(fname,item),theFormat)); 
        }
        std::vector<std::string> myLabels{item}; 
        myLabels.insert(myLabels.end(), labels.begin(),labels.end()); 
        myBooking.push_back(
            PlotContent<HistType>{
               thePlots, myLabels,outName,multiPage,LocalOpts
            }
        );
    }
    return myBooking;  
}