//dht11.cpp
//DHT11 Temperature & Humidity Sensor library by George Hadjikyriacou
//Version 0.2 (24/11/2010)
//License: GPL v3 (http://www.gnu.org/licenses/gpl.html)

#include "WProgram.h"
#include "dht11.h"
#include "math.h"

//Celsius to Fahrenheit conversion
float dht11::to_fahrenheit(int cel) {
    float f = 1.8 * cel + 32;
    return f;
}

//Celsius to Kelvin conversion
float dht11::to_kelvin(int cel) {
    float k = cel + 273.15;
    return k;
}

double dht11::dew_point(int cel, int rh) {
    double TEMP=cel; // Temperature
    double HUM=rh; // Humidity
    double KELV= 273.15+TEMP;
    double A0= 373.16/KELV;
    double A1= -7.90298*(A0-1);
    double A2= 5.02808*log10(A0);
    double A3= -1.3816e-7*(pow(10,(11.344*(1-1/A0)))-1) ;
    double A4= 8.1328e-3*(pow(10,(-3.49149*(A0-1)))-1) ;
    double A5= log10(1013.246);
    double PRESSURE= pow(10,(A1+A2+A3+A4+A5));
    double SVP= PRESSURE*0.10;
    double VP= HUM/100.0*SVP;
    double DEWT= (241.88*log(VP/0.61078)) / (17.558-log(VP/0.61078));
    return DEWT;
}

void dht11::read_pulse(int pin)
{
    int highs[41];
    pinMode(pin, OUTPUT);
    digitalWrite(pin, LOW);
    delay(18);
    digitalWrite(pin, HIGH);
    delayMicroseconds(40);
    pinMode(pin, INPUT);
    for (int i=0; i<41; i++) {
        highs[i] = pulseIn(pin, HIGH);
    }
    rh_1 = create_binary(highs[1],highs[2],highs[3],highs[4],highs[5],highs[6],highs[7],highs[8]);
    rh_2 = create_binary(highs[9],highs[10],highs[11],highs[12],highs[13],highs[14],highs[15],highs[16]);
    t_1 = create_binary(highs[17],highs[18],highs[19],highs[20],highs[21],highs[22],highs[23],highs[24]);
    t_2 = create_binary(highs[25],highs[26],highs[27],highs[28],highs[29],highs[30],highs[31],highs[32]);
    checksum = create_binary(highs[33],highs[34],highs[35],highs[36],highs[37],highs[38],highs[39],highs[40]);

    if (checksum == rh_1 + t_1) {
        checksum_str = "OK";

    }
    else {
        checksum_str = "FAIL";
    }
}

int dht11::create_binary(int a,int b,int c,int d,int e,int f,int g,int h)
{
    int place[]={128,64,32,16,8,4,2,1};
    int pulsedata[8];
    pulsedata[0] = a;
    pulsedata[1] = b;
    pulsedata[2] = c;
    pulsedata[3] = d;
    pulsedata[4] = e;
    pulsedata[5] = f;
    pulsedata[6] = g;
    pulsedata[7] = h;

    //Convert timings to binary
    for (int i=0; i<8; i++) {
        if (pulsedata[i] > 50) {
            pulsedata[i] = 1;
        }
        else {
            if (pulsedata[i] < 50) {
                pulsedata[i] = 0;
            }
        }
    }

    //Convert binary to decimal
    int decimal = (place[0]*pulsedata[0])+ (place[1]*pulsedata[1])+ (place[2]*pulsedata[2])+ (place[3]*pulsedata[3])+ (place[4]*pulsedata[4])+ (place[5]*pulsedata[5])+ (place[6]*pulsedata[6])+ (place[7]*pulsedata[7]);
    return decimal;
}
