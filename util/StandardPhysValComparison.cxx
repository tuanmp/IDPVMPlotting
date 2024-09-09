
#include "IDPhysValPlotting/HistoBooking.h"
#include "IDPhysValPlotting/IDPVMHistoPaths.h"
#include "IDPhysValPlotting/IDPVMPlotting.h"
#include "TProfile2D.h"
#include <iostream>
#include <nlohmann/json.hpp>

int main(int argc, char *argv[])
{

    ///////////////////////////////////////////////////////////
    /// In this first block, we configure what to compare and
    /// how to format and label our plots.
    ///
    /// TODO: If people prefer, I'm happy to provide a json
    /// or other interface for this. Let me know.
    //////////////////////////////////////////////////////////
    // if (argc > 3){
    //     std::cerr << "Usage: \n\
    //                   CompareContent <name of first file> <name of second file>"<<std::endl;
    //     return 1;
    // }

    TColor::InitializeColors();

    /// read filenames from command line
    // const std::string f1 = argv[1];
    // const std::string f2 = argv[2];
    // const std::string f3 = argv[3];
    // const std::string f4 = argv[4];
    const std::string f = argv[1];

    /// A 3-color scheme that we used for the CPU PUB note.
    /// Feel free to use this (or any other colours you like!)
    // Int_t colRef = TColor::GetFreeColorIndex();
    // TColor *c1 = new TColor(colRef, 0.42, 0.7, 0.32);
    // Int_t colTest1 = TColor::GetFreeColorIndex();
    // TColor *c2 = new TColor(colTest1, 0.12, 0.47, 0.71);
    // Int_t colTest2 = TColor::GetFreeColorIndex();
    // TColor *c3 = new TColor(colTest2, 0.65, 0.22, 0.83);
    // Int_t colTest3 = TColor::GetFreeColorIndex();
    // TColor *c4 = new TColor(colTest3, .863, 0.078, 0.235);

    std::ifstream configFile(f);
    if (!configFile.is_open())
    {
        std::cerr << "Counld not open config file" << std::endl;
        return 1;
    }

    nlohmann::json config;
    configFile >> config;

    std::vector<PlotFormat> formats;
    for (const auto &item : config["idpvm"])
    {
        PlotFormat format = PlotFormat().Color(item["Color"]).MarkerStyle(item["MakerStyle"]).LegendOption("PL").LegendTitle(item["LegendTitle"]).ExtraDrawOpts("LP").LineWidth(item["LineWidth"]).CustomString("FileName", item["file"]);
        formats.push_back(format);
    }

    /// This steers which entries to plot on the canvases.
    /// One entry per sample.
    /// The file to read from is provided as the "FileName" argument

    /// In this example, we configure two entries (this was used to validate the tracking geometry updates).
    /// Can just as easily do 3,4,... just make sure to give them clear titles, and distinguishable colours.

    /// The first entry is used as reference for all the ratios that will be drawn.
    /// For the meaning of the various arguments: See NTAU tutorial @ https://gitlab.cern.ch/Atlas-Inner-Tracking/NtupleAnalysisUtils_tutorial
    /// In particular, check out the SWAN notebooks!
    // std::vector<PlotFormat> formats{
    //     PlotFormat().Color(5).MarkerStyle(kFullSquare).LegendOption("PL").LegendTitle("Baseline").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName", f1), // here you can set the file to load!

    //     PlotFormat().Color(6).MarkerStyle(kFullCircle).LegendOption("PL").LegendTitle("Speedup").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName", f2), // here you can set the file to load!

    //     PlotFormat().Color(7).MarkerStyle(kFullTriangleUp).LegendOption("PL").LegendTitle("Ambi").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName", f3),
    //     PlotFormat().Color(8).MarkerStyle(kFullCrossX).LegendOption("PL").LegendTitle("No reuse").ExtraDrawOpts("LP").LineWidth(2).CustomString("FileName", f4),
    //     //.CustomString("FileName","/eos/user/g/goblirsc/Tracking/PhysValPlottingExampleFiles/SglMu_master_noBL.IDPVM.root"), // here you can set the file to load!
    // };

    /// Here, you can tune the appearance of the canvas.
    /// For example, this allows you to override axis ranges (or change how they are detected), manually enforce axis labels,
    /// steer the appearance of legends or palettes, the ATLAS label, etc.
    auto myOpts = CanvasOptions().YAxis(AxisConfig().TopPadding(0.8).BottomPadding(0.15).Min(0)).RatioAxis(AxisConfig().Title("Ratio w.r.t Ref").Symmetric(true).SymmetrisationPoint(1.)).ColorPalette(kBlackBody);

    /// Here you can choose the file name for the output multi page PDF file.
    /// This example will generate a "CheckBLayerGone.pdf" in the default location ("$TestArea/../Plots/<date>/")
    auto multi = PlotUtils::startMultiPagePdfFile("CheckBLayerGone");

    /// This is the set of labels to draw on the plot.
    /// Use this to show what you are testing, which process this is, the pileup, etc.
    /// They will be drawn on your canvas one atop the other.
    /// No need to include the ATLAS label, this is handled automatically, as is the lumi/sqrt{s}.
    /// Both can be changed in the CanvasOptions if desired.
    std::vector<std::string> labels{"ttbar, <#mu>=200"};

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
    auto efficiencies = HistoBooking::bookEffs(interestingEffs, formats, labels, "EffCheck_", multi, myOpts);
    auto efficiencies_Loose = HistoBooking::bookEffs(interestingEffs_Loose, formats, labels, "EffCheck_", multi, myOpts);

    /// Hits and holes - selected
    auto hitsHoles_Selected = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Selected()), formats, labels, "HitHoleCheck_Selected_", multi, myOpts);
    auto hitsHoles_Selected_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Selected_Loose()), formats, labels, "HitHoleCheck_Selected_", multi, myOpts);

    /// Hits and holes - matched
    auto hitsHoles_Matched = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Matched()), formats, labels, "HitHoleCheck_Matched_", multi, myOpts);
    auto hitsHoles_Matched_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Matched_Loose()), formats, labels, "HitHoleCheck_Matched_", multi, myOpts);

    /// Tracks in Jets - Profiles
    auto tracksInJets = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInJets()), formats, labels, "TracksInJets_", multi, myOpts);
    auto tracksInJets_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInJets_Loose()), formats, labels, "TracksInJets_", multi, myOpts);

    /// Tracks in Jets - Efficiencies
    auto tracksInJets_effs = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInJets()), formats, labels, "TracksInJets_", multi, myOpts);
    auto tracksInJets_effs_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInJets_Loose()), formats, labels, "TracksInJets_", multi, myOpts);

    /// Tracks in BJets - Profiles
    auto tracksInBJets = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets()), formats, labels, "TracksInBJets_", multi, myOpts);
    auto tracksInBJets_Loose = HistoBooking::bookThem<TProfile>(IDPVMHistoPaths::scanPath<TProfile>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets_Loose()), formats, labels, "TracksInBJets_", multi, myOpts);

    /// Tracks in BJets - Efficiencies
    auto tracksInBJets_effs = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets()), formats, labels, "TracksInBJets_", multi, myOpts);
    auto tracksInBJets_effs_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_tracksInBJets_Loose()), formats, labels, "TracksInBJets_", multi, myOpts);

    /// Hits and holes - 2D
    auto hitsHoles_Selected2D = HistoBooking::bookThem<TProfile2D>(IDPVMHistoPaths::scanPath<TProfile2D>(fileToCheck, IDPVMHistoPaths::path_hitsOnTrack_Selected()), formats, labels, "HitHoleCheck_Selected2D_", multi, myOpts);

    /// 1D track parameters
    auto params = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(fileToCheck, IDPVMHistoPaths::path_params()), formats, labels, "ParamCheck_", multi, myOpts);
    auto params_Loose = HistoBooking::bookThem<TH1F>(IDPVMHistoPaths::scanPath<TH1F>(fileToCheck, IDPVMHistoPaths::path_params_Loose()), formats, labels, "ParamCheck_", multi, myOpts);

    /// fake rate Unlinked
    auto unlinkedRate = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_unlinked()), formats, labels, "UnlinkedFakeRate_", multi, myOpts);
    auto unlinkedRate_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_unlinked_Loose()), formats, labels, "UnlinkedFakeRate_", multi, myOpts);

    /// fake rate
    auto fake = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_fake()), formats, {}, "FakeRate_", multi, myOpts);
    auto fake_Loose = HistoBooking::bookEffs(IDPVMHistoPaths::scanPath<TEfficiency>(fileToCheck, IDPVMHistoPaths::path_fake_Loose()), formats, {}, "FakeRate_", multi, myOpts);

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
    auto resos = HistoBooking::bookThem<TH1F>(interestingResos, formats, labels, "ResoCheck_", multi, myOpts);
    auto resos_Loose = HistoBooking::bookThem<TH1F>(interestingResos_Loose, formats, labels, "ResoCheck_", multi, myOpts);

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
