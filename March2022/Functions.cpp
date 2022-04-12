
#include "Functions.hpp"




bool foot::GeometryMSDTGLine(std::vector<std::vector<Float_t>> &coordinates,
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

//////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    void print(std::vector<T>* v){
        for(UInt_t i=0;i<v->size();++i){
            std::cout<<" "<<v->at(i)<<" ";
        }
        std::cout<<"            ";
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////



    template<typename T,typename S>
    std::vector<foot::ind> foot::FindTrueTW(std::vector<T>* energy1, std::vector<T>* energy2
    ,std::vector<S>* MSDPoints,int TWPoints){
            std::vector<ind> index;
            std::vector<std::vector<Float_t>> diff(energy1->size(),std::vector<T>(energy2->size()));
            ind indice;
            double difference=0;
            for(UInt_t i=0;i<energy1->size();++i){
                for(UInt_t j=0;j<energy2->size();++j){
                    diff[i][j]=abs(energy1->at(i) - energy2->at(j));
                }
        }
            for(UInt_t i=0;i<energy1->size();++i){
                difference=diff[i][0]; 
                 indice.x=energy1->at(i); 
                for(UInt_t j=0;j< energy2->size();++j){
                    if(difference>=diff[i][j]){
                        difference=diff[i][j];
                        indice.y=energy2->at(j);
                    }
                    else{
                        indice.y=energy2->at(j);
                    }
                }
               index.push_back(indice);
            }
            return index;
    }

    /////////////////////////////////////////////////////////////////////////////////////////
    template<typename T>
    bool foot::GeometryMSD(){
        return true;
    }

//////////////////////////////////////////////////////////////////////////////////////////////
    
    template<typename T>
    void foot::Fill(std::vector<T>* v,
    TH1F* histo,std::vector<int>* charge,int Charge,double var){
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
    }

    ////////////////////////////////////////////////////////////////////////////////////////////