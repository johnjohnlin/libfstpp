#include "Vpicorv32_wrapper.h"
#include "verilated_fst_c.h"
#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

int main(int argc, char **argv, char **env)
{
    auto tic = high_resolution_clock::now();

    printf("Built with %s %s.\n", Verilated::productName(), Verilated::productVersion());
    printf("Recommended: Verilator 4.0 or later.\n");

    // FST option parsing: last argument must be "1" or "0"
    bool dump_fst = false;
    if (argc > 1 && argv[argc-1][0] == '1') {
		dump_fst = true;
        --argc;
    }

    Verilated::commandArgs(argc, argv);
    Vpicorv32_wrapper* top = new Vpicorv32_wrapper;

    // Tracing (fst)
    VerilatedFstC* tfp = NULL;
    if (dump_fst) {
        Verilated::traceEverOn(true);
        tfp = new VerilatedFstC;
        top->trace (tfp, 99);
        tfp->open("testbench.fst");
    }

    // Tracing (data bus, see showtrace.py)
    FILE *trace_fd = NULL;
    const char* flag_trace = Verilated::commandArgsPlusMatch("trace");
    if (flag_trace && 0==strcmp(flag_trace, "+trace")) {
        trace_fd = fopen("testbench.trace", "w");
    }

    top->clk = 0;
    int t = 0;
    while (!Verilated::gotFinish()) {
        if (t > 200)
            top->resetn = 1;
        top->clk = !top->clk;
        top->eval();
        if (tfp) tfp->dump (t);
        if (trace_fd && top->clk && top->trace_valid) fprintf(trace_fd, "%9.9lx\n", top->trace_data);
        t += 5;
    }
    if (tfp) tfp->close();
    delete top;

    auto toc = high_resolution_clock::now();
    cout << duration_cast<microseconds>(toc-tic).count() << "us" << endl;

    exit(0);
}

