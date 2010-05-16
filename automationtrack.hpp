#ifndef AUTOMATIONTRACK
#define AUTOMATIONTRACK

#include "automationwidget.hpp"

#include <iostream>

class AutomationTrack
{
	public:
		AutomationTrack();
		~AutomationTrack();
		
		bool setTime(unsigned int time);
		float getValue();
		
		int getCC();
		int getChannel();
		
		void setCC(int inCC);
		void setChannel(int inChannel);
		
		// should be replaced by a hbox or vbox, so i can add more widgets
		// selecting what type of data & which CC etc to use
		AutomationWidget widget;
	
	private:
		int midiCC;
		int midiChannel;
};

#endif
