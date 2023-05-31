MAXBOTIX_SENSOR_MB7850-B31
TESTING SOFTWARE MAXBOTIX SENSOR MB7850-B31
This version has not been verified when users send commands M or m, updates may be needed.
This code was successfully tested on Arduino nano atmega328P

/*  ELECTRIC WIRE CONNECTIONS: 
 *  MAXBOTIC MB7850    ----->     ARDUINO NANO PIN
 *  PIN 1 (WHITE)      ----->     D11 (mySerial TX)    
 *  PIN 2 (ORANGE)     ----->     GND     
 *  PIN 3 (BROWN)      ----->     FLOATING (Not connecterd)  
 *  PIN 4 (GREEN)      ----->     D8 (Output HIGH/LOW)  
 *  PIN 5 (BLUE)       ----->     D12 (mySerial RX) 
 *  PIN 6 (RED)        ----->     +5V (make sure that supply voltage and TTL levels are the same! you will need a voltage shifter between pins 11 and 12 and Maxbotix white/blue wires if you would like to user 3.3V power supply)  
 *  PIN 7 (BLACK)      ----->     GND      
