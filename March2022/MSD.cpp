#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>

#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "THStack.h"
#include "TLegend.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TTree.h"
bool GeometryMSDTGLine(std::vector<std::vector<Float_t>> &coordinates,
                        Float_t xTarget = 2, Float_t yTarget = 2,Float_t errorxyMSd=0.01,Float_t errorZ=0.1) {
    ///////////////////////////////////////////////////////////////////////////////
    /////////////Ritorna Falso se la retta prolungata esce dal
    ///target//////////////
    ///////////////////////////////////////////////////////////////////////////////
    Float_t x[3];
    Float_t y[3];
    Float_t z[3];
    for (int i = 0; i < 3; ++i) {
        x[i] = coordinates[0][i];
    }
    for (int i = 0; i < 3; ++i) {
        y[i] = coordinates[1][i];
    }
    for (int i = 0; i < 3; ++i) {
        z[i] = coordinates[2][i];
    }
    Float_t errorxy[3]={errorxyMSd,errorxyMSd,errorxyMSd};
    Float_t errorZeta[3]={errorZ,errorZ,errorZ};
    TGraphErrors XZ(3, z, x,errorZeta,errorxy);
    TGraphErrors YZ(3, z, y,errorZeta,errorxy);
    TF1 fitXZ("fitXZ", "[0]*x+[1]", 0, 50);
    TF1 fitYZ("fitYZ", "[0]*x+[1]", 0, 50);
    fitXZ.SetParameter(0, 0);
    fitXZ.SetParameter(1, 0);
    fitYZ.SetParameter(0, 0);
    fitYZ.SetParameter(1, 0);
    XZ.Fit("fitXZ", "QN");
    YZ.Fit("fitYZ", "QN");
    Float_t absXZ = abs(fitXZ.GetParameter(1)-fitXZ.GetParError(1));
    Float_t absYZ = abs(fitYZ.GetParameter(1)-fitYZ.GetParError(1));
    if (absXZ >= xTarget || absYZ >= yTarget) {
        return false;
    } else if (absXZ < xTarget && absYZ < yTarget) {
        return true;
    } else {
        return false;
    }
   
}

