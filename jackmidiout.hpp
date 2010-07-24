#ifndef JACKMIDIOUT
#define JACKMIDIOUT

#include <iostream>
#include <jack/jack.h>
#include <jack/midiport.h>

class JackMidiOut
{
	public:
		JackMidiOut();
		~JackMidiOut();
		
		void activate();
		
		static int process(jack_nframes_t nframes, void *arg);
	
	private:
		static int i;
		
		static jack_client_t*	client;
		static jack_port_t*		inputPort;
		static jack_port_t*		outputPort;
};

#endif 
