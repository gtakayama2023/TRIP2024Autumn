void ribf_branch_raw(TTree *tree){

  tree->Branch("Nevent",&Nevent,"Nevent/I");
  tree->Branch("Brho_NMR",Brho_NMR,"Brho_NMR[8]/D");

  //===== time stemp =====
  tree->Branch("camac_ts0",camac_ts0,"camac_ts0[2][2]/l");
  tree->Branch("camac_ts",camac_ts,"camac_ts[2]/l");

  tree->Branch("ccnet08_data",ccnet08_data,"ccnet08_data[6]/I");
  //===== time stemp =====
  tree->Branch("mpv_Nevent",mpv_Nevent,"mpv_Nevent[1]/i");
  tree->Branch("mpv_ts0",mpv_ts0,"mpv_ts0[1][2]/l");
  tree->Branch("mpv_ts",mpv_ts,"mpv_ts[1]/l");
  tree->Branch("mpv_10kclock",mpv_10kclock,"mpv_10kclock[1]/i");

  //===== V1190 =====
  tree->Branch("v1190",v1190,Form("v1190[32][%d]/L",N_Mhit));
  tree->Branch("v1190raw",v1190raw,Form("v1190raw[32][%d]/L",N_Mhit));
  tree->Branch("v1190num",v1190num,"v1190num[32]/I");

  //===== PPAC =====
  tree->Branch("PPAC_Qraw",PPAC_Qraw,Form("PPAC_Qraw[%d][4][4]/I",Nfpl_PPAC));
  tree->Branch("PPAC_Traw",PPAC_Traw,Form("PPAC_Traw[%d][4][4]/I",Nfpl_PPAC));
  tree->Branch("PPAC_AQraw",PPAC_AQraw,Form("PPAC_AQraw[%d][4]/I",Nfpl_PPAC));
  tree->Branch("PPAC_ATraw",PPAC_ATraw,Form("PPAC_ATraw[%d][4]/I",Nfpl_PPAC));

  //===== PLA =====
  tree->Branch("PLA_Qraw",PLA_Qraw,Form("PLA_Qraw[%d][2]/I",Nfpl_PLA));
  tree->Branch("PLA_Traw",PLA_Traw,Form("PLA_Traw[%d][2]/I",Nfpl_PLA));
  //  tree->Branch("PLA2_Qraw",PLA2_Qraw,Form("PLA2_Qraw[%d][2]/I",Nfpl_PLA));
  //  tree->Branch("PLA2_Traw",PLA2_Traw,Form("PLA2_Traw[%d][2]/I",Nfpl_PLA));

  //===== F8VETO =====
  tree->Branch("F8VETO_Qraw",F8VETO_Qraw,"F8VETO_Qraw[2]/I");
  tree->Branch("F8VETO_Traw",F8VETO_Traw,"F8VETO_Traw[2]/I");

  //===== F11Long =====
  //  tree->Branch("F11Long_Qraw",F11Long_Qraw,"F11Long_Qraw[2]/I");
  //  tree->Branch("F11Long_Traw",F11Long_Traw,"F11Long_Traw[2]/I");

  //===== IC =====
  tree->Branch("F7IC_Eraw",F7IC_Eraw,"F7IC_Eraw[6]/I");
  tree->Branch("F8IC_Eraw",F8IC_Eraw,"F8IC_Eraw[3]/I");
  tree->Branch("F11IC_Eraw",F11IC_Eraw,"F11IC_Eraw[6]/I");
  tree->Branch("F7IC_Gas",&F7IC_Gas,"F7IC_Gas/I");
  tree->Branch("F8IC_Gas",&F8IC_Gas,"F8IC_Gas/I");
  tree->Branch("F11IC_Gas",&F11IC_Gas,"F11IC_Gas/I");

  //===== Mhit TDC ========
  tree->Branch("PLA_MT",PLA_MT,Form("PLA_MT[%d][2][%d]/D",Nfpl_PLA,N_Mhit));
  tree->Branch("PLA_Mhit",PLA_Mhit,Form("PLA_Mhit[%d][2]/I",Nfpl_PLA));
  tree->Branch("F8VETO_MT",F8VETO_MT,Form("F8VETO_MT[2][%d]/D",N_Mhit));
  tree->Branch("F8VETO_Mhit",F8VETO_Mhit,"F8VETO_Mhit[2]/I");
  tree->Branch("F8PPACA_MT",F8PPACA_MT,Form("F8PPACA_MT[4][%d]/D",N_Mhit));
  tree->Branch("F8PPACA_Mhit",F8PPACA_Mhit,"F8PPACA_Mhit[4]/I");
  
}


