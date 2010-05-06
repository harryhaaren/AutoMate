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
		int playheadPosition;				//	strange resolution
		int width,height;
		float mouseX,mouseY;					// pixel co-ordinates, NOT points values.
		std::vector <float> horizontals;
		std::vector <float> verticals;
		
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
