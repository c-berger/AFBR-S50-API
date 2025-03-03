/*************************************************************************//**
 * @file
 * @brief       This file is part of the STM32F401RE platform layer.
 * @details     This file provides generic board abstraction.
 *
 * @copyright
 *
 * Copyright (c) 2021, Broadcom Inc
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************/

#include "board/board.h"
#include "board/board_config.h"
#include "driver/s2pi.h"
#include "driver/uart.h"
#include "driver/timer.h"
#include "driver/flash.h"
#include "debug.h" // declaration of print() and error_log()
#include "hal_data.h"

#if defined(_RENESAS_RA_)
#else
#error No appropriate target specified!
#endif


extern void SystemClock_Config(void);


status_t Board_Init(void)
{
    /* Initialize timer required by the API. */
    Timer_Init();

    /* Initialize UART for print functionality. */
    status_t status = UART_Init();
    if (status < STATUS_OK)
    {
        error_log("UART driver initialization failed, error code: %d", status);
        return status;
    }

    /* Initialize the S2PI hardware required by the API. */
    status = S2PI_Init(SPI_DEFAULT_SLAVE, SPI_MAX_BAUDRATE);
    if (status < STATUS_OK)
    {
        error_log("S2PI driver initialization failed, error code: %d", status);
        return status;
    }

    /* Initialize the Flash driver module. */
    status = Flash_Init();
    if (status < STATUS_OK)
    {
        error_log("Flash driver initialization failed, error code: %d", status);
        return status;
    }

    return STATUS_OK;
}

void Board_Reset(void)
{
    NVIC_SystemReset();
}

