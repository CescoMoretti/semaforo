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
    delay(specificMs *1000);
#else
    Sleep(specificMs);
    cout << "sto aspettando "<< specificMs*1000<< " millisecondi"<< endl;
#endif

    //spengo i led giusti in base al tipo di semaforo
    switch (currentIndex) {
        case 0:{
            status[currentIndex]=!status[currentIndex];
            setLed(currentIndex,status[currentIndex]);
        }break;
        case 2:{
            status[currentIndex-1]=!status[currentIndex-1];
            setLed(currentIndex-1,status[currentIndex-1]);
            status[currentIndex]=!status[currentIndex];
            setLed(currentIndex,status[currentIndex]);
        }break;

    }


    //aumento l'indice per andare al prossimo stato
    currentIndex++;
    if (currentIndex>2) {
        currentIndex = 0;
    }
    return currentIndex;
}

int main()
{
    //chiamo la funzione fondamentale all'interno di un loop infinito
    init();
    int index=0;
    while(1){
        index = nextStatus(index);
    } // main loop

    return 0;
}
