//for TRIP2024Autumn, see https://docs.google.com/spreadsheets/d/1d11_88mObA7OXC8nCw2cu8NwEl2QN8_2JAX0d5anV0s/edit?gid=0#gid=0
#include "./bigrips_zds.h"

void rawdata_reset(){

  //===== module data =====
  for(int l=0;l<4;l++)for(int n=0;n<128;n++)for(int m=0;m<N_Mhit;m++)v1190[l][n][m] = -9999e6;
  for(int l=0;l<4;l++)for(int n=0;n<128;n++)for(int m=0;m<N_Mhit;m++)v1190raw[l][n][m] = -9999e6;
  for(int l=0;l<4;l++)for(int n=0;n<128;n++)v1190num[l][n] = 0;

  for(int l=0;l<2;l++)for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)v1290L[l][n][m] = -9999;
  for(int l=0;l<2;l++)for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)v1290Lraw[l][n][m] = -9999;
  for(int l=0;l<2;l++)for(int n=0;n<32;n++)v1290Lnum[l][n] = 0;
  for(int l=0;l<2;l++)for(int n=0;n<32;n++)v1290Lnum2[l][n] = 0;

  for(int l=0;l<2;l++)for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)v1290T[l][n][m] = -9999;
  for(int l=0;l<2;l++)for(int n=0;n<32;n++)for(int m=0;m<N_Mhit;m++)v1290Traw[l][n][m] = -9999;
  for(int l=0;l<2;l++)for(int n=0;n<32;n++)v1290Tnum[l][n] = 0;

  for(int n=0;n<32;n++)qdc[n] = -9999;
  for(int m=0;m<5;m++)for(int n=0;n<32;n++)adc[m][n] = -9999;

  //===== raw data ==========
  for(int n=0;n<12;n++)for(int m=0;m<4;m++)for(int l=0;l<4;l++)PPAC_Qraw[n][m][l] = -9999;
  for(int n=0;n<12;n++)for(int m=0;m<4;m++)for(int l=0;l<4;l++)PPAC_Traw[n][m][l] = -9999;
  for(int n=0;n<12;n++)for(int m=0;m<4;m++)PPAC_AQraw[n][m] = -9999;
  for(int n=0;n<12;n++)for(int m=0;m<4;m++)PPAC_ATraw[n][m] = -9999;

  for(int n=0;n<12;n++)for(int m=0;m<2;m++)PLA_Qraw[n][m]= -9999;
  for(int n=0;n<12;n++)for(int m=0;m<2;m++)PLA_Traw[n][m]=-99999;

  for(int m=0;m<2;m++)F8VETO_Qraw[m]= -9999;
  for(int m=0;m<2;m++)F8VETO_Traw[m]=-99999;

  for(int m=0;m<2;m++)F11Long_Qraw[m]= -9999;
  for(int m=0;m<2;m++)F11Long_Traw[m]=-99999;

  for(int l=0;l<12;l++)for(int m=0;m<2;m++)for(int n=0;n<N_Mhit;n++)PLA_MT[l][m][n] = -2e6;
  for(int l=0;l<12;l++)for(int m=0;m<2;m++)PLA_Mhit[l][m] = 0;
  for(int m=0;m<2;m++)for(int n=0;n<N_Mhit;n++)F8VETO_MT[m][n] = -2e6;
  for(int m=0;m<2;m++)F8VETO_Mhit[m] = 0;
  for(int m=0;m<2;m++)for(int n=0;n<N_Mhit;n++)F11Long_MT[m][n] = -2e6;
  for(int m=0;m<2;m++)F11Long_Mhit[m] = 0;
  for(int m=0;m<4;m++)for(int n=0;n<N_Mhit;n++)F8PPACA_MT[m][n] = -2e6;
  for(int m=0;m<4;m++)F8PPACA_Mhit[m] = 0;
  

  for(int m=0;m<6;m++)F3IC_Eraw[m] = -9999;
  for(int m=0;m<6;m++)F7IC_Eraw[m] = -9999;
  for(int m=0;m<3;m++)F8IC_Eraw[m] = -9999;
  for(int m=0;m<6;m++)F11IC_Eraw[m] = -9999;
  F3IC_Gas = -9999;
  F7IC_Gas = -9999;
  F8IC_Gas = -9999;
  F11IC_Gas = -9999;

  for(int m=0;m<2;m++)for(int n=0;n<N_Mhit;n++)F3PLA2_MT[m][n] = -2e6;
  for(int m=0;m<2;m++)for(int n=0;n<N_Mhit;n++)F5PLA2_MT[m][n] = -2e6;
  for(int m=0;m<2;m++)for(int n=0;n<N_Mhit;n++)F7PLA2_MT[m][n] = -2e6;
  for(int m=0;m<2;m++)F3PLA2_Mhit[m] = 0;
  for(int m=0;m<2;m++)F5PLA2_Mhit[m] = 0;
  for(int m=0;m<2;m++)F7PLA2_Mhit[m] = 0;

  for(int m=0;m<2;m++)F3PLA2_Traw[m]=-99999;
  for(int m=0;m<2;m++)F5PLA2_Traw[m]=-99999;
  for(int m=0;m<2;m++)F7PLA2_Traw[m]=-99999;

}

