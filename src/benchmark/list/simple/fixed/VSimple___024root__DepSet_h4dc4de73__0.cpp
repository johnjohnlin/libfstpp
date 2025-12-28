// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See VSimple.h for the primary calling header

#include "VSimple__pch.h"
#include "VSimple___024root.h"

void VSimple___024root___eval_act(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval_act\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void VSimple___024root___nba_sequent__TOP__0(VSimple___024root* vlSelf);

void VSimple___024root___eval_nba(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval_nba\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((3ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        VSimple___024root___nba_sequent__TOP__0(vlSelf);
        vlSelfRef.__Vm_traceActivity[1U] = 1U;
    }
}

VL_INLINE_OPT void VSimple___024root___nba_sequent__TOP__0(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___nba_sequent__TOP__0\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<4>/*127:0*/ __Vtemp_2;
    // Body
    if (vlSelfRef.rst_n) {
        vlSelfRef.Simple__DOT__counter_add = (3U & 
                                              ((IData)(1U) 
                                               + (IData)(vlSelfRef.Simple__DOT__counter_add)));
        __Vtemp_2[1U] = ((vlSelfRef.Simple__DOT__counter_shift[0U] 
                          >> 0x1eU) | (vlSelfRef.Simple__DOT__counter_shift[1U] 
                                       << 2U));
        __Vtemp_2[2U] = ((vlSelfRef.Simple__DOT__counter_shift[1U] 
                          >> 0x1eU) | (vlSelfRef.Simple__DOT__counter_shift[2U] 
                                       << 2U));
        __Vtemp_2[3U] = ((vlSelfRef.Simple__DOT__counter_shift[2U] 
                          >> 0x1eU) | (0x7ffffffcU 
                                       & (vlSelfRef.Simple__DOT__counter_shift[3U] 
                                          << 2U)));
        vlSelfRef.Simple__DOT__counter_shift[0U] = 
            (3U | (vlSelfRef.Simple__DOT__counter_shift[0U] 
                   << 2U));
    } else {
        vlSelfRef.Simple__DOT__counter_add = 0U;
        __Vtemp_2[1U] = 0U;
        __Vtemp_2[2U] = 0U;
        __Vtemp_2[3U] = 0U;
        vlSelfRef.Simple__DOT__counter_shift[0U] = 0U;
    }
    vlSelfRef.Simple__DOT__counter_shift[1U] = __Vtemp_2[1U];
    vlSelfRef.Simple__DOT__counter_shift[2U] = __Vtemp_2[2U];
    vlSelfRef.Simple__DOT__counter_shift[3U] = __Vtemp_2[3U];
}

void VSimple___024root___eval_triggers__act(VSimple___024root* vlSelf);

bool VSimple___024root___eval_phase__act(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval_phase__act\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<2> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    VSimple___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        VSimple___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool VSimple___024root___eval_phase__nba(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval_phase__nba\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        VSimple___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void VSimple___024root___dump_triggers__nba(VSimple___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void VSimple___024root___dump_triggers__act(VSimple___024root* vlSelf);
#endif  // VL_DEBUG

void VSimple___024root___eval(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            VSimple___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("Simple.sv", 2, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                VSimple___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("Simple.sv", 2, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (VSimple___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (VSimple___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void VSimple___024root___eval_debug_assertions(VSimple___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    VSimple___024root___eval_debug_assertions\n"); );
    VSimple__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.clk & 0xfeU)))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY(((vlSelfRef.rst_n & 0xfeU)))) {
        Verilated::overWidthError("rst_n");}
}
#endif  // VL_DEBUG
