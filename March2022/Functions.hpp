#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <TCanvas.h>
#include <TH2.h>
#include <TStyle.h>

#include "TCanvas.h"
#include "TF1.h"
#include "TFile.h"
#include "TFitResult.h"
#include "TGLViewer.h"
#include "TGeoManager.h"
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
#include "TPolyLine3D.h"
#include "TROOT.h"
#include "TRandom.h"
#include "TStyle.h"
#include "TTree.h"
#include<memory>

namespace foot {
constexpr double MSDError_X_Y = 0.014;
constexpr double ErrorZ = 0;
constexpr double Xalign{0.7907-0.8823};
constexpr double Yalign{0.2927-0.09199};
//////////////////////////////////////////////////////////////////////////////
typedef struct index {
    double x = 0;
    double y = 0;
} ind;
//////////////////////////////////////////////////////////////////////////////
static bool GeometryMSDTGLine(std::vector<std::vector<Float_t>>& coordinates,
                              int counter, Float_t xTarget, Float_t yTarget,
                              Float_t errorxyMSd, Float_t errorZ);
//////////////////////////////////////////////////////////////////////////////
static void GeometryPrimaryDraw(std::vector<std::vector<Float_t>>& x,
                                std::vector<std::vector<Float_t>>& y,
                                UInt_t dimension);

//////////////////////////////////////////////////////////////////////////////
template <typename T, typename S>
static auto BeamMSD_vs_MSDRealPoint(T& BeamMSDX, T& BeamMSDY,
                                    std::vector<S>* RealMSDX,
                                    std::vector<S>* RealMSDY) -> bool;
//////////////////////////////////////////////////////////////////////////////
template <typename T, typename S>
static std::vector<ind> FindTrueTW(std::vector<T>* energy1,
                                   std::vector<T>* energy2,
                                   std::vector<S>* MSDPoints, int TWPoints);
////////////////////////////////////////////////////////////////////////////////
template <typename T>
static void Fill(std::vector<T>* v, TH1F* histo, std::vector<int>* charge,
                 int&& which_Charge, double var = 0);
/////////////////////////////////////////////////////////////////////////////
template <typename T>
static void print(std::vector<T>* v);
//////////////////////////////////////////////////////////////////////////////
};  // namespace foot
#include "Functions.cpp"
#endif