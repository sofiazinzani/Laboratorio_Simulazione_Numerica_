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
#include <string>
#include <cstdlib>

#include "datablockingspecial.h"

using namespace std;

double DataBlocking ( char * File_Input, int Dati_Number, int Block_Number, char * File_Output){
//essendo i file in append devo caricare solo i dati dell'ultima simulazione cioè quelli che si trovano nelle ultime Dati_Numeber righe
	double Dati[Dati_Number];
	int k=0;double x;
	ifstream dati(File_Input);
	while(dati>>x) {
		k++;
	}
	dati.close();
	dati.open(File_Input);
	for(int i=0;i<k;i++){
		dati>>x;
		if(i>=k-Dati_Number){
			Dati[i-k+Dati_Number]=x;
		}
	}
	dati.close();

//raggruppo i dati in blocchi calcolando la media per ciascun blocco
	int Block_Length=int(Dati_Number/Block_Number);
    double block[Block_Number];
    for (int i=0; i<Block_Number; i++) block[i]=0;
	for(int i=0;i<Dati_Number;i++){
		block[i/Block_Length] += Dati[i]/(double)Block_Length;
	}

//faccio il datablocking di block[]
	ofstream risul(File_Output);
	double AV[Dati_Number];
	double AV2[Dati_Number];
	double Err[Dati_Number];
	double ave2,sum;

	for (int j=0; j<Block_Number; j++){
		sum=ave2=0;
		for (int i=0; i<j+1; i++){
			sum+=block[i];
			ave2+=block[i]*block[i];
		}
		AV[j]=sum/double(j+1);
		AV2[j]=ave2/double(j+1);
		Err[j]=error(AV[j],AV2[j],j);

		if(j==0) { Err[j]=0; }

		risul<<double(j+1)<<" "<<AV[j]<<" "<<Err[j]<<endl;
	}
	risul.close();
	return 0.;
}

double DataBlockingGofr ( char * File_Input, int Dati_Number, int Block_Number, int Bin_Number, char * File_Output){
//essendo i file in append devo caricare solo i dati dell'ultima simulazione cioè quelli che si trovano nelle ultime Dati_Numeber righe
	double Dati[Dati_Number*Bin_Number];
	int k=0;double x;
	ifstream dati(File_Input);
	while(dati>>x) {
		k++;
	}
	dati.close();
	dati.open(File_Input);
	for(int i=0;i<k;i++){
		dati>>x;
		if(i>=k-Dati_Number*Bin_Number){
			Dati[i-k+Dati_Number*Bin_Number]=x;
		}
	}
	dati.close();

//raggruppo i dati in blocchi calcolando la media per ciascun blocco
	int Block_Length=int(Dati_Number/Block_Number);
    double block[Block_Number][Bin_Number];
    for (int i = 0; i<Block_Number; i++)
    {
        for (int j = 0; j<Bin_Number; j++)
            block[i][j] = 0;
    }
	for(int j=0;j<Bin_Number*Dati_Number;j++){
			block[int(j/(Block_Length*Bin_Number) )][j%Bin_Number] += Dati[j]/(double)Block_Length;
			}

	ofstream blocchi("risultati/ave_block_gofr.dat");
	for(int j=0;j<Block_Number;j++){
		for(int i=0;i<Bin_Number;i++){
			blocchi << block[j][i] << "	";
		}
		blocchi << endl;
	}
	blocchi.close();

//faccio il datablocking di block[]
	ofstream risul(File_Output);
	double AV[Dati_Number];
	double AV2[Dati_Number];
	double Err[Dati_Number];
	double ave2,sum;

for(int k=0; k<Bin_Number; k++){
	for (int j=0; j<Block_Number; j++){
		sum=ave2=0;
		for (int i=0; i<j+1; i++){
			sum+=block[i][k];
			ave2+=block[i][k]*block[i][k];
		}
		AV[j]=sum/double(j+1);
		AV2[j]=ave2/double(j+1);
		Err[j]=error(AV[j],AV2[j],j);

		if(j==0) { Err[j]=0; }

		risul << double(k+1) << "	" << double(j+1) << " " << AV[j] << " " << Err[j] << endl;
	}
}
	risul.close();
	return 0.;
}
double error(double SumAve, double SumAve2, int n){
	return sqrt( ( SumAve2-(SumAve*SumAve) )/double(n) );
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
