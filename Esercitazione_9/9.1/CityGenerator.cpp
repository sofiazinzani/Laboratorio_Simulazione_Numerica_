#include <iostream>
#include <fstream>
#include <cmath>

#include "random.h"
#include "main.h"

using namespace std;

int main(){
ofstream Position ("CityPosition.dat");
    
Random rnd=initialization();

	if(Circonferenza==true) {
		double x;
		for (int i=0; i<nCity; i++){
			x=rnd.Rannyu(0, 2.*M_PI);   // estraggo x tra 0 e 2Pi
			Position << i << " " ;         // salvo il numero di città
			Position << sin(x) << " ";      // salvo il seno e il coseno dell'angolo casuale estratto, quindi suppondendo il raggio pari a 1, ho salvato la posizione
			Position << cos(x) << "\n";
		}
	}
    else {
		for (int i=0; i<nCity; i++){
			Position << i << " ";
			Position << rnd.Rannyu() << " ";        // estraggo le x e le y casualmente in un quadrato di dimensione (0,1)*(0,1)
			Position << rnd.Rannyu() << "\n";
		}
	}
Position.close();

return 0;
}
