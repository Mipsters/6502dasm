#include "Disassembler6502.h"

using ETL_OR_STD::optional;
using ETL_OR_STD::bitset;

const char Disassembler6502::HEX_CHAR[] = "$";
const char Disassembler6502::INT_TO_HEX[] = "0123456789ABCDEF";

optional<Disassembler6502::Opcode> Disassembler6502::opcodeFromData(const Disassembler6502::DataBitset& data)
{
	switch (data.to_ulong())
	{
	case 0x6D:
	case 0x7D:
	case 0x79:
	case 0x69:
	case 0x65:
	case 0x61:
	case 0x75:
	case 0x72:
	case 0x71:
		return ADC_INSTR;
	case 0x2D:
	case 0x3D:
	case 0x39:
	case 0x29:
	case 0x25:
	case 0x21:
	case 0x35:
	case 0x32:
	case 0x31:
		return AND_INSTR;
	case 0x0E:
	case 0x1E:
	case 0x0A:
	case 0x06:
	case 0x16:
		return ASL_INSTR;
	case 0x0F:
		return BBR0_INSTR;
	case 0x1F:
		return BBR1_INSTR;
	case 0x2F:
		return BBR2_INSTR;
	case 0x3F:
		return BBR3_INSTR;
	case 0x4F:
		return BBR4_INSTR;
	case 0x5F:
		return BBR5_INSTR;
	case 0x6F:
		return BBR6_INSTR;
	case 0x7F:
		return BBR7_INSTR;
	case 0x8F:
		return BBS0_INSTR;
	case 0x9F:
		return BBS1_INSTR;
	case 0xAF:
		return BBS2_INSTR;
	case 0xBF:
		return BBS3_INSTR;
	case 0xCF:
		return BBS4_INSTR;
	case 0xDF:
		return BBS5_INSTR;
	case 0xEF:
		return BBS6_INSTR;
	case 0xFF:
		return BBS7_INSTR;
	case 0x90:
		return BCC_INSTR;
	case 0xB0:
		return BCS_INSTR;
	case 0xF0:
		return BEQ_INSTR;
	case 0x2C:
	case 0x3C:
	case 0x89:
	case 0x24:
	case 0x34:
		return BIT_INSTR;
	case 0x30:
		return BMI_INSTR;
	case 0xD0:
		return BNE_INSTR;
	case 0x10:
		return BPL_INSTR;
	case 0x80:
		return BRA_INSTR;
	case 0x00:
		return BRK_INSTR;
	case 0x50:
		return BVC_INSTR;
	case 0x70:
		return BVS_INSTR;
	case 0x18:
		return CLC_INSTR;
	case 0xD8:
		return CLD_INSTR;
	case 0x58:
		return CLI_INSTR;
	case 0xB8:
		return CLV_INSTR;
	case 0xCD:
	case 0xDD:
	case 0xD9:
	case 0xC9:
	case 0xC5:
	case 0xC1:
	case 0xD5:
	case 0xD2:
	case 0xD1:
		return CMP_INSTR;
	case 0xEC:
	case 0xE0:
	case 0xE4:
		return CPX_INSTR;
	case 0xCC:
	case 0xC0:
	case 0xC4:
		return CPY_INSTR;
	case 0xCE:
	case 0xDE:
	case 0x3A:
	case 0xC6:
	case 0xD6:
		return DEC_INSTR;
	case 0xCA:
		return DEX_INSTR;
	case 0x88:
		return DEY_INSTR;
	case 0x4D:
	case 0x5D:
	case 0x59:
	case 0x49:
	case 0x45:
	case 0x41:
	case 0x55:
	case 0x52:
	case 0x51:
		return EOR_INSTR;
	case 0xEE:
	case 0xFE:
	case 0x1A:
	case 0xE6:
	case 0xF6:
		return INC_INSTR;
	case 0xE8:
		return INX_INSTR;
	case 0xC8:
		return INY_INSTR;
	case 0x4C:
	case 0x7C:
	case 0x6C:
		return JMP_INSTR;
	case 0x20:
		return JSR_INSTR;
	case 0xAD:
	case 0xBD:
	case 0xB9:
	case 0xA9:
	case 0xA5:
	case 0xA1:
	case 0xB5:
	case 0xB2:
	case 0xB1:
		return LDA_INSTR;
	case 0xAE:
	case 0xBE:
	case 0xA2:
	case 0xA6:
	case 0xB6:
		return LDX_INSTR;
	case 0xAC:
	case 0xBC:
	case 0xA0:
	case 0xA4:
	case 0xB4:
		return LDY_INSTR;
	case 0x4E:
	case 0x5E:
	case 0x4A:
	case 0x46:
	case 0x56:
		return LSR_INSTR;
	case 0xEA:
		return NOP_INSTR;
	case 0x0D:
	case 0x1D:
	case 0x19:
	case 0x09:
	case 0x05:
	case 0x01:
	case 0x15:
	case 0x12:
	case 0x11:
		return ORA_INSTR;
	case 0x48:
		return PHA_INSTR;
	case 0x08:
		return PHP_INSTR;
	case 0xDA:
		return PHX_INSTR;
	case 0x5A:
		return PHY_INSTR;
	case 0x68:
		return PLA_INSTR;
	case 0x28:
		return PLP_INSTR;
	case 0xFA:
		return PLX_INSTR;
	case 0x7A:
		return PLY_INSTR;
	case 0x07:
		return RMB0_INSTR;
	case 0x17:
		return RMB1_INSTR;
	case 0x27:
		return RMB2_INSTR;
	case 0x37:
		return RMB3_INSTR;
	case 0x47:
		return RMB4_INSTR;
	case 0x57:
		return RMB5_INSTR;
	case 0x67:
		return RMB6_INSTR;
	case 0x77:
		return RMB7_INSTR;
	case 0x2E:
	case 0x3E:
	case 0x2A:
	case 0x26:
	case 0x36:
		return ROL_INSTR;
	case 0x6E:
	case 0x7E:
	case 0x6A:
	case 0x66:
	case 0x76:
		return ROR_INSTR;
	case 0x40:
		return RTI_INSTR;
	case 0x60:
		return RTS_INSTR;
	case 0xED:
	case 0xFD:
	case 0xF9:
	case 0xE9:
	case 0xE5:
	case 0xE1:
	case 0xF5:
	case 0xF2:
	case 0xF1:
		return SBC_INSTR;
	case 0x38:
		return SEC_INSTR;
	case 0xF8:
		return SED_INSTR;
	case 0x78:
		return SEI_INSTR;
	case 0x87:
		return SMB0_INSTR;
	case 0x97:
		return SMB1_INSTR;
	case 0xA7:
		return SMB2_INSTR;
	case 0xB7:
		return SMB3_INSTR;
	case 0xC7:
		return SMB4_INSTR;
	case 0xD7:
		return SMB5_INSTR;
	case 0xE7:
		return SMB6_INSTR;
	case 0xF7:
		return SMB7_INSTR;
	case 0x8D:
	case 0x9D:
	case 0x99:
	case 0x85:
	case 0x81:
	case 0x95:
	case 0x92:
	case 0x91:
		return STA_INSTR;
	case 0xDB:
		return STP_INSTR;
	case 0x8E:
	case 0x86:
	case 0x96:
		return STX_INSTR;
	case 0x8C:
	case 0x84:
	case 0x94:
		return STY_INSTR;
	case 0x9C:
	case 0x9E:
	case 0x64:
	case 0x74:
		return STZ_INSTR;
	case 0xAA:
		return TAX_INSTR;
	case 0xA8:
		return TAY_INSTR;
	case 0x1C:
	case 0x14:
		return TRB_INSTR;
	case 0x0C:
	case 0x04:
		return TSB_INSTR;
	case 0xBA:
		return TSX_INSTR;
	case 0x8A:
		return TXA_INSTR;
	case 0x9A:
		return TXS_INSTR;
	case 0x98:
		return TYA_INSTR;
	case 0xCB:
		return WAI_INSTR;
	}

	return optional<Disassembler6502::Opcode>();
}

