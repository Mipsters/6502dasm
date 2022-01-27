#include <iostream>
#include <iomanip>


#ifdef USE_ETL
#define ETL_NO_STL
#include <etl/platform.h>
#else
#define ETL_OR_STD std
#endif

#include "Disassembler6502.h"


int main()
{
	char program[] = ""
		// tests courtesy of https://github.com/jborza
		// https://github.com/jborza/6502dasm
		// https://jborza.com/post/2021-06-08-6502-disassembler
		// 
		// brick
		"200606205106201006203b0620440660a9028531a902a200203106a908a240203106a905a280203106a907a2c0203106608630a040889130d0fb60a9058501a9f0850360a9118512a91e8513a900851660203107203007200e0720660620b80620d3064c5106206d0620800660a405c403f00ca9009100a403a9069100840560209606a000a9009114a9019110a5108514a511851560a9008511a5138510061006100610061026110610261118a51065128510e611e61160a9012416d005c6124cc506e612a9022416d005c6134cd206e61360a5121007200007e612e612c920d007200007c612c612a5131007200707e613e613c920d007200707c613c61360a5164901851660a5164902851660a602e008f005e002f00c60a503c9e0f010c603c61260a503c9fff005e603e612606060a5ffa20086ffc961f007c964f0084c4c07a908850260a902850260a900850260"
		// random
		//"a5fe8500a5fe29031869028501a5fea00091004c0006"
		// sierpinski
		//"a200a9008500a9028501201f068100e600f0034c0a06e601a401c006d0ec60a500291f8502a5004a4a4a4a4a8503a50138e9020a0a0a05032502f003a90260a90d60"
		// selfmod
		//"a91685a0a0039d0002e888d0f9c6a0a5a0d0f1a9306d07068d0706a990cd0706d0de"
	;

	const size_t programLen = strlen(program);

	Disassembler6502 disassembler;

	for (size_t i = 0; i < programLen;) {
		ETL_OR_STD::bitset<Disassembler6502::DATA_LEN> data;
		ETL_OR_STD::optional<int> argNum;
		
		do {
			char hex[3] = { program[i], program[i + 1], '\0' };
			data = strtol(hex, nullptr, 16);

			if (!argNum.has_value()) {
				printf("% 3zX:\t", disassembler.getCurrentDataOffset());
			}
			
			printf("%02lX ", data.to_ulong());
			
			disassembler.analyze(data);

			Disassembler6502::InstructionStruct instruction = *disassembler.getInstruction();

			// print when done
			if (disassembler.getInstructionStatus() == Disassembler6502::EXECUTING_INSTRUCTION) {
				std::cout 
					<< std::setfill(' ') << std::setw(3 * (2 - instruction.argumentNumber)) << "\t"
					<< instruction.instructionString.c_str() << ' ' << disassembler.to_string()->c_str() << '\n';
			}

			if (!argNum.has_value()) {
				argNum = instruction.argumentNumber;
			}
			i += 2;
		} while ((*argNum)-- > 0);
	}
}
