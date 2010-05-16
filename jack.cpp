
#include "jack.hpp"

Jack::Jack()
{
	bpm = 120.0;
	
	std::cout << "Jack()" << std::flush;
	
	if ((client = jack_client_open("AutoMate", JackNullOption, NULL)) == 0)
	{
		std::cout << "jack server not running?" << std::endl;
	}
	
	inputPort  = jack_port_register (client, "midi_in", JACK_DEFAULT_MIDI_TYPE, JackPortIsInput, 0);
	outputPort = jack_port_register (client, "midi_out",JACK_DEFAULT_MIDI_TYPE, JackPortIsOutput, 0);
	
	jack_set_process_callback (client, staticProcess, static_cast<void*>(this));
	
	std::cout << "\t\t\tDone!" << std::endl;
	
}

Jack::~Jack()
{
	std::cout << "~Jack()" << std::endl;
}

void Jack::setTrackVector(AutomationTrack* array)
{
	std::cout << "In setTrackVector" << std::endl;
	
	// keep a copy of array's address
	arrayPointer = array;
}

void Jack::activate()
{
	std::cout << "activate()" << std::endl;
	
	if (jack_activate(client))
	{
		std::cout<<  "cannot activate client" << std::endl;
	}
}

int Jack::staticProcess(jack_nframes_t nframes, void *arg)
{
	return static_cast<Jack*>(arg)->process(nframes);;
}

int Jack::process(jack_nframes_t nframes)
{
	//std::cout << "Process entered" << std::endl;
	
	jack_midi_event_t in_event;
	jack_nframes_t event_index = 0;
	jack_position_t			positionQuery;
	jack_transport_state_t	transportQuery;
	
	//std::cout << "Getting port buffers" << std::endl;
	
	void* port_buf = jack_port_get_buffer( inputPort, nframes);
	
	/*
	// input: get number of events, and process them.
	jack_nframes_t event_count = jack_midi_get_event_count(port_buf);
	if(event_count > 1)
	{
		std::cout << "midisine: have " << event_count << " events" << std::endl;
		for(int i=0; i<event_count; i++)
		{
			jack_midi_event_get(&in_event, port_buf, i);
			std::cout << "event" << i << "time is " << in_event.time << ". 1st byte is " << *(in_event.buffer) << "." << std::endl;
		}
	}
	*/
	
	// output:
	void* out_port_buf = jack_port_get_buffer( outputPort, nframes);
	unsigned char* buffer;
	jack_midi_clear_buffer(out_port_buf);
	
	//std::cout << "Querying transport" << std::endl;
	
	transportQuery = jack_transport_query(client, &positionQuery );
	
	//std::cout << "Comparing frame & bpm info" << std::endl;
	
	jack_nframes_t frame = jack_get_sample_rate(client);
	
	if(  (unsigned int) (((int)frame) * 60 / bpm)) // (int)(positionQuery->frame) >=
	{
		buffer = jack_midi_event_reserve(out_port_buf, 0, 3);
		
		// write note on
		buffer[0] = 144;	// note on 
		buffer[1] = 60;		// which note
		buffer[2] = 127;	// velocity 
	}
	/*
	if( positionQuery->frame > jack_get_sample_rate(client) * 60 / bpm)
	{
		buffer = jack_midi_event_reserve(out_port_buf, 0, 3);
		
		// write note off
		buffer[0] = 128;	// note off 
		buffer[1] = 60;		// which note
		buffer[2] = 127;	// velocity 
	}
	* */
	
	//std::cout << "normal Process returning" << std::endl;
	
	return 0;
}
