#ifndef AUTOMATIONTRACK
#define AUTOMATIONTRACK

#include "automationwidget.hpp"

#include "jackmidiout.hpp"

#include <iostream>
#include <gtkmm/box.h>

class AutomationTrack : public Gtk::DrawingArea
{
	public:
		AutomationTrack();
		~AutomationTrack();
		
		bool updateTime();
		
		void setCC(int inCC);
		void setChannel(int inChannel);
		
		AutomationWidget widget;
		JackMidiOut jackOut;
	
	private:
		int midiCC;
		int midiChannel;
};

#endif
