/*
 * 		Main.cpp
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


#include "Main.h"
/*
 * MIDI / OSC Processing
 */
int process_incoming_osc(const char *path, const char *types, lo_arg ** argv,
                    int argc, void *data, void *user_data) {
	int err=0;
    try {
        if (arguments.verbose)
            printTime();
        if( strcmp( path, "/oscmidi/parameter_change" ) == 0 && argc == 4) {
        	if(argv[0]->i==YLS916_SYSEX){
        		if (arguments.verbose)
        			cout << "\tOSC received '" << path << hex << argv[0]->i << " " <<
																 argv[1]->i<< " " <<
																 argv[2]->i << " " <<
																 argv[3]->i << " " <<endl;
				u_char send_data[]={SYSEX_START_BYTE,
									MANU_YAMAHA,
									PARAMETER_CHANGE,
									0xff & (Y01V96V2_SYSEX >>16),	// Device Type
									0xff & (Y01V96V2_SYSEX >>8), // Device Type
									0xff & Y01V96V2_SYSEX,
									Y01V96V2_FB_FADER, 			// Function Block
									0xff & (argv[2]->i >>8),	// 	Parameter
									0xff & argv[2]->i,
									0xff & (argv[3]->i >>24),	// 	Value
									0xff & (argv[3]->i >>16),
									0xff & (argv[3]->i >>8),
									0xff & argv[3]->i,
									SYSEX_END_BYTE};

				for (int i=0; i<sizeof(send_data); i++) cout << hex << (int) send_data[i] << " ";
				cout << endl;fflush(stdout);

				if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
										error("cannot send data: %s", snd_strerror(err));


        	} else if(argv[0]->i==Y01V96V2_SYSEX){
        		if (arguments.verbose)
					cout << "\tOSC received '" << path << hex << argv[0]->i << " " <<
																 argv[1]->i<< " " <<
																 argv[2]->i << " " <<
																 argv[3]->i << " " <<endl;
				u_char send_data[]={SYSEX_START_BYTE,
									MANU_YAMAHA,
									PARAMETER_CHANGE,
									0xff & (YLS916_SYSEX >>16),	// Device Type
									0xff & (YLS916_SYSEX >>8),
									0xff & YLS916_SYSEX,
									0xff & (last_request >>24),	// Function Block
									0xff & (last_request >>16),
									0xff & (last_request >>8),
									0xff & last_request,
									0xff & (argv[2]->i >>8),	// Parameter
									0xff & argv[2]->i,
									0,
									0xff & (argv[3]->i >>24),	// Value
									0xff & (argv[3]->i >>16),
									0xff & (argv[3]->i >>8),
									0xff & argv[3]->i,
									SYSEX_END_BYTE};

				for (int i=0; i<sizeof(send_data); i++) cout << hex << (int) send_data[i] << " ";
				cout << endl;fflush(stdout);

				if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
						error("cannot send data: %s", snd_strerror(err));

        	}
         }

        else if( strcmp( path, "/oscmidi/parameter_request" ) == 0 && argc == 1) {
			if (arguments.verbose)
				cout << "\tOSC received '" << path << hex << argv[0]->i << " " << endl;

			u_int function_block=0;
			switch(argv[0]->i){
				case Y01V96V2_RTN1:	function_block = YLS916_FB_INPUT; break;
				case Y01V96V2_RTN2:	 function_block = YLS916_FB_INPUT; break;
				case Y01V96V2_INPUT_1:	 function_block = YLS916_FB_MIX1; break;
				case Y01V96V2_INPUT_2:	 function_block = YLS916_FB_MIX2; break;
				case Y01V96V2_INPUT_3:	 function_block = YLS916_FB_MIX3; break;
				case Y01V96V2_INPUT_4:	 function_block = YLS916_FB_MIX4; break;
				case Y01V96V2_INPUT_5:	 function_block = YLS916_FB_MIX5; break;
				case Y01V96V2_INPUT_6:	 function_block = YLS916_FB_MIX6; break;
				case Y01V96V2_INPUT_7:	 function_block = YLS916_FB_MIX7; break;
				case Y01V96V2_INPUT_8:	 function_block = YLS916_FB_MIX8; break;
				case Y01V96V2_INPUT_9:	 function_block = YLS916_FB_MIX9; break;
				case Y01V96V2_INPUT_10:	 function_block = YLS916_FB_MIX10; break;
				case Y01V96V2_INPUT_11:	 function_block = YLS916_FB_MIX11; break;
				case Y01V96V2_INPUT_12:	 function_block = YLS916_FB_MIX12; break;
				case Y01V96V2_INPUT_13:	 function_block = YLS916_FB_MIX13; break;
				case Y01V96V2_INPUT_14:	 function_block = YLS916_FB_MIX14; break;
				case Y01V96V2_INPUT_15:	 function_block = YLS916_FB_MIX15; break;
				case Y01V96V2_INPUT_16:	 function_block = YLS916_FB_MIX16; break;
#if MASTER_ADDRESS_DUPLICATE_PROBLEM
				case Y01V96V2_MASTER_L:	 function_block = YLS916_FB_MASTER; break;
#endif

			}

			last_request = function_block;

			for(int i=0; i<16;i++){

				u_char send_data[]={SYSEX_START_BYTE,
									MANU_YAMAHA,
									PARAMETER_REQUEST,
									0xff & (YLS916_SYSEX >>16),	// Device Type
									0xff & (YLS916_SYSEX >>8),
									0xff & YLS916_SYSEX,
									0xff & function_block >> 24,	// Function Block
									0xff & function_block >>16,
									0xff & function_block >>8,
									0xff & function_block,
									0,								// Parameter
									0x00 | i,						// Parameter
									SYSEX_END_BYTE};

				for (int i=0; i<sizeof(send_data); i++) cout << hex << (int) send_data[i] << " ";
				cout << endl;fflush(stdout);

				if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
										error("cannot send data: %s", snd_strerror(err));
			}

   		}

        else {
			cout << "\tOSC received '" << path << "' message, which is not oscmidi-message!" << endl;
            return 1;
		}
    } catch ( ... ) {
        cout << "error while parsing message: " <<  "\n";
    }
    return 1;
}