void moduledata_fill(int nj,int neve,int EFN,int dev,int fpl,int det,int mod,int geo,int edge,int ch,unsigned int buf){

  //===== Scaler in sva01 ========================================================================
  if( dev==BIGRIPS && fpl==F7 && det==B2SCALER && mod==C24 ){

    switch(ch){
    case 0:sva_Nevent[0] = buf;break;
    case 1:sva_10kclock[0] = buf;break;
    default:break;
    }

    if(nj==0 && neve==0)cout << "Scaler @sva01" << endl;
    return;
  }
  //===== Scaler in sva02 ========================================================================
  if( dev==ZeroDegree && fpl==F11VME && det==B2SCALER && mod==C24 ){

    switch(ch){
    case 0:sva_Nevent[1] = buf;break;
    case 1:sva_10kclock[1] = buf;break;
    default:break;
    }

    if(nj==0 && neve==0)cout << "Scaler @sva02" << endl;
    return;
  }
  //===== Time stamp in MPV =====================================================================
  //
  // ch0: lower 32 bit of time stamp
  // ch1: higher 16 bit of time stamp
  // ch2: 10k clock
  // ch3: Event number
  //

  if(det==TS && mod==8){

    int tempN;

    switch(EFN){
    case 61: tempN = 0;break; // brmpv01
    case 62: tempN = 1;break; // brmpv02
    case 64: tempN = 2;break; // brmpv04
    case 67: tempN = 3;break; // brmpv07
    case 68: tempN = 4;break; // brmpv08
    case 72: tempN = 5;break; // brmpv12
      //    case 70: tempN = 2;break; 
    case 80: break;
    default:
      //cout << "No assignment in MPV TS" << endl;
      return;
      break;
    }

    switch(ch){
    case 0: 
      mpv_ts0[tempN][0] = buf;
      break;
    case 1: 
      mpv_ts0[tempN][1] = buf;
      mpv_ts[tempN] = mpv_ts0[tempN][0] + (mpv_ts0[tempN][1] << 32);
      break;
    case 2: 
      mpv_10kclock[tempN] = buf;
      break;
    case 3: 
      mpv_Nevent[tempN] = buf;
      break;
    }
    
    if(nj==0 && neve==0)cout << Form("MPV TS @MPV%02d",EFN) << endl;
    return;
  }
  //===== V1190 ===============================================================================
  if( dev==BIGRIPS && fpl==B3F && det==PPACT && mod==V1190 && (geo==7||geo==8||geo==9) ){
    
    if(v1190num[geo-7][ch]<N_Mhit)v1190raw[geo-7][ch][v1190num[geo-7][ch]] = buf;
    v1190num[geo-7][ch]++;
    
    if(nj==0 && neve==0)cout << Form("V1190 (geo=%02d) for PPAC-T",geo) << endl;
    return;
  }
  if( dev==USERGR && fpl==F7 && det==SSDT && mod==V1190 && geo==0 ){

    if(edge==0){
      
      if(v1190num[3][ch]<N_Mhit)v1190raw[3][ch][v1190num[3][ch]] = buf;
      v1190num[3][ch]++;
    }
    
    if(nj==0 && neve==0)cout << Form("V1190 (geo=%02d) for Ge-T",geo) << endl;
    return;
  }
  //===== V1290 ===============================================================================
  if( dev==BIGRIPS && fpl==B3F && det==PLAT && mod==V1290 && (geo==6||geo==9) ){
    
    int temp_geo=0;
    switch(geo){
    case 6: temp_geo = 0;break;
    case 9: temp_geo = 1;break;
    }

    // Leading
    if(edge == 0){
      if(v1290Lnum[temp_geo][ch]<N_Mhit)v1290Lraw[temp_geo][ch][v1290Lnum[temp_geo][ch]] = buf;
      v1290Lnum[temp_geo][ch]++;
    }
    // Trailing
    if(edge == 1){
      if(v1290Tnum[temp_geo][ch]<N_Mhit)v1290Traw[temp_geo][ch][v1290Tnum[temp_geo][ch]] = buf;
      v1290Tnum[temp_geo][ch]++;
    }
    
    if(nj==0 && neve==0 && geo==6)cout << Form("V1290 (geo=%02d) for Plastic-T",geo) << endl;
    return;

  }
  //===== MQDC ================================================================================
  if( dev==BIGRIPS && fpl==B3F && det==PLAQ && mod==MQDC32 && geo==0 ){

    qdc[ch] = buf;

    if(nj==0 && neve==0)cout << "MQDC32 for Plastic-Q" << endl;
    return;
  }
  //===== MADC@F3 ================================================================================
  //  if( dev==USERGR && fpl==F3 && det==ICE && mod==MADC32 && geo==32 ){
  if( dev==USERGR && fpl==F3 && det==ICE && mod==MADC32 && geo==0 ){ // 2024/10/29 MADC ID changed by R. Taguchi

    adc[3][ch] = buf;

    if(nj==0 && neve==0)cout << "MADC32 for F3MUSIC" << endl;
    return;
  }
  //===== MADC@F7 ================================================================================
  if( dev==USERGR && fpl==F7 && det==ICE && mod==MADC32 && geo==0 ){

    adc[0][ch] = buf;

    if(nj==0 && neve==0)cout << "MADC32 for F7MUSIC" << endl;
    return;
  }
  //===== MADC@F7Ge ==============================================================================
  if( dev==USERGR && fpl==F7 && det==SSDE && mod==MADC32 && geo==0 ){

    adc[4][ch] = buf;

    if(nj==0 && neve==0)cout << "MADC32 for F7Ge" << endl;
    return;
  }
  if( dev==USERGR && fpl==F7 && det==SSDE && mod==MADC32 && geo==1 ){

    adc[5][ch] = buf;
    
    if(nj==0 && neve==0)cout << "MADC32 for F7Ge#2" << endl;
    return;
  }
  //===== F7Ge Scaler =========================================================================== 
  if( dev==57 && fpl==7 && det==63 && mod==36){
      
    F7Ge_Scaler[ch] = buf;
    /* cout << "hoge_s" << endl; */

    if(nj==0 && neve==0)cout << "Scaler for F7Ge" << endl;
    return;
  }
  //===== MADC@F8 ================================================================================
  if( dev==USERGR && fpl==F8 && det==ICE && mod==MADC32 && geo==32 ){

    adc[1][ch] = buf;

    if(nj==0 && neve==0)cout << "MADC32 for F8MUSIC" << endl;
    return;
  }
  //===== ADC@F11 ================================================================================
  if( dev==ZeroDegree && fpl==F11VME && det==ICE && mod==V785 && geo==31 ){

    adc[2][ch] = buf;

    if(nj==0 && neve==0)cout << "V785 for F11MUSIC" << endl;
    return;
  }
  //===== Not filled =============================================================================
  if(nj==0&&neve==0)cout << "!!!!!  Not Filled !!!!!" << endl;
}


