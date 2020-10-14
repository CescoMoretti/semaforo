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

const int BlinkErrorMs = 1000;

//faccio il setup delle porte dei led, del vettore con i tempi e dello stato dei led se sono accesi o spenti
//rosso->verde->giallo
const int led_rosso = 0;
const int led_verde = 1;
const int led_giallo = 2;
//                    ros   ver    gia
const int timeMs[] = {5000, 5000, 3000};
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

void setLed(int ledNumber, bool value)
{
    #ifndef NO_PI
        digitalWrite(ledNumber, value);
    #else
        cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
    #endif
}
void wait(int TimeMs)
{
    #ifndef NO_PI
        usleep(TimeMs *1000);
    #else
        Sleep(TimeMs);
    #endif
}
///
/// Function
///
//funzione principale e fondamentale
int nextStatus(int currentIndex){
    //prendo il tempo che dovrò aspettare
    int specificMs = timeMs[currentIndex];
    //cambio lo stato del led, e lo accendo di conseguenza
    status[currentIndex]=!status[currentIndex];
    setLed(currentIndex,status[currentIndex]);

    //aspetto il tempo indicato
    wait(specificMs);
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

void Error()
{
    bool onoff = true;
    while(1)
    {   
        //set led   	
        setLed(led_giallo, onoff);
        //wait
        wait(BlinkErrorMs);
        onoff = !onoff;  
    } // error loop  
}
///
///Main cycle
///
int main()
{
    init();
    int index=0;    
    unsigned int count = 0;
    while(1)
    {
        index = nextStatus(index);
        //Increment timer counter
        count++;
        //start error after 2 full cycle
        if(count > 6)
        {
            Error();
        }
    } // main loop   
}

