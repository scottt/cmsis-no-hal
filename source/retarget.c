/* Copyright (c) 2015 Scott Tsai
 * 
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * 
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission. 
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */


/* This file takes the place of retarget.cpp in mbed-drivers */

#include <cmsis.h>

/* for getpid */
#include <sys/types.h>
#include <unistd.h>

#include <errno.h>

#include <compiler-polyfill/attributes.h>

/* mbed-drivers uses GNU LD's "-wrap,main" mechanism
 * to insert a call to mbed_hal_init() in __wrap_main()
 * The "-Wl,-wrap,main" option is hardcoded by target-mbed-gcc
 * so just use an empty function here to make * the link succeed */
extern int __real_main(void);

int __wrap_main(void) {
    return __real_main();
}

__weak void _exit(int status) {
    (void) status;
    for (;;) {
        __BKPT(0);
    }
}

__weak int _kill(pid_t pid, int sig) {
    (void) pid;
    (void) sig;
    errno = EINVAL;
    return -1;
}

__weak pid_t _getpid(void) {
    return 0;
}

__weak void uvisor_init(void) {
}
