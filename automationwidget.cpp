#include "automationwidget.hpp"


#include <iostream>
#include <vector>
#include <sstream>

#include <iostream>
#include <cairomm/context.h>
#include <gtkmm/drawingarea.h>

// To Convert Floats to STR. Used to display the Value of the Widget on the widget.
std::string AutomationWidget::convertFloatToStr (float number)
{
     std::ostringstream buff;
     buff<<number;
     return buff.str();
}

AutomationWidget::AutomationWidget()
{
	time = 0;
	
	// two initial points
	horizontals.push_back(0);
	verticals.push_back(0);
	
	horizontals.push_back(1);
	verticals.push_back(0);
	
	numberOfBars = 4; // Draws "bar lines" on widget
	
	// Add GTK events to this widget
	add_events( Gdk::BUTTON_PRESS_MASK | Gdk::POINTER_MOTION_MASK | Gdk::BUTTON_RELEASE_MASK | Gdk::SCROLL_MASK);
	
	set_size_request(100,50);
	
	signal_button_press_event().connect( sigc::mem_fun( *this, &AutomationWidget::onMouseClick ) );
	signal_motion_notify_event().connect( sigc::mem_fun( *this, &AutomationWidget::onMouseMove ) );
	
	signal_scroll_event().connect( sigc::mem_fun( *this, &AutomationWidget::onScrollEvent ) );
	
	Glib::signal_timeout().connect(sigc::mem_fun(*this, &AutomationWidget::timer_callback), 20);
}

AutomationWidget::~AutomationWidget()
{
}

void AutomationWidget::setNumberOfBars(int setNumberOfBars)
{
	numberOfBars = setNumberOfBars;
}

int AutomationWidget::timer_callback ()
{
	time = time + 0.01 ;
	
	if(time > 1.0)
		time = 0;
		
	update_time(time);
	
	return 1;
}

bool AutomationWidget::onMouseMove (GdkEventMotion *event)
{
	#ifdef DEBUG_AUTOMATIONWIDGET
	//std::cout << "Mouse move:  X:" << event->x << "   Y: " << event-> y << std::endl;
	#endif
	mouseX = event->x;
	mouseY = event->y;
	return true;
}

bool AutomationWidget::onScrollEvent(GdkEventScroll *event)
{
	float value;
	
	// assign value a number according to scroll direction
	if (event->direction != 1) 
		value = 0.1;
	else
		value = -0.1;
	
	verticals.at(0) +=  value;						// first point
	verticals.at( verticals.size() -1 ) += value;	// last point
	
	// clip values
	if ( verticals.at(0) > 1) { verticals.at(0) = 1; }
	if ( verticals.at(0) < 0.000001){ verticals.at(0) =   0; }
	if ( verticals.at( verticals.size() -1 ) < 0.0) { verticals.at( verticals.size() -1 ) = 0; }
	if ( verticals.at( verticals.size() -1 ) > 1.0) { verticals.at( verticals.size() -1 ) = 1; }
	
	redraw();
	
	return 0;
}


