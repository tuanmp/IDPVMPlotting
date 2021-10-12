#include "IDPhysValPlotting/ResoUtils.h"

namespace ResoUtils{
        /// Stolen from IDPVM for consistency. Sorry!
    std::pair<double,double> getIterRMS1D(std::shared_ptr<TH1D> input){
    // evaluate  mean and RMS using iterative converfgence:
        double mean=input->GetMean();
        double RMS = input->GetRMS();
        
        // iteration parameters:
        // max iteration steps
        unsigned int ntries_max = 100;
        // width of cutting range in [RMS]
        double nRMS_width = 3.0;
        
        // iteration counters and helpers: 
        // min and max range of the histogram:
        double xmin=0.;
        double xmax=0.;
        // min and max bins of the histogram in previous iteration
        // 0-th iteration: range of the original histogram
        int binmin_was = 1;
        int binmax_was = input->GetNbinsX();
        // initial number of iteration steps
        unsigned int ntries = 0;
    
        // iteratively cut tails untill the RMS gets stable about mean
        // RMS stable: when input histogram range after cutting by 
        // +- 3*RMS is same as the range before cutting
        while ( ntries<ntries_max ) {    
        ++ntries;
        RMS = input->GetRMS();
        mean = input->GetMean();
        xmin = -1.0*nRMS_width*RMS + mean;
        xmax = nRMS_width*RMS + mean;
        // find bins corresponding to new range, disregard underflow
        int binmin=std::max(1,input->GetXaxis()->FindFixBin(xmin));
        // find bins corresponding to new range, disregard overflow
        int binmax=std::min(input->GetNbinsX(),input->GetXaxis()->FindFixBin(xmax));
        // end iteration if these are same bins as in prev. iteration
        if ( binmin_was==binmin && binmax_was==binmax ) {
        break;
        }
        else {
        // else set the new range and continue iteration 
        input->GetXaxis()->SetRange(binmin,binmax);
        binmin_was=binmin;
        binmax_was=binmax;
        }
        } // end of ( ntries<ntries_max ) ; iterative convergence loop
        
        // set the iteration results that are accessible to clients: 
        return std::make_pair(RMS, input->GetRMSError());    
    }

    std::shared_ptr<TH1D> getIterRMS(std::shared_ptr<TH2D> input){
        
        std::shared_ptr<TH1D> h1D {input->ProjectionX()}; 
        h1D->Reset(); 
        for (int bin = 1; bin < h1D->GetNbinsX()+1; ++bin){
            std::shared_ptr<TH1D> hY {input->ProjectionY(Form("py_%i",bin),bin,bin)}; 
            auto res = getIterRMS1D(hY); 
            h1D->SetBinContent(bin, res.first); 
            h1D->SetBinError(bin, res.second); 
        }
        return h1D; 
    }

    std::shared_ptr<TH2D> getIterRMS2D(std::shared_ptr<TH3D> input){
        
        std::shared_ptr<TH2D> h2D {dynamic_cast<TH2D*>(input->Project3D("yx"))}; 
        h2D->Reset(); 
        for (int binX = 1; binX < h2D->GetNbinsX()+1; ++binX){
            for (int binY = 1; binY < h2D->GetNbinsY()+1; ++binY){
                std::shared_ptr<TH1D> hZ {input->ProjectionZ(Form("py_%i_%i",binX,binY),binX,binX,binY,binY)}; 
                auto res = getIterRMS1D(hZ); 
                h2D->SetBinContent(binX,binY, res.first); 
                h2D->SetBinError(binX,binY, res.second); 
            }
        }
        return h2D; 
    }
    std::shared_ptr<TH1D> profToTH1(std::shared_ptr<TProfile> input){
        return std::shared_ptr<TH1D>(input->ProjectionX()); 
    }
}