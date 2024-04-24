/*!
    \file    gd32f4xx_libopt.h
    \brief   library optional for gd32f4xx

    \version 2024-01-15, V3.2.0, firmware for GD32F4xx
*/

/*
    Copyright (c) 2024, GigaDevice Semiconductor Inc.

    Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

    1. Redistributions of source code must retain the above copyright notice, this
       list of conditions and the following disclaimer.
    2. Redistributions in binary form must reproduce the above copyright notice,
       this list of conditions and the following disclaimer in the documentation
       and/or other materials provided with the distribution.
    3. Neither the name of the copyright holder nor the names of its contributors
       may be used to endorse or promote products derived from this software without
       specific prior written permission.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY
OF SUCH DAMAGE.
*/

#ifndef GD32F4XX_LIBOPT_H
#define GD32F4XX_LIBOPT_H

#include <config.h>

#if defined (GD32F450) || defined (GD32F405) || defined (GD32F407) || defined (GD32F470) || defined (GD32F425) || defined (GD32F427)

#ifdef CONFIG_GD32F4_RCU
#include "gd32f4xx_rcu.h"
#endif

#ifdef CONFIG_GD32F4_ADC
#include "gd32f4xx_adc.h"
#endif

#ifdef CONFIG_GD32F4_CAN
#include "gd32f4xx_can.h"
#endif 

#ifdef CONFIG_GD32F4_CRC
#include "gd32f4xx_crc.h"
#endif

#ifdef CONFIG_GD32F4_CTC
#include "gd32f4xx_ctc.h"
#endif

#ifdef CONFIG_GD32F4_DAC
#include "gd32f4xx_dac.h"
#endif

#ifdef CONFIG_GD32F4_DBG
#include "gd32f4xx_dbg.h"
#endif

#ifdef CONFIG_GD32F4_DCI
#include "gd32f4xx_dci.h"
#endif

#ifdef CONFIG_GD32F4_DMA
#include "gd32f4xx_dma.h"
#endif

#ifdef CONFIG_GD32F4_EXTI
#include "gd32f4xx_exti.h"
#endif

#ifdef CONFIG_GD32F4_FMC
#include "gd32f4xx_fmc.h"
#endif

#ifdef CONFIG_GD32F4_FWDGT
#include "gd32f4xx_fwdgt.h"
#endif

#ifdef CONFIG_GD32F4_GPIO
#include "gd32f4xx_gpio.h"
#endif

#ifdef CONFIG_GD32F4_SYSCFG
#include "gd32f4xx_syscfg.h"
#endif

#ifdef CONFIG_GD32F4_I2C
#include "gd32f4xx_i2c.h"
#endif 

#ifdef CONFIG_GD32F4_IREF
#include "gd32f4xx_iref.h"
#endif

#ifdef CONFIG_GD32F4_PMU
#include "gd32f4xx_pmu.h"
#endif

#ifdef CONFIG_GD32F4_RTC
#include "gd32f4xx_rtc.h"
#endif

#ifdef CONFIG_GD32F4_SDIO
#include "gd32f4xx_sdio.h"
#endif

#ifdef CONFIG_GD32F4_SPI
#include "gd32f4xx_spi.h"
#endif

#ifdef CONFIG_GD32F4_TIMER
#include "gd32f4xx_timer.h"
#endif

#ifdef CONFIG_GD32F4_TRNG
#include "gd32f4xx_trng.h"
#endif

#ifdef CONFIG_GD32F4_USART
#include "gd32f4xx_usart.h"
#endif

#ifdef CONFIG_GD32F4_WWDGT
#include "gd32f4xx_wwdgt.h"
#endif

#ifdef CONFIG_GD32F4_MISC
#include "gd32f4xx_misc.h"
#endif

#endif /* (GD32F450) || defined (GD32F405) || defined (GD32F407) || defined (GD32F470) || defined (GD32F425) || defined (GD32F427) */
 

#if defined (GD32F450) || defined (GD32F470)

#ifdef CONFIG_GD32F4_ENET
#include "gd32f4xx_enet.h"
#endif

#ifdef CONFIG_GD32F4_EXMC
#include "gd32f4xx_exmc.h"
#endif

#ifdef CONFIG_GD32F4_IPA
#include "gd32f4xx_ipa.h"
#endif

#ifdef CONFIG_GD32F4_TLI
#include "gd32f4xx_tli.h"
#endif 

#endif /* defined (GD32F450) || defined (GD32F470) */


#if defined (GD32F407) || defined (GD32F427)

#ifdef CONFIG_GD32F4_ENET
#include "gd32f4xx_enet.h"
#endif

#ifdef CONFIG_GD32F4_EXMC
#include "gd32f4xx_exmc.h"
#endif

#endif /* defined (GD32F407) || defined (GD32F427) */

#endif /* GD32F4XX_LIBOPT_H */
