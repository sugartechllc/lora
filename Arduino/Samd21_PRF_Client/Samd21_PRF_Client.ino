/*
  Both the TX and RX ProRF boards will need a wire antenna. We recommend a 3" piece of wire.
  This example is a modified version of the example provided by the Radio Head
  Library which can be found here:
  www.github.com/PaulStoffregen/RadioHeadd
*/

#include <SPI.h>

//Radio Head Library:
#include <RH_RF95.h> 

// We need to provide the RFM95 module's chip select and interrupt pins to the
// rf95 instance below.On the SparkFun ProRF those pins are 12 and 6 respectively.
RH_RF95 rf95(12, 6);

int LED = 13; //Status LED is on pin 13

int packetCounter = 0; //Counts the number of packets sent
long timeSinceLastPacket = 0; //Tracks the time stamp of last packet received

// The broadcast frequency is set to 921.2, but the SADM21 ProRf operates
// anywhere in the range of 902-928MHz in the Americas.
// Europe operates in the frequencies 863-870, center frequency at 868MHz.
// This works but it is unknown how well the radio configures to this frequency:
//float frequency = 864.1; 
float frequency = 921.2; //Broadcast frequency

void fail() {
     while (1) {
          digitalWrite(LED, HIGH);
          delay(100);
          digitalWrite(LED, LOW);
          delay(100);
     } 
}

void setup()
{
  pinMode(LED, OUTPUT);

  SerialUSB.begin(9600); 
  SerialUSB.println("RFM Client!"); 

  //Initialize the Radio.
  if (rf95.init() == false){
    SerialUSB.println("Radio Init Failed - Freezing");
    fail();
  }
  else{
    //An LED inidicator to let us know radio initialization has completed. 
    SerialUSB.println("Transmitter up!"); 
    digitalWrite(LED, HIGH);
    delay(500);
    digitalWrite(LED, LOW);
    delay(500);
  }

  // Set frequency
  rf95.setFrequency(frequency);

   // The default transmitter power is 13dBm, using PA_BOOST.
   // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then 
   // you can set transmitter powers from 5 to 23 dBm:
   // Transmitter power can range from 14-20dbm.
   rf95.setTxPower(14, false);
}


void loop()
{
  SerialUSB.println("RFM Client: Sending message");

  //Send a message to the other radio
  uint8_t toSend[] = "Hi there!";
  //sprintf(toSend, "Hi, my counter is: %d", packetCounter++);
  rf95.send(toSend, sizeof(toSend));
  rf95.waitPacketSent();

  // Now wait for a reply
  byte buf[RH_RF95_MAX_MESSAGE_LEN];
  byte len = sizeof(buf);

  digitalWrite(LED, HIGH);
  if (rf95.waitAvailableTimeout(2000)) {
    // Should be a reply message for us now
    if (rf95.recv(buf, &len)) {
      SerialUSB.print("RFM Client: Got reply: ");
      SerialUSB.print((char*)buf);
      SerialUSB.print(" RSSI: ");
      SerialUSB.println(rf95.lastRssi(), DEC);
    }
    else {
      SerialUSB.println("RFM Client: Receive failed");
    }
  }
  else {
    SerialUSB.println("RFM Client: No reply, is the receiver running?");
  }
  digitalWrite(LED, LOW);
  delay(500);
}
