#ifndef AUTOMATIONTRACK
#define AUTOMATIONTRACK

#include "automationwidget.hpp"

#include <iostream>
#include <gtkmm.h>
#include <gtkmm/comboboxtext.h>

class AutomationTrack
{
	public:
		AutomationTrack();
		~AutomationTrack();
		
		bool setTime(unsigned int time);
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
		
		// Widgets
		Gtk::VBox* leftBox;
		Gtk::ComboBoxText cc;
		Gtk::ComboBoxText channel;
		Gtk::ToggleButton* toggleButton;
		AutomationWidget widget;
		
		// functions for selecting inputs
		void on_cc_changed();
		void on_channel_changed();
	
};

#endif
