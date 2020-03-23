#pragma once

#include <QtWidgets/QMainWindow>
#include <qfiledialog.h>
#include <qmessagebox.h>
#include "ui_AReMu_GBA.h"
#include "CPUEngine/interpreter/arm7tdmi_interpreter.h"

class AReMu_GBA : public QMainWindow
{
	Q_OBJECT

public:
	AReMu_GBA(QWidget *parent = Q_NULLPTR);

private:
	Ui::AReMu_GBAClass ui;
	QString romPath;
	bool isInit = false;
	arm7tdmi_interpreter *CPU;

	void initCPU();

public slots:
	void OpenROM();
	void startGBA();
};
