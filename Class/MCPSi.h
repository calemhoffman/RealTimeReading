#ifndef MCPSI
#define MCPSI

#include "../Class/GenericPlane.h"

class MCPSi : public GenericPlane{
  RQ_OBJECT("MCPSi");
public:

  MCPSi();
  ~MCPSi();
  
  void          SetOthersHistograms();
  void          SetCanvasTitleDivision(TString titleExtra);
  virtual void  Fill(UInt_t * energy, ULong64_t * times);
  void          Draw();
  void          ClearHistograms();
  void          SetCanvasID(int canID) {printf("here");};
  
private:
  
  TH1F * hX;
  TH1F * hY;
  TH2F * hXY;

  TH1F * hXg;
  TH1F * hYg;
  TH2F * hXYg;
  TH2F * hXX; 
  TH2F * hYY;
  TH2F * hXE;
  TH2F * hYE;
  
  TH1F * hX1, * hX2, * hY1, * hY2;
  
  int chX1, chX2; // yellow, Red
  int chY1, chY2; // Blue, White
  
};

MCPSi::MCPSi(){
    
  //=========== ClassName and ClassID is for class identification in BoxScoreXY
  className = "MCPSi";
  classID = 1;
  location = "target";  //this is for database tag
  
  //=========== Channel Mask and rangeDE and rangeE is for GenericPlane
  ChannelMask = 0xb6; /// Channel enable mask, 0x01, only frist channel, 0xff, all channel
  
  rangeDE[0] =     0; /// min range for dE
  rangeDE[1] = 16000; /// max range for dE
  rangeE[0] =      0; /// min range for E
  rangeE[1] =  16000; /// max range for E
  rangeTime =    1000; /// range for Tdiff, nano-sec
  
  chE = 4;   chEGain = 1.0;
  chdE = 1;   chdEGain = 1.0;
  mode = 5; ///default channel Gain is equal
  
  NChannelForRealEvent = 4;
  
  //=========== custom histograms for MCPSi
  hX = NULL;
  hY = NULL;
  hXY = NULL;

  hXg = NULL;
  hYg = NULL;
  hXYg = NULL;
  
  hHit = NULL;
  
  hX1 = NULL;
  hX2 = NULL;
  hY1 = NULL;
  hY2 = NULL;
  
  hXX= NULL;
  hYY= NULL;
  hXE= NULL;
  hYE= NULL;
  
  // set MCP positions from dig channel
  chX1 = 2; // left 
  chX2 = 3; // right
  
  chY1 = 6; // top
  chY2 = 7; // bottom
  
  GenericPlane::SetChannelMask(0xffff);
  
}

MCPSi::~MCPSi(){
  
  delete hX;
  delete hY;
  delete hXY;
  
  delete hXg;
  delete hYg;
  delete hXYg;
  
  delete hHit;
  
  delete hX1;
  delete hX2;
  delete hY1;
  delete hY2;
  
}

