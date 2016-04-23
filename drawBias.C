#include "tdrstyle.C"

void drawBias () {
    
    setTDRStyle();
    gStyle->SetOptStat(1);
    gStyle->SetOptTitle(1);
    gStyle->SetFitFormat("2.2g");
    gStyle->SetPadBottomMargin(0.2);
    
    
    const int nDirs = 6;
    
    Color_t cols[nDirs] = {kBlack, kRed+1, kOrange-3, kGreen+1, kAzure+7 , kMagenta};
    
    
    TString dirNames[nDirs] = {"exp1","expow2","pow1","lau1","atlas1","vvdijet1"};
    
    
    const int nPoints = 26;//46;
    TCanvas* c1[nDirs][nPoints];
    TFile * f[nDirs][nPoints];
    TTree* tree_fit_sb[nDirs][nPoints];
    
    TH1D* hists[nDirs][nPoints];
    
    TGraphErrors* biasG[nDirs];
    TGraphErrors* biasG2[nDirs];
    
    TCanvas* c2 = new TCanvas("p2","p2",700,700);
    TH1F *hr = c2->DrawFrame(500,-1,3100,1);
    hr->SetXTitle("m_{X} (GeV)");
    hr->SetYTitle("mean");

    TCanvas* c2a = new TCanvas("c2a","c2a",700,700);
    TH1F *hra = c2a->DrawFrame(500,-1,3100,1);
    hra->SetXTitle("m_{X} (GeV)");
    hra->SetYTitle("medians");
    
    TLegend* leg = new TLegend(0.75,1.0,1.0,0.75,"pull mean","NDC");
    leg->SetTextFont(42);
    TLegend* leg2 = new TLegend(0.65,0.35,0.9,0.1,"medians","NDC");
    leg2->SetTextFont(42);
    
    for (int dd=0; dd!=6; ++dd) {
        biasG[dd] = new TGraphErrors(nPoints);
        biasG2[dd] = new TGraphErrors(nPoints);
        biasG[dd]->SetMarkerColor(cols[dd]);
        biasG[dd]->SetLineColor(cols[dd]);
        biasG2[dd]->SetMarkerColor(cols[dd]);
        biasG2[dd]->SetLineColor(cols[dd]);
        
        
        leg->AddEntry(biasG[dd],dirNames[dd],"p");
        leg2->AddEntry(biasG2[dd],dirNames[dd],"p");
        
        Double_t quantile,prob;
        prob = 0.5;
        
        for (int i=0; i!=nPoints; ++i) {
            if (650+i*100 == 1750) continue;
            TString nameF = dirNames[dd]+Form("/mlfitoutput%d.root",650+i*100);
            if (gSystem->AccessPathName(nameF)) continue;
            c1[dd][i] = new TCanvas(Form("c_%d_%d",dd,i),Form("c_%d_%d",dd,i), 700, 700);
            f[dd][i] = new TFile(nameF);
            if(!f[dd][i]) continue;
            
            tree_fit_sb[dd][i] = static_cast<TTree*>(f[dd][i]->Get("tree_fit_sb"));
            
            TString name = Form("bias_%d_GeV-",650+i*100)+dirNames[dd];
            TString title = Form("bias at %d GeV for ",650+i*100)+dirNames[dd];
            hists[dd][i] = new TH1D(name,title+";#frac{#mu_{fit}-0.0}{#sigma_{fit}};entries/0.25",10000,-10,10);
            
            tree_fit_sb[dd][i]->Draw("(mu-0)/muHiErr>>"+name,"fit_status >= 0","pe");
            hists[dd][i]->Fit("gaus","LM","",-2,2);
            hists[dd][i]->GetXaxis()->SetTitleOffset(1.2);
            c1[dd][i]->SaveAs(dirNames[dd]+Form("_%d.pdf",650+i*100));
            
            
            biasG[dd]->SetPoint(i,650+i*100,hists[dd][i]->GetFunction("gaus")->GetParameter(1));
            biasG[dd]->SetPointError(i,0,hists[dd][i]->GetFunction("gaus")->GetParError(1));
            
            hists[dd][i]->GetQuantiles(1,&quantile,&prob);
            biasG2[dd]->SetPoint(i,650+i*100,quantile); // //GetMean
            //biasG2[dd]->SetPoint(i,650+i*100,hists[dd][i]->GetMean()); // //GetMean
            biasG2[dd]->SetPointError(i,0,hists[dd][i]->GetRMS()/sqrt(hists[dd][i]->GetEntries()));
            
            
        }
        c2->cd();
        biasG[dd]->Draw("pe same");
        c2a->cd();
        biasG2[dd]->Draw("pe same");
    }

    c2->cd();
    leg->Draw("same");
    c2a->cd();
    leg2->Draw("same");
    
}