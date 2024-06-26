/* AUTOGENERATED FILE - DO NOT MODIFY */
#pragma once
#include <cstdint>
#include <string>
#include "encodings.hh"

namespace basim {

struct ArchState; // forward declaration
class Cycles; // forward declaration

/* evi Instruction */
Cycles exeInstEvi(ArchState& ast, EncInst inst);
std::string disasmInstEvi(EncInst inst);
EncInst constrInstEvi(RegId Xs, RegId Xd, uint64_t imm, uint64_t sel);

/* evii Instruction */
Cycles exeInstEvii(ArchState& ast, EncInst inst);
std::string disasmInstEvii(EncInst inst);
EncInst constrInstEvii(RegId Xd, uint64_t imm1, uint64_t imm2, uint64_t sel);

/* ev Instruction */
Cycles exeInstEv(ArchState& ast, EncInst inst);
std::string disasmInstEv(EncInst inst);
EncInst constrInstEv(RegId Xs, RegId Xd, RegId Xop1, RegId Xop2, uint64_t sel);

/* evlb Instruction */
Cycles exeInstEvlb(ArchState& ast, EncInst inst);
std::string disasmInstEvlb(EncInst inst);
EncInst constrInstEvlb(RegId Xd, uint64_t label);

}; // namespace basim
/* AUTOGENERATED FILE - DO NOT MODIFY */