optional<Disassembler6502::AddressingMode> Disassembler6502::addressingModeFromData(const Disassembler6502::DataBitset& data)
{
	switch (data.to_ulong())
	{
	case 0x6D:
	case 0x2D:
	case 0x0E:
	case 0x2C:
	case 0xCD:
	case 0xEC:
	case 0xCC:
	case 0xCE:
	case 0x4D:
	case 0xEE:
	case 0x4C:
	case 0x20:
	case 0xAD:
	case 0xAE:
	case 0xAC:
	case 0x4E:
	case 0x0D:
	case 0x2E:
	case 0x6E:
	case 0xED:
	case 0x8D:
	case 0x8E:
	case 0x8C:
	case 0x9C:
	case 0x1C:
	case 0x0C:
		return ABSOLUTE_AM;
	case 0x7C:
		return ABSOLUTE_INDEXED_INDIRECT_AM;
	case 0x7D:
	case 0x3D:
	case 0x1E:
	case 0x3C:
	case 0xDD:
	case 0xDE:
	case 0x5D:
	case 0xFE:
	case 0xBD:
	case 0xBC:
	case 0x5E:
	case 0x1D:
	case 0x3E:
	case 0x7E:
	case 0xFD:
	case 0x9D:
	case 0x9E:
		return ABSOLUTE_INDEXED_WITH_X_AM;
	case 0x79:
	case 0x39:
	case 0xD9:
	case 0x59:
	case 0xB9:
	case 0xBE:
	case 0x19:
	case 0xF9:
	case 0x99:
		return ABSOLUTE_INDEXED_WITH_Y_AM;
	case 0x6C:
		return ABSOLUTE_INDIRECT_AM;
	case 0x0A:
	case 0x3A:
	case 0x1A:
	case 0x4A:
	case 0x2A:
	case 0x6A:
		return ACCUMULATOR_AM;
	case 0x69:
	case 0x29:
	case 0x89:
	case 0xC9:
	case 0xE0:
	case 0xC0:
	case 0x49:
	case 0xA9:
	case 0xA2:
	case 0xA0:
	case 0x09:
	case 0xE9:
		return IMMEDIATE_ADDRESSING_AM;
	case 0x18:
	case 0xD8:
	case 0x58:
	case 0xB8:
	case 0xCA:
	case 0x88:
	case 0xE8:
	case 0xC8:
	case 0xEA:
	case 0x38:
	case 0xF8:
	case 0x78:
	case 0xDB:
	case 0xAA:
	case 0xA8:
	case 0xBA:
	case 0x8A:
	case 0x9A:
	case 0x98:
	case 0xCB:
		return IMPLIED_AM;
	case 0x0F:
	case 0x1F:
	case 0x2F:
	case 0x3F:
	case 0x4F:
	case 0x5F:
	case 0x6F:
	case 0x7F:
	case 0x8F:
	case 0x9F:
	case 0xAF:
	case 0xBF:
	case 0xCF:
	case 0xDF:
	case 0xEF:
	case 0xFF:
	case 0x90:
	case 0xB0:
	case 0xF0:
	case 0x30:
	case 0xD0:
	case 0x10:
	case 0x80:
	case 0x50:
	case 0x70:
		return PROGRAM_COUNTER_RELATIVE_AM;
	case 0x00:
	case 0x48:
	case 0x08:
	case 0xDA:
	case 0x5A:
	case 0x68:
	case 0x28:
	case 0xFA:
	case 0x7A:
	case 0x40:
	case 0x60:
		return STACK_AM;
	case 0x65:
	case 0x25:
	case 0x06:
	case 0x24:
	case 0xC5:
	case 0xE4:
	case 0xC4:
	case 0xC6:
	case 0x45:
	case 0xE6:
	case 0xA5:
	case 0xA6:
	case 0xA4:
	case 0x46:
	case 0x05:
	case 0x07:
	case 0x17:
	case 0x27:
	case 0x37:
	case 0x47:
	case 0x57:
	case 0x67:
	case 0x77:
	case 0x26:
	case 0x66:
	case 0xE5:
	case 0x87:
	case 0x97:
	case 0xA7:
	case 0xB7:
	case 0xC7:
	case 0xD7:
	case 0xE7:
	case 0xF7:
	case 0x85:
	case 0x86:
	case 0x84:
	case 0x64:
	case 0x14:
	case 0x04:
		return ZERO_PAGE_AM;
	case 0x61:
	case 0x21:
	case 0xC1:
	case 0x41:
	case 0xA1:
	case 0x01:
	case 0xE1:
	case 0x81:
		return ZERO_PAGE_INDEXED_INDIRECT_AM;
	case 0x75:
	case 0x35:
	case 0x16:
	case 0x34:
	case 0xD5:
	case 0xD6:
	case 0x55:
	case 0xF6:
	case 0xB5:
	case 0xB4:
	case 0x56:
	case 0x15:
	case 0x36:
	case 0x76:
	case 0xF5:
	case 0x95:
	case 0x94:
	case 0x74:
		return ZERO_PAGE_INDEXED_WITH_X_AM;
	case 0xB6:
	case 0x96:
		return ZERO_PAGE_INDEXED_WITH_Y_AM;
	case 0x72:
	case 0x32:
	case 0xD2:
	case 0x52:
	case 0xB2:
	case 0x12:
	case 0xF2:
	case 0x92:
		return ZERO_PAGE_INDIRECT_AM;
	case 0x71:
	case 0x31:
	case 0xD1:
	case 0x51:
	case 0xB1:
	case 0x11:
	case 0xF1:
	case 0x91:
		return ZERO_PAGE_INDIRECT_INDEXED_WITH_Y_AM;
	}

	return optional<Disassembler6502::AddressingMode>();
}

