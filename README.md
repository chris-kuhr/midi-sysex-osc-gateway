midi-sysex-osc-gateway
======================

Remote Control for Yamaha Digital Mixers

/*
 *  	Copyright 2013 Christoph Kuhr
 *
 *   	MIDI_SYSEX_OSC_Gateway is free software: you can redistribute it and/or modify
 *   	it under the terms of the GNU General Public License as published by
 *   	the Free Software Foundation, either version 3 of the License, or
 *   	(at your option) any later version.
 *
 *   	MIDI_SYSEX_OSC_Gateway is distributed in the hope that it will be useful,
 *   	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   	GNU General Public License for more details.
 *
 *   	You should have received a copy of the GNU General Public License
 *   	along with MIDI_SYSEX_OSC_Gateway.  If not, see <http://www.gnu.org/licenses/>.
 *
 *	support: info@klangplattform.de 
 *
 */



Dependencies:
Lighweight OSC (liblo)  # compile with '-llo'
ALSA (libasound)	# compile with '-lasound'


Start Application:

./midi_sysex_osc_gateway -i192.168.0.10 -r9000 -s9001 -v 	#RPi LS9
./midi_sysex_osc_gateway -i192.168.0.11 -r9001 -s9000 -v	#RPi 01V96V2
