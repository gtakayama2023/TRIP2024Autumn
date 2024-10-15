void MakeTransPlot1D(TH1 *hin,TH1 *hout,TGraphErrors *gr){

  Int_t nbin =  hin->GetNbinsX();

  if(nbin != hout->GetNbinsX()){
    cout << "ribf_transmission.h: The number of bins is not the same, quit." << endl;
    return;
  }

  //  Double_t valx[nbin],errx[nbin],valy[nbin],erry[nbin];
  Double_t nin,nout,valx,valy,erry;
  Double_t xmin,xmax;

  xmin = hin->GetBinCenter(0);
  xmax = hin->GetBinCenter(nbin+1);
  
  for(int j=0;j<nbin;j++){

    valx = hin->GetBinCenter(j+1);
    nin  = hin-> GetBinContent(j+1);
    nout = hout->GetBinContent(j+1);

    //    if(hin->GetBinContent(j+1)>0){
    //    if(hin->GetBinContent(j+1)>0 || hin->GetBinContent(j+1) != hout->GetBinContent(j+1)){
    if(nin > 0 && (int)nin != (int)nout ){
      


      valy = nout / nin;
      erry = sqrt( nout * (1. - valy) ) / nin;

    }else{
      valy = -0.1;
      erry = 0.;
    }

    gr->SetPoint(j,valx,valy);
    gr->SetPointError(j,0,erry);

    /*
    if(valy==1){
      cout << valx << " " << valy << " " << nin << " " << nout << endl;
    }
    */
  }
  

  gr->GetXaxis()->SetLimits(xmin,xmax);

}
