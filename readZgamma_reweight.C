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



void readZgamma_reweight() {
    setTDRStyle();
    gStyle->SetOptStat(0);
    
    writeExtraText = true;       // if extra text
    extraText  = "Preliminary";  // default extra text is "Preliminary"
    lumi_13TeV  = "7.6 fb^{-1} (2016)"; // default is "19.7 fb^{-1}"

    
    // Fixed size dimensions of array or collections stored in the TTree if any.
    const Int_t kMaxpassFilter_HBHE = 1;
    const Int_t kMaxpassFilter_HBHELoose = 1;
    const Int_t kMaxpassFilter_HBHETight = 1;
    const Int_t kMaxpassFilter_CSCHalo = 1;
    const Int_t kMaxpassFilter_HCALlaser = 1;
    const Int_t kMaxpassFilter_ECALDeadCell = 1;
    const Int_t kMaxpassFilter_GoodVtx = 1;
    const Int_t kMaxpassFilter_TrkFailure = 1;
    const Int_t kMaxpassFilter_EEBadSc = 1;
    const Int_t kMaxpassFilter_ECALlaser = 1;
    const Int_t kMaxpassFilter_TrkPOG = 1;
    const Int_t kMaxpassFilter_TrkPOG_manystrip = 1;
    const Int_t kMaxpassFilter_TrkPOG_toomanystrip = 1;
    const Int_t kMaxpassFilter_TrkPOG_logError = 1;
    const Int_t kMaxpassFilter_METFilters = 1;
    
    // Declaration of leaf types
    Int_t           genParticle_N;
    vector<float>   *genParticle_pt;
    vector<float>   *genParticle_px;
    vector<float>   *genParticle_py;
    vector<float>   *genParticle_pz;
    vector<float>   *genParticle_e;
    vector<float>   *genParticle_eta;
    vector<float>   *genParticle_phi;
    vector<float>   *genParticle_mass;
    vector<int>     *genParticle_pdgId;
    vector<int>     *genParticle_origin;
    vector<int>     *genParticle_status;
    vector<vector<int> > *genParticle_mother;
    vector<int>     *genParticle_nMoth;
    vector<int>     *genParticle_nDau;
    vector<vector<int> > *genParticle_dau;
    Float_t         lheV_pt;
    Float_t         lheHT;
    Float_t         lheNj;
    Float_t         genWeight;
    Float_t         qScale;
    vector<float>   *PDF_x;
    vector<float>   *PDF_xPDF;
    vector<int>     *PDF_id;
    Int_t           ph_N;
    vector<int>     *ph_pdgId;
    vector<float>   *ph_charge;
    vector<float>   *ph_e;
    vector<float>   *ph_eta;
    vector<float>   *ph_phi;
    vector<float>   *ph_mass;
    vector<float>   *ph_pt;
    vector<float>   *ph_et;
    vector<float>   *ph_rho;
    vector<float>   *ph_fixedGridRho;
    vector<float>   *ph_superCluster_eta;
    vector<float>   *ph_superCluster_phi;
    vector<float>   *ph_sigmaIetaIeta;
    vector<float>   *ph_hOverE;
    vector<float>   *ph_isoGamma;
    vector<float>   *ph_isoCh;
    vector<bool>    *ph_passEleVeto;
    vector<int>     *ph_passLooseId;
    vector<int>     *ph_passMediumId;
    vector<int>     *ph_passTightId;
    vector<float>   *ph_mvaVal;
    vector<float>   *ph_mvaCat;
    Int_t           el_N;
    vector<int>     *el_pdgId;
    vector<float>   *el_charge;
    vector<float>   *el_e;
    vector<float>   *el_eta;
    vector<float>   *el_phi;
    vector<float>   *el_mass;
    vector<float>   *el_pt;
    vector<float>   *el_et;
    vector<float>   *el_superCluster_eta;
    vector<int>     *el_isVetoElectron;
    vector<int>     *el_isMediumElectron;
    vector<int>     *el_isTightElectron;
    vector<int>     *el_isHeepElectron;
    vector<int>     *el_isHeep51Electron;
    vector<int>     *el_isLooseElectron;
    vector<int>     *el_isVetoElectronBoosted;
    vector<int>     *el_isMediumElectronBoosted;
    vector<int>     *el_isTightElectronBoosted;
    vector<int>     *el_isHeepElectronBoosted;
    vector<int>     *el_isHeep51ElectronBoosted;
    vector<int>     *el_isLooseElectronBoosted;
    Int_t           mu_N;
    vector<int>     *mu_pdgId;
    vector<float>   *mu_charge;
    vector<float>   *mu_e;
    vector<float>   *mu_eta;
    vector<float>   *mu_phi;
    vector<float>   *mu_mass;
    vector<float>   *mu_pt;
    vector<int>     *mu_isHighPtMuon;
    vector<int>     *mu_isTightMuon;
    vector<int>     *mu_isLooseMuon;
    vector<int>     *mu_isPFMuon;
    vector<int>     *mu_isSoftMuon;
    Float_t         rho;
    Int_t           jetAK4_N;
    vector<float>   *jetAK4_pt;
    vector<float>   *jetAK4_eta;
    vector<float>   *jetAK4_mass;
    vector<float>   *jetAK4_phi;
    vector<float>   *jetAK4_e;
    vector<float>   *jetAK4_jec;
    vector<bool>    *jetAK4_IDLoose;
    vector<bool>    *jetAK4_IDTight;
    vector<bool>    *jetAK4_IDTightLepVeto;
    vector<int>     *jetAK4_charge;
    vector<float>   *jetAK4_cisv;
    vector<float>   *jetAK4_vtxMass;
    vector<float>   *jetAK4_vtxNtracks;
    vector<float>   *jetAK4_vtx3DVal;
    vector<float>   *jetAK4_vtx3DSig;
    vector<int>     *jetAK4_partonFlavour;
    vector<int>     *jetAK4_hadronFlavour;
    vector<int>     *jetAK4_genParton_pdgID;
    vector<int>     *jetAK4_nbHadrons;
    vector<int>     *jetAK4_ncHadrons;
    Int_t           jetAK8_N;
    vector<float>   *jetAK8_pt;
    vector<float>   *jetAK8_eta;
    vector<float>   *jetAK8_mass;
    vector<float>   *jetAK8_phi;
    vector<float>   *jetAK8_e;
    vector<float>   *jetAK8_jec;
    vector<float>   *jetAK8_jecUp;
    vector<float>   *jetAK8_jecDown;

    vector<bool>    *jetAK8_IDLoose;
    vector<bool>    *jetAK8_IDTight;
    vector<bool>    *jetAK8_IDTightLepVeto;
    vector<int>     *jetAK8_charge;
    vector<float>   *jetAK8_Hbbtag;
    vector<int>     *jetAK8_partonFlavour;
    vector<int>     *jetAK8_hadronFlavour;
    vector<int>     *jetAK8_genParton_pdgID;
    vector<int>     *jetAK8_nbHadrons;
    vector<int>     *jetAK8_ncHadrons;
    vector<float>   *jetAK8_csv;
    vector<float>   *jetAK8_tau1;
    vector<float>   *jetAK8_tau2;
    vector<float>   *jetAK8_tau3;
    vector<float>   *jetAK8_pruned_mass;
    vector<float>   *jetAK8_pruned_massCorr;
    vector<float>   *jetAK8_pruned_jec;
    vector<float>   *jetAK8_pruned_jecUp;
    vector<float>   *jetAK8_pruned_jecDown;

    vector<float>   *jetAK8_softdrop_mass;
    vector<float>   *jetAK8_softdrop_massCorr;
    vector<float>   *jetAK8_softdrop_jec;
    vector<int>     *subjetAK8_softdrop_N;
    vector<vector<float> > *subjetAK8_softdrop_pt;
    vector<vector<float> > *subjetAK8_softdrop_eta;
    vector<vector<float> > *subjetAK8_softdrop_mass;
    vector<vector<float> > *subjetAK8_softdrop_phi;
    vector<vector<float> > *subjetAK8_softdrop_e;
    vector<vector<int> > *subjetAK8_softdrop_charge;
    vector<vector<int> > *subjetAK8_softdrop_partonFlavour;
    vector<vector<int> > *subjetAK8_softdrop_hadronFlavour;
    vector<vector<float> > *subjetAK8_softdrop_csv;
    vector<int>     *subjetAK8_pruned_N;
    vector<vector<float> > *subjetAK8_pruned_pt;
    vector<vector<float> > *subjetAK8_pruned_eta;
    vector<vector<float> > *subjetAK8_pruned_mass;
    vector<vector<float> > *subjetAK8_pruned_phi;
    vector<vector<float> > *subjetAK8_pruned_e;
    vector<vector<int> > *subjetAK8_pruned_charge;
    vector<vector<int> > *subjetAK8_pruned_partonFlavour;
    vector<vector<int> > *subjetAK8_pruned_hadronFlavour;
    vector<vector<float> > *subjetAK8_pruned_csv;
    map<string,bool> *HLT_isFired;
    Bool_t          passFilter_HBHE;
    Bool_t          passFilter_HBHELoose;
    Bool_t          passFilter_HBHETight;
    Bool_t          passFilter_CSCHalo;
    Bool_t          passFilter_HCALlaser;
    Bool_t          passFilter_ECALDeadCell;
    Bool_t          passFilter_GoodVtx;
    Bool_t          passFilter_TrkFailure;
    Bool_t          passFilter_EEBadSc;
    Bool_t          passFilter_ECALlaser;
    Bool_t          passFilter_TrkPOG;
    Bool_t          passFilter_TrkPOG_manystrip;
    Bool_t          passFilter_TrkPOG_toomanystrip;
    Bool_t          passFilter_TrkPOG_logError;
    Bool_t          passFilter_METFilters;
    vector<float>   *METraw_et;
    vector<float>   *METraw_phi;
    vector<float>   *METraw_sumEt;
    vector<float>   *MET_corrPx;
    vector<float>   *MET_corrPy;
    vector<float>   *MET_et;
    vector<float>   *MET_phi;
    vector<float>   *MET_sumEt;
    Int_t           EVENT_event;
    Int_t           EVENT_run;
    Int_t           EVENT_lumiBlock;
    vector<int>     *nPuVtxTrue;
    vector<int>     *nPuVtx;
    vector<int>     *bX;
    Int_t           PV_N;
    Bool_t          PV_filter;
    vector<float>   *PV_chi2;
    vector<float>   *PV_ndof;
    vector<float>   *PV_rho;
    vector<float>   *PV_z;
    
    // List of branches
    TBranch        *b_genParticle_N;   //!
    TBranch        *b_genParticle_pt;   //!
    TBranch        *b_genParticle_px;   //!
    TBranch        *b_genParticle_py;   //!
    TBranch        *b_genParticle_pz;   //!
    TBranch        *b_genParticle_e;   //!
    TBranch        *b_genParticle_eta;   //!
    TBranch        *b_genParticle_phi;   //!
    TBranch        *b_genParticle_mass;   //!
    TBranch        *b_genParticle_pdgId;   //!
    TBranch        *b_genParticle_origin;   //!
    TBranch        *b_genParticle_status;   //!
    TBranch        *b_genParticle_mother;   //!
    TBranch        *b_genParticle_nMoth;   //!
    TBranch        *b_genParticle_nDau;   //!
    TBranch        *b_genParticle_dau;   //!
    TBranch        *b_lheV_pt;   //!
    TBranch        *b_lheHT;   //!
    TBranch        *b_lheNj;   //!
    TBranch        *b_genWeight;   //!
    TBranch        *b_qScale;   //!
    TBranch        *b_PDF_x;   //!
    TBranch        *b_PDF_xPDF;   //!
    TBranch        *b_PDF_id;   //!
    TBranch        *b_ph_N;   //!
    TBranch        *b_ph_pdgId;   //!
    TBranch        *b_ph_charge;   //!
    TBranch        *b_ph_e;   //!
    TBranch        *b_ph_eta;   //!
    TBranch        *b_ph_phi;   //!
    TBranch        *b_ph_mass;   //!
    TBranch        *b_ph_pt;   //!
    TBranch        *b_ph_et;   //!
    TBranch        *b_ph_rho;   //!
    TBranch        *b_ph_fixedGridRho;   //!
    TBranch        *b_ph_superCluster_eta;   //!
    TBranch        *b_ph_superCluster_phi;   //!
    TBranch        *b_ph_sigmaIetaIeta;   //!
    TBranch        *b_ph_hOverE;   //!
    TBranch        *b_ph_isoGamma;   //!
    TBranch        *b_ph_isoCh;   //!
    TBranch        *b_ph_passEleVeto;   //!
    TBranch        *b_ph_passLooseId;   //!
    TBranch        *b_ph_passMediumId;   //!
    TBranch        *b_ph_passTightId;   //!
    TBranch        *b_ph_mvaVal;   //!
    TBranch        *b_ph_mvaCat;   //!
    TBranch        *b_el_N;   //!
    TBranch        *b_el_pdgId;   //!
    TBranch        *b_el_charge;   //!
    TBranch        *b_el_e;   //!
    TBranch        *b_el_eta;   //!
    TBranch        *b_el_phi;   //!
    TBranch        *b_el_mass;   //!
    TBranch        *b_el_pt;   //!
    TBranch        *b_el_et;   //!
    TBranch        *b_el_superCluster_eta;   //!
    TBranch        *b_el_isVetoElectron;   //!
    TBranch        *b_el_isMediumElectron;   //!
    TBranch        *b_el_isTightElectron;   //!
    TBranch        *b_el_isHeepElectron;   //!
    TBranch        *b_el_isHeep51Electron;   //!
    TBranch        *b_el_isLooseElectron;   //!
    TBranch        *b_el_isVetoElectronBoosted;   //!
    TBranch        *b_el_isMediumElectronBoosted;   //!
    TBranch        *b_el_isTightElectronBoosted;   //!
    TBranch        *b_el_isHeepElectronBoosted;   //!
    TBranch        *b_el_isHeep51ElectronBoosted;   //!
    TBranch        *b_el_isLooseElectronBoosted;   //!
    TBranch        *b_mu_N;   //!
    TBranch        *b_mu_pdgId;   //!
    TBranch        *b_mu_charge;   //!
    TBranch        *b_mu_e;   //!
    TBranch        *b_mu_eta;   //!
    TBranch        *b_mu_phi;   //!
    TBranch        *b_mu_mass;   //!
    TBranch        *b_mu_pt;   //!
    TBranch        *b_mu_isHighPtMuon;   //!
    TBranch        *b_mu_isTightMuon;   //!
    TBranch        *b_mu_isLooseMuon;   //!
    TBranch        *b_mu_isPFMuon;   //!
    TBranch        *b_mu_isSoftMuon;   //!
    TBranch        *b_rho;   //!
    TBranch        *b_jetAK4_N;   //!
    TBranch        *b_jetAK4_pt;   //!
    TBranch        *b_jetAK4_eta;   //!
    TBranch        *b_jetAK4_mass;   //!
    TBranch        *b_jetAK4_phi;   //!
    TBranch        *b_jetAK4_e;   //!
    TBranch        *b_jetAK4_jec;   //!
    TBranch        *b_jetAK4_IDLoose;   //!
    TBranch        *b_jetAK4_IDTight;   //!
    TBranch        *b_jetAK4_IDTightLepVeto;   //!
    TBranch        *b_jetAK4_charge;   //!
    TBranch        *b_jetAK4_cisv;   //!
    TBranch        *b_jetAK4_vtxMass;   //!
    TBranch        *b_jetAK4_vtxNtracks;   //!
    TBranch        *b_jetAK4_vtx3DVal;   //!
    TBranch        *b_jetAK4_vtx3DSig;   //!
    TBranch        *b_jetAK4_partonFlavour;   //!
    TBranch        *b_jetAK4_hadronFlavour;   //!
    TBranch        *b_jetAK4_genParton_pdgID;   //!
    TBranch        *b_jetAK4_nbHadrons;   //!
    TBranch        *b_jetAK4_ncHadrons;   //!
    TBranch        *b_jetAK8_N;   //!
    TBranch        *b_jetAK8_pt;   //!
    TBranch        *b_jetAK8_eta;   //!
    TBranch        *b_jetAK8_mass;   //!
    TBranch        *b_jetAK8_phi;   //!
    TBranch        *b_jetAK8_e;   //!
    TBranch        *b_jetAK8_jec;   //!
    TBranch        *b_jetAK8_jecUp;   //!
    TBranch        *b_jetAK8_jecDown;   //!

    TBranch        *b_jetAK8_IDLoose;   //!
    TBranch        *b_jetAK8_IDTight;   //!
    TBranch        *b_jetAK8_IDTightLepVeto;   //!
    TBranch        *b_jetAK8_charge;   //!
    TBranch        *b_jetAK8_Hbbtag;   //!
    TBranch        *b_jetAK8_partonFlavour;   //!
    TBranch        *b_jetAK8_hadronFlavour;   //!
    TBranch        *b_jetAK8_genParton_pdgID;   //!
    TBranch        *b_jetAK8_nbHadrons;   //!
    TBranch        *b_jetAK8_ncHadrons;   //!
    TBranch        *b_jetAK8_csv;   //!
    TBranch        *b_jetAK8_tau1;   //!
    TBranch        *b_jetAK8_tau2;   //!
    TBranch        *b_jetAK8_tau3;   //!
    TBranch        *b_jetAK8_pruned_mass;   //!
    TBranch        *b_jetAK8_pruned_massCorr;   //!
    TBranch        *b_jetAK8_pruned_jec;   //!
    TBranch        *b_jetAK8_pruned_jecUp;   //!
    TBranch        *b_jetAK8_pruned_jecDown;   //!

    TBranch        *b_jetAK8_softdrop_mass;   //!
    TBranch        *b_jetAK8_softdrop_massCorr;   //!
    TBranch        *b_jetAK8_softdrop_jec;   //!
    TBranch        *b_subjetAK8_softdrop_N;   //!
    TBranch        *b_subjetAK8_softdrop_pt;   //!
    TBranch        *b_subjetAK8_softdrop_eta;   //!
    TBranch        *b_subjetAK8_softdrop_mass;   //!
    TBranch        *b_subjetAK8_softdrop_phi;   //!
    TBranch        *b_subjetAK8_softdrop_e;   //!
    TBranch        *b_subjetAK8_softdrop_charge;   //!
    TBranch        *b_subjetAK8_softdrop_partonFlavour;   //!
    TBranch        *b_subjetAK8_softdrop_hadronFlavour;   //!
    TBranch        *b_subjetAK8_softdrop_csv;   //!
    TBranch        *b_subjetAK8_pruned_N;   //!
    TBranch        *b_subjetAK8_pruned_pt;   //!
    TBranch        *b_subjetAK8_pruned_eta;   //!
    TBranch        *b_subjetAK8_pruned_mass;   //!
    TBranch        *b_subjetAK8_pruned_phi;   //!
    TBranch        *b_subjetAK8_pruned_e;   //!
    TBranch        *b_subjetAK8_pruned_charge;   //!
    TBranch        *b_subjetAK8_pruned_partonFlavour;   //!
    TBranch        *b_subjetAK8_pruned_hadronFlavour;   //!
    TBranch        *b_subjetAK8_pruned_csv;   //!
    TBranch        *b_HLT_isFired;   //!
    TBranch        *b_passFilter_HBHE_;   //!
    TBranch        *b_passFilter_HBHELoose_;   //!
    TBranch        *b_passFilter_HBHETight_;   //!
    TBranch        *b_passFilter_CSCHalo_;   //!
    TBranch        *b_passFilter_HCALlaser_;   //!
    TBranch        *b_passFilter_ECALDeadCell_;   //!
    TBranch        *b_passFilter_GoodVtx_;   //!
    TBranch        *b_passFilter_TrkFailure_;   //!
    TBranch        *b_passFilter_EEBadSc_;   //!
    TBranch        *b_passFilter_ECALlaser_;   //!
    TBranch        *b_passFilter_TrkPOG_;   //!
    TBranch        *b_passFilter_TrkPOG_manystrip_;   //!
    TBranch        *b_passFilter_TrkPOG_toomanystrip_;   //!
    TBranch        *b_passFilter_TrkPOG_logError_;   //!
    TBranch        *b_passFilter_METFilters_;   //!
    TBranch        *b_METraw_et;   //!
    TBranch        *b_METraw_phi;   //!
    TBranch        *b_METraw_sumEt;   //!
    TBranch        *b_MET_corrPx;   //!
    TBranch        *b_MET_corrPy;   //!
    TBranch        *b_MET_et;   //!
    TBranch        *b_MET_phi;   //!
    TBranch        *b_MET_sumEt;   //!
    TBranch        *b_EVENT_event;   //!
    TBranch        *b_EVENT_run;   //!
    TBranch        *b_EVENT_lumiBlock;   //!
    TBranch        *b_nPuVtxTrue;   //!
    TBranch        *b_nPuVtx;   //!
    TBranch        *b_bX;   //!
    TBranch        *b_PV_N;   //!
    TBranch        *b_PV_filter;   //!
    TBranch        *b_PV_chi2;   //!
    TBranch        *b_PV_ndof;   //!
    TBranch        *b_PV_rho;   //!
    TBranch        *b_PV_z;   //!
    
    genParticle_pt = 0;
    genParticle_px = 0;
    genParticle_py = 0;
    genParticle_pz = 0;
    genParticle_e = 0;
    genParticle_eta = 0;
    genParticle_phi = 0;
    genParticle_mass = 0;
    genParticle_pdgId = 0;
    genParticle_origin = 0;
    genParticle_status = 0;
    genParticle_mother = 0;
    genParticle_nMoth = 0;
    genParticle_nDau = 0;
    genParticle_dau = 0;
    PDF_x = 0;
    PDF_xPDF = 0;
    PDF_id = 0;
    ph_pdgId = 0;
    ph_charge = 0;
    ph_e = 0;
    ph_eta = 0;
    ph_phi = 0;
    ph_mass = 0;
    ph_pt = 0;
    ph_et = 0;
    ph_rho = 0;
    ph_fixedGridRho = 0;
    ph_superCluster_eta = 0;
    ph_superCluster_phi = 0;
    ph_sigmaIetaIeta = 0;
    ph_hOverE = 0;
    ph_isoGamma = 0;
    ph_isoCh = 0;
    ph_passEleVeto = 0;
    ph_passLooseId = 0;
    ph_passMediumId = 0;
    ph_passTightId = 0;
    ph_mvaVal = 0;
    ph_mvaCat = 0;
    el_pdgId = 0;
    el_charge = 0;
    el_e = 0;
    el_eta = 0;
    el_phi = 0;
    el_mass = 0;
    el_pt = 0;
    el_et = 0;
    el_superCluster_eta = 0;
    el_isVetoElectron = 0;
    el_isMediumElectron = 0;
    el_isTightElectron = 0;
    el_isHeepElectron = 0;
    el_isHeep51Electron = 0;
    el_isLooseElectron = 0;
    el_isVetoElectronBoosted = 0;
    el_isMediumElectronBoosted = 0;
    el_isTightElectronBoosted = 0;
    el_isHeepElectronBoosted = 0;
    el_isHeep51ElectronBoosted = 0;
    el_isLooseElectronBoosted = 0;
    mu_pdgId = 0;
    mu_charge = 0;
    mu_e = 0;
    mu_eta = 0;
    mu_phi = 0;
    mu_mass = 0;
    mu_pt = 0;
    mu_isHighPtMuon = 0;
    mu_isTightMuon = 0;
    mu_isLooseMuon = 0;
    mu_isPFMuon = 0;
    mu_isSoftMuon = 0;
    jetAK4_pt = 0;
    jetAK4_eta = 0;
    jetAK4_mass = 0;
    jetAK4_phi = 0;
    jetAK4_e = 0;
    jetAK4_jec = 0;
    jetAK4_IDLoose = 0;
    jetAK4_IDTight = 0;
    jetAK4_IDTightLepVeto = 0;
    jetAK4_charge = 0;
    jetAK4_cisv = 0;
    jetAK4_vtxMass = 0;
    jetAK4_vtxNtracks = 0;
    jetAK4_vtx3DVal = 0;
    jetAK4_vtx3DSig = 0;
    jetAK4_partonFlavour = 0;
    jetAK4_hadronFlavour = 0;
    jetAK4_genParton_pdgID = 0;
    jetAK4_nbHadrons = 0;
    jetAK4_ncHadrons = 0;
    jetAK8_pt = 0;
    jetAK8_eta = 0;
    jetAK8_mass = 0;
    jetAK8_phi = 0;
    jetAK8_e = 0;
    jetAK8_jec = 0;
    jetAK8_jecUp = 0;
    jetAK8_jecDown = 0;

    jetAK8_IDLoose = 0;
    jetAK8_IDTight = 0;
    jetAK8_IDTightLepVeto = 0;
    jetAK8_charge = 0;
    jetAK8_Hbbtag = 0;
    jetAK8_partonFlavour = 0;
    jetAK8_hadronFlavour = 0;
    jetAK8_genParton_pdgID = 0;
    jetAK8_nbHadrons = 0;
    jetAK8_ncHadrons = 0;
    jetAK8_csv = 0;
    jetAK8_tau1 = 0;
    jetAK8_tau2 = 0;
    jetAK8_tau3 = 0;
    jetAK8_pruned_mass = 0;
    jetAK8_pruned_massCorr = 0;
    jetAK8_pruned_jec = 0;
    jetAK8_pruned_jecUp = 0;
    jetAK8_pruned_jecDown = 0;

    jetAK8_softdrop_mass = 0;
    jetAK8_softdrop_massCorr = 0;
    jetAK8_softdrop_jec = 0;
    subjetAK8_softdrop_N = 0;
    subjetAK8_softdrop_pt = 0;
    subjetAK8_softdrop_eta = 0;
    subjetAK8_softdrop_mass = 0;
    subjetAK8_softdrop_phi = 0;
    subjetAK8_softdrop_e = 0;
    subjetAK8_softdrop_charge = 0;
    subjetAK8_softdrop_partonFlavour = 0;
    subjetAK8_softdrop_hadronFlavour = 0;
    subjetAK8_softdrop_csv = 0;
    subjetAK8_pruned_N = 0;
    subjetAK8_pruned_pt = 0;
    subjetAK8_pruned_eta = 0;
    subjetAK8_pruned_mass = 0;
    subjetAK8_pruned_phi = 0;
    subjetAK8_pruned_e = 0;
    subjetAK8_pruned_charge = 0;
    subjetAK8_pruned_partonFlavour = 0;
    subjetAK8_pruned_hadronFlavour = 0;
    subjetAK8_pruned_csv = 0;
    HLT_isFired = 0;
    METraw_et = 0;
    METraw_phi = 0;
    METraw_sumEt = 0;
    MET_corrPx = 0;
    MET_corrPy = 0;
    MET_et = 0;
    MET_phi = 0;
    MET_sumEt = 0;
    nPuVtxTrue = 0;
    nPuVtx = 0;
    bX = 0;
    PV_chi2 = 0;
    PV_ndof = 0;
    PV_rho = 0;
    PV_z = 0;
    // Set branch addresses and branch pointers
    
    const int nFiles = 19;
    const int nProcess = 9;
    const int iSM = 4;
    
    Color_t colsStack[nProcess+2] = {
        kYellow, kCyan, kOrange-3, kBlue,
        kRed-3,
        kGreen-3,
        kViolet+2, kMagenta-7, 1, 1, 1
    };
    
    /*TString sampleString[nFiles] = {
        "M(765)",
        "M(1300)",
        "M(1900)",
        "M(3250)",
        "#gamma+jets[100,200]",
        "#gamma+jets[200,400]",
        "#gamma+jets[400,600]",
        "#gamma+jets[600,#infty]",
        "QCD[100,200]",
        "QCD[200,300]",
        "QCD[300,500]",
        "QCD[500,700]",
        "QCD[700,1000]",
        "QCD[1000,1500]",
        "QCD[1500,2000]",
        "QCD[2000,#infty]",
        "W+jets[180,#infty]",
        "DY+jets[180,#infty]",
        "data"
    };*/
    
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
    
    TString fileList[nFiles] = {
        //"flatTuple_M-750.root",
        //"flatTuple_M-2000.root",
        "signal-W_0-p-014-765.root", //0
        "signal-W_0-p-014-1300.root", //1
        "signal-W_0-p-014-1900.root", //2
        "signal-W_0-p-014-3250.root", //3
        "GJets_HT-100To200.root", //4
        "GJets_HT-200To400.root", //5
        "GJets_HT-400To600.root", //6
        "GJets_HT-600ToInf.root", //7
        "QCD_HT100to200.root", //8
        "QCD_HT200to300.root", //9
        "QCD_HT300to500.root", //10
        "QCD_HT500to700.root", //11
        "QCD_HT700to1000.root", //12
        "QCD_HT1000to1500.root", //13
        "QCD_HT1500to2000.root", //14
        "QCD_HT2000toInf.root", //15
        "WJetsToQQ_HT180.root",//16
        "DYJetsToQQ_HT180.root",
        "data_77.root"
    };
    
    
    const double xsec[nFiles] = {
        0.7,
        0.7,
        0.7,
        0.7,
        5000,
        1079,
        125.9,
        43.36,
        27990000,
        1712000,
        347700,
        32100,
        6831,
        1207,
        119.9,
        25.24,
        2788,
        1187,
        1
    };
    
    int grouping[nFiles] = {
        0,
        1,
        2,
        3,
        4,
        4,
        4,
        4,
        5,
        5,
        5,
        5,
        5,
        5,
        5,
        5,
        6,
        7,
        8
    };
    
    TFile* puwFile = new TFile("puWeights_7fb.root");
    TH1D* puw = (TH1D*)puwFile->Get("puw");
    
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
    
    TH1F* kfactHistLocal[nProcess];
    for (int i=0; i!=nProcess; ++i) {
        kfactHistLocal[i] = (TH1F*)kfactHist[0][2]->Clone(Form("kfact_%d",i));
        kfactHistLocal[i]->Scale(0.);
    }
    */
    
    TH1D* _hCounter = new TH1D("hCounter", "Events counter", 5,0,5);

    TFile* hfile[nFiles];
    TTree* inputTreeFake[nFiles];
    
    TH1D* distribs[nProcess+2][nVars];
    TH2D* distribs2d[nProcess+2];
    for (int sam=0; sam!=nProcess+2; ++sam) {
        distribs2d[sam] = new TH2D(Form("distribs2d_%d",sam),
                                    ";"+vars[1]+";"+vars[2]+";",
                                    nBinsVars[1], varDown[1], varUp[1],nBinsVars[2], varDown[2], varUp[2]
                                    );
        
    }

    for (int sam=0; sam!=nProcess+2; ++sam) for (int i=0; i!=nVars; ++i)  {
        distribs[sam][i] = new TH1D(Form("distribs_%d_%d",sam,i),
                                       ";"+vars[i]+Form(";events / %1.1f",(varUp[i]-varDown[i])/nBinsVars[i])+varsBin[i],
                                       nBinsVars[i], varDown[i], varUp[i]
                                       );
        distribs[sam][i]->Sumw2();
        distribs[sam][i]->SetMarkerSize(0.8);
        if (sam <= nFiles-2 && sam >= iSM)
            distribs[sam][i]->SetFillColor(colsStack[sam]);
        if (sam < iSM)
            distribs[sam][i]->SetLineColor(colsStack[sam]);
        else
            distribs[sam][i]->SetLineColor(1);
        //else
        //    distribs[sam][i]->SetLineColor(colsStack[sam]);
        distribs[sam][i]->GetXaxis()->SetNdivisions(nDivisions[i]);
    }
    
    THStack* distribsStack[nVars];
    for (int i=0; i!=nVars; ++i) {
        distribsStack[i] = new THStack(Form("distribsStack_%d",i),vars[i]);
        for (int sam=nProcess-2; sam!=iSM-1; --sam) {
            distribsStack[i]->Add(distribs[sam][i]);
        }
    }
    
    TLorentzVector phP4;
    TLorentzVector phP4MC;
    TLorentzVector jP4;
    TLorentzVector xP4;
    TLorentzVector phP4b;
    TLorentzVector jP4b;
    
    double kFactor[3];
    
    for (int kSam=0; kSam<nFiles; ++kSam) {
    //for (int kSam=1; kSam<nFiles; ++kSam) {
        
        //if (kSam >=iSM && kSam < nFiles-1) continue;
        
        if (kSam == iSM+4 || kSam == iSM+5) continue;
        
        if (kSam >=iSM) {
            if (gSystem->AccessPathName("loose/small3_"+fileList[kSam])) continue;
            hfile[kSam]=new TFile("loose/small3_"+fileList[kSam],"READ");
        } else {
            if (gSystem->AccessPathName(""+fileList[kSam])) continue;
            hfile[kSam]=new TFile(""+fileList[kSam],"READ");
        }
        hfile[kSam]->cd("ntuplizer");
        inputTreeFake[kSam] = static_cast<TTree*>(hfile[kSam]->Get("ntuplizer/tree"));
        
        //fChain->SetBranchStatus( "*"                        ,  0 );  // disable all branches
        //fChain->SetBranchStatus( "HLT_isFired"              ,  1 );  // activate select branches

        
        inputTreeFake[kSam]->SetBranchAddress("genParticle_N", &genParticle_N, &b_genParticle_N);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_pt", &genParticle_pt, &b_genParticle_pt);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_px", &genParticle_px, &b_genParticle_px);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_py", &genParticle_py, &b_genParticle_py);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_pz", &genParticle_pz, &b_genParticle_pz);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_e", &genParticle_e, &b_genParticle_e);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_eta", &genParticle_eta, &b_genParticle_eta);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_phi", &genParticle_phi, &b_genParticle_phi);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_mass", &genParticle_mass, &b_genParticle_mass);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_pdgId", &genParticle_pdgId, &b_genParticle_pdgId);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_origin", &genParticle_origin, &b_genParticle_origin);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_status", &genParticle_status, &b_genParticle_status);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_mother", &genParticle_mother, &b_genParticle_mother);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_nMoth", &genParticle_nMoth, &b_genParticle_nMoth);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_nDau", &genParticle_nDau, &b_genParticle_nDau);
        inputTreeFake[kSam]->SetBranchAddress("genParticle_dau", &genParticle_dau, &b_genParticle_dau);
        inputTreeFake[kSam]->SetBranchAddress("lheV_pt", &lheV_pt, &b_lheV_pt);
        inputTreeFake[kSam]->SetBranchAddress("lheHT", &lheHT, &b_lheHT);
        inputTreeFake[kSam]->SetBranchAddress("lheNj", &lheNj, &b_lheNj);
        inputTreeFake[kSam]->SetBranchAddress("genWeight", &genWeight, &b_genWeight);
        inputTreeFake[kSam]->SetBranchAddress("qScale", &qScale, &b_qScale);
        inputTreeFake[kSam]->SetBranchAddress("PDF_x", &PDF_x, &b_PDF_x);
        inputTreeFake[kSam]->SetBranchAddress("PDF_xPDF", &PDF_xPDF, &b_PDF_xPDF);
        inputTreeFake[kSam]->SetBranchAddress("PDF_id", &PDF_id, &b_PDF_id);
        inputTreeFake[kSam]->SetBranchAddress("ph_N", &ph_N, &b_ph_N);
        inputTreeFake[kSam]->SetBranchAddress("ph_pdgId", &ph_pdgId, &b_ph_pdgId);
        inputTreeFake[kSam]->SetBranchAddress("ph_charge", &ph_charge, &b_ph_charge);
        inputTreeFake[kSam]->SetBranchAddress("ph_e", &ph_e, &b_ph_e);
        inputTreeFake[kSam]->SetBranchAddress("ph_eta", &ph_eta, &b_ph_eta);
        inputTreeFake[kSam]->SetBranchAddress("ph_phi", &ph_phi, &b_ph_phi);
        inputTreeFake[kSam]->SetBranchAddress("ph_mass", &ph_mass, &b_ph_mass);
        inputTreeFake[kSam]->SetBranchAddress("ph_pt", &ph_pt, &b_ph_pt);
        inputTreeFake[kSam]->SetBranchAddress("ph_et", &ph_et, &b_ph_et);
        inputTreeFake[kSam]->SetBranchAddress("ph_rho", &ph_rho, &b_ph_rho);
        inputTreeFake[kSam]->SetBranchAddress("ph_fixedGridRho", &ph_fixedGridRho, &b_ph_fixedGridRho);
        inputTreeFake[kSam]->SetBranchAddress("ph_superCluster_eta", &ph_superCluster_eta, &b_ph_superCluster_eta);
        inputTreeFake[kSam]->SetBranchAddress("ph_superCluster_phi", &ph_superCluster_phi, &b_ph_superCluster_phi);
        inputTreeFake[kSam]->SetBranchAddress("ph_sigmaIetaIeta", &ph_sigmaIetaIeta, &b_ph_sigmaIetaIeta);
        inputTreeFake[kSam]->SetBranchAddress("ph_hOverE", &ph_hOverE, &b_ph_hOverE);
        inputTreeFake[kSam]->SetBranchAddress("ph_isoGamma", &ph_isoGamma, &b_ph_isoGamma);
        inputTreeFake[kSam]->SetBranchAddress("ph_isoCh", &ph_isoCh, &b_ph_isoCh);
        inputTreeFake[kSam]->SetBranchAddress("ph_passEleVeto", &ph_passEleVeto, &b_ph_passEleVeto);
        inputTreeFake[kSam]->SetBranchAddress("ph_passLooseId", &ph_passLooseId, &b_ph_passLooseId);
        inputTreeFake[kSam]->SetBranchAddress("ph_passMediumId", &ph_passMediumId, &b_ph_passMediumId);
        inputTreeFake[kSam]->SetBranchAddress("ph_passTightId", &ph_passTightId, &b_ph_passTightId);
        inputTreeFake[kSam]->SetBranchAddress("ph_mvaVal", &ph_mvaVal, &b_ph_mvaVal);
        inputTreeFake[kSam]->SetBranchAddress("ph_mvaCat", &ph_mvaCat, &b_ph_mvaCat);
        inputTreeFake[kSam]->SetBranchAddress("rho", &rho, &b_rho);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_N", &jetAK4_N, &b_jetAK4_N);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_pt", &jetAK4_pt, &b_jetAK4_pt);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_eta", &jetAK4_eta, &b_jetAK4_eta);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_mass", &jetAK4_mass, &b_jetAK4_mass);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_phi", &jetAK4_phi, &b_jetAK4_phi);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_e", &jetAK4_e, &b_jetAK4_e);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_jec", &jetAK4_jec, &b_jetAK4_jec);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_IDLoose", &jetAK4_IDLoose, &b_jetAK4_IDLoose);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_IDTight", &jetAK4_IDTight, &b_jetAK4_IDTight);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_IDTightLepVeto", &jetAK4_IDTightLepVeto, &b_jetAK4_IDTightLepVeto);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_charge", &jetAK4_charge, &b_jetAK4_charge);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_cisv", &jetAK4_cisv, &b_jetAK4_cisv);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_vtxMass", &jetAK4_vtxMass, &b_jetAK4_vtxMass);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_vtxNtracks", &jetAK4_vtxNtracks, &b_jetAK4_vtxNtracks);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_vtx3DVal", &jetAK4_vtx3DVal, &b_jetAK4_vtx3DVal);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_vtx3DSig", &jetAK4_vtx3DSig, &b_jetAK4_vtx3DSig);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_partonFlavour", &jetAK4_partonFlavour, &b_jetAK4_partonFlavour);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_hadronFlavour", &jetAK4_hadronFlavour, &b_jetAK4_hadronFlavour);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_genParton_pdgID", &jetAK4_genParton_pdgID, &b_jetAK4_genParton_pdgID);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_nbHadrons", &jetAK4_nbHadrons, &b_jetAK4_nbHadrons);
        inputTreeFake[kSam]->SetBranchAddress("jetAK4_ncHadrons", &jetAK4_ncHadrons, &b_jetAK4_ncHadrons);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_N", &jetAK8_N, &b_jetAK8_N);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_pt", &jetAK8_pt, &b_jetAK8_pt);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_eta", &jetAK8_eta, &b_jetAK8_eta);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_mass", &jetAK8_mass, &b_jetAK8_mass);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_phi", &jetAK8_phi, &b_jetAK8_phi);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_e", &jetAK8_e, &b_jetAK8_e);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_jec", &jetAK8_jec, &b_jetAK8_jec);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_jecUp", &jetAK8_jecUp, &b_jetAK8_jecUp);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_jecDown", &jetAK8_jecDown, &b_jetAK8_jecDown);

        inputTreeFake[kSam]->SetBranchAddress("jetAK8_IDLoose", &jetAK8_IDLoose, &b_jetAK8_IDLoose);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_IDTight", &jetAK8_IDTight, &b_jetAK8_IDTight);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_IDTightLepVeto", &jetAK8_IDTightLepVeto, &b_jetAK8_IDTightLepVeto);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_charge", &jetAK8_charge, &b_jetAK8_charge);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_Hbbtag", &jetAK8_Hbbtag, &b_jetAK8_Hbbtag);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_partonFlavour", &jetAK8_partonFlavour, &b_jetAK8_partonFlavour);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_hadronFlavour", &jetAK8_hadronFlavour, &b_jetAK8_hadronFlavour);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_genParton_pdgID", &jetAK8_genParton_pdgID, &b_jetAK8_genParton_pdgID);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_nbHadrons", &jetAK8_nbHadrons, &b_jetAK8_nbHadrons);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_ncHadrons", &jetAK8_ncHadrons, &b_jetAK8_ncHadrons);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_csv", &jetAK8_csv, &b_jetAK8_csv);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_tau1", &jetAK8_tau1, &b_jetAK8_tau1);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_tau2", &jetAK8_tau2, &b_jetAK8_tau2);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_tau3", &jetAK8_tau3, &b_jetAK8_tau3);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_pruned_mass", &jetAK8_pruned_mass, &b_jetAK8_pruned_mass);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_pruned_massCorr", &jetAK8_pruned_massCorr, &b_jetAK8_pruned_massCorr);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_pruned_jec", &jetAK8_pruned_jec, &b_jetAK8_pruned_jec);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_pruned_jecUp", &jetAK8_pruned_jecUp, &b_jetAK8_pruned_jecUp);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_pruned_jecDown", &jetAK8_pruned_jecDown, &b_jetAK8_pruned_jecDown);

        inputTreeFake[kSam]->SetBranchAddress("jetAK8_softdrop_mass", &jetAK8_softdrop_mass, &b_jetAK8_softdrop_mass);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_softdrop_massCorr", &jetAK8_softdrop_massCorr, &b_jetAK8_softdrop_massCorr);
        inputTreeFake[kSam]->SetBranchAddress("jetAK8_softdrop_jec", &jetAK8_softdrop_jec, &b_jetAK8_softdrop_jec);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_N", &subjetAK8_softdrop_N, &b_subjetAK8_softdrop_N);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_pt", &subjetAK8_softdrop_pt, &b_subjetAK8_softdrop_pt);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_eta", &subjetAK8_softdrop_eta, &b_subjetAK8_softdrop_eta);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_mass", &subjetAK8_softdrop_mass, &b_subjetAK8_softdrop_mass);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_phi", &subjetAK8_softdrop_phi, &b_subjetAK8_softdrop_phi);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_e", &subjetAK8_softdrop_e, &b_subjetAK8_softdrop_e);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_charge", &subjetAK8_softdrop_charge, &b_subjetAK8_softdrop_charge);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_partonFlavour", &subjetAK8_softdrop_partonFlavour, &b_subjetAK8_softdrop_partonFlavour);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_hadronFlavour", &subjetAK8_softdrop_hadronFlavour, &b_subjetAK8_softdrop_hadronFlavour);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_softdrop_csv", &subjetAK8_softdrop_csv, &b_subjetAK8_softdrop_csv);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_N", &subjetAK8_pruned_N, &b_subjetAK8_pruned_N);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_pt", &subjetAK8_pruned_pt, &b_subjetAK8_pruned_pt);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_eta", &subjetAK8_pruned_eta, &b_subjetAK8_pruned_eta);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_mass", &subjetAK8_pruned_mass, &b_subjetAK8_pruned_mass);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_phi", &subjetAK8_pruned_phi, &b_subjetAK8_pruned_phi);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_e", &subjetAK8_pruned_e, &b_subjetAK8_pruned_e);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_charge", &subjetAK8_pruned_charge, &b_subjetAK8_pruned_charge);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_partonFlavour", &subjetAK8_pruned_partonFlavour, &b_subjetAK8_pruned_partonFlavour);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_hadronFlavour", &subjetAK8_pruned_hadronFlavour, &b_subjetAK8_pruned_hadronFlavour);
        inputTreeFake[kSam]->SetBranchAddress("subjetAK8_pruned_csv", &subjetAK8_pruned_csv, &b_subjetAK8_pruned_csv);
        inputTreeFake[kSam]->SetBranchAddress("HLT_isFired", &HLT_isFired, &b_HLT_isFired);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_HBHE", &passFilter_HBHE, &b_passFilter_HBHE_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_HBHELoose", &passFilter_HBHELoose, &b_passFilter_HBHELoose_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_HBHETight", &passFilter_HBHETight, &b_passFilter_HBHETight_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_CSCHalo", &passFilter_CSCHalo, &b_passFilter_CSCHalo_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_HCALlaser", &passFilter_HCALlaser, &b_passFilter_HCALlaser_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_ECALDeadCell", &passFilter_ECALDeadCell, &b_passFilter_ECALDeadCell_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_GoodVtx", &passFilter_GoodVtx, &b_passFilter_GoodVtx_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_TrkFailure", &passFilter_TrkFailure, &b_passFilter_TrkFailure_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_EEBadSc", &passFilter_EEBadSc, &b_passFilter_EEBadSc_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_ECALlaser", &passFilter_ECALlaser, &b_passFilter_ECALlaser_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_TrkPOG", &passFilter_TrkPOG, &b_passFilter_TrkPOG_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_TrkPOG_manystrip", &passFilter_TrkPOG_manystrip, &b_passFilter_TrkPOG_manystrip_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_TrkPOG_toomanystrip", &passFilter_TrkPOG_toomanystrip, &b_passFilter_TrkPOG_toomanystrip_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_TrkPOG_logError", &passFilter_TrkPOG_logError, &b_passFilter_TrkPOG_logError_);
        inputTreeFake[kSam]->SetBranchAddress("passFilter_METFilters", &passFilter_METFilters, &b_passFilter_METFilters_);
        inputTreeFake[kSam]->SetBranchAddress("METraw_et", &METraw_et, &b_METraw_et);
        inputTreeFake[kSam]->SetBranchAddress("METraw_phi", &METraw_phi, &b_METraw_phi);
        inputTreeFake[kSam]->SetBranchAddress("METraw_sumEt", &METraw_sumEt, &b_METraw_sumEt);
        inputTreeFake[kSam]->SetBranchAddress("MET_corrPx", &MET_corrPx, &b_MET_corrPx);
        inputTreeFake[kSam]->SetBranchAddress("MET_corrPy", &MET_corrPy, &b_MET_corrPy);
        inputTreeFake[kSam]->SetBranchAddress("MET_et", &MET_et, &b_MET_et);
        inputTreeFake[kSam]->SetBranchAddress("MET_phi", &MET_phi, &b_MET_phi);
        inputTreeFake[kSam]->SetBranchAddress("MET_sumEt", &MET_sumEt, &b_MET_sumEt);
        inputTreeFake[kSam]->SetBranchAddress("EVENT_event", &EVENT_event, &b_EVENT_event);
        inputTreeFake[kSam]->SetBranchAddress("EVENT_run", &EVENT_run, &b_EVENT_run);
        inputTreeFake[kSam]->SetBranchAddress("EVENT_lumiBlock", &EVENT_lumiBlock, &b_EVENT_lumiBlock);
        inputTreeFake[kSam]->SetBranchAddress("nPuVtxTrue", &nPuVtxTrue, &b_nPuVtxTrue);
        inputTreeFake[kSam]->SetBranchAddress("nPuVtx", &nPuVtx, &b_nPuVtx);
        inputTreeFake[kSam]->SetBranchAddress("bX", &bX, &b_bX);
        inputTreeFake[kSam]->SetBranchAddress("PV_N", &PV_N, &b_PV_N);
        inputTreeFake[kSam]->SetBranchAddress("PV_filter", &PV_filter, &b_PV_filter);
        inputTreeFake[kSam]->SetBranchAddress("PV_chi2", &PV_chi2, &b_PV_chi2);
        inputTreeFake[kSam]->SetBranchAddress("PV_ndof", &PV_ndof, &b_PV_ndof);
        inputTreeFake[kSam]->SetBranchAddress("PV_rho", &PV_rho, &b_PV_rho);
        inputTreeFake[kSam]->SetBranchAddress("PV_z", &PV_z, &b_PV_z);
        
        long nEntries = inputTreeFake[kSam]->GetEntries();
        
        _hCounter->Read("hCounter");
        
        double scale = xsec[kSam]/(_hCounter->GetBinContent(1))*intlumi;
        if (kSam == nFiles-1) scale = 1.;

        
        std::cout<<std::endl;
        std::cout<<fileList[kSam]<<" with entries "<<nEntries<<"; scale "<<scale<<std::endl;
        
        for (long it=0; it!=nEntries; ++it) {
        //for (long it=0; it!=10000; ++it) {
            inputTreeFake[kSam]->GetEntry(it);
            
            if (it%10000 == 0)
                std::cout<<'.'<<std::flush;
            
            double _weight = 1;
            if (kSam < nFiles-1) {
                int ntrue = 0;
                for (unsigned int k=0; k != bX->size(); ++k) {
                    if( bX->at(k) == 0 ) { // in-time PU
                        ntrue = nPuVtxTrue -> at(k);
                    }
                }
                //_weight = scale*getTruePUwUp(ntrue)*genWeight;
                double puwNum = puw->GetBinContent(puw->FindBin(ntrue));

                //_weight = scale*getPUwECO(PV_N);
                _weight = scale*genWeight*puwNum;
            }

            
            bool triggerFired = false;
            bool triggerFired2 = false;
            bool triggerFired3 = false;
            for(map<string,bool>::iterator it = HLT_isFired->begin(); it != HLT_isFired->end(); ++it) {
                if ((it->first).find("HLT_Photon165_HE10_v")!= string::npos) {
                    triggerFired |= (1==it->second);
                }
                if ((it->first).find("HLT_Photon175_v")!= string::npos) {
                    triggerFired2 |= (1==it->second);
                }
                if ((it->first).find("HLT_PFHT800")!= string::npos) {
                    triggerFired3 |= (1==it->second);
                }
            }
            if (kSam == nFiles-1) {
                if (!triggerFired && !triggerFired2 && !triggerFired3) continue;
                //if (!triggerFired && !triggerFired2) continue;
                if (!passFilter_CSCHalo) continue;
                if (!passFilter_GoodVtx) continue;
            }
            
            int phInd = -1;
            for (int i=0; i!=ph_N; ++i) {
                if (ph_pt->at(i) < 200.) continue;
                if (!ph_passEleVeto->at(i)) continue;
                if (fabs(ph_superCluster_eta->at(i)) > 1.4442 && fabs(ph_superCluster_eta->at(i)) < 1.566) continue;
                if (fabs(ph_eta->at(i)) > 2.4) continue;
                //if (fabs(ph_eta->at(i)) > 1.4442) continue;
                //if (fabs(ph_superCluster_eta->at(i)) < 1.4442 && ph_mvaVal->at(i) < 0.374) continue;
                //if (fabs(ph_superCluster_eta->at(i)) > 1.566 && ph_mvaVal->at(i) < 0.336) continue;
                
                if (!ph_passLooseId->at(i)) continue;
                if (fabs(ph_superCluster_eta->at(i)) < 1.4442) {
                    if (ph_sigmaIetaIeta->at(i) > 0.0102) continue;
                    if (ph_hOverE->at(i) > 0.05) continue;
                    if (ph_isoCh->at(i) > 2.5) continue;
                } else {
                    if (ph_sigmaIetaIeta->at(i) > 0.0274) continue;
                    if (ph_hOverE->at(i) > 0.05) continue;
                    if (ph_isoCh->at(i) > 2.5) continue;
                }
                
                if (phInd < 0) phInd = i;
                else if (ph_pt->at(i) > ph_pt->at(phInd)) phInd = i;
                
            }
            if (phInd < 0) continue;
            phP4.SetPtEtaPhiE(ph_pt->at(phInd),ph_eta->at(phInd),ph_phi->at(phInd),ph_e->at(phInd));
            
            if (kSam >= iSM && kSam <iSM+12) {
                int phIndMC = -1;
                double minDeltaR = 10000;
                for (int j=0; j!=genParticle_pt->size(); ++j) {
                    if (genParticle_pdgId->at(j) == 22 && genParticle_status->at(j) == 1) {//&& genParticle_origin->at(j) == 0
                        phP4MC.SetPtEtaPhiE(genParticle_pt->at(j),genParticle_eta->at(j),genParticle_phi->at(j),genParticle_e->at(j));
                        if (phP4.DeltaR(phP4MC) < minDeltaR) {
                            minDeltaR = phP4.DeltaR(phP4MC);
                            phIndMC = j;
                        }
                    }
                }
                if (minDeltaR < 0.3) {
                    if (kSam >= iSM && kSam <iSM+4 && genParticle_origin->at(phIndMC)!=0) continue;//skip non-prompt photons in g+jets samples
                    if (kSam >= iSM+4 && kSam <iSM+12 && genParticle_origin->at(phIndMC)==0) continue;//skip prompt photons in QCD samples
                } else {
                    if (kSam >= iSM && kSam <iSM+4) continue;
                    //std::cout<<minDeltaR<<std::endl;
                }
                if (kSam >= iSM && kSam < iSM+4 && phIndMC >=0) {
                    //_weight = _weight* kfactHist[0][2]->GetBinContent(kfactHist[0][2]->FindBin(genParticle_pt->at(phIndMC)));
                    //_weight = _weight*func->Eval(genParticle_pt->at(phIndMC));
                }
            }
            
            int jInd = -1;
            for (int i=0; i!=jetAK8_N; ++i) {
                if (!jetAK8_IDTightLepVeto->at(i)) continue;
                if (jetAK8_pt->at(i) < 200.) continue;
                if (jetAK8_pruned_massCorr->at(i) < 30.) continue;
                //if (jetAK8_pruned_massCorr->at(i) < 75.) continue;
                //if (jetAK8_pruned_massCorr->at(i) > 105.) continue;
                //if (fabs(jetAK8_eta->at(i)) > 2.0) continue;
                if (fabs(jetAK8_eta->at(i)) > 2.4) continue;
                jP4.SetPtEtaPhiE(jetAK8_pt->at(i),jetAK8_eta->at(i),jetAK8_phi->at(i),jetAK8_e->at(i));
                if (jP4.DeltaR(phP4) < 1.1) continue;
                if (jInd < 0) jInd = i;
                else if (jetAK8_pt->at(i) > jetAK8_pt->at(jInd)) jInd = i;
            }
            if (jInd < 0) continue;
            //jP4.SetPtEtaPhiM(jetAK8_pt->at(jInd),jetAK8_eta->at(jInd),jetAK8_phi->at(jInd),jetAK8_pruned_massCorr->at(jInd));
            jP4.SetPtEtaPhiM(jetAK8_pt->at(jInd),jetAK8_eta->at(jInd),jetAK8_phi->at(jInd),jetAK8_mass->at(jInd));

            xP4 = jP4+phP4;
            
            double massjg = xP4.M();
            //if (massjg < 600) continue;
            //if (massjg < 710 || massjg > 780) continue;
            //if (massjg < 1500) continue;
            
            phP4b = phP4;
            phP4b.Boost(-(xP4.BoostVector()));
            //jP4b = jP4;
            //jP4b.Boost(-(xP4.BoostVector()));
            double cosThetaStar = std::abs(phP4b.Pz()/phP4b.P());
            
            //if (ph_pt->at(phInd)/massjg < 0.34) continue;
            
            //if (cosThetaStar > 0.6) continue;

            
            double minCsv = 0;
            double maxCsv = 0;
            if (subjetAK8_pruned_N->at(jInd) >= 2) {
                for (int i=0; i!=subjetAK8_pruned_N->at(jInd); ++i) {
                    if (subjetAK8_pruned_csv->at(jInd).at(i) > maxCsv) {
                        if (maxCsv > minCsv) {
                            minCsv = maxCsv;
                        }
                        maxCsv = subjetAK8_pruned_csv->at(jInd).at(i);
                    } else if (subjetAK8_pruned_csv->at(jInd).at(i) > minCsv) {
                        minCsv = subjetAK8_pruned_csv->at(jInd).at(i);
                    }
                }
                //minCsv = TMath::Min(subjetAK8_pruned_csv->at(jInd).at(0),subjetAK8_pruned_csv->at(jInd).at(1));
                //maxCsv = TMath::Max(subjetAK8_pruned_csv->at(jInd).at(0),subjetAK8_pruned_csv->at(jInd).at(1));
            }
            //if (minCsv > 0.605 && maxCsv > 0.89) continue;

            
            distribs[grouping[kSam]][0]->Fill(lheHT, _weight);
            distribs[grouping[kSam]][1]->Fill(TMath::Min(ph_pt->at(phInd), varUp[1]-1), _weight);
            
            //kfactHistLocal[grouping[kSam]]->Fill(ph_pt->at(phInd), _weight);
            distribs2d[grouping[kSam]]->Fill(ph_pt->at(phInd), jetAK8_pt->at(jInd),_weight);
            
            distribs[grouping[kSam]][2]->Fill(TMath::Min(jetAK8_pt->at(jInd), varUp[2]-1), _weight);
            distribs[grouping[kSam]][3]->Fill(ph_eta->at(phInd), _weight);
            distribs[grouping[kSam]][4]->Fill(jetAK8_eta->at(jInd), _weight);
            distribs[grouping[kSam]][5]->Fill(PV_N, _weight);
            distribs[grouping[kSam]][6]->Fill(TMath::Min(jetAK8_pruned_massCorr->at(jInd), varUp[6]-1), _weight);
            distribs[grouping[kSam]][7]->Fill(jetAK8_tau2->at(jInd)/jetAK8_tau1->at(jInd), _weight);
            distribs[grouping[kSam]][8]->Fill(jP4.DeltaR(phP4), _weight);
            distribs[grouping[kSam]][9]->Fill(fabs(jetAK8_eta->at(jInd)-ph_eta->at(phInd)), _weight);
            distribs[grouping[kSam]][10]->Fill((jP4+phP4).M(), _weight);
            distribs[grouping[kSam]][11]->Fill(TMath::Min(MET_et->at(0), varUp[11]-1), _weight);
            
            float mt = sqrt(2*ph_pt->at(phInd)*MET_et->at(0)*( 1 - (TMath::Cos(ph_phi->at(phInd) - MET_phi->at(0) )) ) );
            distribs[grouping[kSam]][12]->Fill(TMath::Min(mt, varUp[12]-1), _weight);
            
            //std::cout<<subjetAK8_pruned_N->at(jInd)<<std::endl;
            distribs[grouping[kSam]][13]->Fill(minCsv, _weight);
            distribs[grouping[kSam]][14]->Fill(maxCsv, _weight);
            //std::cout<<std::endl;
            distribs[grouping[kSam]][15]->Fill(cosThetaStar, _weight);
            distribs[grouping[kSam]][16]->Fill(ph_pt->at(phInd)/massjg, _weight);
            if (jetAK8_pruned_massCorr->at(jInd) > 70)
                distribs[grouping[kSam]][17]->Fill(jetAK8_Hbbtag->at(jInd), _weight);
            
            //if (jetAK8_pruned_massCorr->at(jInd) > 75 && jetAK8_pruned_massCorr->at(jInd) < 105)
            distribs[grouping[kSam]][18]->Fill(TMath::Min(jetAK8_mass->at(jInd), varUp[18]-1), _weight);
            
            
            
            if (kSam >= iSM)
                kFactor[int(kSam==nFiles-1)]+=_weight;

        }
    }
    
    gROOT->SetBatch(kTRUE);

    
    kFactor[2] = kFactor[1]/kFactor[0];
    //kFactor[2] = 1.;
    
    //draw the histograms
    TCanvas* c1[nVars];
    TPad* pad[nVars][2];
    TLegend* leg[nVars];
    
    double xPad = 0.25;
    double xG[2] = {-10,4000};
    double yG[2] = {1.0,1.0};
    TGraph* unityG = new TGraph(2, xG, yG);
    unityG->SetLineColor(kGray+2);
    unityG->SetLineWidth(1);
    

    
    for (int i=0; i!=nVars; ++i) {
        leg[i] = new TLegend(0.6,0.9,0.92,0.5,Form("SF=%3.2f",kFactor[2]),"NDC");
        leg[i]->SetTextFont(42);
        leg[i]->SetFillStyle(3001);
        leg[i]->SetBorderSize(0);

        for (int j = 0; j!=iSM; ++j) {
            leg[i]->AddEntry(distribs[j][i],sampleString[j],"l");
        }
        for (int j = iSM; j!=nProcess-1; ++j) {
            if (j == iSM+4 || j == iSM+5) continue;

            leg[i]->AddEntry(distribs[j][i],sampleString[j],"f");
            distribs[j][i]->Scale(kFactor[2]);
            distribs[nProcess][i]->Add(distribs[j][i]);
            std::cout<<sampleString[j]<<" "<<distribs[j][i]->Integral()<<std::endl;
        }
        leg[i]->AddEntry(distribs[nProcess-1][i],sampleString[nProcess-1],"pel");

        c1[i] = new TCanvas(Form("can_%d",i),"",600*(1.-xPad),600);
        c1[i]->cd();

        pad[i][0] = new TPad(Form("pad_%d_0",i),"",0,xPad,1,1);
        pad[i][0]->Draw();
        pad[i][0]->SetBottomMargin(0.01);
        pad[i][0]->cd();

        distribs[nProcess-1][i]->GetXaxis()->SetLabelColor(0);
        
        distribs[nProcess-1][i]->Draw("pe");
        //distribs[nProcess][i]->Draw("hist");
        distribsStack[i]->Draw("hist same");

        distribs[nProcess][i]->SetFillStyle(3005);
        distribs[nProcess][i]->SetFillColor(kGray+2);
        distribs[nProcess][i]->SetMarkerStyle(1);
        distribs[nProcess][i]->Draw("e2same");

        distribs[nProcess][i]->Draw("axis same");
        distribs[nProcess-1][i]->Draw("pe same");
        
        for (int j = 0; j!=iSM; ++j) {
            distribs[j][i]->Draw("hist same");
        }
        
        leg[i]->Draw("same");

        
        pad[i][0]->SetLogy();
        
        CMS_lumi( pad[i][0], iPeriod, iPos );

        c1[i]->cd();
        pad[i][1] = new TPad(Form("pad_%d_1",i),"",0,0.0,1,xPad);
        pad[i][1]->Draw();
        pad[i][1]->SetBottomMargin((1.-xPad)/xPad*0.13);
        pad[i][1]->SetTopMargin(0.06);
        pad[i][1]->cd();
        
        distribs[nProcess+1][i]->Divide(distribs[nProcess-1][i],distribs[nProcess][i]);
        
        distribs[nProcess+1][i]->SetMarkerColor(1);
        distribs[nProcess+1][i]->SetLineColor(1);
        distribs[nProcess+1][i]->GetYaxis()->SetRangeUser(0,2);
        distribs[nProcess+1][i]->GetYaxis()->SetNdivisions(503);
        distribs[nProcess+1][i]->GetYaxis()->SetTitle("data/MC");
        distribs[nProcess+1][i]->GetYaxis()->SetTitleOffset(1.2/((1.-xPad)/xPad));
        distribs[nProcess+1][i]->GetYaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
        distribs[nProcess+1][i]->GetXaxis()->SetTitleSize((1.-xPad)/xPad*0.06);
        distribs[nProcess+1][i]->GetYaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
        distribs[nProcess+1][i]->GetXaxis()->SetLabelSize((1.-xPad)/xPad*0.05);
        
        distribs[nProcess+1][i]->Draw("pe");

        
        unityG->Draw("same");
        distribs[nProcess+1][i]->Draw("pe same");


    }
    
    
    TFile* output = new TFile("histos.root","recreate");
    for (int i = 0; i!=nVars; ++i) {
        c1[i]->Write();
        distribs[nProcess-1][10]->SetName("distribs_18_10_0");
        distribs[nProcess-1][10]->Write("distribs_18_10_0",TObject::kWriteDelete);
        for (int j = 0; j!=nProcess; ++j) {
            distribs[j][i]->Write();
        }
    }
    for (int j = 0; j!=nProcess; ++j) {
        //kfactHistLocal[j]->Write();
        distribs2d[j]->Write();
    }
    output->Close();
    std::cout<<"Done"<<std::endl;
    
}


