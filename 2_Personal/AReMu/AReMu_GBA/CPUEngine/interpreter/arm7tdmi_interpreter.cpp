#include "arm7tdmi_interpreter.h"

void arm7tdmi_interpreter::allocateMEM(unsigned int mapAddr, size_t memSize, ARM7_MEM_SIZE sz_unit)
{
	if (maxMapCnt <= currMapCnt) return; //no allocate when exceeding region count

	switch (sz_unit) {
	case MEM_BYTE:
		break;
	case MEM_KBYTE:
		memSize = memSize * 1024;
		break;
	case MEM_MBYTE:
		memSize = memSize * 1024 * 1024;
		break;
	default:
		return;
		break;
	}

	memoryMAP[currMapCnt].mem = new BYTE[memSize];
	memoryMAP[currMapCnt].memSize = memSize;
	memoryMAP[currMapCnt++].mapAddr = mapAddr;

	//zeroing memory
	memset(memoryMAP[currMapCnt - 1].mem, 0x00, memSize);

	//if (MEM == nullptr) exit(1);
}

void arm7tdmi_interpreter::changeRegisterSet(int procMode)
{
	switch (procMode) {
	case ARM_USER:
		currentREG = 0;
		break;
	case ARM_FIQ:
		currentREG = 1;
		break;
	case ARM_IRQ:
		currentREG = 3;
		break;
	case ARM_SVC:
		currentREG = 2;
		break;
	case ARM_ABT:
		currentREG = 5;
		break;
	case ARM_UND:
		currentREG = 4;
		break;
	case ARM_SYS:
		currentREG = 0;
		break;
	}
}

inline bool arm7tdmi_interpreter::checkCond(char cond, bool C, bool N, bool Z, bool V)
{
	switch (cond) {
	case 0b0000:
		return Z;
		break;
	case 0b0001:
		return !Z;
		break;
	case 0b0010:
		return C;
		break;
	case 0b0011:
		return !C;
		break;
	case 0b0100:
		return N;
		break;
	case 0b0101:
		return !N;
		break;
	case 0b0110:
		return V;
		break;
	case 0b0111:
		return !V;
		break;
	case 0b1000:
		return (C && !Z);
		break;
	case 0b1001:
		return (!C || Z);
		break;
	case 0b1010:
		return (N == V);
		break;
	case 0b1011:
		return (N != V);
		break;
	case 0b1100:
		return (!Z && N == V);
		break;
	case 0b1101:
		return (Z || N != V);
		break;
	case 0b1110://AL
		return true;
		break;
	default://Undefined condition code
		return false;
		break;
	}
}

void arm7tdmi_interpreter::interpret()
{
	//check ticks to limit the performance to target clock
	if (currentTick >= targetCLK) return;
	while (true) {
		/*
			Since, there're two operating modes
				ARM mode (32bits instruction)
				Thumb mode (16bits instruction)
			we have to current processor's mode
		*/

		bool isThumb = isOnThumb();
		ARM7_MODE procMode = getCurrentMode();
		changeRegisterSet(procMode);

		if (!isThumb) {
			//ARM Mode interpreter

			//read instruction from memory
			unsigned int instr = readMem(r[15]);
			r[15] += 4;//increase PC by 4
			
			//Comparison flags
			bool N = cpsr >> 31;
			bool Z = (cpsr << 1) >> 31;
			bool C = (cpsr << 2) >> 31;
			bool V = (cpsr << 3) >> 31;

			//Instruction parameters
			char cond = instr >> 28;
			int preOpCode = (instr << 4) >> 29;
			int OpCode = (instr << 7) >> 28;
			//int OpCode1 = (instr << 8) >> 28; //coprocessor

			bool Link = (instr << 7) >> 31;
			int bAddr = ((int)(instr << 8) >> 6) + r[15] + 4;

			char Rn, Rd, Rs, Rm;
			char shamt, shift;
			char rotate;
			char Mask, SBO;
			int immediate;
			bool regList[16];
			int swiNum;

			bool S, R;
			bool P, U, B, W, L;

			//Check condition field
			bool run = checkCond(cond, C, N, Z, V);

			if (!run) {
				currentTick++;
				continue;
			}

			//decode opcode
			switch (preOpCode) {
			case 0b000:
				switch (OpCode) {
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
				case 5:
				case 6:
				case 7:
				case 8:
				case 9:
				case 10:
				case 11:
				case 12:
				case 13:
				case 14:
				case 15:
				case 16:
					break;
				}
				break;
			case 0b001:
				break;
			case 0b010:
				break;
			case 0b011:
				break;
			case 0b100:
				break;
			case 0b101://branch
				if (Link) *REG[currentREG][14] = r[15];
				r[15] = bAddr;
				currentTick += 2;//branch takes 2 cycle
				break;
			case 0b110:
				break;
			case 0b111:
				break;
			default:
				break;
			}

		}
		else {
			//Thumb Mode interpreter

			//read instruction from memory
			unsigned int instr = readMem16(r[15]);
			r[15] += 2;//increase PC by 2
		}
	}
}

