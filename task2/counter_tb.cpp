#include "Vcounter.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

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

    if (vbdOpen()!=1) return -1;
    vbdHeader("Lab 1: Counter");

    top->clk = 1; // initial clock
    top->rst = 1; // reset
    top->en = 0; // disable counter

    // run simulation for 300 cycles
    for (i = 0; i < 300; i++) {

        for (clk = 0; clk < 2; clk++) {
            tfp -> dump(2*i+clk);
            top -> clk = !top ->clk; // evaluate clock
            top ->eval();
        }

        vbdPlot(int(top->count), 0, 255);
        // vbdHex(4, (int(top->count) >> 12) & 0xF);
        // vbdHex(3, (int(top->count) >> 8) & 0xF);
        // vbdHex(2, (int(top->count) >> 4) & 0xF);
        // vbdHex(1, (int(top->count) & 0xF));
        vbdCycle(i+1);

        top->rst = (i < 2) | (i == 15);
        top->en = vbdFlag();

        if (Verilated::gotFinish())
            exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
    
}