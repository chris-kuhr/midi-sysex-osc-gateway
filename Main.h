/*
 * 		Main.h
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


#ifndef MAIN_H_
#define MAIN_H_
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdarg.h>
#include <argp.h>
#include <string.h>
#include <ctype.h>
#include <getopt.h>
#include <errno.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/poll.h>
#include <sys/stat.h>
#include <pthread.h>
#include <iostream>
#include <cstring>
#include <alsa/asoundlib.h>
#include <lo/lo.h>

using namespace std;


#include "yamaha_specs.h"

#define FALSE                         0
#define TRUE                          1
#define MAX_DEV_STR_LEN               32
#define MAX_MSG_SIZE                1024
#define OUTPUT_BUFFER_SIZE 1024

/* change this definition for the correct port */
//#define _POSIX_SOURCE 1 /* POSIX compliant source */


static char *port_name = "hw:1,0,0";
int stop;
int run;
static snd_rawmidi_t *input, **inputp;
static snd_rawmidi_t *output, **outputp;
static lo_address transmit_socket;
static int timeout;
static u_int last_request=0xffffffff;

/*
 *
 * MIDI / OSC Processing
 *
 */
int process_incoming_osc(const char *path, const char *types, lo_arg ** argv,
                    int argc, void *data, void *user_data);
void* process_incoming_midi(void* argv);

/*
 *
 * Output
 *
 */
static void print_byte(unsigned char byte);
void printTime();

/*
 *
 * 					Arguments
 *
 *
 */
typedef struct _arguments
{
	int verbose;
    int tcp;
    char mixer[MAX_DEV_STR_LEN];
	char ip[MAX_DEV_STR_LEN];
	char name[MAX_DEV_STR_LEN];
	char sport[MAX_DEV_STR_LEN];
	char rport[MAX_DEV_STR_LEN];
	char hw[MAX_DEV_STR_LEN];
} arguments_t;

char doc[]       = "Send Custom MIDI SysEx Messages via OSC";

struct argp_option options[] =
{
	{"mixer" , 'm', "MIXER_TYPE" , 0, "Type of the Connected Mixer" },
	{"ip" , 'i', "IP" , 0, "IP address (or URL, for example foo.dyndns.org) where OSC messages are sent. Default = 127.0.0.1" },
	{"sport"     , 's', "SEND_PORT", 0, "Port where OSC messages are sent. Default = 7000" },
	{"rport"     , 'r', "RECEIVING_PORT", 0, "Port for incoming OSC traffic. Default is port defined with -p" },
	{"hw" , 'h', "MIDI_HW" , 0, "Midi Hardware. default hw:1,0" },
	{"name" , 'n', "NAME" , 0, "Name of Alsa MIDI client created. Default = oscmidi" },
	{"verbose"      , 'v', 0     , 0, "For debugging: Produce verbose output" },
    {"tcp"      , 't', 0     , 0, "Will use TCP instead of UDP" },
	{ 0 }
};

/*
 * Option Parsing
 */
static error_t parse_opt (int key, char *arg, struct argp_state *state);
static void arg_set_defaults(arguments_t *arguments);


const char *argp_program_version     = "midi-sysex-osc-gw 0.1";
const char *argp_program_bug_address = "christoph@klangplattform.de";

struct argp argp = { options, parse_opt, 0, doc };
arguments_t arguments;

/*
 *
 * Main Program & Control
 *
 */
int main(int argc, char *argv[]);
void exit_cli(int sig);

/*
 * Error Handling
 */
void error(int num, const char *msg, const char *path);
static void error(const char *format, ...);
void sig_handler(int dummy);

#endif /* MAIN_H_ */
