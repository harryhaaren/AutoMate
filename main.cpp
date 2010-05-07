#include <iostream>
#include <cstdlib>
#include <vector>

#include "automationwidget.hpp"

#include <gtkmm.h>

//#define DEBUG_AUTOMATIONWIDGET


int main(int argc,char *argv[])
{
	
	Gtk::Main kit(argc, argv);
	
	Gtk::Window window;
	Gtk::VBox   hbox;
	Gtk::Button button;
	
	AutomationWidget autoWidget;
	//AutomationWidget autoWidget2;
	//AutomationWidget autoWidget3;
	
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
	
	//Get the Glade-instantiated Dialog:
	refBuilder->get_widget("mainWindow", gladeWindow);
	if(gladeWindow)
	{
		//Get the Glade-instantiated vBox, and connect a signal handler:
		refBuilder->get_widget("widgetVBox", vBox);
		if(vBox)
		{
			vBox -> add (autoWidget);
			vBox -> set_border_width(10);
			vBox -> set_spacing(10);
			//vBox -> add (autoWidget2);
			//vBox -> add (autoWidget3);
			vBox -> show_all();
		}
	}
	//--- END load GLADE file
	
	autoWidget.update_time(0);
	
	//autoWidget2.setNumberOfBars(4);
	
	gladeWindow -> set_title("AutoMate");
	gladeWindow -> set_default_size(700,250);
	
	// bind the "new-data" signal from MIDI -> not implemented yet
	//midi::signal_newMidiData.connect( sigc::ptr_fun( midi::filterData ) );
	
	//Glib::signal_timeout().connect ( sigc::mem_fun ( &autoWidget ,  &AutomationWidget::get_value ) , 100 );
	
	kit.run(*gladeWindow);
	
	return 0;
}
