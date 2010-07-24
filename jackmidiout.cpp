
#include "jackmidiout.hpp"

int				JackMidiOut::i;
jack_client_t*	JackMidiOut::client;
jack_port_t	*	JackMidiOut::inputPort;
jack_port_t	*	JackMidiOut::outputPort;

JackMidiOut::JackMidiOut()
{
	i = 0;
	
	std::cout << "JackMidiOut()" << std::flush;
	
	if ((client = jack_client_open("AutoMate", JackNullOption, NULL)) == 0)
	{
		std::cout << "jack server not running?" << std::endl;
	}
	
	inputPort  = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
	outputPort = jack_port_register (client, "midi_out",JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
	
	jack_set_process_callback (client, process, 0);
	
	std::cout << "\t\t\tDone!" << std::endl;
	
}

JackMidiOut::~JackMidiOut()
{
	std::cout << "~JackMidiOut()" << std::endl;
}

void JackMidiOut::activate()
{
	std::cout << "activate()" << std::endl;
	
	if (jack_activate(client))
	{
		std::cout<<  "cannot activate client" << std::endl;
	}
}


int JackMidiOut::process(jack_nframes_t nframes, void *arg)
{
	jack_midi_event_t in_event;
	
	jack_nframes_t event_index = 0;
	
	void* port_buf = jack_port_get_buffer( inputPort, nframes);
	
	// input: get number of events, and process them.
	jack_nframes_t event_count = jack_midi_get_event_count(port_buf);
	if(event_count > 1)
	{
		std::cout << "midisine: have " << event_count << " events" << std::endl;
		for(i=0; i<event_count; i++)
		{
			jack_midi_event_get(&in_event, port_buf, i);
			std::cout << "event" << i << "time is " << in_event.time << ". 1st byte is " << *(in_event.buffer) << "." << std::endl;
		}
	}
	
	// output:
	void* out_port_buf = jack_port_get_buffer( outputPort, nframes);
	unsigned char* buffer;
	jack_midi_clear_buffer(out_port_buf);
	
	if(i > 1000)
	{
		buffer = jack_midi_event_reserve(out_port_buf, 0, 3);
		
		// write note on
		buffer[0] = 144;	// note on 
		buffer[1] = 60;		// which note
		buffer[2] = 127;	// velocity 
		
		i = 0;
	}
	if (i > 240)
	{
		buffer = jack_midi_event_reserve(out_port_buf, 0, 3);
		
		// write note off
		buffer[0] = 128;	// note off 
		buffer[1] = 60;		// which note
		buffer[2] = 127;	// velocity 
	}
	
	// std::cout << "Test" << i << std::endl;
	i++;
	
	return 0;
}
