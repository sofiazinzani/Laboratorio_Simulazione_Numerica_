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



    int k=10000;
    int N[4]={1,2,10,100};
    double sum_Uni=0.;
    double sum_Esp=0.;
    double sum_Lor=0.;
    vector <double> uniform (4*k, 0.);
    vector <double> esponential (4*k, 0.);
    vector <double> lorentzian (4*k, 0.);


    
    cout << N[0] << "\t" << N[1] << "\t" << N[2] << "\t" << N[3] << "\t" << endl;


    ofstream Write;

    for (int i=0; i<4; i++){
    	
    	for (int j=0; j<k; j++){


    		for (int l=0; l<N[i]; l++){
    				sum_Uni=sum_Uni+rnd.Rannyu();
    				sum_Esp=sum_Esp+rnd.Esponential(1.);
    				sum_Lor=sum_Lor+rnd.Lorentzian(1.);

    		}

    		sum_Uni=sum_Uni/N[i];
    		sum_Esp=sum_Esp/N[i];
		    sum_Lor=sum_Lor/N[i];


    		uniform[(i*k)+j]=sum_Uni;
    		esponential[(i*k)+j]=sum_Esp;
    		lorentzian[(i*k)+j]=sum_Lor;

        
    		sum_Uni=0.;
    		sum_Esp=0.;
    		sum_Lor=0.;
    	}
    }


    Write.open("Uniform.dat");
      for (int j=0; j<k; j++){
        Write << j << "\t" << uniform[j] << "\t" << uniform[(1*k)+j] << "\t" << uniform[(2*k)+j] << "\t" << uniform[(3*k)+j]<< endl;
      }
    Write.close();   


    Write.open("Esponential.dat");
      for (int j=0; j<k; j++){
        Write << j << "\t" << esponential[j] << "\t" << esponential[(1*k)+j] << "\t" << esponential[(2*k)+j] << "\t" << esponential[(3*k)+j]<< endl;
      }
    Write.close();  


    Write.open("Lorentzian.dat");
      for (int j=0; j<k; j++){
        Write << j << "\t" << lorentzian[j] << "\t" << lorentzian[(1*k)+j] << "\t" << lorentzian[(2*k)+j] << "\t" << lorentzian[(3*k)+j]<< endl;
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
