#ifndef SYS_TIMER_H_
#define SYS_TIMER_H_

#include "main.h"

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

#endif 