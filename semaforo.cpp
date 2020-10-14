///
/// NOTE On Desktop systems, compile with -D NO_PI flag
//

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
const int led_Blue = 0;
const int led_Yellow = 1;
//TODO aggiungere altri led
const int BlinkErrorMs = 1000;
const int timeoutMs = 1000; // 1 second
//TODO vettore stati aggiungere

///
/// Utils
///
void init()
{
#ifndef NO_PI
    wiringPiSetup();
    pinMode(led_Blue, OUTPUT);
#endif
}

void setLed(int ledNumber, bool value) //TODO implementare sleep
{
    #ifndef NO_PI
        digitalWrite(ledNumber, value);
    #else
        cout << "Setting led " << ledNumber << " to " << (value ? "ON" : "OFF") << endl;
    #endif
// int attesaMs[3]={5,10,5};
/* #ifndef NO_PI
        usleep(attesaMs[lednumebr] *1000);
    #else
        Sleep(attesaMs[lednumebr]);
    #endif
 */
}
void Error()
{
    bool onoff = true;
    while(1)
    {    
        //set led   	
        #ifndef NO_PI
            digitalWrite(led_Yellow, onoff);
        #else
            cout << "Setting led " << led_Yellow << " to " << (onoff ? "ON" : "OFF") << endl;
        #endif
        //wait
        #ifndef NO_PI
                usleep(BlinkErrorMs *1000);
        #else
                Sleep(BlinkErrorMs);
        #endif
        onoff = !onoff;  
    } // error loop  
}
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
        //start error after 4 full cycle
        if(count == 12)
        {
            Error();
        }

    } // main loop   
    return 0;
}
