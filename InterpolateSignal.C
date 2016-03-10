#ifndef __CINT__
#include "RooGlobalFunc.h"
#endif
#include "RooRealVar.h"
#include "RooDataSet.h"
#include "RooGaussian.h"
#include "RooConstVar.h"
#include "RooPolynomial.h"
#include "RooIntegralMorph.h"
#include "RooNLLVar.h"
#include "TCanvas.h"
#include "TAxis.h"
#include "RooPlot.h"
#include "TH1.h"
using namespace RooFit ;


void InterpolateSignal(TString postfix = "antibtag") {
    // C r e a t e   e n d   p o i n t   p d f   s h a p e s
    // ------------------------------------------------------
    
    // Observable
    RooRealVar x("x","x",400,3600) ;
    
    const double step = 50;
    const int nMCpoints = 4;
    
    RooAbsPdf* gMass[nMCpoints];
    const double masses[nMCpoints] = {750, 1000, 2000, 3000};
    TFile *f[nMCpoints];
    RooWorkspace* xf[nMCpoints];

    for (int i = 0; i!=nMCpoints; ++i ) {
        TString name = Form("info_%d_",int(masses[i]))+postfix + Form("/w_signal_%d.root",int(masses[i]));
        if (!gSystem->AccessPathName(name)) {
            f[i] = new TFile(name);
            xf[i] = (RooWorkspace*)f[i]->Get("Vg");
            gMass[i] = xf[i]->pdf("signal_fixed_"+postfix);
        } else {
            std::cout<<"File is not found: "<<name<<std::endl;
            return;
        }
    }
    
    RooWorkspace w("w");
    w.import(*gMass[0],RooFit::RenameVariable("signal_fixed_"+postfix,"signal_fixed_"+postfix+"_low"),RooFit::RenameAllVariablesExcept("low","x"));
    gMass[0] = w.pdf("signal_fixed_"+postfix+"_low");
    for (int i = 1; i!=nMCpoints; ++i ) {
        TString name = Form("point_%d",i);
        w.import(*gMass[i],RooFit::RenameConflictNodes(name),RooFit::RenameAllVariablesExcept(name,"x"),RooFit::RenameVariable("signal_fixed_"+postfix,"signal_fixed_"+postfix+"_"+name));
        
        gMass[i] = w.pdf("signal_fixed_"+postfix+"_"+name);

        
    }
    
    TF1* funcEff = new TF1("effFunc","pol3",600,3600);
    if (postfix == "antibtag")
        funcEff->SetParameters(-0.0857011,0.000399934,-1.63561e-07,2.33468e-11);
    else if (postfix == "btag")
        funcEff->SetParameters(-0.0218789,8.83179e-05,-4.6412e-08,6.68673e-12);
    else {
        std::cout<<"Unknown category: "<<postfix<<std::endl;
        return;
    }

    // C r e a t e   i n t e r p o l a t i n g   p d f
    // -----------------------------------------------
    
    // Create interpolation variable
    RooRealVar alpha("alpha","alpha",0,1.0) ;
    
    // Specify sampling density on observable and interpolation variable
    x.setBins(3000,"cache") ;
    alpha.setBins(5000,"cache") ;
    
    RooPlot* frame1[nMCpoints];
    RooPlot* frame2[nMCpoints];
    RooPlot* frame3[nMCpoints];
    TH1* hh[nMCpoints];
    
    TCanvas* c[nMCpoints];
    
    for (int iPoint = 0; iPoint!=nMCpoints-1; ++iPoint) {
        
        // Construct interpolating pdf in (x,a) represent g1(x) at a=a_min
        // and g2(x) at a=a_max
        RooIntegralMorph lmorph("lmorph","lmorph",*gMass[iPoint],*gMass[iPoint+1],x,alpha) ;
        
        // P l o t   i n t e r p o l a t i n g   p d f   a t   v a r i o u s   a l p h a
        // -----------------------------------------------------------------------------
        
        // Show end points as blue curves
        frame1[iPoint] = x.frame() ;
        gMass[iPoint]->plotOn(frame1[iPoint]) ;
        gMass[iPoint+1]->plotOn(frame1[iPoint]) ;
        
        int nPoints = int((masses[iPoint+1]-masses[iPoint])/step);
        for (int i=0; i!=nPoints+1; ++i) {
            //alpha=double(i)/double(nPoints);
            alpha.setVal(double(i)/double(nPoints)) ;
            lmorph.plotOn(frame1[iPoint],LineColor(kRed)) ;
            
            RooDataSet* data2 = lmorph.generate(x,30000);
            
            double effcy = funcEff->Eval(masses[iPoint+1]-i*step);
            double weight = effcy/30000.;
            TH1D* distribs0 = new TH1D("distribs_5_10_0","",4000,0,4000);
            
            data2->fillHistogram(distribs0,x);
            distribs0->Scale(weight);
            TFile* fileNew = new TFile(Form("GenSignal/"+postfix+"/histos_signal-%d.root",int(masses[iPoint+1]-i*step)),"RECREATE");
            distribs0->Write();
            fileNew->Close();
            
            delete data2;
            delete distribs0;
        }
        
        // S h o w   2 D   d i s t r i b u t i o n   o f   p d f ( x , a l p h a )
        // -----------------------------------------------------------------------
        
        // Create 2D histogram
        hh[iPoint] = lmorph.createHistogram("hh",x,Binning(40),YVar(alpha,Binning(40))) ;
        hh[iPoint]->SetLineColor(kBlue) ;
        
        
        // F i t   p d f   t o   d a t a s e t   w i t h   a l p h a = 0 . 8
        // -----------------------------------------------------------------
        
        // Generate a toy dataset at alpha = 0.8
        alpha=0.8 ;
        RooDataSet* data = lmorph.generate(x,1000) ;
        
        // Fit pdf to toy data
        lmorph.setCacheAlpha(kTRUE) ;
        lmorph.fitTo(*data,Verbose(kTRUE)) ;
        
        // Plot fitted pdf and data overlaid
        frame2[iPoint] = x.frame(Bins(1500)) ;
        data->plotOn(frame2[iPoint]) ;
        lmorph.plotOn(frame2[iPoint]) ;
        
        
        // S c a n   - l o g ( L )   v s   a l p h a
        // -----------------------------------------
        
        // Show scan -log(L) of dataset w.r.t alpha
        frame3[iPoint] = alpha.frame(Bins(100),Range(0.1,0.9)) ;
        
        // Make 2D pdf of histogram
        RooNLLVar nll("nll","nll",lmorph,*data) ;
        nll.plotOn(frame3[iPoint],ShiftToZero()) ;
        
        lmorph.setCacheAlpha(kFALSE) ;
        
        
        
        c[iPoint] = new TCanvas(Form("linearmorph_%d",iPoint),Form("linearmorph_%d",iPoint),700,700) ;
        c[iPoint]->Divide(2,2) ;
        c[iPoint]->cd(1) ; gPad->SetLeftMargin(0.15) ; frame1[iPoint]->GetYaxis()->SetTitleOffset(1.6) ; frame1[iPoint]->Draw() ;
        c[iPoint]->cd(2) ; gPad->SetLeftMargin(0.20) ; hh[iPoint]->GetZaxis()->SetTitleOffset(2.5) ; hh[iPoint]->Draw("surf") ;
        c[iPoint]->cd(3) ; gPad->SetLeftMargin(0.15) ; frame3[iPoint]->GetYaxis()->SetTitleOffset(1.4) ; frame3[iPoint]->Draw() ;
        c[iPoint]->cd(4) ; gPad->SetLeftMargin(0.15) ; frame2[iPoint]->GetYaxis()->SetTitleOffset(1.4) ; frame2[iPoint]->Draw() ;
        c[iPoint]->Modified(); c[iPoint]->Update();
    }
    
    
    return ;
    
}
