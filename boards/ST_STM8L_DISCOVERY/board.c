/*
    ChibiOS/RT - Copyright (C) 2006,2007,2008,2009,2010 Giovanni Di Sirio.

    This file is part of ChibiOS/RT.

    ChibiOS/RT is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 3 of the License, or
    (at your option) any later version.

    ChibiOS/RT is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "ch.h"
#include "hal.h"

/*
 * TIM 2 clock after the prescaler.
 */
#define TIM2_CLOCK  (SYSCLK / 16)
#define TIM2_ARR    ((TIM2_CLOCK / CH_FREQUENCY) - 1)

/*
 * Board initialization code.
 */
void hwinit(void) {

  /*
   * HAL initialization.
   */
  halInit();

  /*
   * TIM2 initialization as system tick.
   */
  CLK->PCKENR1 |= CLK_PCKENR1_TIM2;
  TIM2->PSCR    = 4;            /* Prescaler divide by 2^4=16.*/
  TIM2->ARRH    = (uint8_t)(TIM2_ARR >> 8);
  TIM2->ARRL    = (uint8_t)(TIM2_ARR);
  TIM2->CNTRH   = 0;
  TIM2->CNTRL   = 0;
  TIM2->SR1     = 0;
  TIM2->IER     = TIM_IER_UIE;
  TIM2->CR1     = TIM_CR1_CEN;
}