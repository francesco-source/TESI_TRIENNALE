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
#include "TTree.h"
#include "TRandom.h"
#include "TStyle.h"
#include "THStack.h"
 
 void macro(){
     TFile* fileGeom= new TFile("ROOT-FILES/tree4306_newgeom_MAR2022.root");
     TFile* filePileUp= new TFile("ROOT-FILES/tree4306_pileup_MAR2022.root");
     fileGeom->ls();
     filePileUp->ls();
     TTree* TGeomOut=(TTree*)fileGeom->Get("Tree;5");
     TTree* TPileUpOut=(TTree*)filePileUp->Get("Tree;3");
     TH1F *hSCTimeNoPileUp=
           new TH1F("SCTimeNoPileUp","Start counter time without pile up",100,0,200);
     TH1F *hSCTimePileUp=
           new TH1F("SCTimePileUp","Start counter time with pile up",100,0,200);
     TH1F *hSCChargePileUp= 
           new TH1F("SCCharge"," Carica rilasciata nel start counter con pile up",100,0,30);
     TH1F *hSCChargeNoPileUp=
           new TH1F("SCChargeNoPileUP"," Carica rilasciata nel start counter senza pile up",100,0,30);
     TH1F *hTWChargePointPileUp= 
           new TH1F("TWPileup","TOF wall charge con pile up",10,-1,10);
     TH1F *hTWChargeNoPointPileUp= 
           new TH1F("TWNoPileup","TOF wall charge senza pile up",10,-1,10);
  TH1F *hTWDe1Point= new TH1F("TWDe1Point","TWDe1Point con pile up",100,0,100);
  TH1F *hTWDe1PointNoPileUp= new TH1F("TWDe1PointNoPileUP","TWDe1Point senza pile up",100,0,100);
  TH1F *hTWDe1PointPileUp= new TH1F("TWDe1PointPileUP","TWDe1Point  pile up",100,0,100);
  TH1F *hTWPoints=new TH1F("hTWPoints","Punti osservati dal TW in caso di avvenuto Pile UP",7,-2,5);
     Double_t SCCharge=0;//lo leggo da new Geom
     Double_t SCTime=0;//lo leggo da new Geom
     Bool_t SCPileup=false;//lo leggo d PileUpFile
    std::vector<int>     *TWChargePoint=0;
     std::vector<double>  *TWDe1Point=0;
      Int_t           TWPoints;
    TBranch        *b_SCCharge=0;   
    TBranch        *b_SCTime=0;   
    TBranch        *b_SCPileup=0;
    TBranch        *b_TWChargePoint=0; 
     TBranch        *b_TWDe1Point=0; 
     TBranch        *b_TWPoints=0;  
     int var=0;
    Int_t nentriesGeom=TGeomOut->GetEntries();
    Int_t nentriesPileUp=TPileUpOut->GetEntries();
    if(nentriesGeom!=nentriesPileUp){for(int i=0;;){}}
    TGeomOut->SetBranchAddress("SCCharge", &SCCharge, &b_SCCharge);
    TGeomOut->SetBranchAddress("SCTime", &SCTime, &b_SCTime);
    TPileUpOut->SetBranchAddress("SCPileup",&SCPileup,&b_SCPileup);
    TGeomOut->SetBranchAddress("TWChargePoint", &TWChargePoint, &b_TWChargePoint);
     TGeomOut->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
       TGeomOut->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
    Long64_t tGeomEntry=0;
    Long64_t tPileUpEntry=0;
    for(Int_t i=0;i<nentriesGeom;++i){
        tGeomEntry=TGeomOut->LoadTree(i);
        tPileUpEntry=TPileUpOut->LoadTree(i);
        b_SCCharge->GetEntry(tGeomEntry);
        b_SCTime->GetEntry(tGeomEntry);
        b_SCPileup->GetEntry(tPileUpEntry);
        b_TWChargePoint->GetEntry(tGeomEntry);
        b_TWDe1Point->GetEntry(tGeomEntry);
        b_TWPoints->GetEntry(tGeomEntry);
        if(SCPileup==false){
            hSCTimeNoPileUp->Fill(SCTime);
            hSCChargeNoPileUp->Fill(SCCharge);
            for(UInt_t j=0;j<TWChargePoint->size();++j){hTWChargeNoPointPileUp->Fill(TWChargePoint->at(j)); }
            for(UInt_t j=0;j<TWDe1Point->size();++j){hTWDe1PointNoPileUp->Fill(TWDe1Point->at(j));}
        } 
         
        //int counter=1;;
        if(SCPileup==true){         
           for(int j=0;j<TWDe1Point->size();j++){hTWDe1PointPileUp->Fill(TWDe1Point->at(j));
           var=var+1;
           std::cout<<var<<" ";
        
          }
         if(TWDe1Point->size()==0){
            var=var+1;
            std::cout<<var<<" ";
          }
          //std::cout<<TWDe1Point->size()<<std::endl;
          /*var=var+1;*/
           
          hTWPoints->Fill(TWPoints);  
        }
        hSCTimePileUp->Fill(SCTime);    
        hSCChargePileUp->Fill(SCCharge); 
        for(UInt_t j=0;j<TWChargePoint->size();++j){hTWChargePointPileUp->Fill(TWChargePoint->at(j));}
        for(UInt_t j=0;j<TWDe1Point->size();++j){hTWDe1Point->Fill(TWDe1Point->at(j));}
    }


    TCanvas *c= new TCanvas("c","Pile up= file pile up. Eventi= new Geom");

    c->Divide(2,2);
      c->cd(1);
    gPad->SetLogy();
    hSCTimeNoPileUp->GetXaxis()->SetTitle("Time");
      hSCTimeNoPileUp->GetYaxis()->SetTitle("Events");
    hSCTimeNoPileUp->Draw();

      c->cd(2);
    gPad->SetLogy();
     hSCTimePileUp->GetXaxis()->SetTitle("Time");
     hSCTimePileUp->GetYaxis()->SetTitle("Events");
     hSCTimePileUp->Draw();
    
    c->cd(3);
    gPad->SetLogy();
    hSCChargeNoPileUp->GetXaxis()->SetTitle("Charge");
     hSCChargeNoPileUp->GetYaxis()->SetTitle("Events");
      hSCChargeNoPileUp->Draw();
    c->cd(4);
    gPad->SetLogy();
    hSCChargePileUp->GetXaxis()->SetTitle("Charge");
     hSCChargePileUp->GetYaxis()->SetTitle("Events");
    hSCChargePileUp->Draw();

    TCanvas *c1=new TCanvas("c1","Pile up= file pile up. Eventi= new Geom");
    c1->Divide(2,2);
      c1->cd(1);
       gPad->SetLogy();
       hTWChargeNoPointPileUp->Draw();
      hTWChargeNoPointPileUp->GetXaxis()->SetTitle("Charge");
      hTWChargeNoPointPileUp->GetYaxis()->SetTitle("Events");

      c1->cd(2);
       gPad->SetLogy();
       hTWChargePointPileUp->GetXaxis()->SetTitle("Charge");
      hTWChargePointPileUp->GetYaxis()->SetTitle("Events");
       hTWChargePointPileUp->Draw();
     
       hTWDe1Point->SetLineColor(kBlue);
       hTWDe1PointNoPileUp->SetLineColor(kRed);

      c1->cd(3);
      gPad->SetLogy();
      hTWDe1PointNoPileUp->GetXaxis()->SetTitle("dE/dx");
      hTWDe1PointNoPileUp->GetYaxis()->SetTitle("Events");
      hTWDe1PointNoPileUp->Draw();
      c1->cd(4);
      gPad->SetLogy();
       hTWDe1Point->GetXaxis()->SetTitle("dE/dx");
      hTWDe1Point->GetYaxis()->SetTitle("Events");
      hTWDe1Point->Draw();

      TCanvas *c2=new TCanvas("c2","Pile up= file pile up. Eventi= new Geom");
      c2->Divide(3);
      c2->cd(1);
      gPad->SetLogy();
      hTWDe1Point->Draw();
      
       c2->cd(2);
        gPad->SetLogy();
       hTWDe1PointPileUp->Draw();

       c2->cd(3);
      gPad->SetLogy();
      hTWDe1Point->Draw();
      hTWDe1PointPileUp->Draw("SAME");


      TCanvas *c3=new TCanvas("c3","Pile up= file pile up. Eventi= new Geom");

      hTWPoints->Draw();

      c->Print("Immagini/Pile_up_time_and_charge_Start_Counter.pdf");
      c1->Print("Immagini/Pile_Up_TW.pdf");
      c2->Print("Immagini/TWPoints confronto con Pile up.pdf");
      c3->Print("Immagini/Punti osservati dal TW in casp di avvenuto Pile UP.pdf");