#include "timer.h"
int sc_main(int argc, char* argv[]) {
    //signals
    sc_signal<bool> start;
    sc_signal<bool> timeout;

    // clock genration
    sc_clock clk("clk", 10, SC_NS);//10ns period

    timer t("t");
    t.clock(clk);
    t.start(start);
    t.timeout(timeout);

    sc_trace_file *wf = sc_create_vcd_trace_file("RESULT");
    sc_trace(wf, clk, "clock");
    sc_trace(wf, start, "start");
    sc_trace(wf, timeout, "timeout");
    sc_trace(wf, t.count, "count");  // trace count signal


    // First reset phase: Reset for 3 cycles
    start.write(false);
    sc_start(30, SC_NS); 

    start.write(true);
    sc_start(10, SC_NS); 
    start.write(false);
    sc_start(30, SC_NS);  // during counting reset the timer before count reaches 0
    start.write(true);
    sc_start(10, SC_NS); 
    start.write(false);
    sc_start(50, SC_NS);  // During counting: Reset after count reaches 0
    start.write(false);  //reset the timer
    sc_start(170, SC_NS);

    sc_close_vcd_trace_file(wf);
    return 0;
}