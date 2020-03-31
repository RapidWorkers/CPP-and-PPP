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

	MEM_MAP tmp_mmap;

	tmp_mmap.mem = new BYTE[memSize];
	tmp_mmap.memSize = memSize;
	tmp_mmap.mapAddr = mapAddr;

	memoryMAP.push_back(tmp_mmap);

	//zeroing memory
	memset(tmp_mmap.mem, 0x00, memSize);

	//if (MEM == nullptr) exit(1);
}

bool arm7tdmi_interpreter::retriveMAP(unsigned int addr, MEM_MAP*& map)
{
	//find memory map by address
	map = nullptr;
	for (size_t i = 0; i < memoryMAP.size(); i++) {
		if (addr >= memoryMAP[i].mapAddr && addr <= memoryMAP[i].mapAddr + memoryMAP[i].memSize) {
			map = &memoryMAP[i];
			return true;
		}
	}

	return false;
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
	while (true) {
		//check ticks to limit the performance to target clock
		if (currentTick >= targetCLK) break;
		//check pause
		if (!processorStarted) break;

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

			//new flags
			bool newC = C, newN = 0, newZ = 0, newV = V;

			//Instruction parameters
			char cond = instr >> 28;
			int preOpCode = (instr << 4) >> 29;
			int OpCode = (instr << 7) >> 28;
			//int OpCode1 = (instr << 8) >> 28; //coprocessor

			char Rn, Rd, Rs, Rm;
			//Rn = (instr << 12) >> 28;
			//Rd = (instr << 16) >> 28;
			//Rs = (instr << 20) >> 28;
			//Rm = instr & 0b1111;
			char shamt, shift;
			int shift_operand;

			//shamt = (instr >> 7) & 0b11111;
			//shift = (instr >> 5) & 0b11;

			char rotate;
			//rotate = (instr << 20) >> 28;
			char Mask, SBO;
			//Mask = (instr << 12) >> 28;
			//SBO = (instr << 16) >> 28;
			int imm_DP, imm_LDST;
			//imm_DP = instr & 0xFF;
			//imm_LDST = instr & 0xFFF;
			int regList;
			//regList = instr & 0xFFFF;
			int swiNum;
			//swiNum = instr & 0x00FFFFFF;

			bool S, R;
			S = (instr << 11) >> 31;

			bool P, U, B, W, L;

			//for comparison instructions (CMP, TST, ...)
			bool isCmp = false;
			int cmpVar;

			//for calculating carry and overflow
			unsigned long long tmpVar;

			//Check condition field
			bool run = checkCond(cond, C, N, Z, V);

			currentTick++;

			if (!run) {
				continue;
			}

			//decode opcode
			switch (preOpCode) {
			case 0b000://data processing (shift values in register)
				Rn = (instr << 12) >> 28;
				Rd = (instr << 16) >> 28;
				Rs = (instr << 20) >> 28;
				Rm = instr & 0b1111;
				shift = (instr >> 4) & 0b111;
				shamt = (instr >> 7) & 0b11111;
				//LSL = 00, LSR 01 ASR 10 RR 11
				switch (shift) {
				case 0b000:
					shift_operand = *(REG[currentREG][Rn]) << shamt;
					newC = (*(REG[currentREG][Rn]) << (shamt - 1)) >> 31;
					break;
				case 0b010:
					shift_operand = *(REG[currentREG][Rn]) >> shamt;
					break;
				case 0b100:
					shift_operand = ((int)*(REG[currentREG][Rn])) >> shamt;
					break;
				case 0b110:
					shift_operand = _rotr(*(REG[currentREG][Rn]), shamt);
					break;
				case 0b001:
					shift_operand = *(REG[currentREG][Rn]) << *(REG[currentREG][Rm]);
					newC = (*(REG[currentREG][Rn]) << (*(REG[currentREG][Rm]) - 1)) >> 31;
					break;
				case 0b011:
					shift_operand = *(REG[currentREG][Rn]) >> *(REG[currentREG][Rm]);
					break;
				case 0b101:
					shift_operand = _rotr(*(REG[currentREG][Rn]), *(REG[currentREG][Rm]));//instrinsic, need to fixed later
					break;
				case 0b111:
					shift_operand = *(REG[currentREG][Rn]) >> *(REG[currentREG][Rm]);
					break;
				}

				switch (OpCode) {
				case 0://AND
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) & shift_operand;
					break;
				case 1://EOR
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) ^ shift_operand;
					break;
				case 2://SUB
					tmpVar = *(REG[currentREG][Rn]) - shift_operand;
					newC = tmpVar >> 32;
					newV = ((*(REG[currentREG][Rn]) > 0) && (shift_operand < 0) && (tmpVar < 0)) || (*(REG[currentREG][Rn]) < 0) && (shift_operand > 0) && (tmpVar > 0);
					*(REG[currentREG][Rd]) = tmpVar;
					break;
				case 3://RSB
					tmpVar = shift_operand  - *(REG[currentREG][Rn]);
					newC = tmpVar >> 32;
					newV = ((*(REG[currentREG][Rn]) < 0) && (shift_operand > 0) && (tmpVar < 0)) || (*(REG[currentREG][Rn]) > 0) && (shift_operand < 0) && (tmpVar > 0);
					*(REG[currentREG][Rd]) = tmpVar;
					break;
				case 4://ADD
					tmpVar = shift_operand + *(REG[currentREG][Rn]);
					newC = tmpVar >> 32;
					newV = ((*(REG[currentREG][Rn]) > 0) && (shift_operand > 0) && (tmpVar < 0)) || (*(REG[currentREG][Rn]) < 0) && (shift_operand < 0) && (tmpVar > 0);
					*(REG[currentREG][Rd]) = tmpVar;
					break;
				case 5://ADC
					tmpVar = shift_operand + *(REG[currentREG][Rn]) + C;
					newC = tmpVar >> 32;
					//newV = ??
					*(REG[currentREG][Rd]) = tmpVar;
					break;
				case 6://SBC
					tmpVar = *(REG[currentREG][Rn]) - shift_operand + C;
					newC = tmpVar >> 32;
					//newV = ??
					*(REG[currentREG][Rd]) = tmpVar;
					break;
				case 7://RSC
					tmpVar = shift_operand  - *(REG[currentREG][Rn]) + C;
					newC = tmpVar >> 32;
					//newV = ??
					*(REG[currentREG][Rd]) = tmpVar;
					break;
				case 8://TST
					cmpVar = *(REG[currentREG][Rn]) & shift_operand;
					isCmp = true;
					break;
				case 9://TEQ
					cmpVar = *(REG[currentREG][Rn]) ^ shift_operand;
					isCmp = true;
					break;
				case 10://CMP
					tmpVar = *(REG[currentREG][Rn]) - shift_operand;
					newC = tmpVar >> 32;
					newV = ((*(REG[currentREG][Rn]) > 0) && (shift_operand < 0) && (tmpVar < 0)) || (*(REG[currentREG][Rn]) < 0) && (shift_operand > 0) && (tmpVar > 0);
					cmpVar = tmpVar;
					isCmp = true;
					break;
				case 11://CMN
					tmpVar = *(REG[currentREG][Rn]) + shift_operand;
					newC = tmpVar >> 32;
					newV = ((*(REG[currentREG][Rn]) > 0) && (shift_operand > 0) && (tmpVar < 0)) || (*(REG[currentREG][Rn]) < 0) && (shift_operand < 0) && (tmpVar > 0);
					cmpVar = tmpVar;
					isCmp = true;
					break;
				case 12://ORR
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) | ~shift_operand;
					break;
				case 13://MOV
					*(REG[currentREG][Rd]) = shift_operand;
					break;
				case 14://BIC
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) & ~shift_operand;
					break;
				case 15://MVN
					*(REG[currentREG][Rd]) = ~shift_operand;
					break;
				}
				
				if(isCmp) {//comparison instr
					if (cmpVar) == 0) newZ = 1;
					if (cmpVar) >> 31) newN = 1;

					//update cpsr
					cpsr = cpsr & 0x0FFFFFFF + (newN << 31) + (newZ << 30) + (newC << 29) + (newV << 28);
				}
				else if (S) {//XXXS instructions
					if (*(REG[currentREG][Rd]) == 0) newZ = 1;
					if (*(REG[currentREG][Rd]) >> 31) newN = 1;
					
					//update cpsr
					cpsr = cpsr & 0x0FFFFFFF + (newN << 31) + (newZ << 30) + (newC << 29) + (newV << 28);
				}

				break;

			case 0b001://data processing immediate (shift immediate)
				Rn = (instr << 12) >> 28;
				Rd = (instr << 16) >> 28;
				imm_DP = instr & 0xFF;
				rotate = (instr << 20) >> 28;
				shift_operand = _rotr(imm_DP, rotate * 2);
				switch (OpCode) {
				case 0://AND
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) & shift_operand;
					break;
				case 1://EOR
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) ^ shift_operand;
					break;
				case 2://SUB
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) - shift_operand;
					break;
				case 3://RSB
					*(REG[currentREG][Rd]) = shift_operand - *(REG[currentREG][Rn]);
					break;
				case 4://ADD
					*(REG[currentREG][Rd]) = shift_operand + *(REG[currentREG][Rn]);
					break;
				case 5://ADC
					*(REG[currentREG][Rd]) = shift_operand + *(REG[currentREG][Rn]) + C;
					break;
				case 6://SBC
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) - shift_operand + C;
					break;
				case 7://RSC
					*(REG[currentREG][Rd]) = shift_operand - *(REG[currentREG][Rn]) + C;
					break;
				case 8: case 9: case 10: case 11://Not defined
					break;
				case 12://ORR
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) | ~shift_operand;
					break;
				case 13://MOV
					*(REG[currentREG][Rd]) = shift_operand;
					break;
				case 14://BIC
					*(REG[currentREG][Rd]) = *(REG[currentREG][Rn]) & ~shift_operand;
					break;
				case 15://MVN
					*(REG[currentREG][Rd]) = ~shift_operand;
					break;
				}
				break;
			case 0b010:
				break;
			case 0b011:
				break;
			case 0b100:
				break;
			case 0b101://branch
				if ((instr << 7) >> 31) *REG[currentREG][14] = r[15];//If Link
				r[15] = ((int)(instr << 8) >> 6) + r[15] + 4;//Change PC
				currentTick += 1;//branch takes 1 more cycle
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
	
	processorStarted = false;
}

