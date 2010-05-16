#ifndef JACK
#define JACK

#include <iostream>
#include <jack/jack.h>
#include <jack/midiport.h>

#include "automationtrack.hpp"

class Jack
{
	public:
		Jack();
		~Jack();
		
		void activate();
		
		void setTrackVector(AutomationTrack* array);
		
		static int staticProcess(jack_nframes_t nframes, void *arg);
	
	private:
		float bpm;
		
		int process(jack_nframes_t nframes);
		
		AutomationTrack* arrayPointer;
		
		jack_client_t*	client;
		jack_port_t*		inputPort;
		jack_port_t*		outputPort;
};

#endif 
