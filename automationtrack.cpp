
#include "automationtrack.hpp"

AutomationTrack::AutomationTrack()
{
	std::cout << "AutomationTrack();" << std::endl;
	
	midiCC = 10;
	midiChannel = 0;
}

AutomationTrack::~AutomationTrack()
{
	std::cout << "~AutomationTrack();" << std::endl;
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
