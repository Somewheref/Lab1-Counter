#include "Vtop.h"
#include "verilated.h"
#include "verilated_vcd_c.h"
#include "vbuddy.cpp"

int main(int argc, char **argv, char **env) {
    int i;
    int clk;

    Verilated::commandArgs(argc, argv);  // Remember args
    Vtop* top = new Vtop;  // Create instance

    // Tracing
    Verilated::traceEverOn(true);
    VerilatedVcdC* tfp = new VerilatedVcdC;
    top->trace (tfp, 99); // Annotating signals to trace
    tfp->open ("top.vcd"); // Open the dump file

    if (vbdOpen()!=1) return -1;
    vbdHeader("Lab 1: Counter");

    top->clk = 1; // initial clock
    top->rst = 0; // reset

    // run simulation for 300 cycles
    for (i = 0; i < 3000; i++) {

        top -> en = vbdFlag();

        for (clk = 0; clk < 2; clk++) {
            tfp -> dump(2*i+clk);
            top -> clk = !top ->clk; // evaluate clock
            top ->eval();
        }

        vbdHex(4, (int(top->bcd) >> 12) & 0xF);
        vbdHex(3, (int(top->bcd) >> 8) & 0xF);
        vbdHex(2, (int(top->bcd) >> 4) & 0xF);
        vbdHex(1, (int(top->bcd) & 0xF));

        vbdCycle(i+1);

        if (Verilated::gotFinish())
            exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
    
}