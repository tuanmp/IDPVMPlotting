#include "IDPhysValPlotting/MuonMomentumHelpers.h"


// Custom 2D plotting method, adding a few custom tweaks beyond what the defaults provide 

namespace MuonMomentumHelpers{ 

    Selection<MuonMomentumCalibrationTreeExtended> getPtWindow_Pos(double lo, double hi){
        return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (t.Pos_CB_Pt() > lo && t.Pos_CB_Pt() < hi);}); 
    }
    Selection<MuonMomentumCalibrationTreeExtended> getPtWindow_Neg(double lo, double hi){
        return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (t.Neg_CB_Pt() > lo && t.Neg_CB_Pt() < hi);}); 
    }

    Selection<MuonMomentumCalibrationTreeExtended> getAbsEtaWindow_Pos(double lo, double hi){
        return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (std::abs(t.Pos_CB_Eta()) >  lo && std::abs(t.Pos_CB_Eta()) < hi);}); 
    }
    Selection<MuonMomentumCalibrationTreeExtended> getAbsEtaWindow_Neg(double lo, double hi){
        return Selection<MuonMomentumCalibrationTreeExtended>([hi,lo](MuonMomentumCalibrationTreeExtended& t){ return (std::abs(t.Neg_CB_Eta()) >  lo && std::abs(t.Neg_CB_Eta()) < hi);}); 
    }


    void drawReso2D(PlotContent<TH2D>& pc){
        SetAtlasStyle();
        pc.populateAll();
        CanvasOptions canvasOpts = pc.getCanvasOptions();
        // gStyle->SetPalette(kInvertedDarkBodyRadiator);
        // TColor::InvertPalette(); 


        gStyle->SetPalette(canvasOpts.ColorPalette());
        static Int_t  colors[2000];
        static Bool_t initialized = kFALSE;

        Double_t Red[7]    = { 1.00, 0.85, 0.6, 0.9, 0.8, 0.5, 0.2    };
        Double_t Green[7]  = { 1.00, 0.85, 0.2, 0.3, 0.7, 0.7, 0.8      };
        Double_t Blue[7]   = { 1.00, 1.00, 0.8, 0.3, 0.2, 0.2, 0.1    };
        Double_t Length[7] = { 0.00, 0.05, 0.2, 0.4, 0.6, 0.8, 1.0     };

        if(!initialized){
            Int_t FI = TColor::CreateGradientColorTable(7,Length,Red,Green,Blue,2000);
            for (int i=0; i<2000; i++) colors[i] = FI+i;
            initialized = kTRUE;
        //   return ;
        }
        gStyle->SetPalette(2000,colors);

        std::shared_ptr<TCanvas> can = PlotUtils::prepareCanvas(canvasOpts);
        
        auto plots = pc.getPlots();

        std::vector<TLatex*> LegLabels; 
        auto first = plots.front(); 
        size_t iter = 0; 
        for (auto& plot : plots){
            ++iter; 
            // plot->Set
            std::vector<Plot<TH2D>> forRange {plot}; 
            auto theFrame = PlotUtils::drawTopFrame(forRange, canvasOpts); 
            auto range = PlotUtils::getZRange(forRange,canvasOpts);
            LegLabels.push_back(PlotUtils::drawTLatex(canvasOpts.LegendStartX(),canvasOpts.LegendStartY(), plot.plotFormat().LegendTitle()));
            // if (range.first < canvasOpts.ZAxis().Min()) plot->SetMinimum(canvasOpts.ZAxis().Min()); 
            plot->SetMinimum(range.first); 
            if (plot->GetMinimum() < 0) plot->SetMinimum(0); 
            plot->SetMaximum(range.second); 
            std::cout << range.first<<" to "<<range.second<<std::endl; 
            plot->SetContour(2000);
            // if (plot->GetMinimum() > 0) gPad->SetLogz(); 
            plot->Draw("colz");        
            // Plot<TH1D> profx{CopyExisting<TH1D>(plot->ProfileX()), PlotFormat().MarkerStyle(kOpenCircle).MarkerColor(kGray+2).LegendOption("PL").LegendTitle("Mean value").MarkerSize(0.4)}; 
            // Plot<TH1D> medx{CopyExisting<TH1D>(getMedian(plot)), PlotFormat().MarkerStyle(kOpenSquare).MarkerColor(kGray+2).LegendOption("PL").LegendTitle("Median value").MarkerSize(0.4)}; 
            // profx->Draw("SAMEPL"); 
            // medx->Draw("SAMEPL"); 
            if (plot->GetNbinsX() < 15 && plot->GetNbinsY() < 15){
                gStyle->SetPaintTextFormat(".2f");  
                plot->SetMarkerColor(kGray+2); 
                plot->Draw("SAMETEXT");      
            }
            // PlotUtils::drawLegend(std::vector<Plot<TH1D>>{profx,medx}, canvasOpts); 
            gPad->SetRightMargin(0.17);
            auto labelsToDraw = pc.getLabels(); 
            labelsToDraw.push_back(plot.plotFormat().LegendTitle()); 
            PlotUtils::drawLabels(labelsToDraw, canvasOpts); 
            PlotUtils::saveCanvas (can, pc.getFileName()+"_"+std::to_string(iter), canvasOpts);
            if (pc.getMultiPagePdfHandle()) pc.getMultiPagePdfHandle()->saveCanvas(can); 
        }
        PlotUtils::drawLabels(pc.getLabels(),canvasOpts);
    }

    
    std::shared_ptr<TH2D> normaliseInBin(std::shared_ptr<TH2D> in){
        int ny = in->GetNbinsY(); 
        for (int kx = 1; kx <= in->GetNbinsX(); ++kx){
            double integ = in->Integral(kx,kx,1,ny); 
            double normFact= 0; 
            if (integ !=0) normFact=1/integ; 
            for (int ky = 0; ky < ny+1; ++ky){
                in->SetBinContent(kx,ky,in->GetBinContent(kx,ky)*normFact); 
                in->SetBinError(kx,ky,in->GetBinError(kx,ky)*normFact); 
            }
        }
        return in; 
    }
    TH1D* getMedian(Plot<TH2D> h2){
        int ny = h2->GetNbinsY(); 
        TH1D* profx = h2->ProjectionX(); 
        for (int kx = 1; kx <= h2->GetNbinsX(); ++kx){
            double integ = h2->Integral(kx,kx,1,ny); 
            double sum = 0; 
            for (int ky = 0; ky < ny+1; ++ky){
                sum += h2->GetBinContent(kx,ky); 
                if (sum >= 0.5 * integ){
                    profx->SetBinContent(kx,h2->GetYaxis()->GetBinCenter(ky));
                    profx->SetBinError(kx,h2->GetYaxis()->GetBinWidth(ky));  
                    break; 
                }
                profx->SetBinContent(kx,h2->GetYaxis()->GetBinCenter(ny));
                profx->SetBinError(kx,h2->GetYaxis()->GetBinWidth(ny));  
            }
        }
        return profx; 
    }
    std::shared_ptr<TH2D> ProftoTH2D(std::shared_ptr<TProfile2D> in){

        std::shared_ptr<TH2D> res = std::make_shared<TH2D>("asdhkjfa","asdjkasjddas",in->GetXaxis()->GetNbins(), in->GetXaxis()->GetXmin(), in->GetXaxis()->GetXmax(), 
                                                                                    in->GetYaxis()->GetNbins(), in->GetYaxis()->GetXmin(), in->GetYaxis()->GetXmax()); 
        res->GetXaxis()->SetTitle(in->GetXaxis()->GetTitle()); 
        res->GetYaxis()->SetTitle(in->GetYaxis()->GetTitle()); 
        res->Sumw2(); 
        res->SetDirectory(0); 
        res->Reset();
        for (int k = 1; k < in->GetNbinsX()+1; ++k){
            for (int l = 1; l < in->GetNbinsY()+1; ++l){
                res->SetBinContent(k,l,in->GetBinContent(k,l)); 
                res->SetBinError(k,l,in->GetBinError(k,l)); 
            }
        }
        return res; 
    }
}