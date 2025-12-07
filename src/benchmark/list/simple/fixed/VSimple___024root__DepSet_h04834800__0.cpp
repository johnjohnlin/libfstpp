// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimple.h for the primary calling header

#include "VSimple__pch.h"
#include "VSimple__Syms.h"
#include "VSimple___024root.h"

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimple___024root___dump_triggers__act(VSimple___024root* vlSelf);
#endif  // VL_DEBUG

void VSimple___024root___eval_triggers__act(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval_triggers__act\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        VSimple___024root___dump_triggers__act(vlSelf);
    }
#endif
}
