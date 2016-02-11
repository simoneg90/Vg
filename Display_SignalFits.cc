// Creates the images and HTML 
// for displaying changes in Signal MC
// due to JEC+1-1, and JER+1-1

#include <TH1F.h>
#include <TH2F.h>
#include <TROOT.h>
#include <TFile.h>
#include <TTree.h>
#include <TSystem.h>
#include <TChain.h>
#include <TLorentzVector.h>
#include <TLegend.h>
#include <TCanvas.h>
#include <TProfile.h>
#include <iostream>
#include <TFractionFitter.h>
#include <TStyle.h>
#include <TPaveText.h>
#include <THStack.h>
#include <TArrow.h>
#include <TColor.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include "CMS_lumi.C"
//#include "RooRealVar.h"
//#include "RooArgList.h"
//#include "RooChebychev.h"
/*#include "RooDataHist.h"
#include "RooAbsPdf.h"
#include "RooWorkspace.h"
#include "RooPlot.h"
#include "RooFitResult.h"
#include "RooCBShape.h"
#include "RooGaussian.h"
*/
int iPeriod = 4;    // 1=7TeV, 2=8TeV, 3=7+8TeV, 7=7+8+13TeV 
int iPos =11;

int rebin=1;
ofstream outfile;

std::string tostr(float t)
{
  std::ostringstream os; 
  os<<std::setprecision(2)<<t; 
  return os.str(); 
}

double quad(double a, double b, double c=0, double d=0, double e=0, double f=0, double g=0, double h=0, double i=0, double j=0, double k=0)
{
  return pow(a*a+b*b+c*c+d*d+e*e+f*f+g*g+h*h+i*i+j*j+k*k, 0.5);
}

struct Params
{
  double sg_p0;
  double sg_p1;
  double sg_p2;
  double sg_p3;
  double sg_p4;	
  double sg_p5;
  double sg_p6;		
  double sg_p0_err;
  double sg_p1_err;
  double sg_p2_err;
  double sg_p3_err;
  double sg_p4_err;	
  double sg_p5_err;
  double sg_p6_err;	
};


RooPlot* fitSignal(TH1F *h, std::string mass, int color, TLegend *leg, Params &params, bool kinFit=false)
{
  
  RooRealVar *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3, *sg_p4;
  x=new RooRealVar("x", "m_{X} (GeV)", 600., 3000.);
  double rangeLo=-1, rangeHi=-1;

	  if (mass=="750")
	  {
		  rangeLo=600., rangeHi=1100.;
		  sg_p0=new RooRealVar("sg_p0", "sg_p0", 700., 800.);
		  sg_p1=new RooRealVar("sg_p1", "sg_p1", 5., 40.);
		  sg_p2=new RooRealVar("sg_p2", "sg_p2", 0., 20.);
		  sg_p3=new RooRealVar("sg_p3", "sg_p3", 0., 30.);
		  sg_p4=new RooRealVar("sg_p4", "sg_p4", 500., 800.);
		  sg_p5=new RooRealVar("sg_p5", "sg_p5", 10., 300.);	
		  sg_p6=new RooRealVar("sg_p6", "sg_p6", 0.,1.);
	  }

  x=new RooRealVar("x", "m_{X} (GeV)", rangeLo-50., rangeHi+50.);
  //RooGaussian signal("signal", "Signal Prediction", *x, *sg_p0, *sg_p1);
  RooCBShape signalCore("signalCore", "signalCore", *x, *sg_p0, *sg_p1,*sg_p2, *sg_p3);	
  RooGaussian signalComb("signalComb", "Combinatoric", *x, *sg_p4, *sg_p5);
  RooAddPdf signal("signal", "signal", RooArgList(signalCore, signalComb), *sg_p6);
  //
  //  RooBukinPdf signal("signal", "signal", *x, *sg_p0, *sg_p1, *sg_p2, *sg_p3,*sg_p4);
  RooDataHist signalHistogram("signalHistogram", "Signal Histogram", RooArgList(*x), h);
  signal.fitTo(signalHistogram, RooFit::Range(rangeLo, rangeHi), RooFit::Save());
  params.sg_p0=sg_p0->getVal(); params.sg_p0_err=sg_p0->getError();
  params.sg_p1=sg_p1->getVal(); params.sg_p1_err=sg_p1->getError();
  params.sg_p2=sg_p2->getVal(); params.sg_p2_err=sg_p2->getError();
  params.sg_p3=sg_p3->getVal(); params.sg_p3_err=sg_p3->getError();
  params.sg_p4=sg_p4->getVal(); params.sg_p4_err=sg_p4->getError();
   params.sg_p5=sg_p5->getVal(); params.sg_p5_err=sg_p5->getError();
params.sg_p6=sg_p6->getVal(); params.sg_p6_err=sg_p6->getError();	
  RooPlot *plot=x->frame();
  if (color==kBlack)
  {
	  signalHistogram.plotOn(plot, RooFit::MarkerColor(color), RooFit::MarkerSize(1.2));
	  signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(3));
  }
  else 
  {
	  signalHistogram.plotOn(plot, RooFit::MarkerColor(color));
	  signal.plotOn(plot, RooFit::LineColor(color), RooFit::LineWidth(0));
  }
  // leg->AddEntry((TObject*)0, ("norm="+tostr(h->GetSumOfWeights())).c_str(), "");
   leg->AddEntry((TObject*)0, ("#mu= "+tostr(sg_p0->getVal())+"#pm"+tostr(sg_p0->getError())).c_str(), "");
   leg->AddEntry((TObject*)0, ("#sigma= "+tostr(sg_p1->getVal())+"#pm"+tostr(sg_p1->getError())).c_str(), "");


  // std::cout<<"chi2/dof = "<<plot->chiSquare()<<std::endl;

  // Save modified signal shape to workspace
  if (color==kBlack)
  {
	  RooRealVar signal_p0("signal_p0", "signal_p0", sg_p0->getVal());
	  RooRealVar signal_p1("signal_p1", "signal_p1", sg_p1->getVal());
	  RooRealVar signal_p2("signal_p2", "signal_p2", sg_p2->getVal());
	  RooRealVar signal_p3("signal_p3", "signal_p3", sg_p3->getVal());
	  RooRealVar signal_p4("signal_p4", "signal_p4", sg_p4->getVal());
	  RooRealVar signal_p5("signal_p5", "signal_p5", sg_p5->getVal());
	  RooRealVar signal_p6("signal_p6", "signal_p6", sg_p6->getVal());	
	  //RooGaussian signal_fixed("signal_fixed", "Signal Prediction", *x, signal_p0, signal_p1);
	  RooCBShape signalCore_fixed("signalCore_fixed", "signalCore", *x, signal_p0, signal_p1,signal_p2, signal_p3);    
	  RooGaussian signalComb_fixed("signalComb_fixed", "Combinatoric", *x, signal_p4, signal_p5);
	  RooAddPdf signal_fixed("signal_fixed", "signal", RooArgList(signalCore_fixed, signalComb_fixed), signal_p6);
	  //	RooBukinPdf signal_fixed("signal_fixed", "signal_fixed", *x, signal_p0, signal_p1, signal_p2,signal_p3,signal_p4);
	  RooWorkspace *w=new RooWorkspace("Vg");
	  w->import(signal_fixed);
	  if (!kinFit) w->SaveAs(("w_signal_"+mass+".root").c_str());
	  if (kinFit) w->SaveAs(("w_signal_"+mass+".root").c_str());
  }
  return plot;
}

