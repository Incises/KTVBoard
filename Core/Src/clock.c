/* Includes ------------------------------------------------------------------*/
#include "clock.h"

#include "ui.h"

/* Private define ------------------------------------------------------------*/


/* Private macro -------------------------------------------------------------*/

extern lv_obj_t * ui_Week;
extern lv_obj_t * ui_SystemDate;
extern lv_obj_t * ui_SystemTime;
extern lv_obj_t * ui_SystemPanel;
/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/


/* Private function prototypes -----------------------------------------------*/
void ui_Clock_Start(void);
static void clock_date_task_callback(lv_timer_t *timer);

/* Private functions ---------------------------------------------------------*/
void ui_Clock_Start(void)
{
  lv_timer_t* task_timer = lv_timer_create(clock_date_task_callback, 200, (void *)&ui_SystemPanel); // Create a scheduled task and refresh it once every 200ms
  if (task_timer == NULL)
  {
      printf("[%s:%d] lv_timer_create failed\n", __FUNCTION__, __LINE__);
  }
}
static void clock_date_task_callback(lv_timer_t *timer)
{
  static const char *week_day[7] = {"Sun.","Mon.","Tue.","Wed.","Thu.","Fri.","Sat."};
  static struct tm *time_info;

	//HAL_PMU_RTC_GetTime(&hpmu, &time);
  
  
  HAL_RTC_GetTime(&hrtc, &sysTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sysDate, RTC_FORMAT_BIN);
  
  
  int year = (sysDate.Year + 2000);
  int month = sysDate.Month;
  int day = sysDate.Date;
  int weekday = sysDate.WeekDay;

  int hour = sysTime.Hours;
  int minutes = sysTime.Minutes;
  int second = sysTime.Seconds;
 
  if (timer != NULL && timer->user_data != NULL)
  {
    if (ui_SystemTime != NULL)
    {
      lv_label_set_text_fmt(ui_SystemTime, "%02d:%02d:%02d", hour, minutes, second);
    }
    if (ui_SystemDate != NULL)
    {
      lv_label_set_text_fmt(ui_SystemDate, "%d-%02d-%02d",year,month,day);
         
    }
    if (ui_Week != NULL)
    {
      lv_label_set_text_fmt(ui_Week, "%s", week_day[weekday%7]);

    }
  }
}