const char* Disassembler6502::stringFromOpcode(const Disassembler6502::Opcode opcode)
{
	switch (opcode)
	{
	case ADC_INSTR:
		return "ADC";
	case AND_INSTR:
		return "AND";
	case ASL_INSTR:
		return "ASL";
	case BBR0_INSTR:
		return "BBR0";
	case BBR1_INSTR:
		return "BBR1";
	case BBR2_INSTR:
		return "BBR2";
	case BBR3_INSTR:
		return "BBR3";
	case BBR4_INSTR:
		return "BBR4";
	case BBR5_INSTR:
		return "BBR5";
	case BBR6_INSTR:
		return "BBR6";
	case BBR7_INSTR:
		return "BBR7";
	case BBS0_INSTR:
		return "BBS0";
	case BBS1_INSTR:
		return "BBS1";
	case BBS2_INSTR:
		return "BBS2";
	case BBS3_INSTR:
		return "BBS3";
	case BBS4_INSTR:
		return "BBS4";
	case BBS5_INSTR:
		return "BBS5";
	case BBS6_INSTR:
		return "BBS6";
	case BBS7_INSTR:
		return "BBS7";
	case BCC_INSTR:
		return "BCC";
	case BCS_INSTR:
		return "BCS";
	case BEQ_INSTR:
		return "BEQ";
	case BIT_INSTR:
		return "BIT";
	case BMI_INSTR:
		return "BMI";
	case BNE_INSTR:
		return "BNE";
	case BPL_INSTR:
		return "BPL";
	case BRA_INSTR:
		return "BRA";
	case BRK_INSTR:
		return "BRK";
	case BVC_INSTR:
		return "BVC";
	case BVS_INSTR:
		return "BVS";
	case CLC_INSTR:
		return "CLC";
	case CLD_INSTR:
		return "CLD";
	case CLI_INSTR:
		return "CLI";
	case CLV_INSTR:
		return "CLV";
	case CMP_INSTR:
		return "CMP";
	case CPX_INSTR:
		return "CPX";
	case CPY_INSTR:
		return "CPY";
	case DEC_INSTR:
		return "DEC";
	case DEX_INSTR:
		return "DEX";
	case DEY_INSTR:
		return "DEY";
	case EOR_INSTR:
		return "EOR";
	case INC_INSTR:
		return "INC";
	case INX_INSTR:
		return "INX";
	case INY_INSTR:
		return "INY";
	case JMP_INSTR:
		return "JMP";
	case JSR_INSTR:
		return "JSR";
	case LDA_INSTR:
		return "LDA";
	case LDX_INSTR:
		return "LDX";
	case LDY_INSTR:
		return "LDY";
	case LSR_INSTR:
		return "LSR";
	case NOP_INSTR:
		return "NOP";
	case ORA_INSTR:
		return "ORA";
	case PHA_INSTR:
		return "PHA";
	case PHP_INSTR:
		return "PHP";
	case PHX_INSTR:
		return "PHX";
	case PHY_INSTR:
		return "PHY";
	case PLA_INSTR:
		return "PLA";
	case PLP_INSTR:
		return "PLP";
	case PLX_INSTR:
		return "PLX";
	case PLY_INSTR:
		return "PLY";
	case RMB0_INSTR:
		return "RMB0";
	case RMB1_INSTR:
		return "RMB1";
	case RMB2_INSTR:
		return "RMB2";
	case RMB3_INSTR:
		return "RMB3";
	case RMB4_INSTR:
		return "RMB4";
	case RMB5_INSTR:
		return "RMB5";
	case RMB6_INSTR:
		return "RMB6";
	case RMB7_INSTR:
		return "RMB7";
	case ROL_INSTR:
		return "ROL";
	case ROR_INSTR:
		return "ROR";
	case RTI_INSTR:
		return "RTI";
	case RTS_INSTR:
		return "RTS";
	case SBC_INSTR:
		return "SBC";
	case SEC_INSTR:
		return "SEC";
	case SED_INSTR:
		return "SED";
	case SEI_INSTR:
		return "SEI";
	case SMB0_INSTR:
		return "SMB0";
	case SMB1_INSTR:
		return "SMB1";
	case SMB2_INSTR:
		return "SMB2";
	case SMB3_INSTR:
		return "SMB3";
	case SMB4_INSTR:
		return "SMB4";
	case SMB5_INSTR:
		return "SMB5";
	case SMB6_INSTR:
		return "SMB6";
	case SMB7_INSTR:
		return "SMB7";
	case STA_INSTR:
		return "STA";
	case STP_INSTR:
		return "STP";
	case STX_INSTR:
		return "STX";
	case STY_INSTR:
		return "STY";
	case STZ_INSTR:
		return "STZ";
	case TAX_INSTR:
		return "TAX";
	case TAY_INSTR:
		return "TAY";
	case TRB_INSTR:
		return "TRB";
	case TSB_INSTR:
		return "TSB";
	case TSX_INSTR:
		return "TSX";
	case TXA_INSTR:
		return "TXA";
	case TXS_INSTR:
		return "TXS";
	case TYA_INSTR:
		return "TYA";
	case WAI_INSTR:
		return "WAI";
	}

	return NULL;
}

