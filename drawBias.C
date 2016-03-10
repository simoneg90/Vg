{
    TCanvas* c1 = new TCanvas("c1","c1", 700, 700);
    TFile * f = new TFile("mlfitoutput750.root");
    tree_fit_sb->Draw("(mu-0.136)/muHiErr>>h(40, -4,4)");
    c1->SaveAs("lau1_1_750.png");
    delete f;
    
    TFile * f = new TFile("mlfitoutput750_5.root");
    tree_fit_sb->Draw("(mu-0.680)/muHiErr>>h(40, -4,4)");
    c1->SaveAs("lau1_5_750.png");
    delete f;
    
    TFile * f = new TFile("mlfitoutput750_3.root");
    tree_fit_sb->Draw("(mu-0.408)/muHiErr>>h(40, -4,4)");
    c1->SaveAs("lau1_3_750.png");
    delete f;
    
    
    TFile * f = new TFile("mlfitoutput2000.root");
    tree_fit_sb->Draw("(mu-0.016)/muHiErr>>h(40, -4,4)");
    c1->SaveAs("lau1_1_2000.png");
    delete f;
    
    
    TFile * f = new TFile("mlfitoutput2000_5.root");
    tree_fit_sb->Draw("(mu-0.080)/muHiErr>>h(40, -4,4)");
    c1->SaveAs("lau1_5_2000.png");
    delete f;
    
    TFile * f = new TFile("mlfitoutput2000_3.root");
    tree_fit_sb->Draw("(mu-0.048)/muHiErr>>h(40, -4,4)");
    c1->SaveAs("lau1_3_2000.png");
    delete f;
}