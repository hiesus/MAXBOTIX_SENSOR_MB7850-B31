/***TESTING SOFTWARE MAXBOTIX SENSOR MB7850-B31.
This code was successfully tested on Arduino nano atmega328P
***/

#include <SoftwareSerial.h>

/*  ELECTRIC WIRE CONNECTIONS: 
 *  MAXBOTIC MB7850    ----->     ARDUINO NANO PIN
 *  PIN 1 (WHITE)      ----->     D11 (mySerial TX)    
 *  PIN 2 (ORANGE)     ----->     GND     
 *  PIN 3 (BROWN)      ----->     FLOATING (Not connecterd)  
 *  PIN 4 (GREEN)      ----->     D8 (Output HIGH/LOW)  
 *  PIN 5 (BLUE)       ----->     D12 (mySerial RX) 
 *  PIN 6 (RED)        ----->     +5V (make sure that supply voltage and TTL levels are the same! you will need a voltage shifter between pins 11 and 12 and Maxbotix white/blue wires if you would like to user 3.3V power supply)  
 *  PIN 7 (BLACK)      ----->     GND      
 */
 
/*  SoftwareSerial (PIN RX, PIN TX, conversion type) conversion type: true = RS232 ; false = TTL */
SoftwareSerial mySerial(12,11, true);
const int trigger = 8; //Maxbotix trigger range reading wire pin

String data; //Allocate user serial incomming strings
bool w=false; //Write command to Maxbotix sensor
char comm[]= {'T','t','R','r','M','m','A','a','D','d'}; //Maxbotix available command list
int n = sizeof(comm) / sizeof(char) - 1; //Number of comm elements - 1
bool MB7851=false;

void setup() 
{
    pinMode(trigger, OUTPUT);      //Set arduino nano pin to trigger maxbotix sensor reading
    digitalWrite(trigger, LOW);    //Set arduino nano pin low
    Serial.begin(115200);          //Initialize serial communication with arduino nano
    mySerial.begin(9600);          //initialize serial communication with Maxbotix sensor
    Serial.println("Test begins, please select a command!");
    Serial.println("“T” or ”t” Save New Calibration");
    Serial.println("“R” or ”r” Restore Factory Calibration");
    Serial.println("“M” or ”m” Set Max Range, This command will expect to receive three ASCII number characters to set the max range.");
    Serial.println("“A” Analog Envelope ON");
    Serial.println("“a” Analog Envelope OFF");
    Serial.println("“D” Advanced Range ON");
    Serial.println("“d” Advanced Range OFF");
    Serial.println("When a, d commands are used, it may be necessary to de-energize your Maxbotix sensor to fully apply changes!");
}

void loop() 
{   
    if (Serial.available()) {
    data = Serial.readString();
    for (int i=0;i<n;i++){  //This for loop search first incomming string char and compare to Maxbotix commands list
      if (char(data[0])==comm[i]) {
      w=true;               //if the 1st char of the incomming user string is equal to any command w var is set to true
      Serial.println(String(data)+" command received");  //ack the command received to the user
      }
     }
    digitalWrite(trigger, HIGH); //any other char different from Maxbotix commands will trigger a sensor reading
    delayMicroseconds (20);  //delay time acordingly to XL-TankSensor- WRMA™ Series High Performance, IP67 Weather Resistant, Ultrasonic Range Finder MB78503 doc
    digitalWrite(trigger, LOW);
    }
    if (mySerial.available() > 0) { 
      // Read and process the data
      String c = mySerial.readStringUntil(13);
           if (w==true)              {mySerial.write(data[0]); w=false;}   //write a command to Maxbotix sensor when w is true
      else if (c=="Send 1000s Digit") {mySerial.write(data[1]); MB7851=true;}
      else if (c=="Send 100s Digit")  {int m; if (MB7851==true) m=2; else m=1; mySerial.write(data[m]);             }
      else if (c=="Send 10s Digit")   {int m; if (MB7851==true) m=3; else m=2; mySerial.write(data[m]);             }
      else if (c=="Send 1s Digit")    {int m; if (MB7851==true) m=4; else m=3; mySerial.write(data[m]);MB7851=false;}
      Serial.println(c); //print to user any string incomming from Maxbotix sensor
    }
}
