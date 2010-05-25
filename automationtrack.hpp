
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
		Gtk::ComboBoxText channel;
		Gtk::ComboBoxEntryText cc;
		Gtk::Entry* entry;
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