void* process_incoming_midi(void* argv){
	int npfd;
	int err;
	struct pollfd* pfd;


	inputp = &input;
	outputp = &output;

	if ((err = snd_rawmidi_open(inputp, outputp, port_name, 0)) < 0) {
		error("cannot open port \"%s\": %s", port_name, snd_strerror(err));
	}
	if (inputp)
		snd_rawmidi_read(input, NULL, 0); /* trigger reading */

    if (arguments.tcp) {
        transmit_socket = lo_address_new_with_proto(LO_TCP, arguments.ip, arguments.sport);
    } else {
        transmit_socket = lo_address_new(arguments.ip, arguments.sport);
    }

	if (arguments.verbose) {
		cout << "Sending MIDI to " << arguments.ip << ":" << arguments.sport << " using";
        if (arguments.tcp)
            cout << " TCP." << endl;
        else
            cout << " UDP." << endl;
    }

	last_request=0xffff;

	while (run)	{
		if (inputp) {
			int read = 0;
			int npfds, time = 0, j=0;
			struct pollfd *pfds;
			u_char buf[256], msg_buf[20];

			timeout *= 1000;
			snd_rawmidi_nonblock(input, 1);
			npfds = snd_rawmidi_poll_descriptors_count(input);
			pfds = (struct pollfd*) alloca(npfds * sizeof(struct pollfd));
			snd_rawmidi_poll_descriptors(input, pfds, npfds);
			signal(SIGINT, exit_cli);
			signal(SIGTERM, exit_cli);
			for (;;) {
				int i, length;
				unsigned short revents;

				err = poll(pfds, npfds, 200);
				if (stop || (err < 0 && errno == EINTR))
					break;
				if (err < 0) {
					error("poll failed: %s", strerror(errno));
					break;
				}
				if (err == 0) {
					time += 200;
					if (timeout && time >= timeout)
						break;
					continue;
				}
				if ((err = snd_rawmidi_poll_descriptors_revents(input, pfds, npfds, &revents)) < 0) {
					error("cannot get poll events: %s", snd_strerror(errno));
					break;
				}
				if (revents & (POLLERR | POLLHUP))
					break;
				if (!(revents & POLLIN))
					continue;
				err = snd_rawmidi_read(input, buf, sizeof(buf));
				if (err == -EAGAIN)
					continue;
				if (err < 0) {
					error("cannot read from port \"%s\": %s", port_name, snd_strerror(err));
					break;
				}
				length = 0;
				for (i = 0; i < err; ++i)
					if (buf[i] != 0xfe)
						buf[length++] = buf[i];
				if (length == 0)
					continue;
				read += length;
				time = 0;

				for (i = 0; i < length; ++i){

					if(buf[i]==0xF0){
						msg_buf[j]=buf[i];
						//print_byte(buf[i]);
						j++;
					}
					else if(buf[i]==0xF7){
						msg_buf[j]=buf[i];

						if( (msg_buf[3] << 16  | msg_buf[4] << 8 | msg_buf[5]) == Y01V96V2_SYSEX){
							u_int function_block;// = msg_buf[6];
							u_int parameter = msg_buf[7] << 8 | msg_buf[8];
							u_int value =  msg_buf[9] << 24 | msg_buf[10] << 16 | msg_buf[11] << 8 | msg_buf[12];
							if((msg_buf[2]==PARAMETER_CHANGE && msg_buf[6] == Y01V96V2_FB_ON_BT) &&
									((parameter >= Y01V96V2_INPUT_1 && parameter <= Y01V96V2_INPUT_16) ||
									(parameter == Y01V96V2_RTN1 || parameter == Y01V96V2_RTN2) ||
									(parameter == Y01V96V2_MASTER_L || parameter == Y01V96V2_MASTER_R))){

								switch(parameter){
									case Y01V96V2_RTN1:	function_block = YLS916_FB_INPUT; break;
									case Y01V96V2_RTN2:	 function_block = YLS916_FB_INPUT; break;
									case Y01V96V2_INPUT_1:	 function_block = YLS916_FB_MIX1; break;
									case Y01V96V2_INPUT_2:	 function_block = YLS916_FB_MIX2; break;
									case Y01V96V2_INPUT_3:	 function_block = YLS916_FB_MIX3; break;
									case Y01V96V2_INPUT_4:	 function_block = YLS916_FB_MIX4; break;
									case Y01V96V2_INPUT_5:	 function_block = YLS916_FB_MIX5; break;
									case Y01V96V2_INPUT_6:	 function_block = YLS916_FB_MIX6; break;
									case Y01V96V2_INPUT_7:	 function_block = YLS916_FB_MIX7; break;
									case Y01V96V2_INPUT_8:	 function_block = YLS916_FB_MIX8; break;
									case Y01V96V2_INPUT_9:	 function_block = YLS916_FB_MIX9; break;
									case Y01V96V2_INPUT_10:	 function_block = YLS916_FB_MIX10; break;
									case Y01V96V2_INPUT_11:	 function_block = YLS916_FB_MIX11; break;
									case Y01V96V2_INPUT_12:	 function_block = YLS916_FB_MIX12; break;
									case Y01V96V2_INPUT_13:	 function_block = YLS916_FB_MIX13; break;
									case Y01V96V2_INPUT_14:	 function_block = YLS916_FB_MIX14; break;
									case Y01V96V2_INPUT_15:	 function_block = YLS916_FB_MIX15; break;
									case Y01V96V2_INPUT_16:	 function_block = YLS916_FB_MIX16; break;
	#if MASTER_ADDRESS_DUPLICATE_PROBLEM
									case Y01V96V2_MASTER_L:	 function_block = YLS916_FB_MASTER; break;
	#endif
								}

								if(last_request!=function_block) last_request = function_block;

								// [ON] Condition

								/*
								 * 	Set other ON Buttons to 0
								 */
								for(int i=0;i<16;i++){
									if(parameter != (Y01V96V2_INPUT_1 + i)){
										u_char send_data[]={SYSEX_START_BYTE,
														MANU_YAMAHA,
														PARAMETER_CHANGE,
														0xff & (Y01V96V2_SYSEX >>16),	// Device Type
														0xff & (Y01V96V2_SYSEX >>8),
														0xff & Y01V96V2_SYSEX,
														Y01V96V2_FB_ON_BT,
														0x00,
														0x00 | i,
														0,
														0,
														0,
														0,
														SYSEX_END_BYTE};

										if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
											error("cannot send data: %s", snd_strerror(err));
									}
								}

								if(parameter != Y01V96V2_RTN1){
									u_char send_data[]={SYSEX_START_BYTE,
													MANU_YAMAHA,
													PARAMETER_CHANGE,
													0xff & (Y01V96V2_SYSEX >>16),	// Device Type
													0xff & (Y01V96V2_SYSEX >>8),
													0xff & Y01V96V2_SYSEX,
													Y01V96V2_FB_ON_BT,	// Device Type
													0xff & (Y01V96V2_RTN1 >>8),
													0xff & Y01V96V2_RTN1,
													0,
													0,
													0,
													0,
													SYSEX_END_BYTE};

									if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
										error("cannot send data: %s", snd_strerror(err));
								}

								if(parameter != Y01V96V2_RTN2){
									u_char send_data[]={SYSEX_START_BYTE,
														MANU_YAMAHA,
														PARAMETER_CHANGE,
														0xff & (Y01V96V2_SYSEX >>16),	// Device Type
														0xff & (Y01V96V2_SYSEX >>8),
														0xff & Y01V96V2_SYSEX,
														Y01V96V2_FB_ON_BT,	// Device Type
														0xff & (Y01V96V2_RTN2 >>8),
														0xff & Y01V96V2_RTN2,
														0,
														0,
														0,
														0,
														SYSEX_END_BYTE};

									if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
										error("cannot send data: %s", snd_strerror(err));
								}
#if MASTER_ADDRESS_DUPLICATE_PROBLEM
								if(parameter != Y01V96V2_MASTER_L){
									u_char send_data[]={SYSEX_START_BYTE,
													MANU_YAMAHA,
													PARAMETER_CHANGE,
													0xff & (Y01V96V2_SYSEX >>16),	// Device Type
													0xff & (Y01V96V2_SYSEX >>8),
													0xff & Y01V96V2_SYSEX,
													Y01V96V2_FB_MASTER_ON_BT,	// Device Type
													0xff & (Y01V96V2_MASTER_L >>8),
													0xff & Y01V96V2_MASTER_L,
													0,
													0,
													0,
													0,
													SYSEX_END_BYTE};

									if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
										error("cannot send data: %s", snd_strerror(err));
								} else if(parameter != Y01V96V2_MASTER_R){
									u_char send_data[]={SYSEX_START_BYTE,
													MANU_YAMAHA,
													PARAMETER_CHANGE,
													0xff & (Y01V96V2_SYSEX >>16),	// Device Type
													0xff & (Y01V96V2_SYSEX >>8),
													0xff & Y01V96V2_SYSEX,
													Y01V96V2_FB_MASTER_ON_BT,	// Parameter
													0xff & (Y01V96V2_MASTER_R >>8),
													0xff & Y01V96V2_MASTER_R,
													0,
													0,
													0,
													0,
													SYSEX_END_BYTE};

									if (((err = snd_rawmidi_write(output, send_data, sizeof(send_data)))) < 0)
										error("cannot send data: %s", snd_strerror(err));
								}

#endif
								if (lo_send(transmit_socket,
												"/oscmidi/parameter_request",
												"i",
												parameter)
											== -1)
											printf("\tOSC error %d: %s", lo_address_errno(transmit_socket), lo_address_errstr(transmit_socket));
								//else cout << "/oscmidi/parameter_change sent!" << endl; fflush(stdout);
							} else if(msg_buf[2]==PARAMETER_CHANGE && msg_buf[6]==Y01V96V2_FB_FADER){
								if (lo_send(transmit_socket,
										"/oscmidi/parameter_change",
										"iiii",
										Y01V96V2_SYSEX,
										last_request,
										parameter ,
										value)
									== -1)
									printf("\tOSC error %d: %s", lo_address_errno(transmit_socket), lo_address_errstr(transmit_socket));
							//	else cout << "/oscmidi/parameter_change sent!" << endl; fflush(stdout);
							}
						} else if((msg_buf[3] << 16| msg_buf[4] << 8| msg_buf[5]) == YLS916_SYSEX){
							u_int function_block = msg_buf[6] << 24 | msg_buf[7] << 16 | msg_buf[8] << 8| msg_buf[9];
							u_int parameter = msg_buf[10] << 8 | msg_buf[11];
							u_int value =  msg_buf[13] << 24 | msg_buf[14] << 16 | msg_buf[15] << 8 | msg_buf[16];

							if(msg_buf[2]==PARAMETER_CHANGE && function_block==last_request){
								if (lo_send(transmit_socket,
										"/oscmidi/parameter_change",
										"iiii",
										YLS916_SYSEX,
										last_request,
										parameter,
										value)
									== -1)
									printf("\tOSC error %d: %s", lo_address_errno(transmit_socket), lo_address_errstr(transmit_socket));
							//	else cout << "/oscmidi/parameter_change sent!" << endl; fflush(stdout);

							}
						}
						//print_byte(buf[i]);
						j=0;
					} else {
						msg_buf[j]=buf[i];
						//print_byte(buf[i]);
						j++;
					}
				}
				fflush(stdout);
			}
		}
	}
	if (arguments.verbose)
		cout << "Stopping [Alsa]->[OSC] communication..." << endl;

}


