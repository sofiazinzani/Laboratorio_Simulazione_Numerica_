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
#include <math.h>
#include <vector>
#include "random.h"

using namespace std;

double funz_error (vector <double>, vector <double>, int n);




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



   //___________________________________________________________________
   
   
    int M=100000; //Steps totali
    int N=100;      //Block
    int L=int(M/N); // Steps per blocco

    vector <double> r (M, 0.);
    vector <double> x (N, 0.);
    vector <double> ave (N, 0.);
    vector <double> ave2 (N, 0.);
    vector <double> sum_progr (N, 0.);
    vector <double> sum2_progr (N, 0.);
    vector <double> err_progr (N, 0.);

   if (M%N!=0)
       cout << "Attenzione! Numero blocchi e numero di lanci non divisibili ";
    
   for(int i=0; i<M; i++){
      r[i]=rnd.Rannyu();
   }
   
   for (int i=0; i<N; i++){
        double sum=0;
        int k=0;
        
        for (int j=0; j<L; j++){    //L=n* step in ogni blocco
            k=j+i*L;
            sum=sum+(r[k]-0.5)*(r[k]-0.5);
        }
        
        ave[i]=double(sum/L);   //media del blocco i-esimo
        ave2[i]=(ave[i])*(ave[i]);

    }

   
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

        Write << i << "\t" << sum_progr[i] << "\t" << err_progr[i] << endl;
    }
   
    Write.close();
   
   
   rnd.SaveSeed();
   return 0;
}


//___ IMPLEMENTAZIONE FUNZIONE _______

double funz_error (vector <double> AV, vector <double> AV2, int n)
{
   if (n==0) 
       return 0;
   else
       return sqrt(double((AV2[n] - AV[n]*AV[n])/n));
};

/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
