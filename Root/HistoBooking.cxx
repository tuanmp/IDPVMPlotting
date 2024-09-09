#include "IDPhysValPlotting/HistoBooking.h"

std::vector<PlotContent<TEfficiency>> HistoBooking::bookEffs(
    const std::vector<std::string> &itemsToDraw,
    const std::vector<PlotFormat> &entries,
    const std::vector<std::string> &labels,
    const std::string &outFileName_base,
    std::shared_ptr<MultiPagePdfHandle> multiPage,
    CanvasOptions opts)
{

    /// Prepare the output vector
    std::vector<PlotContent<TEfficiency>> myBooking;
    myBooking.reserve(itemsToDraw.size());

    /// now, loop over every histogram to include, and add each to our task list
    for (auto &item : itemsToDraw)
    {
        /// First, we identify the output file name, based on the name of the plot
        TString forFname = item;
        forFname = forFname.ReplaceAll("/", "_");
        forFname = forFname.ReplaceAll(" ", "_");
        forFname = forFname.ReplaceAll(":", "_");
        std::string outName = outFileName_base + std::string(forFname);

        bool isFake = forFname.Contains("fake");
        bool isEff = forFname.Contains("efficiency");

        // Local copy of the canvas options - used to fine-tune behaviour
        auto LocalOpts = opts;
        if (isFake)
        {
            // Fakes get a log-y
            LocalOpts.YAxis(AxisConfig(LocalOpts.YAxis()).TopPadding(0.5).Min(1e-5).Max(1).Title("Fake rate").Log(true));
        }
        else if (isEff)
        {
            /// Use an epsilon min to avoid catching empty bins in the ratio determination
            LocalOpts.YAxis.modify().TopPadding(0.8).BottomPadding(0.3).Min(1e-8).Max(1).Fixed(false).Title("Efficiency");
            LocalOpts.RatioAxis.modify().Min(.1).Max(3).SymmetrisationPoint(1.).Symmetric(true);
        }
        if (forFname.Contains("vs_pt"))
        {
            // draw pt with a log-x
            LocalOpts.XAxis.modify().ExtraTitleOffset(0.7f).Log(false).Title("p_{T} [GeV]");
        }

        std::vector<Plot<TEfficiency>> thePlots;
        for (auto &theFormat : entries)
        {
            std::string fname = "";
            if (!theFormat.CustomString.get("FileName", fname))
            {
                std::cerr << "Please provide a \"FileName\" extra string with your PlotFormat to ensure drawing. Skipping an entry." << std::endl;
                continue;
            }
            thePlots.push_back(Plot<TEfficiency>(LoadFromFile<TEfficiency>(fname, item), theFormat));
        }
        std::vector<std::string> myLabels{item};
        myLabels.insert(myLabels.end(), labels.begin(), labels.end());
        if (thePlots.size() < 40)
        {
            myBooking.push_back(
                PlotContent<TEfficiency>{
                    thePlots, myLabels, outName, multiPage, LocalOpts});
        }
        else
        {

            myBooking.push_back(
                PlotContent<TEfficiency>{
                    thePlots, std::vector<RatioEntry>{RatioEntry(1, 0), RatioEntry(3, 2)}, myLabels, outName, multiPage, LocalOpts});
        }
    }
    return myBooking;
}

std::shared_ptr<TProfile2D> rebin(std::shared_ptr<TProfile2D> in)
{
    return std::shared_ptr<TProfile2D>(in->Rebin2D(4, 4, "asdaswdads"));
}

std::vector<PlotContent<TProfile2D>> HistoBooking::bookProfs(
    const std::vector<std::string> &itemsToDraw,
    const std::vector<PlotFormat> &entries,
    const std::vector<std::string> &labels,
    const std::string &outFileName_base,
    std::shared_ptr<MultiPagePdfHandle> multiPage,
    CanvasOptions opts)
{

    /// Prepare the output vector
    std::vector<PlotContent<TProfile2D>> myBooking;
    myBooking.reserve(itemsToDraw.size());

    /// now, loop over every histogram to include, and add each to our task list
    for (auto &item : itemsToDraw)
    {

        /// First, we identify the output file name, based on the name of the plot
        TString forFname = item;
        forFname = forFname.ReplaceAll("/", "_");
        forFname = forFname.ReplaceAll(" ", "_");
        forFname = forFname.ReplaceAll(":", "_");
        std::string outName = outFileName_base + std::string(forFname);

        // Local copy of the canvas options - used to fine-tune behaviour
        auto LocalOpts = opts;

        if (forFname.Contains("vs_pt"))
        {
            // draw pt with a log-x
            LocalOpts.XAxis.modify().ExtraTitleOffset(0.7f).Log(true).Title("p_{T} [GeV]");
            if (forFname.Contains("Resolution"))
            {
                LocalOpts.RatioAxis.modify().Max(1.4).Min(0.6);
            }
        }
        LocalOpts.RatioAxis.modify().Min(0.).Max(4.).Fixed(true);
        auto rebinOp = WrapToPostProcessor<TProfile2D, TProfile2D>(rebin);

        std::vector<Plot<TProfile2D>> thePlots;
        for (auto &theFormat : entries)
        {
            std::string fname = "";
            if (!theFormat.CustomString.get("FileName", fname))
            {
                std::cerr << "Please provide a \"FileName\" extra string with your PlotFormat to ensure drawing. Skipping an entry." << std::endl;
                continue;
            }
            auto fmt = theFormat;
            fmt.ExtraDrawOpts("COLZ");
            thePlots.push_back(Plot<TProfile2D>(rebinOp(LoadFromFile<TProfile2D>(fname, item)), fmt));
        }
        std::vector<std::string> myLabels{item};
        myLabels.insert(myLabels.end(), labels.begin(), labels.end());
        if (thePlots.size() < 40)
        {
            myBooking.push_back(
                PlotContent<TProfile2D>{
                    thePlots, myLabels, outName, multiPage, LocalOpts});
        }
        else
        {

            myBooking.push_back(
                PlotContent<TProfile2D>{
                    thePlots, std::vector<RatioEntry>{RatioEntry(1, 0), RatioEntry(3, 2)}, myLabels, outName, multiPage, LocalOpts});
        }
    }
    return myBooking;
}