arm7tdmi_interpreter::arm7tdmi_interpreter(int CLK, size_t maxMapCnt, int accuracy) : targetCLK{ CLK }, maxMapCnt{ maxMapCnt }, clkAccuracy{ accuracy } {
	//setting up register banks
	//System and User
	for (int i = 0; i < 16; i++) {
		REG[0][i] = r + i;
	}

	//FIQ
	for (int i = 0; i < 16; i++) {
		if (i < 8) REG[1][i] = r + i;
		else if (i < 15) REG[1][i] = r_FIQ + i - 8;
		else REG[1][i] = r + 15;
	}

	//Others
	for (int i = 0; i < 16; i++) {
		if (i < 13) {
			REG[2][i] = r + i;
			REG[3][i] = r + i;
			REG[4][i] = r + i;
			REG[5][i] = r + i;
		}
		else if (i < 15) {
			REG[2][i] = r_SVC + i - 13;
			REG[3][i] = r_ABT + i - 13;
			REG[4][i] = r_IRQ + i - 13;
			REG[5][i] = r_UND + i - 13;
		}
		else {
			REG[2][i] = r + 15;
			REG[3][i] = r + 15;
			REG[4][i] = r + 15;
			REG[5][i] = r + 15;
		}
	}

	//allocating for memory map
	memoryMAP = new MEM_MAP[maxMapCnt];

}

bool arm7tdmi_interpreter::loadToMem(string filepath, unsigned int memAddr)
{
	char buffer[1024];

	//find memory map by address
	MEM_MAP *targetMap = nullptr;
	for (size_t i = 0; i < this->currMapCnt; i++) {
		if (memAddr >= memoryMAP[i].mapAddr && memAddr <= memoryMAP[i].mapAddr + memoryMAP[i].memSize) {
			targetMap = memoryMAP + i;
			break;
		}
	}

	if (targetMap == nullptr) return false;

	std::filesystem::path p = filepath;
	if (memAddr + std::filesystem::file_size(p) > targetMap->mapAddr + targetMap->memSize) return false;

	ifstream openFile(p, ios::binary);
	if (!openFile.is_open()) return false;

	size_t pos = 0;

	while (true) {
		size_t rd_sz;
		openFile.read(buffer, 1024);
		if (openFile.eof()) break;
		rd_sz = openFile.gcount();
		memcpy(targetMap->mem + pos, buffer, rd_sz);
		pos += rd_sz;
	}

	return true;
}

unsigned int arm7tdmi_interpreter::readMem(unsigned int rdAddr)
{
	//find memory map by address
	MEM_MAP *targetMap = nullptr;
	for (size_t i = 0; i < this->currMapCnt; i++) {
		if (rdAddr >= memoryMAP[i].mapAddr && rdAddr <= memoryMAP[i].mapAddr + memoryMAP[i].memSize) {
			targetMap = memoryMAP + i;
			break;
		}
	}

	if (targetMap == nullptr) return 0;//Just return 0 when error, there's no way to handle this
	if (rdAddr + 4 > targetMap->mapAddr + targetMap->memSize) return 0;//Should not read when exceeding allocated area

	int* readPtr = (int*)(&targetMap->mem[rdAddr - targetMap->mapAddr]);

	return *readPtr;
}

void arm7tdmi_interpreter::writeMem(unsigned int wrAddr, unsigned int wrData)
{
	//find memory map by address
	MEM_MAP *targetMap = nullptr;
	for (size_t i = 0; i < this->currMapCnt; i++) {
		if (wrAddr >= memoryMAP[i].mapAddr && wrAddr <= memoryMAP[i].mapAddr + memoryMAP[i].memSize) {
			targetMap = memoryMAP + i;
			break;
		}
	}

	if (targetMap == nullptr) return;//Just return 0 when error, there's no way to handle this
	if (wrAddr + 4 > targetMap->mapAddr + targetMap->memSize) return;//Should not write when exceeding allocated area
	*(int*)(&targetMap->mem[wrAddr - targetMap->mapAddr]) = wrData;

	return;
}

void arm7tdmi_interpreter::writeMem16(unsigned int wrAddr, unsigned int wrData)
{
}

void arm7tdmi_interpreter::writeMem8(unsigned int wrAddr, unsigned int wrData)
{
}

void arm7tdmi_interpreter::startCPU(unsigned int entryPoint)
{
	//set pc
	r[15] = entryPoint;
	interpret();

}

void arm7tdmi_interpreter::pauseCPU()
{
}

void arm7tdmi_interpreter::resetCPU()
{
}
