/* --COPYRIGHT--,BSD
 * Copyright (c) 2017, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * --/COPYRIGHT--*/
//******************************************************************************
//  Timer_B, Toggle P1.0, Overflow ISR, 32kHz ACLK
//
//  Description: Toggle P1.0 using software and the Timer_B overflow ISR.
//  In this example an ISR triggers when TB overflows. Inside the ISR P1.0
//  is toggled. Toggle rate is exactly 0.25Hz = [32kHz/FFFFh]/2. Proper use of the
//  TBxIV interrupt vector generator is demonstrated.
//  ACLK = TBCLK = 32kHz, MCLK = SMCLK = default DCO ~ 1.045MHz
//
//  Tested On: MSP430FR2311
//         ---------------
//     /|\|               |
//      | |               |
//      --|RST            |
//        |               |
//        |           P1.0|-->LED
//******************************************************************************
#include "driverlib.h"

void main(void)
{
    //Stop WDT
    WDT_A_hold(WDT_A_BASE);

    //Set P1.0 to output direction
    GPIO_setAsOutputPin(
            GPIO_PORT_P1,
            GPIO_PIN0
            );

    //Disable the GPIO power-on default high-impedance mode to activate
    //previously configured port settings
    PMM_unlockLPM5();

    Timer_B_clearTimerInterrupt(TIMER_B0_BASE);

    Timer_B_initContinuousModeParam param = {0};
    param.clockSource = TIMER_B_CLOCKSOURCE_ACLK;
    param.clockSourceDivider = TIMER_B_CLOCKSOURCE_DIVIDER_1;
    param.timerInterruptEnable_TBIE = TIMER_B_TBIE_INTERRUPT_ENABLE;
    param.timerClear = TIMER_B_DO_CLEAR;
    param.startTimer = false;
    Timer_B_initContinuousMode(TIMER_B0_BASE, &param);

    Timer_B_startCounter(TIMER_B0_BASE,
            TIMER_B_CONTINUOUS_MODE
            );

    __bis_SR_register(LPM3_bits + GIE);       // Enter LPM3, enable interrupts
    __no_operation();                         // For debugger
}

// Timer0_B7 Interrupt Vector (TBxIV) handler
#if defined(__TI_COMPILER_VERSION__) || defined(__IAR_SYSTEMS_ICC__)
#pragma vector=TIMER0_B1_VECTOR
__interrupt
#elif defined(__GNUC__)
__attribute__((interrupt(TIMER0_B1_VECTOR)))
#endif
void TIMER0_B1_ISR(void)
{
    /* Any access, read or write, of the TBxIV register automatically resets the
       highest "pending" interrupt flag. */
    switch( __even_in_range(TB0IV,14) )
    {
        case TBIV__NONE:    break;      // No interrupt
        case TBIV__TBCCR1:  break;      // CCR1 not used
        case TBIV__TBCCR2:  break;      // CCR2 not used
        case TBIV__TBCCR3:  break;      // CCR3 not used
        case TBIV__TBCCR4:  break;      // CCR4 not used
        case TBIV__TBCCR5:  break;      // CCR5 not used
        case TBIV__TBCCR6:  break;      // CCR6 not used
        case TBIV__TBIFG:               // Overflow
                           //Toggle P1.0
                           GPIO_toggleOutputOnPin(
                                   GPIO_PORT_P1,
                                   GPIO_PIN0
                                   );
                           break;
        default: break;
    }
}

