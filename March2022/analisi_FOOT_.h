//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Mon Mar 21 20:29:15 2022 by ROOT version 6.20/02
// from TTree Tree/Tree
// found on file: tree4306_newgeom_MAR2022.root
//////////////////////////////////////////////////////////

#ifndef analisi_FOOT__h
#define analisi_FOOT__h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"
#include "vector"
#include "vector"
class analisi_FOOT_ {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        Livetime;
   Double_t        Elapsedtime;
   Long64_t        BCO;
   UInt_t          Sectime;
   Int_t           BMhits;
   Int_t           BMtracks;
   Int_t           WhichTrigger;
   Bool_t          Frag;
   Double_t        MaxAngleTGTW;
   Double_t        BeamTGX;
   Double_t        BeamTGY;
   Double_t        BeamTWX;
   Double_t        BeamTWY;
   Double_t        BeamMSDX;
   Double_t        BeamMSDY;
   TVector3        *OriginTrack;
   TVector3        *SlopeTrack;
   Int_t           TWPoints;
   std::vector<int>     *TWChargePoint;
   std::vector<double>  *TWDe1Point;
   std::vector<double>  *TWDe2Point;
   std::vector<double>  *TWXPoint;
   std::vector<double>  *TWYPoint;
   std::vector<int>     *MSDPoints;
   std::vector<double>  *MSDDe1Point;
   std::vector<double>  *MSDDe2Point;
   std::vector<double>  *MSDXPoint;
   std::vector<double>  *MSDYPoint;
   Long64_t        Evt;
   Double_t        SCCharge;
   Double_t        SCTime;
   Bool_t          SCPileup;

   // List of branches
   TBranch        *b_Livetime;   //!
   TBranch        *b_Elapsedtime;   //!
   TBranch        *b_BCO;   //!
   TBranch        *b_Sectime;   //!
   TBranch        *b_BMhits;   //!
   TBranch        *b_BMtracks;   //!
   TBranch        *b_WhichTrigger;   //!
   TBranch        *b_Frag;   //!
   TBranch        *b_MaxAngleTGTW;   //!
   TBranch        *b_BeamTGX;   //!
   TBranch        *b_BeamTGY;   //!
   TBranch        *b_BeamTWX;   //!
   TBranch        *b_BeamTWY;   //!
   TBranch        *b_BeamMSDX;   //!
   TBranch        *b_BeamMSDY;   //!
   TBranch        *b_OriginTrack;   //!
   TBranch        *b_SlopeTrack;   //!
   TBranch        *b_TWPoints;   //!
   TBranch        *b_TWChargePoint;   //!
   TBranch        *b_TWDe1Point;   //!
   TBranch        *b_TWDe2Point;   //!
   TBranch        *b_TWXPoint;   //!
   TBranch        *b_TWYPoint;   //!
   TBranch        *b_MSDPoints;   //!
   TBranch        *b_MSDDe1Point;   //!
   TBranch        *b_MSDDe2Point;   //!
   TBranch        *b_MSDXPoint;   //!
   TBranch        *b_MSDYPoint;   //!
   TBranch        *b_Evt;   //!
   TBranch        *b_SCCharge;   //!
   TBranch        *b_SCTime;   //!
   TBranch        *b_SCPileup;   //!

   analisi_FOOT_(TTree *tree=0);
   virtual ~analisi_FOOT_();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analisi_FOOT__cxx
analisi_FOOT_::analisi_FOOT_(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("tree4306_newgeom_MAR2022.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("tree4306_newgeom_MAR2022.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
}

analisi_FOOT_::~analisi_FOOT_()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analisi_FOOT_::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analisi_FOOT_::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void analisi_FOOT_::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   OriginTrack = 0;
   SlopeTrack = 0;
   TWChargePoint = 0;
   TWDe1Point = 0;
   TWDe2Point = 0;
   TWXPoint = 0;
   TWYPoint = 0;
   MSDPoints = 0;
   MSDDe1Point = 0;
   MSDDe2Point = 0;
   MSDXPoint = 0;
   MSDYPoint = 0;
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Livetime", &Livetime, &b_Livetime);
   fChain->SetBranchAddress("Elapsedtime", &Elapsedtime, &b_Elapsedtime);
   fChain->SetBranchAddress("BCO", &BCO, &b_BCO);
   fChain->SetBranchAddress("Sectime", &Sectime, &b_Sectime);
   fChain->SetBranchAddress("BMhits", &BMhits, &b_BMhits);
   fChain->SetBranchAddress("BMtracks", &BMtracks, &b_BMtracks);
   fChain->SetBranchAddress("WhichTrigger", &WhichTrigger, &b_WhichTrigger);
   fChain->SetBranchAddress("Frag", &Frag, &b_Frag);
   fChain->SetBranchAddress("MaxAngleTGTW", &MaxAngleTGTW, &b_MaxAngleTGTW);
   fChain->SetBranchAddress("BeamTGX", &BeamTGX, &b_BeamTGX);
   fChain->SetBranchAddress("BeamTGY", &BeamTGY, &b_BeamTGY);
   fChain->SetBranchAddress("BeamTWX", &BeamTWX, &b_BeamTWX);
   fChain->SetBranchAddress("BeamTWY", &BeamTWY, &b_BeamTWY);
   fChain->SetBranchAddress("BeamMSDX", &BeamMSDX, &b_BeamMSDX);
   fChain->SetBranchAddress("BeamMSDY", &BeamMSDY, &b_BeamMSDY);
   fChain->SetBranchAddress("OriginTrack", &OriginTrack, &b_OriginTrack);
   fChain->SetBranchAddress("SlopeTrack", &SlopeTrack, &b_SlopeTrack);
   fChain->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
   fChain->SetBranchAddress("TWChargePoint", &TWChargePoint, &b_TWChargePoint);
   fChain->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
   fChain->SetBranchAddress("TWDe2Point", &TWDe2Point, &b_TWDe2Point);
   fChain->SetBranchAddress("TWXPoint", &TWXPoint, &b_TWXPoint);
   fChain->SetBranchAddress("TWYPoint", &TWYPoint, &b_TWYPoint);
   fChain->SetBranchAddress("MSDPoints", &MSDPoints, &b_MSDPoints);
   fChain->SetBranchAddress("MSDDe1Point", &MSDDe1Point, &b_MSDDe1Point);
   fChain->SetBranchAddress("MSDDe2Point", &MSDDe2Point, &b_MSDDe2Point);
   fChain->SetBranchAddress("MSDXPoint", &MSDXPoint, &b_MSDXPoint);
   fChain->SetBranchAddress("MSDYPoint", &MSDYPoint, &b_MSDYPoint);
   fChain->SetBranchAddress("Evt", &Evt, &b_Evt);
   fChain->SetBranchAddress("SCCharge", &SCCharge, &b_SCCharge);
   fChain->SetBranchAddress("SCTime", &SCTime, &b_SCTime);
   fChain->SetBranchAddress("SCPileup", &SCPileup, &b_SCPileup);
   Notify();
}

Bool_t analisi_FOOT_::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analisi_FOOT_::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analisi_FOOT_::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analisi_FOOT__cxx
