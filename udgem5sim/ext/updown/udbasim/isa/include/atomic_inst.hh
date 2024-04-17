/* AUTOGENERATED FILE - DO NOT MODIFY */
#pragma once
#include <cstdint>
#include <string>
#include "encodings.hh"

namespace basim {

struct ArchState; // forward declaration
class Cycles; // forward declaration

/* cswp Instruction */
Cycles exeInstCswp(ArchState& ast, EncInst inst);
std::string disasmInstCswp(EncInst inst);
EncInst constrInstCswp(RegId X1, RegId X2, RegId X3, RegId X4);

/* cswpi Instruction */
Cycles exeInstCswpi(ArchState& ast, EncInst inst);
std::string disasmInstCswpi(EncInst inst);
EncInst constrInstCswpi(RegId X1, RegId X2, int64_t imm1, int64_t imm2);

}; // namespace basim
/* AUTOGENERATED FILE - DO NOT MODIFY */