/*
 * Output
 */
/*OK*/static void print_byte(unsigned char byte)
{
	static enum {
		STATE_UNKNOWN,
		STATE_1PARAM,
		STATE_1PARAM_CONTINUE,
		STATE_2PARAM_1,
		STATE_2PARAM_2,
		STATE_2PARAM_1_CONTINUE,
		STATE_SYSEX
	} state = STATE_UNKNOWN;
	int newline = 0;

	if (byte >= 0xf8)
		newline = 1;
	else if (byte >= 0xf0) {
		newline = 1;
		switch (byte) {
		case 0xf0:
			state = STATE_SYSEX;
			break;
		case 0xf1:
		case 0xf3:
			state = STATE_1PARAM;
			break;
		case 0xf2:
			state = STATE_2PARAM_1;
			break;
		case 0xf4:
		case 0xf5:
		case 0xf6:
			state = STATE_UNKNOWN;
			break;
		case 0xf7:
			newline = state != STATE_SYSEX;
			state = STATE_UNKNOWN;
			break;
		}
	} else if (byte >= 0x80) {
		newline = 1;
		if (byte >= 0xc0 && byte <= 0xdf)
			state = STATE_1PARAM;
		else
			state = STATE_2PARAM_1;
	} else /* b < 0x80 */ {
		int running_status = 0;
		newline = state == STATE_UNKNOWN;
		switch (state) {
		case STATE_1PARAM:
			state = STATE_1PARAM_CONTINUE;
			break;
		case STATE_1PARAM_CONTINUE:
			running_status = 1;
			break;
		case STATE_2PARAM_1:
			state = STATE_2PARAM_2;
			break;
		case STATE_2PARAM_2:
			state = STATE_2PARAM_1_CONTINUE;
			break;
		case STATE_2PARAM_1_CONTINUE:
			running_status = 1;
			state = STATE_2PARAM_2;
			break;
		default:
			break;
		}
		if (running_status)
			fputs("\n  ", stdout);
	}
	printf("%c%02X", newline ? '\n' : ' ', byte);
}

