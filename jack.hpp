#ifndef JACK
#define JACK

#include <iostream>
#include <jack/jack.h>
#include <jack/midiport.h>

class Jack
{
	public:
		Jack();
		~Jack();
		
		void activate();
		
		static int process(jack_nframes_t nframes, void *arg);
	
	private:
		static int i;
		
		static jack_client_t*	client;
		static jack_port_t*		inputPort;
		static jack_port_t*		outputPort;
};

#endif 