int arm7tdmi_interpreter::cpuThreadHandler()
{
	while (processorStarted) {
		interpret();
		resetTick();
	}

	return 0;
}

arm7tdmi_interpreter::arm7tdmi_interpreter(int CLK, int accuracy) : targetCLK{ CLK }, clkAccuracy{ accuracy } {
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
}

arm7tdmi_interpreter::~arm7tdmi_interpreter()
{
	//TODO: destructor
	//TODO: deallocate dynamic area
}

bool arm7tdmi_interpreter::loadToMem(string filepath, unsigned int memAddr)
{
	char buffer[1024];

	//find memory map by address
	MEM_MAP *targetMap = nullptr;
	if (!retriveMAP(memAddr, targetMap)) return false;

	//check if exceeding size
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
	if (!retriveMAP(rdAddr, targetMap)) return false;

	if (targetMap == nullptr) return 0;//Just return 0 when error, there's no way to handle this
	if (rdAddr + 4 > targetMap->mapAddr + targetMap->memSize) return 0;//Should not read when exceeding allocated area

	int* readPtr = (int*)(&targetMap->mem[rdAddr - targetMap->mapAddr]);

	return *readPtr;
}

void arm7tdmi_interpreter::writeMem(unsigned int wrAddr, unsigned int wrData)
{
	//find memory map by address
	MEM_MAP *targetMap = nullptr;
	if (!retriveMAP(wrAddr, targetMap)) return;

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

	if (processorStarted) return;
	//set pc
	r[15] = entryPoint;

	processorStarted = true;
	thread cpuThread([this]() {cpuThreadHandler(); });

	//launch background
	cpuThread.detach();
}

void arm7tdmi_interpreter::pauseCPU()
{
}

void arm7tdmi_interpreter::resetCPU()
{
}
