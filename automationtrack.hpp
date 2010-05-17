#ifndef AUTOMATIONTRACK
#define AUTOMATIONTRACK

#include "automationwidget.hpp"

#include <iostream>
#include <jack/jack.h>
#include <gtkmm.h>
#include <gtkmm/comboboxtext.h>

class AutomationTrack
{
	public:
		AutomationTrack();
		~AutomationTrack();
		
		bool setTime( jack_transport_state_t transport, jack_position_t pos );
		float getValue();
		
		int getCC();
		int getChannel();
		
		int getActive();
		
		void setCC(int inCC);
		void setChannel(int inChannel);
		
		// should be replaced by a hbox or vbox, so i can add more widgets
		// selecting what type of data & which CC etc to use
		Gtk::HBox* box;
		
	
	private:
		int midiCC;
		int midiChannel;
		
		float time;
		
		// Widgets
		Gtk::VBox* leftBox;
		Gtk::ComboBoxText cc;
		Gtk::ComboBoxText channel;
		Gtk::ToggleButton* toggleButton;
		AutomationWidget widget;
		
		// time handling
		jack_position_t pos;
		jack_transport_state_t transport;
		
		// functions for selecting inputs
		void on_cc_changed();
		void on_channel_changed();
	
};

#endif
