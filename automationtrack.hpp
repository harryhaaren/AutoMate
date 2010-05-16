#ifndef AUTOMATIONTRACK
#define AUTOMATIONTRACK

#include "automationwidget.hpp"

#include <iostream>

class AutomationTrack
{
	public:
		AutomationTrack();
		~AutomationTrack();
		
		bool updateTime();
		float getValue();
		
		void setCC(int inCC);
		void setChannel(int inChannel);
		
		AutomationWidget widget;
	
	private:
		int midiCC;
		int midiChannel;
};

#endif
