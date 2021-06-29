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
#include <ostream>
#include <cmath>
#include <iomanip>
#include "Monte_Carlo_ISING_1D.h"

using namespace std;

int main()
{

  Input(); //Inizialization
  for(int iblk=1; iblk <= nblk; ++iblk) //Simulation
  {
    Reset(iblk);   //Reset block averages
    for(int istep=1; istep <= nstep; ++istep)
    {
      Move(metro);
      Measure();
      Accumulate(); //Update block averages
    }
    Averages(iblk);   //Print results for current block
  }
  ConfFinal(); //Write final configuration
    WriteFinal();
    
  return 0;
}


void Input(void)
{
  ifstream ReadInput;

  cout << "Classic 1D Ising model             " << endl;
  cout << "Monte Carlo simulation             " << endl << endl;
  cout << "Nearest neighbour interaction      " << endl << endl;
  cout << "Boltzmann weight exp(- beta * H ), beta = 1/T " << endl << endl;
  cout << "The program uses k_B=1 and mu_B=1 units " << endl;


  
//Read input informations
  ReadInput.open("input.dat");

  ReadInput >> temp;
  beta = 1.0/temp;
  cout << "Temperature = " << temp << endl;

  ReadInput >> nspin;
  cout << "Number of spins = " << nspin << endl;

  ReadInput >> J;
  cout << "Exchange interaction = " << J << endl;

  ReadInput >> h;
  cout << "External field = " << h << endl << endl;
    
  ReadInput >> metro; // if=1 Metropolis else Gibbs

  ReadInput >> nblk;

  ReadInput >> nstep;
    
    ReadInput >> nsimulazione;
    

  if(metro==1) cout << "The program perform Metropolis moves" << endl;
  else cout << "The program perform Gibbs moves" << endl;
  cout << "Number of blocks = " << nblk << endl;
    cout << "Number of steps in one block = " << nstep << endl;
    cout << "Nsimulazione = " << nsimulazione << endl << endl;
  ReadInput.close();


//Prepare arrays for measurements
  iu = 0; //Energy
  ic = 1; //Heat capacity
  im = 2; //Magnetization
  ix = 3; //Magnetic susceptibility
 
  n_props = 4; //Number of observables

//initial configuration
    if(nsimulazione==0){
        
        //Read seed for random numbers
           int p1, p2;
           ifstream Primes("Primes");
           Primes >> p1 >> p2 ;
           Primes.close();

           ifstream input("seed.in");
           input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
           rnd.SetRandom(seed,p1,p2);
           input.close();
        
      for (int i=0; i<nspin; ++i)
      {
        if(rnd.Rannyu() >= 0.5) s[i] = 1;
        else s[i] = -1;
      }
    }
    
    else{
        
        
        
        int p1, p2;
        ifstream Primes("Primes");
        Primes >> p1 >> p2 ;
        Primes.close();

        ifstream input("seed.out");
        input >> seed[0] >> seed[1] >> seed[2] >> seed[3];
        rnd.SetRandom(seed,p1,p2);
        input.close();
     
     
        ifstream ReadConf;
        cout << "Read initial configuration from file config.final " << endl << endl;
        ReadConf.open("config.final");
        
        for (int i=0; i<nspin; ++i)
        {
            ReadConf >> s[i] ;
        }
        ReadConf.close();
        

        

      

    }
    /*
    nsimulazione=nsimulazione+1;
    ofstream WriteInput;
    WriteInput.open("input.dat");
    
    WriteInput << temp << endl;
    WriteInput << nspin << endl;
    WriteInput << J << endl;
    WriteInput << h << endl;
    WriteInput << metro << endl;
    WriteInput << nblk << endl;
    WriteInput << nstep << endl;
    WriteInput << nsimulazione << endl << endl;

    WriteInput << "  ReadInput >> temp;" << endl;
    WriteInput << "  ReadInput >> nspin;" << endl;
    WriteInput << "  ReadInput >> J;" << endl;
    WriteInput << "  ReadInput >> h;" << endl;
    WriteInput << "  ReadInput >> metro;" << endl;
    WriteInput << "  ReadInput >> nblk;" << endl;
    WriteInput << "  ReadInput >> nstep;" << endl;
    WriteInput << "  ReadInput >> nsimulazione;" << endl;

    WriteInput.close();
  
     */
//Evaluate energy etc. of the initial configuration
  Measure();

//Print initial values for the potential energy and virial
  cout << "Initial energy = " << walker[iu]/(double)nspin << endl;
}


