/**
  ******************************************************************************
  * @file    event.h 
  * @author  Dang Thanh Tri 
  * @version V1.0
  * @date    11-June-2019
  * @brief   event module
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __EVENT_H
#define __EVENT_H

/* Includes ------------------------------------------------------------------*/
#include "bsp/bsp.h"

#include "sys/sys_task.h"
#include <stdint.h>
/* Exported types ------------------------------------------------------------*/
#define EVENT_NUMBER                             6

struct event_bundle_struct 
{
  uint8_t id;
  void *cb;
};

typedef struct
{
  struct event_bundle_struct bundle[EVENT_NUMBER];
  uint8_t num;
} event_t;

/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
bool event_add_callback(event_t *event, uint8_t name, void *callback);
void event_remove(event_t *event_handler, uint8_t id);
void event_execute(event_t *event, uint8_t name);

#endif /* __EVENT_H */

/******************************** END OF FILE *********************************/
