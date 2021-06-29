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





//___________________ Con integrazione a intervallini

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


//_______________________________________________________________________-


   int M=10000; //numero di stime dell'integrale (=step per blocco)
   int N=100; //numero di blocchi
   int L=M/N;
   int n_T=100;

   double z=0;
   double s=0;
   double s0=100;
   double r=0.1;
   double sigma=0.25;
   double T=1;
   double k=100;

   vector <double> C (M, 0.);
   vector <double> P (M, 0.);

   vector <double> ave_C (N, 0.);

   vector <double> ave_P (N, 0.);

   vector <double> ave2_C (N, 0.);
   vector <double> ave2_P (N, 0.);
   vector <double> sum_progr_C (N, 0.);
   vector <double> sum_progr_P (N, 0.);
   vector <double> sum2_progr_C (N, 0.);
   vector <double> sum2_progr_P (N, 0.);
   vector <double> err_progr_C (N, 0.);
   vector <double> err_progr_P (N, 0.);


   if (M%N!=0)
       cout << "Attenzione! Numero blocchi e numero di lanci non divisibili ";



   for(int i=0; i<M; i++){

      for (int j=0; j<n_T; j++){
        z=rnd.Gauss(0,1);
        if (j==0)
          s=s0*exp((r-(sigma*sigma*0.5))*(double(j)/n_T)+sigma*z*sqrt((double(j)/n_T)));


        else
          s=s*exp((r-(sigma*sigma*0.5))*((double(j)/n_T)-(double(j-1)/n_T))+sigma*z*sqrt(((double(j)/n_T)-(double(j-1)/n_T))));
      }
      
	   	

      cout << "s=  " << s << endl;
      if (s-k>0){
        C[i]=exp(-r*T)*(s-k);
        P[i]=0;
      }

      else {
        C[i]=0;
        P[i]=exp(-r*T)*(k-s); 
      }
   }
   
   for (int i=0; i<N; i++){
        double sum_C=0;
        double sum_P=0;
        int k=0;
        
        for (int j=0; j<L; j++){    //L=n* step in ogni blocco
            k=j+i*L;
            sum_C=sum_C+C[k];
            sum_P=sum_P+P[k];
        }
        
        ave_C[i]=double(sum_C/L);   //media del blocco i-esimo
        ave2_C[i]=(ave_C[i])*(ave_C[i]);
        ave_P[i]=double(sum_P/L);   //media del blocco i-esimo
        ave2_P[i]=(ave_P[i])*(ave_P[i]);

    }




    ofstream Write;
    Write.open("Dati.dat");
   
   
    for (int i=0; i<N; i++){

        for (int j=0; j<i+1; j++){
            sum_progr_C[i]=sum_progr_C[i]+ave_C[j];
            sum2_progr_C[i]=sum2_progr_C[i]+ave2_C[j];

            sum_progr_P[i]=sum_progr_P[i]+ave_P[j];
            sum2_progr_P[i]=sum2_progr_P[i]+ave2_P[j];
        }
        
        sum_progr_C[i]=double(sum_progr_C[i]/(i+1));
        sum2_progr_C[i]=double(sum2_progr_C[i]/(i+1));
        err_progr_C[i]=funz_error(sum_progr_C, sum2_progr_C, i);

        sum_progr_P[i]=double(sum_progr_P[i]/(i+1));
        sum2_progr_P[i]=double(sum2_progr_P[i]/(i+1));
        err_progr_P[i]=funz_error(sum_progr_P, sum2_progr_P, i);

        Write << i << "\t" << sum_progr_C[i] << "\t" << err_progr_C[i] << "\t" << sum_progr_P[i] << "\t" << err_progr_P[i]  << endl;
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
