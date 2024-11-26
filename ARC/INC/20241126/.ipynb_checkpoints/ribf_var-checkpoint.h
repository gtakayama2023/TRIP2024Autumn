const int Nfpl_PPAC = 12;
const int Nfpl_PLA = 12;
const int Nfpl_IC = 12;
const int N_Mhit = 5;

double inan=TMath::QuietNaN();

bool tgate[100];
Int_t Nevent;

//===== Raw data ==============================
Double_t Brho_NMR[8];
//===== Scaler in sva01/02 ===================
unsigned int sva_Nevent[2];
unsigned int sva_10kclock[2];
//===== TS in MPV61/64/70 =====================
//unsigned int mpv_Nevent[3];
//unsigned long long mpv_ts0[3][2];
//unsigned long long  mpv_ts[3];
////Double_t mpv_ts[3];
////Double_t mpv_10kclock[3];
//unsigned int  mpv_10kclock[3];

unsigned int mpv_Nevent[6];
unsigned long long mpv_ts0[6][2];
unsigned long long  mpv_ts[6];
//Double_t mpv_ts[3];
//Double_t mpv_10kclock[3];
unsigned int  mpv_10kclock[6];
//===== V1190 =================================
// [32]: Channel
// [10]: 1st/2nd/.../10th-hit event
long long v1190[3][128][N_Mhit];
long long v1190raw[3][128][N_Mhit];
Int_t v1190num[3][128];
long long v1190tref[3];
//===== V1290 =================================
// [32]: Channel
// [10]: 1st/2nd/.../10th-hit event
// Leading
long long v1290L[2][32][N_Mhit];
long long v1290Lraw[2][32][N_Mhit];
Int_t v1290Lnum[2][32];
Int_t v1290Lnum2[2][32];
// Trailing
long long v1290T[2][32][N_Mhit];
long long v1290Traw[2][32][N_Mhit];
Int_t v1290Tnum[2][32];
long long v1290tref[2];
//===== QDC ==================================
Int_t qdc[32];
//===== ADC ==================================
Int_t adc[6][32];

//===== Default DAQ ===========================
//===== PPAC ==================================
//===== Cathodes ==============================
// [Nfpl_PPAC]: Focal plane
// [4] : 1A/1B/2A/2B
// [4] : X1/Y1/X2/Y2
Int_t PPAC_Qraw[Nfpl_PPAC][4][4];
Int_t PPAC_Traw[Nfpl_PPAC][4][4];
//===== Anodes ================================
// [Nfpl_PPAC]: Focal plane
// [4] : 1A/1B/2A/2B
Int_t PPAC_AQraw[Nfpl_PPAC][4];
Int_t PPAC_ATraw[Nfpl_PPAC][4];
//===== Plastic ===============================
// [Nfpl_PLA]: Focal plane
// [2] : L/R
Int_t PLA_Qraw[Nfpl_PLA][2];
Int_t PLA_Traw[Nfpl_PLA][2];
Int_t PLA_QTCraw[Nfpl_PLA][2];
//Int_t PLA2_Qraw[Nfpl_PLA][2];
//Int_t PLA2_Traw[Nfpl_PLA][2];
//===== F8VETO ==========================
// [2] : L/R
Int_t F8VETO_Qraw[2];
Int_t F8VETO_Traw[2];
Int_t F8VETO_QTCraw[2];
//===== F11Long ==========================
// [2] : L/R
Int_t F11Long_Qraw[2];
Int_t F11Long_Traw[2];
Int_t F11Long_QTCraw[2];
//===== IC ====================================
// [6/3/6]: anode number
//Int_t IC_ERaw[Nfpl_IC][8];
//Int_t IC_Gas[Nfpl_IC];
Int_t F3IC_Eraw[6];
Int_t F7IC_Eraw[6];
Int_t F8IC_Eraw[3];
Int_t F11IC_Eraw[6];
Int_t F3IC_Gas;
Int_t F7IC_Gas;
Int_t F8IC_Gas;
Int_t F11IC_Gas;
//===== Ge ====================================
Int_t F7Ge_Eraw[32];
Int_t F7Ge2_Eraw[32];
Int_t F7Ge_Traw[32][4];
Int_t F7Ge_Scaler[32];