float AutomationWidget::getValue()
{
	// takes "time" a float for % across the screen, and
	// uses that X position to get the Y co-ord at that pos to return that
	
	
	int xIndex = 0;
	
	//------------------ Page 1 ---- ------------------------------------------
	
	//######################## check this loop, xIndex should be going up.#####
	
	
	/*
	for (int i = 0; time < horizontals.at(i); i++)
	{
		std::cout << "T: " << time << "\t hori@"<<i<<": "<<horizontals.at(i+1)<<std::endl;
	}*/
	
	while (xIndex > horizontals.at(xIndex))
		xIndex++;
	
	// xIndex		is the next point
	// xIndex - 1	is the previous
	std::cout << "xIndex = " << xIndex << std::endl;
	
	//							Playhead			x1
	float timeFromOrigin = ( time     -     horizontals.at(xIndex));
	
	//							x2							x1
	float distFromOrigin = horizontals.at(xIndex+1) - horizontals.at(xIndex);
	
	//	create %age along the way marker
	float percentAlongPoints = timeFromOrigin / distFromOrigin;
	
	//	make percentBetweenPoints:     float         - (int)of float
	float percentBetweenPoints = percentAlongPoints - (int)percentAlongPoints;
	
	std::cout << "% between points: " << percentBetweenPoints << std::endl;
	
	//------------------ Page 1 DONE ------------------------------------------
	
	//------------------ Page 2 -----------------------------------------------
	//    difference In height between points
	float diffInHeight = ( verticals.at(xIndex+1)     -  verticals.at(xIndex));
	
	//    amount of Y to add for playhead
	float yAmountToAddAtPlayhead = diffInHeight * percentBetweenPoints;
	//------------------ Page 2 DONE ------------------------------------------
	
	//------------------ Page 3 -----------------------------------------------
	
	// add on whatever value the smaller of Y1 or Y2 is
	float returnValue = yAmountToAddAtPlayhead + verticals.at(xIndex);
	
	// if line is going up, invert the value:
	if ( verticals.at(xIndex) < verticals.at(xIndex+1))
		returnValue = 1 - returnValue;
	
	// return absolute value of this
	return returnValue;
	
	//------------------ Page 3 DONE-------------------------------------------
}

void AutomationWidget::update_time(float incomingTime)
{
	time = incomingTime;
	
	if ( time > 1) { time = 1; }
	if ( time < 0) { time = 0; }
	
	//std::cout << "update_time(): new time" << time << std::endl;
	
	// playheadPosition is the num of pixels across
	playheadPosition = time*width;
	
	std::cout << "Value: " << getValue() << std::endl;
	
	redraw();
}

void AutomationWidget::redraw()
{
	// force our program to redraw the entire widget.
	Glib::RefPtr<Gdk::Window> win = get_window();
	if (win)
	{
	    Gdk::Rectangle r(0, 0, get_allocation().get_width(),get_allocation().get_height());
	    win->invalidate_rect(r, false);
	}
}

bool AutomationWidget::onMouseClick (GdkEventButton *event)
{
	// sorts out which mouse button was used, and calls the appropriate func.
	std::cout << "Mouse event->type, event->button: " << event->type << "  " << event->button << std::endl;
	
	if (event->type == 4 && event->button == 1)
	{ //     buttonDown          left-mouse button
		onMouseButton1Down(event);
	}
	if (event->type == 4 && event->button == 3)
	{ //     buttonDown         right-mouse button
		onMouseButton3Down(event);
	}
	
	redraw();
	
	return true;
}


bool AutomationWidget::onMouseButton3Down( GdkEventButton *event )
{
	// mouseX are "pixel-positions", divide by width to get 1 -> 0 range
	float remPointX = mouseX/width;
	
	for (int i = 0; i < horizontals.size();i++)
	{
		
		// Only remove point if its close to the mouse position.
		if ( remPointX - 0.01  < horizontals.at(i) && horizontals.at(i) < remPointX + 0.01)
		{
			// Only remove points if theyre NOT the first or last one
			if( remPointX > 0.05 && remPointX < 0.95 )
			{
				horizontals.erase(horizontals.begin()  + i);
				verticals.erase( verticals.begin()  + i);
			}
		}
	}
	
	redraw();
	
	return 0;
}


bool AutomationWidget::onMouseButton1Down( GdkEventButton *event ) 
{
	// mouseX & mouseY are "pixel-positions" they need to be converted to points.
	float pushPointX = mouseX / width;
	float pushPointY = 1 - (mouseY / height);	// Y needs to be inverted
	
	int insertIndex = 0;
	
	for ( int i = 0 ; pushPointX >= horizontals.at(i); i++)
	{
		insertIndex = i;
		//std::cout << " InsertIndex: " << insertIndex<< " X: " << pushPointX << " Y: " << pushPointY << std::endl;
	}
	
	horizontals.insert(horizontals.begin() + insertIndex + 1 , pushPointX);
	verticals.insert(verticals.begin() + insertIndex + 1 , pushPointY);
	
	
	redraw();		// doesnt "redraw" screen, only asks GTKmm to do it on next refresh.
	
	return true;
}

