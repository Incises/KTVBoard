// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.1
// LVGL VERSION: 8.3.3
// PROJECT: KGUI

#include "ui.h"
#include "ui_helpers.h"
#include "ui_comp.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_Screen1;
lv_obj_t * ui_BgPanel;
lv_obj_t * ui_SoundControllerPanel;
lv_obj_t * ui_OnboardMicLabel;
void ui_event_MicSelector(lv_event_t * e);
lv_obj_t * ui_MicSelector;
void ui_event_MicSwitch(lv_event_t * e);
lv_obj_t * ui_MicSwitch;
void ui_event_MusicMutedSwitch(lv_event_t * e);
lv_obj_t * ui_MusicMutedSwitch;
lv_obj_t * ui_ExternalMicLabel;
lv_obj_t * ui_MicInVolumeLabel;
lv_obj_t * ui_MicInVolValue;
lv_obj_t * ui_OutputVolumeLabel;
lv_obj_t * ui_MusicOutputVolValue;
void ui_event_OutputPlus(lv_event_t * e);
lv_obj_t * ui_OutputPlus;
lv_obj_t * ui_OutputPlusLabel;
void ui_event_OutputMinus(lv_event_t * e);
lv_obj_t * ui_OutputMinus;
lv_obj_t * ui_OutputMinusLabel;
void ui_event_MicInPlusButton(lv_event_t * e);
lv_obj_t * ui_MicInPlusButton;
lv_obj_t * ui_MicInPlusLabel;
void ui_event_MicInMinusButton(lv_event_t * e);
lv_obj_t * ui_MicInMinusButton;
lv_obj_t * ui_MicInMinusLabel;
lv_obj_t * ui_Screen1_Label4;
lv_obj_t * ui_SystemPanel;
lv_obj_t * ui_TopTitle;
void ui_event_SystemTime(lv_event_t * e);
lv_obj_t * ui_SystemTime;
void ui_event_SystemDate(lv_event_t * e);
lv_obj_t * ui_SystemDate;
lv_obj_t * ui_Week;
lv_obj_t * ui_PlayerStatusPanel;
lv_obj_t * ui_FileNameLabel;
lv_obj_t * ui_FileName;
lv_obj_t * ui_StatusLabel;
lv_obj_t * ui_StatusVal;
lv_obj_t * ui_ModeValue;
lv_obj_t * ui_ControllerPanel;
void ui_event_PreviousButton(lv_event_t * e);
lv_obj_t * ui_PreviousButton;
lv_obj_t * ui_Screen1_Label1;
void ui_event_RecButton(lv_event_t * e);
lv_obj_t * ui_RecButton;
void ui_event_NextButton(lv_event_t * e);
lv_obj_t * ui_NextButton;
lv_obj_t * ui_Screen1_Label2;
void ui_event_PlayingButton(lv_event_t * e);
lv_obj_t * ui_PlayingButton;
void ui_event_Screen1_Button3(lv_event_t * e);
lv_obj_t * ui_Screen1_Button3;
lv_obj_t * ui_Screen1_Label3;
void ui_event_CalendarSelector(lv_event_t * e);
lv_obj_t * ui_CalendarSelector;
lv_obj_t * ui_TimeSetPanel;
void ui_event_HourPlusButton(lv_event_t * e);
lv_obj_t * ui_HourPlusButton;
lv_obj_t * ui_HourPlusLabel1;
void ui_event_MinPlusButton(lv_event_t * e);
lv_obj_t * ui_MinPlusButton;
lv_obj_t * ui_MinPlusLabel;
void ui_event_SecPlusButton(lv_event_t * e);
lv_obj_t * ui_SecPlusButton;
lv_obj_t * ui_SecondPlusLabel;
void ui_event_CloseTimeSetPanel(lv_event_t * e);
lv_obj_t * ui_CloseTimeSetPanel;
lv_obj_t * ui_Screen1_Label8;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void ui_event_MicSelector(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ChangeMic(e);
    }
}
void ui_event_MicSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        MicInMuteUnmute(e);
    }
}
void ui_event_MusicMutedSwitch(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        GlobalMute(e);
    }
}
void ui_event_OutputPlus(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        OutputVolPlus(e);
    }
}
void ui_event_OutputMinus(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        OutputVolMinus(e);
    }
}
void ui_event_MicInPlusButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        MicInVolPlus(e);
    }
}
void ui_event_MicInMinusButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        MicInVolMinus(e);
    }
}
void ui_event_SystemTime(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_TimeSetPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_SystemDate(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_CalendarSelector, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_REMOVE);
    }
}
void ui_event_PreviousButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        PreviousClick(e);
    }
}
void ui_event_RecButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        RecBeginEnd(e);
    }
}
void ui_event_NextButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        NextClick(e);
    }
}
void ui_event_PlayingButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        PlayPause(e);
    }
}
void ui_event_Screen1_Button3(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        ModeSwitchFunction(e);
    }
}
void ui_event_CalendarSelector(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_VALUE_CHANGED) {
        ChangeDateCALL(e);
        _ui_flag_modify(ui_CalendarSelector, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}
void ui_event_HourPlusButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        HourPlus(e);
    }
}
void ui_event_MinPlusButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        MinutePlus(e);
    }
}
void ui_event_SecPlusButton(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        SecondPlus(e);
    }
}
void ui_event_CloseTimeSetPanel(lv_event_t * e)
{
    lv_event_code_t event_code = lv_event_get_code(e);
    lv_obj_t * target = lv_event_get_target(e);
    if(event_code == LV_EVENT_CLICKED) {
        _ui_flag_modify(ui_TimeSetPanel, LV_OBJ_FLAG_HIDDEN, _UI_MODIFY_FLAG_ADD);
    }
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_BgPanel = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_BgPanel, 480);
    lv_obj_set_height(ui_BgPanel, 272);
    lv_obj_set_align(ui_BgPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_BgPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_BgPanel, lv_color_hex(0xFFFBFE), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_BgPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_BgPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SoundControllerPanel = lv_obj_create(ui_BgPanel);
    lv_obj_set_width(ui_SoundControllerPanel, 199);
    lv_obj_set_height(ui_SoundControllerPanel, 203);
    lv_obj_set_x(ui_SoundControllerPanel, -133);
    lv_obj_set_y(ui_SoundControllerPanel, 17);
    lv_obj_set_align(ui_SoundControllerPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_SoundControllerPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SoundControllerPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SoundControllerPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_OnboardMicLabel = lv_label_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_OnboardMicLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_OnboardMicLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_OnboardMicLabel, -11);
    lv_obj_set_y(ui_OnboardMicLabel, 13);
    lv_obj_set_align(ui_OnboardMicLabel, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_OnboardMicLabel, "On-board\nMic");
    lv_obj_set_style_text_color(ui_OnboardMicLabel, lv_color_hex(0x4A348B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_OnboardMicLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_OnboardMicLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicSelector = lv_switch_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MicSelector, 50);
    lv_obj_set_height(ui_MicSelector, 25);
    lv_obj_set_x(ui_MicSelector, 3);
    lv_obj_set_y(ui_MicSelector, 82);
    lv_obj_set_align(ui_MicSelector, LV_ALIGN_CENTER);

    lv_obj_set_style_bg_color(ui_MicSelector, lv_color_hex(0xF5A9B8), LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MicSelector, 255, LV_PART_INDICATOR | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_MicSelector, lv_color_hex(0x5BCEFA), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_opa(ui_MicSelector, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);

    ui_MicSwitch = lv_switch_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MicSwitch, 50);
    lv_obj_set_height(ui_MicSwitch, 25);
    lv_obj_set_x(ui_MicSwitch, 10);
    lv_obj_set_y(ui_MicSwitch, -2);
    lv_obj_add_state(ui_MicSwitch, LV_STATE_CHECKED);       /// States

    ui_MusicMutedSwitch = lv_switch_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MusicMutedSwitch, 50);
    lv_obj_set_height(ui_MusicMutedSwitch, 25);
    lv_obj_set_x(ui_MusicMutedSwitch, -4);
    lv_obj_set_y(ui_MusicMutedSwitch, -2);
    lv_obj_set_align(ui_MusicMutedSwitch, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_state(ui_MusicMutedSwitch, LV_STATE_CHECKED);       /// States

    ui_ExternalMicLabel = lv_label_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_ExternalMicLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ExternalMicLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ExternalMicLabel, 10);
    lv_obj_set_y(ui_ExternalMicLabel, 14);
    lv_obj_set_align(ui_ExternalMicLabel, LV_ALIGN_BOTTOM_RIGHT);
    lv_label_set_text(ui_ExternalMicLabel, "External\nMic");
    lv_obj_set_style_text_color(ui_ExternalMicLabel, lv_color_hex(0x4A348B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_ExternalMicLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_ExternalMicLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicInVolumeLabel = lv_label_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MicInVolumeLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MicInVolumeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MicInVolumeLabel, -45);
    lv_obj_set_y(ui_MicInVolumeLabel, -40);
    lv_obj_set_align(ui_MicInVolumeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MicInVolumeLabel, "Mic-in\nVolume");
    lv_obj_set_style_text_color(ui_MicInVolumeLabel, lv_color_hex(0x21005E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_MicInVolumeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_MicInVolumeLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicInVolValue = lv_label_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MicInVolValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MicInVolValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MicInVolValue, -47);
    lv_obj_set_y(ui_MicInVolValue, -14);
    lv_obj_set_align(ui_MicInVolValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MicInVolValue, "10");

    ui_OutputVolumeLabel = lv_label_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_OutputVolumeLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_OutputVolumeLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_OutputVolumeLabel, 54);
    lv_obj_set_y(ui_OutputVolumeLabel, -40);
    lv_obj_set_align(ui_OutputVolumeLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_OutputVolumeLabel, "Music\nVolume");
    lv_obj_set_style_text_color(ui_OutputVolumeLabel, lv_color_hex(0x21005E), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_OutputVolumeLabel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_OutputVolumeLabel, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MusicOutputVolValue = lv_label_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MusicOutputVolValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MusicOutputVolValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_MusicOutputVolValue, 52);
    lv_obj_set_y(ui_MusicOutputVolValue, -14);
    lv_obj_set_align(ui_MusicOutputVolValue, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MusicOutputVolValue, "10");

    ui_OutputPlus = lv_btn_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_OutputPlus, 28);
    lv_obj_set_height(ui_OutputPlus, 28);
    lv_obj_set_x(ui_OutputPlus, 5);
    lv_obj_set_y(ui_OutputPlus, 15);
    lv_obj_set_align(ui_OutputPlus, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_OutputPlus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_OutputPlus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_OutputPlus, lv_color_hex(0x4F378B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_OutputPlus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_OutputPlusLabel = lv_label_create(ui_OutputPlus);
    lv_obj_set_width(ui_OutputPlusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_OutputPlusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_OutputPlusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_OutputPlusLabel, "+");
    lv_obj_set_style_text_font(ui_OutputPlusLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_OutputMinus = lv_btn_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_OutputMinus, 28);
    lv_obj_set_height(ui_OutputMinus, 28);
    lv_obj_set_x(ui_OutputMinus, -30);
    lv_obj_set_y(ui_OutputMinus, 15);
    lv_obj_set_align(ui_OutputMinus, LV_ALIGN_RIGHT_MID);
    lv_obj_add_flag(ui_OutputMinus, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_OutputMinus, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_OutputMinus, lv_color_hex(0xD0BCFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_OutputMinus, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_OutputMinusLabel = lv_label_create(ui_OutputMinus);
    lv_obj_set_width(ui_OutputMinusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_OutputMinusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_OutputMinusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_OutputMinusLabel, "-");
    lv_obj_set_style_text_font(ui_OutputMinusLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicInPlusButton = lv_btn_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MicInPlusButton, 28);
    lv_obj_set_height(ui_MicInPlusButton, 28);
    lv_obj_set_x(ui_MicInPlusButton, 35);
    lv_obj_set_y(ui_MicInPlusButton, 15);
    lv_obj_set_align(ui_MicInPlusButton, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_MicInPlusButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MicInPlusButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MicInPlusButton, lv_color_hex(0x4F378B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MicInPlusButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicInPlusLabel = lv_label_create(ui_MicInPlusButton);
    lv_obj_set_width(ui_MicInPlusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MicInPlusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MicInPlusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MicInPlusLabel, "+");
    lv_obj_set_style_text_font(ui_MicInPlusLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicInMinusButton = lv_btn_create(ui_SoundControllerPanel);
    lv_obj_set_width(ui_MicInMinusButton, 28);
    lv_obj_set_height(ui_MicInMinusButton, 28);
    lv_obj_set_x(ui_MicInMinusButton, 0);
    lv_obj_set_y(ui_MicInMinusButton, 15);
    lv_obj_set_align(ui_MicInMinusButton, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_MicInMinusButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MicInMinusButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MicInMinusButton, lv_color_hex(0xD0BCFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MicInMinusButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MicInMinusLabel = lv_label_create(ui_MicInMinusButton);
    lv_obj_set_width(ui_MicInMinusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MicInMinusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MicInMinusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MicInMinusLabel, "-");
    lv_obj_set_style_text_font(ui_MicInMinusLabel, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Label4 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Screen1_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Screen1_Label4, -4);
    lv_obj_set_y(ui_Screen1_Label4, 29);
    lv_obj_set_align(ui_Screen1_Label4, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_Screen1_Label4, "Ding Zhengchao 19211036");

    ui_SystemPanel = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_SystemPanel, 480);
    lv_obj_set_height(ui_SystemPanel, 24);
    lv_obj_set_align(ui_SystemPanel, LV_ALIGN_TOP_MID);
    lv_obj_clear_flag(ui_SystemPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_SystemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_SystemPanel, lv_color_hex(0x4F378B), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SystemPanel, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_SystemPanel, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TopTitle = lv_label_create(ui_SystemPanel);
    lv_obj_set_width(ui_TopTitle, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_TopTitle, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_TopTitle, LV_ALIGN_CENTER);
    lv_label_set_text(ui_TopTitle, "Karaoke Board");
    lv_obj_set_style_text_color(ui_TopTitle, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_TopTitle, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SystemTime = lv_label_create(ui_SystemPanel);
    lv_obj_set_width(ui_SystemTime, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SystemTime, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SystemTime, 6);
    lv_obj_set_y(ui_SystemTime, 0);
    lv_obj_set_align(ui_SystemTime, LV_ALIGN_RIGHT_MID);
    lv_label_set_text(ui_SystemTime, "00:00:00");
    lv_obj_add_flag(ui_SystemTime, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_SystemTime, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SystemTime, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SystemDate = lv_label_create(ui_SystemPanel);
    lv_obj_set_width(ui_SystemDate, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SystemDate, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_SystemDate, -6);
    lv_obj_set_y(ui_SystemDate, 0);
    lv_obj_set_align(ui_SystemDate, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_SystemDate, "2022-10-13");
    lv_obj_add_flag(ui_SystemDate, LV_OBJ_FLAG_CLICKABLE);     /// Flags
    lv_obj_set_style_text_color(ui_SystemDate, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_SystemDate, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Week = lv_label_create(ui_SystemPanel);
    lv_obj_set_width(ui_Week, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Week, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Week, 78);
    lv_obj_set_y(ui_Week, 0);
    lv_obj_set_align(ui_Week, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_Week, "THU");
    lv_obj_set_style_text_color(ui_Week, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Week, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PlayerStatusPanel = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_PlayerStatusPanel, 250);
    lv_obj_set_height(ui_PlayerStatusPanel, 154);
    lv_obj_set_x(ui_PlayerStatusPanel, 104);
    lv_obj_set_y(ui_PlayerStatusPanel, 1);
    lv_obj_set_align(ui_PlayerStatusPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_PlayerStatusPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_FileNameLabel = lv_label_create(ui_PlayerStatusPanel);
    lv_obj_set_width(ui_FileNameLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_FileNameLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_FileNameLabel, -8);
    lv_obj_set_y(ui_FileNameLabel, 0);
    lv_label_set_text(ui_FileNameLabel, "File Name:");

    ui_FileName = lv_label_create(ui_PlayerStatusPanel);
    lv_obj_set_width(ui_FileName, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_FileName, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_FileName, 77);
    lv_obj_set_y(ui_FileName, 0);
    lv_label_set_text(ui_FileName, "[FILENAME]");

    ui_StatusLabel = lv_label_create(ui_PlayerStatusPanel);
    lv_obj_set_width(ui_StatusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StatusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StatusLabel, -7);
    lv_obj_set_y(ui_StatusLabel, -28);
    lv_obj_set_align(ui_StatusLabel, LV_ALIGN_LEFT_MID);
    lv_label_set_text(ui_StatusLabel, "Status:");

    ui_StatusVal = lv_label_create(ui_PlayerStatusPanel);
    lv_obj_set_width(ui_StatusVal, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_StatusVal, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_StatusVal, -12);
    lv_obj_set_y(ui_StatusVal, 24);
    lv_obj_set_align(ui_StatusVal, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_StatusVal, "IDLE");

    ui_ModeValue = lv_label_create(ui_PlayerStatusPanel);
    lv_obj_set_width(ui_ModeValue, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_ModeValue, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_ModeValue, -4);
    lv_obj_set_y(ui_ModeValue, 7);
    lv_obj_set_align(ui_ModeValue, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_ModeValue, "MODE: Unselected");

    ui_ControllerPanel = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_ControllerPanel, 250);
    lv_obj_set_height(ui_ControllerPanel, 42);
    lv_obj_set_x(ui_ControllerPanel, 103);
    lv_obj_set_y(ui_ControllerPanel, 107);
    lv_obj_set_align(ui_ControllerPanel, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_ControllerPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_PreviousButton = lv_btn_create(ui_ControllerPanel);
    lv_obj_set_width(ui_PreviousButton, 32);
    lv_obj_set_height(ui_PreviousButton, 30);
    lv_obj_set_x(ui_PreviousButton, -47);
    lv_obj_set_y(ui_PreviousButton, 0);
    lv_obj_set_align(ui_PreviousButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PreviousButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_PreviousButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Label1 = lv_label_create(ui_PreviousButton);
    lv_obj_set_width(ui_Screen1_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label1, "<");
    lv_obj_set_style_text_font(ui_Screen1_Label1, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RecButton = lv_btn_create(ui_ControllerPanel);
    lv_obj_set_width(ui_RecButton, 32);
    lv_obj_set_height(ui_RecButton, 30);
    lv_obj_set_x(ui_RecButton, 101);
    lv_obj_set_y(ui_RecButton, 0);
    lv_obj_set_align(ui_RecButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_RecButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_RecButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_RecButton, 20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_RecButton, lv_color_hex(0xFC0101), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RecButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui_RecButton, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui_RecButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui_RecButton, 3, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui_RecButton, LV_BORDER_SIDE_FULL, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_color(ui_RecButton, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_opa(ui_RecButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_width(ui_RecButton, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_outline_pad(ui_RecButton, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_NextButton = lv_btn_create(ui_ControllerPanel);
    lv_obj_set_width(ui_NextButton, 32);
    lv_obj_set_height(ui_NextButton, 30);
    lv_obj_set_x(ui_NextButton, 33);
    lv_obj_set_y(ui_NextButton, 0);
    lv_obj_set_align(ui_NextButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_NextButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_NextButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Label2 = lv_label_create(ui_NextButton);
    lv_obj_set_width(ui_Screen1_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label2, ">");
    lv_obj_set_style_text_font(ui_Screen1_Label2, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_PlayingButton = lv_btn_create(ui_ControllerPanel);
    lv_obj_set_width(ui_PlayingButton, 32);
    lv_obj_set_height(ui_PlayingButton, 30);
    lv_obj_set_x(ui_PlayingButton, -7);
    lv_obj_set_y(ui_PlayingButton, 0);
    lv_obj_set_align(ui_PlayingButton, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_PlayingButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_PlayingButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Button3 = lv_btn_create(ui_ControllerPanel);
    lv_obj_set_width(ui_Screen1_Button3, 34);
    lv_obj_set_height(ui_Screen1_Button3, 31);
    lv_obj_set_x(ui_Screen1_Button3, -9);
    lv_obj_set_y(ui_Screen1_Button3, -1);
    lv_obj_set_align(ui_Screen1_Button3, LV_ALIGN_LEFT_MID);
    lv_obj_add_flag(ui_Screen1_Button3, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_Screen1_Button3, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_Screen1_Button3, 4, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_Screen1_Button3, lv_color_hex(0x2962FF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen1_Button3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Screen1_Label3 = lv_label_create(ui_Screen1_Button3);
    lv_obj_set_width(ui_Screen1_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label3, "M");
    lv_obj_set_style_text_font(ui_Screen1_Label3, &lv_font_montserrat_20, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_CalendarSelector = lv_calendar_create(ui_Screen1);
    lv_calendar_set_today_date(ui_CalendarSelector, 2022, 10, 13);
    lv_calendar_set_showed_date(ui_CalendarSelector, 2022, 10);
    lv_obj_t * ui_CalendarSelector_header = lv_calendar_header_arrow_create(ui_CalendarSelector);
    lv_obj_set_width(ui_CalendarSelector, 230);
    lv_obj_set_height(ui_CalendarSelector, 237);
    lv_obj_set_x(ui_CalendarSelector, -122);
    lv_obj_set_y(ui_CalendarSelector, 13);
    lv_obj_set_align(ui_CalendarSelector, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_CalendarSelector, LV_OBJ_FLAG_HIDDEN);     /// Flags

    ui_TimeSetPanel = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_TimeSetPanel, 139);
    lv_obj_set_height(ui_TimeSetPanel, 116);
    lv_obj_set_x(ui_TimeSetPanel, 174);
    lv_obj_set_y(ui_TimeSetPanel, -54);
    lv_obj_set_align(ui_TimeSetPanel, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_TimeSetPanel, LV_OBJ_FLAG_HIDDEN);     /// Flags
    lv_obj_clear_flag(ui_TimeSetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_HourPlusButton = lv_btn_create(ui_TimeSetPanel);
    lv_obj_set_width(ui_HourPlusButton, 30);
    lv_obj_set_height(ui_HourPlusButton, 30);
    lv_obj_set_x(ui_HourPlusButton, -5);
    lv_obj_set_y(ui_HourPlusButton, -4);
    lv_obj_add_flag(ui_HourPlusButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_HourPlusButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_HourPlusButton, lv_color_hex(0x768FFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_HourPlusButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_HourPlusLabel1 = lv_label_create(ui_HourPlusButton);
    lv_obj_set_width(ui_HourPlusLabel1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_HourPlusLabel1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_HourPlusLabel1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_HourPlusLabel1, "H");

    ui_MinPlusButton = lv_btn_create(ui_TimeSetPanel);
    lv_obj_set_width(ui_MinPlusButton, 30);
    lv_obj_set_height(ui_MinPlusButton, 30);
    lv_obj_set_x(ui_MinPlusButton, 1);
    lv_obj_set_y(ui_MinPlusButton, -4);
    lv_obj_set_align(ui_MinPlusButton, LV_ALIGN_TOP_MID);
    lv_obj_add_flag(ui_MinPlusButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_MinPlusButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_MinPlusButton, lv_color_hex(0x768FFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_MinPlusButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_MinPlusLabel = lv_label_create(ui_MinPlusButton);
    lv_obj_set_width(ui_MinPlusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_MinPlusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_MinPlusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_MinPlusLabel, "M");

    ui_SecPlusButton = lv_btn_create(ui_TimeSetPanel);
    lv_obj_set_width(ui_SecPlusButton, 30);
    lv_obj_set_height(ui_SecPlusButton, 30);
    lv_obj_set_x(ui_SecPlusButton, 7);
    lv_obj_set_y(ui_SecPlusButton, -4);
    lv_obj_set_align(ui_SecPlusButton, LV_ALIGN_TOP_RIGHT);
    lv_obj_add_flag(ui_SecPlusButton, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_SecPlusButton, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_SecPlusButton, lv_color_hex(0x768FFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_SecPlusButton, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_SecondPlusLabel = lv_label_create(ui_SecPlusButton);
    lv_obj_set_width(ui_SecondPlusLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_SecondPlusLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_SecondPlusLabel, LV_ALIGN_CENTER);
    lv_label_set_text(ui_SecondPlusLabel, "S");

    ui_CloseTimeSetPanel = lv_btn_create(ui_TimeSetPanel);
    lv_obj_set_width(ui_CloseTimeSetPanel, 71);
    lv_obj_set_height(ui_CloseTimeSetPanel, 35);
    lv_obj_set_x(ui_CloseTimeSetPanel, 0);
    lv_obj_set_y(ui_CloseTimeSetPanel, 2);
    lv_obj_set_align(ui_CloseTimeSetPanel, LV_ALIGN_BOTTOM_MID);
    lv_obj_add_flag(ui_CloseTimeSetPanel, LV_OBJ_FLAG_SCROLL_ON_FOCUS);     /// Flags
    lv_obj_clear_flag(ui_CloseTimeSetPanel, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Screen1_Label8 = lv_label_create(ui_CloseTimeSetPanel);
    lv_obj_set_width(ui_Screen1_Label8, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Screen1_Label8, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_align(ui_Screen1_Label8, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Screen1_Label8, "OK");

    lv_obj_add_event_cb(ui_MicSelector, ui_event_MicSelector, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MicSwitch, ui_event_MicSwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MusicMutedSwitch, ui_event_MusicMutedSwitch, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_OutputPlus, ui_event_OutputPlus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_OutputMinus, ui_event_OutputMinus, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MicInPlusButton, ui_event_MicInPlusButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MicInMinusButton, ui_event_MicInMinusButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SystemTime, ui_event_SystemTime, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SystemDate, ui_event_SystemDate, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PreviousButton, ui_event_PreviousButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_RecButton, ui_event_RecButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_NextButton, ui_event_NextButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_PlayingButton, ui_event_PlayingButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_Screen1_Button3, ui_event_Screen1_Button3, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CalendarSelector, ui_event_CalendarSelector, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_HourPlusButton, ui_event_HourPlusButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_MinPlusButton, ui_event_MinPlusButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_SecPlusButton, ui_event_SecPlusButton, LV_EVENT_ALL, NULL);
    lv_obj_add_event_cb(ui_CloseTimeSetPanel, ui_event_CloseTimeSetPanel, LV_EVENT_ALL, NULL);

}

void ui_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}