//===== Mhit TDC ========================
Double_t PLA_MT[Nfpl_PLA][2][N_Mhit];
Int_t PLA_Mhit[Nfpl_PLA][2];
Double_t F8VETO_MT[2][N_Mhit];
Int_t F8VETO_Mhit[2];
Double_t F11Long_MT[2][N_Mhit];
Int_t F11Long_Mhit[2];
Double_t F8PPACA_MT[4][N_Mhit];
Int_t F8PPACA_Mhit[4];


//===== Calibrated ============================
//===== PPAC ==================================
// ch -> ns
// [Nfpl_PPAC]: Focal plane
// [4] : 1A/1B/2A/2B
// [4] : X1/Y1/X2/Y2
Double_t PPAC_T[Nfpl_PPAC][4][4];
Double_t PPAC_AT[Nfpl_PPAC][4];
// flag whether PPAC is fired or not
bool PPAC_fT[Nfpl_PPAC][4][4];
bool PPAC_fAT[Nfpl_PPAC][4];
// ns -> mm
// [Nfpl_PPAC]: Focal plane
// [4] : 1A/1B/2A/2B
// [2] : X/Y
Double_t PPAC_Tsum[Nfpl_PPAC][4][2];
Double_t PPAC_Tdiff[Nfpl_PPAC][4][2];
// Position
// [Nfpl_PPAC]: Focal plane
// [4] : 1A/1B/2A/2B
Double_t X[Nfpl_PPAC][4];
Double_t Y[Nfpl_PPAC][4];
// flag whether position can be reconstructed or not
// [Nfpl_PPAC]: Focal plane
// [4] : 1A/1B/2A/2B
bool fX[Nfpl_PPAC][4];
bool fY[Nfpl_PPAC][4];
// Number of fired PPACs in each focal plane
// [Nfpl_PPAC]: Focal plane
// [3] : 0:all / 1:upstream / 2:downstream
Int_t Num_fPPAC_X[Nfpl_PPAC][3];
Int_t Num_fPPAC_Y[Nfpl_PPAC][3];
//===== Tracking ==============================
// [Nfpl_PPAC]: Focal Plane
// [4] : 1A/1B/2A/2B
Double_t Fpl_XA[Nfpl_PPAC]; // const Ax
Double_t Fpl_XB[Nfpl_PPAC]; // const Bx
Double_t Fpl_YA[Nfpl_PPAC]; // const Ay
Double_t Fpl_YB[Nfpl_PPAC]; // const By
Double_t Fpl_XR[Nfpl_PPAC][4]; // residual X
Double_t Fpl_YR[Nfpl_PPAC][4]; // residual Y
// at Z=0 (focus point)
Double_t Fpl_XP[Nfpl_PPAC];// X-Position
Double_t Fpl_XT[Nfpl_PPAC];// X-Theta   
Double_t Fpl_YP[Nfpl_PPAC];// Y-Position
Double_t Fpl_YT[Nfpl_PPAC];// Y-Theta   
// Flag
Bool_t Fpl_XFlag[Nfpl_PPAC];// XFlag
Bool_t Fpl_YFlag[Nfpl_PPAC];// XFlag
//===== Plastic ===============================
// [Nfpl_PLA]: Focal plane 
// [2] : L/R
Double_t PLA_Q[Nfpl_PLA][2];
Double_t PLA_T[Nfpl_PLA][2];
Double_t PLA_S[Nfpl_PLA][2]; // Slew corrected
// Q average
// [2] : 0 = Arithmetic average 1 = Geometric average
Double_t PLA_Qave[Nfpl_PLA][2];
// Q difference (L-R)
Double_t PLA_Qdiff[Nfpl_PLA];
// T average
Double_t PLA_Tave[Nfpl_PLA];
Double_t PLA_Save[Nfpl_PLA]; // Slew corrected
// T difference (L-R)
Double_t PLA_Tdiff[Nfpl_PLA];
Double_t PLA_Sdiff[Nfpl_PLA]; // Slew corrected
// QTC
Double_t PLA_QTC[Nfpl_PLA][2];
Double_t PLA_QTCave[Nfpl_PLA][2];
Double_t PLA_QTCdiff[Nfpl_PLA];
//===== F8VETO ================================
Double_t F8VETO_Q[2];
Double_t F8VETO_T[2];
Double_t F8VETO_Qave[2];
Double_t F8VETO_Qdiff;
Double_t F8VETO_Tave;
Double_t F8VETO_Tdiff;
Double_t F8VETO_QTC[2];
Double_t F8VETO_QTCave[2];
Double_t F8VETO_QTCdiff;
//===== F11Long ================================
Double_t F11Long_Q[2];
Double_t F11Long_T[2];
Double_t F11Long_Qave[2];
Double_t F11Long_Qdiff;
Double_t F11Long_Tave;
Double_t F11Long_Tdiff;
Double_t F11Long_QTC[2];
Double_t F11Long_QTCave[2];
Double_t F11Long_QTCdiff;
//===== Ion Chamber ===========================
// [6] : Anode
// calibrated
Double_t F3IC_E[6];
Double_t F7IC_E[6];
Double_t F8IC_E[3];
Double_t F11IC_E[6];
// arithmetic sum
Double_t F3IC_Esum;
Double_t F7IC_Esum;
Double_t F8IC_Esum;
Double_t F11IC_Esum;

