
#include "Functions.cpp"
#include "Functions.hpp"
void MSD(int choosefile=4306) {
    TFile *fileGeom ;
    TFile *filePileUp ;
    TFile *MSDResult;
    TTree *TGeomOut ;
     TTree *TPileUpOut;
    if(choosefile==4313){
     fileGeom = new TFile("ROOT-FILES/tree4313_newgeom_MAR2022.root");
    filePileUp = new TFile("ROOT-FILES/tree4313_pileup_MAR2022.root");   
    MSDResult = new TFile("MSDResult4313.root", "RECREATE");
    TGeomOut = (TTree *)fileGeom->Get("Tree;1");
    TPileUpOut = (TTree *)filePileUp->Get("Tree;1");
    }
    else {
    fileGeom = new TFile("ROOT-FILES/tree4306_newgeom_MAR2022.root");
    filePileUp = new TFile("ROOT-FILES/tree4306_pileup_MAR2022.root");
    MSDResult = new TFile("MSDResult4306.root", "RECREATE");
    TGeomOut = (TTree *)fileGeom->Get("Tree;5");
    TPileUpOut = (TTree *)filePileUp->Get("Tree;3");
    }
    fileGeom->ls();
    filePileUp->ls();
    std::vector<TH1F *> h(26);
    h[0] = new TH1F("hMSDPoints", " Punti nel MSD", 10, 0, 10);
    h[1] = new TH1F("hTWPointDE1", " DE1 TW", 100, 0, 100);
    h[2] = new TH1F("hTWPointDE1o", " DE1  TWCharge=8", 100, 0, 100);
    h[3] = new TH1F("hTWPointClean", " DE1 persa con MSD==3 e 1 punto nel TW",
                    100, 0, 100);
    h[4] = new TH1F("hTWDE1MSD3TW1NoFrag", " DE1 TW MSD=3,TW=1,Frag=false", 100,
                    0, 100);
    h[5] = new TH1F("hTWDE1MSD3TW1NoFragOxigen",
                    " DE1 TW MSD=3,TW=1,Frag=false,TWCharge=8", 100, 0, 100);
    h[6] = new TH1F("hTWDE1MSD3TW1FragOxigen", " DE1 TW MSD=3,TW=1,TWCharge=8",
                    100, 0, 100);
    h[7] =
        new TH1F("hGeometryOxigen",
                 "DE1 TW MSD=3,Frag=0,TW=1,TWCharge=8,geometria", 100, 0, 100);
    h[8] = new TH1F("hAirFrag", "hTWDE1MSD3TW1Oxigen-hGeometryOxigen", 100, 0,
                    100);
    h[9] = new TH1F("hAirFragMSDTW",
                    "hTWDE1MSD3TW1NoFragOxigen-hGeometryOxigen", 100, 0, 100);
    h[10] = new TH1F("hMSDDE1Points3", "DE1 MSD==3", 1000, 0, 10000);
    h[11] = new TH1F("hMSDDE1Points", "DE1 MSD", 1000, 0, 10000);
    h[12] = new TH1F("hMSDDE1Points3TW", "DE1 MSD==3 e TW=1", 1000, 0, 10000);
    h[13] = new TH1F("hMSDDE1Points3TWOssigeni", "DE1 MSD==3, TW=1, TWCharge=8",
                     1000, 0, 10000);
    h[14] = new TH1F("hMSDDE1Points3TWOssigeniNoFrag",
                     "DE1 MSD==3, TW=1,TWCharge=8,Frag=false", 1000, 0, 10000);
    h[15] = new TH1F("hMSDDE1Points3TWOssigeniNoFragGeometry",
                     "DE1 MSD==3, TW=1,TWCharge=8,Frag=false, Geometry", 1000,
                     0, 10000);
    h[16] = new TH1F("hMSDDE2Points3", "DE2 MSD==3", 1000, 0, 15000);
    h[17] = new TH1F("hMSDDE2Points", "DE2 MSD", 1000, 0, 15000);
    h[18] = new TH1F("hMSDDE2Points3TW", "DE2 MSD==3 e TW=1", 1000, 0, 15000);
    h[19] = new TH1F("hMSDDE2Points3TWOssigeni", "DE2 MSD==3, TW=1, TWCharge=8",
                     1000, 0, 15000);
    h[20] = new TH1F("hMSDDE2Points3TWOssigeniNoFrag",
                     "DE2 MSD==3, TW=1,TWCharge=8,Frag=false", 1000, 0, 15000);
    h[21] = new TH1F("hMSDDE2Points3TWOssigeniNoFragGeometry",
                     "DE2 MSD==3, TW=1,TWCharge=8,Frag=false, Geometry", 1000,
                     0, 15000);
    h[22] = new TH1F("hTWPointNoPileUP",
                     " Energia persa vista dal TW senza pile up", 100, 0, 100);
    h[23] = new TH1F("hPointsMSDSawTWNo",
                     "Quanti punti vede l'MSD quando il TW non vede nulla?", 20,
                     0, 20);
    h[24] = new TH1F(
        "hEnergyMSDSawTWNo",
        "Che energia vede l'MSD quando il TW non vede nulla con Pile up?", 100,
        0, 100);
    h[25] =
        new TH1F("hPointsMSDSawFrag",
                 "Quanti punti vede l'MSD quando il fascio primario frammenta",
                 20, 0, 20);
    std::vector<int> *MSDPoints = 0;
    std::vector<double> *TWDe1Point = 0;
    std::vector<double> *TWDe2Point = 0;
    std::vector<int> *TWChargePoint = 0;
    std::vector<double> *MSDDe1Point = 0;
    std::vector<double> *MSDDe2Point = 0;
    std::vector<double> *MSDXPoint = 0;
    std::vector<double> *MSDYPoint = 0;
    std::vector<double>  *TWXPoint=0;
    std::vector<double>  *TWYPoint=0;
    Double_t        BeamTGX;
   Double_t        BeamTGY;
    Bool_t Frag;
    Bool_t SCPileup = 0;
    Int_t TWPoints = 0;
    TBranch *b_MSDPoints = 0;
    TBranch *b_TWPoints = 0;
    TBranch *b_TWDe1Point = 0;
    TBranch *b_TWDe2Point = 0;
    TBranch *b_TWXPoint=0;   //!
    TBranch *b_TWYPoint=0; 
    TBranch *b_TWChargePoint = 0;
    TBranch *b_MSDDe1Point = 0;
    TBranch *b_MSDDe2Point = 0;
     TBranch        *b_BeamTGX=0;   //!
   TBranch        *b_BeamTGY=0;
    TBranch *b_SCPileup = 0;
    TBranch *b_Frag = 0;
    TBranch *b_MSDXPoint = 0;
    TBranch *b_MSDYPoint = 0;
    Float_t MSDZ0 = 40;
    Float_t MSDZ1 = 40 + 3.8;
    Float_t MSDZ2 = 40 + 3.8 + 3.8;
    std::vector<std::vector<Float_t>> MSDX;
    std::vector<std::vector<Float_t>> MSDY;
    std::vector<Float_t> MSDZ = {MSDZ0, MSDZ1, MSDZ2};
    Long64_t tGeomEntry = 0;
    Long64_t tPileUpEntry = 0;
    UInt_t nentriesGeom = TGeomOut->GetEntries();
    int counter = 0;
    auto Filling = [](std::vector<double> *v, TH1F *histo) {
        for (UInt_t l = 0; l < v->size(); ++l) {
            histo->Fill(v->at(l));
        }
    };
    std::vector<int> sum;
    int ausiliarsum = 0;
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
    for (UInt_t i = 0; i < nentriesGeom; ++i) {
        //////////////////////////////////////////////////////////////////////////
        /////////////////////Get-Entries del
        /// tree/////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
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
        ausiliarsum = 0;
        for (UInt_t j = 0; j < MSDPoints->size(); ++j) {
            ausiliarsum = ausiliarsum + MSDPoints->at(j);
        }
        sum.push_back(ausiliarsum);
        //////////////////////////////////////////////////////////
        //////////////////Riempio energia osservata dal TW////////
        //////////////////////////////////////////////////////////
        Filling(TWDe1Point, h[1]);
        foot::Fill(TWDe1Point, h[2], TWChargePoint, 8);
        if (sum[i] == 3 && TWPoints == 1) {
            Filling(TWDe1Point, h[3]);
            foot::Fill(TWDe1Point, h[6], TWChargePoint, 8);
            if (Frag == false) {
                Filling(TWDe1Point, h[4]);
                foot::Fill(TWDe1Point, h[5], TWChargePoint, 8);
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

        if (sum[i] == 3 && TWPoints == 1) {
            foot::Fill(TWChargePoint, h[13], TWChargePoint, 8, var1);
            foot::Fill(TWChargePoint, h[19], TWChargePoint, 8, var2);
            if (Frag == false) {
                foot::Fill(TWChargePoint, h[14], TWChargePoint, 8, var1);
                foot::Fill(TWChargePoint, h[20], TWChargePoint, 8, var2);
            }
        }
        if (sum[i] == 3 && counter < 20 && TWPoints == 1) {
            print(MSDPoints);
            std::cout << "\n";
            print(MSDXPoint);
            std::cout << "\n";
            print(MSDYPoint);
            std::cout << "\n";
            print(MSDDe1Point);
            std::cout << "\n";
            print(MSDDe2Point);
            std::cout << "\n";
            counter++;
        }
        if (TWPoints == 1 && Frag == false) {
            if ((MSDPoints->at(0) == 1) && (MSDPoints->at(1) == 1) &&
                (MSDPoints->at(2) == 1)) {
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
                if (foot::GeometryMSDTGLine(coordinates) == true) {
                    foot::Fill(TWChargePoint, h[7], TWChargePoint, 8,
                               TWDe1Point->at(0));
                    foot::Fill(TWChargePoint, h[15], TWChargePoint, 8, var1);
                    foot::Fill(TWChargePoint, h[21], TWChargePoint, 8, var2);
                for(UInt_t j=0;j<TWChargePoint->size();++j){
                    std::vector<Float_t> x;
                     std::vector<Float_t> y;
                    if(TWChargePoint->at(j)==8 && MSDX.size()<100){
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
                }
            }
        }
    }
    foot::GeometryPrimaryDraw(MSDX,MSDY,MSDX.size());
    h[8]->Add(h[6], h[7], 1, -1);
    h[9]->Add(h[5], h[7], 1, -1);
    //////////////////////////
    for (UInt_t j = 0; j < h.size(); ++j) {
        h[j]->Write();
    }
    MSDResult->Close();
}
