//PPP2 Chap 16 Exercise Solution
//Under progress
#include "GUI.h"
#include "std_lib_facilities.h"

using namespace Graph_lib;

class My_window : Window {
public:
	My_window(Point xy, int w, int h, const string &title);

	//static void cb_cBrd(Address, Address);

private:
	Button next_btn;
	Button quit_btn;

	//void btnPressed(Button& b){}

	void next() {};
	void quit() { this->hide(); };
};

My_window::My_window(Point xy, int w, int h, const string &title)
	: Window(xy, w, h, title),
	next_btn{ Point(x_max() - 140, 0), 70, 20, "next",
		[](Address, Address pw) {reference_to<My_window>(pw).next(); } },
	quit_btn{ Point(x_max() - 70, 0), 70, 20, "quit",
	[](Address, Address pw) {reference_to<My_window>(pw).quit(); } }
{
	attach(next_btn);
	attach(quit_btn);
	//checkerboard
	//end of checkerboard
};

//void My_window::cb_cBrd(Address, Address pw){
//}

int main(int argc, char *argv[]) {
	try {
		My_window win{ Point{100, 100 }, 600, 400, "My Window" };
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