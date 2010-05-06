#ifndef AUTOMATIONTRACK
#define AUTOMATIONTRACK

#include "automationWidget.hpp"
#include <gtkmm/button.h>

class AutomationTrack
{
	public:
		AutomationTrack();
		~AutomationTrack();
		setMidiCC (int cc);
		setMidiChannel	(int channel);
	private:
		int midiCC;
		int midiChannel;
		//Gtk::Button button
		AutomationWidget automationWidget;
}

#endif