/*OK*/void printTime() {
	time_t currentTime;

	// get and print the current time
 	time (&currentTime); // fill now with the current time

    struct tm * ptm= localtime(&currentTime);

	cout << (ptm->tm_year+1900) << "/";
    if ((ptm->tm_mon)+1 < 10)
        cout << 0;
    cout << ((ptm->tm_mon)+1) << "/";
    if (ptm->tm_mday < 10)
        cout << 0;
	cout << ptm->tm_mday << " ";
    if (ptm->tm_hour < 10)
        cout << 0;
    cout << ptm->tm_hour << ":";
    if (ptm->tm_min < 10)
        cout << 0;
	cout << ptm->tm_min << ":";
    if (ptm->tm_sec < 10)
        cout << 0;
    cout << ptm->tm_sec << " ";
}


/*
 * Error Handling
 */
/*OK*/void error(int num, const char *msg, const char *path)
{
    printf("liblo server error %d in path %s: %s\n", num, path, msg);
    fflush(stdout);
}
//
///*OK*/void sig_handler(int dummy)
//{
//}
///*OK*/static void error(const char *format, ...)
//{
//	va_list ap;
//
//	va_start(ap, format);
//	vfprintf(stderr, format, ap);
//	va_end(ap);
//	putc('\n', stderr);
//}