uint8_t Disassembler6502::argumentNumberFromAddressingMode(const Disassembler6502::AddressingMode addressingMode)
{
	switch (addressingMode)
	{
	case ABSOLUTE_AM:
	case ABSOLUTE_INDEXED_INDIRECT_AM:
	case ABSOLUTE_INDEXED_WITH_X_AM:
	case ABSOLUTE_INDEXED_WITH_Y_AM:
	case ABSOLUTE_INDIRECT_AM:
		return 2;
	case IMMEDIATE_ADDRESSING_AM:
	case PROGRAM_COUNTER_RELATIVE_AM:
	case ZERO_PAGE_AM:
	case ZERO_PAGE_INDEXED_INDIRECT_AM:
	case ZERO_PAGE_INDEXED_WITH_X_AM:
	case ZERO_PAGE_INDEXED_WITH_Y_AM:
	case ZERO_PAGE_INDIRECT_AM:
	case ZERO_PAGE_INDIRECT_INDEXED_WITH_Y_AM:
		return 1;
	case ACCUMULATOR_AM:
	case IMPLIED_AM:
	case STACK_AM:
	default:
		return 0;
	}
}

optional<const Disassembler6502::InstructionStruct> Disassembler6502::instructionFromData(const Disassembler6502::DataBitset data) {
	const optional<Disassembler6502::Opcode> opcode(Disassembler6502::opcodeFromData(data));
	const optional<Disassembler6502::AddressingMode> addressingMode(Disassembler6502::addressingModeFromData(data));

	if (!opcode.has_value() || !addressingMode.has_value()) {
		return optional<const Disassembler6502::InstructionStruct>();
	}

	return optional<const Disassembler6502::InstructionStruct>({
		data,
		Disassembler6502::stringFromOpcode(*opcode),
		*addressingMode,
		*opcode,
		Disassembler6502::argumentNumberFromAddressingMode(*addressingMode)
		});
}

