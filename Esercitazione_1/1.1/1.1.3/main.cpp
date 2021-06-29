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



//______________________________________________________________________________________________
//   	CALCOLO CHI-QUADRO
//______________________________________________________________________________________________



    int M=100;  //numero di celle
    double lenght=10000;    //=n . Ovvero numero totale di numeri casuali da estrarre= numero totale di numeri tra (0,1)
    double med=lenght/M;	//n/M

    vector <double> n (lenght, 0.); //contiene i 10000 numeri di ogni cella
    vector <double> chi2 (M, 0.);
    


    ofstream Write;
    Write.open("Chi2.dat");

    
    for(int j=0; j<M; j++){
    
        for(int i=0; i<lenght; i++){
            n[i]=rnd.Rannyu();
            chi2[j]=(chi2[j] + (n[i]-med)*(n[i]-med))/med;
        }
        
        Write << j << "\t" << chi2[j] << endl;
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
