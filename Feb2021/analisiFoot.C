#define analisiFoot_cxx
#include "analisiFoot.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "TLegend.h"
#include "TMath.h"
#include"TGraph.h"
#include "TMatrixD.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"
#include "THStack.h"

void analisiFoot::Loop()
{
//   In a ROOT session, you can do:
//      root> .L analisiFoot.C
//      root> analisiFoot t
//      root> t.GetEntry(12); // Fill t data members with entry number 12
//      root> t.Show();       // Show values of entry 12
//      root> t.Show(16);     // Read and show values of entry 16
//      root> t.Loop();       // Loop on all entries
//

//     This is the loop skeleton where:
//    jentry is the global entry number in the chain
//    ientry is the entry number in the current Tree
//  Note that the argument to GetEntry must be:
//    jentry for TChain::GetEntry
//    ientry for TTree::GetEntry and TBranch::GetEntry
//
//       To read only selected branches, Insert statements like:
// METHOD1:
//    fChain->SetBranchStatus("*",0);  // disable all branches
//    fChain->SetBranchStatus("branchname",1);  // activate branchname
// METHOD2: replace line
//    fChain->GetEntry(jentry);       //read all branches
//by  b_branchname->GetEntry(ientry); //read only this branch
   if (fChain == 0) return;
   TH1F *hTWLostEnergy[8];
hTWLostEnergy[0]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[1]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[2]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[3]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[4]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[5]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[6]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
hTWLostEnergy[7]= new TH1F("TWLostEnergy","Lost Energy TW",1000,0,70);
TH1F *hTWCahrge= new TH1F("TWLostEnergy","Lost Energy TW",10,0,8);
   Long64_t nbytes = 0, nb = 0;
      Long64_t nentries = fChain->GetEntriesFast();
      std::cout << " nentries in tree = " << nentries << std::endl;
    for(Int_t i=0;i<nentries;i++){
      Long64_t tentry= fChain->LoadTree(i);
      b_TWDe1Point->GetEntry(tentry);
      b_TWChargePoint->GetEntry(tentry);
      for(UInt_t j=0;j<TWDe1Point->size();++j){
       if(TWChargePoint->at(j)==1){hTWLostEnergy[0]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==2){hTWLostEnergy[1]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==3){hTWLostEnergy[2]->Fill(TWDe1Point->at(j));} 
      else if(TWChargePoint->at(j)==4){hTWLostEnergy[3]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==5){hTWLostEnergy[4]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==6){hTWLostEnergy[5]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==7){hTWLostEnergy[6]->Fill(TWDe1Point->at(j));}
      else if(TWChargePoint->at(j)==8){hTWLostEnergy[7]->Fill(TWDe1Point->at(j));}
      }}
      hTWLostEnergy[0]->SetLineColor(kYellow+2);
      hTWLostEnergy[1]->SetLineColor(kOrange);
      hTWLostEnergy[2]->SetLineColor(kRed);
      hTWLostEnergy[3]->SetLineColor(kPink);
      hTWLostEnergy[4]->SetLineColor(kMagenta);
      hTWLostEnergy[5]->SetLineColor(kViolet);
      hTWLostEnergy[6]->SetLineColor(kBlue);
      hTWLostEnergy[7]->SetLineColor(kGreen);
       THStack *hs = new THStack("TWLostEnergy","TWLostEnergy");
       for(int i=0;i<8;++i){
   hTWLostEnergy[i]->GetXaxis()->SetTitle("Energy Lost");
   hTWLostEnergy[i]->GetYaxis()->SetTitle("Events");
   //hTWLostEnergy[i]->Draw("SAME");
}
       for(int i=0;i<8;++i){
         hs->Add(hTWLostEnergy[i]);
       }
            
TCanvas *c1= new TCanvas();
gPad->SetLogy();
gPad->SetGrid();
hs->Draw();
hs->GetXaxis()->SetTitle("Energy lost");
hs->GetYaxis()->SetTitle("Events");
c1->Modified();
  
   /*for (Long64_t jentry=0; jentry<nentries;jentry++) {
      Long64_t ientry = LoadTree(jentry);

      //if (ientry < 0) break;
      //nb = fChain->GetEntry(jentry);   nbytes += nb;

      // if (Cut(ientry) < 0) continue;
   }*/
}
