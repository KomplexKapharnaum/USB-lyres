#include <Arduino.h>
#include <SPI.h>
#include <Ethernet.h>
#include <MIDI.h>
#include <USB-MIDI.h>

#include <Artnet.h>
ArtnetSender artnet;


// Ethernet
//
const IPAddress ip(2, 0, 17, 1);
const IPAddress gateway(2, 0, 0, 1);
const IPAddress subnet(255, 0, 0, 0);
const String broadcast = "2.255.255.255";
uint8_t mac[] = {0x17, 0x00, 0x00, 0x00, 0x00, 0x0A};

// ArtNet
uint32_t universe = 17;
const uint16_t size = 512;
uint8_t data[size] = {0};

// Vars
bool run = false;


// USBMIDI_CREATE_DEFAULT_INSTANCE();


void onStart() {
  run = true;
}

void onStop() {
  run = false;
}

void onCC(byte channel, byte number, byte value) 
{
  if (number < 32) data[ channel*32 + number ] = value*2;
}

// -----------------------------------------------------------------------------

void setup()
{
  // MIDI.begin(MIDI_CHANNEL_OMNI);
  // MIDI.setHandleStart(onStart);
  // MIDI.setHandleControlChange(onCC);
  // MIDI.setHandleStop(onStop);

  Ethernet.begin(mac, ip, gateway, gateway, subnet);
  artnet.begin();
}


void loop()
{ 
  //MIDI.read();

  artnet.streaming_data(data, size);
  if (run) artnet.streaming(broadcast, universe);
}
