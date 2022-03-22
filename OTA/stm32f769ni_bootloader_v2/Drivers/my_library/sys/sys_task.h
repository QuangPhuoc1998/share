/**
  ******************************************************************************
  * @file    task.h 
  * @author  Dang Thanh Tri 
  * @version V1.0
  * @date    17-December-2018
  * @brief   gpio pin for stm32
  *          This file config all required pin used
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __TASK_H
#define __TASK_H
/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>
    
#include "sys_timer.h"

/* Exported types ------------------------------------------------------------*/
typedef enum
{
  TASK_REPEATED = 0,
  TASK_SINGLE   = 1,
} task_mode_t;

typedef void (* callback_t)(void *);

typedef struct
{
  task_mode_t mode;
  struct
  {
    timer_t  start_at;
    unsigned int timeout;
  } time;
  bool enabled;
  callback_t *callback;
} task_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

task_t *task_add(task_mode_t mode, unsigned int timeout, void *callback);
void task_remove(task_t *task);
void task_loop(void);

#endif /* __TASK_H */

/******************************** END OF FILE *********************************/