//===== Brho ==================================
// [6] : 0 = F03-F05   1 = F05-F07   2 = F08-F09
//       3 = F08-F10   4 = F09-F11   5 = F10-F11
Double_t Delta[6];
Double_t Brho[6];
Double_t DeltaD7,DeltaD8;
Double_t BrhoD7,BrhoD8;
//===== Reconstructed angle @F8 ===============
// 0 = "1", if "1" is not valid, "2".
// 1 = from X(F8), X(F9), and A(F9)
// 2 = from X(F8), X(F10), and A(F10)
Double_t RecoF8Angle[3];
//===== TOF ===================================
// [6] : 0 = F03-F07 | 1 = F08-F11
//       2 = F03-F05 | 3 = F05-F07
//       4 = F08-F09 | 5 = F09-F11
Double_t TOF[6];
Double_t dLength[6];
Double_t Beta[6];

Double_t Delta35,Delta57,Delta89,Delta810,Delta911,Delta1011;
Double_t Brho35, Brho57, Brho89, Brho810, Brho911, Brho1011;
Double_t dLength37, dLength811, dLength35, dLength57, dLength89, dLength911;

Double_t TOF37,TOF811;
Double_t TOF35,TOF57,TOF89,TOF911;

// [2] : 0 = Derived directy
//       1 = Derived From F3-F7 or F8-F11
Double_t Beta37,Beta811;
Double_t Beta35[2],Beta57[2],Beta89[2],Beta911[2]; 
Double_t Gamma37,Gamma811;
Double_t Gamma35[2],Gamma57[2],Gamma89[2],Gamma911[2]; 

//===== A/Q ===================================
Double_t AoQ37,AoQ811;
Double_t AoQ35[2],AoQ57[2],AoQ89[2],AoQ911[2];
//===== Z =====================================
Double_t Zet3,Zet7,Zet8,Zet11;

//===== For F5 measurement ====================
Double_t dLength35_2,Beta35_2,Gamma35_2;
Double_t dLength57_2,Beta57_2,Gamma57_2;
Double_t F5PPAC1_X,F7PLA_Q2X;
Double_t Delta35_2,Delta57_2;
Double_t Brho35_2,Brho57_2;
Double_t AoQ35_2,AoQ57_2;
Double_t Zet3_2, Zet7_2;


Double_t F3PLA2_MT[2][N_Mhit],F5PLA2_MT[2][N_Mhit],F7PLA2_MT[2][N_Mhit];
Int_t F3PLA2_Mhit[2],F5PLA2_Mhit[2],F7PLA2_Mhit[2];
Int_t F3PLA2_Traw[2],F5PLA2_Traw[2],F7PLA2_Traw[2];
Double_t F3PLA2_T[2],F5PLA2_T[2],F7PLA2_T[2];
