
#include "IDPhysValPlotting/HistoBooking.h"
#include "IDPhysValPlotting/IDPVMHistoPaths.h"
#include "IDPhysValPlotting/IDPVMPlotting.h"
#include "TProfile2D.h"
#include <iostream>
#include <nlohmann/json.hpp>

int main(int, char *argv[])
{

    ///////////////////////////////////////////////////////////
    /// In this first block, we configure what to compare and
    /// how to format and label our plots.
    ///
    /// TODO: If people prefer, I'm happy to provide a json
    /// or other interface for this. Let me know.
    //////////////////////////////////////////////////////////

    TColor::InitializeColors();

    /// read filenames from command line
    const std::string f = argv[1];

    /// A 3-color scheme that we used for the CPU PUB note.
    /// Feel free to use this (or any other colours you like!)

    std::ifstream configFile(f);
    if (!configFile.is_open())
    {
        std::cerr << "Counld not open config file" << std::endl;
        return 1;
    }

    nlohmann::json config;
    configFile >> config;
    std::string outputDir = config.value("OutputDir", "");

    std::vector<PlotFormat> formats;
    for (const auto &item : config["idpvm"])
    {
        PlotFormat format = PlotFormat()
                                .Color(item["Color"])
                                .MarkerStyle(item["MakerStyle"])
                                .LegendOption("PL")
                                .LegendTitle(item["LegendTitle"])
                                .ExtraDrawOpts("LP")
                                .LineWidth(item["LineWidth"])
                                .CustomString("FileName", item["file"]);
        formats.push_back(format);
    }

    /// Here, you can tune the appearance of the canvas.
    /// For example, this allows you to override axis ranges (or change how they are detected), manually enforce axis labels,
    /// steer the appearance of legends or palettes, the ATLAS label, etc.
    auto myOpts = CanvasOptions()
                      .YAxis(AxisConfig()
                                 .TopPadding(0.8)
                                 .BottomPadding(0.15)
                                 .Min(0))
                      .RatioAxis(AxisConfig()
                                     //  .Title("Ratio w.r.t Ref")
                                     .Symmetric(true)
                                     .SymmetrisationPoint(1.))
                      .ColorPalette(kBlackBody)
                      .LabelLumiTag(config.value("lumiTag", "139 fb^{-1}"))
                      .LabelSqrtsTag(config.value("sqrtTag", "13 TeV"))
                      .LabelStatusTag(config.value("statusTag", "Internal"))
                      .OutputDir(outputDir);

    /// Here you can choose the file name for the output multi page PDF file.
    /// This example will generate a "CheckBLayerGone.pdf" in the default location ("$TestArea/../Plots/<date>/")
    auto multi = PlotUtils::startMultiPagePdfFile("all_plots", myOpts);

    /// This is the set of labels to draw on the plot.
    /// Use this to show what you are testing, which process this is, the pileup, etc.
    /// They will be drawn on your canvas one atop the other.
    /// No need to include the ATLAS label, this is handled automatically, as is the lumi/sqrt{s}.
    /// Both can be changed in the CanvasOptions if desired.
    std::vector<std::string> labels = config.value("labels", std::vector<std::string>{}); //{"t#bar{t}, #sqrt{s}=14 GeV, #langle#mu#rangle=200"};

    ///////////////////////////////////////////////////////////
    /// Now, we decide which items to actually draw comparisons for.
    /// By default, we are a bit selective to limit file sizes.
    /// We could also tell bookThem to start from the "" directory
    /// of the input file, in which case it would pick up
    /// *everything* of the right type.
    /// Note that booking does *not* yet cause any overhead.
    /// Histograms are only loaded when actually needed,
    /// so it is sufficient to comment the drawing command
    /// farther below to suppress certain plots.
    //////////////////////////////////////////////////////////

    /// Perform a look-up of the available histograms based on the first file in our comparison.
    std::string fileToCheck;
    formats.front().CustomString.get("FileName", fileToCheck);

    /// Pick up the sets of items to plot.
    /// bookEffs and bookThem will produce vectors of 'PlotContent'
    /// objects, which each encapsulate a plot to be drawn.
    /// This just defines a workload, nothing is actually run yet.

    /// remove the efficiency plot that causes a crash
    auto listOfEffs = IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_Efficiency());
    std::vector<std::string> interestingEffs;
    std::copy_if(listOfEffs.begin(), listOfEffs.end(), std::back_inserter(interestingEffs),
                 [](const std::string &histName)
                 {
                     std::cout << "histName \t" << histName << std::endl;
                     if (histName.find("vs_pteta") != std::string::npos)
                         return false;
                     return true;
                 });

    auto listOfEffs_Loose = IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_Efficiency_Loose());
    std::vector<std::string> interestingEffs_Loose;
    std::copy_if(listOfEffs_Loose.begin(), listOfEffs_Loose.end(), std::back_inserter(interestingEffs_Loose),
                 [](const std::string &histName)
                 {
                     std::cout << "histName \t" << histName << std::endl;
                     if (histName.find("vs_pteta") != std::string::npos)
                         return false;
                     return true;
                 });
    /// Efficiencies
    auto efficiencies = HistoBooking::bookEffs(interestingEffs, formats, labels, multi, myOpts);
    auto efficiencies_Loose = HistoBooking::bookEffs(interestingEffs_Loose, formats, labels, multi, myOpts);

    /// Hits and holes - selected
    auto hitsHoles_Selected = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Selected()), formats, labels, multi, myOpts);
    auto hitsHoles_Selected_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Selected_Loose()), formats, labels, multi, myOpts);

    /// Hits and holes - matched
    auto hitsHoles_Matched = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Matched()), formats, labels, multi, myOpts);
    auto hitsHoles_Matched_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Matched_Loose()), formats, labels, multi, myOpts);

    /// Tracks in Jets - Profiles
    auto tracksInJets = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInJets()), formats, labels, multi, myOpts);
    auto tracksInJets_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInJets_Loose()), formats, labels, multi, myOpts);

    /// Tracks in Jets - Efficiencies
    auto tracksInJets_effs = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInJets()), formats, labels, multi, myOpts);
    auto tracksInJets_effs_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInJets_Loose()), formats, labels, multi, myOpts);

    /// Tracks in BJets - Profiles
    auto tracksInBJets = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets()), formats, labels, multi, myOpts);
    auto tracksInBJets_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets_Loose()), formats, labels, multi, myOpts);

    /// Tracks in BJets - Efficiencies
    auto tracksInBJets_effs = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets()), formats, labels, multi, myOpts);
    auto tracksInBJets_effs_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets_Loose()), formats, labels, multi, myOpts);

    /// Hits and holes - 2D
    // auto hitsHoles_Selected2D = HistoBooking::bookThem<TProfile2D>(IDPVMHistoPaths::scanPath<TProfile2D>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Selected()), formats, labels, "HitHoleCheck_Selected2D_", multi, myOpts);

    /// 1D track parameters
    auto params = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(fileToCheck, IDPVMHistoPaths::path_params()), formats, labels, multi, myOpts);
    auto params_Loose = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(fileToCheck, IDPVMHistoPaths::path_params_Loose()), formats, labels, multi, myOpts);

    /// fake rate Unlinked
    auto unlinkedRate = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_unlinked()), formats, labels, multi, myOpts);
    auto unlinkedRate_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_unlinked_Loose()), formats, labels, multi, myOpts);

    /// fake rate
    auto fake = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_fake()), formats, {}, multi, myOpts);
    auto fake_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_fake_Loose()), formats, {}, multi, myOpts);

    /// find the resolutions that are actually interesting - veto pull projections to limit file size
    auto listOfResos = IDPVMHistoPaths::scanPath<TH1F>(fileToCheck, IDPVMHistoPaths::path_resolutions());
    std::vector<std::string> interestingResos;
    std::copy_if(listOfResos.begin(), listOfResos.end(), std::back_inserter(interestingResos),
                 [](const std::string &histName)
                 {
                     if (histName.find("resProjection") != std::string::npos)
                         return false;
                     if (histName.find("pullProjection") != std::string::npos)
                         return false;
                     return true;
                 });

    auto listOfResos_Loose = IDPVMHistoPaths::scanPath<TH1F>(fileToCheck, IDPVMHistoPaths::path_resolutions_Loose());
    std::vector<std::string> interestingResos_Loose;
    std::copy_if(listOfResos_Loose.begin(), listOfResos_Loose.end(), std::back_inserter(interestingResos_Loose),
                 [](const std::string &histName)
                 {
                     if (histName.find("resProjection") != std::string::npos)
                         return false;
                     if (histName.find("pullProjection") != std::string::npos)
                         return false;
                     return true;
                 });
    // now book the reso items we kept
    auto resos = HistoBooking::bookThem<TH1F>(interestingResos, formats, labels, multi, myOpts);
    auto resos_Loose = HistoBooking::bookThem<TH1F>(interestingResos_Loose, formats, labels, multi, myOpts);

    ///////////////////////////////////////////////////////////
    /// Finally, we draw everything. Note that draw1D and
    /// draw2DPlots can each take an arbitrarily long set of inputs,
    /// feel free to plug in any extra stuff you like!
    /// This will lead to the histos being loaded and drawn
    /// together with the relevant ratios etc.
    ///
    /// Also note that for certain specialised plots,
    /// it can be useful to write a short custom drawing
    /// script instead of resorting to the pre-made draw1D.
    //////////////////////////////////////////////////////////

    // Writing this in a form where it is easy to comment undesired entries.
    IDPVMPlotting::draw1D(
        efficiencies,
        efficiencies_Loose,
        resos,
        resos_Loose,
        params,
        params_Loose,
        hitsHoles_Selected,
        hitsHoles_Selected_Loose,
        hitsHoles_Matched,
        hitsHoles_Matched_Loose,
        unlinkedRate,
        unlinkedRate_Loose,
        fake,
        fake_Loose
        // tracksInJets,
        // tracksInJets_Loose,
        // tracksInJets_effs,
        // tracksInJets_effs_Loose,
        // tracksInBJets,
        // tracksInBJets_Loose,
        // tracksInBJets_effs,
        // tracksInBJets_effs_Loose
    );
    // IDPVMPlotting::draw2DPlots(
    // 		       hitsHoles_Selected2D
    // 		       );
    return 0;
}