/*
 *
 * 			Argument  Parsing
 *
 */
/*OK*/static error_t parse_opt (int key, char *arg, struct argp_state *state)
{
	/* Get the input argument from argp_parse, which we
	   know is a pointer to our arguments structure. */
	arguments_t *arguments = (arguments_t*)(state->input);

	switch (key)
	{
		case 'v':
			arguments->verbose = 1;
			break;
        case 't':
			arguments->tcp = 1;
			break;
		case 'm':
			if (arg == NULL) break;
			strncpy(arguments->mixer, arg, MAX_DEV_STR_LEN);
			break;
		case 'i':
			if (arg == NULL) break;
			strncpy(arguments->ip, arg, MAX_DEV_STR_LEN);
			break;
		case 'h':
			if (arg == NULL) break;
			 strncpy(arguments->hw, arg, MAX_DEV_STR_LEN);
			break;
		case 'n':
			if (arg == NULL) break;
			strncpy(arguments->name, arg, MAX_DEV_STR_LEN);
			break;
		case 's':
			if (arg == NULL) break;
            strncpy(arguments->sport, arg, MAX_DEV_STR_LEN);
			break;
		case 'r':
			if (arg == NULL) break;
			 strncpy(arguments->rport, arg, MAX_DEV_STR_LEN);
			break;
		case ARGP_KEY_ARG:
		case ARGP_KEY_END:
			break;

		default:
			return ARGP_ERR_UNKNOWN;
	}

	return 0;
}