double lnN(double b, double a, double c)
{
	// std::cout<<"a = "<<a<<", b = "<<b<<", c = "<<c<<std::endl;
	// std::cout<<"1.+(a-c)/(2.*b) = "<<1.+fabs(a-c)/(2.*b)<<std::endl;
	double err=0;
	if (b>0) err=1.+fabs(a-c)/(2.*b);
	return err;
}

int Display_SignalFits(std::string dir_preselection="",
		std::string dir_selection="",
		std::string file_histograms="m-",
		bool focus=false)
{

	std::vector<std::string> masses;
	masses.push_back("750");

	gROOT->SetStyle("Plain");
	gStyle->SetOptStat(000000000);
	gStyle->SetPadGridX(0);
	gStyle->SetPadGridY(0);
	gStyle->SetOptStat(0000);
	gROOT->LoadMacro("CMS_lumi.C");

	writeExtraText = true;       // if extra text
	extraText  = "Preliminary";  // default extra text is "Preliminary"
	lumi_13TeV  = "2.6 fb^{-1}"; // default is "19.7 fb^{-1}"
	lumi_7TeV  = "4.9 fb^{-1}";  // default is "5.1 fb^{-1}"	

	// Calculate nSignal events given production cross section, branching fractions and efficiency
	double totalLumi=2630; // /pb
	double prodXsec_1=1.; // pb

	// Interpolation Plots
	std::vector<double> v_sg_p0, v_sg_p0_err;
	std::vector<double> v_sg_p1, v_sg_p1_err;
	std::vector<double> v_sg_p2, v_sg_p2_err;
	std::vector<double> v_sg_p3, v_sg_p3_err;
	std::vector<double> v_sg_p4, v_sg_p4_err;
	std::vector<double> v_sg_p5, v_sg_p5_err;
	std::vector<double> v_sg_p6, v_sg_p6_err;
	std::vector<double> v_zero;

	// Write to an HTML File
	outfile.open("SignalFits/index.html");
	outfile<<"<html>"<<std::endl;
	outfile<<"<head>"<<std::endl;
	// outfile<<"<base href=\"https://cmslpcweb.fnal.gov/uscms_data/souvik/SignalSystematics\" target=\"_blank\">"<<std::endl;
	outfile<<"<script type=\"text/javascript\">"<<std::endl;
	outfile<<"function toggleMe(a){"<<std::endl;
	outfile<<"var e=document.getElementById(a);"<<std::endl;
	outfile<<"if(!e)return true;"<<std::endl;
	outfile<<"if(e.style.display==\"none\"){"<<std::endl;
	outfile<<"e.style.display=\"block\""<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"else{"<<std::endl;
	outfile<<"e.style.display=\"none\""<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"return true;"<<std::endl;
	outfile<<"}"<<std::endl;
	outfile<<"</script>"<<std::endl;
	outfile<<"</head>"<<std::endl;
	outfile<<"<body>"<<std::endl;
	outfile<<"<h1> Signal with JEC, JER Systematic Uncertainties</h1>"<<std::endl;

	for (unsigned int i=0; i<masses.size(); ++i)
	{
		v_zero.push_back(0);

		TFile *file=new TFile((dir_preselection+"/"+dir_selection+"/"+file_histograms+masses.at(i)+"_no_b_tag_tau21_SB60_70.root").c_str());
		TH1F *h_mX_SR=(TH1F*)file->Get("distribs_14_10_0");

		double nSignal_init=36500;//h_Count->GetBinContent(1);

		/*TFile *file_JECp1;
		  if (focus) file_JECp1=file;
		  else file_JECp1=new TFile((dir_preselection+"_JECp1/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		  TH1F *h_mX_SR_JECp1=(TH1F*)file_JECp1->Get("h_mX_SR")->Clone("h_mX_SR_JECp1");
		  TH1F *h_mX_SR_JECp1_KinFit=(TH1F*)file_JECp1->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_JECp1_KinFit");

		  TFile *file_JECm1;
		  if (focus) file_JECm1=file;
		  else file_JECm1=new TFile((dir_preselection+"_JECm1/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		  TH1F *h_mX_SR_JECm1=(TH1F*)file_JECm1->Get("h_mX_SR")->Clone("h_mX_SR_JECm1");
		  TH1F *h_mX_SR_JECm1_KinFit=(TH1F*)file_JECm1->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_JECm1_KinFit");


		  TFile *file_JERp1;
		  if (focus) file_JERp1=file;
		  else file_JERp1=new TFile((dir_preselection+"_JERp1/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		  TH1F *h_mX_SR_JERp1=(TH1F*)file_JERp1->Get("h_mX_SR")->Clone("h_mX_SR_JERp1");
		  TH1F *h_mX_SR_JERp1_KinFit=(TH1F*)file_JERp1->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_JERp1_KinFit");

		  TFile *file_JERm1;
		  if (focus) file_JERm1=file;
		  else file_JERm1=new TFile((dir_preselection+"_JERm1/"+dir_selection+"/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		  TH1F *h_mX_SR_JERm1=(TH1F*)file_JERm1->Get("h_mX_SR")->Clone("h_mX_SR_JERm1");
		  TH1F *h_mX_SR_JERm1_KinFit=(TH1F*)file_JERm1->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_JERm1_KinFit");	


		  TFile *file_bTagDown;
		  if (focus) file_bTagDown=file;
		  else file_bTagDown=new TFile((dir_preselection+"/"+dir_selection+"_bTagDown/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		  TH1F *h_mX_SR_bTagDown=(TH1F*)file_bTagDown->Get("h_mX_SR")->Clone("h_mX_SR_bTagDown");
		  TH1F *h_mX_SR_bTagDown_KinFit=(TH1F*)file_bTagDown->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_bTagDown_KinFit");

		  TFile *file_bTagUp;
		  if (focus) file_bTagUp=file;
		  else file_bTagUp=new TFile((dir_preselection+"/"+dir_selection+"_bTagUp/"+file_histograms+masses.at(i)+"GeV.root").c_str());
		  TH1F *h_mX_SR_bTagUp=(TH1F*)file_bTagUp->Get("h_mX_SR")->Clone("h_mX_SR_bTagUp");
		  TH1F *h_mX_SR_bTagUp_KinFit=(TH1F*)file_bTagUp->Get("h_mX_SR_kinFit")->Clone("h_mX_SR_bTagUp_KinFit");


		  TCanvas *c_mX_SR=new TCanvas(("c_mX_SR_"+masses.at(i)).c_str(), ("c_mX_SR_"+masses.at(i)).c_str(), 700, 700);
		  h_mX_SR->SetTitle(("m_{X} Peak in Signal MC (m_{X}="+masses.at(i)+" GeV); m_{X} (GeV)").c_str());
		  h_mX_SR->Rebin(rebin);
		  h_mX_SR_JECp1->Rebin(rebin);
		  h_mX_SR_JECm1->Rebin(rebin);
		h_mX_SR_JECp1->SetLineColor(kRed);
		h_mX_SR_JECm1->SetLineColor(kRed+2);
		h_mX_SR->GetXaxis()->SetRangeUser(0, 1200);
		h_mX_SR_JECp1->GetXaxis()->SetRangeUser(0, 1200);
		h_mX_SR_JECm1->GetXaxis()->SetRangeUser(0, 1200);
		TLegend *leg=new TLegend(0.7, 0.5, 0.9, 0.9);
		leg->AddEntry(h_mX_SR, "Baseline");
		i*/		
		//Params par, par_JECp1, par_JECm1;

		TCanvas *c_mX_SR=new TCanvas(("c_mX_SR_"+masses.at(i)).c_str(), ("c_mX_SR_"+masses.at(i)).c_str(), 700, 700);
		h_mX_SR->SetTitle(("m_{X} Peak in Signal MC (m_{X}="+masses.at(i)+" GeV); m_{X} (GeV)").c_str());
		h_mX_SR->Rebin(rebin);
		double nE = h_mX_SR->GetSumOfWeights();
		//h_mX_SR->Scale(1./nE);
		/*		h_mX_SR_JECp1_KinFit->Rebin(rebin);
				h_mX_SR_JECm1_KinFit->Rebin(rebin);
				h_mX_SR_JECp1_KinFit->SetLineColor(kRed);
				h_mX_SR_JECm1_KinFit->SetLineColor(kRed+2);
				h_mX_SR->GetXaxis()->SetRangeUser(0, 1200);
				h_mX_SR_JECp1_KinFit->GetXaxis()->SetRangeUser(0, 1200);
				h_mX_SR_JECm1_KinFit->GetXaxis()->SetRangeUser(0, 1200);
				h_mX_SR_JERp1_KinFit->Rebin(rebin);
				h_mX_SR_JERm1_KinFit->Rebin(rebin);
				h_mX_SR_JERp1_KinFit->SetLineColor(kAzure+1);
				h_mX_SR_JERm1_KinFit->SetLineColor(kBlue+1);
				h_mX_SR_JERp1_KinFit->GetXaxis()->SetRangeUser(0, 1200);
				h_mX_SR_JERm1_KinFit->GetXaxis()->SetRangeUser(0, 1200);
				h_mX_SR_bTagDown_KinFit->Rebin(rebin);
				h_mX_SR_bTagUp_KinFit->Rebin(rebin);
				h_mX_SR_bTagDown_KinFit->SetLineColor(kGreen+1);
				h_mX_SR_bTagUp_KinFit->SetLineColor(kGreen+3);
				h_mX_SR_bTagDown_KinFit->GetXaxis()->SetRangeUser(0, 1200);
				h_mX_SR_bTagUp_KinFit->GetXaxis()->SetRangeUser(0, 1200);

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
				*/
		TLegend *leg = new TLegend(0.75625,0.7721654,0.5765625,0.8903839,NULL,"brNDC");
		leg->SetBorderSize(0);
		leg->SetTextSize(0.035);
		leg->SetLineColor(1);
		leg->SetLineStyle(1);
		leg->SetLineWidth(2);
		leg->SetFillColor(0);
		leg->SetFillStyle(0);


		leg->AddEntry(h_mX_SR, "Signal MC");
		Params params_vg;
		RooPlot *plot_vg=fitSignal(h_mX_SR, masses.at(i), kBlack, leg, params_vg, true);
		v_sg_p0.push_back(params_vg.sg_p0); v_sg_p0_err.push_back(params_vg.sg_p0_err);
		v_sg_p1.push_back(params_vg.sg_p1); v_sg_p1_err.push_back(params_vg.sg_p1_err);
		v_sg_p2.push_back(params_vg.sg_p2); v_sg_p2_err.push_back(params_vg.sg_p2_err);
		v_sg_p3.push_back(params_vg.sg_p3); v_sg_p3_err.push_back(params_vg.sg_p3_err);
		v_sg_p4.push_back(params_vg.sg_p4); v_sg_p4_err.push_back(params_vg.sg_p4_err);	
		v_sg_p5.push_back(params_vg.sg_p5); v_sg_p5_err.push_back(params_vg.sg_p5_err);
		v_sg_p6.push_back(params_vg.sg_p6); v_sg_p6_err.push_back(params_vg.sg_p6_err);

		/*		RooPlot *plot_JECp1_KinFit, *plot_JECm1_KinFit;
				Params par_JERp1_KinFit, par_JERm1_KinFit;
				RooPlot *plot_JERp1_KinFit, *plot_JERm1_KinFit;
				Params par_Trigp1_KinFit, par_Trigm1_KinFit;
				RooPlot *plot_Trigp1_KinFit, *plot_Trigm1_KinFit;
				Params par_bTagDown_KinFit, par_bTagUp_KinFit;
				RooPlot *plot_bTagDown_KinFit, *plot_bTagUp_KinFit;
				if (!focus) {
				leg->AddEntry(h_mX_SR_JECp1_KinFit, "JEC +1 #sigma");
				leg->AddEntry(h_mX_SR_JECm1_KinFit, "JEC -1 #sigma");

				plot_JECp1_KinFit=fitSignal(h_mX_SR_JECp1_KinFit, masses.at(i), kRed, leg, par_JECp1_KinFit, true);
				plot_JECm1_KinFit=fitSignal(h_mX_SR_JECm1_KinFit, masses.at(i), kRed+2, leg, par_JECm1_KinFit, true);

				leg->AddEntry(h_mX_SR_JERp1_KinFit, "JER +1 #sigma");
				leg->AddEntry(h_mX_SR_JERm1_KinFit, "JER -1 #sigma");

				plot_JERp1_KinFit=fitSignal(h_mX_SR_JERp1_KinFit, masses.at(i), kAzure+1, leg, par_JERp1_KinFit, true);
				plot_JERm1_KinFit=fitSignal(h_mX_SR_JERm1_KinFit, masses.at(i), kBlue+1, leg, par_JERm1_KinFit, true);

				leg->AddEntry(h_mX_SR_Trigp1_KinFit, "Trig +1 #sigma");
				leg->AddEntry(h_mX_SR_Trigm1_KinFit, "Trig -1 #sigma");

				plot_Trigp1_KinFit=fitSignal(h_mX_SR_Trigp1_KinFit, masses.at(i), kPink+1, leg, par_Trigp1_KinFit, true);
				plot_Trigm1_KinFit=fitSignal(h_mX_SR_Trigm1_KinFit, masses.at(i), kPink+3, leg, par_Trigm1_KinFit, true);

				leg->AddEntry(h_mX_SR_bTagDown_KinFit, "bTag +1 #sigma");
				leg->AddEntry(h_mX_SR_bTagUp_KinFit, "bTag -1 #sigma");

				plot_bTagDown_KinFit=fitSignal(h_mX_SR_bTagDown_KinFit, masses.at(i), kPink+1, leg, par_bTagDown_KinFit, true);
				plot_bTagUp_KinFit=fitSignal(h_mX_SR_bTagUp_KinFit, masses.at(i), kPink+3, leg, par_bTagUp_KinFit, true);
				}
				plot_vg->SetMaximum(plot_vg->GetMaximum()*1.2);
				plot_vg->Draw();
				if (!focus) 
				{
				plot_JECp1_KinFit->Draw("same");
				plot_JECm1_KinFit->Draw("same");
				plot_JERp1_KinFit->Draw("same");
				plot_JERm1_KinFit->Draw("same");	
				plot_Trigp1_KinFit->Draw("same");
				plot_Trigm1_KinFit->Draw("same");
				plot_bTagUp_KinFit->Draw("same");
				plot_bTagDown_KinFit->Draw("same");
				}
				*/
		plot_vg->SetTitle("");

		plot_vg->GetXaxis()->SetTitleOffset(1.);
		plot_vg->GetXaxis()->SetLabelSize(0.03);
		plot_vg->GetYaxis()->SetLabelSize(0.05);
		plot_vg->GetYaxis()->SetTitleSize(0.04);
		plot_vg->GetXaxis()->SetTitleSize(0.04);
		plot_vg->GetYaxis()->SetLabelSize(.03);
		plot_vg->GetYaxis()->SetTitleOffset(1.2);

		plot_vg->Draw("same");
		leg->SetFillColor(0);
		leg->Draw();
		CMS_lumi(c_mX_SR, iPeriod, iPos );
		c_mX_SR->SaveAs(("SignalFits/c_mX_SR_"+masses.at(i)+".png").c_str());
		c_mX_SR->SetLogy();
		c_mX_SR->SaveAs(("SignalFits/c_mX_SR_"+masses.at(i)+"Log.png").c_str());

		outfile<<"<br/><hr/>"<<std::endl;
		outfile<<"<h2> mX = "<<masses.at(i)<<" </h2>"<<std::endl;
		outfile<<"<table border='1'>"<<std::endl;
		outfile<<" <tr>"<<std::endl;
		outfile<<"  <td>"<<std::endl;
		outfile<<"   <img src='"<<("c_mX_SR_"+masses.at(i)+".png")<<"'/><br/>"<<std::endl;
		outfile<<"   <h2 align='center'>Without Kin-Fit. Fitted to an Exp-Gauss-Exp function.</h2><br/>"<<std::endl;
		outfile<<"   === Baseline plot === </br>"<<std::endl;
		/*outfile<<"   norm = "<<h_mX_SR->GetSumOfWeights()*totalLumi*prodXsec_1/nSignal_init<<" <br/>"<<std::endl;
		  outfile<<"   sg_p0 = "<<par.sg_p0<<" +- "<<par.sg_p0_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p1 = "<<par.sg_p1<<" +- "<<par.sg_p1_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p2 = "<<par.sg_p2<<" +- "<<par.sg_p2_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p3 = "<<par.sg_p3<<" +- "<<par.sg_p3_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p4 = "<<par.sg_p4<<" +- "<<par.sg_p4_err<<" <br/>"<<std::endl;
		  if (!focus) 
		  {
		  outfile<<"   <center><input type='button' onclick=\"return toggleMe('"<<masses.at(i)<<"')\" value='Systematics'></center><br/>"<<std::endl;
		  outfile<<"   <div id=\""<<masses.at(i)<<"\" style=\"display:none\">"<<std::endl;
		  outfile<<"   === JEC +1 sigma === <br/>"<<std::endl;
		  outfile<<"   norm = "<<h_mX_SR_JECp1->GetSumOfWeights()<<" <br/>"<<std::endl;
		  outfile<<"   sg_p0 = "<<par_JECp1.sg_p0<<" +- "<<par_JECp1.sg_p0_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p1 = "<<par_JECp1.sg_p1<<" +- "<<par_JECp1.sg_p1_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p2 = "<<par_JECp1.sg_p2<<" +- "<<par_JECp1.sg_p2_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p3 = "<<par_JECp1.sg_p3<<" +- "<<par_JECp1.sg_p3_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p4 = "<<par_JECp1.sg_p4<<" +- "<<par_JECp1.sg_p4_err<<" <br/>"<<std::endl;
		  outfile<<"   === JEC -1 sigma === <br/>"<<std::endl;
		  outfile<<"   norm = "<<h_mX_SR_JECm1->GetSumOfWeights()<<" <br/>"<<std::endl;
		  outfile<<"   sg_p0 = "<<par_JECm1.sg_p0<<" +- "<<par_JECm1.sg_p0_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p1 = "<<par_JECm1.sg_p1<<" +- "<<par_JECm1.sg_p1_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p2 = "<<par_JECm1.sg_p2<<" +- "<<par_JECm1.sg_p2_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p3 = "<<par_JECm1.sg_p3<<" +- "<<par_JECm1.sg_p3_err<<" <br/>"<<std::endl;
		  outfile<<"   sg_p4 = "<<par_JECm1.sg_p4<<" +- "<<par_JECm1.sg_p4_err<<" <br/>"<<std::endl;
		  outfile<<"   === === <br/>"<<std::endl;
		  outfile<<"   </div>"<<std::endl;

		  }
		  outfile<<"  </td>"<<std::endl;
		  outfile<<"  <td>"<<std::endl;
		  outfile<<"   <img src='"<<("c_mX_SR_"+masses.at(i)+".png")<<"'/><br/>"<<std::endl;
		  outfile<<"   <h2 align='center'>With Kin-Fit. Fitted to an Exp-Gauss-Exp function.</h2><br/>"<<std::endl;
		  */		outfile<<"   === Baseline plot === </br>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR->GetSumOfWeights()*totalLumi*prodXsec_1/nSignal_init<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 param "<<params_vg.sg_p0<<"  "<<params_vg.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 param "<<params_vg.sg_p1<<"  "<<params_vg.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 param "<<params_vg.sg_p2<<"  "<<params_vg.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 param "<<params_vg.sg_p3<<"  "<<params_vg.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 param "<<params_vg.sg_p4<<"  "<<params_vg.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p5 param "<<params_vg.sg_p5<<"  "<<params_vg.sg_p5_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p6 param "<<params_vg.sg_p6<<"  "<<params_vg.sg_p6_err<<" <br/>"<<std::endl;
		/*		if (!focus) 
				{
				outfile<<"   <center><input type='button' onclick=\"return toggleMe('"<<masses.at(i)<<"_KinFit')\" value='Systematics'></center><br/>"<<std::endl;
				outfile<<"   <div id=\""<<masses.at(i)<<"_KinFit\" style=\"display:none\">"<<std::endl;
				outfile<<"   === JEC +1 sigma === <br/>"<<std::endl;
				outfile<<"   norm = "<<h_mX_SR_JECp1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		// outfile<<"   chi2/ndof = "<<plot_JECp1_KinFit->chiSquare()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_JECp1_KinFit.sg_p0<<" +- "<<par_JECp1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_JECp1_KinFit.sg_p1<<" +- "<<par_JECp1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_JECp1_KinFit.sg_p2<<" +- "<<par_JECp1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_JECp1_KinFit.sg_p3<<" +- "<<par_JECp1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_JECp1_KinFit.sg_p4<<" +- "<<par_JECp1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === JEC -1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_JECm1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		// outfile<<"   chi2/ndof = "<<plot_JECm1_KinFit->chiSquare()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_JECm1_KinFit.sg_p0<<" +- "<<par_JECm1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_JECm1_KinFit.sg_p1<<" +- "<<par_JECm1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_JECm1_KinFit.sg_p2<<" +- "<<par_JECm1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_JECm1_KinFit.sg_p3<<" +- "<<par_JECm1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_JECm1_KinFit.sg_p4<<" +- "<<par_JECm1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === JER +1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_JERp1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_JERp1_KinFit.sg_p0<<" +- "<<par_JERp1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_JERp1_KinFit.sg_p1<<" +- "<<par_JERp1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_JERp1_KinFit.sg_p2<<" +- "<<par_JERp1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_JERp1_KinFit.sg_p3<<" +- "<<par_JERp1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_JERp1_KinFit.sg_p4<<" +- "<<par_JERp1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === JER -1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_JERm1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_JERm1_KinFit.sg_p0<<" +- "<<par_JERm1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_JERm1_KinFit.sg_p1<<" +- "<<par_JERm1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_JERm1_KinFit.sg_p2<<" +- "<<par_JERm1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_JERm1_KinFit.sg_p3<<" +- "<<par_JERm1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_JERm1_KinFit.sg_p4<<" +- "<<par_JERm1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === === <br/>"<<std::endl;
		outfile<<"   </div>"<<std::endl;
		outfile<<"   === === <br/>"<<std::endl;
		outfile<<"   === Trig +1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_Trigp1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_Trigp1_KinFit.sg_p0<<" +- "<<par_Trigp1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_Trigp1_KinFit.sg_p1<<" +- "<<par_Trigp1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_Trigp1_KinFit.sg_p2<<" +- "<<par_Trigp1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_Trigp1_KinFit.sg_p3<<" +- "<<par_Trigp1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_Trigp1_KinFit.sg_p4<<" +- "<<par_Trigp1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === Trig -1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_Trigm1_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_Trigm1_KinFit.sg_p0<<" +- "<<par_Trigm1_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_Trigm1_KinFit.sg_p1<<" +- "<<par_Trigm1_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_Trigm1_KinFit.sg_p2<<" +- "<<par_Trigm1_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_Trigm1_KinFit.sg_p3<<" +- "<<par_Trigm1_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_Trigm1_KinFit.sg_p4<<" +- "<<par_Trigm1_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === BTag +1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_bTagDown_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_bTagDown_KinFit.sg_p0<<" +- "<<par_bTagDown_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_bTagDown_KinFit.sg_p1<<" +- "<<par_bTagDown_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_bTagDown_KinFit.sg_p2<<" +- "<<par_bTagDown_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_bTagDown_KinFit.sg_p3<<" +- "<<par_bTagDown_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_bTagDown_KinFit.sg_p4<<" +- "<<par_bTagDown_KinFit.sg_p4_err<<" <br/>"<<std::endl;
		outfile<<"   === BTag -1 sigma === <br/>"<<std::endl;
		outfile<<"   norm = "<<h_mX_SR_bTagUp_KinFit->GetSumOfWeights()<<" <br/>"<<std::endl;
		outfile<<"   sg_p0 = "<<par_bTagUp_KinFit.sg_p0<<" +- "<<par_bTagUp_KinFit.sg_p0_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p1 = "<<par_bTagUp_KinFit.sg_p1<<" +- "<<par_bTagUp_KinFit.sg_p1_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p2 = "<<par_bTagUp_KinFit.sg_p2<<" +- "<<par_bTagUp_KinFit.sg_p2_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p3 = "<<par_bTagUp_KinFit.sg_p3<<" +- "<<par_bTagUp_KinFit.sg_p3_err<<" <br/>"<<std::endl;
		outfile<<"   sg_p4 = "<<par_bTagUp_KinFit.sg_p4<<" +- "<<par_bTagUp_KinFit.sg_p4_err<<" <br/>"<<std::endl;

		outfile<<"   === === <br/>"<<std::endl;
		outfile<<"   </div>"<<std::endl;
		outfile<<"   === === <br/>"<<std::endl;
		double sg_p0_errStat=params_vg.sg_p0_err;
		double sg_p0_errSyst[]={params_vg.sg_p0,
		par_JECp1_KinFit.sg_p0, par_JECm1_KinFit.sg_p0,
			par_JERp1_KinFit.sg_p0, par_JERm1_KinFit.sg_p0,
			par_bTagUp_KinFit.sg_p0, par_bTagDown_KinFit.sg_p0,
			par_Trigp1_KinFit.sg_p0, par_Trigm1_KinFit.sg_p0};
	double sg_p0_errSyst_min=params_vg.sg_p0-(*std::min_element(sg_p0_errSyst, sg_p0_errSyst+7));
	double sg_p0_errSyst_max=(*std::max_element(sg_p0_errSyst, sg_p0_errSyst+7))-params_vg.sg_p0;
	outfile<<"   Uncertainty on sg_p0 = "<<params_vg.sg_p0<<" +- "<<sg_p0_errStat<<" (stat) - "<<sg_p0_errSyst_min<<" + "<<sg_p0_errSyst_max<<" (syst); -"<<quad(sg_p0_errStat/2., sg_p0_errSyst_min)<<"/+"<<quad(sg_p0_errStat/2., sg_p0_errSyst_max)<<" (total) <br/>"<<std::endl;
	double sg_p1_errStat=params_vg.sg_p1_err;
	double sg_p1_errSyst[]={params_vg.sg_p1,
		par_JECp1_KinFit.sg_p1, par_JECm1_KinFit.sg_p1,
		par_JERp1_KinFit.sg_p1, par_JERm1_KinFit.sg_p1,
		par_bTagUp_KinFit.sg_p1, par_bTagDown_KinFit.sg_p1,
		par_Trigp1_KinFit.sg_p1, par_Trigm1_KinFit.sg_p1,};
	double sg_p1_errSyst_min=params_vg.sg_p1-(*std::min_element(sg_p1_errSyst, sg_p1_errSyst+7));
	double sg_p1_errSyst_max=(*std::max_element(sg_p1_errSyst, sg_p1_errSyst+7))-params_vg.sg_p1;
	outfile<<"   Uncertainty on sg_p1 = "<<params_vg.sg_p1<<" +- "<<sg_p1_errStat<<" (stat) - "<<sg_p1_errSyst_min<<" + "<<sg_p1_errSyst_max<<" (syst); -"<<quad(sg_p1_errStat/2., sg_p1_errSyst_min)<<"/+"<<quad(sg_p1_errStat/2., sg_p1_errSyst_max)<<" (total) <br/>"<<std::endl;
	double sg_p2_errStat=params_vg.sg_p2_err;
	double sg_p2_errSyst[]={params_vg.sg_p2,
		par_JECp1_KinFit.sg_p2, par_JECm1_KinFit.sg_p2,
		par_JERp1_KinFit.sg_p2, par_JERm1_KinFit.sg_p2,
		par_bTagUp_KinFit.sg_p2, par_bTagDown_KinFit.sg_p2,
		par_Trigp1_KinFit.sg_p2, par_Trigm1_KinFit.sg_p2};
	double sg_p2_errSyst_min=params_vg.sg_p2-(*std::min_element(sg_p2_errSyst, sg_p2_errSyst+7));
	double sg_p2_errSyst_max=(*std::max_element(sg_p2_errSyst, sg_p2_errSyst+7))-params_vg.sg_p2;
	outfile<<"   Uncertainty on sg_p2 = "<<params_vg.sg_p2<<" +- "<<sg_p2_errStat<<" (stat) - "<<sg_p2_errSyst_min<<" + "<<sg_p2_errSyst_max<<" (syst); -"<<quad(sg_p2_errStat/2., sg_p2_errSyst_min)<<"/+"<<quad(sg_p2_errStat/2., sg_p2_errSyst_max)<<" (total) <br/>"<<std::endl;
	double sg_p3_errStat=params_vg.sg_p3_err;
	double sg_p3_errSyst[]={params_vg.sg_p3,
		par_JECp1_KinFit.sg_p3, par_JECm1_KinFit.sg_p3,
		par_JERp1_KinFit.sg_p3, par_JERm1_KinFit.sg_p3,
		par_bTagUp_KinFit.sg_p3, par_bTagDown_KinFit.sg_p3,
		par_Trigp1_KinFit.sg_p3, par_Trigm1_KinFit.sg_p3};
	double sg_p3_errSyst_min=params_vg.sg_p3-(*std::min_element(sg_p3_errSyst, sg_p3_errSyst+7));
	double sg_p3_errSyst_max=(*std::max_element(sg_p3_errSyst, sg_p3_errSyst+7))-params_vg.sg_p3;
	outfile<<"   Uncertainty on sg_p3 = "<<params_vg.sg_p3<<" +- "<<sg_p3_errStat<<" (stat) - "<<sg_p3_errSyst_min<<" + "<<sg_p3_errSyst_max<<" (syst); -"<<quad(sg_p3_errStat/2., sg_p3_errSyst_min)<<"/+"<<quad(sg_p3_errStat/2.,
			sg_p3_errSyst_max)<<" (total) <br/>"<<std::endl;

	double sg_p4_errStat=params_vg.sg_p4_err;
	double sg_p4_errSyst[]={params_vg.sg_p4,
		par_JECp1_KinFit.sg_p4, par_JECm1_KinFit.sg_p4,
		par_JERp1_KinFit.sg_p4, par_JERm1_KinFit.sg_p4,
		par_bTagUp_KinFit.sg_p4, par_bTagDown_KinFit.sg_p4,
		par_Trigp1_KinFit.sg_p4, par_Trigm1_KinFit.sg_p4};
	double sg_p4_errSyst_min=params_vg.sg_p4-(*std::min_element(sg_p4_errSyst, sg_p4_errSyst+7));
	double sg_p4_errSyst_max=(*std::max_element(sg_p4_errSyst, sg_p4_errSyst+7))-params_vg.sg_p4;
	outfile<<"   Uncertainty on sg_p4 = "<<params_vg.sg_p4<<" +- "<<sg_p4_errStat<<" (stat) - "<<sg_p4_errSyst_min<<" + "<<sg_p4_errSyst_max<<" (syst); -"<<quad(sg_p4_errStat/2., sg_p4_errSyst_min)<<"/+"<<quad(sg_p4_errStat/2., sg_p4_errSyst_max)<<" (total) <br/>"<<std::endl;



	outfile<<"JEC       lnN     "<<lnN(h_mX_SR->GetSumOfWeights(), h_mX_SR_JECp1_KinFit->GetSumOfWeights(), h_mX_SR_JECm1_KinFit->GetSumOfWeights())<<"  -"<<" <br/>"<<std::endl;
	outfile<<"JER       lnN     "<<lnN(h_mX_SR->GetSumOfWeights(), h_mX_SR_JERp1_KinFit->GetSumOfWeights(), h_mX_SR_JERm1_KinFit->GetSumOfWeights())<<"  -"<<" <br/>"<<std::endl;
	outfile<<"trig lnN     "<<lnN(h_mX_SR->GetSumOfWeights(), h_mX_SR_Trigp1_KinFit->GetSumOfWeights(), h_mX_SR_Trigm1_KinFit->GetSumOfWeights())<<"  -"<<" <br/>"<<std::endl;
	outfile<<"bTag lnN     "<<lnN(h_mX_SR->GetSumOfWeights(), h_mX_SR_bTagUp_KinFit->GetSumOfWeights(), h_mX_SR_bTagDown_KinFit->GetSumOfWeights())<<"  -"<<" <br/>"<<std::endl;

	outfile<<"sg_p0     param   "<<params_vg.sg_p0<<" -"<<quad(sg_p0_errStat/2., sg_p0_errSyst_min)<<"/+"<<quad(sg_p0_errStat/2., sg_p0_errSyst_max)<<" <br/>"<<std::endl;
	outfile<<"sg_p1     param   "<<params_vg.sg_p1<<" -"<<quad(sg_p1_errStat/2., sg_p1_errSyst_min)<<"/+"<<quad(sg_p1_errStat/2., sg_p1_errSyst_max)<<" <br/>"<<std::endl;
	outfile<<"sg_p2     param   "<<params_vg.sg_p2<<"  -"<<quad(sg_p2_errStat/2., sg_p2_errSyst_min)<<"/+"<<quad(sg_p2_errStat/2., sg_p2_errSyst_max)<<" <br/>"<<std::endl;
	outfile<<"sg_p3     param   "<<params_vg.sg_p3<<"  -"<<quad(sg_p3_errStat/2., sg_p3_errSyst_min)<<"/+"<<quad(sg_p3_errStat/2., sg_p3_errSyst_max)<<" <br/>"<<std::endl;
	outfile<<"sg_p4     param   "<<params_vg.sg_p4<<"  -"<<quad(sg_p4_errStat/2., sg_p4_errSyst_min)<<"/+"<<quad(sg_p4_errStat/2., sg_p4_errSyst_max)<<" <br/>"<<std::endl;




	}
	*/	outfile<<"   </div>"<<std::endl;
	outfile<<"  </td>"<<std::endl;

	outfile<<" </tr>"<<std::endl;
	outfile<<"</table>"<<std::endl;

	// Close all files
	file->Close();
	/*	file_JECp1->Close();
		file_JECm1->Close();
		file_JERp1->Close();
		file_JERm1->Close();
		file_Trigm1->Close();
		file_bTagDown->Close();
		file_bTagUp->Close();
		*/}


	return 0;
}

