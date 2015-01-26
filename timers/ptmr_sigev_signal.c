#include <signal.h>
#include <time.h>
#include "curr_time.h"
#include "itimerspce_from_str.h"

extern "C" {
    #include "tlpi_hdr.h"
}

#define TIMER_SIG SIGRTMAX