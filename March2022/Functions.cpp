#include "Functions.hpp"

 static bool foot::GeometryMSDTGLine(std::vector<std::vector<Float_t>> &coordinates,int counter=0,
                        Float_t xTarget = 2, Float_t yTarget = 2,
                        Float_t errorxyMSd=0.014,Float_t errorZ=0.01) {
    ///////////////////////////////////////////////////////////////////////////////
    /////////////Ritorna Falso se la proiezione delle rette prolungate esce dal
    ///target//////////////
    ///////////////////////////////////////////////////////////////////////////////
    Float_t x_[3];
    Float_t y_[3];
    Float_t z_[3];
    for (int i = 0; i < 3; ++i) {
        x_[i] = coordinates[0][i];
    }
    for (int i = 0; i < 3; ++i) {
        y_[i] = coordinates[1][i];
    }
    for (int i = 0; i < 3; ++i) {
        z_[i] = coordinates[2][i];
    }
    Float_t errorxy[3]={errorxyMSd,errorxyMSd,errorxyMSd};
    Float_t errorZeta[3]={errorZ,errorZ,errorZ};
    TGraphErrors XZ(3, z_, x_,errorZeta,errorxy);
    TGraphErrors YZ(3, z_, y_,errorZeta,errorxy);
    TF1 fitXZ("fitXZ", "[0]*x+[1]", 0, 50);
    TF1 fitYZ("fitYZ", "[0]*x+[1]", 0, 50);
    XZ.Fit("fitXZ","RQ");
    YZ.Fit("fitYZ","RQ");
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

  static  void foot::GeometryPrimaryDraw(std::vector<std::vector<Float_t>>& x,
     std::vector<std::vector<Float_t>>& y,UInt_t dimension=0){
    TCanvas *c1= new TCanvas("c1","Schema 3 D geometria");
    TGLViewer *view =(TGLViewer*)gPad->GetViewer3D();
    TGeoManager *man= new TGeoManager();
    TGeoVolume *top=man->MakeBox("box",NULL,180,180,189.40);
    TGeoVolume *TGT=man->MakeBox("TW",NULL,25.5,25.5,0.5);
    TGeoVolume *MSD=man->MakeBox("MSD",NULL,55.5,55.5,1.45);
    TGeoVolume *TW=man->MakeBox("TW",NULL,141.7,141.7,4);
    MSD->SetLineColor(kGray);
    TGeoHMatrix *trans_rootMSD1=new TGeoHMatrix("TransROT");
    trans_rootMSD1->SetDz(40);
    TGeoHMatrix *trans_rootMSD2=new TGeoHMatrix("TransROT");
    trans_rootMSD2->SetDz(3.8+40);
    TGeoHMatrix *trans_rootMSD3=new TGeoHMatrix("TransROT1");
    trans_rootMSD3->SetDz(3.8+3.8+40);
    TGeoHMatrix *transRootTW=new TGeoHMatrix("TransROT1");
    transRootTW->SetDz(180);
    man->SetTopVolume(top);
    Float_t MSDZ0 {40};
    Float_t MSDZ1  {45.15};
    Float_t MSDZ2 {40 + 3.8 + 3.8+1.25};
    std::vector<Float_t> MSDZ = {0,MSDZ0, MSDZ1, MSDZ2,189.4};
    top->AddNode(MSD,0,trans_rootMSD1);
    top->AddNode(MSD,1,trans_rootMSD2);
    top->AddNode(MSD,2,trans_rootMSD3);
    top->AddNode(TGT,3);
    top->AddNode(TW,4,transRootTW);
    std::vector<TPolyLine3D*> lines(dimension);
    for(UInt_t j=0;j<dimension;++j){
        lines[j]=new TPolyLine3D();
        for(UInt_t i=0;i<x[j].size();++i){

                 {lines[j]->SetPoint(i,x[j][i],y[j][i],MSDZ[i]);}
          
        }
        lines[j]->SetLineColor(kBlue);
    }
    man->CloseGeometry();
    top->Draw("ogl");
    for(UInt_t j=0;j<dimension;++j){
        lines[j]->Draw("SAME");
    }
    c1->Print("Grafici/Immagine3DFascio.pdf");
}


//////////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
     static void print(std::vector<T>* v){
        for(UInt_t i=0;i<v->size();++i){
            std::cout<<" "<<v->at(i)<<" ";
        }
        std::cout<<"            ";
    }

///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename T, typename S>
static auto foot::BeamMSD_vs_MSDRealPoint(T BeamMSDX, T BeamMSDY,
                                    std::vector<S>* MSDX, std::vector<S>* MSDY)
    -> bool {
    T RealMSDX{MSDX->at(1)+Xalign};
    T RealMSDY{MSDY->at(1)+Yalign};
    bool x;
    bool y;
    {if(BeamMSDX==RealMSDX){
        x=true;
    }
    else if(RealMSDX<BeamMSDX){
        if((RealMSDX+MSDError_X_Y)>=(BeamMSDX-BeamMSDError_X_Y)){
            x=true;
        }
        else{
            x=false;
        }
    }
    else if(BeamMSDX<RealMSDX){
        if((BeamMSDX+BeamMSDError_X_Y)>=(RealMSDX-MSDError_X_Y)){
            x=true;
        }
        else{
            x=false;
        }
    }
    else{
        x=false;
    }
    }
   { if(BeamMSDY==RealMSDY){
        y=true;
    }
   else if(RealMSDY<BeamMSDY){
        if((RealMSDY+MSDError_X_Y)>=(BeamMSDY-BeamMSDError_X_Y)){
            y=true;
        }
        else{
            y=false;
        }
    }
    else if(BeamMSDY<RealMSDY){
        if((BeamMSDY+BeamMSDError_X_Y)>=(RealMSDY-MSDError_X_Y)){
            y=true;
        }
        else{
            y=false;
        }
    }
    else{
        y=false;
    }
   }
    return(x && y);
   
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T,typename S>
    static std::vector<foot::ind> foot::FindTrueTW(std::vector<T>* energy1, std::vector<T>* energy2
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


//////////////////////////////////////////////////////////////////////////////////////////////
    
    template<typename T>
  static  void foot::Fill(std::vector<T>* v,
    TH1F* histo,std::vector<int>* charge,int&& which_charge,double var){
        if(var==0){
        for(UInt_t l=0;l<v->size();++l){
            if(charge->at(l)==which_charge){
                histo->Fill(v->at(l));
            }
        }
        }
        else{
            for(UInt_t l=0;l<v->size();++l){
            if(charge->at(l)==which_charge){
                histo->Fill((var));
            }
        }
        }
    }

    ////////////////////////////////////////////////////////////////////////////////////////////