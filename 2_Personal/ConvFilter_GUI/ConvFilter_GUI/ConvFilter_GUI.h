#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ConvFilter_GUI.h"

class ConvFilter_GUI : public QMainWindow
{
	Q_OBJECT

public:
	ConvFilter_GUI(QWidget *parent = Q_NULLPTR);

private:
	Ui::ConvFilter_GUIClass ui;
};
