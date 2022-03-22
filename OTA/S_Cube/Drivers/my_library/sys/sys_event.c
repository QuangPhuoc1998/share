/**
  ******************************************************************************
  * @file    event.c 
  * @author  Dang Thanh Tri 
  * @version V1.0
  * @date    11-June-2019
  * @brief   event_handler module
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "sys_event.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/


/******************************************************************************/
/*                             				APIs                                    */
/******************************************************************************/

/**
  * @brief  Add new event_handler to a bundle
  * @note   Add id and callback function to event_handler bundle
  * @param  None
  * @retval None.
  */
bool event_add_callback(event_t *event_handler, uint8_t id, void *callback)
{
  if (NULL == callback) { return false; }
  if (EVENT_NUMBER < event_handler->num + 1) { return false; }

  event_handler->bundle[event_handler->num].id = id;
  event_handler->bundle[event_handler->num].cb = callback;
  event_handler->num += 1;
  return true;
}

/**
  * @brief 
  * @param  None
  * @retval None
  */
void event_remove(event_t *event_handler, uint8_t id)
{
	for (short i = event_handler->num - 1; i >= 0; i--)
	{
    if (event_handler->bundle[event_handler->num].id != id)
		{
			continue;
		}

		for (unsigned short j = i; j < event_handler->num - 1; j++)
		{
			event_handler->bundle[j] = event_handler->bundle[j + 1];
		}

		event_handler->num -= 1;
    break;
  }
}

/**
  * @brief  Handle event_handler whenever it occurs
  * @note   .
  * @param  None
  * @retval None
  */
void event_execute(event_t *event_handler, uint8_t id)
{
  for (uint8_t i = 0; i < event_handler->num; i++)
  {
    if (id != event_handler->bundle[i].id) { continue; }
    if (NULL == event_handler->bundle[i].cb) { break; }
    ((void (*)(void *))(event_handler->bundle[i].cb))((void *)&id);
  }
}

/******************************************************************************/
/*                            Module Private APIs                             */
/******************************************************************************/

/******************************************************************************/
/*                             	Module routines                               */
/******************************************************************************/

/******************************************************************************/
/*                         	Module Interrupt Handle                           */
/******************************************************************************/

/******************************** END OF FILE *********************************/


