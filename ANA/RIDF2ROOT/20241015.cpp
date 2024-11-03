#include <signal.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

using namespace std;

#include "TString.h"
#include "TMath.h"
#include "TH1.h"
#include "TF1.h"
#include "TRandom.h"
#include "TCutG.h"

#include "TH2.h"
#include "TSystem.h"
#include "TTree.h"
#include "TFile.h"
#include "TClonesArray.h"
#include "TVector3.h"
#include "TText.h"
#include "TCanvas.h"
#include "TEllipse.h"
#include "TGraphErrors.h"
#include "TLegend.h"

#include "TArtStoreManager.hh"
#include "TArtEventStore.hh"
#include "TArtEventInfo.hh"
#include "TArtBigRIPSParameters.hh"

#include "fstream"
#include "iostream"
#include "unistd.h"

#include "signal.h"
#include "./INC/ribf_interrupt.h"
#include "./INC/ribf_var.h"
#include "./INC/ribf_para.h" 
#include "./INC/ribf_validgate.h" // only for unpacking rawdata
#include "./INC/ribf_raw.h"       // only for unpacking rawdata
#include "./INC/ribf_branch.h"
#include "./INC/ribf_encpid.h"
#include "./INC/ribf_transmission.h"


#define ONLINE_FLAG
#define PLOT_FLAG

Double_t pidgate[2][6]={
  // A/Q(mean, sigma, xsigma), Zet(mean, sigma, xsigma)
  // Upstream
  2.687,0.0026,4., 18.92,0.2362,4.0,
  // Downstream
  2.693,0.0032,5., 18.73,0.1512,5.0,
};

Double_t emtgate[5][2]={
  -6.0, +8.0, // X @F8  Fpl_XP[8]
  -5.0, +10.0, // A @F8  Fpl_XT[8]
  -10.0, +7.0, // Y @F8  Fpl_YP[8]
  -10.0, +10.0, // B @F8  Fpl_YT[8]
  -2.0, +1.0,  // D @D6  Delta57
};

