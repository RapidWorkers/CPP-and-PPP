//Include code fragments of Chapter 16
//This file is solution for all Drill Problems.

#include <iostream>
#include "GUI.h"

using namespace Graph_lib;

struct Lines_window : Window {
	Lines_window(Point xy, int w, int h, const string& title);
	Open_polyline lines;
	Menu color_menu;
	Menu style_menu;

	//callback function
	static void cb_red(Address, Address);
	static void cb_blue(Address, Address);
	static void cb_black(Address, Address);

	//for color menu
	void red_pressed() { changeColor(Color::red); };
	void blue_pressed() { changeColor(Color::blue); };
	void black_pressed() { changeColor(Color::black); };
	void menu_color_pressed() { menu_color_button.hide(); color_menu.show(); };
	void changeColor(Color c) { lines.set_color(c); this->redraw(); };

	//for style menu
	void dash_pressed() { changeStyle(Line_style::dash); };
	void dot_pressed() { changeStyle(Line_style::dot); };
	void dashdotdot_pressed() { changeStyle(Line_style::dashdotdot); };
	void dashdot_pressed() { changeStyle(Line_style::dashdot); };
	void solid_pressed() { changeStyle(Line_style::solid); };
	void menu_style_pressed() { menu_style_button.hide(); style_menu.show(); };
	void changeStyle(Line_style s) { lines.set_style(s); this->redraw(); };

private:
	Button next_button;
	Button quit_button;
	Button menu_color_button;
	Button menu_style_button;
	In_box next_x;
	In_box next_y;
	Out_box xy_out;

	void next();
	void quit() { hide(); };
};

Lines_window::Lines_window(Point xy, int w, int h, const string & title)
	: Window(xy, w, h, title),
	next_button{ Point{x_max() - 150,0}, 70, 20, "Next point",
					[](Address, Address pw) {reference_to<Lines_window>(pw).next(); } },
	quit_button{ Point{x_max() - 70, 0}, 70, 20, "Quit",
					[](Address, Address pw) {reference_to<Lines_window>(pw).quit(); } },
	menu_color_button{ Point{x_max() - 70, 40}, 70, 20, "color menu",
					[](Address, Address pw) {reference_to<Lines_window>(pw).menu_color_pressed(); } },
	menu_style_button{ Point{x_max() - 70, 110}, 70, 20, "style menu",
					[](Address, Address pw) {reference_to<Lines_window>(pw).menu_style_pressed(); } },
	next_x{ Point{x_max() - 310, 0}, 50, 20, "next x:" },
	next_y{ Point{x_max() - 210, 0}, 50, 20, "next y:" },
	xy_out{ Point{100, 0}, 100, 20, "current (x,y)" },
	color_menu{ Point{x_max() - 70, 40}, 70, 20, Menu::vertical, "color" },
	style_menu{ Point{x_max() - 70, 110}, 70, 20, Menu::vertical, "style" }
{

	color_menu.attach(new Button{ Point{0, 0}, 0, 0, "red", cb_red });
	color_menu.attach(new Button{ Point{0, 0}, 0, 0, "blue", cb_blue });
	color_menu.attach(new Button{ Point{0, 0}, 0, 0, "black", cb_black });
	attach(color_menu);

	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "solid", 
		[](Address, Address pw) {reference_to<Lines_window>(pw).solid_pressed(); } });
	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dot", 
		[](Address, Address pw) {reference_to<Lines_window>(pw).dot_pressed(); } });
	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dash", 
		[](Address, Address pw) {reference_to<Lines_window>(pw).dash_pressed(); } });
	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dashdot", 
		[](Address, Address pw) {reference_to<Lines_window>(pw).dashdot_pressed(); } });
	style_menu.attach(new Button{ Point{0, 0}, 0, 0, "dashdotdot", 
		[](Address, Address pw) {reference_to<Lines_window>(pw).dashdotdot_pressed(); } });
	attach(style_menu);

	attach(next_button);
	attach(quit_button);
	attach(next_x);
	attach(next_y);
	attach(xy_out);
	attach(lines);
	attach(menu_color_button);
	attach(menu_style_button);

	//hide menu at start
	color_menu.hide();
	style_menu.hide();
}

void Lines_window::next() {
	int x = next_x.get_int();
	int y = next_y.get_int();
	lines.add(Point{ x, y });

	ostringstream ss;
	ss << '(' << x << ',' << y << ')';
	xy_out.put(ss.str());

	this->redraw();
}

//these callback functions can be changed into lambda function
//these definitions are left for practicing
void Lines_window::cb_red(Address, Address pw){
	reference_to<Lines_window>(pw).red_pressed();
}

void Lines_window::cb_blue(Address, Address pw) {
	reference_to<Lines_window>(pw).blue_pressed();
}

void Lines_window::cb_black(Address, Address pw) {
	reference_to<Lines_window>(pw).black_pressed();
}

int main(int argc, char *argv[]) {
	
	try {
		Lines_window win{ Point{100, 100}, 600, 400, "lines" };
		return gui_main();
	}
	catch (exception &e) {
		cerr << "Exception: " << e.what() << '\n';
		return 1;
	}
	catch (...) {
		cerr << "Exception that I don't know\n";
		return 2;
	}

}