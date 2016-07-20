//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Sat Feb  6 06:39:34 2016 by ROOT version 6.02/05
// from TTree tree/tree
// found on file: WJetsToQQ_HT-600ToInf.root
//////////////////////////////////////////////////////////

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1D.h>
#include <THStack.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "map"

#include "tdrstyle.C"
#include "CMS_lumi.C"
//#include "pu_weights.h"



const double intlumi = 7600;
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV
int iPos =0;

const int nVars = 19;
TString vars[nVars] = {
    "H_{T}^{gen} (GeV)","p_{T}^{#gamma} (GeV)","p_{T}^{AK8} (GeV)","#eta^{#gamma}","#eta^{AK8}",
    "N_{PV}", "M_{J}^{pruned} (GeV)", "#tau_{21}","#DeltaR","#Delta#eta",
    "M_{J#gamma}","E_{T}^{miss} (GeV)","M_{T} (GeV)","subjet min csv","subjet max csv",
    "|cos(#theta^{*})|","p_{T}^{#gamma}/M_{J#gamma}","H_{b#bar{b}}","M_{J} (GeV)"
};
TString varsBin[nVars] = {
    " GeV"," GeV"," GeV","","",
    ""," GeV","","","",
    " GeV"," GeV"," GeV","","",
    "","","",""
};
float varUp[nVars] = {
    2000,1500,2000,2.4,2.4,
    40,200,1,6,4.8,
    4000,400,400,1,1,
    1,1,1,200
};

float varDown[nVars] = {
    0,200,200,-2.4,-2.4,
    0,0,0,0,0,
    0,0,0,0,0,
    0,0,-1,0
};
int nBinsVars[nVars] = {
    20,13,18,48,48,
    40,40,50,30,48,
    80,16,40,100,100,
    50,100,25,50
};

int nDivisions[nVars] = {
    110,505,505,108,108,
    510,510,510,505,505,
    505,505,505,505,505,
    505,505,505,505
};
TString varsPlots[nVars] = {
    "HTgen","photonPt","jetPt","photonEta","jetEta",
    "Npv","Mj","tau21","deltaR","deltaEta",
    "Mjg","ETmiss","MT","csvmin","csvmax",
    "cosTheta","ptOverM","Hbb","Mraw"
};



