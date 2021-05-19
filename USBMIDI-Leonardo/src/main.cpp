#include <Arduino.h>
#include <MIDI.h>
#include <USB-MIDI.h>

USBMIDI_CREATE_DEFAULT_INSTANCE();
MIDI_CREATE_INSTANCE(HardwareSerial, Serial1,    midiB);


// -----------------------------------------------------------------------------

void setup()
{
  MIDI.begin(MIDI_CHANNEL_OMNI);
  midiB.begin(MIDI_CHANNEL_OMNI);
}


void loop()
{ 
  if (MIDI.read())
  {
      // Thru on A has already pushed the input message to out A.
      // Forward the message to out B as well.
      midiB.send(MIDI.getType(),
                  MIDI.getData1(),
                  MIDI.getData2(),
                  MIDI.getChannel());
  }
  if (midiB.read())
  {
      // Thru on B has already pushed the input message to out B.
      // Forward the message to out A as well.
      MIDI.send(midiB.getType(),
                  midiB.getData1(),
                  midiB.getData2(),
                  midiB.getChannel());
  }
}