Disassembler6502::Disassembler6502() : argumentNumberCount(0), currentDataOffset(0) {};

void Disassembler6502::analyze(Disassembler6502::DataBitset data)
{
	currentDataOffset++;

	if (!instruction.has_value() || argumentNumberCount == 0)
	{
		operand.reset();
		instruction.reset();

		const optional currentInstruction = instructionFromData(data);
		if (currentInstruction.has_value()) {
			instruction.emplace(*currentInstruction);
		}

		if (!instruction.has_value()) {
			instruction.reset();
			argumentNumberCount = 0;

			return;
		}

		argumentNumberCount = instruction->argumentNumber;
	}
	else if (argumentNumberCount > 0)
	{
		Disassembler6502::AddrBitset orAble;

		for (size_t i = 0; i < data.size(); i++)
		{
			orAble[i] = data[i];
		}

		orAble <<= DATA_LEN * (instruction->argumentNumber - argumentNumberCount);

		if (!operand.has_value()) {
			operand = Disassembler6502::AddrBitset(0ULL);
		}

		*operand |= orAble;

		argumentNumberCount--;
	}
}

optional<Disassembler6502::string> Disassembler6502::to_string() const {
	// if there're arguments, operand must have a value. if there are 0 arguments, operand cannot have a value
	if (!instruction.has_value() || ((instruction->argumentNumber > 0) ^ operand.has_value())) {
		return optional<Disassembler6502::string>();
	}

	Disassembler6502::string outStr = "";

	if (operand.has_value()) {
		long operandVal;

		if (instruction->addressingMode == PROGRAM_COUNTER_RELATIVE_AM) {
			// This char converstion removes data from the second Byte
			// but in this instruction ther is only one argument, so its fine
			operandVal = static_cast<char>(operand->to_ulong());
			operandVal += static_cast<long>(currentDataOffset);
		}
		else {
			operandVal = operand->to_ulong();
		}

		AddrBitset operand(static_cast<unsigned long>(operandVal));

		if (operand.count() == 0) {
			outStr.insert(0, "00");
		}
		else while (operand.count()) {
			char hex[3] = {
				INT_TO_HEX[(operand.to_ulong() & 0xF0) >> 4],
				INT_TO_HEX[operand.to_ulong() & 0xF],
				'\0'
			};
			outStr.insert(0, hex);

			operand >>= 8;
		}

		outStr.insert(0, HEX_CHAR);
	}

	switch (instruction->addressingMode)
	{
	case ABSOLUTE_AM:                 // a
	case STACK_AM:                    // s
	case ZERO_PAGE_AM:                // zp
	case IMPLIED_AM:                  // i
	case PROGRAM_COUNTER_RELATIVE_AM: // r
		break;
	case ABSOLUTE_INDEXED_INDIRECT_AM:
	case ZERO_PAGE_INDEXED_INDIRECT_AM:
		outStr.insert(0, "(");
		outStr.append(", X)");
		break;
	case ABSOLUTE_INDEXED_WITH_X_AM:
	case ZERO_PAGE_INDEXED_WITH_X_AM:
		outStr.append(", X");
		break;
	case ABSOLUTE_INDEXED_WITH_Y_AM:
	case ZERO_PAGE_INDEXED_WITH_Y_AM:
		outStr.append(", Y");
		break;
	case ABSOLUTE_INDIRECT_AM:
	case ZERO_PAGE_INDIRECT_AM:
		outStr.insert(0, "(");
		outStr.append(")");
		break;
	case IMMEDIATE_ADDRESSING_AM:
		outStr.insert(0, "#");
		break;
		// maybe should be at the top with no string representation added
	case ACCUMULATOR_AM:
		outStr.append(" A");
		break;
	case ZERO_PAGE_INDIRECT_INDEXED_WITH_Y_AM:
		outStr.insert(0, "(");
		outStr.append("), Y");
		break;
	}

	return outStr;
}

