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
    top->rst = 0; // reset

    vbdSetMode(1);

    // run simulation for 300 cycles
    for (i = 0; i < 3000; i++) {

        // for (clk = 0; clk < 2; clk++) {
        //     tfp -> dump(2*i+clk);
        //     top -> clk = !top ->clk; // evaluate clock
        //     top ->eval();
        // }

        // if (vbdFlag())
        // {
        //     top -> v = vbdValue();
        //     top -> ld = 1;
        // }
        // else
        // {
        //     top -> ld = 0;
        // }

        // vbdPlot(int(top->count), 0, 255);
        // vbdCycle(i+1);

        // ======== uncomment above code to run with normal clock ========


        // ========= below are code for single stepping =========

        if (vbdFlag())
        {
            for (clk = 0; clk < 2; clk++) {
                tfp -> dump(2*i+clk);
                top -> clk = !top ->clk; // evaluate clock
                top ->eval();
            }

            vbdPlot(int(top->count), 0, 255);
            vbdCycle(i+1);

            i++;
        }

        i--;
        

        if (Verilated::gotFinish())
            exit(0);
    }

    vbdClose();
    tfp->close();
    exit(0);
    
}