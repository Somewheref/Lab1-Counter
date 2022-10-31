#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);  // Remember args
    Vcounter* top = new Vcounter;  // Create instance

    // Tracing
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99); // Annotating signals to trace
    tfp->open ("counter.vcd"); // Open the dump file

    top->clk = 1; // initial clock
    top->rst = 0; // reset
    top->en = 1;

    // run simulation for 300 cycles
    for (i = 0; i < 300; i++) {

        for (clk = 0; clk < 2; clk++) {
            tfp -> dump(2*i+clk);
            top -> clk = !top ->clk; // evaluate clock
            top ->eval();
        }
        //top->rst = (i < 2) | (i == 15);
        top -> en = (i <= 7 | i >= 10); // stop counting for 3 cycles when reaching 9

        if (Verilated::gotFinish())
            exit(0);
    }
    tfp->close();
    exit(0);
    
}