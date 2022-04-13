#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

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
#include "TGLViewer.h"
#include "TGeoManager.h"
#include "TPolyLine3D.h"

namespace foot{

//////////////////////////////////////////////////////////////////////////////
bool GeometryMSDTGLine(std::vector<std::vector<Float_t>> &coordinates,
                        Float_t xTarget, Float_t yTarget,
                        Float_t errorxyMSd,Float_t errorZ);
//////////////////////////////////////////////////////////////////////////////
void GeometryPrimaryDraw(std::vector<std::vector<Float_t>> &x, std::vector<std::vector<Float_t>> &y,UInt_t dimension);
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
    TH1F* histo,std::vector<int>* charge,int Charge,double var=0);
/////////////////////////////////////////////////////////////////////////////



};
#endif