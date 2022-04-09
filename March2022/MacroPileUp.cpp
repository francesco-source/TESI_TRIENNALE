
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
     TFile *file2 = new TFile("PileUpResult.root","RECREATE");
     fileGeom->ls();
     filePileUp->ls();
     TTree* TGeomOut=(TTree*)fileGeom->Get("Tree;5");
     TTree* TPileUpOut=(TTree*)filePileUp->Get("Tree;3");
     TH1F *hSCTimeNoPileUp=
           new TH1F("SCTimeNoPileUp","SCTime without SCPileUp=true",100,0,200);
     TH1F *hSCTimePileUp=
           new TH1F("SCTimePileUp","SCTime ",100,0,200);
     TH1F *hSCChargePileUp= 
           new TH1F("SCCharge"," SCCharge ",100,0,30);
     TH1F *hSCChargeNoPileUp=
           new TH1F("SCChargeNoPileUP","SCCharge  without SCPileUp=true",100,0,30);
     TH1F *hTWChargePointPileUp= 
           new TH1F("TWPileup","TWCharge ",10,-1,10);
     TH1F *hTWChargeNoPointPileUp= 
           new TH1F("TWNoPileup","TWCharge without SCPileUp=true",10,-1,10);
  TH1F *hTWDe1Point= new TH1F("TWDe1Point","TWDe1Point ",100,0,100);
  TH1F *hTWDe1PointNoPileUp= new TH1F("TWDe1PointNoPileUP","TWDe1Point without SCPileUp=true",100,0,100);
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
           for(UInt_t j=0;j<TWDe1Point->size();j++){hTWDe1PointPileUp->Fill(TWDe1Point->at(j));
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

    hSCTimeNoPileUp->Write();
    hSCTimePileUp->Write(); 
    hSCChargePileUp->Write();  
    hSCChargeNoPileUp->Write();
    hTWChargePointPileUp ->Write();
    hTWChargeNoPointPileUp ->Write();
    hTWDe1Point->Write();
    hTWDe1PointNoPileUp->Write();
    hTWDe1PointPileUp->Write();
    hTWPoints->Write();
    file2->Close();     
 }