void AutomationWidget::set_points(std::vector<int> pointsIn)
{
	#ifdef DEBUG_AUTOMATIONWIDGET
	std::cout << "AutomationWidget::set_points()" << std::endl;
	#endif
	
	// This function "sets" the points data from an external place to
	// this widget Instance.
	//points = pointsIn;
}

bool AutomationWidget::on_expose_event(GdkEventExpose* event)
{
	#ifdef DEBUG_AUTOMATIONWIDGET
	std::cout << "In on_expose_event: automationWidget" << std::endl;
	#endif
	
	// This is where we draw on the window
	Glib::RefPtr<Gdk::Window> window = get_window();
	
	// If this window exists, draw to it.
	if(window)
	{
		Gtk::Allocation allocation = get_allocation();
		width = allocation.get_width();
		height = allocation.get_height();
		
		// coordinates for the center of the window
		int xc, yc;
		xc = width / 2;
		yc = height / 2;
		
		// Create a  Cairo context to draw on.
		Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
		
		// set line Width
		cr -> set_line_width(1.9);
		cr -> set_line_join ( Cairo::LINE_JOIN_ROUND);
		cr -> set_line_cap  ( Cairo::LINE_CAP_ROUND );
		
		
		// clip to the area indicated by the expose event so that we only redraw
		// the portion of the window that needs to be redrawn
		cr -> rectangle(event->area.x, event->area.y,
		        event->area.width, event->area.height);
		cr -> clip();
		
		cr -> set_source_rgb (0.1,0.1,0.1);
		cr -> rectangle (0,0,width,height);
		cr -> fill();
		
		// draw Grid
		int x = 0;
		while (x < width-1)
		{
			x = x + width / numberOfBars;
			cr -> move_to (x, 0);
			cr -> line_to (x , height);
			cr -> set_source_rgba (0.0,0.0,0.0,1.0);
			cr -> stroke();
		}
		
		//  Main loop for drawing each Point on the widget.
		for (int index=0; index < horizontals.size() - 1; index++) 
		{
			int drawX1 = (horizontals.at(index) * width);
			int drawY1 = (verticals.at(index) * height);
			
			int drawX2 = horizontals.at(index+1) * width;
			int drawY2 = verticals.at(index+1) * height;
			
			//std::cout << std::endl << "DrwPnts: " << horizontals.at(index) << " " << verticals.at(index) << "\t";
			
			// Invert heights, so 0 = bottom, 127 = top
			drawY1 = height - drawY1;
			drawY2 = height - drawY2;
			
			// draw points
			cr -> set_line_width(5.3);
			cr -> move_to(drawX1,drawY1);
			cr -> line_to(drawX1,drawY1);
			cr -> set_source_rgba (0.3,0.3,0.3,1.0);
			cr -> stroke();
			
			// draw lines between points
			cr -> set_line_width(1.9);
			cr -> set_source_rgba (0.0,1.0,0.0,0.8);
			cr -> move_to(drawX1,drawY1);
			cr -> line_to(drawX2,drawY2);
			cr -> stroke();
			
			// Show point Co-ords?
			cr -> move_to (drawX1-30,  drawY1 );
			cr -> set_source_rgb (1.0,0.0,0.0);
			cr -> show_text  ( convertFloatToStr( (int)(horizontals.at(index) * 100 ) ) );
			cr -> stroke();
			
			cr -> move_to (drawX1+10,drawY1 );
			cr -> set_source_rgb (1.0,1.0,0.0);
			cr -> show_text  ( convertFloatToStr( (int)(verticals.at(index) *100 ) ) );
			cr -> stroke();
			
		}
		
		
		cr -> set_source_rgb(1.0,0.0,0.0);
		cr -> move_to (time * width , 0);
		cr -> line_to (time * width , height);
		cr -> stroke();
	} 
	return true;
} // on_expose_event()
