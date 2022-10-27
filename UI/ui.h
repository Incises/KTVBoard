// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: KGUI

#ifndef _KGUI_UI_H
#define _KGUI_UI_H

#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

extern lv_obj_t * ui_Screen1;
extern lv_obj_t * ui_BgPanel;
extern lv_obj_t * ui_SoundControllerPanel;
extern lv_obj_t * ui_OnboardMicLabel;
void ui_event_MicSelector(lv_event_t * e);
extern lv_obj_t * ui_MicSelector;
void ui_event_MicSwitch(lv_event_t * e);
extern lv_obj_t * ui_MicSwitch;
void ui_event_MusicMutedSwitch(lv_event_t * e);
extern lv_obj_t * ui_MusicMutedSwitch;
extern lv_obj_t * ui_ExternalMicLabel;
extern lv_obj_t * ui_MicInVolumeLabel;
extern lv_obj_t * ui_MicInVolValue;
extern lv_obj_t * ui_OutputVolumeLabel;
extern lv_obj_t * ui_MusicOutputVolValue;
void ui_event_OutputPlus(lv_event_t * e);
extern lv_obj_t * ui_OutputPlus;
extern lv_obj_t * ui_OutputPlusLabel;
void ui_event_OutputMinus(lv_event_t * e);
extern lv_obj_t * ui_OutputMinus;
extern lv_obj_t * ui_OutputMinusLabel;
void ui_event_MicInPlusButton(lv_event_t * e);
extern lv_obj_t * ui_MicInPlusButton;
extern lv_obj_t * ui_MicInPlusLabel;
void ui_event_MicInMinusButton(lv_event_t * e);
extern lv_obj_t * ui_MicInMinusButton;
extern lv_obj_t * ui_MicInMinusLabel;
extern lv_obj_t * ui_Screen1_Label4;
extern lv_obj_t * ui_SystemPanel;
extern lv_obj_t * ui_TopTitle;
void ui_event_SystemTime(lv_event_t * e);
extern lv_obj_t * ui_SystemTime;
void ui_event_SystemDate(lv_event_t * e);
extern lv_obj_t * ui_SystemDate;
extern lv_obj_t * ui_Week;
extern lv_obj_t * ui_PlayerStatusPanel;
extern lv_obj_t * ui_FileNameLabel;
extern lv_obj_t * ui_FileName;
extern lv_obj_t * ui_StatusLabel;
extern lv_obj_t * ui_StatusVal;
extern lv_obj_t * ui_ModeValue;
extern lv_obj_t * ui_ControllerPanel;
void ui_event_PreviousButton(lv_event_t * e);
extern lv_obj_t * ui_PreviousButton;
extern lv_obj_t * ui_Screen1_Label1;
void ui_event_RecButton(lv_event_t * e);
extern lv_obj_t * ui_RecButton;
void ui_event_NextButton(lv_event_t * e);
extern lv_obj_t * ui_NextButton;
extern lv_obj_t * ui_Screen1_Label2;
void ui_event_PlayingButton(lv_event_t * e);
extern lv_obj_t * ui_PlayingButton;
void ui_event_Screen1_Button3(lv_event_t * e);
extern lv_obj_t * ui_Screen1_Button3;
extern lv_obj_t * ui_Screen1_Label3;
void ui_event_CalendarSelector(lv_event_t * e);
extern lv_obj_t * ui_CalendarSelector;
extern lv_obj_t * ui_TimeSetPanel;
void ui_event_HourPlusButton(lv_event_t * e);
extern lv_obj_t * ui_HourPlusButton;
extern lv_obj_t * ui_HourPlusLabel1;
void ui_event_MinPlusButton(lv_event_t * e);
extern lv_obj_t * ui_MinPlusButton;
extern lv_obj_t * ui_MinPlusLabel;
void ui_event_SecPlusButton(lv_event_t * e);
extern lv_obj_t * ui_SecPlusButton;
extern lv_obj_t * ui_SecondPlusLabel;
void ui_event_CloseTimeSetPanel(lv_event_t * e);
extern lv_obj_t * ui_CloseTimeSetPanel;
extern lv_obj_t * ui_Screen1_Label8;

void ChangeMic(lv_event_t * e);
void MicInMuteUnmute(lv_event_t * e);
void GlobalMute(lv_event_t * e);
void OutputVolPlus(lv_event_t * e);
void OutputVolMinus(lv_event_t * e);
void MicInVolPlus(lv_event_t * e);
void MicInVolMinus(lv_event_t * e);
void PreviousClick(lv_event_t * e);
void RecBeginEnd(lv_event_t * e);
void NextClick(lv_event_t * e);
void PlayPause(lv_event_t * e);
void ModeSwitchFunction(lv_event_t * e);
void ChangeDateCALL(lv_event_t * e);
void HourPlus(lv_event_t * e);
void MinutePlus(lv_event_t * e);
void SecondPlus(lv_event_t * e);





void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
