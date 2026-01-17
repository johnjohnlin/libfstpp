// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
// direct include
#include "VSimple.h" // Generated header for the Testbench module
// C system headers
// C++ standard library headers
#include <iostream>
// Other libraries' .h files.
#include <verilated.h>
#include <verilated_fst_c.h> // For FST waveform tracing
// Your project's .h files.

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "Usage: " << argv[0] << " <output.fst>" << endl;
        return 1;
    }
    Verilated::commandArgs(1, argv);

    // Instantiate the Testbench module
    VSimple* tb = new VSimple;

    // Initialize simulation variables
    vluint64_t sim_time = 0;
    tb->clk = 0;
    tb->rst_n = 0;
    VerilatedFstC* tfp = nullptr;

    Verilated::traceEverOn(true);
    tfp = new VerilatedFstC;
    tb->trace(tfp, 99);
    tfp->open(argv[1]);

    // Deassert reset after a few cycles
    while (sim_time < 20) {
        tb->clk = !tb->clk;
        tb->eval();
        if (tfp) tfp->dump(sim_time);
        sim_time++;
    }
    tb->rst_n = 1;

    // magic number, run 100 cycles
    for (int i = 0; i < 150; i++) {
        tb->clk = !tb->clk;
        tb->eval();
        if (tfp) tfp->dump(sim_time);
        sim_time++;
    }

    // Close trace file
    if (tfp) {
        tfp->close();
        delete tfp;
    }

    // Cleanup and exit
    tb->final();
    delete tb;

    return 0;
}
