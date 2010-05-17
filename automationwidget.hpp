#ifndef AUTOMATIONWIDGET
#define AUTOMATIONWIDGET

#include <gtkmm/drawingarea.h>

class AutomationWidget : public Gtk::DrawingArea
{
	public:
		AutomationWidget();
		~AutomationWidget();
		
		float getValue ();
		void update_time(float inTime);
		void setNumberOfBars(int setNumberOfBars);
		void set_points(std::vector<int> pointsIn);
		
		bool onScrollEvent	(GdkEventScroll *event);
		bool onMouseClick	(GdkEventButton *event);
		bool onMouseMove	(GdkEventMotion *event);
		bool on_expose_event(GdkEventExpose *event);
		bool onMouseButton1Down( GdkEventButton *event ) ;
		bool onMouseButton3Down( GdkEventButton *event ) ;
	
	protected:
		float time;
		int numberOfBars;
		int playheadPosition;				//	in pixels
		int width,height;
		float mouseX,mouseY;				// in pixels
		std::vector <float> horizontals;	// floating-points
		std::vector <float> verticals;		// floating-points
		
		bool redraw();
		int  timer_callback();
		std::string convertFloatToStr (float number);
		

};

#endif // AUTOMATIONWIDGET