void rawdata_fill(){

  //===== V1190/V1290 ==================
  v1190tref[0] = v1190raw[0][0][0]; // PPAC
  v1190tref[1] = v1190raw[1][0][0]; // PPAC
  v1190tref[2] = v1190raw[2][0][0]; // PPAC
  v1190tref[3] = v1190raw[3][16][0]; // Ge-T
  v1290tref[0] = v1290Lraw[0][0][0];
  v1290tref[1] = v1290Lraw[1][31][0];
  for(int l=0;l<4;l++)for(int m=0;m<128;m++)for(int n=0;n<N_Mhit;n++)v1190[l][m][n] = v1190raw[l][m][n]-v1190tref[l];
  for(int l=0;l<2;l++)for(int m=0;m<32 ;m++)for(int n=0;n<N_Mhit;n++)v1290L[l][m][n] = v1290Lraw[l][m][n]-v1290tref[l];
  for(int l=0;l<2;l++)for(int m=0;m<32 ;m++)for(int n=0;n<N_Mhit;n++)v1290T[l][m][n] = v1290Traw[l][m][n]-v1290tref[l];

  for(int l=0;l<2;l++)for(int m=0;m<32 ;m++)for(int n=0;n<N_Mhit;n++)if(v1290L[l][m][n]<3000.)v1290Lnum2[l][m]++;

  //===== PPAC Cathode =========================
                    //F0, F1, F2, F3, F4, F5, F6, F7, F8, F9,F10,F11
  int temp_Mid[12]  = {0,  0,  0,  0,  0,  1,  0,  2,  0,  0,  1,  0}; // Module geo7, 8, or 9
  int temp_CHid[12] = {0,  0,  0, 16,  0,112,  0, 16, 80, 96, 48,112}; // Channel

  for(int l=0;l<12;l++){
    if(Use_PPAC[l]){

      for(int m=0;m<4;m++)for(int n=0;n<4;n++){

	  for(int o=0;o<N_Mhit;o++){
	    if(   vgate_PPAC_T[l][m][n][0] < v1190raw[ temp_Mid[l] ][ 4*m+n + temp_CHid[l] ][o] 
	       && vgate_PPAC_T[l][m][n][1] > v1190raw[ temp_Mid[l] ][ 4*m+n + temp_CHid[l] ][o] ){
	      PPAC_Traw[l][m][n] = v1190[ temp_Mid[l] ][ 4*m+n + temp_CHid[l] ][o];
	      break;
	    }
	  }// for N_Mhit loop

	}// m loop

    }// if Use_PPAC
  }// for l

  //===== PPAC Anode =========================
                      //F0, F1, F2, F3, F4, F5, F6, F7, F8, F9,F10,F11
  int temp_Mid_a[12]  = {0,  0,  0,  0,  0,  1,  0,  2,  0,  0,  1,  0}; // Module geo7, 8, or 9
  int temp_CHid_a[12] = {0,  0,  0,  4,  0, 96,  0,  4, 64, 68, 44, 76}; // 

  for(int l=0;l<12;l++){
    if(Use_PPAC[l]){

      for(int n=0;n<4;n++){

	for(int o=0;o<N_Mhit;o++){
	  if(   vgate_PPAC_AT[l][n][0] < v1190raw[ temp_Mid_a[l] ][ n + temp_CHid_a[l] ][o] 
	     && vgate_PPAC_AT[l][n][1] > v1190raw[ temp_Mid_a[l] ][ n + temp_CHid_a[l] ][o] ){
	    PPAC_ATraw[l][n] = v1190[ temp_Mid_a[l] ][ n + temp_CHid_a[l] ][o];
	    //	    cout << l << " " << n << " " << vgate_PPAC_AT[l][n][0] <<  " " << vgate_PPAC_AT[l][n][1] << " " << v1190raw[ temp_Mid_a[l] ][ n + temp_CHid_a[l] ][o] << " " << v1190tref[0] << " " << v1190[ temp_Mid_a[l] ][ n + temp_CHid_a[l] ][o] << " " << PPAC_ATraw[l][n] << endl;
	    break;
	  }
	}// for N_Mhit loop

      }// n loop

    }// if Use_PPAC
  }// for l
   
  //===== Ge-T =========================
  for (int l=0; l<17; l++){
    for (int n=0; n<N_Mhit; n++) {
      F7Ge_Traw[l][n] = v1190[3][l][n];
    }
  }
  for (int n=0; n<32; n++) {
    F7Ge_Traw[8][n] = v1190[3][18][n]; // F7Pla-L
  }

  //===== Plastic T =============================
  //  int temp_CHid_plat[12]={0,0,0,16,0,18,0,20,22,28,0,24};
  int temp_CHid_plat[12]={0,0,0,12,0, 8,0,14,22,28,0,24};

  for(int l=0;l<12;l++){
    if(Use_PL[l]){

      for(int n=0;n<2;n++){

	for(int o=0;o<N_Mhit;o++){
	  if(   vgate_PLA_T[l][n][0] < v1290Lraw[0][ n + temp_CHid_plat[l] ][o] 
	     && vgate_PLA_T[l][n][1] > v1290Lraw[0][ n + temp_CHid_plat[l] ][o] ){
	    PLA_Traw[l][n] = v1290L[0][ n + temp_CHid_plat[l] ][o];
	    // to fill F*PLA2_Traw, directly set proper v1290L ch
      // now PLA_Traw[3], [5], and [7] is the same as F*PLA2_Traw
      PLA_Traw[3][n] = v1290L[0][ n + 16][o];
      PLA_Traw[5][n] = v1290L[0][ n + 18][o];
      PLA_Traw[7][n] = v1290L[0][ n + 20][o];
	    break;
	  }
	}// for N_Mhit loop

      }// n loop
  
    }// if Use_PPAC
  }// for l

  for(int n=0;n<2;n++){    
    for(int o=0;o<N_Mhit;o++){
      if(   vgate_F3PLA2_T[n][0] < v1290Lraw[0][ n + 16 ][o] 
	    && vgate_F3PLA2_T[n][1] > v1290Lraw[0][ n + 16 ][o] ){
	F3PLA2_Traw[n] = v1290L[0][ n + 16 ][o];
	break;
      }
    }// for N_Mhit loop
  }// n loop

  for(int n=0;n<2;n++){    
    for(int o=0;o<N_Mhit;o++){
      if(   vgate_F5PLA2_T[n][0] < v1290Lraw[0][ n + 18 ][o] 
	    && vgate_F5PLA2_T[n][1] > v1290Lraw[0][ n + 18 ][o] ){
	F5PLA2_Traw[n] = v1290L[0][ n + 18 ][o];
	break;
      }
    }// for N_Mhit loop
  }// n loop

  for(int n=0;n<2;n++){    
    for(int o=0;o<N_Mhit;o++){
      if(   vgate_F7PLA2_T[n][0] < v1290Lraw[0][ n + 20 ][o] 
	    && vgate_F7PLA2_T[n][1] > v1290Lraw[0][ n + 20 ][o] ){
	F7PLA2_Traw[n] = v1290L[0][ n + 20 ][o];
	break;
      }
    }// for N_Mhit loop
  }// n loop
  
  //===== F8VETO T ==================================
  for(int n=0;n<2;n++){
    for(int o=0;o<N_Mhit;o++){
      if(   vgate_F8VETO_T[n][0] < v1290Lraw[0][n+26][o] 
	 && vgate_F8VETO_T[n][1] > v1290Lraw[0][n+26][o] ){
	F8VETO_Traw[n] = v1290L[0][n+26][o];
	break;
      }
    }// for N_Mhit loop
  }// n loop

  //===== F11Long T ==================================
  for(int n=0;n<2;n++){
    for(int o=0;o<N_Mhit;o++){
      if(   vgate_F11Long_T[n][0] < v1290Lraw[0][n+30][o] 
	 && vgate_F11Long_T[n][1] > v1290Lraw[0][n+30][o] ){
	F11Long_Traw[n] = v1290L[0][n+30][o];
	break;
      }
    }// for N_Mhit loop
  }// n loop
  
  //===== Plastic Q =================================
  for(int n=0;n<2;n++){
    //    PLA_Qraw[3][n]   = qdc[n+0];
    PLA_Qraw[3][n]   = qdc[n+10];
    PLA_Qraw[5][n]   = qdc[n+2];
    PLA_Qraw[7][n]   = qdc[n+4];
    PLA_Qraw[8][n]   = qdc[n+6];
    PLA_Qraw[9][n]   = qdc[n+12];
    PLA_Qraw[11][n]  = qdc[n+8];
    F8VETO_Qraw[n]   = qdc[n+10];
    F11Long_Qraw[n]  = qdc[n+14];
  }

  //===== MUSIC ===================================
  for(int n=0;n<8;n++)F7Ge_Eraw[n] = adc[4][Ge_MADC1_ch[n]];
  for(int n=0;n<8;n++)F7Ge2_Eraw[n]= adc[5][Ge_MADC2_ch[n]];
  for(int n=0;n<6;n++)F3IC_Eraw[n]  = adc[3][n];
  for(int n=0;n<6;n++)F7IC_Eraw[n]  = adc[0][n];
  for(int n=0;n<3;n++)F8IC_Eraw[n]  = adc[1][n];
  for(int n=0;n<6;n++)F11IC_Eraw[n] = adc[2][n];
  F8IC_Gas = adc[1][4];


  //===== V1290 wide-range V1290 ==================
  for(int n=0;n<N_Mhit;n++){
    /*
      for(int m=0;m<2;m++)PLA_MT[ 3][m][n]  = v1290Lraw[0][m+16][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 5][m][n]  = v1290Lraw[0][m+18][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 7][m][n]  = v1290Lraw[0][m+20][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 8][m][n]  = v1290Lraw[0][m+22][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 9][m][n]  = v1290Lraw[0][m+28][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[11][m][n]  = v1290Lraw[0][m+24][n] * 0.024413;
      for(int m=0;m<2;m++)F8VETO_MT[m][n]   = v1290Lraw[0][m+26][n] * 0.024413;
      for(int m=0;m<2;m++)F11Long_MT[m][n]  = v1290Lraw[0][m+30][n] * 0.024413;
      for(int m=0;m<4;m++)F8PPACA_MT[m][n]  = v1290Lraw[0][m+ 4][n] * 0.024413;
      for(int m=0;m<2;m++)F3PLA2_MT[m][n]   = v1290Lraw[0][m+12][n] * 0.024413;
      for(int m=0;m<2;m++)F5PLA2_MT[m][n]   = v1290Lraw[0][m+ 8][n] * 0.024413;
      for(int m=0;m<2;m++)F7PLA2_MT[m][n]   = v1290Lraw[0][m+14][n] * 0.024413;
    */
      for(int m=0;m<2;m++)PLA_MT[ 3][m][n]  = v1290Lraw[0][m+12][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 5][m][n]  = v1290Lraw[0][m+ 8][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 7][m][n]  = v1290Lraw[0][m+14][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 8][m][n]  = v1290Lraw[0][m+22][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[ 9][m][n]  = v1290Lraw[0][m+28][n] * 0.024413;
      for(int m=0;m<2;m++)PLA_MT[11][m][n]  = v1290Lraw[0][m+24][n] * 0.024413;
      for(int m=0;m<2;m++)F8VETO_MT[m][n]   = v1290Lraw[0][m+26][n] * 0.024413;
      for(int m=0;m<2;m++)F11Long_MT[m][n]  = v1290Lraw[0][m+30][n] * 0.024413;
      for(int m=0;m<4;m++)F8PPACA_MT[m][n]  = v1290Lraw[0][m+ 4][n] * 0.024413;
      for(int m=0;m<2;m++)F3PLA2_MT[m][n]   = v1290Lraw[0][m+16][n] * 0.024413;
      for(int m=0;m<2;m++)F5PLA2_MT[m][n]   = v1290Lraw[0][m+18][n] * 0.024413;
      for(int m=0;m<2;m++)F7PLA2_MT[m][n]   = v1290Lraw[0][m+20][n] * 0.024413;

    /*
    for(int m=0;m<2;m++)PLA_MT[ 3][m][n]  = ( v1290Lraw[0][m+16][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)PLA_MT[ 5][m][n]  = ( v1290Lraw[0][m+18][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)PLA_MT[ 7][m][n]  = ( v1290Lraw[0][m+20][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)PLA_MT[ 8][m][n]  = ( v1290Lraw[0][m+22][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)PLA_MT[ 9][m][n]  = ( v1290Lraw[0][m+28][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)PLA_MT[11][m][n]  = ( v1290Lraw[0][m+24][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)F8VETO_MT[m][n]   = ( v1290Lraw[0][m+26][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<2;m++)F11Long_MT[m][n]  = ( v1290Lraw[0][m+30][n]- v1290tref[0] ) * 0.024413;
    for(int m=0;m<4;m++)F8PPACA_MT[m][n]  = ( v1290Lraw[0][m+ 4][n]- v1290tref[0] ) * 0.024413;
    */
  }

  /*
      for(int m=0;m<2;m++)PLA_Mhit[ 3][m]  = v1290Lnum[0][m+16];
      for(int m=0;m<2;m++)PLA_Mhit[ 5][m]  = v1290Lnum[0][m+18];
      for(int m=0;m<2;m++)PLA_Mhit[ 7][m]  = v1290Lnum[0][m+20];
      for(int m=0;m<2;m++)PLA_Mhit[ 8][m]  = v1290Lnum[0][m+22];
      for(int m=0;m<2;m++)PLA_Mhit[ 9][m]  = v1290Lnum[0][m+28];
      for(int m=0;m<2;m++)PLA_Mhit[11][m]  = v1290Lnum[0][m+24];
      for(int m=0;m<2;m++)F8VETO_Mhit[m]   = v1290Lnum[0][m+26];
      for(int m=0;m<2;m++)F11Long_Mhit[m]  = v1290Lnum[0][m+30];
      for(int m=0;m<4;m++)F8PPACA_Mhit[m]  = v1290Lnum[0][m+ 4];
  */
      for(int m=0;m<2;m++)PLA_Mhit[ 3][m]  = v1290Lnum[0][m+12];
      for(int m=0;m<2;m++)PLA_Mhit[ 5][m]  = v1290Lnum[0][m+ 8];
      for(int m=0;m<2;m++)PLA_Mhit[ 7][m]  = v1290Lnum[0][m+14];
      for(int m=0;m<2;m++)PLA_Mhit[ 8][m]  = v1290Lnum[0][m+22];
      for(int m=0;m<2;m++)PLA_Mhit[ 9][m]  = v1290Lnum[0][m+28];
      for(int m=0;m<2;m++)PLA_Mhit[11][m]  = v1290Lnum[0][m+24];
      for(int m=0;m<2;m++)F8VETO_Mhit[m]   = v1290Lnum[0][m+26];
      for(int m=0;m<2;m++)F11Long_Mhit[m]  = v1290Lnum[0][m+30];
      for(int m=0;m<4;m++)F8PPACA_Mhit[m]  = v1290Lnum[0][m+ 4];
      for(int m=0;m<2;m++)F3PLA2_Mhit[m]   = v1290Lnum[0][m+16];
      for(int m=0;m<2;m++)F5PLA2_Mhit[m]   = v1290Lnum[0][m+18];
      for(int m=0;m<2;m++)F7PLA2_Mhit[m]   = v1290Lnum[0][m+20];
  

}
