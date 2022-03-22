/**
  ******************************************************************************
  * @file    timer.h 
  * @author  Dang Thanh Tri 
  * @version V1.0
  * @date    17-December-2018
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TIMER_H
#define __TIMER_H

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>

/* Exported types ------------------------------------------------------------*/
typedef struct
{
  unsigned short milis;
  unsigned long sec;
} timer_t;

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

timer_t timer_get(void);
timer_t timer_add_sec(timer_t timer, unsigned short sec);
timer_t timer_add_milis(timer_t timer, unsigned short milis);
signed long timer_get_diff_milis(timer_t tim1, timer_t tim2);
signed long timer_get_diff_milis_from_now(timer_t timx);
signed long timer_get_diff_sec(timer_t tim1, timer_t tim2);
signed long timer_get_diff_sec_from_now(timer_t timx);


void timer_handler(void *pv_context);

#endif /* __TIMER_H */

/******************************** END OF FILE *********************************/

