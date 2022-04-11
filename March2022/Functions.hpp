#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <TH2.h>
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TGraph.h"
#include "TGraphErrors.h"
#include "TH1F.h"
#include "TH2F.h"
#include "TH3F.h"
#include "THStack.h"
#include "TMath.h"
#include "TMatrixD.h"
#include "TMultiGraph.h"
#include "TROOT.h"
#include "TStyle.h"
#include "TTree.h"

namespace foot{

//////////////////////////////////////////////////////////////////////////////
bool GeometryMSDTGLine(std::vector<std::vector<Float_t>> &coordinates,
                        Float_t xTarget, Float_t yTarget,
                        Float_t errorxyMSd,Float_t errorZ);
//////////////////////////////////////////////////////////////////////////////
  typedef struct index{
      double x=0;
      double y=0;
  }ind;
//////////////////////////////////////////////////////////////////////////////
 template<typename T,typename S>
   std::vector<ind> FindTrueTW(std::vector<T>* energy1, std::vector<T>* energy2
    ,std::vector<S>* MSDPoints,int TWPoints);
//////////////////////////////////////////////////////////////////////////////
   template<typename T>
    bool GeometryMSD();
////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    void Fill(std::vector<T>* v,
    TH1F* histo,std::vector<int>* charge,int Charge,double var);
/////////////////////////////////////////////////////////////////////////////
};
#endif