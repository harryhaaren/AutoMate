
/*	Program AutoMate: A musical automation tool
	Author: Harry van Haaren
	E-mail: harryhaaren@gmail.com
	Copyright (C) 2010 Harry van Haaren

	AutoMate is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	AutoMate is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with AutoMate.  If not, see <http://www.gnu.org/licenses/>. */

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
