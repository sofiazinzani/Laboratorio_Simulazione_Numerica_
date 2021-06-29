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


   	int N=100;
   	int M=1000;
   	int L=(M/N);

	int N_thr=1000;
	int N_hit=0;

	double d=2.5; // spaziatura tra righe
	double l=2; // lunghezza ago
	double x=0;
	double theta=0;
	double a=0,b=0;
    

	vector <double> Pi (M, 0.);
	vector <double> ave (N, 0.);
	vector <double> ave2 (N, 0.);
	vector <double> sum_progr (N, 0.);
	vector <double> sum2_progr (N, 0.);
	vector <double> err_progr (N, 0.);


	for (int j=0; j<N; j++){

		for (int i=0; i<M; i++){

		   	for (int k=0; k<N_thr; k++){
		        x=rnd.Rannyu(0., d*0.5);	//distanza del centro dell'ago rispetto alla linea più vicina

		        do {						// Campiono uniformemente l'angolo tra 0 e pigreco
			     	a=rnd.Rannyu(-1,1);
					b=rnd.Rannyu(-1,1);

					if (a*a+b*b<=1){
						if (b>0){
							if (a>=0)
								theta=acos(a/sqrt(a*a+b*b));
							else
								theta=acos(-a/sqrt(a*a+b*b));
						}
						else
							theta=0;
					}
					else
						theta=0;
				}
				while (theta==0);


		        if (x<=l*0.5*sin(theta))
		            N_hit+=1;
	    	}
    
    		Pi[i]=2*l*N_thr/(N_hit*d);
	   	
    		N_hit=0;
    	//	cout << Pi[i] << endl;
	   	}

	   	for (int k=0; k<L; k++){
			int appo=k+j*L;
			ave[j]=ave[j]+Pi[appo];
		}
			
        ave[j]=ave[j]/(L);   //media del blocco i-esimo
        ave2[j]=(ave[j])*(ave[j]);

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