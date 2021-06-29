
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm> // per transform
#include <functional> // per plus
#include <cmath>
#include "random.h"


using namespace std;


vector <double> sigmafunz(vector <double>, vector <double>, int, int);

int main (int argc, char *argv[]){

    Random rnd;
   int seed[4];
   int p1, p2;
   int Np=100, Nb=10000; // Np= Numero Passi, Nb= Numero Blocchi
    vector <double> vettoremodulosingleblocco (Np, 0.);
    vector <double> vettoremoduloquadrosingleblocco (Np, 0.);
    vector <double> vettoremedia (Np, 0.);   //lungo Np
    vector <double> vettoremediadeiquadrati (Np, 0.);   //lungo Np
    vector <double> sigma;

    
   double phi=0, theta=0, num=0, r=1., x=0, y=0, z=0, modulo=0;
   double DuePi=2*M_PI;

   
   
   ifstream Primes("Primes");
   if (Primes.is_open()){
      Primes >> p1 >> p2 ;
   } else cerr << "PROBLEM: Unable to open Primes" << endl;
   Primes.close();

   ifstream input("seed.in");
   string property;
   if (input.is_open()){
      while ( !input.eof() ){
         input >> property;
         if( property == "RANDOMSEED" ){
            input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
            rnd.SetRandom(seed,p1,p2);
         }
      }
      input.close();
   } else cerr << "PROBLEM: Unable to open seed.in" << endl;

   
   
//______________________________________________________________________________________________________   



    for (int j=0; j<Nb; ++j){
        
        for(int i=0; i<Np; ++i){
            phi=rnd.Rannyu(0, DuePi);
            num=rnd.Rannyu(-1., 1.);
            theta=acos(num);
            
            
            x=x+r*sin(theta)*cos(phi);
            y=y+r*sin(theta)*sin(phi);
            z=z+r*cos(theta);
            
            
            modulo=x*x+y*y+z*z;
            vettoremodulosingleblocco[i]=modulo;
            vettoremoduloquadrosingleblocco[i]=modulo*modulo;
        }       
        
        
            std::transform (vettoremedia.begin(), vettoremedia.end(), vettoremodulosingleblocco.begin(), vettoremedia.begin(), plus<double>());
            
            std::transform (vettoremediadeiquadrati.begin(), vettoremediadeiquadrati.end(), vettoremoduloquadrosingleblocco.begin(), vettoremediadeiquadrati.begin(), plus<double>());
            
            std::fill (vettoremodulosingleblocco.begin(), vettoremodulosingleblocco.end(), 0);  // mette a zero le componenti del vettore
            
            std::fill (vettoremoduloquadrosingleblocco.begin(), vettoremoduloquadrosingleblocco.end(), 0);  // mette a zero le componenti del vettore
              
            x=0;
            y=0;
            z=0;
            
            
    }
    
    
    for (int i=0; i<Np; ++i){ 
        vettoremedia[i]=vettoremedia[i]/double(Nb);
    }
    
    for (int i=0; i<Np; ++i){ 
        vettoremediadeiquadrati[i]=vettoremediadeiquadrati[i]/double(Nb);
    }
    
    // Controllo disagiato
        cout << "verifico che la lunghezza del vettoremedie sia 100. Stampo e trovo:  " << vettoremedia.size() << endl;

        
    sigma=sigmafunz(vettoremedia, vettoremediadeiquadrati, Nb, Np);
        
        
   ofstream Write;
   Write.open("Vettore_media.dat");    
   
    Write << 0 << "  " << 0 << "  " << 0 <<endl;
    
   for (int i=1; i<=Np; ++i){
        Write << i << "  " << sqrt(vettoremedia[i-1]) << "  " << (1./(2.*sqrt(vettoremedia[i-1])))*sigma[i-1] << endl;    
   }
            
   Write.close();

   rnd.SaveSeed();

   return 0;
}



//__________________________________________________________________________________________________________


vector <double> sigmafunz (vector <double> mediavett, vector <double> mediadeiquadrvett, int Nblocchi, int Npassi){

   double sig=0; 
   vector <double> sigma;   
   
    for (int i=0;  i<Npassi; ++i){    //blocchi 10000
        
        sig=sqrt((mediadeiquadrvett[i] -(mediavett[i]*mediavett[i]))/double(Nblocchi-1));  
        
        sigma.push_back(sig);        
    }

    return sigma;   //sigma 100
};

