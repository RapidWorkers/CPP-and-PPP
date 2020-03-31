#pragma once

#ifndef BYTE
#define BYTE unsigned char
#endif

#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>
#include <thread>
#include <functional>

using namespace std;

struct MEM_MAP {
	BYTE *mem;
	size_t memSize;
	unsigned int mapAddr;
};

class arm7tdmi_interpreter {
private:
	enum ARM7_MODE {ARM_USER = 0b10000, ARM_FIQ, ARM_IRQ, ARM_SVC, ARM_ABT = 0b10111, ARM_UND, ARM_SYS = 0b11111};
	//for accessing registers
	unsigned int* REG[6][16];

	//general purpose registers
	unsigned int r[16] = { 0, };//System and User mode
	unsigned int r_FIQ[7] = { 0, };//Fast interrupt registers
	unsigned int r_SVC[2] = { 0, };//Supervisor
	unsigned int r_ABT[2] = { 0, };//Abort
	unsigned int r_IRQ[2] = { 0, };//IRQ
	unsigned int r_UND[2] = { 0, };//Undefined

	//current program state register
	unsigned int cpsr = 0x000000D3;//I = 1, F = 1, M = 0x13(SVC)

	//saved program state register
	unsigned int spsr[5] = { 0, };

	size_t maxMapCnt;
	size_t currMapCnt = 2;
	vector<MEM_MAP> memoryMAP;
	bool retriveMAP(unsigned int addr, MEM_MAP*& map);

	int targetCLK;//target Clock Cycle in Hz
	int currentTick = 0;
	int clkAccuracy;

	bool processorStarted = false;

	void resetTick() { currentTick = 0; };

	int currentREG = 0;
	void changeRegisterSet(int procMode);
	bool checkCond(char cond);
	ARM7_MODE getCurrentMode() { return (ARM7_MODE)(cpsr & 0b11111); }
	bool isOnThumb() { return (cpsr >> 5) & 0x01; }

	void interpret();
	int cpuThreadHandler();

public:
	enum ARM7_MEM_SIZE {MEM_BYTE, MEM_KBYTE, MEM_MBYTE};

	arm7tdmi_interpreter(int CLK = 16780000, int accuracy = 60);
	~arm7tdmi_interpreter();

	void allocateMEM(unsigned int mapAddr, size_t memSize, ARM7_MEM_SIZE sz_unit);
	bool loadToMem(string filepath, unsigned int memAddr);

	unsigned int readMem(unsigned int rdAddr);
	void writeMem(unsigned int wrAddr, unsigned int wrData);
	unsigned int readMem16(unsigned int rdAddr) { return 0x0000FFFF & readMem(rdAddr); }
	void writeMem16(unsigned int wrAddr, unsigned int wrData);
	unsigned char readMem8(unsigned int rdAddr) { return 0x000000FF & readMem(rdAddr); }
	void writeMem8(unsigned int wrAddr, unsigned int wrData);


	void startCPU(unsigned int entryPoint = 0x00000000);
	void pauseCPU();
	void resetCPU();
};