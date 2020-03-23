#include "AReMu_GBA.h"

AReMu_GBA::AReMu_GBA(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.actionOpen_ROM_O, SIGNAL(triggered()), this, SLOT(OpenROM()));
	connect(ui.actionRUN_R, SIGNAL(triggered()), this, SLOT(startGBA()));
}

void AReMu_GBA::initCPU()
{
	if (isInit) return;//no need to initialize

	ui.logBox->appendPlainText("Creating interpreter instance");
	qApp->processEvents();
	CPU = new arm7tdmi_interpreter{};
	ui.logBox->appendPlainText("Allocating BIOS Space");
	qApp->processEvents();
	CPU->allocateMEM(0x00000000, 16, CPU->MEM_KBYTE);
	ui.logBox->appendPlainText("Loading BIOS to Memory");
	qApp->processEvents();
	CPU->loadToMem("./gba_bios.bin", 0x00000000);

	ui.logBox->appendPlainText("Allocating Essential Space (34MB)");
	qApp->processEvents();
	CPU->allocateMEM(0x02000000, 256, CPU->MEM_KBYTE);	//WRAM - Onboard
	CPU->allocateMEM(0x03000000, 32, CPU->MEM_KBYTE);	//WRAM - InChip
	CPU->allocateMEM(0x04000000, 1022, CPU->MEM_BYTE);	//IO Registers
	CPU->allocateMEM(0x05000000, 1, CPU->MEM_KBYTE);		//BG/OBJ Palette RAM
	CPU->allocateMEM(0x06000000, 96, CPU->MEM_KBYTE);	//VRAM
	CPU->allocateMEM(0x07000000, 1, CPU->MEM_KBYTE);		//OAM - OBJ Attributes
	CPU->allocateMEM(0x08000000, 32, CPU->MEM_MBYTE);	//Game Pack #1
	//CPU->allocateMEM(0x0A000000, 32, CPU->MEM_MBYTE);	//Game Pack #2
	//CPU->allocateMEM(0x0C000000, 32, CPU->MEM_MBYTE);	//Game Pack #3
	CPU->allocateMEM(0x0E000000, 64, CPU->MEM_KBYTE);	//Game Pack SRAM

	isInit = true;

}

void AReMu_GBA::startGBA()
{
	if (!isInit) {
		QMessageBox::information(this, "ROM not loaded", "Please load ROM first");
		return;
	}

	ui.logBox->appendPlainText("Setting up ROM insert flag");
	//qApp->processEvents();
	//CPU->writeMem()

	ui.logBox->appendPlainText("Starting CPU...");
	qApp->processEvents();
	CPU->startCPU();
}

void AReMu_GBA::OpenROM() {
	QString target = QFileDialog::getOpenFileName(this, "Open ROM", "./", "GBA ROMs (*.gba);;ALL files (*.*)");
	if (!target.isNull() && !target.isEmpty()) {
		initCPU();
		romPath = target;
		ui.logBox->appendPlainText("ROM Opened - Copying to MEM");
		ui.logBox->appendPlainText("Please wait....");
		qApp->processEvents();
		CPU->loadToMem(romPath.toStdString(), 0x08000000);
		ui.logBox->appendPlainText("Copying done");
		qApp->processEvents();
	}

}
