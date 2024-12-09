#ifndef TIMER_H
#define TIMER_H

#include "systemc.h"

SC_MODULE(timer) {
    sc_in<bool> start;
    sc_out<bool> timeout;
    sc_in<bool> clock;
    int count;

    void runtimer();

    SC_CTOR(timer) {
        SC_CTHREAD(runtimer, clock.pos());  // SC_CTHREAD and clock synch
        reset_signal_is(start, true);  // start synch
        count = 0;
    }
};

#endif