void Move(int metro)
{
  int o;
  double p, energy_old, energy_new, sm; // p è la probabilità, sm il valore dello spin della particella o che sto considerando

  for(int i=0; i<nspin; ++i)
  {
  //Select randomly a particle (for C++ syntax, 0 <= o <= nspin-1)
    o = (int)(rnd.Rannyu()*nspin);

    if(metro==1) //Metropolis
    {
        
        sm=s[o];
        energy_old=Boltzmann(sm, o);
        sm=sm*(-1);
        energy_new=Boltzmann(sm,o);
        
        p=exp(-(energy_new-energy_old) / temp);
        if( rnd.Rannyu()<=p ) { //accetiamo la mossa
            s[o]=sm;
            accepted++;
            attempted++;
        }else{
            attempted++;
        }
// INCLUDE YOUR CODE HERE____ FATTO!
    }
    else //Gibbs sampling
    {
// INCLUDE YOUR CODE HERE____ FATTO!
        p = exp(-Boltzmann(1., o )/temp) / (exp(-Boltzmann(1.,o)/temp)+ exp(-Boltzmann(-1.,o)/temp) );//probabilità che s[o] = +1
        if( rnd.Rannyu() <= p ) {
            s[o]=+1;
        }else{
            s[o]=-1;
        }
    }
  }
}

double Boltzmann(int sm, int ip)    // ip indice di spin che sto scambiando, sm è lo spin della particella che vorrei cambiare
{
  double ene = -J * sm * ( s[Pbc(ip-1)] + s[Pbc(ip+1)] ) - h * sm;
  return ene;
}

void Measure()
{

  double u = 0.0, m = 0.0;

//cycle over spins
  for (int i=0; i<nspin; ++i)
  {
      u += -J * s[i] * s[Pbc(i+1)] - 0.5 * h * (s[i] + s[Pbc(i+1)]);
      m += s[i];
// INCLUDE YOUR CODE HERE____FATTO!
  }
    
    walker[iu] = u;
    walker[ic] = u*u;
    walker[im] = m;
    walker[ix] = m*m;


// INCLUDE YOUR CODE HERE____FATTO!
}


void Reset(int iblk) //Reset block averages
{
   
   if(iblk == 1)
   {
       for(int i=0; i<n_props; ++i)
       {
           glob_av[i] = 0;
           glob_av2[i] = 0;
       }
   }

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = 0;
   }
   blk_norm = 0;
   attempted = 0;
   accepted = 0;
}


void Accumulate(void) //Update block averages
{

   for(int i=0; i<n_props; ++i)
   {
     blk_av[i] = blk_av[i] + walker[i];
   }
   blk_norm = blk_norm + 1.0;
}


