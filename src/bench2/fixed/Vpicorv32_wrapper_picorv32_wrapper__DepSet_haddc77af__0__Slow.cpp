// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vpicorv32_wrapper.h for the primary calling header

#include "Vpicorv32_wrapper__pch.h"
#include "Vpicorv32_wrapper__Syms.h"
#include "Vpicorv32_wrapper_picorv32_wrapper.h"

extern const VlWide<32>/*1023:0*/ Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0;

VL_ATTR_COLD void Vpicorv32_wrapper_picorv32_wrapper___eval_initial__TOP__picorv32_wrapper(Vpicorv32_wrapper_picorv32_wrapper* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpicorv32_wrapper_picorv32_wrapper___eval_initial__TOP__picorv32_wrapper\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlWide<3>/*95:0*/ __Vtemp_1;
    // Body
    __Vtemp_1[0U] = 0x653d2573U;
    __Vtemp_1[1U] = 0x6d776172U;
    __Vtemp_1[2U] = 0x666972U;
    if ((! VL_VALUEPLUSARGS_INW(1024, VL_CVT_PACK_STR_NW(3, __Vtemp_1), 
                                vlSelfRef.__PVT__firmware_file))) {
        vlSelfRef.__PVT__firmware_file[0U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0U];
        vlSelfRef.__PVT__firmware_file[1U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[1U];
        vlSelfRef.__PVT__firmware_file[2U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[2U];
        vlSelfRef.__PVT__firmware_file[3U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[3U];
        vlSelfRef.__PVT__firmware_file[4U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[4U];
        vlSelfRef.__PVT__firmware_file[5U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[5U];
        vlSelfRef.__PVT__firmware_file[6U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[6U];
        vlSelfRef.__PVT__firmware_file[7U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[7U];
        vlSelfRef.__PVT__firmware_file[8U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[8U];
        vlSelfRef.__PVT__firmware_file[9U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[9U];
        vlSelfRef.__PVT__firmware_file[0xaU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0xaU];
        vlSelfRef.__PVT__firmware_file[0xbU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0xbU];
        vlSelfRef.__PVT__firmware_file[0xcU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0xcU];
        vlSelfRef.__PVT__firmware_file[0xdU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0xdU];
        vlSelfRef.__PVT__firmware_file[0xeU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0xeU];
        vlSelfRef.__PVT__firmware_file[0xfU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0xfU];
        vlSelfRef.__PVT__firmware_file[0x10U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x10U];
        vlSelfRef.__PVT__firmware_file[0x11U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x11U];
        vlSelfRef.__PVT__firmware_file[0x12U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x12U];
        vlSelfRef.__PVT__firmware_file[0x13U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x13U];
        vlSelfRef.__PVT__firmware_file[0x14U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x14U];
        vlSelfRef.__PVT__firmware_file[0x15U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x15U];
        vlSelfRef.__PVT__firmware_file[0x16U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x16U];
        vlSelfRef.__PVT__firmware_file[0x17U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x17U];
        vlSelfRef.__PVT__firmware_file[0x18U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x18U];
        vlSelfRef.__PVT__firmware_file[0x19U] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x19U];
        vlSelfRef.__PVT__firmware_file[0x1aU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x1aU];
        vlSelfRef.__PVT__firmware_file[0x1bU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x1bU];
        vlSelfRef.__PVT__firmware_file[0x1cU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x1cU];
        vlSelfRef.__PVT__firmware_file[0x1dU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x1dU];
        vlSelfRef.__PVT__firmware_file[0x1eU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x1eU];
        vlSelfRef.__PVT__firmware_file[0x1fU] = Vpicorv32_wrapper__ConstPool__CONST_hac2bd5b2_0[0x1fU];
    }
    VL_READMEM_N(true, 32, 32768, 0, VL_CVT_PACK_STR_NW(32, vlSelfRef.__PVT__firmware_file)
                 ,  &(vlSymsp->TOP__picorv32_wrapper__mem.memory)
                 , 0, ~0ULL);
}

extern const VlUnpacked<VlWide<4>/*127:0*/, 256> Vpicorv32_wrapper__ConstPool__TABLE_hc6df3ca5_0;

VL_ATTR_COLD void Vpicorv32_wrapper_picorv32_wrapper___stl_sequent__TOP__picorv32_wrapper__0(Vpicorv32_wrapper_picorv32_wrapper* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+      Vpicorv32_wrapper_picorv32_wrapper___stl_sequent__TOP__picorv32_wrapper__0\n"); );
    Vpicorv32_wrapper__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0;
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 = 0;
    CData/*3:0*/ uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0;
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 = 0;
    CData/*7:0*/ __Vtableidx1;
    __Vtableidx1 = 0;
    // Body
    vlSelfRef.__PVT__irq = 0U;
    vlSelfRef.__PVT__irq = ((0xffffffcfU & vlSelfRef.__PVT__irq) 
                            | ((((IData)((0xffffU == (IData)(vlSelfRef.__PVT__count_cycle))) 
                                 << 1U) | (0x1fffU 
                                           == (0x1fffU 
                                               & (IData)(vlSelfRef.__PVT__count_cycle)))) 
                               << 4U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_ready 
        = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_mul_ready) 
           | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_div_ready));
    if ((0U == (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wdata 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2;
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wstrb = 0xfU;
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_word 
            = vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata;
    } else if ((1U == (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wdata 
            = ((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2 
                << 0x10U) | (0xffffU & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2));
        if ((2U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1)) {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wstrb = 0xcU;
            if ((2U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1)) {
                vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_word 
                    = (vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata 
                       >> 0x10U);
            }
        } else {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wstrb = 3U;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_word 
                = (0xffffU & vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata);
        }
    } else if ((2U == (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_wordsize))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wdata 
            = ((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2 
                << 0x18U) | ((0xff0000U & (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2 
                                           << 0x10U)) 
                             | ((0xff00U & (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2 
                                            << 8U)) 
                                | (0xffU & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2))));
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_wstrb 
            = (0xfU & ((IData)(1U) << (3U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1)));
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_word 
            = ((2U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1)
                ? ((1U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1)
                    ? (vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata 
                       >> 0x18U) : (0xffU & (vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata 
                                             >> 0x10U)))
                : ((1U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1)
                    ? (0xffU & (vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata 
                                >> 8U)) : (0xffU & vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata)));
    }
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_rs1 
        = ((0U != (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs1))
            ? ((0x23U >= (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs1))
                ? vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs
               [vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs1]
                : 0U) : 0U);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_rs2 
        = ((0U != (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs2))
            ? vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs
           [vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs2]
            : 0U);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk2__DOT__pcpi_div__DOT__start 
        = ((~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk2__DOT__pcpi_div__DOT__pcpi_wait_q)) 
           & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_div_wait));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_write 
        = ((IData)(vlSymsp->TOP.resetn) & ((~ (IData)(
                                                      (0U 
                                                       != (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_state)))) 
                                           & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_wdata)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__instr_any_mulh 
        = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulh) 
           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhsu) 
              | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__instr_mulhu)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_wr = 0U;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_rd = 0U;
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_mul_ready) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_wr 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_mul_wr;
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_rd 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_mul_rd;
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_div_ready) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_wr 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_div_wr;
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_int_rd 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__pcpi_div_rd;
    }
    __Vtableidx1 = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpu_state;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_state[0U] 
        = Vpicorv32_wrapper__ConstPool__TABLE_hc6df3ca5_0
        [__Vtableidx1][0U];
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_state[1U] 
        = Vpicorv32_wrapper__ConstPool__TABLE_hc6df3ca5_0
        [__Vtableidx1][1U];
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_state[2U] 
        = Vpicorv32_wrapper__ConstPool__TABLE_hc6df3ca5_0
        [__Vtableidx1][2U];
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_state[3U] 
        = Vpicorv32_wrapper__ConstPool__TABLE_hc6df3ca5_0
        [__Vtableidx1][3U];
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_write = 0U;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__is_rdcycle_rdcycleh_rdinstr_rdinstrh 
        = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdcycle) 
           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdcycleh) 
              | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdinstr) 
                 | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdinstrh))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_imm 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__q_insn_imm;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_opcode 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__q_insn_opcode;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rs1 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__q_insn_rs1;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rs2 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__q_insn_rs2;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rd 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__q_insn_rd;
    vlSelfRef.__PVT__mem_axi_rready = ((~ (IData)((0U 
                                                   != (IData)(vlSelfRef.__PVT__uut__DOT__mem_wstrb)))) 
                                       & (IData)(vlSelfRef.__PVT__uut__DOT__mem_valid));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__launch_next_insn 
        = ((0x40U == (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpu_state)) 
           & ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoder_trigger) 
              & ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_delay) 
                 | ((~ (IData)((0U != ((~ vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_mask) 
                                       & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_pending)))) 
                    | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_active)))));
    vlSelfRef.__PVT__mem_axi_bready = ((IData)(vlSelfRef.__PVT__uut__DOT__mem_valid) 
                                       & (0U != (IData)(vlSelfRef.__PVT__uut__DOT__mem_wstrb)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_wrdata = 0U;
    if ((0x40U == (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpu_state))) {
        if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_branch) {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_pc 
                   + ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_compr)
                       ? 2U : 4U));
        } else if (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_store) 
                    & (~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_branch)))) {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_stalu)
                    ? vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_q
                    : vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_out);
        } else if ((1U & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_state))) {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_next_pc 
                   | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_compr));
        } else if ((2U & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_state))) {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_write = 1U;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cpuregs_wrdata 
                = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_pending 
                   & (~ vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_mask));
        }
    }
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__rd;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__rdx;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs1 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__rs1;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs2 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__rs2;
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
        = ((1U & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs1))
            ? vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs2
            : 0ULL);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt = 0ULL;
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd)) 
                   + (0xfU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx))) 
                  + (0xfU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2))) 
                 >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
                    + (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx)) 
                   + (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfffffffffffffff7ULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 3U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffffffffffffff0ULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | (IData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 4U))) + (0xfU 
                                                & (IData)(
                                                          (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                           >> 4U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 4U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 4U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                >> 4U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 4U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xffffffffffffff7fULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 7U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xffffffffffffff0fULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 8U))) + (0xfU 
                                                & (IData)(
                                                          (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                           >> 8U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 8U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 8U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                >> 8U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 8U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfffffffffffff7ffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0xbU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffffffffffff0ffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 8U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0xcU))) + (0xfU 
                                                  & (IData)(
                                                            (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                             >> 0xcU)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0xcU)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0xcU)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                  >> 0xcU))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0xcU))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xffffffffffff7fffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0xfU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xffffffffffff0fffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0xcU));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x10U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x10U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x10U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x10U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x10U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x10U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfffffffffff7ffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x13U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffffffffff0ffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x10U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x14U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x14U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x14U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x14U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x14U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x14U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xffffffffff7fffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x17U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xffffffffff0fffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x14U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x18U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x18U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x18U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x18U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x18U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x18U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfffffffff7ffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x1bU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffffffff0ffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x18U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x1cU))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x1cU)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x1cU)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x1cU)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x1cU))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x1cU))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xffffffff7fffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x1fU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xffffffff0fffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x1cU));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x20U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x20U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x20U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x20U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x20U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x20U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfffffff7ffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x23U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffffff0ffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x20U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x24U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x24U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x24U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x24U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x24U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x24U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xffffff7fffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x27U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xffffff0fffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x24U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x28U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x28U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x28U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x28U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x28U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x28U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfffff7ffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x2bU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffff0ffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x28U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x2cU))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x2cU)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x2cU)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x2cU)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x2cU))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x2cU))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xffff7fffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x2fU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xffff0fffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x2cU));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x30U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x30U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x30U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x30U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x30U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x30U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xfff7ffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x33U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfff0ffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x30U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x34U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x34U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x34U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x34U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x34U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x34U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xff7fffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x37U));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xff0fffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x34U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x38U))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x38U)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x38U)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x38U)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x38U))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x38U))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0xf7ffffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x3bU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xf0ffffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x38U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0 
        = (1U & ((((0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                                    >> 0x3cU))) + (0xfU 
                                                   & (IData)(
                                                             (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                              >> 0x3cU)))) 
                  + (0xfU & (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                                     >> 0x3cU)))) >> 4U));
    uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0 
        = (0xfU & (((IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
                             >> 0x3cU)) + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
                                                   >> 0x3cU))) 
                   + (IData)((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__this_rs2 
                              >> 0x3cU))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt 
        = ((0x7fffffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2f5ee7e8__0)) 
              << 0x3fU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd 
        = ((0xfffffffffffffffULL & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rd) 
           | ((QData)((IData)(uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT____Vconcswap_1_h2e3fb9a0__0)) 
              << 0x3cU));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdx 
        = VL_SHIFTL_QQI(64,64,32, vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rdt, 1U);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs1 
        = VL_SHIFTR_QQI(64,64,32, vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs1, 1U);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs2 
        = VL_SHIFTL_QQI(64,64,32, vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__genblk1__DOT__pcpi_mul__DOT__next_rs2, 1U);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_eq 
        = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
           == vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_lts 
        = VL_LTS_III(32, vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1, vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_ltu 
        = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
           < vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2);
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_trap 
        = (1U & (~ ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lui) 
                    | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_auipc) 
                       | (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_jal) 
                           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_jalr) 
                              | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_beq) 
                                 | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bne) 
                                    | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_blt) 
                                       | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bge) 
                                          | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bltu) 
                                             | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bgeu) 
                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lb) 
                                                   | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lh) 
                                                      | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lw) 
                                                         | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lbu) 
                                                            | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lhu) 
                                                               | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sb) 
                                                                  | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sh) 
                                                                     | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sw) 
                                                                        | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_addi) 
                                                                           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_slti) 
                                                                              | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sltiu) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_xori) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_ori) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_andi) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_slli) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_srli) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_srai) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_add) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sub) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sll) 
                                                                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_slt) 
                                                                                | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sltu)))))))))))))))))))))))))))))) 
                          | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_xor) 
                             | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_srl) 
                                | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sra) 
                                   | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_or) 
                                      | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_and) 
                                         | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdcycle) 
                                            | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdcycleh) 
                                               | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdinstr) 
                                                  | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdinstrh) 
                                                     | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_fence) 
                                                        | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_getq) 
                                                           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_setq) 
                                                              | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_retirq) 
                                                                 | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_maskirq) 
                                                                    | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_timer) 
                                                                       | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_waitirq)))))))))))))))))))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0ULL;
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lui) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6c7569ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_auipc) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6175697063ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_jal) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6a616cULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_jalr) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6a616c72ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_beq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x626571ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bne) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x626e65ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_blt) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x626c74ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bge) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x626765ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bltu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x626c7475ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bgeu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x62676575ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lb) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6c62ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lh) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6c68ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lw) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6c77ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lbu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6c6275ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_lhu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6c6875ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sb) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x7362ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sh) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x7368ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sw) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x7377ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_addi) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x61646469ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_slti) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x736c7469ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sltiu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x736c746975ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_xori) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x786f7269ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_ori) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6f7269ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_andi) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x616e6469ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_slli) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x736c6c69ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_srli) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x73726c69ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_srai) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x73726169ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_add) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x616464ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sub) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x737562ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sll) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x736c6cULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_slt) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x736c74ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sltu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x736c7475ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_xor) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x786f72ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_srl) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x73726cULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sra) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x737261ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_or) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6f72ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_and) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x616e64ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdcycle) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x72646379636c65ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdcycleh) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x72646379636c6568ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdinstr) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x7264696e737472ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_rdinstrh) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x7264696e73747268ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_fence) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x66656e6365ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_getq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x67657471ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_setq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x73657471ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_retirq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x726574697271ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_maskirq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x6d61736b697271ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_waitirq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x77616974697271ULL;
    }
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_timer) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr = 0x74696d6572ULL;
    }
    vlSelfRef.__PVT__uut__DOT__mem_ready = ((IData)(vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_bvalid) 
                                            | (IData)(vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rvalid));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__clear_prefetched_high_word 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__clear_prefetched_high_word_q;
    if ((1U & (~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__prefetched_high_word)))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__clear_prefetched_high_word = 0U;
    }
    if ((1U & (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_branch) 
                | (0U != (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__irq_state))) 
               | (~ (IData)(vlSymsp->TOP.resetn))))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__clear_prefetched_high_word = 1U;
    }
    vlSelfRef.uut__DOT__picorv32_core__DOT____VdfgRegularize_hc635ebbb_0_0 
        = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_prefetch) 
           | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rinst));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__next_pc 
        = (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_branch) 
            & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__latched_store))
            ? (0xfffffffeU & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_out)
            : vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_next_pc);
    vlSelfRef.__PVT__mem_axi_arvalid = ((~ (IData)(vlSelfRef.__PVT__uut__DOT__axi_adapter__DOT__ack_arvalid)) 
                                        & (IData)(vlSelfRef.__PVT__mem_axi_rready));
    vlSelfRef.__PVT__mem_axi_awvalid = ((~ (IData)(vlSelfRef.__PVT__uut__DOT__axi_adapter__DOT__ack_awvalid)) 
                                        & (IData)(vlSelfRef.__PVT__mem_axi_bready));
    vlSelfRef.__PVT__mem_axi_wvalid = ((~ (IData)(vlSelfRef.__PVT__uut__DOT__axi_adapter__DOT__ack_wvalid)) 
                                       & (IData)(vlSelfRef.__PVT__mem_axi_bready));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 = 0U;
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_beq) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_eq;
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bne) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 
            = (1U & (~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_eq)));
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bge) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 
            = (1U & (~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_lts)));
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_bgeu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 
            = (1U & (~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_ltu)));
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__is_slti_blt_slt) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_lts;
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__is_sltiu_bltu_sltu) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_ltu;
    }
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out = 0U;
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__is_lui_auipc_jal_jalr_addi_add_sub) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out 
            = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_sub)
                ? (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
                   - vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2)
                : (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
                   + vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2));
    } else if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__is_compare) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out_0;
    } else if (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_xori) 
                | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_xor))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out 
            = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
               ^ vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2);
    } else if (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_ori) 
                | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_or))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out 
            = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
               | vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2);
    } else if (((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_andi) 
                | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__instr_and))) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__alu_out 
            = (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op1 
               & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__reg_op2);
    }
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_instr 
        = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__q_ascii_instr;
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_next) {
        if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoder_pseudo_trigger_q) {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_imm 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cached_insn_imm;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_opcode 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cached_insn_opcode;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rs1 
                = (0x1fU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cached_insn_rs1));
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rs2 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cached_insn_rs2;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rd 
                = (0x1fU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cached_insn_rd));
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_instr 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__cached_ascii_instr;
        } else {
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_imm 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_imm;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_opcode 
                = ((3U == (3U & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__next_insn_opcode))
                    ? vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__next_insn_opcode
                    : (0xffffU & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__next_insn_opcode));
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rs1 
                = (0x1fU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs1));
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rs2 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rs2;
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_insn_rd 
                = (0x1fU & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__decoded_rd));
            vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__dbg_ascii_instr 
                = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__new_ascii_instr;
        }
    }
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword 
        = ((IData)(vlSelfRef.uut__DOT__picorv32_core__DOT____VdfgRegularize_hc635ebbb_0_0) 
           & ((~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_secondword)) 
              & (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__next_pc 
                 >> 1U)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_use_prefetched_high_word 
        = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword) 
           & ((~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__clear_prefetched_high_word)) 
              & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__prefetched_high_word)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_xfer 
        = (((IData)(vlSelfRef.__PVT__uut__DOT__mem_ready) 
            & (IData)(vlSelfRef.__PVT__uut__DOT__mem_valid)) 
           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_use_prefetched_high_word) 
              & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rinst)));
    if (vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_xfer) {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword_xfer 
            = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__last_mem_valid)
                ? (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword_reg)
                : (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword));
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
            = vlSymsp->TOP__picorv32_wrapper__mem.__PVT__mem_axi_rdata;
    } else {
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword_xfer = 0U;
        vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
            = vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_q;
    }
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched 
        = ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_use_prefetched_high_word)
            ? (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_16bit_buffer)
            : ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_secondword)
                ? ((vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle 
                    << 0x10U) | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_16bit_buffer))
                : ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword)
                    ? VL_SHIFTR_III(32,32,32, vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle, 0x10U)
                    : vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched_noshuffle)));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_done 
        = ((IData)(vlSymsp->TOP.resetn) & ((((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_xfer) 
                                             & ((0U 
                                                 != (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_state)) 
                                                & ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rinst) 
                                                   | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rdata) 
                                                      | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_wdata))))) 
                                            | ((3U 
                                                == (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_state)) 
                                               & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rinst))) 
                                           & ((~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword)) 
                                              | ((~ (IData)(
                                                            (3U 
                                                             == 
                                                             (3U 
                                                              & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched)))) 
                                                 & (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_xfer)))));
    vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_read 
        = ((IData)(vlSymsp->TOP.resetn) & (((~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_use_prefetched_high_word)) 
                                            & ((~ (IData)(
                                                          (0U 
                                                           != (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_state)))) 
                                               & ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rinst) 
                                                  | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_prefetch) 
                                                     | (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_do_rdata))))) 
                                           | ((IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_firstword_xfer) 
                                              & ((~ (IData)(vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_la_secondword)) 
                                                 & (3U 
                                                    == 
                                                    (3U 
                                                     & vlSelfRef.__PVT__uut__DOT__picorv32_core__DOT__mem_rdata_latched))))));
}