void ribf_branch_raw_read(TTree *tree2){

  tree2->SetBranchAddress("Nevent",&Nevent);
  tree2->SetBranchAddress("Brho_NMR",Brho_NMR);

  tree2->SetBranchAddress("camac_ts0",camac_ts0);
  tree2->SetBranchAddress("camac_ts",camac_ts);

  tree2->SetBranchAddress("mpv_Nevent",mpv_Nevent);
  tree2->SetBranchAddress("mpv_ts0",mpv_ts0);
  tree2->SetBranchAddress("mpv_ts",mpv_ts);
  tree2->SetBranchAddress("mpv_10kclock",mpv_10kclock);

  tree2->SetBranchAddress("v1190",v1190);
  tree2->SetBranchAddress("v1190raw",v1190raw);
  tree2->SetBranchAddress("v1190num",v1190num);

  tree2->SetBranchAddress("PPAC_Qraw",PPAC_Qraw);  
  tree2->SetBranchAddress("PPAC_Traw",PPAC_Traw);  
  tree2->SetBranchAddress("PPAC_AQraw",PPAC_AQraw);  
  tree2->SetBranchAddress("PPAC_ATraw",PPAC_ATraw);  
  
  tree2->SetBranchAddress("PLA_Qraw",PLA_Qraw);  
  tree2->SetBranchAddress("PLA_Traw",PLA_Traw);  
  //  tree2->SetBranchAddress("PLA2_Qraw",PLA2_Qraw);  
  //  tree2->SetBranchAddress("PLA2_Traw",PLA2_Traw);  

  tree2->SetBranchAddress("F8VETO_Qraw",F8VETO_Qraw);  
  tree2->SetBranchAddress("F8VETO_Traw",F8VETO_Traw);  

  //  tree2->SetBranchAddress("F11Long_Qraw",F11Long_Qraw);  
  //  tree2->SetBranchAddress("F11Long_Traw",F11Long_Traw);  

  tree2->SetBranchAddress("F7IC_Eraw",F7IC_Eraw);  
  tree2->SetBranchAddress("F8IC_Eraw",F8IC_Eraw);  
  tree2->SetBranchAddress("F11IC_Eraw",F11IC_Eraw);  
  tree2->SetBranchAddress("F7IC_Gas",&F7IC_Gas);
  tree2->SetBranchAddress("F8IC_Gas",&F8IC_Gas);
  tree2->SetBranchAddress("F11IC_Gas",&F11IC_Gas);

  tree2->SetBranchAddress("PLA_MT",PLA_MT);  
  tree2->SetBranchAddress("PLA_Mhit",PLA_Mhit);  
  tree2->SetBranchAddress("F8VETO_MT",F8VETO_MT);  
  tree2->SetBranchAddress("F8VETO_Mhit",F8VETO_Mhit);  
  tree2->SetBranchAddress("F8PPACA_MT",F8PPACA_MT);  
  tree2->SetBranchAddress("F8PPACA_Mhit",F8PPACA_Mhit);  

}