void MCPSi::SetOthersHistograms(){
  
  int bin = 1000; //2cm / 40 bins = 0.5 mm / bin
  float labelSize = 0.04;
  
  float xMin = -1.1;
  float xMax =  1.1;
  float yMin = -1.1;
  float yMax =  1.1;
  
  hX = new TH1F("hX", "X; X[ch]; count", bin, xMin, xMax);
  hY = new TH1F("hY", "Y; Y[ch]; count", bin, yMin, yMax);  
  hXY  = new TH2F("hXY", "X-Y; X[ch]; Y[ch]", bin, xMin, xMax, bin, yMin, yMax);

  hXg = new TH1F("hXg", "X (cut1); X[ch]; count", bin, xMin, xMax);
  hYg = new TH1F("hYg", "Y (cut1); Y[ch]; count", bin, yMin, yMax);
  hXYg = new TH2F("hXYg", "X-Y (cut1); X[ch]; Y[ch]", bin, xMin, xMax, bin, yMin, yMax);
  
  hXX= new TH2F("hXX", "X1-X2; X[ch]; X[ch]", bin, 0, 16000, bin, 0, 16000);
  hYY= new TH2F("hYY", "Y1-Y2; Y[ch]; Y[ch]", bin, 0, 16000, bin, 0, 16000);
  hXE= new TH2F("hXE", "X-E; X[ch]; E[ch]", bin, 0, 16000, 2*bin, 2*xMin, 2*xMax);
  hYE= new TH2F("hYE", "Y-E; Y[ch]; E[ch]", bin, 0, 16000, 2*bin, 2*yMin, 2*yMax);
  
  hX->GetXaxis()->SetLabelSize(labelSize);
  hX->GetYaxis()->SetLabelSize(labelSize);
  
  hY->GetXaxis()->SetLabelSize(labelSize);
  hY->GetYaxis()->SetLabelSize(labelSize);
  
  hXY->GetXaxis()->SetLabelSize(labelSize);
  hXY->GetYaxis()->SetLabelSize(labelSize);

  hXg->SetLineColor(2);
  hYg->SetLineColor(2);
  hXYg->SetLineColor(2);

  hXY->SetMinimum(1);
  hXYg->SetMinimum(1);
  bin = bin*2.0;
  hX1 = new TH1F("hX1", Form("X1 LEFT (ch=%d)", chX1), bin, 100, 26000);
  hX2 = new TH1F("hX2", Form("X2 RIGHT (ch=%d)", chX2), bin, 100, 26000);
  hY1 = new TH1F("hY1", Form("Y1 TOP (ch=%d)", chY1), bin, 100, 26000);
  hY2 = new TH1F("hY2", Form("Y2 BOTTOM (ch=%d)", chY2), bin, 100, 26000);
  
  hdE->SetTitle("de");;
  hE->SetTitle("e");
  hE->SetBins(1000,0,8000);
  
  isHistogramSet = true;
  
  printf(" Histograms set \n");
  
  mode = 5;
  
}

void MCPSi::SetCanvasTitleDivision(TString titleExtra = ""){
 
  fCanvas->Clear();
  if (canID==0) {
    fCanvas->Divide(1,2);
    fCanvas->cd(1)->Divide(2,1); 
    fCanvas->cd(1)->cd(1)->SetLogz();
    fCanvas->cd(1)->cd(2)->Divide(2,2);
    fCanvas->cd(2)->Divide(2,1); 
    fCanvas->cd(2)->cd(1)->Divide(2,2);
    fCanvas->cd(2)->cd(2)->Divide(2,2);
  } else if (canID==1)
  {
    fCanvas->Divide(2,2);//ede 2D, 1Ds
  } else {
    fCanvas->Divide(3,3);//XY, X1D, Y1D, DE, E, DE-E
  }

}

void MCPSi::Draw(){
  
  if ( !isHistogramSet ) return;
  
  
  if (canID==0) {
    fCanvas->cd(1)->cd(1); hdEE->Draw("colz");
    if( numCut > 0 ){
      for( int i = 0; i < numCut; i++){
        cutG = (TCutG *) cutList->At(i);
        cutG->Draw("same");
      }
    }
    fCanvas->cd(1)->cd(2)->cd(1); hE->Draw();
    fCanvas->cd(1)->cd(2)->cd(2); hdE->Draw();
    ///fCanvas->cd(1)->cd(2)->cd(4); hTDiff->Draw(); line->Draw();
    ///fCanvas->cd(1)->cd(2)->cd(3); rateGraph->Draw("AP"); legend->Draw();
    fCanvas->cd(2)->cd(2)->cd(1); hX1->Draw("");
    fCanvas->cd(2)->cd(2)->cd(2); hX2->Draw("");
    fCanvas->cd(2)->cd(2)->cd(3); hY1->Draw("");
    fCanvas->cd(2)->cd(2)->cd(4); hY2->Draw("");
    fCanvas->cd(2)->cd(1)->cd(2); hHit->Draw("HIST");
    fCanvas->cd(2)->cd(1)->cd(3); gStyle->SetOptStat("neiour"); hX->Draw("");
    if( numCut > 0  ) hXg->Draw("same");
    fCanvas->cd(2)->cd(1)->cd(4); gStyle->SetOptStat("neiour"); hY->Draw("");
    if( numCut > 0  ) hYg->Draw("same");
    fCanvas->cd(2)->cd(1)->cd(1); 
    fCanvas->cd(2)->cd(1)->cd(1)->SetGrid(); 
    gStyle->SetOptStat("neiou"); hXY->Draw("colz"); 
    if( numCut > 0  ) hXYg->Draw("box same");
    fCanvas->cd(2)->cd(1)->cd(1)->SetLogz();
  } else if (canID==1) {
    fCanvas->cd(1); hdEE->Draw("colz");
    if( numCut > 0 ){
      for( int i = 0; i < numCut; i++){
        cutG = (TCutG *) cutList->At(i);
        cutG->Draw("same");
      }
    }
    fCanvas->cd(2); hdE->Draw();
    fCanvas->cd(4); hE->Draw();
  } else if (canID==2) { /////
    fCanvas->cd(1); hXY->Draw("col"); 
    if( numCut > 0  ) hXYg->Draw("same");
    fCanvas->cd(3); gStyle->SetOptStat("neiour"); hX->Draw("");
    if( numCut > 0  ) hXg->Draw("same");
    fCanvas->cd(2); gStyle->SetOptStat("neiour"); hY->Draw("");
    if( numCut > 0  ) hYg->Draw("same");
    fCanvas->cd(4); gStyle->SetOptStat("neiour"); hdE->Draw(""); 
    fCanvas->cd(5); gStyle->SetOptStat("neiour"); hE->Draw("");
    fCanvas->cd(6); gStyle->SetOptStat("neiour"); hdEE->Draw("col");
    fCanvas->cd(7); gStyle->SetOptStat("neiour");hTDiff->Draw();
 //   fCanvas->cd(9); gStyle->SetOptStat("neiour"); hYY->Draw("col");
 //   fCanvas->cd(8); gStyle->SetOptStat("neiour"); hXE->Draw("col");
 //   fCanvas->cd(7); gStyle->SetOptStat("neiour"); hYE->Draw("col");
  }
  
  fCanvas->Modified();
  fCanvas->Update();
  gSystem->ProcessEvents();
  
  mode = 5;
  
}


