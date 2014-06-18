midi-sysex-osc-gateway
======================

Remote Control for Yamaha Digital Mixers


Dependencies:

Lighweight OSC (liblo)  # compile with '-llo'

ALSA (libasound)	# compile with '-lasound'




Start Application:

./midi_sysex_osc_gateway -i192.168.0.10 -r9000 -s9001 -v 	#RPi LS9

./midi_sysex_osc_gateway -i192.168.0.11 -r9001 -s9000 -v	#RPi 01V96V2
