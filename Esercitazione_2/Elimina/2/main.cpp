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


   int steps_rw=20;  // numero di passi che fa il singolo rw
   int N_rw=15;  // numero di random walk eseguiti



   vector <double> modulo (N_rw*steps_rw, 0.);


   vector <double> modulo2 (N_rw*steps_rw, 0.);

   vector <double> ave (N, 0.);
   vector <double> ave2 (N, 0.);
   vector <double> sum_progr (N, 0.);
   vector <double> sum2_progr (N, 0.);
   vector <double> err_progr (N, 0.);


   if (M%N!=0)
       cout << "Attenzione! Numero blocchi e numero di lanci non divisibili ";

     cout << "AAAA " << N*steps_rw << endl; 


    double num1=0, num2=0, x=0, y=0, z=0, mod=0, sum=0;




    for (int j=0; j<N_rw; ++j){
        

      sum=0;
      x=y=z=0;


        for(int i=0; i<steps_rw; ++i){
            num1=rnd.Rannyu(0,3);
            num2=rnd.Rannyu();
            
 //           cout << num1 << " _____ " << num2 << endl;
            
            if (num1 <= 1){
                if (num2<=0.5)         
                  x=x-1;  // mi muovo a sx
                else 
                  x=x+1;  // mi muovo a dx
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

            modulo[j*steps_rw+i]=mod;             // alla fine salvo in modulo tutte le posizioni di tutti i rw
            modulo2[j*steps_rw+i]=mod*mod;

            cout << "BBB " << i << "\t" << modulo[j*steps_rw+i] << endl;

        }   

      }    


      // PARTE MONTECARLO

15*20=300
        int M=10; //numero di stime (=step per blocco)
        int N=8; //numero di blocchi
        int L=M/N;






   /*
      ave[j]=double(sum)/(M);   //media tra i blocchi i-esimo
//     cout << j << "media " <<ave[j] << endl;
      ave2[j]=(ave[j])*(ave[j]);

         
        x=0;
        y=0;
        z=0;
            
            
    }















   for(int i=0; i<M; i++){
      x=rnd.Rannyu(a,b);
	   	f=Pi*0.5*cos(Pi*x*0.5);
	   	integrale[i]=f;			// sarebbe f*(b-a) ma b-a=1
   }
   
   for (int i=0; i<N; i++){
        double sum=0;
        int k=0;
        
        for (int j=0; j<L; j++){    //L=n* step in ogni blocco
            k=j+i*L;
            sum=sum+integrale[k];
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
   
*/




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