void MCPSi::Fill(UInt_t * energy, ULong64_t * times){
  //GenericPlane::Fill(energy);
  if ( !isHistogramSet ) return;
  int E = energy[chE];
  int dE = energy[chdE];//+ gRandom->Gaus(0, 500);
  float X = 0;
  float Y = 0;
  if( energy[chX1] !=0 && energy[chX2] !=0) {
    X = ((float)energy[chX1] - (float)energy[chX2])/((float)energy[chX1] + (float)energy[chX2]);
    hXX->Fill(energy[chX1],energy[chX2]);
    hXE->Fill(E,X);
  }
  if( energy[chY1] !=0 && energy[chY2] !=0 ) {
    Y = ((float)energy[chY1] - (float)energy[chY2])/((float)energy[chY1] + (float)energy[chY2]);
    hYY->Fill(energy[chY1],energy[chY2]);
    hYE->Fill(dE,X);
  }

  hX1->Fill(energy[chX1]);
  hX2->Fill(energy[chX2]);
  hY1->Fill(energy[chY1]);
  hY2->Fill(energy[chY2]);

 /// if (canID == 2) {
 ///   hX->Reset();
 ///   hY->Reset();
 ///   hXY->Reset();
 /// }
  if( X != 0.0 ) {hX->Fill(X); hE->Fill((float)E);}
  if( Y != 0.0 ) {hY->Fill(Y);   hdE->Fill((float)dE); }

  if (X != 0.0 && Y != 0.0) {
    hXY->Fill(X, Y);  
  }
  hdEE->Fill(E, dE);
  
  float totalE = dE * chdEGain + E * chEGain;
  hdEtotE->Fill(totalE, dE);
  
  if( numCut > 0  ){
    for( int i = 0; i < numCut; i++){
      cutG = (TCutG *) cutList->At(i);
      if( cutG->IsInside(E, dE)){
        countOfCut[i] += 1;
        if( i == 0 ) { ///&& X!= 0.0 && Y!=0.0) {
          hXYg->Fill(X,Y);
          hXg->Fill(X);
          hYg->Fill(Y);
        }
      }
    }
  }
  
}

void MCPSi::ClearHistograms(){
  
  GenericPlane::ClearHistograms();
  
  hX1->Reset();
  hX2->Reset();
  hY1->Reset();
  hY2->Reset();
  
  hX->Reset();
  hY->Reset();
  hXY->Reset();
  
  hXg->Reset();
  hYg->Reset();
  hXYg->Reset();
  
  hHit->Reset();
  
}
#endif
