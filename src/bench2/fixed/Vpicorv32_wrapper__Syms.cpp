// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vpicorv32_wrapper__pch.h"
#include "Vpicorv32_wrapper.h"
#include "Vpicorv32_wrapper___024root.h"
#include "Vpicorv32_wrapper_picorv32_wrapper.h"
#include "Vpicorv32_wrapper_axi4_memory.h"

// FUNCTIONS
Vpicorv32_wrapper__Syms::~Vpicorv32_wrapper__Syms()
{
}

Vpicorv32_wrapper__Syms::Vpicorv32_wrapper__Syms(VerilatedContext* contextp, const char* namep, Vpicorv32_wrapper* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
    , TOP__picorv32_wrapper{this, Verilated::catName(namep, "picorv32_wrapper")}
    , TOP__picorv32_wrapper__mem{this, Verilated::catName(namep, "picorv32_wrapper.mem")}
{
        // Check resources
        Verilated::stackCheck(139);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-12);
    // Setup each module's pointers to their submodules
    TOP.picorv32_wrapper = &TOP__picorv32_wrapper;
    TOP__picorv32_wrapper.mem = &TOP__picorv32_wrapper__mem;
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    TOP__picorv32_wrapper.__Vconfigure(true);
    TOP__picorv32_wrapper__mem.__Vconfigure(true);
    // Setup scopes
    __Vscope_picorv32_wrapper__mem.configure(this, name(), "picorv32_wrapper.mem", "mem", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_picorv32_wrapper__mem.varInsert(__Vfinal,"memory", &(TOP__picorv32_wrapper__mem.memory), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,1,1 ,0,32767 ,31,0);
    }
}
