//dht11.h
//DHT11 Temperature & Humidity Sensor library by George Hadjikyriacou
//Version 0.2 (24/11/2010)
//License: GPL v3 (http://www.gnu.org/licenses/gpl.html)

#ifndef dht11_h
#define dht11_h

#include "WProgram.h"

class dht11
{
public:
    float to_fahrenheit(int cel);
    float to_kelvin(int cel);
    double dew_point(int cel, int rh);
    void read_pulse(int pin);
    int create_binary(int a,int b,int c,int d,int e,int f,int g,int h);
    int rh_1,rh_2,t_1,t_2,checksum;
    String checksum_str;
};
#endif
