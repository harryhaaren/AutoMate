#ifndef AUTOMATIONWIDGET
#define AUTOMATIONWIDGET

#include <gtkmm/drawingarea.h>

class AutomationWidget : public Gtk::DrawingArea
{
	public:
		AutomationWidget();
		~AutomationWidget();
		
		float  getValue ();
		void update_time(float time);
		void setNumberOfBars(int setNumberOfBars);
		void set_points(std::vector<int> pointsIn);
	
	protected:
		float time;
		int numberOfBars;
		int playheadPosition;				//	in pixels
		int width,height;
		float mouseX,mouseY;				// in pixels
		std::vector <float> horizontals;	// floating-points
		std::vector <float> verticals;		// floating-points
		
		void redraw();
		int  timer_callback();
		bool onScrollEvent	(GdkEventScroll *event);
		bool onMouseClick	(GdkEventButton *event);
		bool onMouseMove	(GdkEventMotion *event);
		bool on_expose_event(GdkEventExpose *event);
		std::string convertFloatToStr (float number);
		bool onMouseButton1Down( GdkEventButton *event ) ;
		bool onMouseButton3Down( GdkEventButton *event ) ;
};

#endif // AUTOMATIONWIDGET
