
#define LED 13
#define BAUDRATE 57600
#define DEBUGOUTPUT 0

//Shifter part //

#include <Shifter.h>

#define SER_Pin 4 //SER_IN
#define RCLK_Pin 3 //L_CLOCK
#define SRCLK_Pin 2 //CLOCK

#define NUM_REGISTERS 26 //how many registers are in the chain

//initaize shifter using the Shifter library
Shifter shifter(SER_Pin, RCLK_Pin, SRCLK_Pin, NUM_REGISTERS); 

#define powercontrol 10

// checksum variables
byte generatedChecksum = 0;
byte checksum = 0; 
int payloadLength = 0;
byte payloadData[64] = {0};
byte poorQuality = 0;
byte attention = 0;
byte meditation = 0;

// system variables
long lastReceivedPacket = 0;
boolean bigPacket = false;

//////////////////////////
// Microprocessor Setup //
//////////////////////////
void setup() 

{
  pinMode(LED, OUTPUT);
  Serial.begin(BAUDRATE);           // USB
}

////////////////////////////////
// Read data from Serial UART //
////////////////////////////////
byte ReadOneByte() 

{
  int ByteRead;
  while(!Serial.available());
  ByteRead = Serial.read();

#if DEBUGOUTPUT  
  Serial.print((char)ByteRead);   // echo the same byte out the USB serial (for debug purposes)
#endif

  return ByteRead;
}

/////////////
//MAIN LOOP//
/////////////
void loop() 

{
  // Look for sync bytes
  if(ReadOneByte() == 170) 
  {
    if(ReadOneByte() == 170) 
    {
        payloadLength = ReadOneByte();
      
        if(payloadLength > 169)                      //Payload length can not be greater than 169
        return;
        generatedChecksum = 0;        
        for(int i = 0; i < payloadLength; i++) 
        {  
        payloadData[i] = ReadOneByte();            //Read payload into memory
        generatedChecksum += payloadData[i];
        }   

        checksum = ReadOneByte();                      //Read checksum byte from stream      
        generatedChecksum = 255 - generatedChecksum;   //Take one's compliment of generated checksum

        if(checksum == generatedChecksum) 
        {    
          poorQuality = 200;
          attention = 0;
          meditation = 0;

          for(int i = 0; i < payloadLength; i++) 
          {                                          // Parse the payload
          switch (payloadData[i]) 
          {
          case 2:
            i++;            
            poorQuality = payloadData[i];
            bigPacket = true;            
            break;
          case 4:
            i++;
            attention = payloadData[i];                        
            break;
          case 5:
            i++;
            meditation = payloadData[i];
            break;
          case 0x80:
            i = i + 3;
            break;
          case 0x83:
            i = i + 25;      
            break;
          default:
            break;
          } // switch
        } // for loop

#if !DEBUGOUTPUT

        // *** Add your code here ***

        if(bigPacket) 
        {
          if(poorQuality == 0)
             digitalWrite(LED, HIGH);
          else
            digitalWrite(LED, LOW);
          
          Serial.print("PoorQuality: ");
          Serial.print(poorQuality, DEC);
          Serial.print(" Attention: ");
          Serial.print(attention, DEC);
          Serial.print(" Meditation: ");
          Serial.print(meditation, DEC);
          Serial.print('\n');
          
          //Serial.print(" Time since last packet: ");
          //Serial.print(millis() - lastReceivedPacket, DEC);
          //lastReceivedPacket = millis();
          //Serial.print("\n");
         // shifter.clear();
          switch(attention / 10) 
          {
          case 0:
            shifter.clear(); 
            shifter.write();
            break;
          case 1:
            for(int i = 1 ; i<6 ; i++ ){
            shifter.setPin(i, HIGH);
            for(int i = 6 ; i<199 ; i++) {
            shifter.setPin(i , LOW);
            }
            shifter.write();
            }
            break;
          case 2:
            for(int i = 1 ; i< 22 ; i++ ){
            shifter.setPin(i, HIGH);
            }
            for(int i = 22 ; i<199 ; i++) {
            shifter.setPin(i , LOW);
            }
            
            shifter.write();
            break;
          case 4:              
            for(int i = 1 ; i < 31 ; i++ ){
            shifter.setPin(i, HIGH);
            }     
            for(int i = 31 ; i<199 ; i++) {
            shifter.setPin(i , LOW);
            } 
            shifter.write();
            break;
          case 6:
            for(int i = 1 ; i < 40 ; i++ ){
            shifter.setPin(i, HIGH);      
            }
            for(int i = 40 ; i<199 ; i++) {
            shifter.setPin(i , LOW);
            }     
            shifter.write();
            break;
          case 7:
            for(int i = 1 ; i < 58 ; i++ ){
            shifter.setPin(i, HIGH);      
            }
            for(int i = 58 ; i<199 ; i++) {
            shifter.setPin(i , LOW);
            }        
            shifter.write();
            break;
          case 8:              
            for(int i = 1 ; i < 142 ; i++ ){
            shifter.setPin(i, HIGH);            
            }
            for(int i = 142 ; i<199 ; i++) {
            shifter.setPin(i , LOW);
            }                
            shifter.write();
            break;
          case 9:
            for(int i = 1 ; i < 199 ; i++ ){
            shifter.setPin(i, HIGH);
            }
            shifter.write(); 
            break;   
             
          
          }                   
        }
#endif        
        bigPacket = false;        
      }
      else {
        // Checksum Error
      }  // end if else for checksum
    } // end if read 0xAA byte
  } // end if read 0xAA byte
}
