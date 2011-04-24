//DHT11 Temperature & Humidity Sensor driver by George Hadjikyriacou
//Version 0.4 (24/11/2010)
//License: GPL v3 (http://www.gnu.org/licenses/gpl.html)

#include <dht11.h>

dht11 ther_ygr;

void setup(){
  Serial.begin(9600);
}
void loop(){

  ther_ygr.read_pulse(2);

  Serial.println("--------Start--------");
  Serial.print("Humidity (%):");
  Serial.print(ther_ygr.rh_1);
  Serial.print(".");
  Serial.println(ther_ygr.rh_2);
  Serial.print("Temperature (oC):");
  Serial.print(ther_ygr.t_1);
  Serial.print(".");
  Serial.println(ther_ygr.t_2);
  Serial.print("Temperature (oF):");
  Serial.println(ther_ygr.to_fahrenheit(ther_ygr.t_1));
  Serial.print("Temperature (K):");
  Serial.println(ther_ygr.to_kelvin(ther_ygr.t_1));
  Serial.print("Dew Point (oC):");
  Serial.println(ther_ygr.dew_point(ther_ygr.t_1, ther_ygr.rh_1));
  Serial.print("Checksum:");
  Serial.print(ther_ygr.checksum);
  Serial.print(" - ");
  Serial.println(ther_ygr.checksum_str);
  Serial.println("--------Stop--------");

  delay(5000);

}

