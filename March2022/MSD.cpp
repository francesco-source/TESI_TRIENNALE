
#include "Functions.cpp"

void MSD() {
     
    TFile *fileGeom = new TFile("ROOT-FILES/tree4306_newgeom_MAR2022.root");
    TFile *filePileUp = new TFile("ROOT-FILES/tree4306_pileup_MAR2022.root");
    TFile* MSDResult = new TFile("MSDResult.root","RECREATE");
   // TFile *file = new TFile("MSD.root");
    fileGeom->ls();
    filePileUp->ls();
    TTree *TGeomOut = (TTree *)fileGeom->Get("Tree;5");
    TTree *TPileUpOut = (TTree *)filePileUp->Get("Tree;3");
    TH1F *hMSDPoints = new TH1F("hMSDPoints", " Punti nel MSD", 10, 0, 10);
    //////Energia TW//////////////////////////////////////////
      TH1F *hTWPointDE1 =new TH1F("hTWPointDE1", " DE1 TW", 100, 0, 100);
         TH1F *hTWPointDE1o =
        new TH1F("hTWPointDE1o", " DE1  TWCharge=8",
                 100, 0, 100);
    TH1F *hTWPointDE1Clean =
        new TH1F("hTWPointClean", " DE1 persa con MSD==3 e 1 punto nel TW",
                 100, 0, 100);
    TH1F *hTWDE1MSD3TW1NoFrag=new TH1F("hTWDE1MSD3TW1NoFrag", " DE1 TW MSD=3,TW=1,Frag=false",
                 100, 0, 100);
    TH1F *hTWDE1MSD3TW1NoFragOxigen=new TH1F("hTWDE1MSD3TW1NoFragOxigen", " DE1 TW MSD=3,TW=1,Frag=false,TWCharge=8",
                 100, 0, 100);
    TH1F*hTWDE1MSD3TW1Oxigen=new TH1F("hTWDE1MSD3TW1FragOxigen", " DE1 TW MSD=3,TW=1,TWCharge=8",
                 100, 0, 100);
    TH1F *hGeometryOxigen =
        new TH1F("hGeometryOxigen", "DE1 TW MSD=3,Frag=0,TW=1,TWCharge=8,geometria", 100, 0, 100);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        ////Grafici confronto con cui faccio la sottrazione///////////////////////////////////
    TH1F *hAirFrag=new TH1F("hAirFrag", "hTWDE1MSD3TW1Oxigen-hGeometryOxigen", 100, 0, 100);
    TH1F *hAirFragMSDTW=new TH1F("hAirFragMSDTW", "hTWDE1MSD3TW1NoFragOxigen-hGeometryOxigen", 100, 0, 100);

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    TH1F *hMSDDE1Points3 =
        new TH1F("hMSDDE1Points3", "DE1 MSD==3", 1000, 0, 10000);
    TH1F *hMSDDE1Points =
        new TH1F("hMSDDE1Points", "DE1 MSD", 1000, 0, 10000);
    TH1F *hMSDDE1Points3TW = new TH1F(
        "hMSDDE1Points3TW", "DE1 MSD==3 e TW=1", 1000, 0, 10000);
    TH1F *hMSDDE1Points3TWOssigeni =
        new TH1F("hMSDDE1Points3TWOssigeni",
                 "DE1 MSD==3, TW=1, TWCharge=8", 1000, 0, 10000);
     TH1F *hMSDDE1Points3TWOssigeniNoFrag =
        new TH1F("hMSDDE1Points3TWOssigeniNoFrag",
                 "DE1 MSD==3, TW=1,TWCharge=8,Frag=false", 1000, 0, 10000);  
      TH1F *hMSDDE1Points3TWOssigeniNoFragGeometry =
        new TH1F("hMSDDE1Points3TWOssigeniNoFragGeometry",
                 "DE1 MSD==3, TW=1,TWCharge=8,Frag=false, Geometry", 1000, 0, 10000);  
      TH1F *hMSDDE2Points3 =
        new TH1F("hMSDDE2Points3", "DE2 MSD==3", 1000, 0, 15000);
    TH1F *hMSDDE2Points =
        new TH1F("hMSDDE2Points", "DE2 MSD", 1000, 0, 15000);
    TH1F *hMSDDE2Points3TW = new TH1F(
        "hMSDDE2Points3TW", "DE2 MSD==3 e TW=1", 1000, 0, 15000);
    TH1F *hMSDDE2Points3TWOssigeni =
        new TH1F("hMSDDE2Points3TWOssigeni",
                 "DE2 MSD==3, TW=1, TWCharge=8", 1000, 0, 15000);
     TH1F *hMSDDE2Points3TWOssigeniNoFrag =
        new TH1F("hMSDDE2Points3TWOssigeniNoFrag",
                 "DE2 MSD==3, TW=1,TWCharge=8,Frag=false", 1000, 0, 15000);  
      TH1F *hMSDDE2Points3TWOssigeniNoFragGeometry =
        new TH1F("hMSDDE2Points3TWOssigeniNoFragGeometry",
                 "DE2 MSD==3, TW=1,TWCharge=8,Frag=false, Geometry", 1000, 0, 15000);                    
    TH1F *hTWPointDE1NoPileUP =
        new TH1F("hTWPointNoPileUP",
                 " Energia persa vista dal TW senza pile up", 100, 0, 100);
    TH1F *hPointsMSDSawTWNo = new TH1F(
        "hPointsMSDSawTWNo",
        "Quanti punti vede l'MSD quando il TW non vede nulla?", 20, 0, 20);
    TH1F *hEnergyMSDSawTWNo = new TH1F(
        "hEnergyMSDSawTWNo",
        "Che energia vede l'MSD quando il TW non vede nulla con Pile up?", 100,
        0, 100);
    TH1F *hPointsMSDSawFrag =
        new TH1F("hPointsMSDSawFrag",
                 "Quanti punti vede l'MSD quando il fascio primario frammenta",
                 20, 0, 20);

    std::vector<int> *MSDPoints = 0;
    std::vector<double> *TWDe1Point = 0;
    std::vector<int> *TWChargePoint = 0;
    std::vector<double> *MSDDe1Point = 0;
    std::vector<double>  *MSDDe2Point =0;
    std::vector<double> *MSDXPoint = 0;
    std::vector<double> *MSDYPoint = 0;
    Bool_t Frag;
    Bool_t SCPileup = 0;
    Int_t TWPoints = 0;
    TBranch *b_MSDPoints = 0;
    TBranch *b_TWPoints = 0;
    TBranch *b_TWDe1Point = 0;
    TBranch *b_TWChargePoint = 0;
    TBranch *b_MSDDe1Point = 0;
    TBranch *b_MSDDe2Point =0;
    TBranch *b_SCPileup = 0;
    TBranch *b_Frag = 0;
    TBranch *b_MSDXPoint = 0;
    TBranch *b_MSDYPoint = 0;
    Float_t MSDZ0 = 40;
    Float_t MSDZ1 = 40 + 3.8;
    Float_t MSDZ2 = 40 + 3.8 + 3.8;
    std::vector<Float_t> MSDZ = {MSDZ0, MSDZ1, MSDZ2};
    Long64_t tGeomEntry = 0;
    Long64_t tPileUpEntry = 0;
    UInt_t nentriesGeom = TGeomOut->GetEntries();
    int counter = 0;
    auto Filling=[](std::vector<double>* v,TH1F* histo){
        for(UInt_t l=0;l<v->size();++l){histo->Fill(v->at(l));}
    };
    std::vector<int> sum;
    int ausiliarsum = 0;
    TGeomOut->SetBranchAddress("MSDPoints", &MSDPoints, &b_MSDPoints);
    TGeomOut->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
    TGeomOut->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
    TGeomOut->SetBranchAddress("TWChargePoint", &TWChargePoint,
                               &b_TWChargePoint);
    TGeomOut->SetBranchAddress("MSDDe1Point", &MSDDe1Point, &b_MSDDe1Point);
    TGeomOut->SetBranchAddress("MSDDe2Point", &MSDDe2Point, &b_MSDDe2Point);
    TPileUpOut->SetBranchAddress("SCPileup", &SCPileup, &b_SCPileup);
    TGeomOut->SetBranchAddress("Frag", &Frag, &b_Frag);
    TGeomOut->SetBranchAddress("MSDXPoint", &MSDXPoint, &b_MSDXPoint);
    TGeomOut->SetBranchAddress("MSDYPoint", &MSDYPoint, &b_MSDYPoint);
    for (UInt_t i = 0; i < nentriesGeom; ++i) {
        //////////////////////////////////////////////////////////////////////////
        /////////////////////Get-Entries del
        ///tree/////////////////////////////////
        //////////////////////////////////////////////////////////////////////////
        tGeomEntry = TGeomOut->LoadTree(i);
        b_MSDPoints->GetEntry(i);
        b_TWPoints->GetEntry(i);
        b_TWDe1Point->GetEntry(i);
        b_TWChargePoint->GetEntry(i);
        b_MSDDe1Point->GetEntry(i);
        b_MSDDe2Point->GetEntry(i);
        b_SCPileup->GetEntry(i);
        b_Frag->GetEntry(i);
        b_MSDXPoint->GetEntry(i);
        b_MSDYPoint->GetEntry(i);
         ausiliarsum = 0;
         for (UInt_t j = 0; j < MSDPoints->size(); ++j) {
            ausiliarsum = ausiliarsum + MSDPoints->at(j);
        }
        sum.push_back(ausiliarsum);
        //////////////////////////////////////////////////////////
        //////////////////Riempio energia osservata dal TW////////
        //////////////////////////////////////////////////////////
        Filling(TWDe1Point,hTWPointDE1);
        FillingCharge(TWDe1Point,hTWPointDE1o,TWChargePoint,8);
        if (sum[i] == 3 && TWPoints == 1) {
        Filling(TWDe1Point,hTWPointDE1Clean);
        FillingCharge(TWDe1Point,hTWDE1MSD3TW1Oxigen,TWChargePoint,8);
        if(Frag==false){
        Filling(TWDe1Point,hTWDE1MSD3TW1NoFrag);
        FillingCharge(TWDe1Point,hTWDE1MSD3TW1NoFragOxigen,TWChargePoint,8);
        }
        }
        if (TWPoints == 0 && SCPileup == true) {
            hPointsMSDSawTWNo->Fill(sum[i]);
        }
        if (Frag == true) {
            hPointsMSDSawFrag->Fill(sum[i]);
        }
        double var1 = 0;
        double var2 =0;
        if (sum[i] == 3) {
            for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
                var1 = var1 + MSDDe1Point->at(j);
            }
            for (UInt_t j = 0; j < MSDDe2Point->size(); ++j) {
                var2 = var2 + MSDDe2Point->at(j);
            }   
        }
        if(sum[i]==3)
        { hMSDDE1Points3->Fill(var1); hMSDDE2Points3->Fill(var2); }
        if (sum[i] == 3 && TWPoints == 1) {
            hMSDDE1Points3TW->Fill(var1);
             hMSDDE2Points3TW->Fill(var2);
        }
     
        if (sum[i] == 3 && TWPoints == 1) {
            FillingCharge(TWChargePoint,hMSDDE1Points3TWOssigeni,TWChargePoint,8,var1);
            FillingCharge(TWChargePoint,hMSDDE2Points3TWOssigeni,TWChargePoint,8,var2);
        if(Frag==false){
            FillingCharge(TWChargePoint,hMSDDE1Points3TWOssigeniNoFrag,TWChargePoint,8,var1);
            FillingCharge(TWChargePoint,hMSDDE2Points3TWOssigeniNoFrag,TWChargePoint,8,var2);
        }
        }

          if (sum[i] == 3 && TWPoints==1 && Frag==false) {
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
            if (GeometryMSDTGLine(coordinates) == true) {
                FillingCharge(TWChargePoint,hGeometryOxigen,TWChargePoint,8,TWDe1Point->at(0));
                FillingCharge(TWChargePoint,hMSDDE1Points3TWOssigeniNoFragGeometry,TWChargePoint,8,var1);
                FillingCharge(TWChargePoint,hMSDDE2Points3TWOssigeniNoFragGeometry,TWChargePoint,8,var2);
            }
          }
    }
    hAirFrag->Add(hTWDE1MSD3TW1Oxigen,hGeometryOxigen,1,-1);
    hAirFragMSDTW->Add(hTWDE1MSD3TW1NoFragOxigen,hGeometryOxigen,1,-1);
    //MSDResult->Write();
    //////////////////////////
     hMSDPoints->Write();
     hMSDPoints->Write();
     hTWPointDE1->Write();
     hTWPointDE1o ->Write();
     hTWPointDE1Clean ->Write();
     hTWDE1MSD3TW1NoFrag->Write();
     hTWDE1MSD3TW1NoFragOxigen->Write();
     hTWDE1MSD3TW1Oxigen->Write();
     hGeometryOxigen ->Write();
     hAirFrag->Write();
     hAirFragMSDTW->Write();
     hMSDDE1Points3 ->Write();
     hMSDDE1Points ->Write();
     hMSDDE1Points3TW ->Write();
     hMSDDE1Points3TWOssigeni ->Write();
     hMSDDE1Points3TWOssigeniNoFrag ->Write();
     hMSDDE1Points3TWOssigeniNoFragGeometry ->Write();
     hMSDDE2Points3 ->Write();
     hMSDDE2Points ->Write();
     hMSDDE2Points3TW ->Write(); 
     hMSDDE2Points3TWOssigeni ->Write();
     hMSDDE2Points3TWOssigeniNoFrag ->Write(); 
     hMSDDE2Points3TWOssigeniNoFragGeometry ->Write();                    
     hTWPointDE1NoPileUP ->Write();
     hPointsMSDSawTWNo ->Write();
     hEnergyMSDSawTWNo ->Write(); 
     hPointsMSDSawFrag ->Write();
     MSDResult->Close();
   
}
