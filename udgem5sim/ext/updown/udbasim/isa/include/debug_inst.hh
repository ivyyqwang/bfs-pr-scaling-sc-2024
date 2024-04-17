/* AUTOGENERATED FILE - DO NOT MODIFY */
#pragma once
#include <cstdint>
#include <string>
#include "encodings.hh"

namespace basim {

struct ArchState; // forward declaration
class Cycles; // forward declaration

/* print, perflog Instruction */
Cycles exeInstPrintPerflog(ArchState& ast, EncInst inst);
std::string disasmInstPrintPerflog(EncInst inst);
EncInst constrInstPrintPerflog(uint64_t offset, uint64_t func);

}; // namespace basim
/* AUTOGENERATED FILE - DO NOT MODIFY */