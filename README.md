midi-sysex-osc-gateway
======================

Remote Control for Yamaha Digital Mixers


Dependencies:

Lighweight OSC (liblo)  # compile with '-llo'

ALSA (libasound)	# compile with '-lasound'

##### H5 Quick and dirty build instructions for Ubuntu:
1. Verify you have "universe" in your sources.list. If not add it

Dirty way

```$ grep universe /etc/apt/sources.list|grep -v "^#"

deb http://ar.archive.ubuntu.com/ubuntu/ xenial universe
deb http://ar.archive.ubuntu.com/ubuntu/ xenial-updates universe
deb http://ar.archive.ubuntu.com/ubuntu/ xenial-backports main restricted universe multiverse
deb http://security.ubuntu.com/ubuntu xenial-security universe
```

If Univese not present, add it:
`$ sudo add-apt-repository "deb http://archive.ubuntu.com/ubuntu $(lsb_release -sc) universe"`

2. add necesary libs:
` $ apt -y install build-essential libasound2-dev liblo-dev `

3. Clone repo:
`$ git clone --depth 1 https://github.com/chris-kuhr/midi-sysex-osc-gateway`

4. Build:
`$ cd midi-sysex-osc-gateway
$ g++ Main.cpp -o midi_sysex_osc_gateway -llo -lpthread -lasound`

5. Now go on.

Start Application:

./midi_sysex_osc_gateway -i192.168.0.10 -r9000 -s9001 -v 	#RPi LS9

./midi_sysex_osc_gateway -i192.168.0.11 -r9001 -s9000 -v	#RPi 01V96V2
