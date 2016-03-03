#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TF1.h>
#include <TSystem.h>
#include <TGraphErrors.h>
#include <TF1.h>
using namespace RooFit;
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos =11;

bool blind = true;
double H_mass=125.0;
double mH_diff_cut=40.;
double mH_mean_cut=20.;

double rebin=1;
bool useRatioFit=false;

std::string tags="nominal"; // MMMM

double SR_lo=650.; 
double SR_hi=2500.;

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
	//p_1->SetBottomMargin(0.05);
	p_1->SetFrameFillColor(0);
	//p_2->SetFrameFillColor(0);
	p_2 = new TPad("p_2", "p_2",0,0.003740648,0.9975278,0.3391022);
	//p_2->Draw();
	//p_2->cd();
	p_2->Range(160.1237,-0.8717948,1008.284,2.051282);
	p_2->SetFillColor(0);
	p_2->SetBorderMode(0);
	p_2->SetBorderSize(2);
	p_2->SetTopMargin(0.01754386);
	p_2->SetBottomMargin(0.2982456);
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
	   h_ratio->SetTitle();//("VR/VR-SB Ratio "+title+" ; VR/VR-SB Ratio").c_str());
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
	frameP->SetTitle();frameP->GetYaxis()->SetTitle("Pull");frameP->GetXaxis()->SetRangeUser(SR_lo, SR_hi);

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

