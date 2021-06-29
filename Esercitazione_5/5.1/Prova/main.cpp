

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm> // per transform
#include <functional> // per plus
#include <cmath>
#include "random.h"

#include "metropolis.h"


using namespace std;

double funz_error (vector <double>, vector <double>, int);
void DataBlocking (vector <double>, int , const char* );


int main (int argc, char *argv[]){

    
    
    ofstream position("Posizioni.dat");
    
    int Np=1000, Nb=100; // Np= Numero Passi, Nb= Numero Blocchi
    vector <double> AV (Nb, 0.);
    double Start[3]={1.,1.,1.};
    double sum;

    double* Pos;
    
    
    
    for (int k=0; k<2; k++){
        
        Metropolis Met(Start,1.,k);
        Met.Equilibration(0.50);
    
        for (int j=0; j<Nb; ++j){
        
            for(int i=0; i<Np; ++i){
            
                
                Met.Make_Pass();
                Pos=Met.GetPosition();
                sum+= sqrt(Pos[0]*Pos[0]+Pos[1]*Pos[1]+Pos[2]*Pos[2]);
                if(((i+1)+(j+1)*Np)%100 == 0){position<<Pos[0]<<"    "<<Pos[1]<<"    "<<Pos[2]<<"    "<<endl;}                //stampo 1 punto ogni 100
            }
            AV[j]=sum/double(Np);

        }
        string str="Risultati"+to_string(k)+".dat";
        const char * outputfile = str.c_str();
        DataBlocking ( AV,  Nb, outputfile);
    }
    
    
    

    position.close();
    
    return 0;
}

















double funz_error (vector <double> AV, vector <double> AV2, int n)
{
   if (n==0)
       return 0;
   else
       return sqrt(double((AV2[n] - AV[n]*AV[n])/n));
};


void DataBlocking (vector <double> Dati_Blk, int Num_Dati_Blk, const char* File_Output){
    
    
    //DuePi
    vector <double> sum_progr (Num_Dati_Blk, 0.);
    vector <double> sum2_progr (Num_Dati_Blk, 0.);
    vector <double> err_progr (Num_Dati_Blk, 0.);
    
    
    
    ofstream Write(File_Output);
   
   
    for (int i=0; i<Num_Dati_Blk; i++){

        for (int j=0; j<i+1; j++){
            sum_progr[i]=sum_progr[i]+Dati_Blk[j];
            sum2_progr[i]=sum2_progr[i]+Dati_Blk[j]*Dati_Blk[j];
        }
        
        //cout << "somma progressiva " << sum_progr[i] << endl;
        sum_progr[i]=double(sum_progr[i])/(i+1);
        sum2_progr[i]=double(sum2_progr[i])/(i+1);
        err_progr[i]=funz_error(sum_progr, sum2_progr, i);

        //cout << "media progressiva " << sum_progr[i] << endl;

        Write << i << "\t" << sum_progr[i] << "\t" << err_progr[i] << endl;


    }
   
    Write.close();
    
};
