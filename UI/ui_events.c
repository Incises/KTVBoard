// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: KGUI

#include "ui.h"
#include "clock.h"
#include "recorder.h"


extern AUDIO_PLAYBACK_StateTypeDef   AudioState;
extern AUDIO_PLAYER_StateMachine     AudioPlayer;
extern uint8_t flagOutputMuted;
extern uint8_t flagMicInMuted;
extern uint8_t currentMicInVolIndex;
extern uint8_t currentMusicOutVolIndex;

void ChangeDateCALL(lv_event_t * e)
{
  lv_calendar_date_t date;
  if(lv_calendar_get_pressed_date(ui_CalendarSelector, &date))
  {
    lv_calendar_set_today_date(ui_CalendarSelector, date.year, date.month, date.day);
    lv_calendar_set_showed_date(ui_CalendarSelector, date.year, date.month);
    
    RTC_DateTypeDef newDate;
    newDate.Year = date.year - 2000;
    newDate.Month = date.month;
    newDate.Date = date.day;
    newDate.WeekDay = RTC_Get_WeekDay(date.year, date.month, date.day);
    HAL_RTC_SetDate(&hrtc, &newDate, RTC_FORMAT_BIN);
  }
}

void PreviousClick(lv_event_t * e)
{
  if(AudioState != AUDIO_STATE_RECORD && AudioState != AUDIO_STATE_PRERECORD)
    AudioState = AUDIO_STATE_PREVIOUS;
}

void NextClick(lv_event_t * e)
{
  if(AudioState != AUDIO_STATE_RECORD && AudioState != AUDIO_STATE_PRERECORD)
    AudioState = AUDIO_STATE_NEXT;
}

void GlobalMute(lv_event_t * e)
{
	if(flagOutputMuted==0)
    flagOutputMuted = 1;
  else
    flagOutputMuted = 0;
  
}

void HourPlus(lv_event_t * e)
{
  RTC_TimeTypeDef newTime;
  HAL_RTC_GetTime(&hrtc, &sysTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sysDate, RTC_FORMAT_BIN);
  newTime.Hours = (sysTime.Hours+1)%24;
  newTime.Minutes = sysTime.Minutes;
  newTime.Seconds = sysTime.Seconds;

  HAL_RTC_SetTime(&hrtc, &newTime, RTC_FORMAT_BIN);
}

void MinutePlus(lv_event_t * e)
{
  RTC_TimeTypeDef newTime;
  HAL_RTC_GetTime(&hrtc, &sysTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sysDate, RTC_FORMAT_BIN);
  newTime.Hours = sysTime.Hours;
  newTime.Minutes = (sysTime.Minutes+1)%60;
  newTime.Seconds = sysTime.Seconds;

  HAL_RTC_SetTime(&hrtc, &newTime, RTC_FORMAT_BIN);
}

void SecondPlus(lv_event_t * e)
{
  RTC_TimeTypeDef newTime;
  HAL_RTC_GetTime(&hrtc, &sysTime, RTC_FORMAT_BIN);
  HAL_RTC_GetDate(&hrtc, &sysDate, RTC_FORMAT_BIN);
  newTime.Hours = sysTime.Hours;
  newTime.Minutes = sysTime.Minutes;
  newTime.Seconds = (sysTime.Seconds+5)%60;

  HAL_RTC_SetTime(&hrtc, &newTime, RTC_FORMAT_BIN);
}

void PlayPause(lv_event_t * e)
{
  if(AudioPlayer.state == AUDIO_PLAYER_PLAYBACK)
  {
    if(AudioState == AUDIO_STATE_PLAY)
    {
      AudioState = AUDIO_STATE_PAUSE;
      lv_label_set_text_fmt(ui_StatusVal,"  Paused");
    }
    else if(AudioState == AUDIO_STATE_WAIT)
    { 
      AudioState = AUDIO_STATE_RESUME;
      lv_label_set_text_fmt(ui_StatusVal,"  Playing");
    }
  }
}

void ModeSwitchFunction(lv_event_t * e)
{
	if(AudioPlayer.state == AUDIO_PLAYER_WAIT)
  {
    AudioPlayer.state = AUDIO_PLAYER_PLAYBACK;
    BSP_AUDIO_IN_Stop(CODEC_PDWN_SW);
    
    lv_label_set_text_fmt(ui_ModeValue,"MODE: Player");
  }
  else if(AudioPlayer.state == AUDIO_PLAYER_PLAYBACK)
  {
    AUDIO_PLAYER_Stop();

    AudioPlayer.state = AUDIO_PLAYER_IN;
    
    lv_label_set_text_fmt(ui_ModeValue,"MODE: Recorder (KTV)");
    //lv_label_set_text_fmt(ui_FileName,"[FILENAME]");
    lv_label_set_text_fmt(ui_StatusVal,"  IDLE");
  }
  else if(AudioPlayer.state == AUDIO_PLAYER_IN && AudioState == AUDIO_STATE_IDLE )
  {
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_Init();                     //Re-init to default
    lv_label_set_text_fmt(ui_ModeValue,"MODE: Unselected");
    AudioPlayer.state = AUDIO_PLAYER_WAIT;
    lv_label_set_text_fmt(ui_FileName,"[FILENAME]");
  }
  
}

void ChangeMic(lv_event_t * e)
{
	// Your code here
}

void MicInMuteUnmute(lv_event_t * e)
{
  if(flagMicInMuted == 0)
    flagMicInMuted = 1;
  else
    flagMicInMuted = 0;
}

void RecBeginEnd(lv_event_t * e)
{
  if(AudioPlayer.state == AUDIO_PLAYER_IN && AudioState == AUDIO_STATE_IDLE)
  {
    HAL_Delay(50);
    AudioState = AUDIO_STATE_PRERECORD;
  
  }  
  else if(AudioPlayer.state == AUDIO_PLAYER_IN && AudioState == AUDIO_STATE_RECORD)
  {  
    AudioState = AUDIO_STATE_STOP;
    
  }
}

void OutputVolPlus(lv_event_t * e)
{
  if(currentMusicOutVolIndex<11)
    currentMusicOutVolIndex++;
  lv_label_set_text_fmt(ui_MusicOutputVolValue,"%d",currentMusicOutVolIndex+1);
}

void OutputVolMinus(lv_event_t * e)
{
  if(currentMusicOutVolIndex>0)
    currentMusicOutVolIndex--;
  lv_label_set_text_fmt(ui_MusicOutputVolValue,"%d",currentMusicOutVolIndex+1);
}

void MicInVolPlus(lv_event_t * e)
{
  if(currentMicInVolIndex<11)
    currentMicInVolIndex++;
  lv_label_set_text_fmt(ui_MicInVolValue,"%d",currentMicInVolIndex+1);
}

void MicInVolMinus(lv_event_t * e)
{
  if(currentMicInVolIndex>0)
    currentMicInVolIndex--;
  lv_label_set_text_fmt(ui_MicInVolValue,"%d",currentMicInVolIndex+1);
}
