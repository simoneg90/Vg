#include <iostream>

#include <TROOT.h>
#include <TSystem.h>
#include <TMath.h>
#include <TFile.h>
#include <TF1.h>
#include <TH1F.h>
#include <TProfile.h>
#include <THStack.h>
#include <TGraphErrors.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <TLegend.h>
#include <TCanvas.h>


/*#include <RooFit.h>
 #include <RooHist.h>
 #include <RooDataHist.h>
 #include <RooGenericPdf.h>
 #include <RooRealVar.h>
 #include <RooPlot.h>
 */

#include "CMS_lumi.C"
#include "tdrstyle.C"

using namespace RooFit;
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV
int iPos =11;
bool bias= false;
bool blind = false;
double H_mass=125.0;
double mH_diff_cut=40.;
double mH_mean_cut=20.;

double rebin=1;
bool useRatioFit=false;

std::string tags="nominal"; // MMMM

double SR_lo=600.;
double SR_hi=3600.;

Double_t ErfExp(Double_t x, Double_t c, Double_t offset, Double_t width){
    if(width<1e-2)width=1e-2;
    if (c==0)c=-1e-7;
    return TMath::Exp(c*x)*(1.+TMath::Erf((x-offset)/width))/2. ;
}

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0)
{
    return pow(a*a+b*b+c*c+d*d+e*e+f*f, 0.5);
}

std::string itoa(int i)
{
    char res[10];
    sprintf(res, "%d", i);
    std::string ret(res);
    return ret;
}


TCanvas* comparePlots2(RooPlot *plot_bC, RooPlot *plot_bS, TH1F *data, TH1F *qcd, std::string title)
{
    
    RooRealVar x("x", "m_{X} (GeV)", SR_lo, SR_hi);
    TCanvas *c=new TCanvas(("c_RooFit_"+title).c_str(), "c", 700, 700);
    TPad *p_1=new TPad("p_1", "p_1", 0, 0.35, 1, 1);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gROOT->SetStyle("Plain");
    p_1->SetFrameFillColor(0);
    p_2 = new TPad("p_2", "p_2",0,0.003740648,0.9975278,0.3391022);
    p_2->Range(160.1237,-0.8717948,1008.284,2.051282);
    p_2->SetFillColor(0);
    p_2->SetBorderMode(0);
    p_2->SetBorderSize(2);
    p_2->SetTopMargin(0.02);
    p_2->SetBottomMargin(0.3);
    p_2->SetFrameBorderMode(0);
    p_2->SetFrameBorderMode(0);
    
    p_1->Draw();
    p_2->Draw();
    p_1->cd();
    double maxdata=data->GetMaximum();
    double maxqcd=qcd->GetMaximum();
    double maxy=(maxdata>maxqcd) ? maxdata : maxqcd;
    
    title=";m_{X} (GeV); Events / "+itoa(data->GetBinWidth(1))+" GeV";
    p_1->DrawFrame(SR_lo, 0, SR_hi, maxy*1., title.c_str());
    plot_bS->SetMarkerStyle(20);
    plot_bS->Draw("same");
    // plot_bS->Draw("same");
    CMS_lumi( p_1, iPeriod, iPos );
    p_2->cd();
    /* TH1F *h_ratio=(TH1F*)data->Clone("h_ratio");
     h_ratio->GetYaxis()->SetTitle("VR/VSB Ratio");
     h_ratio->GetXaxis()->SetTitle("m_{X} (GeV)");
     h_ratio->SetTitle("");//("VR/VR-SB Ratio "+title+" ; VR/VR-SB Ratio").c_str());
     h_ratio->GetYaxis()->SetTitleSize(0.07);
     h_ratio->GetYaxis()->SetTitleOffset(0.5);
     h_ratio->GetXaxis()->SetTitleSize(0.09);
     h_ratio->GetXaxis()->SetTitleOffset(1.0);
     h_ratio->GetXaxis()->SetLabelSize(0.07);
     h_ratio->GetYaxis()->SetLabelSize(0.06);
     
     h_ratio->Divide(qcd);
     h_ratio->SetLineColor(1);
     h_ratio->SetMarkerStyle(20);
     h_ratio->GetXaxis()->SetRangeUser(SR_lo, SR_hi-10);
     h_ratio->GetYaxis()->SetRangeUser(0.,2.);
     */
    RooHist* hpull;
    hpull = plot_bS->pullHist();
    hpull->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
    RooPlot* frameP = x.frame() ;
    frameP->SetTitle("");
    frameP->GetYaxis()->SetTitle("Pull");
    frameP->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
    
    frameP->addPlotable(hpull,"P");
    frameP->GetYaxis()->SetTitle("Pull");
    
    frameP->GetYaxis()->SetTitleSize(0.07);
    frameP->GetYaxis()->SetTitleOffset(0.5);
    frameP->GetXaxis()->SetTitleSize(0.09);
    frameP->GetXaxis()->SetTitleOffset(1.0);
    frameP->GetXaxis()->SetLabelSize(0.07);
    frameP->GetYaxis()->SetLabelSize(0.06);
    
    frameP->Draw();
    
    
    //  TLine *m_one_line = new TLine(SR_lo,1,SR_hi,1);
    
    
    // h_ratio->Draw("");
    // m_one_line->Draw("same");
    p_1->cd();
    return c;
}

