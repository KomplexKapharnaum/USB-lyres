//
// Note: to make release: cd release; pkg ../
//

const VERSION = "1.0.0"

// ARTNET
//
const UNIVERSE = 16

var artnet = require('artnet')({
    host: '2.255.255.255', // default: 255.255.255.255
    refresh: 1000, // default: 4000
    sendAll: true // default: send only new values
});

// MIDI
//
var easymidi = require('easymidi');
var input = new easymidi.Input('KArtNet-32', true);

input.on('cc', function(data) {
    // console.log(data)

    if (data.controller > 32) return;

    dmxChannel = data.controller + 32 * data.channel

    artnet.set(UNIVERSE, dmxChannel, data.value * 2, function(err, res) {
        console.log(err, res)
    });
});

console.log(".:: KArtNet-32 v" + VERSION + " ::.")
console.log("Forward midi CC 1->32 to ArtNet universe " + UNIVERSE)
console.log("DMX channel = CC n° + 32 * MIDI channel")
console.log("DMX value = MIDI value * 2")
console.log("ready :)")