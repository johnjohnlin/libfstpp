// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See VSimple.h for the primary calling header

#ifndef VERILATED_VSIMPLE___024ROOT_H_
#define VERILATED_VSIMPLE___024ROOT_H_  // guard

#include "verilated.h"


class VSimple__Syms;

class alignas(VL_CACHE_LINE_BYTES) VSimple___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(clk,0,0);
    VL_IN8(rst_n,0,0);
    CData/*1:0*/ Simple__DOT__counter_add;
    CData/*0:0*/ __Vtrigprevexpr___TOP__clk__0;
    CData/*0:0*/ __Vtrigprevexpr___TOP__rst_n__0;
    CData/*0:0*/ __VactContinue;
    IData/*31:0*/ __VactIterCount;
    VlTriggerVec<2> __VactTriggered;
    VlTriggerVec<2> __VnbaTriggered;

    // INTERNAL VARIABLES
    VSimple__Syms* const vlSymsp;

    // CONSTRUCTORS
    VSimple___024root(VSimple__Syms* symsp, const char* v__name);
    ~VSimple___024root();
    VL_UNCOPYABLE(VSimple___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