void BackgroundPrediction(std::string pname,int rebin_factor,int model_number = 0,int imass=750)
{
    rebin = rebin_factor;
    //std::string fname = std::string("../fitFilesBtagSF/") + pname + std::string("/histos_bkg.root");
    std::string fname = std::string("../GenSignal/") + pname + std::string("/histos_bkg.root");
    
    stringstream iimass ;
    iimass << imass;
    std::string dirName = "info_"+iimass.str()+"_"+pname;

    
    gStyle->SetOptStat(000000000);
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    
    setTDRStyle();
    gStyle->SetPadGridX(0);
    gStyle->SetPadGridY(0);
    gStyle->SetOptStat(0000);
    
    writeExtraText = true;       // if extra text
    extraText  = "Preliminary";  // default extra text is "Preliminary"
    lumi_13TeV  = "2.7 fb^{-1}"; // default is "19.7 fb^{-1}"
    lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"
    
    
    double ratio_tau=-1;
    
    TFile *f=new TFile(fname.c_str());
    TH1F *h_mX_CR_tau=(TH1F*)f->Get("distribs_18_10_1")->Clone("CR_tau");
    TH1F *h_mX_SR=(TH1F*)f->Get("distribs_18_10_0")->Clone("The_SR");
    double maxdata = h_mX_SR->GetMaximum();
    double nEventsSR = h_mX_SR->Integral(600,4000);
    ratio_tau=(h_mX_SR->GetSumOfWeights()/(h_mX_CR_tau->GetSumOfWeights()));
    //double nEventsSR = h_mX_SR->Integral(600,4000);
    
    std::cout<<"ratio tau "<<ratio_tau<<std::endl;
    
    h_mX_CR_tau->Rebin(rebin);
    h_mX_CR_tau->SetLineColor(kBlack);
    TH1F *h_SR_Prediction;
    
    if(blind)h_SR_Prediction=(TH1F*)h_mX_CR_tau->Clone("h_SR_Prediction");
    else {
        h_mX_SR->Rebin(rebin);
        h_mX_SR->SetLineColor(kBlack);
        h_SR_Prediction=(TH1F*)h_mX_SR->Clone("h_SR_Prediction");
        
    }
    h_SR_Prediction->SetMarkerSize(0.7);
    h_SR_Prediction->GetYaxis()->SetTitleOffset(1.2);
    h_SR_Prediction->Sumw2();
    
    
    RooRealVar x("x", "m_{X} (GeV)", SR_lo, SR_hi);
    
    RooRealVar nBackground((std::string("bg_")+pname+std::string("_norm")).c_str(),"nbkg",h_mX_SR->GetSumOfWeights());
    RooRealVar nBackground2((std::string("alt_bg_")+pname+std::string("_norm")).c_str(),"nbkg",h_mX_SR->GetSumOfWeights());
    std::string blah = pname;
    pname=""; //Antibtag=tag to constrain b-tag to the anti-btag shape
    
    
/*    RooRealVar bg_p0((std::string("bg_p0_")+pname).c_str(), "bg_p0", 4.2, 0, 200.);
    RooRealVar bg_p1((std::string("bg_p1_")+pname).c_str(), "bg_p1", 4.5, 0, 300.);
    RooRealVar bg_p2((std::string("bg_p2_")+pname).c_str(), "bg_p2", 0.000047, 0, 10.1);
    RooGenericPdf bg = RooGenericPdf((std::string("bg_")+blah).c_str(),"(pow(1-@0/13000,@1)/pow(@0/13000,@2+@3*log(@0/13000)))",RooArgList(x,bg_p0,bg_p1,bg_p2));*/

    RooRealVar bg_p0((std::string("bg_p0_")+pname).c_str(), "bg_p0", 0., -1000, 200.);
    RooRealVar bg_p1((std::string("bg_p1_")+pname).c_str(), "bg_p1", -13, -1000, 1000.);
    RooRealVar bg_p2((std::string("bg_p2_")+pname).c_str(), "bg_p2", -1.4, -1000, 1000);
    bg_p0.setConstant(kTRUE);
    
    RooGenericPdf bg = RooGenericPdf((std::string("bg_")+blah).c_str(),"(pow(@0/13000,@1+@2*log(@0/13000)))",RooArgList(x,bg_p1,bg_p2));

    string name_output = "CR_RooFit_Exp";
    
    
    RooDataHist pred("pred", "Prediction from SB", RooArgList(x), h_SR_Prediction);
    //RooFitResult *r_bg=bg.fitTo(pred, RooFit::Minimizer("Minuit2"), RooFit::Range(SR_lo, SR_hi), RooFit::SumW2Error(kTRUE), RooFit::Save());
    RooFitResult *r_bg=bg.fitTo(pred, RooFit::Range(SR_lo, SR_hi), RooFit::Save());

    std::cout<<" --------------------- Building Envelope --------------------- "<<std::endl;
    //std::cout<< "bg_p0_"<< pname << "   param   "<<bg_p0.getVal() <<  " "<<bg_p0.getError()<<std::endl;
    std::cout<< "bg_p1_"<< pname << "   param   "<<bg_p1.getVal() <<  " "<<bg_p1.getError()<<std::endl;
    std::cout<< "bg_p2_"<< pname << "   param   "<<bg_p2.getVal() <<  " "<<bg_p2.getError()<<std::endl;
    
    RooPlot *aC_plot=x.frame();
    pred.plotOn(aC_plot, RooFit::MarkerColor(kPink+2));
    bg.plotOn(aC_plot, RooFit::VisualizeError(*r_bg, 1), RooFit::FillColor(kGray+1), RooFit::FillStyle(3001));
    bg.plotOn(aC_plot, RooFit::LineColor(kBlack));
    pred.plotOn(aC_plot, RooFit::LineColor(kBlack), RooFit::MarkerColor(kBlack));
    
    double xPad = 0.3;
    TCanvas *c_rooFit=new TCanvas("c_rooFit", "c_rooFit", 800*(1.-xPad), 600);
    c_rooFit->SetFillStyle(4000);
    c_rooFit->SetFrameFillColor(0);
    
    TPad *p_1=new TPad("p_1", "p_1", 0, xPad, 1, 1);
    p_1->SetFillStyle(4000);
    p_1->SetFrameFillColor(0);
    p_1->SetBottomMargin(0.02);
    TPad* p_2 = new TPad("p_2", "p_2",0,0,1,xPad);
    p_2->SetBottomMargin((1.-xPad)/xPad*0.13);
    p_2->SetTopMargin(0.03);
    p_2->SetFillColor(0);
    p_2->SetBorderMode(0);
    p_2->SetBorderSize(2);
    p_2->SetFrameBorderMode(0);
    p_2->SetFrameBorderMode(0);
    
    p_1->Draw();
    p_2->Draw();
    p_1->cd();
    
    int nbins = (int) (SR_hi- SR_lo)/rebin;
    x.setBins(nbins);
    
    std::cout << "chi2(data) " <<  aC_plot->chiSquare()<<std::endl;
    
    //std::cout << "p-value: data     under hypothesis H0:  " << TMath::Prob(chi2_data->getVal(), nbins - 1) << std::endl;
    
    
    aC_plot->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
    aC_plot->GetXaxis()->SetLabelOffset(0.03);
    aC_plot->GetYaxis()->SetRangeUser(0.3, 500.);
    h_SR_Prediction->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
    string rebin_ = itoa(rebin);
    
    aC_plot->GetXaxis()->SetTitle("m_{X} (GeV) ");
    aC_plot->GetYaxis()->SetTitle(("Events / "+rebin_+" GeV ").c_str());
    aC_plot->SetMarkerSize(0.7);
    //aC_plot->GetYaxis()->SetLabelSize(0.03);
    aC_plot->GetYaxis()->SetTitleOffset(1.2);
    aC_plot->Draw();
    
    
    
    aC_plot->SetTitle("");
    TPaveText *pave = new TPaveText(0.85,0.4,0.67,0.5,"NDC");
    //TLegend *leg = new TLegend(0.85625,0.7721654,0.6765625,0.8903839,NULL,"brNDC");`
    pave->SetBorderSize(0);
    pave->SetTextSize(0.05);
    pave->SetTextFont(42);
    pave->SetLineColor(1);
    pave->SetLineStyle(1);
    pave->SetLineWidth(2);
    pave->SetFillColor(0);
    pave->SetFillStyle(0);
    char name[1000];
    sprintf(name,"#chi^{2}/n = %.2f",aC_plot->chiSquare());
    pave->AddText(name);
    pave->Draw();
    
    TLegend *leg = new TLegend(0.35,0.55,0.85,0.90,NULL,"brNDC");
    leg->SetBorderSize(0);
    leg->SetTextSize(0.05);
    leg->SetTextFont(42);
    leg->SetLineColor(1);
    leg->SetLineStyle(1);
    leg->SetLineWidth(2);
    leg->SetFillColor(0);
    leg->SetFillStyle(0);
    h_SR_Prediction->SetMarkerColor(kBlack);
    h_SR_Prediction->SetLineColor(kBlack);
    h_SR_Prediction->SetMarkerStyle(20);
    //h_mMMMMa_3Tag_SR->GetXaxis()->SetTitleSize(0.09);
    leg->AddEntry(h_SR_Prediction, "Data: sideband", "lep");
    TH1F *h=new TH1F();
    h->SetLineColor(kRed);
    h->SetLineWidth(3);
    leg->Draw();
    
    CMS_lumi( p_1, iPeriod, iPos );
    
    p_2->cd();
    RooHist* hpull;
    hpull = aC_plot->pullHist();
    RooPlot* frameP = x.frame() ;
    frameP->SetTitle("");
    frameP->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
    
    frameP->addPlotable(hpull,"P");
    frameP->GetYaxis()->SetRangeUser(-7,7);
    frameP->GetYaxis()->SetNdivisions(505);
    frameP->GetYaxis()->SetTitle("Pull");
    
    frameP->GetYaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
    frameP->GetYaxis()->SetTitleOffset(1.2/((1.-xPad)/xPad));
    frameP->GetXaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
    //frameP->GetXaxis()->SetTitleOffset(1.0);
    frameP->GetXaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
    frameP->GetYaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
    
    
    frameP->Draw();
    
    
    c_rooFit->SaveAs((dirName+"/"+name_output+".pdf").c_str());
    
    const int nModels = 9;
    TString models[nModels] = {
        "env_pdf_0_13TeV_dijet2", //0
        "env_pdf_0_13TeV_exp1", //1
        "env_pdf_0_13TeV_expow1", //2
        "env_pdf_0_13TeV_expow2", //3 => skip
        "env_pdf_0_13TeV_pow1", //4
        "env_pdf_0_13TeV_lau1", //5
        "env_pdf_0_13TeV_atlas1", //6
        "env_pdf_0_13TeV_atlas2", //7 => skip
        "env_pdf_0_13TeV_vvdijet1" //8
    };
    
    int nPars[nModels] = {
        2, 1, 2, 3, 1, 1, 2, 3, 2
    };
    
    TString parNames[nModels][3] = {
        "env_pdf_0_13TeV_dijet2_log1","env_pdf_0_13TeV_dijet2_log2","",
        "env_pdf_0_13TeV_exp1_p1","","",
        "env_pdf_0_13TeV_expow1_exp1","env_pdf_0_13TeV_expow1_pow1","",
        "env_pdf_0_13TeV_expow2_exp1","env_pdf_0_13TeV_expow2_pow1","env_pdf_0_13TeV_expow2_exp2",
        "env_pdf_0_13TeV_pow1_p1","","",
        "env_pdf_0_13TeV_lau1_l1","","",
        "env_pdf_0_13TeV_atlas1_coeff1","env_pdf_0_13TeV_atlas1_log1","",
        "env_pdf_0_13TeV_atlas2_coeff1","env_pdf_0_13TeV_atlas2_log1","env_pdf_0_13TeV_atlas2_log2",
        "env_pdf_0_13TeV_vvdijet1_coeff1","env_pdf_0_13TeV_vvdijet1_log1",""
    }
    
    if(bias){
        //alternative model
        gSystem->Load("libHiggsAnalysisCombinedLimit");
        gSystem->Load("libdiphotonsUtils");
        
        
        
        TFile *f = new TFile("btag_all_multipdf.root");
        RooWorkspace* xf = (RooWorkspace*)f->Get("wtemplates");
        RooWorkspace *w_alt=new RooWorkspace("Vg");
        for(int i=model_number; i<=model_number; i++){
            RooMultiPdf *alternative = (RooMultiPdf *)xf->pdf("model_bkg_Btag");
            std::cout<<"Number of pdfs "<<alternative->getNumPdfs()<<std::endl;
            for (int j=0; j!=alternative->getNumPdfs(); ++j){
                std::cout<<alternative->getPdf(j)->GetName()<<std::endl;
            }
            RooAbsPdf *alt_bg = alternative->getPdf(alternative->getCurrentIndex()+i);//->clone();
            w_alt->import(*alt_bg, RooFit::RenameVariable(alt_bg->GetName(),("alt_bg_"+blah).c_str()));
            w_alt->Print("V");
            std::cerr<<w_alt->var("x")<<std::endl;
            RooRealVar * range_ = w_alt->var("x");
            range_->setRange(SR_lo,SR_hi);
            char* asd = ("alt_bg_"+blah).c_str()	;
            w_alt->import(nBackground2);
            std::cout<<alt_bg->getVal() <<std::endl;
            w_alt->pdf(asd)->fitTo(pred, RooFit::Minimizer("Minuit2"), RooFit::Range(SR_lo, SR_hi), RooFit::SumW2Error(kTRUE), RooFit::Save());
            alt_bg->plotOn(aC_plot, RooFit::LineColor(i+1), RooFit::LineStyle(i+2));
            p_1->cd();
            aC_plot->GetYaxis()->SetRangeUser(0.01, maxdata*50.);
            aC_plot->Draw("same");
            TH1F *h=new TH1F();
            h->SetLineColor(1+i);
            h->SetLineStyle(i+2);
            leg->AddEntry(h, alt_bg->GetName(), "l");
            
            
            w_alt->SaveAs((dirName+"/w_background_alternative.root").c_str());
        }
        leg->Draw();
        p_1->SetLogy();
        c_rooFit->Update();
        c_rooFit->SaveAs((dirName+"/"+name_output+blah+"_multipdf.pdf").c_str());
        
        for (int i=0; i!=nPars[model_number]; ++i) {
            std::cout<<parNames[model_number][i]<<" param "<< w_alt->var(parNames[model_number][i])->getVal()<<"   "<<w_alt->var(parNames[model_number][i])->getError()<<std::endl;
        }
        
    } else {
        p_1->SetLogy();
        c_rooFit->Update();
        c_rooFit->SaveAs((dirName+"/"+name_output+"_log.pdf").c_str());
    }
    
    RooWorkspace *w=new RooWorkspace("Vg");
    w->import(bg);
    w->import(nBackground);
    w->SaveAs((dirName+"/w_background_GaussExp.root").c_str());
    
    TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
    h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
    RooDataHist data_obs("data_obs", "Data", RooArgList(x), h_mX_SR_fakeData);
    std::cout<<" Background number of events = "<<nEventsSR<<std::endl;
    RooWorkspace *w_data=new RooWorkspace("Vg");
    w_data->import(data_obs);
    w_data->SaveAs((dirName+"/w_data.root").c_str());
    
}