//void VME2Tree(int runN, bool file_output=0 /* 0 = NO, 1 = Yes */ ,TString runname="run"){
//void VME2Tree(int runN=285, TString runname="55Ca", bool tree_output=0 /* 0 = NO, 1 = Yes */){
void ridf2root(int runN=48, TString runname="56Co", bool tree_output=0, int loadEvt = 10000 /* 0 = NO, 1 = Yes */){

  bool file_output = 1;
  
  /*
    TEllipse *ellipse_PID[2];
    for(int i=0;i<2;i++){
    ellipse_PID[i] = new TEllipse(pidgate[i][0],pidgate[i][3],pidgate[i][1]*pidgate[i][2],pidgate[i][4]*pidgate[i][5]);
    ellipse_PID[i]->SetFillStyle(0);
    ellipse_PID[i]->SetLineColor(2);
    ellipse_PID[i]->SetLineWidth(2);
    }
  */

  cout << fixed;

  //===== Define the path of input/output files ====================  
  TString ifname, ofname;
  ifname = "./RIDF/"      + runname + Form("%04d.ridf",runN);

  if(tree_output){
    ofname = "./ROOT/" + runname + Form("%04d.root",runN);
  }else{
    ofname = "./HIST/" + runname + Form("%04d.root",runN);
  }

  if(runN==9999)ofname="./HIST/temp.root";

  Int_t Ndatabyte = 0;

  // For user interrupt
  signal(SIGINT,sig_interrupt);

  //===== Open file & Set EventStore, RawEvent Object ==============  
  TArtStoreManager * sman = TArtStoreManager::Instance();
  TArtEventStore *estore = new TArtEventStore();
  TArtRawEventObject *rawevent = new TArtRawEventObject();

  // return rawevent
  rawevent = estore->GetRawEventObject();

  // Open input file (ridf file)
  if(runN==9999){
    estore->Open(0);  // online
  }else{
    estore->Open(ifname);
  }

  estore->SetInterrupt(&stoploop); 

  //===== Define output file (ROOT file) ===========================
  TFile *fout = new TFile(ofname, "RECREATE");

  //===== Define tree =============================
  TTree *tree = new TTree("tree","tree");
    
  tree->SetAutoFlush(6000000);
  //===== Set branches of tree ====================
#ifdef ONLINE_FLAG
  // defined in include/ribf_branch.h
  ribf_branch(tree); 
#else
  // defined in include/ribf_branch.h
  ribf_branch_raw(tree);
#endif


  //===== 2D CUTG ========================
  const int Ng2d=2;
  TCutG *g2d[Ng2d];
  //  gROOT->ProcessLine(".x cut/run0007_g1.C");
  //  gROOT->ProcessLine(".x cut/run0007_g2.C");

  g2d[0] = (TCutG*)gROOT->FindObject("run0007_g1");
  g2d[1] = (TCutG*)gROOT->FindObject("run0007_g2");
  
  
  cout << "==== 2D gate =====================================================================" << endl;
  cout << setw(10) << "tgate[XX]" << setw(20) << "Gate name" << setw(15) << "VarX" << setw(15) << "VarY" << setw(20) << "Comment" << endl;
  cout << "----------------------------------------------------------------------------------" << endl;
  for(int i=0;i<Ng2d;i++){
    if(!g2d[i]){
      //      cout << Form("A gate2d_%02d cannot be loaded. Quit",i) << endl;
      //      return;
      cout << Form("A gate2d_%02d cannot be loaded.",i) << endl;
      //      return;
    }else{
      g2d[i]->SetLineColor(2);
      g2d[i]->SetLineWidth(2);
      cout << setw(10) << Form("tgate[%02d]",80+i)
	   << setw(20) << g2d[i]->GetName() 
	   << setw(15) << g2d[i]->GetVarX() 
	   << setw(15) << g2d[i]->GetVarY() 
	   << setw(20) << g2d[i]->GetTitle() << endl;
    }
  }
  cout << "=================================================================================" << endl;

  //===== Histograms =======================================================
  TH2D *hraw_v1190[3];
  hraw_v1190[0] = new TH2D("hraw_v1190_0",Form("V1190-0 (PPAC| F3) rawdata | run%04d;ID;T (ns)",runN),128,0,128,1000,0,200000);
  hraw_v1190[1] = new TH2D("hraw_v1190_1",Form("V1190-1 (PPAC| F5) rawdata | run%04d;ID;T (ns)",runN),128,0,128,1000,0,200000);
  hraw_v1190[2] = new TH2D("hraw_v1190_2",Form("V1190-2 (PPAC| F7) rawdata | run%04d;ID;T (ns)",runN),128,0,128,1000,0,200000);
  TH2D *hraw_v1190num[3];
  hraw_v1190num[0] = new TH2D("hraw_v1190num_0",Form("V1190 (PPAC| F3) Multiplicity | run%04d;ID;#it{N}_{hit}",runN),128,0,128,5,0,5);
  hraw_v1190num[1] = new TH2D("hraw_v1190num_1",Form("V1190 (PPAC| F5) Multiplicity | run%04d;ID;#it{N}_{hit}",runN),128,0,128,5,0,5);
  hraw_v1190num[2] = new TH2D("hraw_v1190num_2",Form("V1190 (PPAC| F7) Multiplicity | run%04d;ID;#it{N}_{hit}",runN),128,0,128,5,0,5);

  TH2D *hraw_v1290L[2];
  hraw_v1290L[0] = new TH2D("hraw_v1290L_0",Form("V1290L (PLA-T) rawdata | run%04d;ID;T (ns)"          ,runN),32,0,32,1000,0,25000);
  hraw_v1290L[1] = new TH2D("hraw_v1290L_1",Form("V1290 Leading  (PLA-QTC) rawdata | run%04d;ID;T (ns)",runN),32,0,32,500,0,3000);
  TH2D *hraw_v1290Lnum[2];
  hraw_v1290Lnum[0] = new TH2D("hraw_v1290Lnum_0",Form("V1290 (PLA-T) Multiplicity | run%04d;ID;#it{N}_{hit}"          ,runN),32,0,32,10,0,10);
  hraw_v1290Lnum[1] = new TH2D("hraw_v1290Lnum_1",Form("V1290 Leading (PLA-QTC) Multiplicity | run%04d;ID;#it{N}_{hit}",runN),32,0,32,10,0,10);
  TH2D *hraw_v1290Lnum2[2];
  hraw_v1290Lnum2[0] = new TH2D("hraw_v1290Lnum2_0",Form("V1290 (PLA-T) Multiplicity2 | run%04d;ID;#it{N}_{hit}"          ,runN),32,0,32,10,0,10);
  hraw_v1290Lnum2[1] = new TH2D("hraw_v1290Lnum2_1",Form("V1290 Leading (PLA-QTC) Multiplicity2 | run%04d;ID;#it{N}_{hit}",runN),32,0,32,10,0,10);
  /*
  TH2D *hraw_v1290T[2];
  hraw_v1290T[0] = new TH2D("hraw_v1290T_0","V1290L-0 (PLA-T) rawdata;ID;T (ns)",32,0,32,1200,0,12000);
  hraw_v1290T[1] = new TH2D("hraw_v1290T_1","V1290L-1 (PLA-QTC) rawdata;ID;T (ns)",32,0,32,1200,0,100000);
  TH2D *hraw_v1290Tnum[2];
  hraw_v1290Tnum[0] = new TH2D("hraw_v1290Tnum_0","V1290L (PLA-T) Multiplicity;ID;#it{N}_{hit}",32,0,32,10,0,10);
  hraw_v1290Tnum[1] = new TH2D("hraw_v1290Tnum_1","V1290L (PLA-QTC) Multiplicity;ID;#it{N}_{hit}",32,0,32,10,0,10);
  */
  TH2D *hraw_v1290T;
  hraw_v1290T = new TH2D("hraw_v1290T",Form("V1290 Trailing (PLA-QTC) rawdata | run%04d;ID;T (ns)" ,runN),32,0,32,1500,0,3000);
  TH2D *hraw_v1290W;
  hraw_v1290W = new TH2D("hraw_v1290W",Form("V1290 Width (PLA-QTC) rawdata | run%04d;ID;Width (ns)",runN),32,0,32,400,-100,1100);

  TH2D *hraw_qdc;
  hraw_qdc = new TH2D("hraw_qdc",Form("QDC (PLA) rawdata | run%04d;ID;Q (ch)",runN),16,0,16,430,-100,4200);
  TH2D *hraw_adc[4];
  hraw_adc[0] = new TH2D("hraw_adc_F07IC",Form("ADC (F07MUSIC) rawdata | run%04d;ID;ADC (ch)",runN),8,0,8,860,-200,8400);
  hraw_adc[1] = new TH2D("hraw_adc_F08IC",Form("ADC (F08MUSIC) rawdata | run%04d;ID;ADC (ch)",runN),4,0,4,860,-200,8400);
  hraw_adc[2] = new TH2D("hraw_adc_F11IC",Form("ADC (F11MUSIC) rawdata | run%04d;ID;ADC (ch)",runN),8,0,8,430,-100,4200);
  hraw_adc[3] = new TH2D("hraw_adc_F03IC",Form("ADC (F03MUSIC) rawdata | run%04d;ID;ADC (ch)",runN),8,0,8,860,-200,8400);

  //=====
  TH2D *hraw_PPAC_v1190[7];
  hraw_PPAC_v1190[0] = new TH2D("hraw_PPAC_v1190_F03",Form("F03PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,0000,165000);
  hraw_PPAC_v1190[1] = new TH2D("hraw_PPAC_v1190_F05",Form("F05PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,0000,165000);
  hraw_PPAC_v1190[2] = new TH2D("hraw_PPAC_v1190_F07",Form("F07PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,0000,165000);
  hraw_PPAC_v1190[3] = new TH2D("hraw_PPAC_v1190_F08",Form("F08PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,0000,150000);
  hraw_PPAC_v1190[4] = new TH2D("hraw_PPAC_v1190_F09",Form("F09PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,4000,10000);
  hraw_PPAC_v1190[5] = new TH2D("hraw_PPAC_v1190_F10",Form("F10PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,4000,10000);
  hraw_PPAC_v1190[6] = new TH2D("hraw_PPAC_v1190_F11",Form("F11PPAC V1190raw | run%04d;ID;V1190raw (ch)",runN),20,0,20,500,4000,10000);

  TH2D *hraw_PLA_v1290[2];
  hraw_PLA_v1290[0] = new TH2D("hraw_PLA_v1290_T"  ,Form("PLA-T   V1290raw | run%04d;F03/F05/F07/F08/F09/F11/F8VETO/F11Long/F3-2/F5-2/F7-2;V1290raw (ch)",runN),22,0,22,500,400e3,600e3);
  hraw_PLA_v1290[1] = new TH2D("hraw_PLA_v1290_QTC",Form("PLA-QTC V1290raw | run%04d;F03/F05/F07/F08/F09/F11/F8VETO/F11Long;V1290raw (ch)"               ,runN),16,0,16,500,   0*40,1000*40);

  // 
  TH2D *hcalib_pileup_IC[3];
  hcalib_pileup_IC[0] = new TH2D("hcalib_pileup_IC_F7" ,Form("#it{T}_{2nd} #minus #it{T}_{1st} of F7PLA-L vs #Delta#it{E}_{F07IC} | run%04d;#it{T}_{2nd} #minus #it{T}_{1st};#Delta#it{E}_{F08IC} (MeV)",runN),650,-0.5,12.5,400,0,300);
  hcalib_pileup_IC[1] = new TH2D("hcalib_pileup_IC_F8" ,Form("#it{T}_{2nd} #minus #it{T}_{1st} of F7PLA-L vs #Delta#it{E}_{F08IC} | run%04d;#it{T}_{2nd} #minus #it{T}_{1st};#Delta#it{E}_{F08IC} (MeV)",runN),650,-0.5,12.5,400,0,300);
  hcalib_pileup_IC[2] = new TH2D("hcalib_pileup_IC_F11",Form("#it{T}_{2nd} #minus #it{T}_{1st} of F7PLA-L vs #Delta#it{E}_{F11IC} | run%04d;#it{T}_{2nd} #minus #it{T}_{1st};#Delta#it{E}_{F11IC} (MeV)",runN),650,-0.5,12.5,400,0,300);

  //===== Rawdata ============================
  //===== PPAC ==========
  TH2D *hraw_PPAC_Traw[7];
  hraw_PPAC_Traw[0] = new TH2D("hraw_PPAC_Traw_F03",Form("F03PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  hraw_PPAC_Traw[1] = new TH2D("hraw_PPAC_Traw_F05",Form("F05PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  hraw_PPAC_Traw[2] = new TH2D("hraw_PPAC_Traw_F07",Form("F07PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  hraw_PPAC_Traw[3] = new TH2D("hraw_PPAC_Traw_F08",Form("F08PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  hraw_PPAC_Traw[4] = new TH2D("hraw_PPAC_Traw_F09",Form("F09PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  hraw_PPAC_Traw[5] = new TH2D("hraw_PPAC_Traw_F10",Form("F10PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  hraw_PPAC_Traw[6] = new TH2D("hraw_PPAC_Traw_F11",Form("F11PPAC Traw | run%04d;ID;T (ns)",runN),20,0,20,400,-200000,200000);
  TH2D *hraw_PPAC_T[7];
  hraw_PPAC_T[0] = new TH2D("hraw_PPAC_T_F03",Form("F03PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  hraw_PPAC_T[1] = new TH2D("hraw_PPAC_T_F05",Form("F05PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  hraw_PPAC_T[2] = new TH2D("hraw_PPAC_T_F07",Form("F07PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  hraw_PPAC_T[3] = new TH2D("hraw_PPAC_T_F08",Form("F08PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  hraw_PPAC_T[4] = new TH2D("hraw_PPAC_T_F09",Form("F09PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  hraw_PPAC_T[5] = new TH2D("hraw_PPAC_T_F10",Form("F10PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  hraw_PPAC_T[6] = new TH2D("hraw_PPAC_T_F11",Form("F11PPAC T | run%04d;ID;T (ns)",runN),20,0,20,400,-2000,2000);
  //===== Plastic ==========
  TH2D *hraw_PLA_T;
  hraw_PLA_T    = new TH2D("hraw_PLA_T",   Form("Plastic T | run%04d;F3/F5/F7/F8/F9/F11/F8VETO/F11Long/F3-2/F5-2/F7-2;T(ns)"    ,runN),22,0,22,600,-300,300);
  TH1D *hraw_PLA_T1[3][2];
  hraw_PLA_T1[0][0]= new TH1D("hraw_PLA_T_00",   Form("F3Pla-L T | run%04d;T(ns)" ,runN),600,10000,20000);
  hraw_PLA_T1[0][1]= new TH1D("hraw_PLA_T_01",   Form("F3Pla-R T | run%04d;T(ns)" ,runN),600,10000,20000);
  hraw_PLA_T1[1][0]= new TH1D("hraw_PLA_T_10",   Form("F5Pla-L T | run%04d;T(ns)" ,runN),600,10000,20000);
  hraw_PLA_T1[1][1]= new TH1D("hraw_PLA_T_11",   Form("F5Pla-R T | run%04d;T(ns)" ,runN),600,10000,20000);
  hraw_PLA_T1[2][0]= new TH1D("hraw_PLA_T_20",   Form("F7Pla-L T | run%04d;T(ns)" ,runN),600,10000,20000);
  hraw_PLA_T1[2][1]= new TH1D("hraw_PLA_T_21",   Form("F7Pla-R T | run%04d;T(ns)" ,runN),600,10000,20000);
  TH2D *hraw_PLA_QTC;
  hraw_PLA_QTC  = new TH2D("hraw_PLA_QTC", Form("Plastic QTC | run%04d;F3/F5/F7/F8/F9/F11/F8VETO/F11Long;QTC (ns)"              ,runN),16,0,16,500,-50,950);
  TH2D *hraw_PLA_Qraw;
  hraw_PLA_Qraw = new TH2D("hraw_PLA_Qraw",Form("Plastic Qraw | run%04d;F3/F5/F7/F8/F9/F11/F8VETO/F11Long;Qraw (ch)"            ,runN),16,0,16,430,-100,4200);
  TH2D *hraw_PLA_Qraw2[3];
  hraw_PLA_Qraw2[0] = new TH2D("hraw_PLA_Qraw2_0", Form("F3Pla Q (L vs R)| run%04d;Q_L(ch);Q_R(ch)" ,runN),600,0,3000,600,0,3000);
  hraw_PLA_Qraw2[1] = new TH2D("hraw_PLA_Qraw2_1", Form("F5Pla Q (L vs R)| run%04d;Q_L(ch);Q_R(ch)" ,runN),600,0,3000,600,0,3000);
  hraw_PLA_Qraw2[2] = new TH2D("hraw_PLA_Qraw2_2", Form("F7Pla Q (L vs R)| run%04d;Q_L(ch);Q_R(ch)" ,runN),600,0,3000,600,0,3000);
  TH2D *hraw_PLA_Mhit;
  hraw_PLA_Mhit = new TH2D("hraw_PLA_Mhit",Form("Ratio of Multiplicity | run%04d;F3/F5/F7/F8/F9/F11/F8VETO/F11Long;Multiplicity",runN),16,0,16,5,0,5);
  TH1D *hraw_TOF[3];
  hraw_TOF[0] = new TH1D("hraw_TOF_0", Form("TOF35| run%04d;TOF35 (ns);counts", runN), 600, 0, 300);
  hraw_TOF[1] = new TH1D("hraw_TOF_1", Form("TOF57| run%04d;TOF57 (ns);counts", runN), 600, 0, 300);
  hraw_TOF[2] = new TH1D("hraw_TOF_2", Form("TOF37| run%04d;TOF37 (ns);counts", runN), 600, 0, 300);
  //===== MUSIC ==========
  TH2D *hraw_IC_Eraw[4];
  hraw_IC_Eraw[0] = new TH2D("hraw_IC_Eraw_F07",Form("F07IC Eraw | run%04d;ID;Eraw (ch)",runN),6,0,6, 8400,-200, 8400);
  hraw_IC_Eraw[1] = new TH2D("hraw_IC_Eraw_F08",Form("F08IC Eraw | run%04d;ID;Eraw (ch)",runN),3,0,3, 860,-200, 8400);
  hraw_IC_Eraw[2] = new TH2D("hraw_IC_Eraw_F11",Form("F11IC Eraw | run%04d;ID;Eraw (ch)",runN),6,0,6, 430,-100, 4200);
  hraw_IC_Eraw[3] = new TH2D("hraw_IC_Eraw_F03",Form("F03IC Eraw | run%04d;ID;Eraw (ch)",runN),6,0,6, 860,-200, 8400);
  TH1D *hraw_IC_Esum[2];
  hraw_IC_Esum[0] = new TH1D("hraw_IC_Esum_F03",Form("F03IC Esum | run%04d;ID;Eraw (ch)",runN),1e3, 0, 60e3);
  hraw_IC_Esum[1] = new TH1D("hraw_IC_Esum_F07",Form("F07IC Esum | run%04d;ID;Eraw (ch)",runN),1e3, 0, 60e3);
  //===== PID_raw ==========
  TH2D *hraw_PID[3];
  hraw_PID[0] = new TH2D("hraw_PID_0",Form("PID raw (TOF35 vs F3MUSIC Esum) | run%04d;TOF35 (ns);F3MUSIC Esum (ch)",runN),400,90,150, 1e3,0,20e3); 
  hraw_PID[1] = new TH2D("hraw_PID_1",Form("PID raw (TOF57 vs F7MUSIC Esum) | run%04d;TOF57 (ns);F7MUSIC Esum (ch)",runN),400,120,200,1e3,0,20e3); 
  hraw_PID[2] = new TH2D("hraw_PID_2",Form("PID raw (TOF37 vs F7MUSIC Esum) | run%04d;TOF37 (ns);F7MUSIC Esum (ch)",runN),400,210,350,1e3,0,20e3); 
  //===== PID_calib ==========
  TH2D *hcalib_PID[3];
  hcalib_PID[0] = new TH2D("hcalib_PID_0",Form("PID calib (AoQ35 vs Z3) | run%04d;AoQ35;Z3",runN),1e3,2.0,2.6,1e3,0,50); 
  hcalib_PID[1] = new TH2D("hcalib_PID_1",Form("PID calib (AoQ57 vs Z5) | run%04d;AoQ57;Z5",runN),1e3,2.0,2.6,1e3,0,50); 
  hcalib_PID[2] = new TH2D("hcalib_PID_2",Form("PID calib (AoQ37 vs Z5) | run%04d;AoQ37;Z5",runN),1e3,2.0,2.6,1e3,0,50); 
  //===== PID_calib2 ==========
  TH2D *hcalib_PID2[3];
  hcalib_PID2[0] = new TH2D("hcalib_PID2_0",Form("PID calib2 (AoQ35_2 vs Z3) | run%04d;AoQ35;Z3",runN),1e3,2.0,2.6,1e3,0,50); 
  hcalib_PID2[1] = new TH2D("hcalib_PID2_1",Form("PID calib2 (AoQ57_2 vs Z5) | run%04d;AoQ57;Z5",runN),1e3,2.0,2.6,1e3,0,50); 
  hcalib_PID2[2] = new TH2D("hcalib_PID2_2",Form("PID calib2 (AoQ37_2 vs Z5) | run%04d;AoQ37;Z5",runN),1e3,2.0,2.6,1e3,0,50); 

  //===== Ge =============
  TH2D *hraw_Ge_Eraw[2];
  hraw_Ge_Eraw[0] = new TH2D("hraw_Ge_Eraw_F07",Form("F07Ge Eraw | run%04d;ID;Eraw (ch)",runN),32,0,32, 8000,-200,8400);
  hraw_Ge_Eraw[1] = new TH2D("hraw_Ge2_Eraw_F07",Form("F07Ge2 Eraw | run%04d;ID;Eraw (ch)",runN),32,0,32, 8000,-200,8400);
  TH2D *hraw_Ge_Traw[1];
  hraw_Ge_Traw[0] = new TH2D("hraw_Ge_Traw_F07",Form("G07Ge Traw | run%04d;ID;Traw (ch)",runN),128,0,128, 5000,-100000,100000);

  //===== PPAC =================================
  TH2D *hcalib_PPAC_TsumX;
  hcalib_PPAC_TsumX = new TH2D("hcalib_PPAC_TsumX",Form("PPAC TsumX | run%04d;F03/05/07/08/09/10/11;TsumX (ns)",runN),28,0,28,300,-2000,2000);
  //  hcalib_PPAC_TsumX = new TH2D("hcalib_PPAC_TsumX","PPAC TsumX;F03/05/07/08/09/10/11;TsumX (ns)",28,0,28,50,-3,3);
  TH2D *hcalib_PPAC_TsumY;
  hcalib_PPAC_TsumY = new TH2D("hcalib_PPAC_TsumY",Form("PPAC TsumY | run%04d;F03/05/07/08/09/10/11;TsumY (ns)",runN),28,0,28,300,-200000,200000);
  //  hcalib_PPAC_TsumY = new TH2D("hcalib_PPAC_TsumY","PPAC TsumY;F03/05/07/08/09/10/11;TsumY (ns)",28,0,28,50,-3,3);
  /*
  TH2D *hcalib_PPAC_TsumX[7];
  hcalib_PPAC_TsumX[0] = new TH2D("hcalib_PPAC_TsumX_F03","F03PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumX[1] = new TH2D("hcalib_PPAC_TsumX_F05","F05PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumX[2] = new TH2D("hcalib_PPAC_TsumX_F07","F07PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumX[3] = new TH2D("hcalib_PPAC_TsumX_F08","F08PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumX[4] = new TH2D("hcalib_PPAC_TsumX_F09","F09PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumX[5] = new TH2D("hcalib_PPAC_TsumX_F10","F10PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumX[6] = new TH2D("hcalib_PPAC_TsumX_F11","F11PPAC TsumX;ID;TsumX (ns)",4,0,4,300,-30,30);
  TH2D *hcalib_PPAC_TsumY[7];
  hcalib_PPAC_TsumY[0] = new TH2D("hcalib_PPAC_TsumY_F03","F03PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumY[1] = new TH2D("hcalib_PPAC_TsumY_F05","F05PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumY[2] = new TH2D("hcalib_PPAC_TsumY_F07","F07PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumY[3] = new TH2D("hcalib_PPAC_TsumY_F08","F08PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumY[4] = new TH2D("hcalib_PPAC_TsumY_F09","F09PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumY[5] = new TH2D("hcalib_PPAC_TsumY_F10","F10PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  hcalib_PPAC_TsumY[6] = new TH2D("hcalib_PPAC_TsumY_F11","F11PPAC TsumY;ID;TsumY (ns)",4,0,4,300,-30,30);
  */

  /*
  TH2D *hcalib_PPAC_TdiffX[7];
  hcalib_PPAC_TdiffX[0] = new TH2D("hcalib_PPAC_TdiffX_F03","F03PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffX[1] = new TH2D("hcalib_PPAC_TdiffX_F05","F05PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffX[2] = new TH2D("hcalib_PPAC_TdiffX_F07","F07PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffX[3] = new TH2D("hcalib_PPAC_TdiffX_F08","F08PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffX[4] = new TH2D("hcalib_PPAC_TdiffX_F09","F09PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffX[5] = new TH2D("hcalib_PPAC_TdiffX_F10","F10PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffX[6] = new TH2D("hcalib_PPAC_TdiffX_F11","F11PPAC TdiffX;ID;TdiffX (ns)",4,0,4,400,-100,100);
  TH2D *hcalib_PPAC_TdiffY[7];
  hcalib_PPAC_TdiffY[0] = new TH2D("hcalib_PPAC_TdiffY_F03","F03PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffY[1] = new TH2D("hcalib_PPAC_TdiffY_F05","F05PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffY[2] = new TH2D("hcalib_PPAC_TdiffY_F07","F07PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffY[3] = new TH2D("hcalib_PPAC_TdiffY_F08","F08PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffY[4] = new TH2D("hcalib_PPAC_TdiffY_F09","F09PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffY[5] = new TH2D("hcalib_PPAC_TdiffY_F10","F10PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  hcalib_PPAC_TdiffY[6] = new TH2D("hcalib_PPAC_TdiffY_F11","F11PPAC TdiffY;ID;TdiffY (ns)",4,0,4,400,-100,100);
  */

  TH2D *hcalib_PPAC_Pos[7][4];
  string tlabel[2]={"A","B"};
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[0][i] = new TH2D(Form("hcalib_PPAC_Pos_F03_%d",i),Form("F03PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300, -60, 60,300,-60,60);
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[1][i] = new TH2D(Form("hcalib_PPAC_Pos_F05_%d",i),Form("F05PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300,-120,120,300,-60,60);
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[2][i] = new TH2D(Form("hcalib_PPAC_Pos_F07_%d",i),Form("F07PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300,-150,150,300,-60,60);
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[3][i] = new TH2D(Form("hcalib_PPAC_Pos_F08_%d",i),Form("F08PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300, -60, 60,300,-60,60);
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[4][i] = new TH2D(Form("hcalib_PPAC_Pos_F09_%d",i),Form("F09PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300,-150,150,300,-60,60);
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[5][i] = new TH2D(Form("hcalib_PPAC_Pos_F10_%d",i),Form("F10PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300,-150,150,300,-60,60);
  for(int i=0;i<4;i++)hcalib_PPAC_Pos[6][i] = new TH2D(Form("hcalib_PPAC_Pos_F11_%d",i),Form("F11PPAC%d%s X vs Y | run%04d;X (mm);Y (mm)",i/2+1,tlabel[i%2].c_str(),runN),300, -60, 60,300,-60,60);

  TH2D *hcalib_Fpl_XY[7];
  hcalib_Fpl_XY[0] = new TH2D("hcalib_Fpl_XY_F03",Form("F03 X vs Y | run%04d;X (mm);Y (mm)",runN),300,  -60,  60, 300, -60, 60);
  hcalib_Fpl_XY[1] = new TH2D("hcalib_Fpl_XY_F05",Form("F05 X vs Y | run%04d;X (mm);Y (mm)",runN),300, -120, 120, 300, -60, 60);
  hcalib_Fpl_XY[2] = new TH2D("hcalib_Fpl_XY_F07",Form("F07 X vs Y | run%04d;X (mm);Y (mm)",runN),300, -150, 150, 300, -60, 60);
  hcalib_Fpl_XY[3] = new TH2D("hcalib_Fpl_XY_F08",Form("F08 X vs Y | run%04d;X (mm);Y (mm)",runN),300,  -60,  60, 300, -60, 60);
  hcalib_Fpl_XY[4] = new TH2D("hcalib_Fpl_XY_F09",Form("F09 X vs Y | run%04d;X (mm);Y (mm)",runN),300, -120, 120, 300, -60, 60);
  hcalib_Fpl_XY[5] = new TH2D("hcalib_Fpl_XY_F10",Form("F10 X vs Y | run%04d;X (mm);Y (mm)",runN),300, -120, 120, 300, -60, 60);
  hcalib_Fpl_XY[6] = new TH2D("hcalib_Fpl_XY_F11",Form("F11 X vs Y | run%04d;X (mm);Y (mm)",runN),300,  -60,  60, 300, -60, 60);

  TH2D *hcalib_Fpl_XA[7];
  hcalib_Fpl_XA[0] = new TH2D("hcalib_Fpl_XA_F03",Form("F03 X vs A | run%04d;X (mm);A (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_XA[1] = new TH2D("hcalib_Fpl_XA_F05",Form("F05 X vs A | run%04d;X (mm);A (mrad)",runN),300, -120, 120, 300, -50, 50);
  hcalib_Fpl_XA[2] = new TH2D("hcalib_Fpl_XA_F07",Form("F07 X vs A | run%04d;X (mm);A (mrad)",runN),300, -150, 150, 300, -50, 50);
  hcalib_Fpl_XA[3] = new TH2D("hcalib_Fpl_XA_F08",Form("F08 X vs A | run%04d;X (mm);A (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_XA[4] = new TH2D("hcalib_Fpl_XA_F09",Form("F09 X vs A | run%04d;X (mm);A (mrad)",runN),300, -120, 120, 300, -50, 50);
  hcalib_Fpl_XA[5] = new TH2D("hcalib_Fpl_XA_F10",Form("F10 X vs A | run%04d;X (mm);A (mrad)",runN),300, -120, 120, 300, -50, 50);
  hcalib_Fpl_XA[6] = new TH2D("hcalib_Fpl_XA_F11",Form("F11 X vs A | run%04d;X (mm);A (mrad)",runN),300,  -60,  60, 300, -50, 50);

  TH2D *hcalib_Fpl_YB[7];
  hcalib_Fpl_YB[0] = new TH2D("hcalib_Fpl_YB_F03",Form("F03 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_YB[1] = new TH2D("hcalib_Fpl_YB_F05",Form("F05 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_YB[2] = new TH2D("hcalib_Fpl_YB_F07",Form("F07 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_YB[3] = new TH2D("hcalib_Fpl_YB_F08",Form("F08 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_YB[4] = new TH2D("hcalib_Fpl_YB_F09",Form("F09 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_YB[5] = new TH2D("hcalib_Fpl_YB_F10",Form("F10 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);
  hcalib_Fpl_YB[6] = new TH2D("hcalib_Fpl_YB_F11",Form("F11 Y vs B | run%04d;X (mm);B (mrad)",runN),300,  -60,  60, 300, -50, 50);

  TH2D *hcalib_PLA_T;
  hcalib_PLA_T = new TH2D("hcalib_PLA_T",Form("Plastic T | run%04d;F3/F5/F7/F8/F9/F11/F8VETO/F11Long;Traw (ch)",runN),16,0,16,400,-400,400);

  TH2D *hcalib_PLA_LRQ[7];
  hcalib_PLA_LRQ[0] = new TH2D("hcalib_PLA_LRQ_F03",    Form(" F03PLA LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[1] = new TH2D("hcalib_PLA_LRQ_F05",    Form(" F05PLA LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[2] = new TH2D("hcalib_PLA_LRQ_F07",    Form(" F07PLA LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[3] = new TH2D("hcalib_PLA_LRQ_F08",    Form(" F08PLA LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[4] = new TH2D("hcalib_PLA_LRQ_F09",    Form(" F09PLA LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[5] = new TH2D("hcalib_PLA_LRQ_F11",    Form(" F11PLA LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[6] = new TH2D("hcalib_PLA_LRQ_F8VETO", Form(" F8VETO LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  hcalib_PLA_LRQ[7] = new TH2D("hcalib_PLA_LRQ_F11Long",Form("F11Long LQ vs RQ | run%04d;LQ (ch);RQ (ch)" ,runN), 430,-100,4200,430,-100,4200);
  
  TH2D *hcalib_PLA_LRQTC[7];
  hcalib_PLA_LRQTC[0] = new TH2D("hcalib_PLA_LRQTC_F03",    Form("F03PLA QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 700,400,-10, 700);
  hcalib_PLA_LRQTC[1] = new TH2D("hcalib_PLA_LRQTC_F05",    Form("F05PLA QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 700,400,-10, 700);
  hcalib_PLA_LRQTC[2] = new TH2D("hcalib_PLA_LRQTC_F07",    Form("F07PLA QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 700,400,-10, 700);
  hcalib_PLA_LRQTC[3] = new TH2D("hcalib_PLA_LRQTC_F08",    Form("F08PLA QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 200,400,-10, 200);
  hcalib_PLA_LRQTC[4] = new TH2D("hcalib_PLA_LRQTC_F09",    Form("F09PLA QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 700,400,-10, 700);
  hcalib_PLA_LRQTC[5] = new TH2D("hcalib_PLA_LRQTC_F11",    Form("F11PLA QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 200,400,-10, 200);
  hcalib_PLA_LRQTC[6] = new TH2D("hcalib_PLA_LRQTC_F8VETO", Form("F8VETO QTC LQ vs RQ  | run%04d;LQ (ns);RQ (ns)" ,runN), 400,-10, 700,400,-10, 700);
  hcalib_PLA_LRQTC[7] = new TH2D("hcalib_PLA_LRQTC_F11Long",Form("F11Long QTC LQ vs RQ | run%04d;LQ (ns);RQ (ns)" ,runN),400,-10, 700,400,-10, 700);

  TH2D *hcalib_PLA_Qdiff_Pos[7];
  hcalib_PLA_Qdiff_Pos[0] = new TH2D("hcalib_PLA_Qdiff_Pos_F03",    Form("F03PLA LQ-RQ vs F03X  | run%04d;F03X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[1] = new TH2D("hcalib_PLA_Qdiff_Pos_F05",    Form("F05PLA LQ-RQ vs F05X  | run%04d;F05X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[2] = new TH2D("hcalib_PLA_Qdiff_Pos_F07",    Form("F07PLA LQ-RQ vs F07X  | run%04d;F07X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[3] = new TH2D("hcalib_PLA_Qdiff_Pos_F08",    Form("F08PLA LQ-RQ vs F08X  | run%04d;F08X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[4] = new TH2D("hcalib_PLA_Qdiff_Pos_F09",    Form("F09PLA LQ-RQ vs F09X  | run%04d;F09X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[5] = new TH2D("hcalib_PLA_Qdiff_Pos_F11",    Form("F11PLA LQ-RQ vs F11X  | run%04d;F11X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[6] = new TH2D("hcalib_PLA_Qdiff_Pos_F8VETO", Form("F8VETO LQ-RQ vs F08X  | run%04d;F08X (mm);LQ-RQ (ch)",runN),  300,-50,50,300,-1000,1000);
  hcalib_PLA_Qdiff_Pos[7] = new TH2D("hcalib_PLA_Qdiff_Pos_F11Long",Form("F11Long LQ-RQ vs F11X | run%04d;F11X (mm);LQ-RQ (ch)",runN), 300,-50,50,300,-1000,1000);

  TH2D *hcalib_PPAC_fX[7];
  hcalib_PPAC_fX[0] = new TH2D("hcalib_PPAC_fX_F03",Form("F03PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fX[1] = new TH2D("hcalib_PPAC_fX_F05",Form("F05PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fX[2] = new TH2D("hcalib_PPAC_fX_F07",Form("F07PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fX[3] = new TH2D("hcalib_PPAC_fX_F08",Form("F08PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fX[4] = new TH2D("hcalib_PPAC_fX_F09",Form("F09PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fX[5] = new TH2D("hcalib_PPAC_fX_F10",Form("F10PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fX[6] = new TH2D("hcalib_PPAC_fX_F11",Form("F11PPAC fX | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);

  TH2D *hcalib_PPAC_fY[7];
  hcalib_PPAC_fY[0] = new TH2D("hcalib_PPAC_fY_F03",Form("F03PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fY[1] = new TH2D("hcalib_PPAC_fY_F05",Form("F05PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fY[2] = new TH2D("hcalib_PPAC_fY_F07",Form("F07PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fY[3] = new TH2D("hcalib_PPAC_fY_F08",Form("F08PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fY[4] = new TH2D("hcalib_PPAC_fY_F09",Form("F09PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fY[5] = new TH2D("hcalib_PPAC_fY_F10",Form("F10PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);
  hcalib_PPAC_fY[6] = new TH2D("hcalib_PPAC_fY_F11",Form("F11PPAC fY | run%04d;ID;fired(1) or not(0)",runN),4,0,4,2,0,2);

  // [7] : F03/05/07/08/09/10/11
  // [2] : X/Y
  // [4] : 1A/1B/2A/2B

  TH1D *hcalib_PPAC_eff2D0[2];
  hcalib_PPAC_eff2D0[0] = new TH1D("hcalib_eff2D_total_0",Form("F07IC_Esum for PPAC (Total) | run%04d;F07IC_Esum (MeV);#it{N} (events)",runN),100,0,200);
  hcalib_PPAC_eff2D0[1] = new TH1D("hcalib_eff2D_total_1",Form("F11IC_Esum for PPAC (Total) | run%04d;F11IC_Esum (MeV);#it{N} (events)",runN),100,0,200);
  TH1D *hcalib_PPAC_eff2D[7][2][4];
  string tlabel_eff2D1[7]={"F03","F05","F07","F08","F09","F10","F11"};
  string tlabel_eff2D2[2]={"X","Y"};
  string tlabel_eff2D3[4]={"1A","1B","2A","2B"};

  // F03/05/07-X
  for(int ii=0;ii<3;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D[ii][0][kk] = 
	new TH1D(Form("hcalib_eff2D_%sPPAC_%s_%s",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[0].c_str()),
		 Form("F07IC_Esum for %sPPAC-%s-%s (Fired) | run%04d;F07IC_Esum (MeV);#it{N} (events)",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[0].c_str(), runN),
		 100,0,200);
    }
  // F08/09/10/11-X
  for(int ii=3;ii<7;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D[ii][0][kk] = 
	new TH1D(Form("hcalib_eff2D_%sPPAC_%s_%s",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[0].c_str()),
		 Form("F11IC_Esum for %sPPAC-%s-%s (Fired) | run%04d;F11IC_Esum (MeV);#it{N} (events)",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[0].c_str(), runN),
		 100,0,200);
    }
  // F03/05/07-Y
  for(int ii=0;ii<3;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D[ii][1][kk] = 
	new TH1D(Form("hcalib_eff2D_%sPPAC_%s_%s",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[1].c_str()),
		 Form("F07IC_Esum for %sPPAC-%s-%s (Fired) | run%04d;F07IC_Esum (MeV);#it{N} (events)",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[1].c_str(), runN),
		 100,0,200);
    }
  // F08/09/10/11-Y
  for(int ii=3;ii<7;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D[ii][1][kk] = 
	new TH1D(Form("hcalib_eff2D_%sPPAC_%s_%s",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[1].c_str()),
		 Form("F11IC_Esum for %sPPAC-%s-%s (Fired) | run%04d;F11IC_Esum (MeV);#it{N} (events)",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[1].c_str(), runN),
		 100,0,200);
    }

  //========================================================================
  TH2D *hana_PID35[4];
  hana_PID35[0] = new TH2D("hana_PID35_0",Form("AoQ35_2  vs Zet3 | run%04d;AoQ35_2;Zet7", runN),1500,1.5,3.0,1500,0,50);
  hana_PID35[1] = new TH2D("hana_PID35_1",Form("AoQ35_2  vs Zet3 | run%04d;AoQ35_2;Zet7", runN), 500,1.8,2.2,400,10,17);
  hana_PID35[2] = new TH2D("hana_PID35_2",Form("AoQ35_2  vs Zet3 | run%04d;AoQ35_2;Zet7", runN), 500,1.8,2.2,400,17,24);
  hana_PID35[3] = new TH2D("hana_PID35_3",Form("AoQ35_2  vs Zet3 | run%04d;AoQ35_2;Zet7", runN), 500,1.8,2.2,400,24,31);

  TH2D *hana_PID57[4];
  hana_PID57[0] = new TH2D("hana_PID57_0",Form("AoQ57_2  vs Zet7 | run%04d;AoQ57_2;Zet7", runN),1500,1.5,3.0,1500,0,50);
  hana_PID57[1] = new TH2D("hana_PID57_1",Form("AoQ57_2  vs Zet7 | run%04d;AoQ57_2;Zet7", runN), 500,1.8,2.2,400,10,17);
  hana_PID57[2] = new TH2D("hana_PID57_2",Form("AoQ57_2  vs Zet7 | run%04d;AoQ57_2;Zet7", runN), 500,1.8,2.2,400,17,24);
  hana_PID57[3] = new TH2D("hana_PID57_3",Form("AoQ57_2  vs Zet7 | run%04d;AoQ57_2;Zet7", runN), 500,1.8,2.2,400,24,31);

  TH2D *hana_PID37[4];
  hana_PID37[0] = new TH2D("hana_PID37_0",Form("AoQ57[1] vs Zet7 | run%04d;AoQ57[1];Zet7", runN),1500,1.5,3.0,1500,0,50);
  hana_PID37[1] = new TH2D("hana_PID37_1",Form("AoQ57[1] vs Zet7 | run%04d;AoQ57[1];Zet7", runN), 500,1.8,2.2,400,10,17);
  hana_PID37[2] = new TH2D("hana_PID37_2",Form("AoQ57[1] vs Zet7 | run%04d;AoQ57[1];Zet7", runN), 500,1.8,2.2,400,17,24);
  hana_PID37[3] = new TH2D("hana_PID37_3",Form("AoQ57[1] vs Zet7 | run%04d;AoQ57[1];Zet7", runN), 500,1.8,2.2,400,24,31);

  TH1D *hana_AoQ[3];
  hana_AoQ[0] = new TH1D("hana_AoQ_35",Form("AoQ35_2  | run%04d;AoQ35_2 from PLA35" , runN),1000,1.5,3.0);
  hana_AoQ[1] = new TH1D("hana_AoQ_57",Form("AoQ57_2  | run%04d;AoQ57_2 from PLA57" , runN),1000,1.5,3.0);
  hana_AoQ[2] = new TH1D("hana_AoQ_37",Form("AoQ57[1] | run%04d;AoQ57[1] from PLA37", runN),1000,1.5,3.0);

  TH1D *hana_Zet[4];
  hana_Zet[0] = new TH1D("hana_Zet_F3" ,Form("Zet3  | run%04d;#it{N} (events)",runN) ,400,10,35);
  hana_Zet[1] = new TH1D("hana_Zet_F7" ,Form("Zet7  | run%04d;#it{N} (events)",runN) ,400,10,35);
  hana_Zet[2] = new TH1D("hana_Zet_F8" ,Form("Zet8  | run%04d;#it{N} (events)",runN) ,400,10,35);
  hana_Zet[3] = new TH1D("hana_Zet_F11",Form("Zet11 | run%04d;#it{N} (events)",runN) ,400,10,35);

  TH2D *hana_PID[2][2];
  hana_PID[0][0] = new TH2D("hana_PID_up_wogate",  Form("AoQ57[1] vs Zet7   | run%04d;AoQ57[1] from PLA37;Zet7"  ,runN),300,2.66,2.71,300,17,21);
  hana_PID[0][1] = new TH2D("hana_PID_up_wgate",   Form("AoQ57[1] vs Zet7   | run%04d;AoQ57[1] from PLA37;Zet7"  ,runN),300,2.66,2.71,300,17,21);
  hana_PID[1][0] = new TH2D("hana_PID_down_wogate",Form("AoQ911[1] vs Zet11 | run%04d;AoQ911[1] from PLA811;Zet7",runN),300,2.66,2.71,300,17,21);
  hana_PID[1][1] = new TH2D("hana_PID_down_wgate", Form("AoQ911[1] vs Zet11 | run%04d;AoQ911[1] from PLA811;Zet7",runN),300,2.66,2.71,300,17,21);

  TH2D *hana_PID2[2][2];
  hana_PID2[0][0] = new TH2D("hana_PID2_up_wogate",  Form("AoQ57[1] vs Zet7 (wEMT)   | run%04d;AoQ57[1] from PLA37;Zet7"  ,runN), 300,2.66,2.71,300,17,21);
  hana_PID2[0][1] = new TH2D("hana_PID2_up_wgate",   Form("AoQ57[1] vs Zet7 (wEMT)   | run%04d;AoQ57[1] from PLA37;Zet7"  ,runN), 300,2.66,2.71,300,17,21);
  hana_PID2[1][0] = new TH2D("hana_PID2_down_wogate",Form("AoQ911[1] vs Zet11 (wEMT) | run%04d;AoQ911[1] from PLA811;Zet7",runN),300,2.66,2.71,300,17,21);
  hana_PID2[1][1] = new TH2D("hana_PID2_down_wgate", Form("AoQ911[1] vs Zet11 (wEMT) | run%04d;AoQ911[1] from PLA811;Zet7",runN),300,2.66,2.71,300,17,21);

  TH2D *hana_F7QF8Q;
  hana_F7QF8Q = new TH2D("hana_F7QF8Q",Form("F7Pla_Q vs F8Pla_Q | run%04d;F7Pla_Q (ch);F8Pla_Q (ch)",runN),400,0,4000,400,0,4000);

  TH2D *hana_profile1[7];
  hana_profile1[0] = new TH2D("hana_profile1_0", Form("F03 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);
  hana_profile1[1] = new TH2D("hana_profile1_1", Form("F05 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);
  hana_profile1[2] = new TH2D("hana_profile1_2", Form("F07 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);
  hana_profile1[3] = new TH2D("hana_profile1_3", Form("F08 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);
  hana_profile1[4] = new TH2D("hana_profile1_4", Form("F09 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);
  hana_profile1[5] = new TH2D("hana_profile1_5", Form("F10 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);
  hana_profile1[6] = new TH2D("hana_profile1_6", Form("F11 X vs Y gated | run%04d;X (mm);Y (mm)",runN), 400,-150,150,400,-150,150);

  TH2D *hana_profile2[7];
  hana_profile2[0] = new TH2D("hana_profile2_0", Form("F03 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile2[1] = new TH2D("hana_profile2_1", Form("F05 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile2[2] = new TH2D("hana_profile2_2", Form("F07 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile2[3] = new TH2D("hana_profile2_3", Form("F08 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile2[4] = new TH2D("hana_profile2_4", Form("F09 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile2[5] = new TH2D("hana_profile2_5", Form("F10 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile2[6] = new TH2D("hana_profile2_6", Form("F11 X vs A gated | run%04d;X (mm);A (mrad)",runN), 400,-150,150,400,-50,50);

  TH2D *hana_profile3[7];
  hana_profile3[0] = new TH2D("hana_profile3_0", Form("F03 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile3[1] = new TH2D("hana_profile3_1", Form("F05 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile3[2] = new TH2D("hana_profile3_2", Form("F07 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile3[3] = new TH2D("hana_profile3_3", Form("F08 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile3[4] = new TH2D("hana_profile3_4", Form("F09 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile3[5] = new TH2D("hana_profile3_5", Form("F10 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);
  hana_profile3[6] = new TH2D("hana_profile3_6", Form("F11 Y vs B gated | run%04d;Y (mm);B (mrad)",runN), 400,-150,150,400,-50,50);

  TH1D *hana_emt[3][2][5];
  {
    string label_emt1[3]={"No EMTcut","EMTcut","Full EMTcut"}; 
    string label_emt2[2]={"#it{N}_{in}","#it{N}_{out}"}; 
    double range[5]={20,40,20,40,4.0};
    
    for(int i=0;i<3;i++)for(int j=0;j<2;j++){
	hana_emt[i][j][0] = new TH1D(Form("EMT_X_%d_%d",i,j),Form("F8X %s %s | run%04d;F8X (mm)   ;#it{N} (events/mm)",       label_emt1[i].c_str(),label_emt2[j].c_str(),runN),2*(int)range[0],  -1.*range[0], range[0]);
	hana_emt[i][j][1] = new TH1D(Form("EMT_A_%d_%d",i,j),Form("F8A %s %s | run%04d;F8A (mrad) ;#it{N} (events/mrad)" ,    label_emt1[i].c_str(),label_emt2[j].c_str(),runN),2*(int)range[1],  -1.*range[1], range[1]);
	hana_emt[i][j][2] = new TH1D(Form("EMT_Y_%d_%d",i,j),Form("F8Y %s %s | run%04d;F8Y (mm)   ;#it{N} (events/mm)",       label_emt1[i].c_str(),label_emt2[j].c_str(),runN),2*(int)range[2],  -1.*range[2], range[2]);
	hana_emt[i][j][3] = new TH1D(Form("EMT_B_%d_%d",i,j),Form("F8B %s %s | run%04d;F8B (mrad) ;#it{N} (events/mrad)" ,    label_emt1[i].c_str(),label_emt2[j].c_str(),runN),2*(int)range[3],  -1.*range[3], range[3]);
	hana_emt[i][j][4] = new TH1D(Form("EMT_D_%d_%d",i,j),Form("Delta57 %s %s | run%04d;Delta57 (%);#it{N} (events/0.05%)",label_emt1[i].c_str(),label_emt2[j].c_str(),runN),10*(int)range[4], -1.*range[4], range[4]);
      }
  }

  // Random number
  TRandom *grand = new TRandom();
  grand->SetSeed( time(NULL) );

  // event counter
  int neve = 0; 

  //===== Timer; start time =========================
  TDatime *T0=new TDatime();
  int t0[3];
  t0[0]= T0->GetHour();t0[1]= T0->GetMinute();t0[2]= T0->GetSecond();

  //=====  Event Loop & Decode ================================
  while(estore->GetNextEvent()){
  //    while(estore->GetNextEvent()&&neve<10000){

    if(neve==0){

	// for 52Carune0186
	/*
	Brho_NMR[0] = 6.9800;
	Brho_NMR[1] = 6.5935;
	Brho_NMR[2] = 6.5616;
	Brho_NMR[3] = 6.5616;
	Brho_NMR[4] = 6.2051;
	Brho_NMR[5] = 6.2051;
	Brho_NMR[6] = 5.5382;
	Brho_NMR[7] = 5.5200;
	*/

      cout << "===== Load Dipole Brho ======================================================================" << endl;
      TArtBigRIPSParameters *para = TArtBigRIPSParameters::Instance();
      para->LoadDipoleBrho();
      for(int m=0;m<8;m++){
	TString* namedipole = new TString(Form("D%d",m+1));
	

	Brho_NMR[m] = para->GetDipoleBrho(namedipole);
	//	cout << Form("D%d : %6.4f Tm",m+1,Brho_NMR[m]) << endl;
      }
      delete para;
      cout << "=============================================================================================" << endl;
    }
    
    Nevent = rawevent->GetEventNumber();
    if(Nevent<0){ continue;}

    // Number of segment
    int numseg = rawevent->GetNumSeg();

    //===== Initialize variables =======================
    // defined in include/ribf_raw.h
    rawdata_reset();
#ifdef ONLINE_FLAG
    // defined in include/ribf_encpid.h
    var_init();
#endif
    //===== Segment Loop ==============================
    for(int i=0; i<numseg; i++){
      TArtRawSegmentObject *seg = rawevent->GetSegment(i);
      int dev=seg->GetDevice();
      int fpl=seg->GetFP();
      int det=seg->GetDetector();
      int mod=seg->GetModule();
      int EFN=seg->GetAddress();
      int num=seg->GetNumData();

      // 20240511
      // to skip the number of odd-channels reading
      // for may10th0001.ridf
      bool tempflag = false;
      if (Nevent < 10) if (mod == 36) cout << Form("dev: %d, fpl: %d, det: %d, mod: %d, EFN: %d, num: %d, ", dev, fpl, det, mod, EFN, num ) << endl;

      //===== Data read from one segment ===============
      for(int j=0; j<num; j++){	    

	TArtRawDataObject *d = seg->GetData(j);
	unsigned int buf = d->GetVal();
	int geo = d->GetGeo();
	int ch = d->GetCh();
	int edge = d->GetEdge();

      if(neve==0 && j==0){
	cout << Form("(SEG,EFN)=(%3d,%3d) (dev,fpl,det,mod,geo)=(%3d,%3d,%3d,%3d,%3d) (ndata)=(%3d)  ",i,EFN,dev,fpl,det,mod,geo,num);
	if(num==0)cout << endl;
      }      	

      // 20240511
      // to skip the number of odd-channels reading
      // for may10th0001.ridf
      if(dev==0 && fpl==7 && det==4 && mod==32 && geo==2 && ch==0){
	if(tempflag){continue;}else{tempflag=true;}
      }

      // defined in include/ribf_raw.h
      moduledata_fill(j,neve,EFN,dev,fpl,det,mod,geo,edge,ch,buf);

      } // End of loop in one segment

    }	// End of loop in one event
    
    //===== Calibration ======================
    // defined in include/ribf_raw.h
    rawdata_fill();

    //===== for debug data taken on Dec. 05th =====
    /*
    if(runN<=14){
      PPAC_ATraw[8][2] = -1685;
      PPAC_Traw[8][3][3] = PPAC_Traw[8][2][3];
    }
    */

#ifdef ONLINE_FLAG
    // defined in include/ribf_encpid.h
    ribf_encpid(runN,grand);
#endif

    //===== gate =============================
    // Pileup rejection
    if(PLA_Mhit[3][0]==1 && PLA_Mhit[3][1]==1){tgate[0]=true;}
    if(PLA_Mhit[5][0]==1 && PLA_Mhit[5][1]==1){tgate[1]=true;}
    if(PLA_Mhit[7][0]==1 && PLA_Mhit[7][1]==1){tgate[2]=true;}
    if(PLA_Mhit[8][0]==1 && PLA_Mhit[8][1]==1){tgate[3]=true;}
    // Single hit within +-6 us for all F03/F05/F07/F08 plastics
    //    if(tgate[0]&&tgate[1]&&tgate[2]&&tgate[3]){tgate[4]=true;}
    if(PLA_Mhit[3][0]==1){tgate[4]=true;}

    //    if(PLA_Mhit[7][0]==1 && tgate[5] && tgate[6]){tgate[7]==true;}
    if(PLA_Mhit[7][0]==1){tgate[7]=true;}

    // upstream PID, ellipse-shaped cut
    //    if(pow((AoQ57[1]-2.553)/(0.0032*4),2.) + pow((Zet7-20.)/(0.128*4),2.) <= 1.){tgate[10]=true;}
    if(pow((AoQ57[1] - pidgate[0][0])/(pidgate[0][1]*pidgate[0][2]),2.)  + pow((Zet7-pidgate[0][3])/(pidgate[0][4]*pidgate[0][5]),2.) <= 1.){tgate[8]=true;}
    if(pow((AoQ911[1] - pidgate[1][0])/(pidgate[1][1]*pidgate[1][2]),2.) + pow((Zet11-pidgate[1][3])/(pidgate[1][4]*pidgate[1][5]),2.) <= 1.){tgate[9]=true;}

    if(tgate[ 7] && tgate[ 8]){tgate[10]=true;}
    if(tgate[10] && tgate[ 9]){tgate[20]=true;}

      
    if(emtgate[0][0] < Fpl_XP[8] && Fpl_XP[8] < emtgate[0][1]){tgate[31]=true;}
    if(emtgate[1][0] < Fpl_XT[8] && Fpl_XT[8] < emtgate[1][1]){tgate[32]=true;}
    if(emtgate[2][0] < Fpl_YP[8] && Fpl_YP[8] < emtgate[2][1]){tgate[33]=true;}
    if(emtgate[3][0] < Fpl_YT[8] && Fpl_YT[8] < emtgate[3][1]){tgate[34]=true;}
    if(emtgate[4][0] < Delta57   && Delta57   < emtgate[4][1]){tgate[35]=true;}

    if(tgate[31]&&tgate[32]&&tgate[33]&&tgate[34]&&tgate[35] ){tgate[40]=true;}
    if(           tgate[32]&&tgate[33]&&tgate[34]&&tgate[35] ){tgate[41]=true;}
    if(tgate[31]           &&tgate[33]&&tgate[34]&&tgate[35] ){tgate[42]=true;}
    if(tgate[31]&&tgate[32]           &&tgate[34]&&tgate[35] ){tgate[43]=true;}
    if(tgate[31]&&tgate[32]&&tgate[33]           &&tgate[35] ){tgate[44]=true;}
    if(tgate[31]&&tgate[32]&&tgate[33]&&tgate[34]            ){tgate[45]=true;}

    // 2Dgate
    if(g2d[0] && g2d[0]->IsInside(TOF37,F7IC_Esum)){tgate[80]=true;}
    if(g2d[1] && g2d[1]->IsInside(TOF37,F7IC_Esum)){tgate[81]=true;}

    //===== Fill data in histogram/tree ======
     
    //for(int n=0;n<128;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][n])cout << v1190raw[0][n][m]*0.1 << endl;
    for(int n=0;n<128;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][n])hraw_v1190[0]->Fill(n,v1190raw[0][n][m]*0.1);
    for(int n=0;n<128;n++)hraw_v1190num[0]->Fill(n,v1190num[0][n]);
    for(int n=0;n<128;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[1][n])hraw_v1190[1]->Fill(n,v1190raw[1][n][m]*0.1);
    for(int n=0;n<128;n++)hraw_v1190num[1]->Fill(n,v1190num[1][n]);
    for(int n=0;n<128;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[2][n])hraw_v1190[2]->Fill(n,v1190raw[2][n][m]*0.1);
    for(int n=0;n<128;n++)hraw_v1190num[2]->Fill(n,v1190num[2][n]);

    for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n])hraw_v1290L[0]->Fill(n,v1290Lraw[0][n][m]*0.025);
    for(int n=0;n<32;n++)hraw_v1290Lnum[0]->Fill(n,v1290Lnum[0][n]);
    for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n])hraw_v1290L[1]->Fill(n,v1290Lraw[1][n][m]*0.025);
    for(int n=0;n<32;n++)hraw_v1290Lnum[1]->Fill(n,v1290Lnum[1][n]);

    for(int n=0;n<32;n++)hraw_v1290Lnum2[0]->Fill(n,v1290Lnum2[0][n]);
    for(int n=0;n<32;n++)hraw_v1290Lnum2[1]->Fill(n,v1290Lnum2[1][n]);

    /*
    for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Tnum[0][n])hraw_v1290T[0]->Fill(n,v1290Traw[0][n][m]*0.025);
    for(int n=0;n<32;n++)hraw_v1290Tnum[0]->Fill(n,v1290Tnum[0][n]);
    for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Tnum[1][n])hraw_v1290T[1]->Fill(n,v1290Traw[1][n][m]);
    for(int n=0;n<32;n++)hraw_v1290Tnum[1]->Fill(n,v1290Tnum[1][n]);
    */

    for(int n=0;n<32;n++)hraw_v1290T->Fill(n,(v1290Traw[1][n][0])*0.025);
    for(int n=0;n<32;n++)hraw_v1290W->Fill(n,(v1290Traw[1][n][0]-v1290Lraw[1][n][0])*0.025);

    for(int n=0;n<16;n++)hraw_qdc->Fill(n,qdc[n]);

    for(int n=0;n<6;n++)hraw_adc[0]->Fill(n,adc[0][n]);
    for(int n=0;n<4;n++)hraw_adc[1]->Fill(n,adc[1][n]);
    for(int n=0;n<6;n++)hraw_adc[2]->Fill(n,adc[2][n]);
    for(int n=0;n<6;n++)hraw_adc[3]->Fill(n,adc[3][n]);

    // PPAC Anode
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][n+ 4])hraw_PPAC_v1190[0]->Fill(n,v1190raw[0][n+ 4][m]); // F03
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[1][n+96])hraw_PPAC_v1190[1]->Fill(n,v1190raw[1][n+96][m]); // F05
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[2][n+ 4])hraw_PPAC_v1190[2]->Fill(n,v1190raw[2][n+ 4][m]); // F07
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][n+64])hraw_PPAC_v1190[3]->Fill(n,v1190raw[0][n+64][m]); // F08
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][n+68])hraw_PPAC_v1190[4]->Fill(n,v1190raw[0][n+68][m]); // F09
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[1][n+44])hraw_PPAC_v1190[5]->Fill(n,v1190raw[1][n+44][m]); // F10
    for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][n+76])hraw_PPAC_v1190[6]->Fill(n,v1190raw[0][n+76][m]); // F11
    // PPAC Cathode
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][l*4+n+ 16])hraw_PPAC_v1190[0]->Fill(l*4+n+4,v1190raw[0][l*4+n+ 16][m]);
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[1][l*4+n+112])hraw_PPAC_v1190[1]->Fill(l*4+n+4,v1190raw[1][l*4+n+112][m]);
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[2][l*4+n+ 16])hraw_PPAC_v1190[2]->Fill(l*4+n+4,v1190raw[2][l*4+n+ 16][m]);
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][l*4+n+ 80])hraw_PPAC_v1190[3]->Fill(l*4+n+4,v1190raw[0][l*4+n+ 80][m]);
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][l*4+n+ 96])hraw_PPAC_v1190[4]->Fill(l*4+n+4,v1190raw[0][l*4+n+ 96][m]);
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[1][l*4+n+ 48])hraw_PPAC_v1190[5]->Fill(l*4+n+4,v1190raw[1][l*4+n+ 48][m]);
    for(int l=0;l<4;l++)for(int n=0;n<4;n++)for(int m=0;m<N_Mhit;m++)if(m<v1190num[0][l*4+n+112])hraw_PPAC_v1190[6]->Fill(l*4+n+4,v1190raw[0][l*4+n+112][m]);

    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+16])hraw_PLA_v1290[0]->Fill(n   ,v1290Lraw[0][n+12][m]); // F03
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+18])hraw_PLA_v1290[0]->Fill(n+ 2,v1290Lraw[0][n+ 8][m]); // F05
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+20])hraw_PLA_v1290[0]->Fill(n+ 4,v1290Lraw[0][n+14][m]); // F07
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+22])hraw_PLA_v1290[0]->Fill(n+ 6,v1290Lraw[0][n+22][m]); // F08
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+28])hraw_PLA_v1290[0]->Fill(n+ 8,v1290Lraw[0][n+28][m]); // F09
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+24])hraw_PLA_v1290[0]->Fill(n+10,v1290Lraw[0][n+24][m]); // F11
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+26])hraw_PLA_v1290[0]->Fill(n+12,v1290Lraw[0][n+26][m]); // F08VETO
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+30])hraw_PLA_v1290[0]->Fill(n+14,v1290Lraw[0][n+30][m]); // F11Long
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+12])hraw_PLA_v1290[0]->Fill(n+16,v1290Lraw[0][n+16][m]); // F3-2
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+ 8])hraw_PLA_v1290[0]->Fill(n+18,v1290Lraw[0][n+18][m]); // F5-2
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[0][n+20])hraw_PLA_v1290[0]->Fill(n+20,v1290Lraw[0][n+20][m]); // F7-2

    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+ 0])hraw_PLA_v1290[1]->Fill(n   ,v1290Lraw[1][n+ 0][m]); // F03
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+ 2])hraw_PLA_v1290[1]->Fill(n+ 2,v1290Lraw[1][n+ 2][m]); // F05
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+ 4])hraw_PLA_v1290[1]->Fill(n+ 4,v1290Lraw[1][n+ 4][m]); // F07
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+ 6])hraw_PLA_v1290[1]->Fill(n+ 6,v1290Lraw[1][n+ 6][m]); // F08
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+12])hraw_PLA_v1290[1]->Fill(n+ 8,v1290Lraw[1][n+12][m]); // F09
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+ 8])hraw_PLA_v1290[1]->Fill(n+10,v1290Lraw[1][n+ 8][m]); // F11
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+10])hraw_PLA_v1290[1]->Fill(n+12,v1290Lraw[1][n+10][m]); // F08VETO
    for(int n=0;n<2;n++)for(int m=0;m<N_Mhit;m++)if(m<v1290Lnum[1][n+14])hraw_PLA_v1290[1]->Fill(n+14,v1290Lraw[1][n+14][m]); // F11Long

    //    for(int ii=0;ii<4;ii++)cout << ii << " " << PPAC_ATraw[7][ii] << " " << PPAC_AT[7][ii] << endl;
    //    if(tgate[3]){
    //===== Rawdata ===============
    //===== PPAC-T =========
    for(int n=0;n<4;n++)hraw_PPAC_Traw[0]->Fill(n,PPAC_ATraw[ 3][n]);
    for(int n=0;n<4;n++)hraw_PPAC_Traw[1]->Fill(n,PPAC_ATraw[ 5][n]);
    for(int n=0;n<4;n++)hraw_PPAC_Traw[2]->Fill(n,PPAC_ATraw[ 7][n]);
    for(int n=0;n<4;n++)hraw_PPAC_Traw[3]->Fill(n,PPAC_ATraw[ 8][n]);
    for(int n=0;n<4;n++)hraw_PPAC_Traw[4]->Fill(n,PPAC_ATraw[ 9][n]);
    for(int n=0;n<4;n++)hraw_PPAC_Traw[5]->Fill(n,PPAC_ATraw[10][n]);
    for(int n=0;n<4;n++)hraw_PPAC_Traw[6]->Fill(n,PPAC_ATraw[11][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[0]->Fill(m*4+n+4,PPAC_Traw[ 3][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[1]->Fill(m*4+n+4,PPAC_Traw[ 5][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[2]->Fill(m*4+n+4,PPAC_Traw[ 7][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[3]->Fill(m*4+n+4,PPAC_Traw[ 8][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[4]->Fill(m*4+n+4,PPAC_Traw[ 9][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[5]->Fill(m*4+n+4,PPAC_Traw[10][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_Traw[6]->Fill(m*4+n+4,PPAC_Traw[11][m][n]);

    for(int n=0;n<4;n++)hraw_PPAC_T[0]->Fill(n,PPAC_AT[ 3][n]);
    for(int n=0;n<4;n++)hraw_PPAC_T[1]->Fill(n,PPAC_AT[ 5][n]);
    for(int n=0;n<4;n++)hraw_PPAC_T[2]->Fill(n,PPAC_AT[ 7][n]);
    for(int n=0;n<4;n++)hraw_PPAC_T[3]->Fill(n,PPAC_AT[ 8][n]);
    for(int n=0;n<4;n++)hraw_PPAC_T[4]->Fill(n,PPAC_AT[ 9][n]);
    for(int n=0;n<4;n++)hraw_PPAC_T[5]->Fill(n,PPAC_AT[10][n]);
    for(int n=0;n<4;n++)hraw_PPAC_T[6]->Fill(n,PPAC_AT[11][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[0]->Fill(m*4+n+4,PPAC_T[ 3][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[1]->Fill(m*4+n+4,PPAC_T[ 5][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[2]->Fill(m*4+n+4,PPAC_T[ 7][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[3]->Fill(m*4+n+4,PPAC_T[ 8][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[4]->Fill(m*4+n+4,PPAC_T[ 9][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[5]->Fill(m*4+n+4,PPAC_T[10][m][n]);
    for(int m=0;m<4;m++)for(int n=0;n<4;n++)hraw_PPAC_T[6]->Fill(m*4+n+4,PPAC_T[11][m][n]);
    //===== PLA-T ==========
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n   ,PLA_T[ 3][n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+ 2,PLA_T[ 5][n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+ 4,PLA_T[ 7][n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+ 6,PLA_T[ 8][n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+ 8,PLA_T[ 9][n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+10,PLA_T[11][n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+12,F8VETO_T[n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+14,F11Long_T[n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+16,F3PLA2_T[n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+18,F5PLA2_T[n]);
    for(int n=0;n<2;n++)hraw_PLA_T->Fill(n+20,F7PLA2_T[n]);
    //cout << PLA_T[3][0] << endl;
    for(int lr=0;lr<2;lr++)hraw_PLA_T1[0][lr]->Fill(PLA_T[3][lr]);
    for(int lr=0;lr<2;lr++)hraw_PLA_T1[1][lr]->Fill(PLA_T[5][lr]);
    for(int lr=0;lr<2;lr++)hraw_PLA_T1[2][lr]->Fill(PLA_T[7][lr]);
    hraw_TOF[0]->Fill(TOF35);
    hraw_TOF[1]->Fill(TOF57);
    hraw_TOF[2]->Fill(TOF37);
    //===== PLA-QTC ==========
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n   ,PLA_QTC[ 3][n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+ 2,PLA_QTC[ 5][n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+ 4,PLA_QTC[ 7][n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+ 6,PLA_QTC[ 8][n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+ 8,PLA_QTC[ 9][n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+10,PLA_QTC[11][n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+12,F8VETO_QTC[n]);
    for(int n=0;n<2;n++)hraw_PLA_QTC->Fill(n+14,F11Long_QTC[n]);
    //===== PLA-Qraw ==========
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n   ,PLA_Qraw[ 3][n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+ 2,PLA_Qraw[ 5][n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+ 4,PLA_Qraw[ 7][n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+ 6,PLA_Qraw[ 8][n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+ 8,PLA_Qraw[ 9][n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+10,PLA_Qraw[11][n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+12,F8VETO_Qraw[n]);
    for(int n=0;n<2;n++)hraw_PLA_Qraw->Fill(n+14,F11Long_Qraw[n]);
    for(int n=0;n<3;n++)hraw_PLA_Qraw2[n]->Fill(PLA_Qraw[2*n+3][0], PLA_Qraw[2*n+3][1]);
    //===== Pla_Mhit =========
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n   ,PLA_Mhit[ 3][n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+ 2,PLA_Mhit[ 5][n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+ 4,PLA_Mhit[ 7][n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+ 6,PLA_Mhit[ 8][n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+ 8,PLA_Mhit[ 9][n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+10,PLA_Mhit[11][n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+12,F8VETO_Mhit[n]);
    for(int n=0;n<2;n++)hraw_PLA_Mhit->Fill(n+14,F11Long_Mhit[n]);
    //===== IC-Eraw ==========
    for(int n=0;n<6;n++)hraw_IC_Eraw[0]->Fill(n, F7IC_Eraw[n]);
    for(int n=0;n<3;n++)hraw_IC_Eraw[1]->Fill(n, F8IC_Eraw[n]);
    for(int n=0;n<6;n++)hraw_IC_Eraw[2]->Fill(n,F11IC_Eraw[n]);
    for(int n=0;n<6;n++)hraw_IC_Eraw[3]->Fill(n, F3IC_Eraw[n]);
    hraw_IC_Esum[0]->Fill(F3IC_Eraw[0]+F3IC_Eraw[1]+F3IC_Eraw[2]+F3IC_Eraw[3]+F3IC_Eraw[4]+F3IC_Eraw[5]); 
    hraw_IC_Esum[1]->Fill(F7IC_Eraw[0]+F7IC_Eraw[1]+F7IC_Eraw[2]+F7IC_Eraw[3]+F7IC_Eraw[4]+F7IC_Eraw[5]);
    //===== PID raw ==========
    hraw_PID[0]->Fill(TOF35, F3IC_Eraw[0]+F3IC_Eraw[1]+F3IC_Eraw[2]+F3IC_Eraw[3]+F3IC_Eraw[4]+F3IC_Eraw[5]);
    hraw_PID[1]->Fill(TOF57, F7IC_Eraw[0]+F7IC_Eraw[1]+F7IC_Eraw[2]+F7IC_Eraw[3]+F7IC_Eraw[5]);
    hraw_PID[2]->Fill(TOF37, F7IC_Eraw[0]+F7IC_Eraw[1]+F7IC_Eraw[2]+F7IC_Eraw[3]+F7IC_Eraw[5]);
    //===== PID calib ========
    hcalib_PID[0]->Fill(AoQ35[0], Zet3);
    hcalib_PID[1]->Fill(AoQ57[0], Zet7);
    hcalib_PID[2]->Fill(AoQ37, Zet7);
    //===== PID calib #2 ========
    hcalib_PID2[0]->Fill(AoQ35[1], Zet3);
    hcalib_PID2[1]->Fill(AoQ57[1], Zet7);
    hcalib_PID2[2]->Fill(AoQ37, Zet7);
 
    //===== Ge-Eraw ==========
    for(int n=0;n<32;n++)hraw_Ge_Eraw[0]->Fill(n, F7Ge_Eraw[n]);
    for(int n=0;n<32;n++)hraw_Ge_Eraw[1]->Fill(n, F7Ge2_Eraw[n]);

    if(PLA_Mhit[7][0]==2){
      hcalib_pileup_IC[0]->Fill((PLA_MT[7][0][1]-PLA_MT[7][0][0])*0.001,F7IC_Esum );
      hcalib_pileup_IC[1]->Fill((PLA_MT[7][0][1]-PLA_MT[7][0][0])*0.001,F8IC_Esum );
      hcalib_pileup_IC[2]->Fill((PLA_MT[7][0][1]-PLA_MT[7][0][0])*0.001,F11IC_Esum);
    }

    //===== Calibratied information ===============================================================
    //===== PPAC Tsum ===========================
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m   ,PPAC_Tsum[ 3][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m+ 4,PPAC_Tsum[ 5][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m+ 8,PPAC_Tsum[ 7][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m+12,PPAC_Tsum[ 8][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m+16,PPAC_Tsum[ 9][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m+20,PPAC_Tsum[10][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX->Fill(m+24,PPAC_Tsum[11][m][0]);

    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m   ,PPAC_Tsum[ 3][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m+ 4,PPAC_Tsum[ 5][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m+ 8,PPAC_Tsum[ 7][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m+12,PPAC_Tsum[ 8][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m+16,PPAC_Tsum[ 9][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m+20,PPAC_Tsum[10][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY->Fill(m+24,PPAC_Tsum[11][m][1]);

    /*
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[0]->Fill(m,PPAC_Tsum[3][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[1]->Fill(m,PPAC_Tsum[5][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[2]->Fill(m,PPAC_Tsum[7][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[3]->Fill(m,PPAC_Tsum[8][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[4]->Fill(m,PPAC_Tsum[9][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[5]->Fill(m,PPAC_Tsum[10][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumX[6]->Fill(m,PPAC_Tsum[11][m][0]);

    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[0]->Fill(m,PPAC_Tsum[3][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[1]->Fill(m,PPAC_Tsum[5][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[2]->Fill(m,PPAC_Tsum[7][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[3]->Fill(m,PPAC_Tsum[8][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[4]->Fill(m,PPAC_Tsum[9][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[5]->Fill(m,PPAC_Tsum[10][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TsumY[6]->Fill(m,PPAC_Tsum[11][m][1]);
    */
    /*
    //===== PPAC Tdiff ===============
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[0]->Fill(m,PPAC_Tdiff[3][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[1]->Fill(m,PPAC_Tdiff[5][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[2]->Fill(m,PPAC_Tdiff[7][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[3]->Fill(m,PPAC_Tdiff[8][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[4]->Fill(m,PPAC_Tdiff[9][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[5]->Fill(m,PPAC_Tdiff[10][m][0]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffX[6]->Fill(m,PPAC_Tdiff[11][m][0]);

    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[0]->Fill(m,PPAC_Tdiff[3][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[1]->Fill(m,PPAC_Tdiff[5][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[2]->Fill(m,PPAC_Tdiff[7][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[3]->Fill(m,PPAC_Tdiff[8][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[4]->Fill(m,PPAC_Tdiff[9][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[5]->Fill(m,PPAC_Tdiff[10][m][1]);
    for(int m=0;m<4;m++)hcalib_PPAC_TdiffY[6]->Fill(m,PPAC_Tdiff[11][m][1]);
    */

    for(int m=0;m<4;m++)if(fX[ 3][m]&&fY[ 3][m])hcalib_PPAC_Pos[0][m]->Fill(X[ 3][m],Y[ 3][m]);
    for(int m=0;m<4;m++)if(fX[ 5][m]&&fY[ 5][m])hcalib_PPAC_Pos[1][m]->Fill(X[ 5][m],Y[ 5][m]);
    for(int m=0;m<4;m++)if(fX[ 7][m]&&fY[ 7][m])hcalib_PPAC_Pos[2][m]->Fill(X[ 7][m],Y[ 7][m]);
    for(int m=0;m<4;m++)if(fX[ 8][m]&&fY[ 8][m])hcalib_PPAC_Pos[3][m]->Fill(X[ 8][m],Y[ 8][m]);
    for(int m=0;m<4;m++)if(fX[ 9][m]&&fY[ 9][m])hcalib_PPAC_Pos[4][m]->Fill(X[ 9][m],Y[ 9][m]);
    for(int m=0;m<4;m++)if(fX[10][m]&&fY[10][m])hcalib_PPAC_Pos[5][m]->Fill(X[10][m],Y[10][m]);
    for(int m=0;m<4;m++)if(fX[11][m]&&fY[11][m])hcalib_PPAC_Pos[6][m]->Fill(X[11][m],Y[11][m]);

    hcalib_Fpl_XY[0]->Fill(Fpl_XP[ 3],Fpl_YP[ 3]);
    hcalib_Fpl_XY[1]->Fill(Fpl_XP[ 5],Fpl_YP[ 5]);
    hcalib_Fpl_XY[2]->Fill(Fpl_XP[ 7],Fpl_YP[ 7]);
    hcalib_Fpl_XY[3]->Fill(Fpl_XP[ 8],Fpl_YP[ 8]);
    hcalib_Fpl_XY[4]->Fill(Fpl_XP[ 9],Fpl_YP[ 9]);
    hcalib_Fpl_XY[5]->Fill(Fpl_XP[10],Fpl_YP[10]);
    hcalib_Fpl_XY[6]->Fill(Fpl_XP[11],Fpl_YP[11]);

    hcalib_Fpl_XA[0]->Fill(Fpl_XP[ 3],Fpl_XT[ 3]);
    hcalib_Fpl_XA[1]->Fill(Fpl_XP[ 5],Fpl_XT[ 5]);
    hcalib_Fpl_XA[2]->Fill(Fpl_XP[ 7],Fpl_XT[ 7]);
    hcalib_Fpl_XA[3]->Fill(Fpl_XP[ 8],Fpl_XT[ 8]);
    hcalib_Fpl_XA[4]->Fill(Fpl_XP[ 9],Fpl_XT[ 9]);
    hcalib_Fpl_XA[5]->Fill(Fpl_XP[10],Fpl_XT[10]);
    hcalib_Fpl_XA[6]->Fill(Fpl_XP[11],Fpl_XT[11]);

    hcalib_Fpl_YB[0]->Fill(Fpl_YP[ 3],Fpl_YT[ 3]);
    hcalib_Fpl_YB[1]->Fill(Fpl_YP[ 5],Fpl_YT[ 5]);
    hcalib_Fpl_YB[2]->Fill(Fpl_YP[ 7],Fpl_YT[ 7]);
    hcalib_Fpl_YB[3]->Fill(Fpl_YP[ 8],Fpl_YT[ 8]);
    hcalib_Fpl_YB[4]->Fill(Fpl_YP[ 9],Fpl_YT[ 9]);
    hcalib_Fpl_YB[5]->Fill(Fpl_YP[10],Fpl_YT[10]);
    hcalib_Fpl_YB[6]->Fill(Fpl_YP[11],Fpl_YT[11]);

    //===== PLA-T ==========
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n   ,PLA_T[ 3][n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+ 2,PLA_T[ 5][n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+ 4,PLA_T[ 7][n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+ 6,PLA_T[ 8][n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+ 8,PLA_T[ 9][n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+10,PLA_T[11][n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+12,F8VETO_T[n]);
    for(int n=0;n<2;n++)hcalib_PLA_T->Fill(n+14,F11Long_T[n]);

    hcalib_PLA_LRQ[0]->Fill(PLA_Qraw[ 3][0],PLA_Qraw[ 3][1]);
    hcalib_PLA_LRQ[1]->Fill(PLA_Qraw[ 5][0],PLA_Qraw[ 5][1]);
    hcalib_PLA_LRQ[2]->Fill(PLA_Qraw[ 7][0],PLA_Qraw[ 7][1]);
    hcalib_PLA_LRQ[3]->Fill(PLA_Qraw[ 8][0],PLA_Qraw[ 8][1]);
    hcalib_PLA_LRQ[4]->Fill(PLA_Qraw[ 9][0],PLA_Qraw[ 9][1]);
    hcalib_PLA_LRQ[5]->Fill(PLA_Qraw[11][0],PLA_Qraw[11][1]);
    hcalib_PLA_LRQ[6]->Fill(F8VETO_Qraw[0], F8VETO_Qraw[1] );
    hcalib_PLA_LRQ[7]->Fill(F11Long_Qraw[0],F11Long_Qraw[1]);

    hcalib_PLA_LRQTC[0]->Fill(PLA_QTC[ 3][0],PLA_QTC[ 3][1]);
    hcalib_PLA_LRQTC[1]->Fill(PLA_QTC[ 5][0],PLA_QTC[ 5][1]);
    hcalib_PLA_LRQTC[2]->Fill(PLA_QTC[ 7][0],PLA_QTC[ 7][1]);
    hcalib_PLA_LRQTC[3]->Fill(PLA_QTC[ 8][0],PLA_QTC[ 8][1]);
    hcalib_PLA_LRQTC[4]->Fill(PLA_QTC[ 9][0],PLA_QTC[ 9][1]);
    hcalib_PLA_LRQTC[5]->Fill(PLA_QTC[11][0],PLA_QTC[11][1]);
    hcalib_PLA_LRQTC[6]->Fill(F8VETO_QTC[0], F8VETO_QTC[1] );
    hcalib_PLA_LRQTC[7]->Fill(F11Long_QTC[0],F11Long_QTC[1]);

    hcalib_PLA_Qdiff_Pos[0]->Fill(Fpl_XP[ 3],PLA_Qdiff[ 3]);
    hcalib_PLA_Qdiff_Pos[1]->Fill(Fpl_XP[ 5],PLA_Qdiff[ 5]);
    hcalib_PLA_Qdiff_Pos[2]->Fill(Fpl_XP[ 7],PLA_Qdiff[ 7]);
    hcalib_PLA_Qdiff_Pos[3]->Fill(Fpl_XP[ 8],PLA_Qdiff[ 8]);
    hcalib_PLA_Qdiff_Pos[4]->Fill(Fpl_XP[ 9],PLA_Qdiff[ 9]);
    hcalib_PLA_Qdiff_Pos[5]->Fill(Fpl_XP[11],PLA_Qdiff[11]);
    hcalib_PLA_Qdiff_Pos[6]->Fill(Fpl_XP[ 8], F8VETO_Qdiff);
    hcalib_PLA_Qdiff_Pos[7]->Fill(Fpl_XP[11],F11Long_Qdiff);

    //    }

    //    if(tgate[50]){
    //    if(abs(Zet7-20)<0.3 && abs(Zet8-20)<0.3 && 800<PLA_Qave[11][1]<1200){
    //    if(abs(Zet7-20)<0.3 && F8IC_Esum>70 && 800<PLA_Qave[11][1]<1500){
    //    if(55<F7IC_Esum&&F7IC_Esum<75 && 150<F8IC_Esum&&F8IC_Esum<220 && 800<PLA_Qave[11][1]<1500){
    //  52Catune
    //    if(55<F7IC_Esum&&F7IC_Esum<75 && 150<F8IC_Esum&&F8IC_Esum<220){
    // 55Catune
    if(52<F7IC_Esum&&F7IC_Esum<57 && 140<F8IC_Esum&&F8IC_Esum<152&&6000<F11IC_Esum&&F11IC_Esum<6600){
      for(int m=0;m<4;m++)hcalib_PPAC_fX[0]->Fill(m,fX[ 3][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fX[1]->Fill(m,fX[ 5][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fX[2]->Fill(m,fX[ 7][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fX[3]->Fill(m,fX[ 8][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fX[4]->Fill(m,fX[ 9][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fX[5]->Fill(m,fX[10][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fX[6]->Fill(m,fX[11][m]);

      for(int m=0;m<4;m++)hcalib_PPAC_fY[0]->Fill(m,fY[ 3][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fY[1]->Fill(m,fY[ 5][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fY[2]->Fill(m,fY[ 7][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fY[3]->Fill(m,fY[ 8][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fY[4]->Fill(m,fY[ 9][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fY[5]->Fill(m,fY[10][m]);
      for(int m=0;m<4;m++)hcalib_PPAC_fY[6]->Fill(m,fY[11][m]);
    }

    // PPAC eff against MUSIC_Esum
    hcalib_PPAC_eff2D0[0]->Fill(F7IC_Esum);
    hcalib_PPAC_eff2D0[1]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fX[ 3][m])hcalib_PPAC_eff2D[0][0][m]->Fill( F7IC_Esum);
    for(int m=0;m<4;m++)if(fX[ 5][m])hcalib_PPAC_eff2D[1][0][m]->Fill( F7IC_Esum);
    for(int m=0;m<4;m++)if(fX[ 7][m])hcalib_PPAC_eff2D[2][0][m]->Fill( F7IC_Esum);
    for(int m=0;m<4;m++)if(fX[ 8][m])hcalib_PPAC_eff2D[3][0][m]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fX[ 9][m])hcalib_PPAC_eff2D[4][0][m]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fX[10][m])hcalib_PPAC_eff2D[5][0][m]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fX[11][m])hcalib_PPAC_eff2D[6][0][m]->Fill(F11IC_Esum);

    for(int m=0;m<4;m++)if(fY[ 3][m])hcalib_PPAC_eff2D[0][1][m]->Fill( F7IC_Esum);
    for(int m=0;m<4;m++)if(fY[ 5][m])hcalib_PPAC_eff2D[1][1][m]->Fill( F7IC_Esum);
    for(int m=0;m<4;m++)if(fY[ 7][m])hcalib_PPAC_eff2D[2][1][m]->Fill( F7IC_Esum);
    for(int m=0;m<4;m++)if(fY[ 8][m])hcalib_PPAC_eff2D[3][1][m]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fY[ 9][m])hcalib_PPAC_eff2D[4][1][m]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fY[10][m])hcalib_PPAC_eff2D[5][1][m]->Fill(F11IC_Esum);
    for(int m=0;m<4;m++)if(fY[11][m])hcalib_PPAC_eff2D[6][1][m]->Fill(F11IC_Esum);

    if(tgate[4]){
      for(int mmm=0;mmm<4;mmm++)hana_PID35[mmm]->Fill(AoQ35_2,Zet3_2);
      for(int mmm=0;mmm<4;mmm++)hana_PID57[mmm]->Fill(AoQ57_2,Zet7_2);
      for(int mmm=0;mmm<4;mmm++)hana_PID37[mmm]->Fill(AoQ57[1],Zet7_2);

      hana_AoQ[0]->Fill(AoQ35_2);
      hana_AoQ[1]->Fill(AoQ57_2);
      hana_AoQ[2]->Fill(AoQ57[1]);

      hana_Zet[0]->Fill(Zet3);
      hana_Zet[1]->Fill(Zet7);
      hana_Zet[2]->Fill(Zet8);
      hana_Zet[3]->Fill(Zet11);
    }
     
    if(tgate[ 4])hana_PID[0][0]->Fill(AoQ57[1] ,Zet7);
    if(tgate[10])hana_PID[0][1]->Fill(AoQ57[1] ,Zet7);
    if(tgate[10])hana_PID[1][0]->Fill(AoQ911[1],Zet11);
    if(tgate[20])hana_PID[1][1]->Fill(AoQ911[1],Zet11);
    
    if(tgate[40]){
      if(tgate[ 4])hana_PID2[0][0]->Fill(AoQ57[1] ,Zet7);
      if(tgate[10])hana_PID2[0][1]->Fill(AoQ57[1] ,Zet7);
      if(tgate[10])hana_PID2[1][0]->Fill(AoQ911[1],Zet11);
      if(tgate[20])hana_PID2[1][1]->Fill(AoQ911[1],Zet11);
    }
    
    if(tgate[10])hana_F7QF8Q->Fill(PLA_Qave[7][0],PLA_Qave[8][0]);
    
    if(tgate[10]){
      hana_profile1[0]->Fill(Fpl_XP[ 3],Fpl_YP[ 3]);
      hana_profile1[1]->Fill(Fpl_XP[ 5],Fpl_YP[ 5]);
      hana_profile1[2]->Fill(Fpl_XP[ 7],Fpl_YP[ 7]);
      hana_profile1[3]->Fill(Fpl_XP[ 8],Fpl_YP[ 8]);
      hana_profile1[4]->Fill(Fpl_XP[ 9],Fpl_YP[ 9]);
      hana_profile1[5]->Fill(Fpl_XP[10],Fpl_YP[10]);
      hana_profile1[6]->Fill(Fpl_XP[11],Fpl_YP[11]);

      hana_profile2[0]->Fill(Fpl_XP[ 3],Fpl_XT[ 3]);
      hana_profile2[1]->Fill(Fpl_XP[ 5],Fpl_XT[ 5]);
      hana_profile2[2]->Fill(Fpl_XP[ 7],Fpl_XT[ 7]);
      hana_profile2[3]->Fill(Fpl_XP[ 8],Fpl_XT[ 8]);
      hana_profile2[4]->Fill(Fpl_XP[ 9],Fpl_XT[ 9]);
      hana_profile2[5]->Fill(Fpl_XP[10],Fpl_XT[10]);
      hana_profile2[6]->Fill(Fpl_XP[11],Fpl_XT[11]);

      hana_profile3[0]->Fill(Fpl_YP[ 3],Fpl_YT[ 3]);
      hana_profile3[1]->Fill(Fpl_YP[ 5],Fpl_YT[ 5]);
      hana_profile3[2]->Fill(Fpl_YP[ 7],Fpl_YT[ 7]);
      hana_profile3[3]->Fill(Fpl_YP[ 8],Fpl_YT[ 8]);
      hana_profile3[4]->Fill(Fpl_YP[ 9],Fpl_YT[ 9]);
      hana_profile3[5]->Fill(Fpl_YP[10],Fpl_YT[10]);
      hana_profile3[6]->Fill(Fpl_YP[11],Fpl_YT[11]);
    }

    if(tgate[10]){
      Double_t temp_fillemt;
      
      for(int i=0;i<5;i++){

	switch(i){
	case 0:temp_fillemt = Fpl_XP[8];break;
	case 1:temp_fillemt = Fpl_XT[8];break;
	case 2:temp_fillemt = Fpl_YP[8];break;
	case 3:temp_fillemt = Fpl_YT[8];break;
	case 4:temp_fillemt = Delta57  ;break;
	}

	hana_emt[0][0][i]->Fill(temp_fillemt);
	if(tgate[20])hana_emt[0][1][i]->Fill(temp_fillemt);
	if(tgate[41+i])hana_emt[1][0][i]->Fill(temp_fillemt);	
	if(tgate[41+i]&&tgate[20])hana_emt[1][1][i]->Fill(temp_fillemt);
	if(tgate[40])hana_emt[2][0][i]->Fill(temp_fillemt);	
	if(tgate[40]&&tgate[20])hana_emt[2][1][i]->Fill(temp_fillemt);	
      }
    }
    

    //====================
    if(tree_output)Ndatabyte = tree->Fill();  
    if(neve==0)cout << Form("1-event data size | %5d bytes",Ndatabyte) << endl;
    neve++;
    if(neve > loadEvt)break;

    //    if(Nevent%500==0){
    if(neve%10000==0){
      TDatime *T1=new TDatime();
      int t1[3];  
      t1[0]= T1->GetHour();t1[1]= T1->GetMinute();t1[2]= T1->GetSecond();
      int time = (t1[0]-t0[0])*3600+(t1[1]-t0[1])*60+(t1[2]-t0[2]);
      double rate = neve/(double)time;

      cout << setprecision(0) 
	//	   << setw(10) << Nevent <<" events; " 
	   << setw(10) << neve <<" events; " 
	   << setw(6) << time << " s; " 
	   << setw(6) << rate << " cps" << endl;
	   //<< flush << "\r";
    }

  } // End of event loop

  TDatime *T1=new TDatime();
  int t1[3];
  t1[0]= T1->GetHour();t1[1]= T1->GetMinute();t1[2]= T1->GetSecond();
  int time = (t1[0]-t0[0])*3600+(t1[1]-t0[1])*60+(t1[2]-t0[2]);
  //  double rate = Nevent/(double)time;
  double rate = neve/(double)time;

  cout << setprecision(0) 
    //       << setw(10) << Nevent <<" events; " 
       << setw(10) << neve <<" events; " 
       << setw(6) << time << " s; " 
       << setw(6) << rate << " cps"
       << endl;

  //===== Efficiency of PPAC against IC_Esum ====
  hcalib_PPAC_eff2D0[0]->Sumw2();
  hcalib_PPAC_eff2D0[1]->Sumw2();
  for(int ii=0;ii<7;ii++)for(int jj=0;jj<2;jj++)for(int kk=0;kk<4;kk++)hcalib_PPAC_eff2D[ii][jj][kk]->Sumw2();

  TH1D *hcalib_PPAC_eff2D_div[7][2][4];
  for(int ii=0;ii<7;ii++)for(int jj=0;jj<2;jj++)for(int kk=0;kk<4;kk++){
	hcalib_PPAC_eff2D_div[ii][jj][kk] = 
	  (TH1D*)hcalib_PPAC_eff2D[ii][jj][kk]->Clone(Form("hcalib_eff2D_%sPPAC_%s_%s_div",tlabel_eff2D1[ii].c_str(),tlabel_eff2D3[kk].c_str(),tlabel_eff2D2[jj].c_str()));
      }

  // X
  for(int ii=0;ii<3;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D_div[ii][0][kk]->Divide(hcalib_PPAC_eff2D0[0]);
    }
  // X
  for(int ii=3;ii<7;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D_div[ii][0][kk]->Divide(hcalib_PPAC_eff2D0[1]);
    }
  // Y
  for(int ii=0;ii<3;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D_div[ii][1][kk]->Divide(hcalib_PPAC_eff2D0[0]);
    }
  // Y
  for(int ii=3;ii<7;ii++)for(int kk=0;kk<4;kk++){
      hcalib_PPAC_eff2D_div[ii][1][kk]->Divide(hcalib_PPAC_eff2D0[1]);
    }

  for(int ii=0;ii<7;ii++)for(int jj=0;jj<2;jj++)for(int kk=0;kk<4;kk++){
	hcalib_PPAC_eff2D_div[ii][jj][kk]->SetFillColor(0);
	hcalib_PPAC_eff2D_div[ii][jj][kk]->SetAxisRange(0,1.1,"Y");
      }

  //===== Efficiency of PPAC ====================
  for(int i=0;i<2;i++)cout << endl;
  cout << "PPAC efficiency" << endl;
  // Ncount_PPAC[i][j][k][0] : not fired;
  // Ncount_PPAC[i][j][k][1] : all;
  Int_t Ncount_PPAC[7][2][4][2]={};
  for(int i=0;i<7;i++)for(int j=0;j<4;j++){
      Ncount_PPAC[i][0][j][0] = hcalib_PPAC_fX[i]->GetBinContent(1+j,1);
      Ncount_PPAC[i][0][j][1] = hcalib_PPAC_fX[i]->GetBinContent(1+j,2);
      Ncount_PPAC[i][0][j][1] += Ncount_PPAC[i][0][j][0];
      
      Ncount_PPAC[i][1][j][0] = hcalib_PPAC_fY[i]->GetBinContent(1+j,1);
      Ncount_PPAC[i][1][j][1] = hcalib_PPAC_fY[i]->GetBinContent(1+j,2);
      Ncount_PPAC[i][1][j][1] += Ncount_PPAC[i][0][j][0];
    }
  

  string tppacname[7]={"F03","F05","F07","F08","F09","F10","F11"};
  string tppacname2[4]={"1A","1B","2A","2B"};

  for(int i=0;i<7;i++){
    cout << "===== " << tppacname[i].c_str() << " =====================================" << endl;
    Double_t temp_eff[4][2]={};
    Double_t temp_err[4][2]={};
    Double_t temp_eff2[2][2]={};
    Double_t temp_err2[2][2]={};
    Double_t temp_eff3[2]={};
    Double_t temp_err3[2]={};

    for(int j=0;j<4;j++){

      for(int k=0;k<2;k++){
	temp_eff[j][k] = (Double_t)Ncount_PPAC[i][k][j][0] / Ncount_PPAC[i][k][j][1];
	temp_err[j][k] = sqrt( temp_eff[j][k] * (1.-temp_eff[j][k]) / Ncount_PPAC[i][k][j][1]);
	temp_eff[j][k] = (1. - temp_eff[j][k]);
      }

      cout << tppacname2[j].c_str() << "     " 
	   << Form("X: %6.2f +- %4.2f",100.*temp_eff[j][0],100.*temp_err[j][0]) << "%   "
	   << Form("Y: %6.2f +- %4.2f",100.*temp_eff[j][1],100.*temp_err[j][1]) << "%" << endl;
    }

    cout << endl;cout << "OR efficiency" << endl;

    for(int j=0;j<2;j++){

      for(int k=0;k<2;k++){
	temp_eff2[j][k] = 1.0 - (1.0-temp_eff[2*j][k]) * (1.0-temp_eff[2*j+1][k]);
	temp_err2[j][k] = sqrt( pow((1-temp_eff[2*j+1][k])*temp_err[2*j][k],2.) + pow((1-temp_eff[2*j][k])*temp_err[2*j+1][k],2.) );
      }
    
      cout << Form("PPAC%d",j+1) << "  " 
	   << Form("X: %6.2f +- %4.2f",100.*temp_eff2[j][0],100.*temp_err2[j][0]) << "%   "
	   << Form("Y: %6.2f +- %4.2f",100.*temp_eff2[j][1],100.*temp_err2[j][1]) << "%" << endl;
    }

    cout << endl;cout << "Tracking efficiency" << endl;

    for(int k=0;k<2;k++){
      temp_eff3[k] = temp_eff2[0][k] * temp_eff2[1][k];
      temp_err3[k] = sqrt( pow(temp_eff2[1][k]*temp_err2[0][k],2.) + pow(temp_eff2[0][k]*temp_err2[1][k],2.) );
    }
    
    cout << "       " 
	 << Form("X: %6.2f +- %4.2f",100.*temp_eff3[0],100.*temp_err3[0]) << "%   "
	 << Form("Y: %6.2f +- %4.2f",100.*temp_eff3[1],100.*temp_err3[1]) << "%" << endl;
    
  }
  cout << "==============================================" << endl;



#ifndef PLOT_FLAG

  TGraphErrors *gr_trans[3][5];
  string lab_gr1[5]={"X","A","Y","B","D"};
  string lab_gr2[5]={"mm","mrad","mm","mrad","%"};
  string lab_gr3[3]={"Nocut","4cut","EMTcut"}; 
  for(int i=0;i<3;i++)for(int j=0;j<5;j++){
      gr_trans[i][j] = new TGraphErrors();
      MakeTransPlot1D(hana_emt[i][0][j],hana_emt[i][1][j],gr_trans[i][j]);
      gr_trans[i][j]->SetName(Form("Gr_Trans_%s_%s",lab_gr1[j].c_str(),lab_gr3[i].c_str()));
      gr_trans[i][j]->SetTitle(Form("Transmission %s (%s);%s (%s);Transmission",lab_gr1[j].c_str(),lab_gr3[i].c_str(),lab_gr1[j].c_str(),lab_gr2[j].c_str()));
      gr_trans[i][j]->SetMinimum(0.6);gr_trans[i][j]->SetMaximum(1.1);
  }

  for(int j=0;j<5;j++){
    gr_trans[0][j]->SetMarkerStyle(24);gr_trans[0][j]->SetMarkerColor(1);gr_trans[0][j]->SetLineColor(1);
    gr_trans[1][j]->SetMarkerStyle(24);gr_trans[1][j]->SetMarkerColor(2);gr_trans[1][j]->SetLineColor(2);
    gr_trans[2][j]->SetMarkerStyle(20);gr_trans[2][j]->SetMarkerColor(2);gr_trans[2][j]->SetLineColor(2);

    hana_emt[0][0][j]->SetFillColor(0);hana_emt[0][0][j]->SetLineColor(1);
    hana_emt[1][0][j]->SetFillColor(0);hana_emt[1][0][j]->SetLineColor(2);
    hana_emt[2][0][j]->SetFillColor(2);hana_emt[2][0][j]->SetLineColor(2);
    hana_emt[0][0][j]->SetTitle(lab_gr1[j].c_str());
  }

  TLegend *legend = new TLegend(0.65,0.70,0.83,0.83);
  legend->AddEntry(hana_emt[0][0][0],"No cut"  ,"l");
  legend->AddEntry(hana_emt[1][0][0],"4 cut"   ,"l");
  legend->AddEntry(hana_emt[2][0][0],"Full cut","f");
  legend->SetFillColor(0);
  //  TCanvas *ctrans = new TCanvas("canvas_trans","canvas_trans",1400,1400*0.7);
  TCanvas *ctrans = new TCanvas("canvas_trans","canvas_trans",1200,1200*0.7);
  ctrans->Divide(5,2);
  for(int j=0;j<5;j++){
    ctrans->cd(j+1);
    gr_trans[1][j]->Draw("APE");gr_trans[2][j]->Draw("PE");
  }
  for(int j=0;j<5;j++){
    ctrans->cd(5+j+1);
    hana_emt[0][0][j]->Draw();hana_emt[1][0][j]->Draw("same");hana_emt[2][0][j]->Draw("same");
    hana_emt[0][0][j]->SetStats(0);
    legend->Draw();
  }

  ctrans->Modified();
  ctrans->Update();
  ctrans->Print(Form("ps/transmission/png/%s%04d.png",runname.Data(),runN));
  ctrans->Print(Form("ps/transmission/pdf/%s%04d.pdf",runname.Data(),runN));
#endif  

  // ====== PPAC canvas =====================================================
  TCanvas *cPPAC = new TCanvas("cPPAC","cPPAC",1200,1200*0.7);
  cPPAC->Divide(3, 3);
  for(int j=0;j<3;j++){
    cPPAC->cd(j+1); hcalib_Fpl_XY[j]->Draw("colz");
    cPPAC->cd(j+4); hcalib_Fpl_XA[j]->Draw("colz");
    cPPAC->cd(j+7); hcalib_Fpl_YB[j]->Draw("colz");
  }
  cPPAC->Modified();
  cPPAC->Update();
  cPPAC->Write();

  // ====== IC canvas =======================================================
  TCanvas *cMUSIC = new TCanvas("cMUSIC","cMUSIC",1200,1200*0.7);
  cMUSIC->Divide(2, 1);
  for (int ii = 0; ii < 2; ii++) {
    cMUSIC->cd(ii + 1); hraw_IC_Esum[ii]->Draw("");
  }
  cMUSIC->Modified();
  cMUSIC->Update();
  cMUSIC->Write();

  // ====== PLA canvas ======================================================
  TCanvas *cPLA = new TCanvas("cPLA","cPLA",1200,1200*0.7);
  cPLA->Divide(3, 3);
  for(int j=0;j<3;j++) {cPLA->cd(j+1); hraw_PLA_T1[j][0]->Draw("colz");};
  for(int j=0;j<3;j++) {cPLA->cd(j+4); hraw_PLA_T1[j][1]->Draw("colz");};
  for(int j=0;j<3;j++) {cPLA->cd(j+7); hraw_PLA_Qraw2[j]->Draw("colz");};
  cPLA->Modified();
  cPLA->Update();
  cPLA->Write();

  // ====== TOF canvas ======================================================
  TCanvas *cTOF = new TCanvas("cTOF","cTOF",1200,1200*0.7);
  cTOF->Divide(1,3);
  cTOF->cd(1);hraw_TOF[0]->Draw("colz");
  cTOF->cd(2);hraw_TOF[1]->Draw("colz");
  cTOF->cd(3);hraw_TOF[2]->Draw("colz");
  cTOF->Modified();cTOF->Update();cTOF->Write();

  // ====== PIDraw canvas ===================================================
  TCanvas *cPIDraw = new TCanvas("cPIDraw","cPIDraw",1200,1200*0.7);
  cPIDraw->Divide(2,2);
  cPIDraw->cd(1);hraw_PID[0]->Draw("colz");
  cPIDraw->cd(2);hraw_PID[1]->Draw("colz");
  cPIDraw->cd(3);hraw_PID[2]->Draw("colz");
  cPIDraw->Modified();cPIDraw->Update();cPIDraw->Write();

  // ====== PIDcalib canvas ===================================================
  TCanvas *cPIDcalib = new TCanvas("cPIDcalib","cPIDcalib",1200,1200*0.7);
  cPIDcalib->Divide(2,2);
  cPIDcalib->cd(1);hcalib_PID[0]->Draw("colz");
  cPIDcalib->cd(2);hcalib_PID[1]->Draw("colz");
  cPIDcalib->cd(3);hcalib_PID[2]->Draw("colz");
  cPIDcalib->Modified();cPIDcalib->Update();cPIDcalib->Write();

  // ====== PIDcalib #2 canvas ===================================================
  TCanvas *cPIDcalib2 = new TCanvas("cPIDcalib2","cPIDcalib2",1200,1200*0.7);
  cPIDcalib2->Divide(2,2);
  cPIDcalib2->cd(1);hcalib_PID2[0]->Draw("colz");
  cPIDcalib2->cd(2);hcalib_PID2[1]->Draw("colz");
  cPIDcalib2->cd(3);hcalib_PID2[2]->Draw("colz");
  cPIDcalib2->Modified();cPIDcalib2->Update();cPIDcalib2->Write();

  if(file_output){

  /*
    //    TFile *fout = new TFile(ofname, "RECREATE");  

    // tree 
    tree->Write();

    // unpack
    for(int i=0;i<2;i++)hraw_v1190[i]->Write();
    for(int i=0;i<2;i++)hraw_v1190num[i]->Write();
    for(int i=0;i<2;i++)hraw_v1290L[i]->Write();
    for(int i=0;i<2;i++)hraw_v1290Lnum[i]->Write();
    for(int i=0;i<2;i++)hraw_v1290Lnum2[i]->Write();
    hraw_v1290T->Write();
    hraw_v1290W->Write();
    hraw_qdc->Write();
    for(int i=0;i<4;i++)hraw_adc[i]->Write();
    for(int i=0;i<7;i++)hraw_PPAC_v1190[i]->Write();
    for(int i=0;i<2;i++)hraw_PLA_v1290[i]->Write();
    for(int i=0;i<7;i++)hraw_PPAC_T[i]->Write();
    hraw_PLA_T->Write();
    hraw_PLA_QTC->Write();
    hraw_PLA_Qraw->Write();
    hraw_PLA_Mhit->Write();
    for(int i=0;i<3;i++)hraw_IC_Eraw[i]->Write();

    // calibrated
    hcalib_PPAC_TsumX->Write();
    hcalib_PPAC_TsumY->Write();
    for(int i=0;i<7;i++)for(int j=0;j<4;j++)hcalib_PPAC_Pos[i][j]->Write();
    for(int i=0;i<7;i++)hcalib_Fpl_XY[i]->Write();
    hcalib_PLA_T->Write();
    for(int i=0;i<7;i++)hcalib_PLA_LRQ[i]->Write();
    for(int i=0;i<7;i++)hcalib_PLA_LRQTC[i]->Write();
    for(int i=0;i<7;i++)hcalib_PLA_Qdiff_Pos[i]->Write();
    for(int i=0;i<3;i++)hcalib_PIDup[i]->Write();
    for(int i=0;i<3;i++)hcalib_PIDdown[i]->Write();
    for(int i=0;i<3;i++)hcalib_AoQup[i]->Write();
    for(int i=0;i<3;i++)hcalib_AoQdown[i]->Write();
    for(int i=0;i<4;i++)hcalib_Zet[i]->Write();
    for(int i=0;i<3;i++)hcalib_pileup_IC[i]->Write();
    for(int i=0;i<7;i++)hcalib_PPAC_fX[i]->Write();
    for(int i=0;i<7;i++)hcalib_PPAC_fY[i]->Write();

    // for analysis
    for(int i=0;i<2;i++)for(int j=0;j<2;j++)hana_PID[i][j]->Write();
    for(int i=0;i<3;i++)for(int j=0;j<2;j++)for(int k=0;k<5;k++)hana_emt[i][j][k]->Write();
    hana_F7QF8Q->Draw();
    for(int i=0;i<7;i++)hana_profile1[i]->Write();
    for(int i=0;i<7;i++)hana_profile2[i]->Write();
    for(int i=0;i<7;i++)hana_profile3[i]->Write();
  */

#ifndef PLOT_FLAG
    for(int i=0;i<3;i++)for(int k=0;k<5;k++)gr_trans[i][k]->Write();
    legend->Write();
    ctrans->Write();
#endif



    fout->Write();
    //    fout->Close();    
    //    if(runN!=9999)fout->Close();
    

    TDatime *T2=new TDatime();
    int t2[3];
    t2[0]= T2->GetHour();t2[1]= T2->GetMinute();t2[2]= T2->GetSecond();
    int time2 = (t2[0]-t0[0])*3600+(t2[1]-t0[1])*60+(t2[2]-t0[2]);
    //    double rate2 = Nevent/(double)time2;
    double rate2 = neve/(double)time2;
    
    cout << setprecision(0) 
      //	 << setw(10) << Nevent <<" events; " 
	 << setw(10) << neve <<" events; " 
	 << setw(6)  << time << " s to load data" << endl; 
    cout << setw(19) << "+" 
	 << setw(6) <<time2-time << " s to write in output file."
	 << endl;
    cout << endl;  
    cout << "Output file : " << ofname.Data() << endl;
  }
  
}