void ribf_branch(TTree *tree){
  //===== Raw data ==========================================

  tree->Branch("tgate",tgate,"tgate[100]/O");

  tree->Branch("Nevent",&Nevent,"Nevent/I");
  tree->Branch("Brho_NMR",Brho_NMR,"Brho_NMR[8]/D");

  //===== time stemp =====
  tree->Branch("camac_ts0",camac_ts0,"camac_ts0[2][2]/l");
  tree->Branch("camac_ts",camac_ts,"camac_ts[2]/l");

  tree->Branch("ccnet08_data",ccnet08_data,"ccnet08_data[6]/I");

  //===== time stemp =====
  tree->Branch("mpv_Nevent",mpv_Nevent,"mpv_Nevent[1]/i");
  tree->Branch("mpv_ts0",mpv_ts0,"mpv_ts0[1][2]/l");
  tree->Branch("mpv_ts",mpv_ts,"mpv_ts[1]/l");
  tree->Branch("mpv_10kclock",mpv_10kclock,"mpv_10kclock[1]/i");

  //===== V1190 =====
  tree->Branch("v1190",v1190,Form("v1190[32][%d]/L",N_Mhit));
  tree->Branch("v1190raw",v1190raw,Form("v1190raw[32][%d]/L",N_Mhit));
  tree->Branch("v1190num",v1190num,"v1190num[32]/I");

  //===== PPAC =====
  tree->Branch("PPAC_Qraw",PPAC_Qraw,Form("PPAC_Qraw[%d][4][4]/I",Nfpl_PPAC));
  tree->Branch("PPAC_Traw",PPAC_Traw,Form("PPAC_Traw[%d][4][4]/I",Nfpl_PPAC));
  tree->Branch("PPAC_AQraw",PPAC_AQraw,Form("PPAC_AQraw[%d][4]/I",Nfpl_PPAC));
  tree->Branch("PPAC_ATraw",PPAC_ATraw,Form("PPAC_ATraw[%d][4]/I",Nfpl_PPAC));

  //===== PLA =====
  tree->Branch("PLA_Qraw",PLA_Qraw,Form("PLA_Qraw[%d][2]/I",Nfpl_PLA));
  tree->Branch("PLA_Traw",PLA_Traw,Form("PLA_Traw[%d][2]/I",Nfpl_PLA));
  //  tree->Branch("PLA2_Qraw",PLA2_Qraw,Form("PLA2_Qraw[%d][2]/I",Nfpl_PLA));
  //  tree->Branch("PLA2_Traw",PLA2_Traw,Form("PLA2_Traw[%d][2]/I",Nfpl_PLA));

  //===== F8VETO =====
  tree->Branch("F8VETO_Qraw",F8VETO_Qraw,"F8VETO_Qraw[2]/I");
  tree->Branch("F8VETO_Traw",F8VETO_Traw,"F8VETO_Traw[2]/I");

  //===== F11Long =====
  //  tree->Branch("F11Long_Qraw",F11Long_Qraw,"F11Long_Qraw[2]/I");
  //  tree->Branch("F11Long_Traw",F11Long_Traw,"F11Long_Traw[2]/I");

  //===== IC =====
  tree->Branch("F7IC_Eraw",F7IC_Eraw,"F7IC_Eraw[6]/I");
  tree->Branch("F8IC_Eraw",F8IC_Eraw,"F8IC_Eraw[3]/I");
  tree->Branch("F11IC_Eraw",F11IC_Eraw,"F11IC_Eraw[6]/I");
  tree->Branch("F7IC_Gas",&F7IC_Gas,"F7IC_Gas/I");
  tree->Branch("F8IC_Gas",&F8IC_Gas,"F8IC_Gas/I");
  tree->Branch("F11IC_Gas",&F11IC_Gas,"F11IC_Gas/I");

  //===== Mhit TDC ========
  tree->Branch("PLA_MT",PLA_MT,Form("PLA_MT[%d][2][%d]/D",Nfpl_PLA,N_Mhit));
  tree->Branch("PLA_Mhit",PLA_Mhit,Form("PLA_Mhit[%d][2]/I",Nfpl_PLA));
  tree->Branch("F8VETO_MT",F8VETO_MT,Form("F8VETO_MT[2][%d]/D",N_Mhit));
  tree->Branch("F8VETO_Mhit",F8VETO_Mhit,"F8VETO_Mhit[2]/I");
  tree->Branch("F8PPACA_MT",F8PPACA_MT,Form("F8PPACA_MT[4][%d]/D",N_Mhit));
  tree->Branch("F8PPACA_Mhit",F8PPACA_Mhit,"F8PPACA_Mhit[4]/I");

  //===== Calibrated ================================

  //===== PPAC =====
  tree->Branch("PPAC_T",PPAC_T,Form("PPAC_T[%d][4][4]/D",Nfpl_PPAC));
  tree->Branch("PPAC_AT",PPAC_AT,Form("PPAC_AT[%d][4]/D",Nfpl_PPAC));
  tree->Branch("PPAC_fT",PPAC_fT,Form("PPAC_fT[%d][4][4]/O",Nfpl_PPAC));
  tree->Branch("PPAC_fAT",PPAC_fAT,Form("PPAC_fAT[%d][4]/O",Nfpl_PPAC));
  tree->Branch("PPAC_Tsum",PPAC_Tsum,Form("PPAC_Tsum[%d][4][2]/D",Nfpl_PPAC));
  tree->Branch("PPAC_Tdiff",PPAC_Tdiff,Form("PPAC_Tdiff[%d][4][2]/D",Nfpl_PPAC));
  tree->Branch("X",X,Form("X[%d][4]/D",Nfpl_PPAC));
  tree->Branch("Y",Y,Form("Y[%d][4]/D",Nfpl_PPAC));
  tree->Branch("fX",fX,Form("fX[%d][4]/O",Nfpl_PPAC));
  tree->Branch("fY",fY,Form("fY[%d][4]/O",Nfpl_PPAC));
  tree->Branch("Num_fPPAC_X",Num_fPPAC_X,Form("Num_fPPAC_X[%d][3]/I",Nfpl_PPAC));
  tree->Branch("Num_fPPAC_Y",Num_fPPAC_Y,Form("Num_fPPAC_Y[%d][3]/I",Nfpl_PPAC));

  //===== FocalPlane =====
  //  tree->Branch("Fpl_XA",Fpl_XA,Form("Fpl_XA[%d]/D",Nfpl_PPAC));
  //  tree->Branch("Fpl_XB",Fpl_XB,Form("Fpl_XB[%d]/D",Nfpl_PPAC));
  //  tree->Branch("Fpl_YA",Fpl_YA,Form("Fpl_YA[%d]/D",Nfpl_PPAC));
  //  tree->Branch("Fpl_YB",Fpl_YB,Form("Fpl_YB[%d]/D",Nfpl_PPAC));
  //  tree->Branch("Fpl_XR",Fpl_XR,Form("Fpl_XR[%d][4]/D",Nfpl_PPAC));
  //  tree->Branch("Fpl_YR",Fpl_YR,Form("Fpl_YR[%d][4]/D",Nfpl_PPAC));
  tree->Branch("Fpl_XP",Fpl_XP,Form("Fpl_XP[%d]/D",Nfpl_PPAC));
  tree->Branch("Fpl_XT",Fpl_XT,Form("Fpl_XT[%d]/D",Nfpl_PPAC));
  tree->Branch("Fpl_YP",Fpl_YP,Form("Fpl_YP[%d]/D",Nfpl_PPAC));
  tree->Branch("Fpl_YT",Fpl_YT,Form("Fpl_YT[%d]/D",Nfpl_PPAC));
  //  tree->Branch("Fpl_XFlag",Fpl_XFlag,Form("Fpl_XFlag[%d]/O",Nfpl_PPAC));
  //  tree->Branch("Fpl_YFlag",Fpl_YFlag,Form("Fpl_YFlag[%d]/O",Nfpl_PPAC));

  //===== Plastic ===================================================
  tree->Branch("PLA_Q",PLA_Q,Form("PLA_Q[%d][2]/D",Nfpl_PLA));
  tree->Branch("PLA_T",PLA_T,Form("PLA_T[%d][2]/D",Nfpl_PLA));
  tree->Branch("PLA_S",PLA_S,Form("PLA_S[%d][2]/D",Nfpl_PLA));
  tree->Branch("PLA_Qave",PLA_Qave,Form("PLA_Qave[%d][2]/D",Nfpl_PLA));
  tree->Branch("PLA_Qdiff",PLA_Qdiff,Form("PLA_Qdiff[%d]/D",Nfpl_PLA));
  tree->Branch("PLA_Tave",PLA_Tave,Form("PLA_Tave[%d]/D",Nfpl_PLA));
  tree->Branch("PLA_Save",PLA_Save,Form("PLA_Save[%d]/D",Nfpl_PLA));
  tree->Branch("PLA_Tdiff",PLA_Tdiff,Form("PLA_Tdiff[%d]/D",Nfpl_PLA));
  tree->Branch("PLA_Sdiff",PLA_Sdiff,Form("PLA_Sdiff[%d]/D",Nfpl_PLA));

  //===== F8VETO ===================================================
  tree->Branch("F8VETO_Q",F8VETO_Q,"F8VETO_Q[2]/D");
  tree->Branch("F8VETO_T",F8VETO_T,"F8VETO_T[2]/D");
  tree->Branch("F8VETO_Qave",F8VETO_Qave,"F8VETO_Qave[2]/D");
  tree->Branch("F8VETO_Qdiff",&F8VETO_Qdiff,"F8VETO_Qdiff/D");
  tree->Branch("F8VETO_Tave",&F8VETO_Tave,"F8VETO_Tave/D");
  tree->Branch("F8VETO_Tdiff",&F8VETO_Tdiff,"F8VETO_Tdiff/D");

  //===== F11Long ===================================================
  //  tree->Branch("F11Long_Q",F11Long_Q,"F11Long_Q[2]/D");
  //  tree->Branch("F11Long_T",F11Long_T,"F11Long_T[2]/D");
  //  tree->Branch("F11Long_Qave",F11Long_Qave,"F11Long_Qave[2]/D");
  //  tree->Branch("F11Long_Qdiff",&F11Long_Qdiff,"F11Long_Qdiff/D");
  //  tree->Branch("F11Long_Tave",&F11Long_Tave,"F11Long_Tave/D");
  //  tree->Branch("F11Long_Tdiff",&F11Long_Tdiff,"F11Long_Tdiff/D");

  //===== IC ======================================================
  tree->Branch("F7IC_E",F7IC_E,"F7IC_E[6]/D");
  tree->Branch("F8IC_E",F8IC_E,"F8IC_E[3]/D");
  tree->Branch("F11IC_E",F11IC_E,"F11IC_E[6]/D");
  tree->Branch("F7IC_Esum",&F7IC_Esum,"F7IC_Esum/D");
  tree->Branch("F8IC_Esum",&F8IC_Esum,"F8IC_Esum/D");
  tree->Branch("F11IC_Esum",&F11IC_Esum,"F11IC_Esum/D");

  //===== Reconstruction =========================================
  tree->Branch("RecoF8Angle",RecoF8Angle,"RecoF8Angle[3]/D");

  //  tree->Branch("Delta",Delta,"Delta[6]/D");
  //  tree->Branch("Brho",Brho,"Brho[6]/D");
  tree->Branch("DeltaD7",&DeltaD7,"DeltaD7/D");
  tree->Branch("DeltaD8",&DeltaD8,"DeltaD8/D");
  tree->Branch("BrhoD7",&BrhoD7,"BrhoD7/D");
  tree->Branch("BrhoD8",&BrhoD8,"BrhoD8/D");

  tree->Branch("Delta35",&Delta35,"Delta35/D");
  tree->Branch("Delta57",&Delta57,"Delta57/D");
  tree->Branch("Delta89",&Delta89,"Delta89/D");
  tree->Branch("Delta810",&Delta810,"Delta810/D");
  tree->Branch("Delta911",&Delta911,"Delta911/D");
  tree->Branch("Delta1011",&Delta1011,"Delta1011/D");

  tree->Branch("Brho35",&Brho35,"Brho35/D");
  tree->Branch("Brho57",&Brho57,"Brho57/D");
  tree->Branch("Brho89",&Brho89,"Brho89/D");
  tree->Branch("Brho810",&Brho810,"Brho810/D");
  tree->Branch("Brho911",&Brho911,"Brho911/D");
  tree->Branch("Brho1011",&Brho1011,"Brho1011/D");

  tree->Branch("dLength37",&dLength37,"dLength37/D");
  tree->Branch("dLength811",&dLength811,"dLength811/D");
  tree->Branch("dLength35",&dLength35,"dLength35/D");
  tree->Branch("dLength57",&dLength57,"dLength57/D");
  tree->Branch("dLength89",&dLength89,"dLength89/D");
  tree->Branch("dLength911",&dLength911,"dLength911/D");

  //  tree->Branch("TOF",TOF,"TOF[6]/D");
  //tree->Branch("dLength",dLength,"dLength[6]/D");
  //  tree->Branch("Beta",Beta,"Beta[6]/D");

  tree->Branch("TOF37",&TOF37,"TOF37/D");
  tree->Branch("TOF811",&TOF811,"TOF811/D");
  tree->Branch("TOF35",&TOF35,"TOF35/D");
  tree->Branch("TOF57",&TOF57,"TOF57/D");
  tree->Branch("TOF89",&TOF89,"TOF89/D");
  tree->Branch("TOF911",&TOF911,"TOF911/D");

  tree->Branch("Beta37",&Beta37,"Beta37/D");
  tree->Branch("Beta811",&Beta811,"Beta811/D");
  tree->Branch("Beta35",Beta35,"Beta35[2]/D");
  tree->Branch("Beta57",Beta57,"Beta57[2]/D");
  tree->Branch("Beta89",Beta89,"Beta89[2]/D");
  tree->Branch("Beta911",Beta911,"Beta911[2]/D");

  //  tree->Branch("Gamma37",&Gamma37,"Gamma37/D");
  //  tree->Branch("Gamma811",&Gamma811,"Gamma811/D");
  //  tree->Branch("Gamma35",Gamma35,"Gamma35[2]/D");
  //  tree->Branch("Gamma57",Gamma57,"Gamma57[2]/D");
  //  tree->Branch("Gamma89",Gamma89,"Gamma89[2]/D");
  //  tree->Branch("Gamma911",Gamma911,"Gamma911[2]/D");

  tree->Branch("AoQ37",&AoQ37,"AoQ37/D");
  tree->Branch("AoQ811",&AoQ811,"AoQ811/D");
  tree->Branch("AoQ35",AoQ35,"AoQ35[2]/D");
  tree->Branch("AoQ57",AoQ57,"AoQ57[2]/D");
  tree->Branch("AoQ89",AoQ89,"AoQ89[2]/D");
  tree->Branch("AoQ911",AoQ911,"AoQ911[2]/D");

  tree->Branch("Zet7",&Zet7,"Zet7/D");
  tree->Branch("Zet8",&Zet8,"Zet8/D");
  tree->Branch("Zet11",&Zet11,"Zet11/D");

}