/*OK*/void arg_set_defaults(arguments_t *arguments)
{
	char *ip_temp = (char *)"127.0.0.1";
    char *sport_temp = (char *)"9000";
    char *rport_temp = (char *)"9001";
    char *mixer_temp = (char *)"Y01V96";
    char *hw_temp = (char *)"hw:4,0,0";
	strncpy(arguments->mixer, mixer_temp, MAX_DEV_STR_LEN);
    strncpy(arguments->hw, hw_temp, MAX_DEV_STR_LEN);
	strncpy(arguments->ip, ip_temp, MAX_DEV_STR_LEN);
    strncpy(arguments->sport, sport_temp, MAX_DEV_STR_LEN);
    strncpy(arguments->rport, rport_temp, MAX_DEV_STR_LEN);

	arguments->verbose      = 0;
    arguments->tcp      = 0;

	char *name_temp = (char *)"oscmidi";
	strncpy(arguments->name, name_temp, MAX_DEV_STR_LEN);
}




/*
 * Main Program & Control
 */

int main(int argc, char *argv[])
{
	/*
	 * read command line arguments
	 */
	arg_set_defaults(&arguments);
	argp_parse(&argp, argc, argv, 0, 0, &arguments);

	/*
	 * Open MIDI ports
	 */

	if (arguments.verbose)
		cout << endl << "oscmidi  Copyright (C) 2011  Jari Suominen" << endl << "This program comes with ABSOLUTELY NO WARRANTY."
			<< endl << "This program is free software: you can redistribute it and/or modify" << endl
			<< "it under the terms of the GNU General Public License as published by" << endl
			<< "the Free Software Foundation, either version 3 of the License, or" << endl
			<< "(at your option) any later version." << endl << endl;

	/* Starting thread that is polling alsa midi in port */
	pthread_t midi_out_thread;//, midi_in_thread;
	int iret1;
	run = TRUE;
	iret1 = pthread_create(&midi_out_thread, NULL, process_incoming_midi, (void*)argv);

	/*
	 * OSC In
	 */
	if (strlen(arguments.rport) == 0) {
		strncpy(arguments.rport, arguments.sport, MAX_DEV_STR_LEN);
	}
	lo_server_thread st;
	if (arguments.tcp) {
		st = lo_server_thread_new_with_proto(arguments.rport,LO_TCP, error);
	} else {
		st = lo_server_thread_new_with_proto(arguments.rport,LO_UDP, error);
	}
	/* add method that will match any path and args */
	lo_server_thread_add_method(st, NULL, NULL, process_incoming_osc, NULL);
	lo_server_thread_start(st);
	if (arguments.verbose) {
		cout << "Waiting for OSC messages at port " << arguments.rport << " using";
		if (arguments.tcp)
			cout << " TCP." << endl;
		else
			cout << " UDP." << endl;
	}

	signal(SIGINT, exit_cli);
	signal(SIGTERM, exit_cli);

//	s->Run();

	/* Here we wait until ctrl-c or kill signal will be sent... */

	run = TRUE;

	while (run) { sleep(1000); }

	/* Destruction routine */
	if (arguments.verbose)
		cout << "\r   " << endl << "Stopping [OSC]->[Alsa] communication..." << endl;
	run = FALSE; 		// Alsa thread will poll this...
	void* status;

	pthread_join(midi_out_thread, &status);
	lo_server_thread_stop(st);
	lo_server_thread_free(st);
	usleep(1000); // Attempt to make sure that there is time to free the port. But might not help at all in this!

	if (arguments.verbose)
		cout << "Leaving!" << endl;
	cout << endl;

	return 0;
}


static void error(const char *format, ...)
{
	va_list ap;

	va_start(ap, format);
	vfprintf(stderr, format, ap);
	va_end(ap);
	putc('\n', stderr);
}

/*OK*/void exit_cli(int sig)
{
	stop = 1;
	run = FALSE;
	if (inputp)
		snd_rawmidi_close(input);
	if (outputp)
		snd_rawmidi_close(output);
}








