void var_init(){

  for(int l=0; l<100; l++)tgate[l]=false;

  // PPAC
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)for(int n=0; n<4; n++)PPAC_T[l][m][n]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)PPAC_AT[l][m]=0;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)for(int n=0; n<4; n++)PPAC_fT[l][m][n]=false;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)PPAC_fAT[l][m]=0;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)for(int n=0; n<2; n++)PPAC_Tsum[l][m][n]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)for(int n=0; n<2; n++)PPAC_Tdiff[l][m][n]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)X[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)X[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)fX[l][m]=false;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)fY[l][m]=false;
  for(int l=0; l<12; l++)for(int m=0; m<3; m++)Num_fPPAC_X[l][m]=0;
  for(int l=0; l<12; l++)for(int m=0; m<3; m++)Num_fPPAC_Y[l][m]=0;

  // Tracking
  for(int l=0; l<12; l++)Fpl_XA[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_XB[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_YA[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_YB[l]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)Fpl_XR[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<4; m++)Fpl_YR[l][m]=-9999.;
  for(int l=0; l<12; l++)Fpl_XP[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_XT[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_YP[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_YT[l]=-9999.;
  for(int l=0; l<12; l++)Fpl_XFlag[l]=false;
  for(int l=0; l<12; l++)Fpl_YFlag[l]=false;

  // Plastic
  for(int l=0; l<12; l++)for(int m=0; m<2; m++)PLA_Q[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<2; m++)PLA_T[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<2; m++)PLA_S[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<2; m++)PLA_Qave[l][m]=-9999.;
  for(int l=0; l<12; l++)PLA_Qdiff[l]=-9999.;
  for(int l=0; l<12; l++)PLA_Tave[l]=-9999.;
  for(int l=0; l<12; l++)PLA_Save[l]=-9999.;
  for(int l=0; l<12; l++)PLA_Tdiff[l]=-9999.;
  for(int l=0; l<12; l++)PLA_Sdiff[l]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<2; m++)PLA_QTC[l][m]=-9999.;
  for(int l=0; l<12; l++)for(int m=0; m<2; m++)PLA_QTCave[l][m]=-9999.;
  for(int l=0; l<12; l++)PLA_QTCdiff[l]=-9999.;

  // F8VETO
  for(int m=0; m<2; m++)F8VETO_Q[m] = -9999.;
  for(int m=0; m<2; m++)F8VETO_T[m] = -9999.;
  for(int m=0; m<2; m++)F8VETO_Qave[m] = -9999.;
  F8VETO_Qdiff = -9999.;
  F8VETO_Tave = -9999.;
  F8VETO_Tdiff = -9999.;
  for(int m=0; m<2; m++)F8VETO_QTC[m] = -9999.;
  for(int m=0; m<2; m++)F8VETO_QTCave[m] = -9999.;
  F8VETO_QTCdiff = -9999.;

  // F11Long
  for(int m=0; m<2; m++)F11Long_Q[m] = -9999.;
  for(int m=0; m<2; m++)F11Long_T[m] = -9999.;
  for(int m=0; m<2; m++)F11Long_Qave[m] = -9999.;
  F11Long_Qdiff = -9999.;
  F11Long_Tave = -9999.;
  F11Long_Tdiff = -9999.;
  for(int m=0; m<2; m++)F11Long_QTC[m] = -9999.;
  for(int m=0; m<2; m++)F11Long_QTCave[m] = -9999.;
  F11Long_QTCdiff = -9999.;

  // IC     
  for(int m=0; m<6; m++)F3IC_E[m] = 0.;
  for(int m=0; m<6; m++)F7IC_E[m] = 0.;
  for(int m=0; m<3; m++)F8IC_E[m] = 0.;
  for(int m=0; m<6; m++)F11IC_E[m] = 0.;
  F3IC_Esum = 0.;
  F7IC_Esum = 0.;
  F8IC_Esum = 0.;
  F11IC_Esum = 0.;

  // Brho
  for(int l=0; l<6; l++)Delta[l] = -9999.;
  for(int l=0; l<6; l++)Brho[l] = -9999.;
  DeltaD7=-9999.;
  DeltaD8=-9999.;
  BrhoD7=-9999.;
  BrhoD8=-9999.;

  // Reconstructed X-Angle @F8
  for(int l=0; l<3; l++)RecoF8Angle[l] = -9999.;

  // TOF
  for(int l=0; l<6; l++)TOF[l] = -9999.;
  for(int l=0; l<6; l++)dLength[l] = 0.;
  for(int l=0; l<6; l++)Beta[l] = -9999.;

  Delta35 = -9999.;
  Delta57 = -9999.;
  Delta89 = -9999.;
  Delta810 = -9999.;
  Delta911 = -9999.;
  Delta1011 = -9999.;

  Brho35 = -9999.;
  Brho57 = -9999.;
  Brho89 = -9999.;
  Brho810 = -9999.;
  Brho911 = -9999.;
  Brho1011 = -9999.;

  dLength37 = -9999.;
  dLength811 = -9999.;
  dLength35 = -9999.;
  dLength57 = -9999.;
  dLength89 = -9999.;
  dLength911 = -9999.;

  TOF37 = -9999.;
  TOF811 = -9999.;
  TOF35 = -9999.;
  TOF57 = -9999.;
  TOF89 = -9999.;
  TOF911 = -9999.;

  Beta37 = -9999.;
  Beta811 = -9999.;
  Gamma37 = -9999.;
  Gamma811 = -9999.;
  AoQ37 = -9999.;
  AoQ811 = -9999.;

  for(int l=0; l<2; l++)Beta35[l] = -9999.;
  for(int l=0; l<2; l++)Beta57[l] = -9999.;
  for(int l=0; l<2; l++)Beta89[l] = -9999.;
  for(int l=0; l<2; l++)Beta911[l] = -9999.;
  for(int l=0; l<2; l++)Gamma35[l] = -9999.;
  for(int l=0; l<2; l++)Gamma57[l] = -9999.;
  for(int l=0; l<2; l++)Gamma89[l] = -9999.;
  for(int l=0; l<2; l++)Gamma911[l] = -9999.;
  for(int l=0; l<2; l++)AoQ35[l] = -9999.;
  for(int l=0; l<2; l++)AoQ57[l] = -9999.;
  for(int l=0; l<2; l++)AoQ89[l] = -9999.;
  for(int l=0; l<2; l++)AoQ911[l] = -9999.;

  // Zet
  Zet3 = -9999.;
  Zet7 = -9999.;
  Zet8 = -9999.;
  Zet11 = -9999.;

  dLength35_2 = 0.;
  dLength57_2 = 0.;
  Beta35_2 = -9999.;
  Beta57_2 = -9999.;
  Gamma35_2 = -9999.;
  Gamma57_2 = -9999.;

  F5PPAC1_X = -9999.;
  F7PLA_Q2X = -9999.;
  Delta35_2 = -9999.;
  Delta57_2 = -9999.;
  Brho35_2 = -9999.;
  Brho57_2 = -9999.;
  AoQ35_2 = -9999.;
  AoQ57_2 = -9999.;
  Zet3_2 = -9999.;
  Zet7_2 = -9999.;

};



void ribf_encpid(int runN,TRandom *grand){


  //===== PPAC =======================================================
  for(int l=1;l<12;l++){
    if(Use_PPAC[l]){
      for(int m=0;m<4;m++){
      
	//===== Fired or not ==========
	for(int n=0;n<4;n++){
	  if(-8000<PPAC_Traw[l][m][n]&&PPAC_Traw[l][m][n]<8000){PPAC_fT[l][m][n]=true;}else{PPAC_fT[l][m][n]=false;}
	}
	if(-8000<PPAC_ATraw[l][m]&&PPAC_ATraw[l][m]<8000){PPAC_fAT[l][m]=true;}else{PPAC_fAT[l][m]=false;}
      
	//===== ch2ns =================
	//	for(int n=0;n<4;n++)PPAC_T[l][m][n] = (double)PPAC_Traw[l][m][n] * ch2ns_PPAC[l][m][n];
	//	PPAC_AT[l][m] = (double)PPAC_ATraw[l][m] * ch2ns_PPACA[l][m];
	for(int n=0;n<4;n++)PPAC_T[l][m][n] = ( (double)PPAC_Traw[l][m][n] + grand->Uniform(0,1) ) * ch2ns_PPAC[l][m][n];
	PPAC_AT[l][m] = ( (double)PPAC_ATraw[l][m] + grand->Uniform(0,1) ) * ch2ns_PPACA[l][m];

	//===== For X =============
	if(PPAC_fT[l][m][0]&&PPAC_fT[l][m][2]&&PPAC_fAT[l][m]){

	  PPAC_Tsum[l][m][0]  = PPAC_T[l][m][0] + PPAC_T[l][m][2] -2.*PPAC_AT[l][m] - Tsum_Offset[0][l][m];
	  PPAC_Tdiff[l][m][0] = PPAC_T[l][m][0] - PPAC_T[l][m][2] - Outoffset[l][m][0];

	  X[l][m] = PPAC_Tdiff[l][m][0] * ns2mm[l][m][0] * 0.5;
	  X[l][m] -= Inoffset[l][m][0];
	  X[l][m] -= Geomoffset[l][m][0];
	  X[l][m] = -X[l][m]; // definition for optics only for X
	  if( (Tsum_Max[0][l][m] <= Tsum_Min[0][l][m]) ||
	      (Tsum_Min[0][l][m] <= PPAC_Tsum[l][m][0] && PPAC_Tsum[l][m][0] <= Tsum_Max[0][l][m]) ){
	    fX[l][m] = true;
	  }
	
	} 
      
	//===== For Y =============
	if(PPAC_fT[l][m][1]&&PPAC_fT[l][m][3]&&PPAC_fAT[l][m]){

	  PPAC_Tsum[l][m][1] = PPAC_T[l][m][1] + PPAC_T[l][m][3] - 2. * PPAC_AT[l][m] - Tsum_Offset[1][l][m];
	  PPAC_Tdiff[l][m][1] = PPAC_T[l][m][1] - PPAC_T[l][m][3] - Outoffset[l][m][1];

	  Y[l][m] = PPAC_Tdiff[l][m][1] * ns2mm[l][m][1] * 0.5;
	  Y[l][m] -= Inoffset[l][m][1];
	  Y[l][m] -= Geomoffset[l][m][1];
	  if( (Tsum_Max[1][l][m] <= Tsum_Min[1][l][m]) ||
	      (Tsum_Min[1][l][m] <= PPAC_Tsum[l][m][1] && PPAC_Tsum[l][m][1] <= Tsum_Max[1][l][m]) ){
	    fY[l][m] = true;
	  }

	} 
      
	//===== Additional offset (if needed) =============
	X[l][m] = X[l][m] - Resioffset[l][m][0];
	Y[l][m] = Y[l][m] - Resioffset[l][m][1];
      
	//===== Number of fired PPACs =====================
	if(fX[l][m]){
	  Num_fPPAC_X[l][0]++;
	  if(m<2){Num_fPPAC_X[l][1]++;}else{Num_fPPAC_X[l][2]++;}
	}

	if(fY[l][m]){
	  Num_fPPAC_Y[l][0]++;
	  if(m<2){Num_fPPAC_Y[l][1]++;}else{Num_fPPAC_Y[l][2]++;}
	}
     
      }
    }
  }


  // For F5 measurement
  switch(Num_fPPAC_X[5][1]){
  case 0:
    F5PPAC1_X = -9999.;
    break;
  case 1:
    if(fX[5][0]){
      F5PPAC1_X = X[5][0];
    }else{
      F5PPAC1_X = X[5][1];
    }
    break;
  case 2:
    F5PPAC1_X = 0.5*(X[5][0]+X[5][1]);
    break;
  default:
    F5PPAC1_X = -9999.;
    break;
  }
  

  //===== Focal plane ====================================================
  for(int l=1; l<12; l++){
    if(Use_PPAC[l]){

      //===== For X =============
      if( Num_fPPAC_X[l][1]>0 && Num_fPPAC_X[l][2]>0 ){	

	Fpl_XFlag[l]=true;

	double cx=0.;
	double czz=0.;
	double cxz=0.;
	double cz=0.;

	for(int m=0; m<4; m++){
	  if(fX[l][m]){	    
	    cx  += X[l][m];
	    czz += pow(Zpos[0][l][m] + Zoffset[l], 2.);
	    cxz += X[l][m] * (Zpos[0][l][m] + Zoffset[l]);
	    cz  += Zpos[0][l][m] + Zoffset[l];
	  }// fire X/Y
	}// m

	double cdelta = Num_fPPAC_X[l][0] * czz - pow(cz,2.);

	Fpl_XA[l] = (cx*czz - cxz*cz) / cdelta; 
	Fpl_XB[l] = (Num_fPPAC_X[l][0]*cxz - cx*cz) / cdelta; 
	Fpl_XP[l] = Fpl_XA[l];
	Fpl_XT[l] = TMath::ATan(Fpl_XB[l]) * 1000.;
	
	for(int m=0;m<4;m++)if(fX[l][m])Fpl_XR[l][m] = X[l][m] - (Fpl_XA[l] + Fpl_XB[l] * Zpos[0][l][m]);
      }// if(Num_fPPAC_X)

      //===== For Y =============
      if( Num_fPPAC_Y[l][1]>0 && Num_fPPAC_Y[l][2]>0 ){	

	Fpl_YFlag[l]=true;

	double cy=0;
	double czz=0.;
	double cyz=0.;
	double cz=0.;

	for(int m=0; m<4; m++){
	  if(fY[l][m]){
	    cy  += Y[l][m];
	    czz += pow(Zpos[1][l][m] + Zoffset[l], 2.);
	    cyz += Y[l][m] * (Zpos[1][l][m] + Zoffset[l]);
	    cz  += Zpos[1][l][m] + Zoffset[l];
	  }// fire X/Y
	}// m

	double cdelta = Num_fPPAC_Y[l][0] * czz - pow(cz,2.);

	Fpl_YA[l] = (cy*czz - cyz*cz) / cdelta; 
	Fpl_YB[l] = (Num_fPPAC_Y[l][0]*cyz - cy*cz) / cdelta; 
	Fpl_YP[l] = Fpl_YA[l];
	Fpl_YT[l] = TMath::ATan(Fpl_YB[l]) * 1000.;
	
	for(int m=0; m<4; m++)if(fY[l][m])Fpl_YR[l][m] = Y[l][m] - (Fpl_YA[l] + Fpl_YB[l] * Zpos[1][l][m]);
      }// if(Num_fPPAC_Y)

    }// Use_PPAC
  }// Focal plane loop

  //===== Plastic ==========================================

  for(int l=0; l<12; l++){
    if(Use_PL[l]){

      for(int m=0; m<2; m++){
	//	PLA_Q[l][m] = ch2MeV_PLA[0][l][m] * ( (double)PLA_Qraw[l][m] - ch2MeV_PLA[1][l][m] );
	//	PLA_T[l][m] = ch2ns_PLA[l][m] * (double)PLA_Traw[l][m];
	PLA_Q[l][m] = ch2MeV_PLA[0][l][m] * ( (double)PLA_Qraw[l][m] + grand->Uniform(0,1) - ch2MeV_PLA[1][l][m] );
	PLA_T[l][m] = ch2ns_PLA[l][m] * ( (double)PLA_Traw[l][m] + grand->Uniform(0,1) );
	PLA_S[l][m] = PLA_T[l][m] - ( Slew_PLA[0][l][m] * pow(PLA_Q[l][m],Slew_PLA[1][l][m]) + Slew_PLA[2][l][m] );
	PLA_QTC[l][m] = ch2MeV_PLA_QTC[0][l][m] * ( (double)PLA_QTCraw[l][m] + grand->Uniform(0,1) - ch2MeV_PLA_QTC[1][l][m] );
      }
    
      PLA_Qave[l][0] = 0.5 * ( PLA_Q[l][0] + PLA_Q[l][1] );
      PLA_Qave[l][1] = TMath::Sqrt(PLA_Q[l][0] * PLA_Q[l][1]);
      PLA_Qdiff[l] = ( PLA_Q[l][0] - PLA_Q[l][1] );

      PLA_QTCave[l][0] = 0.5 * ( PLA_QTC[l][0] + PLA_QTC[l][1] );
      PLA_QTCave[l][1] = TMath::Sqrt(PLA_QTC[l][0] * PLA_QTC[l][1]);
      PLA_QTCdiff[l] = ( PLA_QTC[l][0] - PLA_QTC[l][1] );
      
      PLA_Tave[l] = 0.5 * ( PLA_T[l][0] + PLA_T[l][1] );
      PLA_Save[l] = 0.5 * ( PLA_S[l][0] + PLA_S[l][1] );
      PLA_Tdiff[l] = PLA_T[l][0] - PLA_T[l][1];
      PLA_Sdiff[l] = PLA_S[l][0] - PLA_S[l][1];
   
    }
  } 
  
  F7PLA_Q2X = MeV2mm_F7PLA[0]+MeV2mm_F7PLA[1]*log(PLA_Q[7][1]/PLA_Q[7][0])+MeV2mm_F7PLA[2]*pow(log(PLA_Q[7][1]/PLA_Q[7][0]),2.);
  

  //===== F8VETO ============================================

  for(int m=0; m<2; m++){
    //    F8VETO_Q[m] = ch2MeV_F8VETO[0][m] * ( (double)F8VETO_Qraw[m] - ch2MeV_F8VETO[1][m] );
    //    F8VETO_T[m] = ch2ns_F8VETO[m] * (double)F8VETO_Traw[m];
    F8VETO_Q[m] = ch2MeV_F8VETO[0][m] * ( (double)F8VETO_Qraw[m] + grand->Uniform(0,1) - ch2MeV_F8VETO[1][m] );
    F8VETO_T[m] = ch2ns_F8VETO[m] * ( (double)F8VETO_Traw[m] + grand->Uniform(0,1) );
    F8VETO_QTC[m] = ch2MeV_F8VETO_QTC[0][m] * ( (double)F8VETO_QTCraw[m] + grand->Uniform(0,1) - ch2MeV_F8VETO_QTC[1][m] );
  }
  
  F8VETO_Qave[0] = 0.5 * ( F8VETO_Q[0] + F8VETO_Q[1] );
  F8VETO_Qave[1] = sqrt( F8VETO_Q[0] * F8VETO_Q[1] );
  F8VETO_Qdiff = ( F8VETO_Q[0] - F8VETO_Q[1] );

  F8VETO_QTCave[0] = 0.5 * ( F8VETO_QTC[0] + F8VETO_QTC[1] );
  F8VETO_QTCave[1] = sqrt( F8VETO_QTC[0] * F8VETO_QTC[1] );
  F8VETO_QTCdiff = ( F8VETO_QTC[0] - F8VETO_QTC[1] );

  F8VETO_Tave = 0.5 * ( F8VETO_T[0] + F8VETO_T[1] );
  F8VETO_Tdiff = ( F8VETO_T[0] - F8VETO_T[1] );

  //===== F11Long ============================================

  for(int m=0; m<2; m++){
    //    F11Long_Q[m] = ch2MeV_F11Long[0][m] * ( (double)F11Long_Qraw[m] - ch2MeV_F11Long[1][m] );
    //    F11Long_T[m] = ch2ns_F11Long[m] * (double)F11Long_Traw[m];
    F11Long_Q[m] = ch2MeV_F11Long[0][m] * ( (double)F11Long_Qraw[m] + grand->Uniform(0,1) - ch2MeV_F11Long[1][m] );
    F11Long_T[m] = ch2ns_F11Long[m] * ( (double)F11Long_Traw[m] + grand->Uniform(0,1) );
    F11Long_QTC[m] = ch2MeV_F11Long_QTC[0][m] * ( (double)F11Long_QTCraw[m] + grand->Uniform(0,1) - ch2MeV_F11Long_QTC[1][m] );
  }
  
  F11Long_Qave[0] = 0.5 * ( F11Long_Q[0] + F11Long_Q[1] );
  F11Long_Qave[1] = sqrt( F11Long_Q[0] * F11Long_Q[1] );
  F11Long_Qdiff = ( F11Long_Q[0] - F11Long_Q[1] );

  F11Long_QTCave[0] = 0.5 * ( F11Long_QTC[0] + F11Long_QTC[1] );
  F11Long_QTCave[1] = sqrt( F11Long_QTC[0] * F11Long_QTC[1] );
  F11Long_QTCdiff = ( F11Long_QTC[0] - F11Long_QTC[1] );

  F11Long_Tave = 0.5 * ( F11Long_T[0] + F11Long_T[1] );
  F11Long_Tdiff = ( F11Long_T[0] - F11Long_T[1] );

  //===== IC ================================================
  
  for(int m=0;m<6;m++){
    //    F7IC_E[m] = ch2MeV_IC[0][0][m] * (F7IC_Eraw[m] - ch2MeV_IC[1][0][m]);
    F3IC_E[m] = ch2MeV_IC[0][3][m] * (F3IC_Eraw[m] + grand->Uniform(0,1) - ch2MeV_IC[1][3][m]);
    F3IC_Esum += F3IC_E[m];
  }


  for(int m=0;m<6;m++){
    //    F7IC_E[m] = ch2MeV_IC[0][0][m] * (F7IC_Eraw[m] - ch2MeV_IC[1][0][m]);
    F7IC_E[m] = ch2MeV_IC[0][0][m] * (F7IC_Eraw[m] + grand->Uniform(0,1) - ch2MeV_IC[1][0][m]);
    F7IC_Esum += F7IC_E[m];
  }
  
  F7IC_Esum = F7IC_E[0] + F7IC_E[1] + F7IC_E[3] + F7IC_E[4] + F7IC_E[5];
  //  F7IC_Esum = 6./5. * F7IC_Esum;

  for(int m=0;m<3;m++){
    //    F8IC_E[m] = ch2MeV_IC[0][1][m] * (F8IC_Eraw[m] - ch2MeV_IC[1][1][m]);
    F8IC_E[m] = ch2MeV_IC[0][1][m] * (F8IC_Eraw[m] + grand->Uniform(0,1) - ch2MeV_IC[1][1][m]);
    F8IC_Esum += F8IC_E[m];
  }

  for(int m=0;m<6;m++){
    //    F11IC_E[m] = ch2MeV_IC[0][2][m] * (F11IC_Eraw[m] - ch2MeV_IC[1][2][m]);
    F11IC_E[m] = ch2MeV_IC[0][2][m] * (F11IC_Eraw[m] + grand->Uniform(0,1) - ch2MeV_IC[1][2][m]);
    F11IC_Esum += F11IC_E[m];
  }
  

  //===== Brho =============================================
  for(int l=0;l<6;l++){
    
    int ii,jj,kk;
    switch(l){
    case 0: ii= 3; jj= 5; kk=2;break; // kk = 2 -> Brho_NMR[2] -> D3
    case 1: ii= 5; jj= 7; kk=4;break; // kk = 4 -> Brho_NMR[4] -> D5
    case 2: ii= 8; jj= 9; kk=6;break; // kk = 6 -> Brho_NMR[6] -> D7
    case 3: ii= 8; jj=10; kk=6;break; // kk = 6 -> Brho_NMR[6] -> D7
    case 4: ii= 9; jj=11; kk=7;break; // kk = 7 -> Brho_NMR[7] -> D8
    case 5: ii=10; jj=11; kk=7;break; // kk = 7 -> Brho_NMR[7] -> D8
    default: cout << "Error in Brho calculation."<< endl;break;
    }
    
    if( Fpl_XFlag[ii] && Fpl_XFlag[jj] ){
      double detM =       TMat[l][0][1] * TMat[l][1][5] - TMat[l][0][5] * TMat[l][1][1];
      double para_d_Xu =  TMat[l][0][0] * TMat[l][1][1] - TMat[l][0][1] * TMat[l][1][0];
      double para_d_Xd = -TMat[l][1][1];
      double para_d_Ad =  TMat[l][0][1];
      para_d_Xu = para_d_Xu/detM;
      para_d_Xd = para_d_Xd/detM;
      para_d_Ad = para_d_Ad/detM;
      //      double para_a_Xu = -TMat[l][0][0] * TMat[l][1][5] - TMat[l][0][5] * TMat[l][1][0];
      //      double para_a_Xd =  TMat[l][1][5];
      //      double para_a_Ad = -TMat[l][0][5];
      //      para_a_Xu = para_a_Xu/detM;
      //      para_a_Xd = para_a_Xd/detM;
      //      para_a_Ad = para_a_Ad/detM;

      Delta[l] = para_d_Xu * Fpl_XP[ii] + para_d_Xd * Fpl_XP[jj] + para_d_Ad * Fpl_XT[jj];
      Brho[l] = Brho_NMR[kk] * (1.0 + Delta[l] * 0.01);
    }
    
  }

  Delta35   = Delta[0];
  Delta57   = Delta[1];
  Delta89   = Delta[2];
  Delta810  = Delta[3];
  Delta911  = Delta[4];
  Delta1011 = Delta[5];

  Brho35   = Brho[0];
  Brho57   = Brho[1];
  Brho89   = Brho[2];
  Brho810  = Brho[3];
  Brho911  = Brho[4];
  Brho1011 = Brho[5];

  // Delta @D7
  // if delta@F8-F9 is valid, delta@F8-F9 is used,
  // if not, delta@F8-F10 is used.
  DeltaD7 = Delta89;
  BrhoD7 = Brho89;
  if(DeltaD7 < -500.){
    DeltaD7 = Delta810;
    BrhoD7 = Brho810;
  }

  // Delta @D8
  // if delta@F9-F11 is valid, delta@F9-F11 is used,
  // if not, delta@F10-F11 is used.
  DeltaD8 = Delta911;
  BrhoD8 = Brho911;
  if(DeltaD8 < -500.){
    DeltaD8 = Delta1011;
    BrhoD8 = Brho1011;
  }


  // For F5 measurement
  if(Fpl_XFlag[3] && -9990 < F5PPAC1_X ){
    Delta35_2 = ( F5PPAC1_X -  TMat[0][0][0] * Fpl_XP[3] ) / TMat[0][0][5];
    Brho35_2 = Brho_NMR[2] * (1.0 + Delta35_2 * 0.01);
  }

  if(Fpl_XFlag[7] && -9990 < F5PPAC1_X ){
    Delta57_2 = ( Fpl_XP[7] -  TMat[1][0][0] * Fpl_XP[5] ) / TMat[1][0][5];
    Delta57_2 = ( F7PLA_Q2X -  TMat[1][0][0] * Fpl_XP[5] ) / TMat[1][0][5];
    //    Brho57_2 = Brho_NMR[4] * (1.0 + Delta57_2 * 0.01);
  }

  //===== Reconstructed X-angle @F8 =====================
  for(int l=0;l<2;l++){
    
    int ii,jj,kk;
    switch(l){
    case 0: ii= 8; jj= 9; kk=2;break;
    case 1: ii= 8; jj=10; kk=3;break;
    default: cout << "Error in Angle calculation."<< endl;break;
    }
    
    if( Fpl_XFlag[ii] && Fpl_XFlag[jj] ){
      double detM =       TMat[kk][0][1] * TMat[kk][1][5] - TMat[kk][0][5] * TMat[kk][1][1];
      double para_a_Xu = -TMat[kk][0][0] * TMat[kk][1][5] + TMat[kk][0][5] * TMat[kk][1][0];
      double para_a_Xd =  TMat[kk][1][5];
      double para_a_Ad = -TMat[kk][0][5];
      para_a_Xu = para_a_Xu/detM;
      para_a_Xd = para_a_Xd/detM;
      para_a_Ad = para_a_Ad/detM;

      RecoF8Angle[l+1] = para_a_Xu * Fpl_XP[ii] + para_a_Xd * Fpl_XP[jj] + para_a_Ad * Fpl_XT[jj];
    }
    
  }

  RecoF8Angle[0] = RecoF8Angle[1];
  if(RecoF8Angle[0] < -500.)RecoF8Angle[0] = RecoF8Angle[2];
  
  //===== TOF ===========================================
  // [6] : 0 = F03-F07 | 1 = F08-F11
  //       2 = F03-F05 | 3 = F05-F07
  //       4 = F08-F09 | 5 = F09-F11
  TOF[0] = PLA_Tave[7]  - PLA_Tave[3] + TOFoffset[0];
  TOF[1] = PLA_Tave[11] - PLA_Tave[8] + TOFoffset[1];
  TOF[2] = PLA_Tave[5]  - PLA_Tave[3] + TOFoffset[2];
  TOF[3] = PLA_Tave[7]  - PLA_Tave[5] + TOFoffset[3];
  TOF[4] = PLA_Tave[9]  - PLA_Tave[8] + TOFoffset[4];
  TOF[5] = PLA_Tave[11] - PLA_Tave[9] + TOFoffset[5];

  TOF37  = TOF[0];
  TOF811 = TOF[1];
  TOF35  = TOF[2];
  TOF57  = TOF[3];
  TOF89  = TOF[4];
  TOF911 = TOF[5];

  //===== Length ==========
  // F3-F7
  if(-500<Delta[0])dLength[0] = TMat[6][4][5] * Delta[0];
  if(-500<Delta[1])dLength[0] = TMat[6][4][5] * Delta[1];
  // F8-F11
  if(-500<DeltaD7)dLength[1] = TMat[7][4][5] * DeltaD7;
  // F3-F5
  if(-500<Delta[0] && Fpl_XFlag[3])dLength[2] = TMat[0][4][5] * Delta[0] + TMat[0][4][1] * Fpl_XT[3]; 
  // F5-F7
  if(-500<Delta[1] && Fpl_XFlag[5])dLength[3] = TMat[1][4][5] * Delta[1] + TMat[1][4][1] * Fpl_XT[5]; 
  // F8-F9
  if(-500<DeltaD7 && -500<RecoF8Angle[0])dLength[4] = TMat[2][4][5] * DeltaD7 + TMat[2][4][1] * RecoF8Angle[0]; 
  // F9-F11
  if(-500<DeltaD8){
    if(Fpl_XFlag[9])dLength[5] = TMat[4][4][5] * DeltaD8 + TMat[4][4][1] * Fpl_XT[9]; 
    if(Fpl_XFlag[10])dLength[5] = TMat[5][4][5] * DeltaD8 + TMat[5][4][1] * Fpl_XT[10]; 
  }

  for(int i=0;i<6;i++)dLength[i] *= 0.001; // mm -> m

  dLength37  = dLength[0];
  dLength811 = dLength[1];
  dLength35  = dLength[2];
  dLength57  = dLength[3];
  dLength89  = dLength[4];
  dLength911 = dLength[5];

  // F3-F5
  if( abs(Delta35_2)<10. && Fpl_XFlag[3])dLength35_2 = TMat[0][4][5] * Delta35_2 + TMat[0][4][1] * Fpl_XT[3]; 
  // F5-F7
  if( abs(Delta57_2)<10. && abs(F5PPAC1_X)<400. )dLength57_2 = TMat[1][4][5] * Delta57_2 + TMat[1][4][1] * Fpl_XT[3]; 
  dLength35_2 *=0.001;
  dLength57_2 *=0.001;

  Beta35_2  = (Length0[2] - dLength35_2)/TOF35/Clight;
  Beta57_2  = (Length0[3] - dLength57_2)/TOF57/Clight;
  Gamma35_2 = 1. / sqrt( 1. - pow(Beta35_2 ,2.));
  Gamma57_2 = 1. / sqrt( 1. - pow(Beta57_2 ,2.));

  //===== Beta ============
  // Between Achromatic and Dispersive
  for(int m=0;m<6;m++)Beta[m] = ( Length0[m] - dLength[m] )/ TOF[m] / Clight;
  //  for(int m=0;m<6;m++)Beta[m] = ( Length0[m] + dLength[m] )/ TOF[m] / Clight;
  //  for(int m=0;m<6;m++)Beta[m] = ( Length0[m] )/ TOF[m] / Clight;
  Beta37     = Beta[0];
  Beta811    = Beta[1];
  Beta35[0]  = Beta[2];
  Beta57[0]  = Beta[3];
  Beta89[0]  = Beta[4];
  Beta911[0] = Beta[5];

  // Between Achromatic and Achromatic
  for(int m=0;m<2;m++){
    
    double temp_TOF,temp_Brho_up,temp_Brho_down,temp_L_up,temp_L_down;
    double temp_Beta_up,temp_Beta_down;
    switch(m){
    case 0:
      temp_TOF = TOF37;        // TOF37
      temp_Brho_up = Brho35;   // Brho35
      temp_Brho_down = Brho57; // Brho57
      temp_L_up   = Length0[2]; // Length@F3-F5
      temp_L_down = Length0[3]; // Length@F5-F7
      //      temp_L_up = Length0[2] + dLength[2]; // Length@F3-F5
      //      temp_L_down = Length0[3] + dLength[3]; // Length@F5-F7
      break;
    case 1:
      temp_TOF = TOF[1];        // TOF811
      temp_Brho_up = BrhoD7;   // Brho89 or Brho810
      temp_Brho_down = BrhoD8; // Brho911 or Brho1011
      temp_L_up   = Length0[4]; // Length@F8-F9
      temp_L_down = Length0[5]; // Length@F9-F11
      //      temp_L_up = Length0[4] + dLength[4]; // Length@F8-F9
      //      temp_L_down = Length0[5] + dLength[5]; // Length@F9-F11
      break;   
    }

    double para_alpha,para_p0,para_p1,para_k;
    para_alpha = temp_Brho_up / temp_Brho_down;
    para_p0 = temp_TOF * Clight / temp_L_down;
    para_p1 = temp_L_up / temp_L_down;
    para_k = sqrt( pow(para_p0 * para_p1,2.) + (pow(para_p0,2.)+pow(para_alpha,2.)-1.) * (pow(para_alpha,2.)-pow(para_p1,2.)) );

    temp_Beta_up   = (para_p0 * para_p1 + para_k) / (pow(para_p0,2.) + pow(para_alpha,2.) - 1.);
    temp_Beta_down = (para_p0 * para_p1 + para_k) / (para_p0 * para_k - para_p1 * (pow(para_alpha,2.) - 1.));

    /*
      if(m==0 && 252.5 < TOF37 && TOF37 < 253.5 && 72 < F7IC_Esum && F7IC_Esum < 76 && abs(Delta35)<0.1){
      cout << setprecision(5) 
      << temp_TOF << " " 
      << temp_Brho_up << " " << temp_Brho_down << " " 
      << temp_L_up << " " << temp_L_down << " " 
      << para_alpha << " " << para_p0 << " " << para_p1 << " " << para_k << " "
      << temp_Beta_up << " " << temp_Beta_down << endl;
      }
    */


    switch(m){
    case 0:
      Beta35[1] = temp_Beta_up;
      Beta57[1] = temp_Beta_down;
      break;
    case 1:
      Beta89[1] = temp_Beta_up;
      Beta911[1] = temp_Beta_down;
      break;
    }

  }
  
  //===== Gamma =======================================
  Gamma37  = 1. / sqrt( 1. - pow(Beta37 ,2.));
  Gamma811  = 1. / sqrt( 1. - pow(Beta811 ,2.));
  for(int m=0;m<2;m++){
    Gamma35[m]  = 1. / sqrt( 1. - pow(Beta35[m] ,2.));
    Gamma57[m]  = 1. / sqrt( 1. - pow(Beta57[m] ,2.));
    Gamma89[m]  = 1. / sqrt( 1. - pow(Beta89[m] ,2.));
    Gamma911[m] = 1. / sqrt( 1. - pow(Beta911[m],2.));
  }

  //===== AoQ ========================================
  AoQ37   = Brho57  * Clight / (Gamma37  * Beta37  * Mnucleon);
  AoQ811  = BrhoD7  * Clight / (Gamma37  * Beta37  * Mnucleon);
  for(int m=0;m<2;m++)AoQ35[m]  = Brho35 * Clight / (Gamma35[m]  * Beta35[m]  * Mnucleon);
  for(int m=0;m<2;m++)AoQ57[m]  = Brho57 * Clight / (Gamma57[m]  * Beta57[m]  * Mnucleon);
  for(int m=0;m<2;m++)AoQ89[m]  = BrhoD7 * Clight / (Gamma89[m]  * Beta89[m]  * Mnucleon);
  for(int m=0;m<2;m++)AoQ911[m] = BrhoD8 * Clight / (Gamma911[m] * Beta911[m] * Mnucleon);

  AoQ35_2  = Brho35_2 * Clight / (Gamma35_2  * Beta35_2  * Mnucleon);
  AoQ57_2  = Brho57_2 * Clight / (Gamma57_2  * Beta57_2  * Mnucleon);
  //  AoQ35_2  = Brho35_2 * Clight / (Gamma35[0]  * Beta35[0]  * Mnucleon);
  //  AoQ57_2  = Brho57_2 * Clight / (Gamma57[0]  * Beta57[0]  * Mnucleon);


  for(int m=0;m<4;m++){

    double temp_Beta,temp_dE;
    switch(m){
    case 0:
      temp_Beta = Beta57[1];
      temp_dE = F7IC_Esum;
      break;
    case 1:
      temp_Beta = Beta89[1];
      temp_dE = F8IC_Esum;
      break;
    case 2:
      //      temp_Beta = Beta89[1];
      temp_Beta = Beta911[1];
      temp_dE = F11IC_Esum;
      break;
    case 3:
      temp_Beta = Beta35[0];
      //      temp_Beta = Beta35[1];
      temp_dE = F3IC_Esum;
      break;
    }

    // ionpair = 2 * me / I * c^2
    double de_v;
    de_v 
      = TMath::Log(ionpair[m] * pow(temp_Beta,2.)) 
      - TMath::Log(1. - pow(temp_Beta,2.)) - pow(temp_Beta,2.);
    

    double temp_zet;
    temp_zet = Zcoef[m][0] * sqrt(temp_dE/de_v) * temp_Beta + Zcoef[m][1];

    switch(m){
    case 0: Zet7  = temp_zet; break;
    case 1: Zet8  = temp_zet; break;
    case 2: Zet11 = temp_zet; break;
    case 3: Zet3 = temp_zet; break;
    }

  }





  for(int m=0;m<2;m++){

    double temp_Beta,temp_dE;
    int mmm;
    switch(m){
    case 0:
      temp_Beta = Beta35[0];
      temp_dE = F3IC_Esum;
      break;
    case 1:
      temp_Beta = Beta57[0];
      temp_dE = F7IC_Esum;
      break;
    }

    // ionpair = 2 * me / I * c^2
    double de_v;
    de_v 
      = TMath::Log(ionpair_2[m] * pow(temp_Beta,2.)) 
      - TMath::Log(1. - pow(temp_Beta,2.)) - pow(temp_Beta,2.);
    

    double temp_zet;
    temp_zet = Zcoef_2[m][0] * sqrt(temp_dE/de_v) * temp_Beta + Zcoef_2[m][1];

    switch(m){
    case 0: Zet3_2  = temp_zet; break;
    case 1: Zet7_2  = temp_zet; break;
    }

  }




  /*  
  //===== Z =========================================

  de_v = TMath::Log(ionpair[0] * pow(Beta2[1][0][0],2.)) - 
  TMath::Log(1.-pow(Beta2[1][0][0],2.)) - pow(Beta2[1][0][0],2.);
    
  Z[0] = Z_calib[0][0] * (sqrt(IC_ESum[0]/de_v)) * Beta2[1][0][0] + Z_calib[1][0];
  */
  

}
