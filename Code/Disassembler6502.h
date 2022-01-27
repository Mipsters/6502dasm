#ifndef DISASSEMBLER_H
#define DISASSEMBLER_H


#ifdef USE_ETL
#define ETL_NO_STL
#include <etl/bitset.h>
#include <etl/optional.h>
#include <etl/string.h>
#else
#define ETL_OR_STD std
#include <bitset>
#include <optional>
#include <string>
#endif

class Disassembler6502
{
public:

	enum Opcode {
		ADC_INSTR,
		AND_INSTR,
		ASL_INSTR,
		BBR0_INSTR,
		BBR1_INSTR,
		BBR2_INSTR,
		BBR3_INSTR,
		BBR4_INSTR,
		BBR5_INSTR,
		BBR6_INSTR,
		BBR7_INSTR,
		BBS0_INSTR,
		BBS1_INSTR,
		BBS2_INSTR,
		BBS3_INSTR,
		BBS4_INSTR,
		BBS5_INSTR,
		BBS6_INSTR,
		BBS7_INSTR,
		BCC_INSTR,
		BCS_INSTR,
		BEQ_INSTR,
		BIT_INSTR,
		BMI_INSTR,
		BNE_INSTR,
		BPL_INSTR,
		BRA_INSTR,
		BRK_INSTR,
		BVC_INSTR,
		BVS_INSTR,
		CLC_INSTR,
		CLD_INSTR,
		CLI_INSTR,
		CLV_INSTR,
		CMP_INSTR,
		CPX_INSTR,
		CPY_INSTR,
		DEC_INSTR,
		DEX_INSTR,
		DEY_INSTR,
		EOR_INSTR,
		INC_INSTR,
		INX_INSTR,
		INY_INSTR,
		JMP_INSTR,
		JSR_INSTR,
		LDA_INSTR,
		LDX_INSTR,
		LDY_INSTR,
		LSR_INSTR,
		NOP_INSTR,
		ORA_INSTR,
		PHA_INSTR,
		PHP_INSTR,
		PHX_INSTR,
		PHY_INSTR,
		PLA_INSTR,
		PLP_INSTR,
		PLX_INSTR,
		PLY_INSTR,
		RMB0_INSTR,
		RMB1_INSTR,
		RMB2_INSTR,
		RMB3_INSTR,
		RMB4_INSTR,
		RMB5_INSTR,
		RMB6_INSTR,
		RMB7_INSTR,
		ROL_INSTR,
		ROR_INSTR,
		RTI_INSTR,
		RTS_INSTR,
		SBC_INSTR,
		SEC_INSTR,
		SED_INSTR,
		SEI_INSTR,
		SMB0_INSTR,
		SMB1_INSTR,
		SMB2_INSTR,
		SMB3_INSTR,
		SMB4_INSTR,
		SMB5_INSTR,
		SMB6_INSTR,
		SMB7_INSTR,
		STA_INSTR,
		STP_INSTR,
		STX_INSTR,
		STY_INSTR,
		STZ_INSTR,
		TAX_INSTR,
		TAY_INSTR,
		TRB_INSTR,
		TSB_INSTR,
		TSX_INSTR,
		TXA_INSTR,
		TXS_INSTR,
		TYA_INSTR,
		WAI_INSTR
	};

	enum AddressingMode {
		ABSOLUTE_AM,
		ABSOLUTE_INDEXED_INDIRECT_AM,
		ABSOLUTE_INDEXED_WITH_X_AM,
		ABSOLUTE_INDEXED_WITH_Y_AM,
		ABSOLUTE_INDIRECT_AM,
		ACCUMULATOR_AM,
		IMMEDIATE_ADDRESSING_AM,
		IMPLIED_AM,
		PROGRAM_COUNTER_RELATIVE_AM,
		STACK_AM,
		ZERO_PAGE_AM,
		ZERO_PAGE_INDEXED_INDIRECT_AM,
		ZERO_PAGE_INDEXED_WITH_X_AM,
		ZERO_PAGE_INDEXED_WITH_Y_AM,
		ZERO_PAGE_INDIRECT_AM,
		ZERO_PAGE_INDIRECT_INDEXED_WITH_Y_AM
	};

	enum InstructionStatus {
		NO_INSTRUCTION,
		AWAITING_FIRST_ARGUMENT,
		AWAITING_SECOND_ARGUMENT,
		EXECUTING_INSTRUCTION
	};

	static const size_t DATA_LEN = 8;
	static const size_t ADDR_LEN = 16;

	static const size_t MAX_OPCODE_LEN = 4;

	static const size_t MAX_INSTRUCTION_LEN =
		MAX_OPCODE_LEN +
		1 + // space character
		5 + // max addressing mode characters
		1 + // hex symbol
		4;  // max hex length

#if ETL_NOT_USING_STL
	typedef etl::string<MAX_INSTRUCTION_LEN> string;
	typedef etl::string<MAX_OPCODE_LEN + 1> opcodeString;
#else
	typedef std::string string;
	typedef std::string opcodeString;
#endif

	typedef ETL_OR_STD::bitset<ADDR_LEN> AddrBitset;
	typedef ETL_OR_STD::bitset<DATA_LEN> DataBitset;

	struct InstructionStruct {
		const DataBitset data;
		const opcodeString instructionString;
		const AddressingMode addressingMode;
		const Opcode instruction;
		const uint8_t argumentNumber;
	};

private:

	typedef ETL_OR_STD::optional<AddrBitset> OptionalAddrBitset;

	static const char HEX_CHAR[];
	static const char INT_TO_HEX[];

	ETL_OR_STD::optional<const InstructionStruct> instruction;
	ETL_OR_STD::optional<AddrBitset> operand;
	size_t argumentNumberCount;
	size_t currentDataOffset;

protected:

	static ETL_OR_STD::optional<Opcode> opcodeFromData(const DataBitset& data);

	static const char* stringFromOpcode(const Opcode instruction);

	static ETL_OR_STD::optional<AddressingMode> addressingModeFromData(const DataBitset& data);

	static uint8_t argumentNumberFromAddressingMode(const Disassembler6502::AddressingMode addressingMode);

	static ETL_OR_STD::optional<const Disassembler6502::InstructionStruct> instructionFromData(const Disassembler6502::DataBitset data);

public:

	Disassembler6502();

	void analyze(DataBitset instruction);

	ETL_OR_STD::optional<string> to_string() const;

	InstructionStatus getInstructionStatus() const;

	ETL_OR_STD::optional<const InstructionStruct> getInstruction() const;

	ETL_OR_STD::optional<Opcode> getOpcode() const;

	ETL_OR_STD::optional<AddressingMode> getAddressingMode() const;

	ETL_OR_STD::optional<DataBitset> getOpCodeData() const;

	ETL_OR_STD::optional<AddrBitset> getOperand() const;

	size_t getCurrentDataOffset() const;
};

#endif