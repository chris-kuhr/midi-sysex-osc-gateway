/*
 * 		yamaha_specs.h
 *
 *  	Copyright 2013 Christoph Kuhr
 *
 *   	This file is part of MIDI_SYSEX_OSC_Gateway.
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
 *		support: info@klangplattform.de 
 *
 */


#ifndef YAMAHA_SPECS_H_
#define YAMAHA_SPECS_H_

#define MASTER_ADDRESS_DUPLICATE_PROBLEM 0
/*
 * Manufacturer
 */
#define MANU_YAMAHA 0x43

/*
 * Mixer ID
 */
#define Y01V96V2_SYSEX 0x003E7F01 // Yamaha 01v96 V2
#define YLS916_SYSEX 0x003E1201 // Yamaha LS9 16

/*
 * Parameter Msg Bytes
 */
#define SYSEX_START_BYTE 0xF0
#define SYSEX_END_BYTE 0xF7
#define PARAMETER_CHANGE 0x10
#define PARAMETER_REQUEST 0x30

/*
 * Functional Block
 */
#define YLS916_FB_INPUT 0x00330000
#define YLS916_FB_MIX1 0x00430005
#define YLS916_FB_MIX2 0x00430008
#define YLS916_FB_MIX3 0x0043000B
#define YLS916_FB_MIX4 0x0043000E
#define YLS916_FB_MIX5 0x00430011
#define YLS916_FB_MIX6 0x00430014
#define YLS916_FB_MIX7 0x00430017
#define YLS916_FB_MIX8 0x0043001A
#define YLS916_FB_MIX9 0x0043001D
#define YLS916_FB_MIX10 0x00430020
#define YLS916_FB_MIX11 0x00430023
#define YLS916_FB_MIX12 0x00430026
#define YLS916_FB_MIX13 0x00430029
#define YLS916_FB_MIX14 0x0043002C
#define YLS916_FB_MIX15 0x0043002F
#define YLS916_FB_MIX16 0x00430032
#define YLS916_FB_MASTER 0x004E0000

/*
 * 	Parameter Addresses
 */
#define YLS916_INPUT_1_INPUT 0x0000
#define YLS916_INPUT_2_INPUT 0x0001
#define YLS916_INPUT_3_INPUT 0x0002
#define YLS916_INPUT_4_INPUT 0x0003
#define YLS916_INPUT_5_INPUT 0x0004
#define YLS916_INPUT_6_INPUT 0x0005
#define YLS916_INPUT_7_INPUT 0x0006
#define YLS916_INPUT_8_INPUT 0x0007
#define YLS916_INPUT_9_INPUT 0x0008
#define YLS916_INPUT_10_INPUT 0x0009
#define YLS916_INPUT_11_INPUT 0x000A
#define YLS916_INPUT_12_INPUT 0x000B
#define YLS916_INPUT_13_INPUT 0x000C
#define YLS916_INPUT_14_INPUT 0x000D
#define YLS916_INPUT_15_INPUT 0x000E
#define YLS916_INPUT_16_INPUT 0x000F
#define YLS916_INPUT_17_INPUT 0x0010
#define YLS916_INPUT_18_INPUT 0x0011
#define YLS916_INPUT_19_INPUT 0x0012
#define YLS916_INPUT_20_INPUT 0x0013
#define YLS916_INPUT_21_INPUT 0x0014
#define YLS916_INPUT_22_INPUT 0x0015
#define YLS916_INPUT_23_INPUT 0x0016
#define YLS916_INPUT_24_INPUT 0x0017
#define YLS916_INPUT_25_INPUT 0x0018
#define YLS916_INPUT_26_INPUT 0x0019
#define YLS916_INPUT_27_INPUT 0x001A
#define YLS916_INPUT_28_INPUT 0x001B
#define YLS916_INPUT_29_INPUT 0x001C
#define YLS916_INPUT_30_INPUT 0x001D
#define YLS916_INPUT_31_INPUT 0x001E
#define YLS916_INPUT_32_INPUT 0x001F
#define YLS916_MASTER_STEREO 0x0000


/*
 * 	Parameter Addresses 01v96 V2
 */
#define Y01V96V2_FB_ON_BT 0x1A
#define Y01V96V2_FB_FADER 0x1C
#define Y01V96V2_FB_MASTER_ON_BT 0x4D
#define Y01V96V2_FB_MASTER_FADER 0x4F

#define Y01V96V2_INPUT_1 0x0000
#define Y01V96V2_INPUT_2 0x0001
#define Y01V96V2_INPUT_3 0x0002
#define Y01V96V2_INPUT_4 0x0003
#define Y01V96V2_INPUT_5 0x0004
#define Y01V96V2_INPUT_6 0x0005
#define Y01V96V2_INPUT_7 0x0006
#define Y01V96V2_INPUT_8 0x0007
#define Y01V96V2_INPUT_9 0x0008
#define Y01V96V2_INPUT_10 0x0009
#define Y01V96V2_INPUT_11 0x000A
#define Y01V96V2_INPUT_12 0x000B
#define Y01V96V2_INPUT_13 0x000C
#define Y01V96V2_INPUT_14 0x000D
#define Y01V96V2_INPUT_15 0x000E
#define Y01V96V2_INPUT_16 0x000F
#define Y01V96V2_RTN1 0x0021
#define Y01V96V2_RTN2 0x0023
#define Y01V96V2_MASTER_L 0x0000
#define Y01V96V2_MASTER_R 0x0001


#endif /* YAMAHA_SPECS_H_ */