void localRead3() {
    setTDRStyle();
    gStyle->SetOptStat(0);
    
    writeExtraText = true;       // if extra text
    extraText  = "Preliminary";  // default extra text is "Preliminary"
    lumi_13TeV  = "7.6 fb^{-1} (2016)"; // default is "19.7 fb^{-1}"

    const int nFiles = 19;
    const int nProcess = 9;
    const int iSM = 4;
    
    Color_t colsStack[nProcess+3] = {
        kYellow, kCyan, kOrange-3, kBlue,
        kRed-3,
        kGreen-3,
        kViolet+2, kMagenta-7, 1, 1, 1, 1
    };
    
    TString sampleString[nProcess] = {
        "M(765)",
        "M(1300)",
        "M(1900)",
        "M(3250)",
        "#gamma+jets",
        "QCD",
        "W+jets[180,#infty]",
        "DY+jets[180,#infty]",
        "data"
    };
    

    /*TFile* kFactFile = new TFile("uncertainties_EWK_24bins.root");
    TH1F* kfactHist[3][3];
    kfactHist[0][0] = (TH1F*)kFactFile->Get("GJets_LO/inv_pt_G");
    kfactHist[1][0] = (TH1F*)kFactFile->Get("WJets_LO/inv_pt");
    kfactHist[2][0] = (TH1F*)kFactFile->Get("ZJets_LO/inv_pt");

    kfactHist[0][1] = (TH1F*)kFactFile->Get("EWKcorr/photon");
    //kfactHist[0][1] = (TH1F*)kFactFile->Get("GJets_1j_NLO/nominal_G");
    kfactHist[1][1] = (TH1F*)kFactFile->Get("EWKcorr/W");
    kfactHist[2][1] = (TH1F*)kFactFile->Get("EWKcorr/Z");
    
    //TFile* kFactFile2 = new TFile("uncertainties2.root","recreate");

    TF1* func = new TF1("func","[0]*exp([1]*x) + [2]*exp([3]*x)");
    
    func->SetParameters(6.72541e-01,-2.59338e-03,1.04464e+00,-1.61432e-04);
    
    for (int i=0; i!=3; ++i) {
        //kfactHist[i][1]->Rebin(2);
        //kfactHist[i][0]->Rebin(2);
        kfactHist[i][2] = (TH1F*)kfactHist[i][1]->Clone(Form("kfact%d",i));
        kfactHist[i][2]->Divide(kfactHist[i][1],kfactHist[i][0]);
        
        //kfactHist[i][2]->Fit("func","","",200,1150);
        //kfactHist[i][2]->Fit("expo","","",200,1000);
        
        //kfactHist[i][2]->Write();
    }
    //kFactFile2->Close();
    //return;
    
    TH1F* kfactHist2[5];
    std::cout<<"reading"<<std::endl;
    kfactHist2[0] = (TH1F*)kFactFile->Get("GJets_1j_NLO/nominal_G");
    kfactHist2[1] = (TH1F*)kFactFile->Get("GJets_1j_NLO/fact_up_G");
    kfactHist2[2] = (TH1F*)kFactFile->Get("GJets_1j_NLO/fact_down_G");
    kfactHist2[3] = (TH1F*)kFactFile->Get("GJets_1j_NLO/ren_up_G");
    kfactHist2[4] = (TH1F*)kFactFile->Get("GJets_1j_NLO/ren_down_G");
    
    
    for (int i=0; i!=5; ++i) {
        
        kfactHist2[i]->SetLineColor(i+2);
        kfactHist2[i]->SetLineWidth(2);
        kfactHist2[i]->Divide(kfactHist[0][0]);
        
    }
    

   */ 
    
    TH1D* _hCounter = new TH1D("hCounter", "Events counter", 5,0,5);
    TH1D* distribs[nProcess+3][nVars];
    
    TH2D* distribs2d[nProcess+3];

    
    TFile* infile = new TFile("histos.root");
    
    for (int sam=0; sam!=nProcess+3; ++sam) {
        distribs2d[sam] = new TH2D(Form("distribs2d_%d",sam),
                                   ";"+vars[1]+";"+vars[2]+";",
                                   nBinsVars[1], varDown[1], varUp[1],nBinsVars[2], varDown[2], varUp[2]
                                   );
        
        if (sam < nProcess) {
            distribs2d[sam]->Read(Form("distribs2d_%d",sam));
            std::cout<<"read "<<Form("distribs2d_%d",sam)<<std::endl;
            //if (sam >= iSM && sam < nProcess-1)
            //    distribs[sam][i]->Scale(1./1.3);
        }
        
    }
    
    std::cout<<"done"<<std::endl;

    for (int sam=iSM+1; sam!=nProcess-1; ++sam) {//sum of qcd, w, dy
        distribs2d[nProcess]->Add(distribs2d[sam]);

    }
    distribs2d[nProcess+1]->Add(distribs2d[nProcess-1]); //add data
    distribs2d[nProcess+1]->Add(distribs2d[nProcess],-1.); //subtract MC
    distribs2d[nProcess+2]->Divide(distribs2d[nProcess+1],distribs2d[iSM]); //subtract MC

    gStyle->SetPaintTextFormat("4.1f");
    
    TCanvas* c2 = new TCanvas("c2","c2",800,800);
    //distribs[nProcess+1][2]->Draw("pe");
    //distribs[iSM][2]->Draw("pe same");
    gStyle->SetOptStat(0);
    gStyle->SetPaintTextFormat("4.1f");
     distribs2d[nProcess+2]->GetXaxis()->SetLabelSize(0.03);
     distribs2d[nProcess+2]->GetXaxis()->SetTitleOffset(0.95);
	distribs2d[nProcess+2]->GetYaxis()->SetTitleOffset(1.2);
     distribs2d[nProcess+2]->GetXaxis()->SetTitleSize(0.04);
     distribs2d[nProcess+2]->GetYaxis()->SetTitleSize(0.04);
    distribs2d[nProcess+2]->GetYaxis()->SetLabelSize(0.03);
    distribs2d[nProcess+2]->GetXaxis()->SetRangeUser(200,1100);
    distribs2d[nProcess+2]->GetYaxis()->SetRangeUser(200,1200);
    distribs2d[nProcess+2]->Draw("colz");
    distribs2d[nProcess+2]->Draw("text e same");
    c2->Print("asd.pdf");
    c2->Print("asd.root");
    
    //distribs[nProcess+2][2]->Draw("pe");
    //distribs[nProcess+2][2]->GetYaxis()->SetTitle("k-factor");
    
    TFile* newFile = new TFile("data_kfact3_4fb.root","recreate");
    //distribs2d[nProcess+2]->GetZaxis()->SetRangeUser(0,5);
    distribs2d[nProcess+2]->GetXaxis()->SetRangeUser(200,1100);
    distribs2d[nProcess+2]->GetYaxis()->SetRangeUser(200,1200);
    distribs2d[nProcess+2]->Write();
    newFile->Close();
    
    return;
    
    std::cout<<"Done"<<std::endl;
    
}



