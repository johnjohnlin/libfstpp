// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv32_wrapper.h for the primary calling header

#include "Vpicorv32_wrapper__pch.h"
#include "Vpicorv32_wrapper__Syms.h"
#include "Vpicorv32_wrapper___024root.h"

VL_ATTR_COLD void Vpicorv32_wrapper_picorv32_wrapper___eval_static__TOP__picorv32_wrapper(Vpicorv32_wrapper_picorv32_wrapper* vlSelf);
VL_ATTR_COLD void Vpicorv32_wrapper___024root____Vm_traceActivitySetAll(Vpicorv32_wrapper___024root* vlSelf);
VL_ATTR_COLD void Vpicorv32_wrapper_axi4_memory___eval_static__TOP__picorv32_wrapper__mem(Vpicorv32_wrapper_axi4_memory* vlSelf);

VL_ATTR_COLD void Vpicorv32_wrapper___024root___eval_static(Vpicorv32_wrapper___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv32_wrapper___024root___eval_static\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vpicorv32_wrapper_picorv32_wrapper___eval_static__TOP__picorv32_wrapper((&vlSymsp->TOP__picorv32_wrapper));
    Vpicorv32_wrapper___024root____Vm_traceActivitySetAll(vlSelf);
    Vpicorv32_wrapper_axi4_memory___eval_static__TOP__picorv32_wrapper__mem((&vlSymsp->TOP__picorv32_wrapper__mem));
    vlSelfRef.__Vtrigprevexpr___TOP__clk__0 = vlSelfRef.clk;
}

VL_ATTR_COLD void Vpicorv32_wrapper_picorv32_wrapper___eval_initial__TOP__picorv32_wrapper(Vpicorv32_wrapper_picorv32_wrapper* vlSelf);
VL_ATTR_COLD void Vpicorv32_wrapper_axi4_memory___eval_initial__TOP__picorv32_wrapper__mem(Vpicorv32_wrapper_axi4_memory* vlSelf);

VL_ATTR_COLD void Vpicorv32_wrapper___024root___eval_initial(Vpicorv32_wrapper___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv32_wrapper___024root___eval_initial\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    Vpicorv32_wrapper_picorv32_wrapper___eval_initial__TOP__picorv32_wrapper((&vlSymsp->TOP__picorv32_wrapper));
    Vpicorv32_wrapper___024root____Vm_traceActivitySetAll(vlSelf);
    Vpicorv32_wrapper_axi4_memory___eval_initial__TOP__picorv32_wrapper__mem((&vlSymsp->TOP__picorv32_wrapper__mem));
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vpicorv32_wrapper___024root___dump_triggers__stl(Vpicorv32_wrapper___024root* vlSelf);
#endif  // VL_DEBUG

VL_ATTR_COLD void Vpicorv32_wrapper___024root___eval_triggers__stl(Vpicorv32_wrapper___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv32_wrapper___024root___eval_triggers__stl\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VstlTriggered.setBit(0U, (IData)(vlSelfRef.__VstlFirstIteration));
#ifdef VL_DEBUG
    if (VL_UNLIKELY(vlSymsp->_vm_contextp__->debug())) {
        Vpicorv32_wrapper___024root___dump_triggers__stl(vlSelf);
    }
#endif
}

VL_ATTR_COLD void Vpicorv32_wrapper___024root___stl_sequent__TOP__0(Vpicorv32_wrapper___024root* vlSelf);
VL_ATTR_COLD void Vpicorv32_wrapper_picorv32_wrapper___stl_sequent__TOP__picorv32_wrapper__0(Vpicorv32_wrapper_picorv32_wrapper* vlSelf);

VL_ATTR_COLD void Vpicorv32_wrapper___024root___eval_stl(Vpicorv32_wrapper___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv32_wrapper___024root___eval_stl\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VstlTriggered.word(0U))) {
        Vpicorv32_wrapper___024root___stl_sequent__TOP__0(vlSelf);
        Vpicorv32_wrapper___024root____Vm_traceActivitySetAll(vlSelf);
        Vpicorv32_wrapper_picorv32_wrapper___stl_sequent__TOP__picorv32_wrapper__0((&vlSymsp->TOP__picorv32_wrapper));
    }
}

VL_ATTR_COLD void Vpicorv32_wrapper___024root___stl_sequent__TOP__0(Vpicorv32_wrapper___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vpicorv32_wrapper___024root___stl_sequent__TOP__0\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.trace_data = vlSymsp->TOP__picorv32_wrapper.trace_data;
    vlSelfRef.trace_valid = vlSymsp->TOP__picorv32_wrapper.trace_valid;
    vlSelfRef.trap = vlSymsp->TOP__picorv32_wrapper.trap;
}
