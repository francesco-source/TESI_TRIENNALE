#include "Functions.hpp"

void MSD(int choosefile = 4306) {
    gStyle->SetOptStat(2210);
    gStyle->SetOptFit(1111);
    TFile *fileGeom;
    TFile *filePileUp;
    TFile *MSDResult;
    TTree *TGeomOut;
    TTree *TPileUpOut;
    if (choosefile == 4313) {
        fileGeom = new TFile("ROOT-FILES/tree4313_newgeom_MAR2022.root");
        filePileUp = new TFile("ROOT-FILES/tree4313_pileup_MAR2022.root");
        MSDResult = new TFile("MSDResult4313.root", "RECREATE");
        TGeomOut = (TTree *)fileGeom->Get("Tree;1");
        TPileUpOut = (TTree *)filePileUp->Get("Tree;1");
    } else {
        fileGeom = new TFile("ROOT-FILES/tree4306_newgeom_MAR2022.root");
        filePileUp = new TFile("ROOT-FILES/tree4306_pileup_MAR2022.root");
        MSDResult = new TFile("MSDResult4306.root", "RECREATE");
        TGeomOut = (TTree *)fileGeom->Get("Tree;5");
        TPileUpOut = (TTree *)filePileUp->Get("Tree;3");
    }
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
    std::vector<std::unique_ptr<TH1F>> align;
   /* 0 */ align.push_back(std::unique_ptr<TH1F>(new TH1F("hBeamMSDXPoint","BeamMSD X Points",100,-1.5,2.5)));
   /* 1 */ align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDXPoint","MSD X Points",100,-1,2.5)));
   /* 2 */ align.push_back(std::unique_ptr<TH1F>(new TH1F("hBeamMSDYPoint","BeamMSD Y Points",100,-2,3)));
   /* 3 */ align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDYPoint","MSD Y Points",100,-2,1.5)));
   /* 4 */ align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDXPointAlign","MSD X Points dopo allineamento",100,-2,2)));
   /* 5 */ align.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDYPointAlign","MSD Y Points dopo allineamento",100,-2,2)));
   std::vector<std::unique_ptr<TH1F>> MSD_layerPoints;
   /* 0 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1-2","MSD.at(0)=1 cosa vede il secondo layer",25,0,25)));
   /* 1 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1-3","MSD.at(0)=1 cosa vede il terzo layer",25,0,25)));
   /* 2 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1-1-3","MSD.at(0)=1, MSD.at(1)=1, il terzo layer",25,0,25)));
   /* 3 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1-2!","MSD.at(0)=1, MSD.at(1)!=1, il secondo layer",25,0,25)));
   /* 4 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1-3!","MSD.at(0)=1, MSD.at(1)!=1, il terzo layer",25,0,25)));
   /* 5 */  MSD_layerPoints.push_back(std::unique_ptr<TH1F>(new TH1F("hMSDFirst1-!1-3","MSD.at(0)=1, MSD.at(1)=!1, il terzo layer",25,0,25)));
    std::vector<std::unique_ptr<TH1F>> MSD_layerEnergy;
    /* 0 */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hFirst-MSDEnergy2","MSD.at(0)=1 Energia MSD2",3000,0,3000)));
    /* 1 */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hFirst-MSDEnergy3","MSD.at(0)=1 Energia MSD3",3000,0,3000)));
    /* 2 */ MSD_layerEnergy.push_back(std::unique_ptr<TH1F>(new TH1F("hFirstSecond-MSDEnergy3","MSD->at(0)=1, MSD->at(1)=1,Energia MSD3",3000,0,3000)));
    double Xalign{0.8057-0.8836};
    double Yalign{0.2682-0.1917};
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
    UInt_t nentriesGeom = TGeomOut->GetEntries();
    Long64_t tGeomEntry = 0;
    Long64_t tPileUpEntry = 0;
    TGeomOut->SetBranchAddress("MSDPoints", &MSDPoints, &b_MSDPoints);
    TGeomOut->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
    TGeomOut->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
    TGeomOut->SetBranchAddress("TWDe2Point", &TWDe2Point, &b_TWDe2Point);
    TGeomOut->SetBranchAddress("TWChargePoint", &TWChargePoint,
                               &b_TWChargePoint);
    TGeomOut->SetBranchAddress("TWXPoint", &TWXPoint, &b_TWXPoint);
    TGeomOut->SetBranchAddress("TWYPoint", &TWYPoint, &b_TWYPoint);
    TGeomOut->SetBranchAddress("MSDDe1Point", &MSDDe1Point, &b_MSDDe1Point);
    TGeomOut->SetBranchAddress("MSDDe2Point", &MSDDe2Point, &b_MSDDe2Point);
    TPileUpOut->SetBranchAddress("SCPileup", &SCPileup, &b_SCPileup);
    TGeomOut->SetBranchAddress("Frag", &Frag, &b_Frag);
    TGeomOut->SetBranchAddress("MSDXPoint", &MSDXPoint, &b_MSDXPoint);
    TGeomOut->SetBranchAddress("MSDYPoint", &MSDYPoint, &b_MSDYPoint);
    TGeomOut->SetBranchAddress("BeamTGX", &BeamTGX, &b_BeamTGX);
    TGeomOut->SetBranchAddress("BeamTGY", &BeamTGY, &b_BeamTGY);
    TGeomOut->SetBranchAddress("BeamMSDX", &BeamMSDX, &b_BeamMSDX);
    TGeomOut->SetBranchAddress("BeamMSDY", &BeamMSDY, &b_BeamMSDY);
    ////////////////////////////////////////////////////////////////////////////
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

    for (UInt_t i = 0; i < nentriesGeom; ++i) {
        tGeomEntry = TGeomOut->LoadTree(i);
        b_MSDPoints->GetEntry(i);
        b_TWPoints->GetEntry(i);
        b_TWDe1Point->GetEntry(i);
        b_TWDe2Point->GetEntry(i);
        b_TWChargePoint->GetEntry(i);
        b_MSDDe1Point->GetEntry(i);
        b_MSDDe2Point->GetEntry(i);
        b_SCPileup->GetEntry(i);
        b_Frag->GetEntry(i);
        b_MSDXPoint->GetEntry(i);
        b_MSDYPoint->GetEntry(i);
        b_TWXPoint->GetEntry(i);
        b_TWYPoint->GetEntry(i);
        b_BeamTGX->GetEntry(i);
        b_BeamTGY->GetEntry(i);
        b_BeamMSDX->GetEntry(i);
        b_BeamMSDY->GetEntry(i);
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
        if(sum[i]==3 && (MSDPoints->at(0) == 1) &&
            (MSDPoints->at(1) == 1) && (MSDPoints->at(2) == 1)){
            align[0]->Fill(BeamMSDX);
            align[1]->Fill(MSDXPoint->at(1));
            align[2]->Fill(BeamMSDY);
            align[3]->Fill(MSDYPoint->at(1));
            align[4]->Fill(MSDYPoint->at(1)+Xalign);
            align[5]->Fill(MSDYPoint->at(1)+Yalign);
        }
        if(MSDPoints->size()>0){
           if(MSDPoints->at(0)==1 && MSDPoints->at(1)>=0 && MSDPoints->at(2)>=0){
           if(MSDDe1Point->at(0)>=1500 && MSDDe1Point->at(0)<=2500 ){
               MSD_layerPoints[0]->Fill(MSDPoints->at(1));
               MSD_layerPoints[1]->Fill(MSDPoints->at(2));
               if(MSDPoints->at(1)>1){
                   MSD_layerPoints[3]->Fill(MSDPoints->at(1));
               }
               if(MSDPoints->at(2)>1){
                   MSD_layerPoints[4]->Fill(MSDPoints->at(2));
               }
               if(MSDPoints->at(1)==1){
              MSD_layerPoints[2]->Fill(MSDPoints->at(2));
              if(MSDPoints->at(2)>1){
                  MSD_layerPoints[5]->Fill(MSDPoints->at(2));
              }  
           }
           }
         }
        }
        if (sum[i] == 3 && TWPoints == 1) {
            foot::Fill(TWChargePoint, h[13].get(), TWChargePoint, 8, var1);
            foot::Fill(TWChargePoint, h[19].get(), TWChargePoint, 8, var2);
            if (Frag == false) {
                foot::Fill(TWChargePoint, h[14].get(), TWChargePoint, 8, var1);
                foot::Fill(TWChargePoint, h[20].get(), TWChargePoint, 8, var2);
            }
        }

        if (TWPoints == 1 && Frag == false && (MSDPoints->at(0) == 1) &&
            (MSDPoints->at(1) == 1) && (MSDPoints->at(2) == 1)) {
            std::vector<std::vector<Float_t>> coordinates;
            std::vector<Float_t> fillCordinates;
            for (UInt_t j = 0; j < MSDXPoint->size(); ++j) {
                fillCordinates.push_back(MSDXPoint->at(j));
            }
            coordinates.push_back(fillCordinates);
            fillCordinates.clear();
            for (UInt_t j = 0; j < MSDYPoint->size(); ++j) {
                fillCordinates.push_back(MSDYPoint->at(j));
            }
            coordinates.push_back(fillCordinates);
            fillCordinates.clear();
            coordinates.push_back(MSDZ);
            if (foot::GeometryMSDTGLine(coordinates, counter3) == true) {
                foot::Fill(TWChargePoint, h[7].get(), TWChargePoint, 8,
                           TWDe1Point->at(0));
                foot::Fill(TWChargePoint, h[15].get(), TWChargePoint, 8, var1);
                foot::Fill(TWChargePoint, h[21].get(), TWChargePoint, 8, var2);
                counter3++;
                // data 3D visualisation////
                for (UInt_t j = 0; j < TWChargePoint->size(); ++j) {
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
            ////////////////////////////////////
            if (foot::BeamMSD_vs_MSDRealPoint(BeamMSDX, BeamMSDY, MSDXPoint, MSDYPoint)) {
                ++counter2;
            }
        }
    }
   // foot::GeometryPrimaryDraw(MSDX, MSDY, MSDX.size());
    h[8]->Add(h[6].get(), h[7].get(), 1, -1);
    h[9]->Add(h[5].get(), h[7].get(), 1, -1);
    /////////////////////////////////////////////////
    for (UInt_t j = 0; j < h.size(); ++j) {
        h[j]->Write();
    }
    for(UInt_t j=0;j<align.size();++j){
        align[j]->Fit("gaus");
        align[j]->Write();
    }
    for(UInt_t j=0;j<MSD_layerPoints.size();++j){
        MSD_layerPoints[j]->Write();
    }
    std::cout << counter2 << std::endl;
    // MSDResult->Close();
}