void Averages(int iblk) //Print results for current block
{
    
   ofstream Ene, Cap, Magn, Susc;

    
    cout << "Block number " << iblk << endl;
    cout << "Acceptance rate " << accepted/attempted << endl << endl;
    
    Ene.open("Risultati/output.ene_" + to_string(temp) + ".0",ios::app);
    stima_u = blk_av[iu]/blk_norm/(double)nspin; //Energy
    glob_av[iu]  += stima_u;
    glob_av2[iu] += stima_u*stima_u;
    err_u=Error(glob_av[iu],glob_av2[iu],iblk);
    if (nsimulazione==0){
        Ene << iblk <<  '\t' << stima_u << '\t' << glob_av[iu]/(double)iblk << '\t' << err_u << endl;
    }
    else{
        Ene << iblk+nblk*(nsimulazione-1) <<  '\t' << stima_u << '\t' << glob_av[iu]/(double)iblk << '\t' << err_u << endl;
    }
    Ene.close();

// INCLUDE YOUR CODE HERE
    
    
    Cap.open("Risultati/output.capacity_" + to_string(temp) + ".0",ios::app);
    stima_c = 1/(temp*temp)*(blk_av[ic]/blk_norm - blk_av[iu]*blk_av[iu]/(blk_norm*blk_norm))/(double)nspin; //Energy
    glob_av[ic]  += stima_c;
    glob_av2[ic] += stima_c*stima_c;
    err_c=Error(glob_av[ic],glob_av2[ic],iblk);
    if (nsimulazione==0){
        Cap << iblk <<  '\t' << stima_c << '\t' << glob_av[ic]/(double)iblk << '\t' << err_c << endl;
    }
    else{
        Cap << iblk+nblk*(nsimulazione-1) <<  '\t' << stima_c << '\t' << glob_av[ic]/(double)iblk << '\t' << err_c << endl;
    }
    Cap.close();


    
    Susc.open("Risultati/output.susceptibility_" + to_string(temp) + ".0",ios::app);
    stima_s = 1/(temp)*(blk_av[ix]/blk_norm)/(double)nspin; //Energy
    glob_av[ix]  += stima_s;
    glob_av2[ix] += stima_s*stima_s;
    err_s=Error(glob_av[ix],glob_av2[ix],iblk);
    if (nsimulazione==0){
        Susc << iblk <<  '\t' << stima_s << '\t' << glob_av[ix]/(double)iblk << '\t' << err_s << endl;
    }
    else{
        Susc << iblk+nblk*(nsimulazione-1) <<  '\t' << stima_s << '\t' << glob_av[ix]/(double)iblk << '\t' << err_s << endl;
    }
    Susc.close();
    
    
    
    Magn.open("Risultati/output.magnetization_" + to_string(temp) + ".0",ios::app);
    stima_m = (blk_av[im]/blk_norm)/(double)nspin; //Energy
    glob_av[im]  += stima_m;
    glob_av2[im] += stima_m*stima_m;
    err_m=Error(glob_av[im],glob_av2[im],iblk);
    if (nsimulazione==0){
        Magn << iblk <<  '\t' << stima_m << '\t' << glob_av[im]/(double)iblk << '\t' << err_m << endl;
    }
    else{
        Magn << iblk+nblk*(nsimulazione-1) <<  '\t' << stima_m << '\t' << glob_av[im]/(double)iblk << '\t' << err_m << endl;
    }
    Magn.close();
    

    cout << "----------------------------" << endl << endl;
}


void ConfFinal(void)
{
  ofstream WriteConf;

  cout << "Print final configuration to file config.final " << endl << endl;
  WriteConf.open("config_" + to_string(temp) + ".final");
  for (int i=0; i<nspin; ++i)
  {
    WriteConf << s[i] << endl;
  }
  WriteConf.close();

  rnd.SaveSeed();
}



void WriteFinal(void)
{
    
    
    ofstream Ene, Cap, Magn, Susc;
    

    Ene.open("Risultati/output.ene_" + to_string(temp) + ".final",ios::app);

    Ene << temp <<  '\t' << stima_u << '\t' << glob_av[iu]/(double)nblk << '\t' << err_u << endl;
    Ene.close();


    Cap.open("Risultati/output.capacity_" + to_string(temp) + ".final",ios::app);

        Cap << temp <<  '\t' << stima_c << '\t' << glob_av[ic]/(double)nblk << '\t' << err_c << endl;

    Cap.close();


    
    Susc.open("Risultati/output.susceptibility_" + to_string(temp) + ".final",ios::app);

        Susc << temp <<  '\t' << stima_s << '\t' << glob_av[ix]/(double)nblk << '\t' << err_s << endl;
    Susc.close();
    
    
    
    Magn.open("Risultati/output.magnetization_" + to_string(temp) + ".final",ios::app);
        Magn << temp <<  '\t' << stima_m << '\t' << glob_av[im]/(double)nblk << '\t' << err_m << endl;
    Magn.close();
    



}


int Pbc(int i)  //Algorithm for periodic boundary conditions
{
    if(i >= nspin) i = i - nspin;
    else if(i < 0) i = i + nspin;
    return i;
}

double Error(double sum, double sum2, int iblk)
{
    if(iblk==1) return 0.0;
    else return sqrt((sum2/(double)iblk - pow(sum/(double)iblk,2))/(double)(iblk-1));
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
