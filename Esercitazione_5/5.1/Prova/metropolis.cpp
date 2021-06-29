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
#include <cmath>
#include <cstdlib>

#include "metropolis.h"
#include "random.h"

using namespace std;

Metropolis :: Metropolis (double* Position, double Delta,int i){
	for(int i=0;i<3;i++){
		pos[i]=Position[i];
	}
	delta=Delta;
	Acceptance=0.;
	Ntot=0;
	Nacc=0;
	f=i;
}

Metropolis ::	~Metropolis() {}

bool Metropolis ::  Make_Pass(){

    double A=0;
    double pos_new[3];

  
    for(int i=0;i<3;i++){
       pos_new[i]=rnd.Rannyu(pos[i]-delta/2.,pos[i]+delta/2.);
//        pos_new[i]=rnd.Gauss(pos[i],delta);
    }
    
    if(f==0) {A=min(1., psi_ground(pos_new[0], pos_new[1], pos_new[2])/psi_ground(pos[0], pos[1], pos[2])); }
    if(f==1) {A=min(1., psi_2p(pos_new[0], pos_new[1], pos_new[2])/psi_2p(pos[0], pos[1], pos[2])); }
    
    double k=rnd.Rannyu();
    
    if(k<=A) {
        for(int i=0;i<3;i++){
            pos[i]=pos_new[i];
        }
        Ntot++;
        Nacc++;
        Acceptance=double(Nacc)/double(Ntot);
        return true;
    }
    else {
        Ntot++;
        Acceptance=double(Nacc)/double(Ntot);
        return false;
    }
    
}


double* Metropolis :: GetPosition(){
	return pos;
}

double Metropolis :: GetAcceptance(){
	return Acceptance;
}

double Metropolis :: Equilibration(double Desire_Acceptance){
	cout<<"Equilibration: \nDesire acceptance = "<<Desire_Acceptance<<endl;
	cout<<" Acc 	  Delta  Numero_correzioni"<<endl;
	for(int i=0;i<10000;i++){
		if(Acceptance==Desire_Acceptance){
			cout<<Acceptance<<"	"<<delta<<"		"<<i<<endl;
			break;
		}
		Ntot=Nacc=0;
		for(int j=0;j<100;j++){
			Make_Pass();
		}
//		cout<<Acceptance<<"	"<<delta<<"		"<<i<<endl;
		if(Acceptance<Desire_Acceptance){delta=delta-1./(i+1.);}
		if(Acceptance>Desire_Acceptance){delta=delta+1./(i+1.);}
		if(i==9999){
			cout<<Acceptance<<"	"<<delta<<"		"<<i<<endl;
			cout<<"Dopo "<<i+1<<" tentativi non ho raggiunto il valore di accettazione desiderato \n Acceptance ="<<Acceptance<<endl;}
	}
	return Acceptance;
}




double psi_ground (double x,double y,double z){
    double r=sqrt(x*x+y*y+z*z);
    return M_PI*exp(-2*r);
}

double psi_2p (double x,double y,double z){
    double r=sqrt(x*x+y*y+z*z);
    double CosTheta=z/r;
    return 1./(32.*M_PI)*exp(-r)*pow(r*CosTheta,2);
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
