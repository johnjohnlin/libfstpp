// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv32_wrapper.h for the primary calling header

#include "Vpicorv32_wrapper__pch.h"
#include "Vpicorv32_wrapper_axi4_memory.h"

VL_INLINE_OPT void Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__1(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__1\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__VdlySet__memory__v4 = 0U;
    vlSelfRef.__VdlySet__memory__v5 = 0U;
    vlSelfRef.__VdlySet__memory__v6 = 0U;
    vlSelfRef.__VdlySet__memory__v7 = 0U;
    vlSelfRef.__VdlySet__memory__v0 = 0U;
    vlSelfRef.__VdlySet__memory__v1 = 0U;
    vlSelfRef.__VdlySet__memory__v2 = 0U;
    vlSelfRef.__VdlySet__memory__v3 = 0U;
}

VL_INLINE_OPT void Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__2(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__2\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__Vdly__mem_axi_arready = vlSelfRef.__PVT__mem_axi_arready;
    vlSelfRef.__Vdly__mem_axi_awready = vlSelfRef.__PVT__mem_axi_awready;
    vlSelfRef.__Vdly__mem_axi_wready = vlSelfRef.__PVT__mem_axi_wready;
    vlSelfRef.__Vdly__fast_raddr = vlSelfRef.__PVT__fast_raddr;
    vlSelfRef.__Vdly__fast_waddr = vlSelfRef.__PVT__fast_waddr;
    vlSelfRef.__Vdly__fast_wdata = vlSelfRef.__PVT__fast_wdata;
    vlSelfRef.__Vdly__mem_axi_rvalid = vlSelfRef.__PVT__mem_axi_rvalid;
    vlSelfRef.__Vdly__mem_axi_bvalid = vlSelfRef.__PVT__mem_axi_bvalid;
}

VL_INLINE_OPT void Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__5(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__5\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__mem_axi_arready = vlSelfRef.__Vdly__mem_axi_arready;
    vlSelfRef.__PVT__mem_axi_awready = vlSelfRef.__Vdly__mem_axi_awready;
    vlSelfRef.__PVT__mem_axi_wready = vlSelfRef.__Vdly__mem_axi_wready;
    vlSelfRef.__PVT__fast_raddr = vlSelfRef.__Vdly__fast_raddr;
    vlSelfRef.__PVT__fast_waddr = vlSelfRef.__Vdly__fast_waddr;
    vlSelfRef.__PVT__fast_wdata = vlSelfRef.__Vdly__fast_wdata;
    vlSelfRef.__PVT__mem_axi_rvalid = vlSelfRef.__Vdly__mem_axi_rvalid;
    vlSelfRef.__PVT__mem_axi_bvalid = vlSelfRef.__Vdly__mem_axi_bvalid;
}

VL_INLINE_OPT void Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__6(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___nba_sequent__TOP__picorv32_wrapper__mem__6\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.__VdlySet__memory__v0) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v0] 
            = ((0xffffff00U & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v0]) 
               | (IData)(vlSelfRef.__VdlyVal__memory__v0));
    }
    if (vlSelfRef.__VdlySet__memory__v1) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v1] 
            = ((0xffff00ffU & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v1]) 
               | ((IData)(vlSelfRef.__VdlyVal__memory__v1) 
                  << 8U));
    }
    if (vlSelfRef.__VdlySet__memory__v2) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v2] 
            = ((0xff00ffffU & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v2]) 
               | ((IData)(vlSelfRef.__VdlyVal__memory__v2) 
                  << 0x10U));
    }
    if (vlSelfRef.__VdlySet__memory__v3) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v3] 
            = ((0xffffffU & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v3]) 
               | ((IData)(vlSelfRef.__VdlyVal__memory__v3) 
                  << 0x18U));
    }
    if (vlSelfRef.__VdlySet__memory__v4) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v4] 
            = ((0xffffff00U & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v4]) 
               | (IData)(vlSelfRef.__VdlyVal__memory__v4));
    }
    if (vlSelfRef.__VdlySet__memory__v5) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v5] 
            = ((0xffff00ffU & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v5]) 
               | ((IData)(vlSelfRef.__VdlyVal__memory__v5) 
                  << 8U));
    }
    if (vlSelfRef.__VdlySet__memory__v6) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v6] 
            = ((0xff00ffffU & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v6]) 
               | ((IData)(vlSelfRef.__VdlyVal__memory__v6) 
                  << 0x10U));
    }
    if (vlSelfRef.__VdlySet__memory__v7) {
        vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v7] 
            = ((0xffffffU & vlSelfRef.memory[vlSelfRef.__VdlyDim0__memory__v7]) 
               | ((IData)(vlSelfRef.__VdlyVal__memory__v7) 
                  << 0x18U));
    }
}
