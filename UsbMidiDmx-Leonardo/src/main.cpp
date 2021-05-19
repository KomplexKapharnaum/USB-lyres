#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MIDI.h>
#include <USB-MIDI.h>

// DMX
//
#include <LeoDMX.class.h>
LeoDMX DMX;

// Ethernet
//
const IPAddress ip(2, 0, 17, 1);
const IPAddress gateway(2, 0, 0, 1);
const IPAddress subnet(255, 0, 0, 0);
const String broadcast = "2.255.255.255";
uint8_t mac[] = {0x17, 0x00, 0x00, 0x00, 0x00, 0x0A};


// ArtNet
#include <Artnet.h>
ArtnetSender artnet;

uint32_t universe = 17;
uint8_t data[512] = {0};


// Midi
//
USBMIDI_CREATE_DEFAULT_INSTANCE();

// void onCC(byte channel, byte number, byte value) 
// {
//   if (number <= 32) {
//     int dmxAddr = (channel-1) * 32 + (number-1);
//     data[ dmxAddr ] = value*2;
//   }
// }

// void onNoteOn(byte channel, byte note, byte velocity)
// {
//   TXLED1;
//   MIDI.sendNoteOn(note, velocity, channel);
// }

// void onNoteOff(byte channel, byte note, byte velocity)
// {
//   TXLED0;
//   MIDI.sendNoteOff(note, velocity, channel);
// } 


// -----------------------------------------------------------------------------

void setup()
{
  DMX.null();
  
  MIDI.begin(MIDI_CHANNEL_OMNI);
  // MIDI.setHandleControlChange(onCC);
  // MIDI.setHandleNoteOn(onNoteOn);
  // MIDI.setHandleNoteOff(onNoteOff);

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  artnet.begin();
}


void loop()
{ 
  MIDI.read();

  artnet.streaming_data(data, 512);
  //artnet.streaming(broadcast, universe);
  
  // DMX.send( (unsigned char*) data, 512);

}