void MSD() {
    TFile *fileGeom = new TFile("ROOT-FILES/tree4306_newgeom_MAR2022.root");
    TFile *filePileUp = new TFile("ROOT-FILES/tree4306_pileup_MAR2022.root");
    TFile *file = new TFile("MSD.root");
    fileGeom->ls();
    filePileUp->ls();
    TTree *TGeomOut = (TTree *)fileGeom->Get("Tree;5");
    TTree *TPileUpOut = (TTree *)filePileUp->Get("Tree;3");
    TH1F *hMSDPoints = new TH1F("hMSDPoints", " Punti nel MSD", 10, 0, 10);
    //////Energia TW//////////////////////////////////////////
      TH1F *hTWPointDE1 =
        new TH1F("hTWPoint", " DE1 TW", 100, 0, 100);
         TH1F *hTWPointDE1o =
        new TH1F("hTWPoint", " DE1  TWCharge=8",
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


    TH1F *hMSDDE1Points3 =
        new TH1F("hMSDDE1Points3", "Perdita di energia MSD==3", 1000, 0, 5000);
    TH1F *hMSDDE1Points =
        new TH1F("hMSDDE1Points", "Perdita di energia MSD", 1000, 0, 5000);
    TH1F *hMSDDE1Points3TW = new TH1F(
        "hMSDDE1Points3TW", "Perdita di energia MSD==3 e TW=1", 1000, 0, 5000);
    TH1F *hMSDDE1Points3TWOssigeni =
        new TH1F("hMSDDE1Points3TWOssigeni",
                 "Perdita di energia MSD==3, TW=1, Carica 8", 1000, 0, 5000);
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
    std::vector<int> sum;
    int ausiliarsum = 0;
    TGeomOut->SetBranchAddress("MSDPoints", &MSDPoints, &b_MSDPoints);
    TGeomOut->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
    TGeomOut->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
    TGeomOut->SetBranchAddress("TWChargePoint", &TWChargePoint,
                               &b_TWChargePoint);
    TGeomOut->SetBranchAddress("MSDDe1Point", &MSDDe1Point, &b_MSDDe1Point);
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
        b_SCPileup->GetEntry(i);
        b_Frag->GetEntry(i);
        b_MSDXPoint->GetEntry(i);
        b_MSDYPoint->GetEntry(i);
        //////////////////////////////////////////////////////////
        //////////////////Riempio energia osservata dal TW////////
        //////////////////////////////////////////////////////////
        for (UInt_t j = 0; j < TWDe1Point->size(); ++j) {
            { hTWPointDE1->Fill(TWDe1Point->at(j)); }
        }
        /////////////////////////////////////////////////////////////////
        /////Riempio energia osservata nel TW dei soli ossigeni//////////
        ////////////////////////////////////////////////////////////////
        for (UInt_t j = 0; j < TWDe1Point->size(); ++j) {
            if (TWChargePoint->at(j) == 8) {
                hTWPointDE1o->Fill(TWDe1Point->at(j));
            }
        }
        /////////////////////////////////////////////////////////
        //////Conto i punti totali osservati dall'MSD////////////
        /////////////////////////////////////////////////////////
        for (UInt_t j = 0; j < MSDPoints->size(); ++j) {
            ausiliarsum = ausiliarsum + MSDPoints->at(j);
        }
        sum.push_back(ausiliarsum);

        /////////////////////////////////////////////////////////
        ///////Riempio la perdita di energia del MSD/////////////
        /////////////////////////////////////////////////////////
        double variab = 0;
        for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
            variab = variab + MSDDe1Point->at(j);
        }
        hMSDDE1Points->Fill(variab);

        ///////////////////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////Condizioni di visibilità del
        /// rivelatore////////////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        ////////////////////////////////////////////////////////////////
        /// Punti visti da MSD quando TW non vede niente e c' è pile up//
        ////////////////////////////////////////////////////////////////
        if (TWPoints == 0 && SCPileup == true) {
            hPointsMSDSawTWNo->Fill(sum[i]);
        }

        ////////////////////////////////////////////////////////////////
        ////Quanti punti vede l' MSD quando il fascio frammenta?///////////////
        ///////////////////////////////////////////////////////////////
        if (Frag == true) {
            hPointsMSDSawFrag->Fill(sum[i]);
        }
        //////////////////////////////////////////////////////////////
        // Energia persa in MSD quando TW non vede nulla con Pile UP///
        //////////////////////////////////////////////////////////////
        if (TWPoints == 0 && SCPileup == true) {
            // Riempilo con il grafico metto uno zero ora di default devo finire
            std::vector<int> same_charge;
            for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
                hEnergyMSDSawTWNo->Fill(0);
            }
        }

        // Energia TW quando TW ed MSD vedono solo un punto che succede/////
        if (sum[i] == 3 && TWPoints == 1) {
            for (UInt_t j = 0; j < TWDe1Point->size(); ++j) {
                hTWPointDE1Clean->Fill(TWDe1Point->at(j));
                if(Frag==false){hTWDE1MSD3TW1NoFrag->Fill(TWDe1Point->at(j));}
                if(TWChargePoint->at(j)==8){hTWDE1MSD3TW1Oxigen->Fill(TWDe1Point->at(j));}
                if(Frag==false && TWChargePoint->at(j)==8){hTWDE1MSD3TW1NoFragOxigen->Fill(TWDe1Point->at(j));}
               
            }
        }


        /// Energia quando l' MSD vede un solo punto//////////////
        if (sum[i] == 3) {
            double var = 0;
            for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
                var = var + MSDDe1Point->at(j);
            }
            hMSDDE1Points3->Fill(var);
        }

        ////Energia MSD quando TW ed MSD vedono solo un punto che succede//////
        if (sum[i] == 3 && TWPoints == 1) {
            double v = 0;
            for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
                v = v + MSDDe1Point->at(j);
            }
            hMSDDE1Points3TW->Fill(v);
        }
        // Energia ossigeni quando TW ed MSD vedono un solo punto///////////////
        if (sum[i] == 3 && TWPoints == 1) {
            double var = 0;
            for (UInt_t j = 0; j < MSDDe1Point->size(); ++j) {
                var = var + MSDDe1Point->at(j);
            }
            for (UInt_t j = 0; j < TWChargePoint->size(); ++j) {
                if (TWChargePoint->at(j) == 8) {
                    hMSDDE1Points3TWOssigeni->Fill(var);
                }
            }
        }
        ausiliarsum = 0;
        //////////////////////////////////////////////////////////////////////////////////////////////
        //////////////////////////////////////////////////////////////////////////////////////////////
        ///////////////////////////Geometria
        ///Primari//////////////////////////////////////////////////
        ///////////////////////////////////////////////////////////////////////////////////////////////
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
                for (UInt_t j = 0; j < TWChargePoint->size(); ++j) {
                    if (TWChargePoint->at(j) == 8) {
                        hGeometryOxigen->Fill(TWDe1Point->at(0));
                        counter++;
                    }
                }
            }
        }
    }
    std::cout << counter << std::endl;

    ///////////////////////////////////////////////////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////////////////////////////////////
    ///////////////////////Cosmetica//////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////////////////////////////////////

    hTWPointDE1->SetLineColor(kBlack);
    hTWPointDE1o->SetLineColor(kBlue);
    hTWPointDE1Clean->SetLineColor(kRed);
    hGeometryOxigen->SetLineColor(kGreen);
    TCanvas *c4 = new TCanvas("c4", "Pile up= file pile up. Eventi= new Geom");
    c4->Divide(3,3);

    c4->cd(1);
    gPad->SetLogy();
    hTWPointDE1->GetXaxis()->SetTitle("dE/dx");
    hTWPointDE1->GetYaxis()->SetTitle("Events");
    hTWPointDE1->Draw();

    c4->cd(2);
    gPad->SetLogy();
    hTWPointDE1Clean->GetXaxis()->SetTitle("dE/dx");
    hTWPointDE1Clean->GetYaxis()->SetTitle("Events");
    hTWPointDE1Clean->Draw();


    c4->cd(3);
    gPad->SetLogy();
    hTWPointDE1o->GetXaxis()->SetTitle("dE/dx");
    hTWPointDE1o->GetYaxis()->SetTitle("Events");
    hTWPointDE1Clean->Draw();
    hTWPointDE1->Draw("SAME");



    c4->cd(4);
     gPad->SetLogy();
    hTWPointDE1Clean->GetXaxis()->SetTitle("dE/dx");
    hTWPointDE1Clean->GetYaxis()->SetTitle("Events");
    hTWPointDE1Clean->Draw();

   
    c4->cd(5);
    gPad->SetLogy();
    hTWDE1MSD3TW1NoFrag->GetXaxis()->SetTitle("dE/dx");
    hTWDE1MSD3TW1NoFrag->GetYaxis()->SetTitle("Events");
    hTWDE1MSD3TW1NoFrag->Draw();

    c4->cd(6);
    gPad->SetLogy();
    hTWPointDE1Clean->GetXaxis()->SetTitle("dE/dx");
    hTWPointDE1Clean->GetYaxis()->SetTitle("Events");
    hTWPointDE1Clean->Draw();
    hTWDE1MSD3TW1NoFrag->Draw("SAME");

    c4->cd(7);
     gPad->SetLogy();
     hTWDE1MSD3TW1Oxigen->GetXaxis()->SetTitle("dE/dx");
    hTWDE1MSD3TW1Oxigen->GetYaxis()->SetTitle("Events");
    hTWDE1MSD3TW1Oxigen->Draw();

    c4->cd(8);
     gPad->SetLogy();
     hTWDE1MSD3TW1NoFragOxigen->GetXaxis()->SetTitle("dE/dx");
    hTWDE1MSD3TW1NoFragOxigen->GetYaxis()->SetTitle("Events");
    hTWDE1MSD3TW1NoFragOxigen->Draw();
    
    c4->cd(9);
    gPad->SetLogy();
     hGeometryOxigen->GetXaxis()->SetTitle("dE/dx");
    hGeometryOxigen->GetYaxis()->SetTitle("Events");
    hGeometryOxigen->Draw();

    TCanvas *c5 = new TCanvas("c5", "Pile up= file pile up. Eventi= new Geom");
    c5->Divide(2, 2);
    hMSDDE1Points3->SetLineColor(kBlack);
    hMSDDE1Points->SetLineColor(kRed);
    hMSDDE1Points3TW->SetLineColor(kGreen);
    hMSDDE1Points3TWOssigeni->SetLineColor(kBlue);
    c5->cd(1);
    gPad->SetLogy();
    hMSDDE1Points->GetXaxis()->SetTitle("dE/dx");
    hMSDPoints->GetYaxis()->SetTitle("Events");
    hMSDDE1Points->Draw();

    c5->cd(2);
    gPad->SetLogy();
    hMSDDE1Points3->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3->Draw();

    c5->cd(3);
    gPad->SetLogy();
    hMSDDE1Points3TW->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3TW->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3TW->Draw();

    c5->cd(4);
    gPad->SetLogy();
    hMSDDE1Points3TWOssigeni->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3TWOssigeni->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3TWOssigeni->Draw();

    TCanvas *c6 = new TCanvas("c6", "Pile up= file pile up. Eventi= new Geom");
    gPad->SetLogy();
    hMSDPoints->GetXaxis()->SetTitle("dE/dx");
    hMSDPoints->GetYaxis()->SetTitle("Events");
    hMSDDE1Points->Draw();
    hMSDDE1Points3->Draw("SAME");
    hMSDDE1Points3TW->Draw("SAME");
    hMSDDE1Points3TWOssigeni->Draw("SAME");

    TCanvas *c7 = new TCanvas("c7", "Pile up= file pile up. Eventi= new Geom");
    hTWPointDE1NoPileUP->SetLineColor(kBlue);
    c7->Divide(3);
    c7->cd(1);
    gPad->SetLogy();
    hTWPointDE1->Draw();
    c7->cd(2);
    gPad->SetLogy();
    hTWPointDE1NoPileUP->Draw();
    c7->cd(3);
    gPad->SetLogy();
    hTWPointDE1->Draw();
    hTWPointDE1NoPileUP->Draw("Same");
    TCanvas *c8 = new TCanvas("c8", "Pile up= file pile up. Eventi= new Geom");
    hPointsMSDSawTWNo->GetXaxis()->SetTitle("Points");
    hPointsMSDSawTWNo->GetYaxis()->SetTitle("Events");
    hPointsMSDSawTWNo->Draw();
    TCanvas *c9 = new TCanvas("c9", "Pile up= file pile up. Eventi= new Geom");
    hPointsMSDSawFrag->GetXaxis()->SetTitle("Points");
    hPointsMSDSawFrag->GetYaxis()->SetTitle("Events");
    hPointsMSDSawFrag->Draw();

    c4->Print("Grafici/TwLostEnergy.pdf");
    c5->Print("Grafici/MSDLostEnergy.pdf");
    c6->Print("Grafici/MSDLostEnergyConfronto.pdf");
    c7->Print("Grafici/TW Energy lost and pile up.pdf");
    c8->Print(
        "Grafici/Quanti punti vede l'MSd quando TW non vede nulla con Pile "
        "up?.pdf");
    c9->Print("Grafici/Quando ho frammentazione quanti punti vede MSD?.pdf");
}