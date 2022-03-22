/**
  ******************************************************************************
  * @file    task.c 
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
#include "sys_task.h"
#include "sys_timer.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
#define MAX_NUM_OF_TASK								((unsigned short)25)
/* Private variables ---------------------------------------------------------*/
struct
{
	unsigned short num_of_task;
	task_t 	list_of_task[MAX_NUM_OF_TASK];
} tasks;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
/******************************************************************************/
/*                           Module Configuration                             */
/******************************************************************************/
/******************************************************************************/
/*                             Module APIs                                    */
/******************************************************************************/
/**
  * @brief 
  * @param  None
  * @retval None
  */
task_t *task_add(task_mode_t mode, unsigned int timeout, void *callback)
{
	if (tasks.num_of_task >= MAX_NUM_OF_TASK) { return 0; }

	unsigned short new_task_id = tasks.num_of_task;
	tasks.list_of_task[new_task_id].time.start_at = timer_get();
	tasks.list_of_task[new_task_id].time.timeout = timeout;
	tasks.list_of_task[new_task_id].callback = callback;
	tasks.list_of_task[new_task_id].mode = mode;
	tasks.num_of_task += 1;
	return &(tasks.list_of_task[new_task_id]);
}
/**
  * @brief 
  * @param  None
  * @retval None
  */
void task_remove(task_t *task)
{
	for (unsigned short i = 0; i < tasks.num_of_task; i++)
	{
		if (&(tasks.list_of_task[i]) != task)
		{
			continue;
		}
		for (unsigned short j = i; j < tasks.num_of_task - 1; j++)
		{
			tasks.list_of_task[j] = tasks.list_of_task[j + 1];
		}
		tasks.num_of_task -= 1;
		break;
	}
}
/******************************************************************************/
/*                            Module Private APIs                             */
/******************************************************************************/
/******************************************************************************/
/*                             Module routines                                */
/******************************************************************************/
void task_loop(void)
{
	for (unsigned char i = 0; i < tasks.num_of_task; i++)
	{
		if (tasks.list_of_task[i].time.timeout > timer_get_diff_milis_from_now(tasks.list_of_task[i].time.start_at)){ continue;	}
		tasks.list_of_task[i].enabled = true;	
		tasks.list_of_task[i].time.start_at = timer_get();
	}

	for (unsigned char i = 0; i < tasks.num_of_task; i++)
	{
		if (false == tasks.list_of_task[i].enabled) {	continue;	}

		((void (*)(void *))(tasks.list_of_task[i].callback))((void *)&(tasks.list_of_task[i].time.timeout));
		tasks.list_of_task[i].enabled = false;
		
		if (TASK_SINGLE == tasks.list_of_task[i].mode)	
		{
			task_remove(&(tasks.list_of_task[i]));
		}
	}
}
/******************************************************************************/
/*                         Module Interrupt Handle                            */
/******************************************************************************/
/******************************** END OF FILE *********************************/
