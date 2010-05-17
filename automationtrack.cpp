
#include "automationtrack.hpp"

#include <sstream>

// To Convert Floats to STR. Used to display the Value of the Widget on the widget.
std::string floatToStr (float number)
{
     std::ostringstream buff;
     buff<<number;
     return buff.str();
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
	
	for (int i = 0; i < 20; i++)
		cc.append_text( floatToStr(i) );
	
	box->add( widget );
	box->show_all();
	
	
	channel.signal_changed().connect( sigc::mem_fun(*this, &AutomationTrack::on_channel_changed ));
	cc.signal_changed().connect( sigc::mem_fun(*this, &AutomationTrack::on_cc_changed ));
}

void AutomationTrack::on_channel_changed()
{
	std::cout << "Channel changed: " << midiChannel << std::endl;
	midiChannel = channel.get_active_row_number();
}

void AutomationTrack::on_cc_changed()
{
	midiCC = cc.get_active_row_number();
	std::cout << "CC changed: " << midiCC << std::endl;
}


AutomationTrack::~AutomationTrack()
{
}

bool AutomationTrack::setTime(unsigned int time)
{
	//std::cout << "AutomationTrack::updateTime();" << std::endl;
	
	widget.update_time(time);
	
	return true;
}

float AutomationTrack::getValue()
{
	//std::cout << "AutomationTrack::getValue();" << std::endl;
	
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
