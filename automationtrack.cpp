
#include "automationtrack.hpp"

AutomationTrack::AutomationTrack()
{
	std::cout << "AutomationTrack();" << std::endl;
	
	add_events( Gdk::EXPOSURE_MASK | Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::SCROLL_MASK);
	
	midiCC = 10;
	midiChannel = 0;
	
	jackOut.activate();
}

AutomationTrack::~AutomationTrack()
{
	std::cout << "~AutomationTrack();" << std::endl;
}

bool AutomationTrack::updateTime()
{
	//std::cout << "AutomationTrack::updateTime();" << std::endl;
	
	widget.update_time();
	
	return true;
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
