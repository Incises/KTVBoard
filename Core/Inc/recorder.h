#ifndef __RECORDER_H
#define __RECORDER_H

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "fatfs.h"
#include "ui.h"
#include "tim.h"
/* Exported constants --------------------------------------------------------*/

#define AUDIO_OUT_BUFFER_SIZE                      256*2*8    /* buffer size in 2 bytes   (2*8bit)  */
#define AUDIO_IN_PCM_BUFFER_SIZE                   256*2*8    /* buffer size in half-word (16bit) */

#define FILEMGR_LIST_DEPDTH                        24
#define FILEMGR_FILE_NAME_SIZE                     40
#define FILEMGR_FULL_PATH_SIZE                     256
#define FILEMGR_MAX_LEVEL                          4    
#define FILETYPE_DIR                               0
#define FILETYPE_FILE                              1

#define DEFAULT_TIME_REC                      600  /* Recording time in second (default: 600s) */

#define REC_FILENAME_PREFIX       "REC"
#define REC_FILENAME_EXTENSION    ".WAV"

#define MAXIMUM_RECORDING_FILES   100

#define REC_FREQ_DEFAULT              SAI_AUDIO_FREQUENCY_48K
#define DEFAULT_AUDIO_IN_BIT_DEPTH    ((uint8_t)16)


#define REC_SAMPLE_LENGTH   (DEFAULT_TIME_REC * REC_FREQ_DEFAULT * DEFAULT_AUDIO_IN_CHANNEL_NBR * 2)


/* Exported types ------------------------------------------------------------*/



/* Application State Machine Structure */
typedef enum {
  APPLICATION_IDLE = 0,  
  APPLICATION_START,   
  APPLICATION_READY,
  APPLICATION_DISCONNECT,
}AUDIO_ApplicationTypeDef;
    
/* Audio Player State Structure */    
typedef enum {
  AUDIO_PLAYER_IDLE = 0,
  AUDIO_PLAYER_WAIT,  
  AUDIO_PLAYER_EXPLORE,
  AUDIO_PLAYER_PLAYBACK,
  AUDIO_PLAYER_IN,        // RECORDING
}AUDIO_Player_State;

/* Audio Player State Machine Structure */
typedef struct _PlayerStateMachine {
  __IO AUDIO_Player_State state;
  __IO uint8_t select;  
}AUDIO_PLAYER_StateMachine;

typedef enum {
  AUDIO_STATE_IDLE = 0,
  AUDIO_STATE_WAIT,    
  AUDIO_STATE_INIT,    
  AUDIO_STATE_PLAY,
  AUDIO_STATE_PRERECORD,
  AUDIO_STATE_RECORD,  
  AUDIO_STATE_NEXT,  
  AUDIO_STATE_PREVIOUS,
  AUDIO_STATE_FORWARD,   
  AUDIO_STATE_BACKWARD,
  AUDIO_STATE_STOP,   
  AUDIO_STATE_PAUSE,
  AUDIO_STATE_RESUME,
  AUDIO_STATE_VOLUME_UP,
  AUDIO_STATE_VOLUME_DOWN,
  AUDIO_STATE_ERROR,  
}AUDIO_PLAYBACK_StateTypeDef;

typedef enum {
  AUDIO_SELECT_MENU = 0,
  AUDIO_PLAYBACK_CONTROL,  
}AUDIO_DEMO_SelectMode;

typedef enum {
  BUFFER_OFFSET_NONE = 0,  
  BUFFER_OFFSET_HALF,  
  BUFFER_OFFSET_FULL,     
}BUFFER_StateTypeDef;

/* Audio buffer control struct */
typedef struct {
  int16_t buff[AUDIO_OUT_BUFFER_SIZE];
  BUFFER_StateTypeDef state;
  uint32_t fptr;
}AUDIO_OUT_BufferTypeDef;

typedef enum {
  BUFFER_EMPTY = 0,  
  BUFFER_FULL,     
}WR_BUFFER_StateTypeDef;

typedef struct {
  int16_t pcm_buff[AUDIO_IN_PCM_BUFFER_SIZE];
  uint32_t pcm_ptr;
  WR_BUFFER_StateTypeDef wr_state;
  uint32_t offset;  
  uint32_t fptr;
}AUDIO_IN_BufferTypeDef;

typedef struct {
  uint32_t ChunkID;       /* 0 */ 
  uint32_t FileSize;      /* 4 */
  uint32_t FileFormat;    /* 8 */
  uint32_t SubChunk1ID;   /* 12 */
  uint32_t SubChunk1Size; /* 16*/  
  uint16_t AudioFormat;   /* 20 */ 
  uint16_t NbrChannels;   /* 22 */   
  uint32_t SampleRate;    /* 24 */
  
  uint32_t ByteRate;      /* 28 */
  uint16_t BlockAlign;    /* 32 */  
  uint16_t BitPerSample;  /* 34 */  
  uint32_t SubChunk2ID;   /* 36 */   
  uint32_t SubChunk2Size; /* 40 */    
}WAVE_FormatTypeDef;

typedef enum {
  AUDIO_ERROR_NONE = 0,  
  AUDIO_ERROR_IO,
  AUDIO_ERROR_EOF,
  AUDIO_ERROR_INVALID_VALUE,     
}AUDIO_ErrorTypeDef;

typedef struct _FILELIST_LineTypeDef {
  uint8_t type;
  uint8_t name[FILEMGR_FILE_NAME_SIZE];
}FILELIST_LineTypeDef;

typedef struct _FILELIST_FileTypeDef {
  FILELIST_LineTypeDef  file[FILEMGR_LIST_DEPDTH] ;
  uint16_t              ptr; 
}FILELIST_FileTypeDef;

/* Exported macro ------------------------------------------------------------*/

/* Exported functions ------------------------------------------------------- */
AUDIO_ErrorTypeDef AUDIO_Init(void);

AUDIO_ErrorTypeDef AUDIO_PLAYER_Start(uint8_t idx);
AUDIO_ErrorTypeDef AUDIO_PLAYER_Process(void);
AUDIO_ErrorTypeDef AUDIO_PLAYER_Stop(void);

AUDIO_ErrorTypeDef AUDIO_REC_Process(void);
AUDIO_ErrorTypeDef AUDIO_REC_Start(void);

FRESULT AUDIO_StorageParse(void);
uint16_t AUDIO_GetWavObjectNumber(void);
uint16_t AUDIO_GetRECObjectNumber(void);

void AUDIO_StateMachineProcess(void);

void BSP_AUDIO_IN_TransferComplete_CallBack(void);
void BSP_AUDIO_IN_HalfTransfer_CallBack(void);
void BSP_AUDIO_OUT_TransferComplete_CallBack(void);
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void);

#endif