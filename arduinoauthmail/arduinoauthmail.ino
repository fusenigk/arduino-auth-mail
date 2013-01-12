/*
SEND AN EMAIL WITH ARDUINO

This code was created by modifying the connect example from arduino.cc and with the help of the YABB forums and their very helpful members.
This code sends an email to any email address and then disconnects.  It will also print on screen (in the serial monitor) the data the server sends the Arduino.  Make sure to replace all the *'s with your own information.
*/

#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; // Arduino's artificial mac address
byte ip[] = { 192, 168, 0, 177 }; // my ip
byte server[] = { 83, 133, 227, 116 }; // my smtp.***.net server ip
int time = 5000;
int wait = 2000;


EthernetClient client;

void setup()
{
 delay(time);
 
 Ethernet.begin(mac, ip);
 Serial.begin(9600);
 
 delay(1000);
 
 Serial.println("connecting...");
 
 if (client.connect(server, 25)) 
 {
                        Serial.println("connected");
   
                        client.println("HELO MAILADRESS); /* say hello (statement after helo is needed but irrelevant)*/
                          delay(wait); /* wait for a response */
                     
                        client.println("AUTH LOGIN");
                        delay(wait); /* wait for a response */
 
                        client.println("USERNAME_BASE64=");  // user name, *base64*
                        delay(wait); /* wait for a response */
                        
                        client.println("PASSWORD_BASE64=");  // user password, *base64*
                        delay(wait); /* wait for a response */

                        client.println("MAIL From: MAILADRESS"); /* identify sender, this should be the same as the smtp server you are using */
                          delay(wait); /* wait for a response */

                        client.println("RCPT To: MAILADRESS"); /* identify recipient */
                        delay(wait); /* wait for a response */

                        client.println("DATA"); 
                          delay(wait); /* wait for a response */
 
                        client.println("From: MAILADRESS"); /* identify recipient */
                        client.println("To: MAILADRESS"); /* identify recipient */
                        client.println("Subject: You Have Mail!!"); /* insert subject */
                        delay(wait); /* wait for a response */

                        client.println("Please let me know it worked!!!"); /* insert body */
                        client.println("."); /* end email */
                 
                        client.println("QUIT"); /* terminate connection */
                         delay(wait); /* wait for a response */

  
   client.println();
   
 } else {
   Serial.println("connection failed");
 }
}

void loop()
{
 while (client.available()) {
   char c = client.read();
   Serial.print(c);
 }
 
 if (!client.connected()) {
   Serial.println();
   Serial.println("disconnecting.");
   client.stop();
   for(;;)
     ;
 }
}

