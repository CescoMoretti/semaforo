<<<<<<< HEAD
=======
///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//

/*	- fare un vettore con gli stati
	- vettore con i tempi
	Dentro un while infinito si chiama la funzione per calcolare il prossimo stato:
	1. prende in input lo stato attuale
	2. guarda lo stato attuale e lo posizione nel vettore
	3. restituisce il numero in millisecondi (ogni timer � diverso)
	4. con quelli richiami lo speep e cambi lo stato dopo
*/

>>>>>>> 57cf8def9997a115b44e43b6f3c3c0f4fda7d085
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

#include <iostream>

#ifndef NO_PI
#include <wiringPi.h>
#endif

using namespace std;

///
/// Configuration
///
//faccio il setup delle porte dei led, del vettore con i tempi e dello stato dei led se sono accesi o spenti
//rosso->verde->giallo
const int led_rosso = 0;
const int led_verde = 1;
const int led_giallo = 2;

const int timeMs[] = {5, 7, 3};
bool status[] = {false, false, false};
///
/// Utils
///

void init()
{
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_rosso, OUTPUT);
    pinMode(led_verde, OUTPUT);
    pinMode(led_giallo, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value){
#ifndef NO_PI
    digitalWrite(ledNumber, value);
#else
    cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
#endif
}

//funzione principale e fondamentale
int nextStatus(int currentIndex){
    //prendo il tempo che dovrò aspettare
    int specificMs = timeMs[currentIndex];
    //cambio lo stato del led, e lo accendo di conseguenza
    status[currentIndex]=!status[currentIndex];
    setLed(currentIndex,status[currentIndex]);

//aspetto il tempo indicato
#ifndef NO_PI
    usleep(specificMs *1000);
#else
    Sleep(specificMs);
    cout << "sto aspettando"<< specificMs*1000<< " millisecondi"<< endl;
#endif

    //spengo il led perchè non più utile
    status[currentIndex]=!status[currentIndex];
    setLed(currentIndex,status[currentIndex]);

    //aumento l'indice per andare al prossimo stato
    currentIndex++;
    if (currentIndex>2) {
        currentIndex = 0;
    }
    return currentIndex;
}

<<<<<<< HEAD
int main()
{
    //chiamo la funzione fondamentale all'interno di un loop infinito
    init();
    int index=0;
    while(1){
        index = nextStatus(index);
=======


//TODO funzione errore (lampeggio)
int main()
{
    init();   
    bool onoff = true;
    unsigned int count = 0;
    while(1)
    {       	
        cout << "Current value is " << count << endl;        
        setLed(led_Blue, onoff);
        onoff = !onoff;

        //Increment timer counter
        count++;
        //TODO togliere sleep
        
        /*#ifndef NO_PI
                usleep(timeoutMs *1000);
        #else
                Sleep(timeoutMs);
        #endif*/
        
>>>>>>> 57cf8def9997a115b44e43b6f3c3c0f4fda7d085
    } // main loop

    return 0;
}
