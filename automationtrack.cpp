
#include "automationtrack.hpp"

#include <sstream>

// To Convert Floats to STR. Used to display the Value of the Widget on the widget.
std::string floatToStr (float number)
{
     std::ostringstream buff;
     buff<<number;
     return buff.str();
}

int strToInt(std::string string)
{
	std::istringstream buffer(string);
	int output;
	buffer >> output;
	return output;
}

AutomationTrack::AutomationTrack()
{
	midiCC = 10;
	midiChannel = 0;
	
	//Load the widget from Glade file and instiate its widgets
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	std::string gladeFile = "automate.glade";
	
	try
	{
		refBuilder->add_from_file(gladeFile);
	}
	catch(const Glib::FileError& ex)
	{
		std::cerr << "FileError: " << ex.what() << std::endl;
		std::cout << "\nAutoMate has encountered an error. It seems that" << std::endl;
		std::cout << "automate.glade, cannot be found in its usual place." << std::endl;
		std::cout << "AutoMate cannot continue without this file. Sorry..." << std::endl;
		exit(1);
	}
	catch(const Gtk::BuilderError& ex)
	{
		std::cerr << "BuilderError: " << ex.what() << std::endl;
		std::cout << "\nLuppp has encountered an error. It seems that" << std::endl;
		std::cout << "mainwindow.glade, cannot be found in its usual place." << std::endl;
		std::cout << "Luppp cannot continue without this file. Sorry..." << std::endl;
		exit(1);
	}
	
	refBuilder->get_widget("widgetBox", box);
	refBuilder->get_widget("leftBox"  , leftBox);
	refBuilder->get_widget("activate" , toggleButton);
	
	leftBox->add(channel);
	leftBox->add(cc);
	
	
	for (int i = 0; i < 16; i++)
		channel.append_text( floatToStr(i) );
	
	cc.append_text(  "1"); // mod wheel
	cc.append_text(  "2"); // breath
	cc.append_text(  "7"); // vol
	cc.append_text( "10"); // pan
	cc.append_text( "64"); // sustain pedal
	cc.append_text( "71"); // resonance (timbre)
	cc.append_text( "74"); // Cutoff freq
	cc.append_text( "91"); // reverb
	cc.append_text( "93"); // Chorus
	
	box->add( widget );
	box->show_all();
	
	entry = cc.get_entry(); // gets the entry buffer, we connect to it below
	
	
	channel.signal_changed().connect( sigc::mem_fun(*this, &AutomationTrack::on_channel_changed ));
	entry->signal_changed().connect( sigc::mem_fun(*this, &AutomationTrack::on_cc_changed ));
}

void AutomationTrack::on_channel_changed()
{
	std::cout << "Channel changed: " << midiChannel << std::endl;
	midiChannel = channel.get_active_row_number();
}

void AutomationTrack::on_cc_changed()
{
	std::string  string = cc.get_entry()->get_text(); //cc.get_active_row_number();
	
	if (string != "")
	{
		midiCC = strToInt(string);
	std::cout << "CC changed: " << midiCC << std::endl;
	}
}


AutomationTrack::~AutomationTrack()
{
}

bool AutomationTrack::setTime(jack_transport_state_t inTransport , jack_position_t inPos)
{
	pos  = inPos;
	transport = inTransport;
	
	// gotta sort out the length of the automation loop, beats bars, 
	// current frame & beat bar tick. Finally send a float to update_time
	if (transport & JackTransportRolling)
	{
		time = ((pos.beat-1) + (pos.tick / pos.ticks_per_beat)) / 4.0;
		
		// here we pass a float value 0 = begin, 1 = end
		widget.update_time( time );
	}
	
	return true;
}

float AutomationTrack::getValue()
{
	//std::cout << "AutomationTrack::getValue();" << std::endl;
	if (transport & JackTransportRolling)
	return widget.getValue();
}

int AutomationTrack::getCC()
{
	return midiCC;
}

int AutomationTrack::getChannel()
{
	return midiChannel;
}

int AutomationTrack::getActive()
{
	return toggleButton->get_active();
}

void AutomationTrack::setChannel(int inChannel)
{
	std::cout << "AutomationTrack::setChannel("<<inChannel<<");" << std::endl;
	midiChannel = inChannel;
}

void AutomationTrack::setCC(int inCC)
{
	std::cout << "AutomationTrack::setCC("<<inCC<<");" << std::endl;
	midiCC = inCC;
}
