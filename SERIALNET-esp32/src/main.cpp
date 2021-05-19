#include <Arduino.h>
#include <MIDI.h>

#define K32_SET_NODEID 150 // board unique id
#define LULU_UNI 1         // univers artnet

#include <K32.h>
K32* k32;

#include <hardware/K32_pwm.h>
K32_pwm* pwm;

#include <light/K32_light.h>
K32_light* light;

#include <network/K32_wifi.h>
K32_wifi* wifi;

#include <network/K32_osc.h>
K32_osc* osc;

#include <network/K32_mqtt.h>
K32_mqtt* mqtt;

MIDI_CREATE_INSTANCE(HardwareSerial, Serial1, midiA);



void setup() 
{
  k32 = new K32();

  // pwm = new K32_pwm(k32);

  // light = new K32_light(k32);
  // light->addStrip(14, LED_SK6812_V1, 100);
  // light->anim( 0, "test0",   new K32_anim_test )->push(300)->master(100)->play();

  wifi = new K32_wifi(k32, k32->system->name());
  wifi->connect("interweb", "superspeed37"); //KXKM
  // wifi->connect("kxkm-wifi", "KOMPLEXKAPHARNAUM"); //KXKM

  // osc = new K32_osc(k32, wifi, {
  //       .port_in = 1818,       // osc port input (0 = disable)  // 1818
  //       .port_out = 1819,      // osc port output (0 = disable) // 1819
  //       .beatInterval = 0,     // heartbeat interval milliseconds (0 = disable)
  //       .beaconInterval = 3000 // full beacon interval milliseconds (0 = disable)
  // });

  mqtt = new K32_mqtt(k32, wifi);

  mqtt->subscribe({.topic = "k32/monitor/beat",
                        .qos = 0,
                        .callback = [](char *payload, size_t length) {
                          LOG("beat received");
                        }});

  mqtt->start({
        .broker = "192.168.1.169",// Komplex
        .beatInterval = 2000,  // heartbeat interval milliseconds (0 = disable)
        .beaconInterval = 000 // full beacon interval milliseconds (0 = disable)
  });

  k32->intercom->ee.addListener("monitor", [](Orderz* order) { 
      LOGINL(order->engine); 
      LOG(order->action); 
  });

  k32->intercom->ee.addListener("cool", [](Orderz* order) { 
      LOG("cool received"); 
  });

  midiA.begin(MIDI_CHANNEL_OMNI);
}

void loop() 
{
  if (midiA.read())
  {
    Serial.printf("%d %d %d %d\n", 
                  midiA.getType(),
                  midiA.getData1(),
                  midiA.getData2(),
                  midiA.getChannel());
  }

  delay(2000);
  // k32->intercom->ee.emit("cool", nullptr);
  // k32->intercom->queue( "super/genial" );
}