Disassembler6502::InstructionStatus Disassembler6502::getInstructionStatus() const
{
	if (!instruction.has_value())
	{
		return NO_INSTRUCTION;
	}

	if (argumentNumberCount == 0)
	{
		// TODO: know if an instruction ended without relaying on SYNC
		return EXECUTING_INSTRUCTION;
	}

	if (argumentNumberCount == instruction->argumentNumber) {
		return AWAITING_FIRST_ARGUMENT;
	}

	if (argumentNumberCount < instruction->argumentNumber) {
		return AWAITING_SECOND_ARGUMENT;
	}

	return NO_INSTRUCTION;
}

optional<const Disassembler6502::InstructionStruct> Disassembler6502::getInstruction() const {
	return instruction;
};

optional<Disassembler6502::Opcode> Disassembler6502::getOpcode() const {
	if (!instruction.has_value()) {
		return optional<Disassembler6502::Opcode>();
	}

	return instruction->instruction;
}

optional<Disassembler6502::AddressingMode> Disassembler6502::getAddressingMode() const {
	if (!instruction.has_value()) {
		return optional<Disassembler6502::AddressingMode>();
	}

	return instruction->addressingMode;
}

optional<Disassembler6502::DataBitset> Disassembler6502::getOpCodeData() const {
	return instruction->data;
}

optional<Disassembler6502::AddrBitset> Disassembler6502::getOperand() const {
	return operand;
}

size_t Disassembler6502::getCurrentDataOffset() const
{
	return currentDataOffset;
}
