
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

	jack_position_t			positionQuery;
	jack_transport_state_t	transportQuery;
	
	// get output port buffers
	void* out_port_buf = jack_port_get_buffer( outputPort, nframes);
	unsigned char* buffer;
	jack_midi_clear_buffer(out_port_buf);
	
	transportQuery 			= jack_transport_query ( client, &positionQuery );
	jack_nframes_t frame	= jack_get_sample_rate ( client );
	
	if( (transportQuery & JackTransportRolling) && (positionQuery.valid & JackPositionBBT) && (positionQuery.tick == 0) )
	{
		buffer = jack_midi_event_reserve(out_port_buf, 0, 3);
		
		// write note on
		buffer[0] = 144;	// note on 
		buffer[1] = 60;		// which note
		buffer[2] = 127;	// velocity
	}
	
	//std::cout << jack_frame_time(client) % 22050 << std::endl;
	
	return 0;
}
