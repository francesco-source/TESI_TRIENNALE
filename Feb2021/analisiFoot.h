//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Wed Mar  2 13:01:09 2022 by ROOT version 6.20/02
// from TTree Tree/Tree
// found on file: tree4306_newgeom_FEB2021.root
//////////////////////////////////////////////////////////

#ifndef analisiFoot_h
#define analisiFoot_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "TVector3.h"
#include "vector"
#include "vector"
using namespace std;
class analisiFoot {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Double_t        Livetime;
   Double_t        Elapsedtime;
   Int_t           BMhits;
   Int_t           BMtracks;
   Int_t           WhichTrigger;
   Bool_t          Frag;
   Double_t        MaxAngleTGTW;
   Double_t        BeamTGX;
   Double_t        BeamTGY;
   Double_t        BeamTWX;
   Double_t        BeamTWY;
   TVector3        *OriginTrack;
   TVector3        *SlopeTrack;
   Int_t           TWPoints;
   vector<int>     *TWChargePoint;
   vector<double>  *TWDe1Point;
   vector<double>  *TWDe2Point;
   vector<double>  *TWXPoint;
   vector<double>  *TWYPoint;

   // List of branches
   TBranch        *b_Livetime;   //!
   TBranch        *b_Elapsedtime;   //!
   TBranch        *b_BMhits;   //!
   TBranch        *b_BMtracks;   //!
   TBranch        *b_WhichTrigger;   //!
   TBranch        *b_Frag;   //!
   TBranch        *b_MaxAngleTGTW;   //!
   TBranch        *b_BeamTGX;   //!
   TBranch        *b_BeamTGY;   //!
   TBranch        *b_BeamTWX;   //!
   TBranch        *b_BeamTWY;   //!
   TBranch        *b_OriginTrack;   //!
   TBranch        *b_SlopeTrack;   //!
   TBranch        *b_TWPoints;   //!
   TBranch        *b_TWChargePoint;   //!
   TBranch        *b_TWDe1Point;   //!
   TBranch        *b_TWDe2Point;   //!
   TBranch        *b_TWXPoint;   //!
   TBranch        *b_TWYPoint;   //!

   analisiFoot(TTree *tree=0);
   virtual ~analisiFoot();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef analisiFoot_cxx
analisiFoot::analisiFoot(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("tree4306_newgeom_FEB2021.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("tree4306_newgeom_FEB2021.root");
      }
      f->GetObject("Tree",tree);

   }
   Init(tree);
}

analisiFoot::~analisiFoot()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t analisiFoot::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Long64_t analisiFoot::LoadTree(Long64_t entry)
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

void analisiFoot::Init(TTree *tree)
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
   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("Livetime", &Livetime, &b_Livetime);
   fChain->SetBranchAddress("Elapsedtime", &Elapsedtime, &b_Elapsedtime);
   fChain->SetBranchAddress("BMhits", &BMhits, &b_BMhits);
   fChain->SetBranchAddress("BMtracks", &BMtracks, &b_BMtracks);
   fChain->SetBranchAddress("WhichTrigger", &WhichTrigger, &b_WhichTrigger);
   fChain->SetBranchAddress("Frag", &Frag, &b_Frag);
   fChain->SetBranchAddress("MaxAngleTGTW", &MaxAngleTGTW, &b_MaxAngleTGTW);
   fChain->SetBranchAddress("BeamTGX", &BeamTGX, &b_BeamTGX);
   fChain->SetBranchAddress("BeamTGY", &BeamTGY, &b_BeamTGY);
   fChain->SetBranchAddress("BeamTWX", &BeamTWX, &b_BeamTWX);
   fChain->SetBranchAddress("BeamTWY", &BeamTWY, &b_BeamTWY);
   fChain->SetBranchAddress("OriginTrack", &OriginTrack, &b_OriginTrack);
   fChain->SetBranchAddress("SlopeTrack", &SlopeTrack, &b_SlopeTrack);
   fChain->SetBranchAddress("TWPoints", &TWPoints, &b_TWPoints);
   fChain->SetBranchAddress("TWChargePoint", &TWChargePoint, &b_TWChargePoint);
   fChain->SetBranchAddress("TWDe1Point", &TWDe1Point, &b_TWDe1Point);
   fChain->SetBranchAddress("TWDe2Point", &TWDe2Point, &b_TWDe2Point);
   fChain->SetBranchAddress("TWXPoint", &TWXPoint, &b_TWXPoint);
   fChain->SetBranchAddress("TWYPoint", &TWYPoint, &b_TWYPoint);
   Notify();
}

Bool_t analisiFoot::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void analisiFoot::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t analisiFoot::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef analisiFoot_cxx
