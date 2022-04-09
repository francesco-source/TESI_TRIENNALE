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
                        Float_t xTarget = 2, Float_t yTarget = 2,
                        Float_t errorxyMSd=0.01,Float_t errorZ=0.1) {
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
   
};

 typedef struct index{
    public:
        int i=0;
        int j=0;
}ind;


    template<typename T>
    auto GostTW(std::vector<T>* energy1, std::vector<T>* energy2,
                int sumMSD,std::vector<int> MSDPoints,int TWPoints){
            std::vector<ind> index;
            std::vector<std::vector<T>> sum(energy1->size(),std::vector<T>(energy2->size()));
            std::vector<std::vector<T>> diff(energy1->size(),std::vector<T>(energy2->size()));
            for(UInt_t i=0;i<energy1->size();++i){
                for(UInt_t j=0;j<energy2->size();++j){
                    sum[i][j]=abs(energy1->at(i) + energy2->at(j));
                    diff[i][j]=abs(energy1->at(i) - energy2->at(j));
                }
        }
        if(energy1->size()>=energy2->size()){
            //trovo gli indici delle particelle e li metto in index;
            return index;
        }
        else 
        //trovo gli indici delle particelle vere e li metto in index;
        return index;
    }

    template<typename T>
    void FillingCharge(std::vector<T>* v,
    TH1F* histo,std::vector<int>* charge,int Charge=8,double var=0){
        if(var==0){
        for(UInt_t l=0;l<v->size();++l){
            if(charge->at(l)==Charge){
                histo->Fill(v->at(l));
            }
        }
        }
        else{
            for(UInt_t l=0;l<v->size();++l){
            if(charge->at(l)==Charge){
                histo->Fill((var));
            }
        }
        }
    };