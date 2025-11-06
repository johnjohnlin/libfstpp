// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv32_wrapper.h for the primary calling header

#include "Vpicorv32_wrapper__pch.h"
#include "Vpicorv32_wrapper__Syms.h"
#include "Vpicorv32_wrapper_axi4_memory.h"

void Vpicorv32_wrapper_axi4_memory___ctor_var_reset(Vpicorv32_wrapper_axi4_memory* vlSelf);

Vpicorv32_wrapper_axi4_memory::Vpicorv32_wrapper_axi4_memory(Vpicorv32_wrapper__Syms* symsp, const char* v__name)
    : VerilatedModule{v__name}
    , vlSymsp{symsp}
 {
    // Reset structure values
    Vpicorv32_wrapper_axi4_memory___ctor_var_reset(this);
}

void Vpicorv32_wrapper_axi4_memory::__Vconfigure(bool first) {
    (void)first;  // Prevent unused variable warning
}

Vpicorv32_wrapper_axi4_memory::~Vpicorv32_wrapper_axi4_memory() {
}