void BackgroundPrediction(std::string pname,int rebin_factor)
{
        std::string fname = std::string("data_") + pname + std::string(".root");

	gROOT->SetStyle("Plain");
	gStyle->SetOptStat(000000000);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0); 

	gROOT->LoadMacro("tdrstyle.C");
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptStat(0000);
	gROOT->LoadMacro("CMS_lumi.C");

	writeExtraText = true;       // if extra text
	extraText  = "Preliminary";  // default extra text is "Preliminary"
	lumi_13TeV  = "2.7 fb^{-1}"; // default is "19.7 fb^{-1}"
	lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"


	double ratio_tau=-1, ratio_btag=-1;

	TFile *f=new TFile(fname.c_str());
	TH1F *h_mX_CR_tau=(TH1F*)f->Get("distribs_18_10_1")->Clone("CR_tau");
        h_mX_CR_tau->Rebin(rebin_factor);
	TH1F *h_mX_CR_btag=(TH1F*)f->Get("distribs_18_10_1")->Clone("CR_btag");
        h_mX_CR_btag->Rebin(rebin_factor);
        TH1F *h_mX_SR=(TH1F*)f->Get("distribs_18_10_0")->Clone("The_SR");
	double nEventsSR = h_mX_SR->Integral(600,4000);
        h_mX_SR->Rebin(rebin_factor);
	ratio_tau=(h_mX_SR->GetSumOfWeights()/(h_mX_CR_tau->GetSumOfWeights()));
	ratio_btag= h_mX_SR->GetSumOfWeights()/(h_mX_CR_btag->GetSumOfWeights());
	//double nEventsSR = h_mX_SR->Integral(600,4000);
	


	std::cout<<"ratio btag = "<<ratio_btag<<"ratio tau "<<ratio_tau<<std::endl;



	rebin= rebin_factor;
	h_mX_CR_tau->Rebin(rebin);
	h_mX_CR_tau->SetLineColor(kBlack);
	if(blind)TH1F *h_SR_Prediction=(TH1F*)h_mX_CR_tau->Clone("h_SR_Prediction");
	else {
		h_mX_SR->Rebin(rebin);	
		h_mX_SR->SetLineColor(kBlack);
		TH1F *h_SR_Prediction=(TH1F*)h_mX_SR->Clone("h_SR_Prediction");

	}
	h_SR_Prediction->SetMarkerSize(0.7);
	h_SR_Prediction->GetYaxis()->SetTitleOffset(1.2);


	RooRealVar x("x", "m_{X} (GeV)", SR_lo, SR_hi);

	/*  RooRealVar bg_p0("bg_p0", "bg_p0", 700., 1200.);
	    RooRealVar bg_p1("bg_p1", "bg_p1", 50., 300.1);
	    RooRealVar bg_p2("bg_p2", "bg_p2", 0.01, 10.1);
	    GaussExp bg("bg", "Background Prediction PDF", x, bg_p0, bg_p1, bg_p2);
	    string name_output="CR_RooFit_GaussExp";
	    */

	RooRealVar bg_p0((std::string("bg_p0_")+pname).c_str(), "bg_p0", 0., 200.);
	RooRealVar bg_p1((std::string("bg_p1_")+pname).c_str(), "bg_p1", 0., 30.1);
	RooRealVar bg_p2((std::string("bg_p2_")+pname).c_str(), "bg_p2", 0., 10.1);	
	bg = RooGenericPdf((std::string("bg_")+pname).c_str(),"(pow(1-@0/13000,@1)/pow(@0/13000,@2+@3*log(@0/13000)))",RooArgList(x,bg_p0,bg_p1,bg_p2));
	string name_output = "CR_RooFit_Exp";	

	/* TO FIX
	 * RooRealVar bg_p0("bg_p0", "bg_p0", 700.0, 1200.1);
	 RooRealVar bg_p1("bg_p1", "bg_p1", 10., 60.);
	 RooRealVar bg_p2("bg_p2", "bg_p2", 10.0, 800.1);
	 RooRealVar bg_p3("bg_p3", "bg_p3", 10., 500.);

	 RooLandau landaubg("landaubg", "Combinatoric", x, bg_p0,bg_p1);//, *sg_3, *sg_4));//, *sg_5, *sg_6));
	 RooGaussian gauss1("gauss1","gauss1", x, bg_p2, bg_p3);
	 RooFFTConvPdf bg("bg" ,"bg",x, landaubg, gauss1);
	 bg.setBufferFraction(0.9);
	 string name_output = "CR_RooFit_Landau";	
	 */
	/* //TO FIX 
	   bg_p0=new RooRealVar("bg_p0", "bg_p0", 0., 10.);
	   bg_p1=new RooRealVar("bg_p1", "bg_p1", 0., 10.);
	   bg_p2=new RooRealVar("bg_p2", "bg_p2", 0., 10.);
	   bg_p3=new RooRealVar("bg_p3", "bg_p3", 0., 12.);
	   bg_p4=new RooRealVar("bg_p4", "bg_p4", 0., 10.);
	   bg_p5=new RooRealVar("bg_p5", "bg_p5", 0., 5.);
	   bg_p6=new RooRealVar("bg_p6", "bg_p6", 0., 5.);
	   bg_p7=new RooRealVar("bg_p7", "bg_p7", 0., 5.);
	   bg_p8=new RooRealVar("bg_p8", "bg_p8", 0., 5.);
	   RooBernstein bg("bg", "bg", x, RooArgList(*bg_p1,*bg_p2, *bg_p3, *bg_p4, *bg_p5));// *bg_p6, *bg_p7, *bg_p8));
	   string name_output = "CR_RooFit_Bernestein"; 
	   */

	RooDataHist pred("pred", "Prediction from SB", RooArgList(x), h_SR_Prediction);
	RooFitResult *r_bg=bg.fitTo(pred, RooFit::Range(SR_lo, SR_hi), RooFit::Save());
	//RooDataHist  data_=*(bg.generateBinned(x, h_mMMMMa_3Tag_SR_Prediction->Integral(h_mMMMMa_3Tag_SR_Prediction->FindBin(SR_lo), h_mX_SR->FindBin(SR_hi)-1) , RooAbsData::Poisson));
	std::cout<<" --------------------- Building Envelope --------------------- "<<std::endl;
	std::cout<< "bg_p0_"<< pname << "   param   "<<bg_p0.getVal() <<  " "<<bg_p0.getError()<<std::endl;
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
        aC_plot->GetYaxis()->SetRangeUser(1, 500.);
        h_SR_Prediction->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
        string rebin_ = itoa(rebin);

        aC_plot->GetXaxis()->SetTitle("m_{X} (GeV) ");  aC_plot->GetYaxis()->SetTitle(("Events / "+rebin_+" GeV ").c_str());
        aC_plot->SetMarkerSize(0.7);


	aC_plot->Draw();




        aC_plot->SetTitle("");
        TPaveText *pave = new TPaveText(0.85625,0.7,0.67,0.8,"NDC");
        pave->SetBorderSize(0);
        pave->SetTextSize(0.03);
        pave->SetLineColor(1);
        pave->SetLineStyle(1);
        pave->SetLineWidth(2);
        pave->SetFillColor(0);
        pave->SetFillStyle(0);
        char name[1000];
        sprintf(name,"#chi^{2}/n = %.2f",aC_plot->chiSquare());
        pave->AddText(name);
        pave->Draw();

        TLegend *leg = new TLegend(0.85625,0.7721654,0.6765625,0.8903839,NULL,"brNDC");
        leg->SetBorderSize(0);
        leg->SetTextSize(0.035);
        leg->SetLineColor(1);
        leg->SetLineStyle(1);
        leg->SetLineWidth(2);
        leg->SetFillColor(0);
        leg->SetFillStyle(0);
        h_SR_Prediction->SetMarkerColor(kBlack);
        h_SR_Prediction->SetLineColor(kBlack);
        h_SR_Prediction->SetMarkerStyle(20);
	   leg->AddEntry(h_SR_Prediction, "Data", "lep");
        TH1F *h=new TH1F();
        h->SetLineColor(kRed);
        h->SetLineWidth(3);
        leg->Draw();

        CMS_lumi( p_1, iPeriod, iPos );

        p_2->cd();
        RooHist* hpull;
        hpull = aC_plot->pullHist();
        hpull->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
        RooPlot* frameP = x.frame() ;

        frameP->addPlotable(hpull,"P");
    	frameP->GetYaxis()->SetRangeUser(-5,5);
    	frameP->GetXaxis()->SetRangeUser(SR_lo, SR_hi);
    	frameP->SetTitle("");
    	frameP->GetYaxis()->SetTitle("Pull");

    	frameP->GetYaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
    	frameP->GetYaxis()->SetTitleOffset(1.2/((1.-xPad)/xPad));
    	frameP->GetXaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
        frameP->GetXaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
        frameP->GetYaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
        frameP->Draw();



	frameP->Draw();


	c_rooFit->SaveAs((name_output+".pdf").c_str()); 
	
	p_1->SetLogy();	
	c_rooFit->Update();
	c_rooFit->SaveAs((name_output+"_log.pdf").c_str());

	// ------------------------------------------
	RooRealVar nBackground((std::string("bg_")+pname+std::string("_norm")).c_str(),"nbkg",h_mX_SR->GetSumOfWeights());	

	RooWorkspace *w=new RooWorkspace("Vg");
	w->import(bg);
	w->import(nBackground);
	w->SaveAs("w_background_GaussExp.root");

	TH1F *h_mX_SR_fakeData=(TH1F*)h_mX_SR->Clone("h_mX_SR_fakeData");
	h_mX_SR_fakeData->Scale(nEventsSR/h_mX_SR_fakeData->GetSumOfWeights());
	RooDataHist data_obs("data_obs", "Data", RooArgList(x), h_mX_SR_fakeData);
	std::cout<<" Background number of events = "<<nEventsSR<<std::endl;
	RooWorkspace *w_data=new RooWorkspace("Vg");
	w_data->import(data_obs);
	w_data->SaveAs("w_data.root");	

}




