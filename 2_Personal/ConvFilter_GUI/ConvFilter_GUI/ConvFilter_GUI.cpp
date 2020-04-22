#include "ConvFilter_GUI.h"

ConvFilter_GUI::ConvFilter_GUI(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionOpen_O, SIGNAL(triggered()), this, SLOT(openImage()));
	connect(ui.actionBlur_Box, SIGNAL(triggered()), this, SLOT(bBlur()));
	connect(ui.actionBlur_Gaussian, SIGNAL(triggered()), this, SLOT(gBlur()));
	connect(ui.actionEdgeDetect_Heavy, SIGNAL(triggered()), this, SLOT(eHeavy()));
	connect(ui.actionEdgeDetect_Light, SIGNAL(triggered()), this, SLOT(eLight()));
	connect(ui.actionEdgeDetect_Medium, SIGNAL(triggered()), this, SLOT(eMedium()));
	connect(ui.actionReset, SIGNAL(triggered()), this, SLOT(resetImg()));
	connect(ui.actionmaxPool_2x2, SIGNAL(triggered()), this, SLOT(poolImg()));
}


