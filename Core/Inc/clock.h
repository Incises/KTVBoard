#ifndef __CLOCK_H
#define __CLOCK_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "rtc.h"

/* Private variables ---------------------------------------------------------*/
extern RTC_TimeTypeDef sysTime;
extern RTC_DateTypeDef sysDate;



/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
void ui_Clock_Start(void);
static void clock_date_task_callback(lv_timer_t *timer);

#endif