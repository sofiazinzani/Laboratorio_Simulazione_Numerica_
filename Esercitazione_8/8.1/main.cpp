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
#include <cmath>

#include "random.h"
#include "metropolis.h"
#include "datablocking.h"

using namespace std;

double Psi(double, double, double);
double Psi_Second(double, double, double);
double Potential(double);

int main (int argc, char *argv[]){
	if(argc !=3){
		cout<<" Errore: inserire ./main.exe mu sigma ";
	}

	int M=100000;
	int N=1000; // step per blk
	int L=M/N; // blk
	double AV[L];

	double Start=0.0;
	double ene, sum, mu, sigma;
	mu = atof(argv[1]);
	sigma = atof(argv[2]);
	Metropolis Met(Start, mu, sigma, 1.);
	Met.Equilibration(0.50);

	for (int l=0;l<L;l++){ // ciclo sui blk
		sum=0;
		for (int i=0;i<N; i++){
			Met.MakePass();
			ene = -0.5*Psi_Second(Met.GetPosition(),mu,sigma)/Psi(Met.GetPosition(),mu,sigma)+Potential(Met.GetPosition()); // H= -h^2/2m * d^2/dx^2 psi(sigma, mu, T, x) / psi(sigma, mu, T, x) + V(x)     dove abbiamo posto h=m=1
			sum += ene;
		}
		AV[l]=sum/double(N);
	}

	Data_Blocking (AV, L);

	ifstream risul("Risultati.dat");
	ofstream energie("Energie.dat", ios::app);
	double x;
	while(! risul.eof()){
		risul >> x;
	}
	energie << mu << "	" << sigma << "	" << x << endl;
	energie.close();
	risul.close();
	
	return 0;
}


double Psi(double x,double mu, double sigma){   //    psi(sigma, mu, T, x) = e^[-(x-mu)^2/(2*sigma^2)] + e^[-(x+mu)^2/(2*sigma^2)]
	return (exp( -(x-mu)*(x-mu)/(2.*sigma*sigma) ) + exp( -(x+mu)*(x+mu)/(2.*sigma*sigma) ) );
}
double Psi_Second(double x, double mu, double sigma){   // d^2/dx^2 psi(sigma, mu, T, x)
	return (exp( -(x-mu)*(x-mu)/(2.*sigma*sigma) )*( pow((x-mu)/(sigma*sigma),2.) - 1./pow(sigma,2.) ) + exp( -(x+mu)*(x+mu)/(2.*sigma*sigma) ) * ( pow((x+mu)/(sigma*sigma),2.) - 1./pow(sigma,2.) ) );
}
double Potential(double x){
	return pow(x,4.)-5./2.*pow(x,2.);
}
/****************************************************************
*****************************************************************
    _/    _/  _/_/_/  _/       Numerical Simulation Laboratory
   _/_/  _/ _/       _/       Physics Department
  _/  _/_/    _/    _/       Universita' degli Studi di Milano
 _/    _/       _/ _/       Prof. D.E. Galli
_/    _/  _/_/_/  _/_/_/_/ email: Davide.Galli@unimi.it
*****************************************************************
*****************************************************************/
