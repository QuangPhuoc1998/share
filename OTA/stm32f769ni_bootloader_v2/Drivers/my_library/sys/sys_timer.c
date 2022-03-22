/**
  ******************************************************************************
  * @file    timer.c 
  * @author  Dang Thanh Tri 
  * @version V1.0
  * @date    17-December-2018
  * @brief   
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "sys_timer.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
timer_t timer;

/* Private function prototypes -----------------------------------------------*/

/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*                           Module Configuration                             */
/******************************************************************************/
/******************************************************************************/
/*                             Module APIs                                    */
/******************************************************************************/

timer_t timer_get(void)
{
  return timer;
}

timer_t timer_add_sec(timer_t timer, unsigned short sec)
{
  timer_t _timer_added;
  _timer_added.sec = timer.sec + sec;
  return _timer_added;
}

timer_t timer_add_milis(timer_t timer, unsigned short milis)
{
  timer_t _timer_added;
  _timer_added.sec = timer.sec + milis / 1000;
  _timer_added.milis = timer.milis + milis % 1000;
  if (_timer_added.milis >= 1000)
  {
    _timer_added.sec += 1;
    _timer_added.milis %= 1000; 
  }
  else
  {
  }
  return _timer_added;
}

signed long timer_get_diff_milis(timer_t tim1, timer_t tim2)
{
  signed long _diff_milis;
  // check fail condition
  // get time in milisecond
  _diff_milis = (tim1.sec - tim2.sec) * 1000 +  // second to milis
                  tim1.milis - tim2.milis;      // milis
  return _diff_milis;
}

signed long timer_get_diff_milis_from_now(timer_t timx)
{
  signed long _diff_milis;
  // check fail condition
  // get time in milisecond
  _diff_milis = (timer.sec - timx.sec) * 1000 +  // second to milis
                  timer.milis - timx.milis;      // milis

  return _diff_milis;
}

signed long timer_get_diff_sec(timer_t tim1, timer_t tim2)
{
  signed long _diff_sec;
  // check fail condition
  // get time in second
  _diff_sec = tim1.sec - tim2.sec;
  
  return _diff_sec;
}

signed long timer_get_diff_sec_from_now(timer_t timx)
{
  signed long _diff_sec;
  // check fail condition
  // get time in second
  _diff_sec = timer.sec - timx.sec;
  
  return _diff_sec;
}

/******************************************************************************/
/*                            Module Private APIs                             */
/******************************************************************************/



/******************************************************************************/
/*                             Module routines                                */
/******************************************************************************/



/******************************************************************************/
/*                         Module Interrupt Handle                            */
/******************************************************************************/
void timer_handler(void *pv_context)
{
  // update timer;
  timer.milis += 1;

  // check milisecond timeout
  if (timer.milis < 1000){ return; }

  // update second if milisecond reach its limit
  timer.sec += 1;
  timer.milis = 0;

  (void)pv_context;
}
/******************************** END OF FILE *********************************/

