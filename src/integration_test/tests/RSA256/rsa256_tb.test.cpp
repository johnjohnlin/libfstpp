// SPDX-FileCopyrightText: 2025-2026 Yu-Sheng Lin <johnjohnlys@gmail.com>
// SPDX-FileCopyrightText: 2025-2026 Yoda Lee <lc85301@gmail.com>
// SPDX-License-Identifier: MIT
// direct include
#include "VRSA_tb.h" // Generated header for the Testbench module
// C system headers
// C++ standard library headers
#include <iostream>
#include <memory>
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
    Verilated::commandArgs(argc, argv);

    // Instantiate the Testbench module
    unique_ptr<VRSA_tb> tb(new VRSA_tb);
    unique_ptr<VerilatedFstC> tfp(new VerilatedFstC);

    // Initialize simulation variables
    vluint64_t sim_time = 0;
    tb->clk = 0;
    tb->rst_n = 0;

    Verilated::traceEverOn(true);
    tb->trace(tfp.get(), 99);
    tfp->open(argv[1]);

    // Deassert reset after a few cycles
    while (sim_time < 20) {
        tb->clk = !tb->clk;
        tb->eval();
        tfp->dump(sim_time);
        sim_time++;
    }
    tb->rst_n = 1;

    for (int i = 0; i < 10000; i++) {
        tb->clk = !tb->clk;
        tb->eval();
        tfp->dump(sim_time);
        sim_time++;
        // this value ensures manual flush before auto-flush for THIS test
        // so we can compare our implementation with gtkwave's block-by-block
        if (sim_time % 4000 == 0) {
            tfp->flush();
        }
    }

    // Close trace file
    tfp->close();
    tb->final();

    return 0;
}