void ribf_branch_read(TTree *tree2){

  tree2->SetBranchAddress("Nevent",&Nevent);
  tree2->SetBranchAddress("Brho_NMR",Brho_NMR);

  tree2->SetBranchAddress("camac_ts0",camac_ts0);
  tree2->SetBranchAddress("camac_ts",camac_ts);

  tree2->SetBranchAddress("mpv_Nevent",mpv_Nevent);
  tree2->SetBranchAddress("mpv_ts0",mpv_ts0);
  tree2->SetBranchAddress("mpv_ts",mpv_ts);
  tree2->SetBranchAddress("mpv_10kclock",mpv_10kclock);

  tree2->SetBranchAddress("v1190",v1190);
  tree2->SetBranchAddress("v1190raw",v1190raw);
  tree2->SetBranchAddress("v1190num",v1190num);

  tree2->SetBranchAddress("PPAC_Qraw",PPAC_Qraw);  
  tree2->SetBranchAddress("PPAC_Traw",PPAC_Traw);  
  tree2->SetBranchAddress("PPAC_AQraw",PPAC_AQraw);  
  tree2->SetBranchAddress("PPAC_ATraw",PPAC_ATraw);  
  
  tree2->SetBranchAddress("PLA_Qraw",PLA_Qraw);  
  tree2->SetBranchAddress("PLA_Traw",PLA_Traw);  
  //  tree2->SetBranchAddress("PLA2_Qraw",PLA2_Qraw);  
  //  tree2->SetBranchAddress("PLA2_Traw",PLA2_Traw);  

  tree2->SetBranchAddress("F8VETO_Qraw",F8VETO_Qraw);  
  tree2->SetBranchAddress("F8VETO_Traw",F8VETO_Traw);  

  //  tree2->SetBranchAddress("F11Long_Qraw",F11Long_Qraw);  
  //  tree2->SetBranchAddress("F11Long_Traw",F11Long_Traw);  

  tree2->SetBranchAddress("F7IC_Eraw",F7IC_Eraw);  
  tree2->SetBranchAddress("F8IC_Eraw",F8IC_Eraw);  
  tree2->SetBranchAddress("F11IC_Eraw",F11IC_Eraw);  
  tree2->SetBranchAddress("F7IC_Gas",&F7IC_Gas);
  tree2->SetBranchAddress("F8IC_Gas",&F8IC_Gas);
  tree2->SetBranchAddress("F11IC_Gas",&F11IC_Gas);

  tree2->SetBranchAddress("PLA_MT",PLA_MT);  
  tree2->SetBranchAddress("PLA_Mhit",PLA_Mhit);  
  tree2->SetBranchAddress("F8VETO_MT",F8VETO_MT);  
  tree2->SetBranchAddress("F8VETO_Mhit",F8VETO_Mhit);  
  tree2->SetBranchAddress("F8PPACA_MT",F8PPACA_MT);  
  tree2->SetBranchAddress("F8PPACA_Mhit",F8PPACA_Mhit);  

  //===== PPAC =====
  tree2->SetBranchAddress("PPAC_T",PPAC_T);
  tree2->SetBranchAddress("PPAC_AT",PPAC_AT);
  tree2->SetBranchAddress("PPAC_fT",PPAC_fT);
  tree2->SetBranchAddress("PPAC_fAT",PPAC_fAT);
  tree2->SetBranchAddress("PPAC_Tsum",PPAC_Tsum);
  tree2->SetBranchAddress("PPAC_Tdiff",PPAC_Tdiff);
  tree2->SetBranchAddress("X",X);
  tree2->SetBranchAddress("Y",Y);
  tree2->SetBranchAddress("fX",fX);
  tree2->SetBranchAddress("fY",fY);
  tree2->SetBranchAddress("Num_fPPAC_X",Num_fPPAC_X);
  tree2->SetBranchAddress("Num_fPPAC_Y",Num_fPPAC_Y);

  //===== FocalPlane =====
  //  tree2->SetBranchAddress("Fpl_XA",Fpl_XA);
  //  tree2->SetBranchAddress("Fpl_XB",Fpl_XB);
  //  tree2->SetBranchAddress("Fpl_YA",Fpl_YA);
  //  tree2->SetBranchAddress("Fpl_YB",Fpl_YB);
  //  tree2->SetBranchAddress("Fpl_XR",Fpl_XR);
  //  tree2->SetBranchAddress("Fpl_YR",Fpl_YR);
  tree2->SetBranchAddress("Fpl_XP",Fpl_XP);
  tree2->SetBranchAddress("Fpl_XT",Fpl_XT);
  tree2->SetBranchAddress("Fpl_YP",Fpl_YP);
  tree2->SetBranchAddress("Fpl_YT",Fpl_YT);
  //  tree2->SetBranchAddress("Fpl_XFlag",Fpl_XFlag);
  //  tree2->SetBranchAddress("Fpl_YFlag",Fpl_YFlag);

  //===== Plastic ===================================================
  tree2->SetBranchAddress("PLA_Q",PLA_Q);
  tree2->SetBranchAddress("PLA_T",PLA_T);
  tree2->SetBranchAddress("PLA_S",PLA_S);
  tree2->SetBranchAddress("PLA_Qave",PLA_Qave);
  tree2->SetBranchAddress("PLA_Qdiff",PLA_Qdiff);
  tree2->SetBranchAddress("PLA_Tave",PLA_Tave);
  tree2->SetBranchAddress("PLA_Save",PLA_Save);
  tree2->SetBranchAddress("PLA_Tdiff",PLA_Tdiff);
  tree2->SetBranchAddress("PLA_Sdiff",PLA_Sdiff);

  //===== F8VETO ===================================================
  tree2->SetBranchAddress("F8VETO_Q",F8VETO_Q);
  tree2->SetBranchAddress("F8VETO_T",F8VETO_T);
  tree2->SetBranchAddress("F8VETO_Qave",F8VETO_Qave);
  tree2->SetBranchAddress("F8VETO_Qdiff",&F8VETO_Qdiff);
  tree2->SetBranchAddress("F8VETO_Tave",&F8VETO_Tave);
  tree2->SetBranchAddress("F8VETO_Tdiff",&F8VETO_Tdiff);

  //===== F11Long ===================================================
  //  tree2->SetBranchAddress("F11Long_Q",F11Long_Q);
  //  tree2->SetBranchAddress("F11Long_T",F11Long_T);
  //  tree2->SetBranchAddress("F11Long_Qave",F11Long_Qave);
  //  tree2->SetBranchAddress("F11Long_Qdiff",&F11Long_Qdiff);
  //  tree2->SetBranchAddress("F11Long_Tave",&F11Long_Tave);
  //  tree2->SetBranchAddress("F11Long_Tdiff",&F11Long_Tdiff);

  //===== IC ======================================================
  tree2->SetBranchAddress("F7IC_E",F7IC_E);
  tree2->SetBranchAddress("F8IC_E",F8IC_E);
  tree2->SetBranchAddress("F11IC_E",F11IC_E);
  tree2->SetBranchAddress("F7IC_Esum",&F7IC_Esum);
  tree2->SetBranchAddress("F8IC_Esum",&F8IC_Esum);
  tree2->SetBranchAddress("F11IC_Esum",&F11IC_Esum);

  //===== Reconstruction =========================================
  tree2->SetBranchAddress("RecoF8Angle",RecoF8Angle);

  //  tree2->SetBranchAddress("Delta",Delta);
  //  tree2->SetBranchAddress("Brho",Brho);
  tree2->SetBranchAddress("DeltaD7",&DeltaD7);
  tree2->SetBranchAddress("DeltaD8",&DeltaD8);
  tree2->SetBranchAddress("BrhoD7",&BrhoD7);
  tree2->SetBranchAddress("BrhoD8",&BrhoD8);

  tree2->SetBranchAddress("Delta35",&Delta35);
  tree2->SetBranchAddress("Delta57",&Delta57);
  tree2->SetBranchAddress("Delta89",&Delta89);
  tree2->SetBranchAddress("Delta810",&Delta810);
  tree2->SetBranchAddress("Delta911",&Delta911);
  tree2->SetBranchAddress("Delta1011",&Delta1011);

  tree2->SetBranchAddress("Brho35",&Brho35);
  tree2->SetBranchAddress("Brho57",&Brho57);
  tree2->SetBranchAddress("Brho89",&Brho89);
  tree2->SetBranchAddress("Brho810",&Brho810);
  tree2->SetBranchAddress("Brho911",&Brho911);
  tree2->SetBranchAddress("Brho1011",&Brho1011);

  //  tree2->SetBranchAddress("TOF",TOF);
  //  tree2->SetBranchAddress("dLength",dLength);
  //  tree2->SetBranchAddress("Beta",Beta);

  tree2->SetBranchAddress("TOF37",&TOF37);
  tree2->SetBranchAddress("TOF811",&TOF811);
  tree2->SetBranchAddress("TOF35",&TOF35);
  tree2->SetBranchAddress("TOF57",&TOF57);
  tree2->SetBranchAddress("TOF89",&TOF89);
  tree2->SetBranchAddress("TOF911",&TOF911);

  tree2->SetBranchAddress("Beta37",&Beta37);
  tree2->SetBranchAddress("Beta811",&Beta811);
  tree2->SetBranchAddress("Beta35",Beta35);
  tree2->SetBranchAddress("Beta57",Beta57);
  tree2->SetBranchAddress("Beta89",Beta89);
  tree2->SetBranchAddress("Beta911",Beta911);

  //  tree2->SetBranchAddress("Gamma37",&Gamma37);
  //  tree2->SetBranchAddress("Gamma811",&Gamma811);
  //  tree2->SetBranchAddress("Gamma35",Gamma35);
  //  tree2->SetBranchAddress("Gamma57",Gamma57);
  //  tree2->SetBranchAddress("Gamma89",Gamma89);
  //  tree2->SetBranchAddress("Gamma911",Gamma911);

  tree2->SetBranchAddress("AoQ37",&AoQ37);
  tree2->SetBranchAddress("AoQ811",&AoQ811);
  tree2->SetBranchAddress("AoQ35",AoQ35);
  tree2->SetBranchAddress("AoQ57",AoQ57);
  tree2->SetBranchAddress("AoQ89",AoQ89);
  tree2->SetBranchAddress("AoQ911",AoQ911);

  tree2->SetBranchAddress("Zet7",&Zet7);
  tree2->SetBranchAddress("Zet8",&Zet8);
  tree2->SetBranchAddress("Zet11",&Zet11);

}
