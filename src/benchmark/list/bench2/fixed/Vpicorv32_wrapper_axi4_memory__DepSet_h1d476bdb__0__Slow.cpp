// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv32_wrapper.h for the primary calling header

#include "Vpicorv32_wrapper__pch.h"
#include "Vpicorv32_wrapper_axi4_memory.h"

VL_ATTR_COLD void Vpicorv32_wrapper_axi4_memory___eval_static__TOP__picorv32_wrapper__mem(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___eval_static__TOP__picorv32_wrapper__mem\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__xorshift64_state = 0x139408dcbbf7a44ULL;
    vlSelfRef.__PVT__fast_axi_transaction = 7U;
    vlSelfRef.__PVT__async_axi_transaction = 0x1fU;
    vlSelfRef.__PVT__delay_axi_transaction = 0U;
    vlSelfRef.__PVT__latched_raddr_en = 0U;
    vlSelfRef.__PVT__latched_waddr_en = 0U;
    vlSelfRef.__PVT__latched_wdata_en = 0U;
    vlSelfRef.__PVT__fast_raddr = 0U;
    vlSelfRef.__PVT__fast_waddr = 0U;
    vlSelfRef.__PVT__fast_wdata = 0U;
}

VL_ATTR_COLD void Vpicorv32_wrapper_axi4_memory___eval_initial__TOP__picorv32_wrapper__mem(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___eval_initial__TOP__picorv32_wrapper__mem\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.__PVT__verbose = (0U != VL_TESTPLUSARGS_I(
                                                        std::string{"verbose"}));
    vlSelfRef.__PVT__axi_test = (0U != VL_TESTPLUSARGS_I(
                                                         std::string{"axi_test"}));
    vlSelfRef.__PVT__mem_axi_awready = 0U;
    vlSelfRef.__PVT__mem_axi_wready = 0U;
    vlSelfRef.__PVT__mem_axi_bvalid = 0U;
    vlSelfRef.__PVT__mem_axi_arready = 0U;
    vlSelfRef.__PVT__mem_axi_rvalid = 0U;
    vlSelfRef.__PVT__tests_passed = 0U;
}

VL_ATTR_COLD void Vpicorv32_wrapper_axi4_memory___ctor_var_reset(Vpicorv32_wrapper_axi4_memory* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+        Vpicorv32_wrapper_axi4_memory___ctor_var_reset\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelf->__PVT__clk = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_awvalid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_awready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_awaddr = VL_RAND_RESET_I(32);
    vlSelf->__PVT__mem_axi_awprot = VL_RAND_RESET_I(3);
    vlSelf->__PVT__mem_axi_wvalid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_wready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_wdata = VL_RAND_RESET_I(32);
    vlSelf->__PVT__mem_axi_wstrb = VL_RAND_RESET_I(4);
    vlSelf->__PVT__mem_axi_bvalid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_bready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_arvalid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_arready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_araddr = VL_RAND_RESET_I(32);
    vlSelf->__PVT__mem_axi_arprot = VL_RAND_RESET_I(3);
    vlSelf->__PVT__mem_axi_rvalid = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_rready = VL_RAND_RESET_I(1);
    vlSelf->__PVT__mem_axi_rdata = VL_RAND_RESET_I(32);
    vlSelf->__PVT__tests_passed = VL_RAND_RESET_I(1);
    for (int __Vi0 = 0; __Vi0 < 32768; ++__Vi0) {
        vlSelf->memory[__Vi0] = VL_RAND_RESET_I(32);
    }
    vlSelf->__PVT__verbose = VL_RAND_RESET_I(1);
    vlSelf->__PVT__axi_test = VL_RAND_RESET_I(1);
    vlSelf->__PVT__xorshift64_state = VL_RAND_RESET_Q(64);
    vlSelf->__PVT__fast_axi_transaction = VL_RAND_RESET_I(3);
    vlSelf->__PVT__async_axi_transaction = VL_RAND_RESET_I(5);
    vlSelf->__PVT__delay_axi_transaction = VL_RAND_RESET_I(5);
    vlSelf->__PVT__latched_raddr_en = VL_RAND_RESET_I(1);
    vlSelf->__PVT__latched_waddr_en = VL_RAND_RESET_I(1);
    vlSelf->__PVT__latched_wdata_en = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fast_raddr = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fast_waddr = VL_RAND_RESET_I(1);
    vlSelf->__PVT__fast_wdata = VL_RAND_RESET_I(1);
    vlSelf->__PVT__latched_raddr = VL_RAND_RESET_I(32);
    vlSelf->__PVT__latched_waddr = VL_RAND_RESET_I(32);
    vlSelf->__PVT__latched_wdata = VL_RAND_RESET_I(32);
    vlSelf->__PVT__latched_wstrb = VL_RAND_RESET_I(4);
    vlSelf->__PVT__latched_rinsn = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__mem_axi_arready = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__mem_axi_awready = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__mem_axi_wready = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__fast_raddr = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__fast_waddr = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__fast_wdata = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__mem_axi_rvalid = VL_RAND_RESET_I(1);
    vlSelf->__Vdly__mem_axi_bvalid = VL_RAND_RESET_I(1);
    vlSelf->__VdlyVal__memory__v0 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v0 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v0 = 0;
    vlSelf->__VdlyVal__memory__v1 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v1 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v1 = 0;
    vlSelf->__VdlyVal__memory__v2 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v2 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v2 = 0;
    vlSelf->__VdlyVal__memory__v3 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v3 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v3 = 0;
    vlSelf->__VdlyVal__memory__v4 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v4 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v4 = 0;
    vlSelf->__VdlyVal__memory__v5 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v5 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v5 = 0;
    vlSelf->__VdlyVal__memory__v6 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v6 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v6 = 0;
    vlSelf->__VdlyVal__memory__v7 = VL_RAND_RESET_I(8);
    vlSelf->__VdlyDim0__memory__v7 = VL_RAND_RESET_I(15);
    vlSelf->__VdlySet__memory__v7 = 0;
}
