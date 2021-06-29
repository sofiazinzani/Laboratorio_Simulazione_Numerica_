/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/




//CHIEDERE SU COSA CAVOLO DOVREI FARE LE MEDIE!!!!!!



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

//________________________________________________________



int N=10000, M=100; // N= Numero Passi, M= Numero Blocchi
  /*  vector <double> vettoremodulosingleblocco (Np, 0.);
    vector <double> vettoremoduloquadrosingleblocco (Np, 0.);
    vector <double> vettoremedia (Np, 0.);   //lungo Np
    vector <double> vettoremediadeiquadrati (Np, 0.);   //lungo Np
    vector <double> sigma;
*/

	
	vector <double> modulo (N, 0.);
	vector <double> modulo2 (N, 0.);
	vector <double> ave (N, 0.);
	vector <double> ave2 (N, 0.);
	vector <double> sum_progr (N, 0.);
	vector <double> sum2_progr (N, 0.);
	vector <double> err_progr (N, 0.);

	double num1=0, num2=0, x=0, y=0, z=0, mod=0, sum=0;




    for (int j=0; j<N; ++j){
        

   		sum=0;

        for(int i=0; i<M; ++i){
            num1=rnd.Rannyu(0,3);
            num2=rnd.Rannyu();
            
 //           cout << num1 << " _____ " << num2 << endl;
            
            if (num1 <= 1){
                if (num2<=0.5)         
                	x=x-1;	// mi muovo a sx
                else 
                	x=x+1;	// mi muovo a dx
            }
            
            else if (1 < num1 && num1 <= 2){
                if (num2<=0.5)         
                	y=y-1;
                else 
                	y=y+1;
            }
            
            else if (2 < num1 && num1<= 3){ 
                if (num2<=0.5)         
                	z=z-1;
                else 
                	z=z+1;
            }
            
            mod=x*x+y*y+z*z;
            modulo[i]=mod;
            modulo2[i]=mod*mod;

            sum=sum+modulo[i];
        }       
   
    	ave[j]=double(sum)/(M);   //media tra i blocchi i-esimo
//     cout << j << "media " <<ave[j] << endl;
    	ave2[j]=(ave[j])*(ave[j]);

         
        x=0;
        y=0;
        z=0;
            
            
    }


    ofstream Write;
    Write.open("Prova.dat");
   
   
    for (int i=0; i<M; i++){


    	 cout << "AAAAAAA " << ave[i] << endl;
        for (int j=0; j<i+1; j++){
            sum_progr[i]=sum_progr[i]+ave[j];
            sum2_progr[i]=sum2_progr[i]+ave2[j];
        }
        
        cout << "somma progressiva " << sum_progr[i] << endl;
        sum_progr[i]=double(sum_progr[i])/(i+1);
        sum2_progr[i]=double(sum2_progr[i])/(i+1);
        err_progr[i]=funz_error(sum_progr, sum2_progr, i);

        cout << "media progressiva " << sum_progr[i] << endl;

        Write << i << "\t" << sqrt(sum_progr[i]) << "\t" << (1./(2.*sqrt(sum_progr[i])))*err_progr[i] << endl;


        //Write << i << "\t" << sqrt(ave[i]) << "\t" << (1./(2.*sqrt(ave[i])))*err_progr[i] << endl;    
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
