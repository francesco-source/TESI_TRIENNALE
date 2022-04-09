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



void Draw_MSD_PileUP(){
    TFile *file = new TFile("MSDResult.root");
    TH1F *hMSDPoints = (TH1F*)file->Get("hMSDPoints"); 
    TH1F *hTWPointDE1 =(TH1F*)file->Get("hTWPointDE1"); 
    TH1F *hTWPointDE1o =(TH1F*)file->Get("hTWPointDE1o");
    TH1F *hTWPointDE1Clean =(TH1F*)file->Get("hTWPointClean");
    TH1F *hTWDE1MSD3TW1NoFrag=(TH1F*)file->Get("hTWDE1MSD3TW1NoFrag");
    TH1F *hTWDE1MSD3TW1NoFragOxigen=(TH1F*)file->Get("hTWDE1MSD3TW1NoFragOxigen");
    TH1F*hTWDE1MSD3TW1Oxigen=(TH1F*)file->Get("hTWDE1MSD3TW1FragOxigen");
    TH1F *hGeometryOxigen =(TH1F*)file->Get("hGeometryOxigen");
    TH1F *hAirFrag=(TH1F*)file->Get("hAirFrag");
    TH1F *hAirFragMSDTW=(TH1F*)file->Get("hAirFragMSDTW");


    TH1F *hMSDDE1Points3 =(TH1F*)file->Get("hMSDDE1Points3");
    TH1F *hMSDDE1Points =(TH1F*)file->Get("hMSDDE1Points");
    TH1F *hMSDDE1Points3TW =(TH1F*)file->Get("hMSDDE1Points3TW");
    TH1F *hMSDDE1Points3TWOssigeni =(TH1F*)file->Get("hMSDDE1Points3TWOssigeni");
    TH1F *hMSDDE1Points3TWOssigeniNoFrag =(TH1F*)file->Get("hMSDDE1Points3TWOssigeniNoFrag");
    TH1F *hMSDDE1Points3TWOssigeniNoFragGeometry =(TH1F*)file->Get("hMSDDE1Points3TWOssigeniNoFragGeometry");
    TH1F *hMSDDE2Points3 =(TH1F*)file->Get("hMSDDE2Points3");
    TH1F *hMSDDE2Points =(TH1F*)file->Get("hMSDDE2Points");
    TH1F *hMSDDE2Points3TW = (TH1F*)file->Get("hMSDDE2Points3TW");
    TH1F *hMSDDE2Points3TWOssigeni =(TH1F*)file->Get("hMSDDE2Points3TWOssigeni");
    TH1F *hMSDDE2Points3TWOssigeniNoFrag =  (TH1F*)file->Get("hMSDDE2Points3TWOssigeniNoFrag");
    TH1F *hMSDDE2Points3TWOssigeniNoFragGeometry = (TH1F*)file->Get("hMSDDE2Points3TWOssigeniNoFragGeometry");                   
    TH1F *hTWPointDE1NoPileUP =(TH1F*)file->Get("hTWPointNoPileUP");
    TH1F *hPointsMSDSawTWNo =(TH1F*)file->Get("hPointsMSDSawTWNo");
    TH1F *hEnergyMSDSawTWNo = (TH1F*)file->Get("hEnergyMSDSawTWNo");
    TH1F *hPointsMSDSawFrag =(TH1F*)file->Get("hPointsMSDSawFrag");
    hTWPointDE1->SetLineColor(kBlack);
    hTWPointDE1o->SetLineColor(kBlue);
    hTWPointDE1Clean->SetLineColor(kRed);
    hGeometryOxigen->SetLineColor(kGreen);
    TCanvas *c4 = new TCanvas("c4", "Pile up= file pile up. Eventi= new Geom");
    c4->Divide(3,4);

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

    c4->cd(10);
     gPad->SetLogy();
     hTWDE1MSD3TW1Oxigen->GetXaxis()->SetTitle("dE/dx");
    hTWDE1MSD3TW1Oxigen->GetYaxis()->SetTitle("Events");
    hTWDE1MSD3TW1Oxigen->Draw();
     hTWDE1MSD3TW1NoFragOxigen->Draw("SAME");
      hGeometryOxigen->Draw("SAME");

     c4->cd(11);
    gPad->SetLogy();
    hAirFrag->GetXaxis()->SetTitle("dE/dx");
    hAirFrag->GetYaxis()->SetTitle("Events");
    hAirFrag->Draw();


    c4->cd(12);
    gPad->SetLogy();
    hAirFragMSDTW->GetXaxis()->SetTitle("dE/dx");
    hAirFragMSDTW->GetYaxis()->SetTitle("Events");
    hAirFragMSDTW->Draw();


    TCanvas *c5 = new TCanvas("c5", "Pile up= file pile up. Eventi= new Geom");
    c5->Divide(3,4);
    hMSDDE1Points3->SetLineColor(kBlack);
    hMSDDE1Points->SetLineColor(kRed);
    hMSDDE1Points3TW->SetLineColor(kGreen);
    hMSDDE1Points3TWOssigeni->SetLineColor(kBlue);
    hMSDDE1Points3TWOssigeniNoFrag->SetLineColor(kMagenta);
    hMSDDE1Points3TWOssigeniNoFragGeometry->SetLineColor(kRed);
    hMSDDE2Points3->SetLineColor(kBlack);
    hMSDDE2Points->SetLineColor(kRed);
    hMSDDE2Points3TW->SetLineColor(kGreen);
    hMSDDE2Points3TWOssigeni->SetLineColor(kBlue);
    hMSDDE2Points3TWOssigeniNoFrag->SetLineColor(kMagenta);
    hMSDDE2Points3TWOssigeniNoFragGeometry->SetLineColor(kRed);
   
    c5->cd(1);
    gPad->SetLogy();
    hMSDDE1Points3->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3->Draw();

    c5->cd(2);
    gPad->SetLogy();
    hMSDDE1Points3TW->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3TW->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3TW->Draw();

    c5->cd(3);
    gPad->SetLogy();
    hMSDDE1Points3TWOssigeni->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3TWOssigeni->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3TWOssigeni->Draw();
    c5->cd(4);
    gPad->SetLogy();
     hMSDDE1Points3TWOssigeniNoFrag->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3TWOssigeniNoFrag->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3TWOssigeniNoFrag->Draw();
      c5->cd(5);
    gPad->SetLogy();
    hMSDDE1Points3TWOssigeniNoFragGeometry->GetXaxis()->SetTitle("dE/dx");
    hMSDDE1Points3TWOssigeniNoFragGeometry->GetYaxis()->SetTitle("Events");
    hMSDDE1Points3TWOssigeniNoFragGeometry->Draw();

    c5->cd(6);
    gPad->SetLogy();
    hMSDPoints->GetXaxis()->SetTitle("dE/dx");
    hMSDPoints->GetYaxis()->SetTitle("Events");
    //hMSDDE1Points->Draw();
    hMSDDE1Points3->Draw();
    hMSDDE1Points3TW->Draw("SAME");
    hMSDDE1Points3TWOssigeni->Draw("SAME");
    hMSDDE1Points3TWOssigeniNoFrag->Draw("SAME");
    hMSDDE1Points3TWOssigeniNoFragGeometry->Draw("SAME");
        c5->cd(7);
    gPad->SetLogy();
    hMSDDE2Points3->GetXaxis()->SetTitle("dE/dx");
    hMSDDE2Points3->GetYaxis()->SetTitle("Events");
    hMSDDE2Points3->Draw();

    c5->cd(8);
    gPad->SetLogy();
    hMSDDE2Points3TW->GetXaxis()->SetTitle("dE/dx");
    hMSDDE2Points3TW->GetYaxis()->SetTitle("Events");
    hMSDDE2Points3TW->Draw();

    c5->cd(9);
    gPad->SetLogy();
    hMSDDE2Points3TWOssigeni->GetXaxis()->SetTitle("dE/dx");
    hMSDDE2Points3TWOssigeni->GetYaxis()->SetTitle("Events");
    hMSDDE2Points3TWOssigeni->Draw();
    c5->cd(10);
    gPad->SetLogy();
     hMSDDE2Points3TWOssigeniNoFrag->GetXaxis()->SetTitle("dE/dx");
    hMSDDE2Points3TWOssigeniNoFrag->GetYaxis()->SetTitle("Events");
    hMSDDE2Points3TWOssigeniNoFrag->Draw();
      c5->cd(11);
    gPad->SetLogy();
    hMSDDE2Points3TWOssigeniNoFragGeometry->GetXaxis()->SetTitle("dE/dx");
    hMSDDE2Points3TWOssigeniNoFragGeometry->GetYaxis()->SetTitle("Events");
    hMSDDE2Points3TWOssigeniNoFragGeometry->Draw();

    c5->cd(12);
    gPad->SetLogy();
    hMSDPoints->GetXaxis()->SetTitle("dE/dx");
    hMSDPoints->GetYaxis()->SetTitle("Events");
    hMSDDE2Points3->Draw();
    hMSDDE2Points3TW->Draw("SAME");
    hMSDDE2Points3TWOssigeni->Draw("SAME");
    hMSDDE2Points3TWOssigeniNoFrag->Draw("SAME");
    hMSDDE2Points3TWOssigeniNoFragGeometry->Draw("SAME");

    TCanvas *c8 = new TCanvas("c8", "Pile up= file pile up. Eventi= new Geom");
    c8->Divide(2);
    c8->cd(1);
    hPointsMSDSawTWNo->GetXaxis()->SetTitle("Points");
    hPointsMSDSawTWNo->GetYaxis()->SetTitle("Events");
    hPointsMSDSawTWNo->Draw();
   c8->cd(2);
    hPointsMSDSawFrag->GetXaxis()->SetTitle("Points");
    hPointsMSDSawFrag->GetYaxis()->SetTitle("Events");
    hPointsMSDSawFrag->Draw();

    c4->Print("Grafici/TwLostEnergy.pdf");
    c5->Print("Grafici/MSDLostEnergy.pdf");
    c8->Print(
        "Grafici/MSD-Points-Seen.pdf");
}

