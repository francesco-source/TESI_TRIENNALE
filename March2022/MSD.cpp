#include "Functions.hpp"
#include"TChain.h"
#include "TCut.h"
#include "TCutG.h"
template<typename T>
T Fitgaus(T *x,double_t* par){
    T xx =x[0];
    T val= par[0]*TMath::Gaus(xx+par[3],par[1],par[2]);
    return val;
    
}
void MSD(int choosefile = 4306) {

    gStyle->SetOptStat(1111);
    gStyle->SetOptFit(1111);
    TFile *fileGeom;
    TFile *filePileUp;
    TFile *MSDResult;
    TTree *TGeomOut;
    TTree *TPileUpOut;
    TChain *Chain;
    if (choosefile == 4313) {
        Chain= new TChain("Tree;1");
        Chain->Add("ROOT-FILES/tree4313_newgeom_MAR2022.root");
        fileGeom = new TFile("ROOT-FILES/tree4313_newgeom_MAR2022.root");
        filePileUp = new TFile("ROOT-FILES/tree4313_pileup_MAR2022.root");
        MSDResult = new TFile("MSDResult4313.root", "RECREATE");
        TGeomOut = (TTree *)fileGeom->Get("Tree;1");
        TPileUpOut = (TTree *)filePileUp->Get("Tree;1");
    } else {
        Chain= new TChain("Tree;4");
        Chain->Add("ROOT-FILES/tree4306_newgeom_MAR2022.root",577096);
        Chain->Add("ROOT-FILES/tree4307_newgeom_MAR2022.root",513372);
        fileGeom = new TFile("ROOT-FILES/tree4306_newgeom_MAR2022.root");
        filePileUp = new TFile("ROOT-FILES/tree4306_pileup_MAR2022.root");
        MSDResult = new TFile("MSDResult4306.root", "RECREATE");
        TGeomOut = (TTree *)fileGeom->Get("Tree;5");
        TPileUpOut = (TTree *)filePileUp->Get("Tree;3");
    }
    Chain->ls();
    fileGeom->ls();
    filePileUp->ls();
    std::vector<std::unique_ptr<TH1F>> h;
   /* 0 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDPoints", " Punti nel MSD", 10, 0, 10)));
   /* 1 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWPointDE1", " DE1 TW", 100, 0, 100)));
   /* 2 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWPointDE1o", " DE1  TWCharge=8", 100, 0, 100)));
   /* 3 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWPointClean", " DE1 persa con MSD==3 e 1 punto nel TW", 100, 0, 100)));
   /* 4 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWDE1MSD3TW1NoFrag", " DE1 TW MSD=3,TW=1,Frag=false", 100, 0, 100)));
   /* 5 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWDE1MSD3TW1NoFragOxigen", " DE1 TW MSD=3,TW=1,Frag=false,TWCharge=8", 100, 0, 100)));
   /* 6 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWDE1MSD3TW1FragOxigen"," DE1 TW MSD=3,TW=1,TWCharge=8", 100, 0, 100)));
   /* 7 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hGeometryOxigen", "DE1 TW MSD=3,Frag=0,TW=1,TWCharge=8,geometria", 100,0, 100)));
   /* 8 */ h.push_back(std::unique_ptr<TH1F>(new TH1F( "hAirFrag","hTWDE1MSD3TW1Oxigen-hGeometryOxigen", 100, 0, 100)));
   /* 9 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hAirFragMSDTW", "hTWDE1MSD3TW1NoFragOxigen-hGeometryOxigen",100, 0, 100)));
   /*10 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE1Points3", "DE1 MSD==3", 1000, 0, 10000)));
   /*11 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE1Points", "DE1 MSD", 1000, 0, 10000)));
   /*12 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE1Points3TW", "DE1 MSD==3 e TW=1", 1000, 0, 10000)));
   /*13 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE1Points3TWOssigeni", "DE1 MSD==3, TW=1, TWCharge=8", 1000, 0, 10000)));
   /*14 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE1Points3TWOssigeniNoFrag", "DE1 MSD==3, TW=1,TWCharge=8,Frag=false", 1000, 0, 10000)));
   /*15 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE1Points3TWOssigeniNoFragGeometry","DE1 MSD==3, TW=1,TWCharge=8,Frag=false, Geometry", 1000, 0, 10000)));
   /*16 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE2Points3", "DE2 MSD==3", 1000, 0, 15000)));
   /*17 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE2Points", "DE2 MSD", 1000, 0, 15000)));
   /*18 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE2Points3TW", "DE2 MSD==3 e TW=1", 1000, 0, 15000)));
   /*19 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE2Points3TWOssigeni", "DE2 MSD==3, TW=1, TWCharge=8", 1000, 0, 15000)));
   /*20 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDDE2Points3TWOssigeniNoFrag", "DE2 MSD==3, TW=1,TWCharge=8,Frag=false", 1000, 0, 15000)));
   /*21 */ h.push_back(std::unique_ptr<TH1F>(new TH1F( "hMSDDE2Points3TWOssigeniNoFragGeometry", "DE2 MSD==3, TW=1,TWCharge=8,Frag=false, Geometry", 1000, 0, 15000)));
   /*22 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hTWPointNoPileUP"," Energia persa vista dal TW senza pile up", 100, 0, 100)));
   /*23 */ h.push_back(std::unique_ptr<TH1F>(new TH1F( "hPointsMSDSawTWNo", "Quanti punti vede l'MSD quando il TW non vede nulla?", 20, 0, 20)));
   /*24 */ h.push_back(std::unique_ptr<TH1F>(new TH1F( "hEnergyMSDSawTWNo", "Che energia vede l'MSD quando il TW non vede nulla con Pile up?", 100, 0, 100)));
   /*25 */ h.push_back(std::unique_ptr<TH1F>(new TH1F("hPointsMSDSawFrag", "Quanti punti vede l'MSD quando il fascio primario frammenta", 20, 0, 20)));
    /* Allineamento *///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    std::vector<std::unique_ptr<TH1F>> align;
   /* 0 */align.push_back(std::unique_ptr<TH1F>(new TH1F("hBeamMSDXPoint","BeamMSD X Points",150*4,-2,3)));/* -2 3 ci sta*/
   /* 1 */align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDXPoint","MSD X Points",150*3,-2,3))); 
   /* 2 */align.push_back(std::unique_ptr<TH1F>(new TH1F("hBeamMSDYPoint","BeamMSD Y Points",150*4,-2,3)));
   /* 3 */align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDYPoint","MSD Y Points",150*4,-2,3)));
   /* 4 */align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDXPointAlign","MSD X Points dopo allineamento",150*4,-2,3)));
   /* 5 */align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDYPointAlign","MSD Y Points dopo allineamento",150*4,-2,3)));
   /* 6 */align.push_back(std::unique_ptr<TH1F>(new TH1F("Sottrazione X post allineamento","Sottrazione X post allineamento",150*4,-2,3)));
   /* 7 */align.push_back(std::unique_ptr<TH1F>(new TH1F("Sottrazione Y post allineamento","Sottrazione Y post allineamento",150*4,-2,3)));
   std::vector<std::unique_ptr<TH1F>> MSD_layerPoints;
   /* 0 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1","MSD primo Layer Points=1",25,0,25)));
   /* 1 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDSecond","MSD secondo Layer Points=1",25,0,25)));
   /* 2 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDThird","MSD terzo Layer Points=1",25,0,25)));
   /* 3 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1Filter","MSD primo Layer Points=1, filterDE",25,0,25)));
   /* 4 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDSecond1Filter","MSD secondo Layer Points=1, filterDE",25,0,25)));
   /* 5 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDThird1Filter","MSD terzo Layer Points=1, filterDE",25,0,25)));
   /* 6 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDTW_After_filters","MSD TW alfer filters",25,0,25)));
   /* 7 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDTW_witth_charge","MSD=3 TW=1 with charge",25,0,25)));
   std::vector<std::unique_ptr<TH2F>> BeamMSD;
    /* 0*/BeamMSD.push_back(std::unique_ptr<TH2F>( new TH2F("BeamMSDX-MSDX-Pre0","BeamMSDX-MSDXPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
     /* 1*/BeamMSD.push_back(std::unique_ptr<TH2F>( new TH2F("BeamMSDX-MSDX-Pre1","BeamMSDX-MSDXPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
     /* 2*/BeamMSD.push_back(std::unique_ptr<TH2F>( new TH2F("BeamMSDX-MSDX-Pre2","BeamMSDX-MSDXPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
    /* 3*/BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDY-MSDY-Pre0","BeamMSDY-MSDYPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
     /*4*/ BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDY-MSDY-Pre1","BeamMSDY-MSDYPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
     /*5*/ BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDY-MSDY-Pre2","BeamMSDY-MSDYPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
    /* 6*/BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDX-MSDX-Post","BeamMSDX-MSDXPoint post allienamento",150*4,-2,3,150*4,-2,3)));
    /* 7*/BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDY-MSDY-Post","BeamMSDY-MSDYPoint post allienamento",150*4,-2,3,150*4,-2,3)));
    /* 8*/BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDX-MSDX-Clean","BeamMSDX-MSDXPoint post allienamento puliti",150*4,-2,3,150*4,-2,3)));
    /* 9*/BeamMSD.push_back(std::unique_ptr<TH2F>(new  TH2F("BeamMSDY-MSDY-Clean","BeamMSDY-MSDYPoint post allienamento puliti",150*4,-2,3,150*4,-2,3)));
         /* 10*/BeamMSD.push_back(std::unique_ptr<TH2F>( new TH2F("BeamMSDX-MSDX-Pre2Energy","BeamMSDX-MSDXPoint pre allienamento",150*4,-2,3,150*4,-2,3)));
     /* 11*/ BeamMSD.push_back(std::unique_ptr<TH2F>(new TH2F("BeamMSDSENZA0.3-0.5","BeamMSDSENZA0.3-0.5",150*4,-2,3,150*4,-2,3)));
     TH1F *energy=new TH1F("energy","energycut",3000,0,3000);
     std::vector<std::unique_ptr<TH1F>> MSD_layerEnergy;
    /* 0 */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hFirstDE1","MSD.at(0)=1 Energia MSD2",3000,0,3000)));
    /* 1  */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hSecondDE1","MSD.at(0)=1 Energia MSD3",3000,0,3000)));
    /* 2  */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hThirdDE1","MSD->at(0)=1, MSD->at(1)=1,Energia MSD3",3000,0,3000)));
     /* 3 */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hFirstDE2","MSD.at(0)=1 Energia MSD2",3000,0,3000)));
    /* 4  */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hSecondDE2","MSD.at(0)=1 Energia MSD3",3000,0,3000)));
    /* 5  */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hThirdDE2","MSD->at(0)=1, MSD->at(1)=1,Energia MSD3",3000,0,3000)));
    /*  6 */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hThirdDE2TWChrge=8","MSD->at(0)=1, MSD->at(1)=1,Energia MSD3 TWCharge=8",3000,0,3000)));
       TCutG *cutg = new TCutG("CUTG",10);
       TH1F *counterOKTarget= new TH1F("counterOKTarget", "counterOKtarget",10,0,10);
       TH1F *counterNOTarget= new TH1F("counterNoTarget", "counterNOTarget",10,0,10);
       TH1F* counter1Point= new TH1F("counter1point", "counter1pont",10,0,10);
   cutg->SetVarX("BeamMSDX-MSDXPoint post allienamento");
   cutg->SetVarY("");
   cutg->SetTitle("Graph");
   cutg->SetFillStyle(1000);
   cutg->SetPoint(0,0.26335,0.437996);
   cutg->SetPoint(1,1.01578,1.23165);
   cutg->SetPoint(2,1.51335,1.62847);
   cutg->SetPoint(3,1.65898,1.38046);
   cutg->SetPoint(4,0.760922,0.437996);
   cutg->SetPoint(5,0.415049,0.214782);
   cutg->SetPoint(6,0.226942,0.251984);
   cutg->SetPoint(7,0.287621,0.462798);
   cutg->SetPoint(8,0.281553,0.437996);
   cutg->SetPoint(9,0.26335,0.437996);
    std::vector<int> *MSDPoints = 0;
    std::vector<double> *TWDe1Point = 0;
    std::vector<double> *TWDe2Point = 0;
    std::vector<int> *TWChargePoint = 0;
    std::vector<double> *MSDDe1Point = 0;
    std::vector<double> *MSDDe2Point = 0;
    std::vector<double> *MSDXPoint = 0;
    std::vector<double> *MSDYPoint = 0;
    std::vector<double> *TWXPoint = 0;
    std::vector<double> *TWYPoint = 0;
    Double_t BeamMSDX{0};
    Double_t BeamMSDY{0};
    Double_t BeamTGX;
    Double_t BeamTGY;
    Bool_t Frag;
    Bool_t SCPileup{0};
    Int_t TWPoints{0};
    TBranch *b_MSDPoints = 0;
    TBranch *b_TWPoints = 0;
    TBranch *b_TWDe1Point = 0;
    TBranch *b_TWDe2Point = 0;
    TBranch *b_TWXPoint = 0;
    TBranch *b_TWYPoint = 0;
    TBranch *b_TWChargePoint = 0;
    TBranch *b_MSDDe1Point = 0;
    TBranch *b_MSDDe2Point = 0;
    TBranch *b_BeamTGX = 0;
    TBranch *b_BeamTGY = 0;
    TBranch *b_SCPileup = 0;
    TBranch *b_Frag = 0;
    TBranch *b_MSDXPoint = 0;
    TBranch *b_MSDYPoint = 0;
    TBranch *b_BeamMSDX = 0;
    TBranch *b_BeamMSDY = 0;
    UInt_t nentriesGeom = Chain->GetEntries();
    Long64_t tGeomEntry = 0;
    Long64_t tPileUpEntry = 0;
    ////////////////////////////////////////////////////////////////////////////
    Chain->SetBranchAddress("MSDPoints", &MSDPoints, &b_MSDPoints);
    Chain->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
    Chain->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
    Chain->SetBranchAddress("TWDe2Point", &TWDe2Point, &b_TWDe2Point);
    Chain->SetBranchAddress("TWChargePoint", &TWChargePoint,
                               &b_TWChargePoint);
    Chain->SetBranchAddress("TWXPoint", &TWXPoint, &b_TWXPoint);
    Chain->SetBranchAddress("TWYPoint", &TWYPoint, &b_TWYPoint);
    Chain->SetBranchAddress("MSDDe1Point", &MSDDe1Point, &b_MSDDe1Point);
    Chain->SetBranchAddress("MSDDe2Point", &MSDDe2Point, &b_MSDDe2Point);
    TPileUpOut->SetBranchAddress("SCPileup", &SCPileup, &b_SCPileup);
    Chain->SetBranchAddress("Frag", &Frag, &b_Frag);
    Chain->SetBranchAddress("MSDXPoint", &MSDXPoint, &b_MSDXPoint);
    Chain->SetBranchAddress("MSDYPoint", &MSDYPoint, &b_MSDYPoint);
    Chain->SetBranchAddress("BeamTGX", &BeamTGX, &b_BeamTGX);
    Chain->SetBranchAddress("BeamTGY", &BeamTGY, &b_BeamTGY);
    Chain->SetBranchAddress("BeamMSDX", &BeamMSDX, &b_BeamMSDX);
    Chain->SetBranchAddress("BeamMSDY", &BeamMSDY, &b_BeamMSDY);
    ////////////////////////////////////////////////////////////////////////////
    /////////////////////////////////////////////////////////////////////////////
    Float_t MSDZ0 = 40;
    Float_t MSDZ1 = 45.15;
    Float_t MSDZ2 = 40 + 3.8 + 3.8 + 1.25;
    std::vector<std::vector<Float_t>> MSDX;
    std::vector<std::vector<Float_t>> MSDY;
    std::vector<Float_t> MSDZ = {MSDZ0, MSDZ1, MSDZ2};
    int counter = 0;
    int counter2 = 0;
    int counter3 = 0;
    int ausiliarsum = 0;
    std::vector<int> sum;
    auto Filling = [](std::vector<double> *v, TH1F *histo) {
        for (UInt_t l = 0; l < v->size(); ++l) {
            histo->Fill(v->at(l));
        }
    };
//////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
    for(UInt_t i=0;i<Chain->GetEntries();++i){
        Chain->GetEntry(i);
        TPileUpOut->GetEntry(i);
        if((TWPoints==1) &&(MSDPoints->at(0) == 1) &&
            (MSDPoints->at(1) == 1) && (MSDPoints->at(2) == 1) 
             && (TWChargePoint->at(0)==8)){
         align[0]->Fill(BeamMSDX);
         align[1]->Fill(MSDXPoint->at(1));
         align[2]->Fill(BeamMSDY);
         align[3]->Fill(MSDYPoint->at(1));
            }
    }
       TF1 *align0= new TF1 ("align0",Fitgaus<double>,-1,2.5,4);
        align0->SetParameters(5000,align[0]->GetMean(),align[0]->GetStdDev(),0);
        align[0]->Fit("align0","R");

        TF1 *align1= new TF1 ("align1",Fitgaus<double>,0,2,4);
        align1->SetParameters(6000,align[1]->GetMean(),align[1]->GetStdDev(),0);
        align[1]->Fit("align1");

        TF1 *align2= new TF1 ("align2",Fitgaus<double>,-2,3.,4);
         align2->SetParameters(10000,align[2]->GetMean(),align[2]->GetStdDev(),0);
        align[2]->Fit("align2");

        TF1 *align3= new TF1 ("align3",Fitgaus<double>,-0.7,0.8,4);
        align3->SetParameters(6000,align[3]->GetMean(),align[3]->GetStdDev(),0);
        align[3]->Fit("align3");
        double Xalign=(align0->GetParameter(1))-(align1->GetParameter(1));
        double Yalign=(align2->GetParameter(1))-(align3->GetParameter(1));
        foot::Xalign=Xalign;
        foot::Yalign=Yalign;
        //////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////
    for (UInt_t i = 0; i < Chain->GetEntries(); ++i) {
        Chain->GetEntry(i);
        TPileUpOut->GetEntry(i);
        
        ausiliarsum = 0;
        for (UInt_t j = 0; j < MSDPoints->size(); ++j) {
            ausiliarsum = ausiliarsum + MSDPoints->at(j);
        }
        sum.push_back(ausiliarsum);
       
        Filling(TWDe1Point, h[1].get());
        foot::Fill(TWDe1Point, h[2].get(), TWChargePoint, 8);
        if (sum[i] == 3 && TWPoints == 1) {
            Filling(TWDe1Point, h[3].get());
            foot::Fill(TWDe1Point, h[6].get(), TWChargePoint, 8);
            if (Frag == false) {
                Filling(TWDe1Point, h[4].get());
                foot::Fill(TWDe1Point, h[5].get(), TWChargePoint, 8);
            }
        }
        if (TWPoints <= 0 && SCPileup == true) {
            h[23]->Fill(sum[i]);
        }
        if (Frag == true) {
            h[25]->Fill(sum[i]);
        }
        double var1 = 0;
        double var2 = 0;
        if (sum[i] == 3) {
            for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
                var1 = var1 + MSDDe1Point->at(j);
            }
            for (UInt_t j = 0; j < MSDDe2Point->size(); ++j) {
                var2 = var2 + MSDDe2Point->at(j);
            }
        }
        if (sum[i] == 3) {
            h[10]->Fill(var1);
            h[16]->Fill(var2);
        }
        if (sum[i] == 3 && TWPoints == 1) {
            h[12]->Fill(var1);
            h[18]->Fill(var2);
        }
        if(sum[i]==3 &&(MSDPoints->at(0) == 1) &&
            (MSDPoints->at(1) == 1) && (MSDPoints->at(2) == 1) 
            && (TWPoints==1) && (TWChargePoint->at(0)==8)){
            align[4]->Fill(MSDXPoint->at(1)+Xalign);
            align[5]->Fill(MSDYPoint->at(1)+Yalign);
            BeamMSD[0]->Fill(BeamMSDX,MSDXPoint->at(0));
            BeamMSD[1]->Fill(BeamMSDX,MSDXPoint->at(1));
            BeamMSD[2]->Fill(BeamMSDX,MSDXPoint->at(2));
            BeamMSD[3]->Fill(BeamMSDY,MSDYPoint->at(0));
            BeamMSD[4]->Fill(BeamMSDY,MSDYPoint->at(1));
            BeamMSD[5]->Fill(BeamMSDY,MSDYPoint->at(2));
            BeamMSD[6]->Fill(BeamMSDX,MSDXPoint->at(1)+Xalign);
            BeamMSD[7]->Fill(BeamMSDY,MSDYPoint->at(1)+Yalign);
            if(BeamTGX<=-0.5 || BeamTGX>=0.5){
              BeamMSD[11]->Fill(BeamMSDX,MSDXPoint->at(1));
            }
            else if(BeamTGX>=-0.3 && BeamTGX<=0.3){
                    BeamMSD[11]->Fill(BeamMSDX,MSDXPoint->at(1));
            }
             if(!(cutg->IsInside(BeamMSDX,MSDXPoint->at(1)+Xalign))){
            energy->Fill(MSDDe1Point->at(1));
        }
            if(MSDDe1Point->at(0)<1300){
            BeamMSD[10]->Fill(BeamMSDX,MSDXPoint->at(1)+Xalign);
            }
        }
       /* if( TWPoints==1 && sum[i]==3 && MSDPoints->at(0)==1 && MSDPoints->at(1)==1 && MSDPoints->at(2)==1 && TWChargePoint->at(0)==(8)){
        MSD_layerEnergy[0]->Fill(MSDDe1Point->at(0));
        MSD_layerEnergy[1]->Fill(MSDDe1Point->at(1));
        MSD_layerEnergy[2]->Fill(MSDDe1Point->at(2));
         MSD_layerEnergy[3]->Fill(MSDDe2Point->at(0));
        }*/
       /*if(MSDPoints->size()>0){
           if(MSDPoints->at(0)==1){           
               MSD_layerPoints[0]->Fill(MSDPoints->at(0));
               MSD_layerEnergy[0]->Fill(MSDDe1Point->at(0));
                MSD_layerEnergy[3]->Fill(MSDDe2Point->at(0));
               if(MSDPoints->at(1)==1){
                MSD_layerPoints[1]->Fill(MSDPoints->at(1));
                MSD_layerEnergy[1]->Fill(MSDDe1Point->at(1)); 
                 MSD_layerEnergy[4]->Fill(MSDDe2Point->at(1)); 
                if(MSDPoints->at(2)==1){
                    MSD_layerPoints[2]->Fill(MSDPoints->at(2));
                    MSD_layerEnergy[2]->Fill(MSDDe1Point->at(2)); 
                     MSD_layerEnergy[5]->Fill(MSDDe2Point->at(2)); 
                     if( TWPoints==1 && TWChargePoint->at(0)==8 && MSDDe1Point->at(2)<1000){
                            MSD_layerEnergy[6]->Fill(MSDDe1Point->at(2));
                     }
                } 
               }
           }
           if(MSDPoints->at(0)==1 && MSDDe1Point->at(0)>=1000 && MSDDe2Point->at(1)>=1000){
           MSD_layerPoints[3]->Fill(MSDPoints->at(0));
        }
       
           if(MSDPoints->at(0)==1 && MSDPoints->at(1)>=0){           
           if(MSDDe1Point->at(0)>=1000 && MSDPoints->at(1)==1 && MSDDe1Point->at(1)>=1000 && MSDDe2Point->at(1)>=1000){
            MSD_layerPoints[4]->Fill(MSDPoints->at(1));
            if( MSDPoints->at(2)==1 && MSDDe1Point->at(2)>=1000 && MSDDe2Point->at(2)>=1000){
            MSD_layerPoints[5]->Fill(MSDPoints->at(2));
            if(TWPoints==1 && TWChargePoint->at(0)==8){
            MSD_layerPoints[6]->Fill(TWPoints);
            }
            }       
        }

       }
       if(MSDPoints->at(0)==1 && MSDPoints->at(1)==1 && MSDPoints->at(2)==1 && TWPoints==1 && TWChargePoint->at(0)==8){
            MSD_layerPoints[7]->Fill(TWPoints);
       }

       }*/
       
      /* if(TWPoints==1 && TWChargePoint->at(0)!=8 
       && MSDPoints->at(0)==1 
       && MSDPoints->at(1)==1 
       && MSDPoints->at(2)==1){
           if(MSDDe1Point->at(2)>=1500){
                MSD_layerPoints[0]->Fill(1);
           }
           if(MSDDe1Point->at(1)>=1500){
               if(MSDDe1Point->at(2)<1200){
                   MSD_layerPoints[1]->Fill(1);
               }
           }
           if(MSDDe1Point->at(0)>=1500){
               if(MSDDe1Point->at(1)<=1200){
                 MSD_layerPoints[2]->Fill(1);  
               }
           }     
       }*/
      /* if(MSDPoints->size()==3){
       if(MSDPoints->at(0)==1){
           MSD_layerPoints[3]->Fill(1);
           if(MSDPoints->at(1)==1){
             MSD_layerPoints[4]->Fill(1);  
             if(MSDPoints->at(2)==1){
                 MSD_layerPoints[5]->Fill(1);
           }
           }
           
       }
       }*/


       /* if (sum[i] == 3 && TWPoints == 1) {
            foot::Fill(TWChargePoint, h[13].get(), TWChargePoint, 8, var1);
            foot::Fill(TWChargePoint, h[19].get(), TWChargePoint, 8, var2);
            if (Frag == false) {
                foot::Fill(TWChargePoint, h[14].get(), TWChargePoint, 8, var1);
                foot::Fill(TWChargePoint, h[20].get(), TWChargePoint, 8, var2);
            }
        }*/

      /* if (TWPoints == 1 &&  (MSDPoints->at(0) == 1) &&
            (MSDPoints->at(1) == 1) && (MSDPoints->at(2) == 1)) {
            std::vector<std::vector<Float_t>> coordinates;
            std::vector<Float_t> fillCordinates;
            for (UInt_t j = 0; j < MSDXPoint->size(); ++j) {
                fillCordinates.push_back(MSDXPoint->at(j)+Xalign);
            }
            coordinates.push_back(fillCordinates);
            fillCordinates.clear();
            for (UInt_t j = 0; j < MSDYPoint->size(); ++j) {
                fillCordinates.push_back(MSDYPoint->at(j)+Yalign);
            }
            coordinates.push_back(fillCordinates);
            fillCordinates.clear();
            coordinates.push_back(MSDZ);
            counter1Point->Fill(1);
            if (foot::GeometryMSDTGLine(coordinates, counter3) == true) {
                counterOKTarget->Fill(1);

                foot::Fill(TWChargePoint, h[7].get(), TWChargePoint, 8,
                           TWDe1Point->at(0));
                foot::Fill(TWChargePoint, h[15].get(), TWChargePoint, 8, var1);
                foot::Fill(TWChargePoint, h[21].get(), TWChargePoint, 8, var2);
                counter3++;
             
                // data 3D visualisation////
               /* for (UInt_t j = 0; j < TWChargePoint->size(); ++j) {
                    std::vector<Float_t> x;
                    std::vector<Float_t> y;
                    if (TWChargePoint->at(j) == 8 && MSDX.size() < 100) {
                        x.push_back(BeamTGX);
                        x.push_back(MSDXPoint->at(0));
                        x.push_back(MSDXPoint->at(1));
                        x.push_back(MSDXPoint->at(2));
                        x.push_back(TWXPoint->at(0));
                        y.push_back(BeamTGY);
                        y.push_back(MSDYPoint->at(0));
                        y.push_back(MSDYPoint->at(1));
                        y.push_back(MSDYPoint->at(2));
                        y.push_back(TWYPoint->at(0));
                        MSDX.push_back(x);
                        MSDY.push_back(y);
                    }
                }
                //////////////////////////////
            }
            else{
                counterNOTarget->Fill(1);
            }
            ////////////////////////////////////
           
        }*/
        if(TWPoints == 1  && (MSDPoints->at(0) == 1) &&
            (MSDPoints->at(1) == 1) && (MSDPoints->at(2) == 1))
         if (foot::BeamMSD_vs_MSDRealPoint(BeamMSDX,BeamMSDY, MSDXPoint, MSDYPoint)
          && TWChargePoint->at(0)==8) {
              BeamMSD[8]->Fill(BeamMSDX,MSDXPoint->at(1));
              BeamMSD[9]->Fill(BeamMSDY,MSDYPoint->at(1));
                ++counter2;
            }
    }
    // foot::GeometryPrimaryDraw(MSDX, MSDY, MSDX.size());
        h[8]->Add(h[6].get(), h[7].get(), 1, -1);
        h[9]->Add(h[5].get(), h[7].get(), 1, -1);


        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
        //Da qui in poi fitto e scrivo su file/////////////////
        ///////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////
       for (UInt_t j = 0; j < h.size(); ++j) {
            h[j]->Write();
        }
        TF1 *align4= new TF1 ("align4",Fitgaus<double>,-0.7,0.7,4);
        align4->SetParameters(6000,align[4]->GetMean(),align[4]->GetStdDev(),0);
        align[4]->Fit("align4");

        TF1 *align5= new TF1 ("align5",Fitgaus<double>,-0.5,1,4);
        align5->SetParameters(6000,align[5]->GetMean(),align[5]->GetStdDev(),0);
        align[5]->Fit("align5");  
        
        align[6]->Add(align[0].get(),align[4].get(),1,-1);
        int entries6=0;
        for(int j=0;j<600;++j){
               entries6=entries6+abs(align[6]->GetBinContent(j));
        }
        align[6]->SetEntries(entries6);
        
        align[7]->Add(align[2].get(),align[5].get(),1,-1);
        int entries7=0;
         for(int j=0;j<600;++j){
               entries7=entries7+abs(align[7]->GetBinContent(j));
        }
        align[7]->SetEntries(entries7);

        for(UInt_t j=0;j<align.size();++j){
        align[j]->Write();
        }
        for(UInt_t j=0;j<BeamMSD.size();++j){
            BeamMSD[j]->Write();
        }

        for(UInt_t j=0;j<MSD_layerPoints.size();++j){
            MSD_layerPoints[j]->Draw();
        MSD_layerPoints[j]->Write();
        }
         for(UInt_t j=0;j<MSD_layerEnergy.size();++j){
        
        MSD_layerEnergy[j]->Write();
        }
        energy->Write();
        std::cout<<"Il numero di primari osservati dal BeamMonitor è : "<<
        align[0]->GetEntries()<<std::endl;
        std::cout <<"Il numero di primari post allineamento è :"<< 
        counter3 << std::endl;
        counterNOTarget->Write();
        counterOKTarget->Write();
        counter1Point->Write();
         //MSDResult->Close();
}
//fix parmeter


