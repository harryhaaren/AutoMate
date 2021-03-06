
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

#include <iostream>
#include <cstdlib>
#include <vector>

#include "jack.hpp"
#include "automationtrack.hpp"

#include <gtkmm.h>

int main(int argc,char *argv[])
{
	
	Gtk::Main kit(argc, argv);
	
	Jack jack;
	
	Gtk::Window window;
	Gtk::VBox   hbox;
	Gtk::Button button;
	
	//--- Load GLADE file
	Gtk::VBox 	*vBox = 0;
	Gtk::Window *gladeWindow = 0;
	
	//Load the Glade file and instiate its widgets:
	Glib::RefPtr<Gtk::Builder> refBuilder = Gtk::Builder::create();
	
	std::string gladeFile = "automate.glade";
	
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
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
	#else
	std::auto_ptr<Glib::Error> error;

	if (!refBuilder->add_from_file(gladeFile, error))
	{
		std::cerr << error->what() << std::endl;
		exit(1);
	}
	#endif /* !GLIBMM_EXCEPTIONS_ENABLED */
	
	
	// create Automation tracks here
	AutomationTrack autoTrack[4];
	
	
	//Get the Glade-instantiated Dialog:
	refBuilder->get_widget("mainWindow", gladeWindow);
	if(gladeWindow)
	{
		//Get the Glade-instantiated vBox, and connect a signal handler:
		refBuilder->get_widget("widgetVBox", vBox);
		if(vBox)
		{
			// ugly: but it passes events straight to widget.. which is nice
			for (int i = 0; i < 4; i++)
				vBox -> add ( *autoTrack[i].box);
			
			vBox -> set_border_width(10);
			vBox -> set_spacing(10);
			vBox -> show_all();
		}
	}
	//--- END load GLADE file
	
	// Set up window details
	gladeWindow -> set_title("AutoMate");
	gladeWindow -> set_default_size(700,250);
	gladeWindow -> show_all();
	
	//Glib::signal_timeout().connect(sigc::mem_fun( autoTrack, &AutomationTrack::updateTime ), 100);
	
	// add the array to the jack class, so it can update the times
	jack.setTrackVector(&autoTrack[0]);
	
	// activate the client
	jack.activate();
	
	kit.run(*gladeWindow);
	
	return 0;
}
