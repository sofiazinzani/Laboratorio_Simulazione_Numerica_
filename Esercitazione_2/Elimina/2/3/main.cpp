/*****************************************************************
****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
/*
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm> // per transform
#include <functional> // per plus
#include "random.h"

using namespace std;

int main (int argc, char *argv[]){

    Random rnd;
   int seed[4];
   int p1, p2;
   int Np=100, Nb=10000; // Np= Numero Passi, Nb= Numero Blocchi
    vector <double> vettoremoduli;  //lungo Np*Nb
    vector <double> vettoremedia (Np, 0.);   //lungo Np

    
   double num1=0, num2=0, x=0, y=0, z=0, modulo=0;

   
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
            num1=rnd.Rannyu(0,3);
            num2=rnd.Rannyu();
            
 //           cout << num1 << " _____ " << num2 << endl;
            
            if (num1 <= 1){
                if (num2<=0.5)         x=x-1;
                else x=x+1;
            }
            
            else if (1 < num1 && num1 <= 2){
                if (num2<=0.5)         y=y-1;
                else y=y+1;
            }
            
            else if (2 < num1 && num1<= 3){ 
                if (num2<=0.5)         z=z-1;
                else z=z+1;
            }
            
            modulo=x*x+y*y+z*z;
            vettoremoduli.push_back(modulo);
        }       
        
        x=0;
        y=0;
        z=0;
    }

    
      // Controllo disagiato
        cout << "verifico che la lunghezza del vettoremodulo sia 100*Nb. Stampo e trovo:  "<<vettoremoduli.size() << endl;
        
    

    
        for (int j=0; j<Nb; ++j){
    
            for (int i=0; i<Np; ++i){
                vettoremedia[i]=(((vettoremedia[i])*j) + vettoremoduli[(i+(j*Np))])/double(j+1);
//                vettoremedia[i]=((vettoremedia[i]) + vettoremoduli[(i+(j*Np))]);
            }
        }
        
        

   
    // Controllo disagiato
        cout << "verifico che la lunghezza del vettoremedie sia 100. Stampo e trovo:  "<<vettoremedia.size() << endl;
        

    
        
        
   ofstream Write;
   Write.open("Vettore_media.dat");    
   
   for (int i=0; i<Np; ++i){
        Write << i << "  " << vettoremedia[i] << endl;    
   }
            
   Write.close();

   rnd.SaveSeed();

   return 0;
}
*/


/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/



#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <algorithm> // per transform
#include <functional> // per plus
#include "random.h"

using namespace std;


double funz_error (vector <double> AV, vector <double> AV2, int n);



int main (int argc, char *argv[]){

    Random rnd;
   int seed[4];
   int p1, p2;


   
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


      int N=3, M=2; // Np=N Numero Passi, Nb= M Numero Blocchi

      int lunghezza_rw=3;
      int quanti_rw=6;

    double rw [lunghezza_rw][quanti_rw];
    double ave [lunghezza_rw][N];


    vector <double> step (N, 0.);


   vector <double> ave2 (N, 0.);
   vector <double> sum_progr (N, 0.);
   vector <double> sum2_progr (N, 0.);
   vector <double> err_progr (N, 0.);

    
   double num1=0, num2=0, x=0, y=0, z=0, mod=0;


    for (int j=0; j<quanti_rw; ++j){      // ho costruito i rw
        
        for(int i=0; i<lunghezza_rw; ++i){
            num1=rnd.Rannyu(0,3);
            num2=rnd.Rannyu();

            
            if (num1 <= 1){
                if (num2<=0.5)         x=x-1;
                else x=x+1;
            }
            
            else if (1 < num1 && num1 <= 2){
                if (num2<=0.5)         y=y-1;
                else y=y+1;
            }
            
            else if (2 < num1 && num1<= 3){ 
                if (num2<=0.5)         z=z-1;
                else z=z+1;
            }
            
            mod=x*x+y*y+z*z;

            rw[i][j]=mod;


            cout << j << " AAA \t " << i << " \t " << rw[i][j] << endl;
        }    

            x=0;
            y=0;
            z=0;   
      }


// creo step e blocchi MC

for (int j=0; j<N; j++){
      for (int i=0; i<M; i++){


        ave[0][j]=ave[0][j]+rw[0][j*M+i];
        cout << j << " BBB \t " << i << " \t " << ave[j][0] << endl;

      }
}

/*
            ave[j]=ave[j]/M;
            ave2[j]=(ave[j])*(ave[j]);

            x=0;
            y=0;
            z=0;
            
            

    cout << "ave " << ave[j] << endl;
    

    }
*/

/*



    ofstream Write;
    Write.open("Dati.dat");
   
   
    for (int i=0; i<N; i++){

        for (int j=0; j<i+1; j++){
            sum_progr[i]=sum_progr[i]+ave[j];
            sum2_progr[i]=sum2_progr[i]+ave2[j];
        }
        
        sum_progr[i]=double(sum_progr[i]/(i+1));
        sum2_progr[i]=double(sum2_progr[i]/(i+1));
        err_progr[i]=funz_error(sum_progr, sum2_progr, i);


        Write << i << "\t" << sqrt(sum_progr[i]) << "\t" << (1./(2.*sqrt(ave[i])))*err_progr[i] << endl; 
    }
   
    Write.close();
   
*/


   rnd.SaveSeed();

   return 0;
}



//__________________________________________________________________________________________________________


double funz_error (vector <double> AV, vector <double> AV2, int n)
{
   if (n==0) 
       return 0;
   else
       return sqrt(double((AV2[n] - AV[n]*AV[n])/n));
};

