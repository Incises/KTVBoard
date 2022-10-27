/* Includes ------------------------------------------------------------------*/
#include "recorder.h"

/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/

/* Private typedef -----------------------------------------------------------*/
extern char SDPath[4];
extern AUDIO_ApplicationTypeDef appli_state;


FILELIST_FileTypeDef FileList;

AUDIO_PLAYBACK_StateTypeDef   AudioState;
AUDIO_PLAYER_StateMachine     AudioPlayer;



/* Private variables ---------------------------------------------------------*/

static AUDIO_OUT_BufferTypeDef  BufferCtlOut;
static AUDIO_IN_BufferTypeDef  BufferCtlIn;
uint8_t pHeaderBuff[44];

static uint32_t  display_update = 1;


static uint16_t NumObs = 0;
static int8_t RecFilesNum = 0;
static int16_t FilePos = 0;
static __IO uint32_t uwVolume = 90;

static double MicInVolList[12]    = {0.56, 0.60, 0.64, 0.68, 0.72, 0.76, 0.80, 0.84, 0.88, 0.92, 0.96, 1.00};
static double MusicOutVolList[12] = {0.10, 0.20, 0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.85, 0.90, 0.95, 1.00};
uint8_t currentMicInVolIndex = 9;
uint8_t currentMusicOutVolIndex = 9;

uint8_t KTVMode = 1;
uint8_t flagOutputMuted = 0;
uint8_t flagMicInMuted = 0;
int16_t mixRatio = 1;
uint8_t flagMicLightOn = 1;

WAVE_FormatTypeDef WaveFormat;
FIL WavFile;
WAVE_FormatTypeDef RECWaveFormat;
FIL RecFile;
extern FILELIST_FileTypeDef FileList;

/* Private function prototypes -----------------------------------------------*/
static AUDIO_ErrorTypeDef GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info);
static uint8_t PlayerInit(uint32_t AudioFreq);                               
static uint32_t WavProcess_EncInit(uint32_t Freq, uint8_t* pHeader);
static uint32_t WavProcess_HeaderInit(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct);
static uint32_t WavProcess_HeaderUpdate(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct);

FRESULT AUDIO_StorageParse(void);
uint16_t AUDIO_GetWavObjectNumber(void);
uint16_t AUDIO_GetRECObjectNumber(void);
uint8_t AUDIO_ShowWavFiles(void);

void AUDIO_StateMachineProcess(void);


/* Private functions ---------------------------------------------------------*/


/**
  * @brief  Initializes Audio Interface.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_Init(void)
{
  AudioPlayer.state = AUDIO_PLAYER_IDLE;

  if(BSP_AUDIO_IN_OUT_Init(INPUT_DEVICE_DIGITAL_MICROPHONE_2, OUTPUT_DEVICE_HEADPHONE, SAI_AUDIO_FREQUENCY_48K, 
                            DEFAULT_AUDIO_IN_BIT_DEPTH, DEFAULT_AUDIO_IN_CHANNEL_NBR)
      == AUDIO_OK)
  {
    BSP_AUDIO_IN_Record((uint16_t*)&BufferCtlIn.pcm_buff[0], AUDIO_IN_PCM_BUFFER_SIZE);
    BSP_AUDIO_IN_SetVolume(90);

    BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);

    BSP_AUDIO_OUT_Play((uint16_t*)&BufferCtlIn.pcm_buff[0], AUDIO_IN_PCM_BUFFER_SIZE*2);
    
    
    printf("Audio Init Successful\n");
    return AUDIO_ERROR_NONE;
  }
  else
    return AUDIO_ERROR_IO;
}  

FRESULT AUDIO_StorageParse(void)
{
  FRESULT res = FR_OK;
  FILINFO fno;
  DIR dir;
  char *fn;
  
  res = f_opendir(&dir, SDPath);
  FileList.ptr = 0;
  
  if(res == FR_OK)
  {
    RecFilesNum = 0;
    while(1)
    {
      res = f_readdir(&dir, &fno);
      if(res != FR_OK || fno.fname[0] == 0)
      {
        break;
      }
      if(fno.fname[0] == '.')
      {
        continue;
      }
      fn = fno.fname;
      
      if(FileList.ptr < FILEMGR_LIST_DEPDTH)
      {
        if((fno.fattrib & AM_DIR) == 0)
        {
          if((strstr(fn, "wav")) || (strstr(fn, "WAV")))
          {

            if((strstr(fn, "REC")) || (strstr(fn, "rec")))
              RecFilesNum++;
            strncpy((char *)FileList.file[FileList.ptr].name, (char *)fn, FILEMGR_FILE_NAME_SIZE);
            FileList.file[FileList.ptr].type = FILETYPE_FILE;
            FileList.ptr++;
          }
        }
      }   
    }
  }
  NumObs = FileList.ptr;
  f_closedir(&dir);
  return res;
}


/**
  * @brief  Shows audio file (*.wav) on the root
  * @param  None
  * @retval None
  */
uint8_t AUDIO_ShowWavFiles(void)
{
  uint8_t i = 0;
  uint8_t line_idx = 0;

  if(AUDIO_StorageParse() ==  FR_OK)
  {
    if(FileList.ptr > 0)
    {
     // LCD_UsrLog("audio file(s) [ROOT]:\n\n");
      for(i = 0; i < FileList.ptr; i++)
      {
        line_idx++;
        //LCD_DbgLog((char *)FileList.file[i].name);
        //LCD_DbgLog("\n");
      }
      //LCD_UsrLog("\nEnd of files list.\n");
      return 0;
    }
    return 1;
  }
  return 2;
}

/**
  * @brief  Gets Wav Object Number.
  * @param  None
  * @retval None
  */
uint16_t AUDIO_GetWavObjectNumber(void)
{
  return NumObs;
}
uint16_t AUDIO_GetRECObjectNumber(void)
{
  return RecFilesNum;
}


void AUDIO_StateMachineProcess(void)
{
  AUDIO_ErrorTypeDef  status;
  
  if(appli_state == APPLICATION_READY)
  { 
    // FOR DEBUG
    // AudioPlayer.state = AUDIO_PLAYER_PLAYBACK;
    
    switch(AudioPlayer.state)
    {
    case AUDIO_PLAYER_IDLE:     
      AudioPlayer.state = AUDIO_PLAYER_WAIT;
      break;    
      
    case AUDIO_PLAYER_WAIT:
      break;
      
    case AUDIO_PLAYER_EXPLORE: 
      if(appli_state == APPLICATION_READY)
      {
        if(AUDIO_ShowWavFiles() > 0)
        {
          printf("There is no WAV file.\n");         
          AudioPlayer.state = AUDIO_PLAYER_IDLE;
        }
        else
          AudioPlayer.state = AUDIO_PLAYER_WAIT;
      }
      else
      {
        AudioPlayer.state = AUDIO_PLAYER_WAIT;
      }
      break;
      
    case AUDIO_PLAYER_PLAYBACK:
      if(appli_state == APPLICATION_READY)
      {
        if(AudioState == AUDIO_STATE_IDLE)
        {
          if(AUDIO_ShowWavFiles() > 0)
          {
            printf("There is no WAV file.\n");         
            //AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
            AudioPlayer.state = AUDIO_PLAYER_IDLE;
          }
          else
          {
            /* Start Playing */
            printf("Start playing...\n");
            AudioState = AUDIO_STATE_INIT;
          }
        
         if(AUDIO_PLAYER_Start(FilePos) == AUDIO_ERROR_IO)
          {
//            AUDIO_ChangeSelectMode(AUDIO_SELECT_MENU); 
            AudioPlayer.state = AUDIO_PLAYER_IDLE;
          }
        }
        else /* Not idle */
        {
          if(AUDIO_PLAYER_Process() == AUDIO_ERROR_IO)
          { 
            AudioPlayer.state = AUDIO_PLAYER_IDLE;
          }
        }
      }
      else
      {
        AudioPlayer.state = AUDIO_PLAYER_WAIT;
      }
      break; 
//      
    case AUDIO_PLAYER_IN:
      if(appli_state == APPLICATION_READY)
      {

          /* Configure the audio recorder: sampling frequency, bits-depth, number of channels */   
            
          if(AUDIO_REC_Process() == AUDIO_ERROR_IO )
          {         
            lv_label_set_text_fmt(ui_StatusVal,"  AUDIO_ERROR_IO");
            AudioPlayer.state = AUDIO_PLAYER_IDLE;
            
          }

      }

      else
      {
        AudioPlayer.state = AUDIO_PLAYER_WAIT;
      }
      break;
      
    default:
      break;
    }
  }
  
  if(appli_state == APPLICATION_DISCONNECT)
  {
    appli_state = APPLICATION_IDLE;     
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);    
  }
}



/**
  * @brief  Starts Audio streaming.    
  * @param  idx: File index
  * @retval Audio error
  */ 
AUDIO_ErrorTypeDef AUDIO_PLAYER_Start(uint8_t idx)
{
  uint32_t bytesread;
  
  f_close(&WavFile);
  if(AUDIO_GetWavObjectNumber() > idx)
  { 
    GetFileInfo(idx, &WaveFormat);
    
    BufferCtlOut.state = BUFFER_OFFSET_NONE;

    f_lseek(&WavFile, 0); // Get Data from microSD card
    
    /* Fill whole buffer at first time */
    if(f_read(&WavFile, &BufferCtlOut.buff[0], AUDIO_OUT_BUFFER_SIZE*2, (void *)&bytesread) == FR_OK)
    {

      if(AudioPlayer.state == AUDIO_PLAYER_PLAYBACK)
      {
        /*Adjust the Audio frequency */
        PlayerInit(WaveFormat.SampleRate); 
        
        lv_label_set_text_fmt(ui_StatusVal,"  Playing");
        AudioState = AUDIO_STATE_PLAY;
      }
      if(AudioPlayer.state == AUDIO_PLAYER_IN)
      {
        BSP_AUDIO_IN_OUT_Init(INPUT_DEVICE_DIGITAL_MICROPHONE_2, OUTPUT_DEVICE_HEADPHONE, SAI_AUDIO_FREQUENCY_48K, DEFAULT_AUDIO_IN_BIT_DEPTH ,DEFAULT_AUDIO_IN_CHANNEL_NBR);
        BSP_AUDIO_IN_Record((uint16_t*)&BufferCtlIn.pcm_buff[0], AUDIO_IN_PCM_BUFFER_SIZE);
        printf("player in out init success\n");
        
      } 
      
      if(bytesread != 0)
      {
          BSP_AUDIO_IN_SetVolume(90);
          BSP_AUDIO_OUT_SetAudioFrameSlot(CODEC_AUDIOFRAME_SLOT_02);
          //if(AudioPlayer.state == AUDIO_PLAYER_PLAYBACK)
          BSP_AUDIO_OUT_Play((uint16_t*)&BufferCtlOut.buff[0], AUDIO_OUT_BUFFER_SIZE*2);
          
          printf("general output init success\n");
          BufferCtlOut.fptr = bytesread;
          BufferCtlIn.fptr = 0;
          return AUDIO_ERROR_NONE;
      }
      
    }
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Manages Audio process. 
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_PLAYER_Process(void)
{
  uint32_t bytesread, elapsed_time;
  AUDIO_ErrorTypeDef audio_error = AUDIO_ERROR_NONE;
  static uint32_t prev_elapsed_time = 0xFFFFFFFF;
  uint8_t str[16];
  
  switch(AudioState)
  {
  case AUDIO_STATE_PLAY:
    if(BufferCtlOut.fptr >= WaveFormat.FileSize)
    {
      BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
      AudioState = AUDIO_STATE_NEXT;
    }
    
    if(BufferCtlOut.state == BUFFER_OFFSET_HALF)
    {
      if(f_read(&WavFile, &BufferCtlOut.buff[0], AUDIO_OUT_BUFFER_SIZE, (void *)&bytesread) != FR_OK)
      { 
        BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW); 
        return AUDIO_ERROR_IO;       
      } 
      
      for(int i=0;i<AUDIO_OUT_BUFFER_SIZE/2;i++)
        if(flagOutputMuted)
          BufferCtlOut.buff[i] = 0;
        else
          BufferCtlOut.buff[i] *= MusicOutVolList[currentMusicOutVolIndex];
      
      
      BufferCtlOut.state = BUFFER_OFFSET_NONE;
      BufferCtlOut.fptr += bytesread; 
    }
    
    if(BufferCtlOut.state == BUFFER_OFFSET_FULL)
    {
      if(f_read(&WavFile, &BufferCtlOut.buff[AUDIO_OUT_BUFFER_SIZE/2], AUDIO_OUT_BUFFER_SIZE, (void *)&bytesread) != FR_OK)
      { 
        BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW); 
        return AUDIO_ERROR_IO;       
      } 
      
      for(int i=AUDIO_OUT_BUFFER_SIZE/2;i<AUDIO_OUT_BUFFER_SIZE;i++)
        if(flagOutputMuted)
          BufferCtlOut.buff[i] = 0;
        else
          BufferCtlOut.buff[i] *= MusicOutVolList[currentMusicOutVolIndex];
    
      BufferCtlOut.state = BUFFER_OFFSET_NONE;
      BufferCtlOut.fptr += bytesread; 
    }
    

    
    
    /* Display elapsed time */
    elapsed_time = BufferCtlOut.fptr / WaveFormat.ByteRate; 
    if(prev_elapsed_time != elapsed_time)
    {
      prev_elapsed_time = elapsed_time;
      sprintf((char *)str, "[%02d:%02d]", (int)(elapsed_time /60), (int)(elapsed_time%60));

    }
    break;
    
  case AUDIO_STATE_STOP:
    
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AudioState = AUDIO_STATE_IDLE; 
    audio_error = AUDIO_ERROR_IO;
    break;
    
  case AUDIO_STATE_NEXT:
    if(++FilePos >= AUDIO_GetWavObjectNumber())
    {
      FilePos = 0; 
    }
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_PLAYER_Start(FilePos);

    break;    
    
  case AUDIO_STATE_PREVIOUS:
    if(--FilePos < 0)
    {
      FilePos = AUDIO_GetWavObjectNumber() - 1; 
    }
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
    AUDIO_PLAYER_Start(FilePos);

    break;   
    
  case AUDIO_STATE_PAUSE:

   // BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PAUSE]", LEFT_MODE);

    printf("Playback paused\n");
    BSP_AUDIO_OUT_Pause();
    AudioState = AUDIO_STATE_WAIT;
    break;
    
  case AUDIO_STATE_RESUME:
   // BSP_LCD_DisplayStringAt(250, LINE(9), (uint8_t *)"  [PLAY ]", LEFT_MODE);
   //                                         /* Display blue cyan pause rectangles */

    BSP_AUDIO_OUT_Resume();

    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_VOLUME_UP: 
    if( uwVolume <= 80)
    {
      uwVolume += 10;
    }
    BSP_AUDIO_OUT_SetVolume(uwVolume);

    //sprintf((char *)str,  "Volume : %lu ", uwVolume);
    printf((char *)str,  "Volume : %lu \n", uwVolume);

    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_VOLUME_DOWN:    
    if( uwVolume >= 10)
    {
      uwVolume -= 10;
    }
    BSP_AUDIO_OUT_SetVolume(uwVolume);
 
    //sprintf((char *)str,  "Volume : %lu ", uwVolume);
    printf((char *)str,  "Volume : %lu \n", uwVolume);
    AudioState = AUDIO_STATE_PLAY;
    break;
    
  case AUDIO_STATE_WAIT:
  case AUDIO_STATE_IDLE:
    AudioState = AUDIO_STATE_WAIT;
    break;
  case AUDIO_STATE_INIT:    
  default:
    /* Update audio state machine according to touch acquisition */
    //AUDIO_AcquireTouchButtons();
    break;
  }
  return audio_error;
}

/**
  * @brief  Stops Audio streaming.
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_PLAYER_Stop(void)
{
  AudioState = AUDIO_STATE_IDLE;
  //FilePos = 0;
  
  BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);
  f_close(&WavFile);
  return AUDIO_ERROR_NONE;
}

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_TransferComplete_CallBack(void)
{
  if(AudioState == AUDIO_STATE_PLAY || AudioState == AUDIO_STATE_RECORD)
  {
    BufferCtlOut.state = BUFFER_OFFSET_FULL;
  }
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_OUT_HalfTransfer_CallBack(void)
{ 
  if(AudioState == AUDIO_STATE_PLAY || AudioState == AUDIO_STATE_RECORD)
  {
    BufferCtlOut.state = BUFFER_OFFSET_HALF;
  }
}
/*******************************************************************************
                            Static Functions
*******************************************************************************/

/**
  * @brief  Gets the file info.
  * @param  file_idx: File index
  * @param  info: Pointer to WAV file info
  * @retval Audio error
  */
static AUDIO_ErrorTypeDef GetFileInfo(uint16_t file_idx, WAVE_FormatTypeDef *info)
{
  uint32_t bytesread;
  uint32_t duration;
  uint8_t str[FILEMGR_FILE_NAME_SIZE + 20];  
  
  if(f_open(&WavFile, (char *)FileList.file[file_idx].name, FA_OPEN_EXISTING | FA_READ) == FR_OK) 
  {
    /* Fill the buffer to Send */
    if(f_read(&WavFile, info, sizeof(WaveFormat), (void *)&bytesread) == FR_OK)
    {
      //sprintf((char *)str, "Playing file (%d/%d): %s", file_idx + 1, FileList.ptr, (char *)FileList.file[file_idx].name);
      printf("Playing file (%d/%d): %s\n", file_idx + 1, FileList.ptr, (char *)FileList.file[file_idx].name);
      lv_label_set_text_fmt(ui_FileName,"%s",FileList.file[file_idx].name);
      
      //sprintf((char *)str,  "Sample rate : %d Hz", (int)(info->SampleRate));
      printf("Sample rate : %d Hz\n", (int)(info->SampleRate));
      
      //sprintf((char *)str,  "Channels number : %d", info->NbrChannels);
      printf("Channels number : %d\n", info->NbrChannels);
      
      duration = info->FileSize / info->ByteRate; 
      //sprintf((char *)str, "File Size : %d KB [%02d:%02d]\n", (int)(info->FileSize/1024), (int)(duration/60), (int)(duration%60));
      printf("File Size : %d KB [%02d:%02d]\n", (int)(info->FileSize/1024), (int)(duration/60), (int)(duration%60));
      
      //sprintf((char *)str,  "Volume : %lu", uwVolume);
      printf("Volume : %d\n", (int)uwVolume);

      return AUDIO_ERROR_NONE;
    }
    f_close(&WavFile);
  }
  return AUDIO_ERROR_IO;
}

/**
  * @brief  Initializes the Wave player.
  * @param  AudioFreq: Audio sampling frequency
  * @retval None
  */
static uint8_t PlayerInit(uint32_t AudioFreq)
{ 
  //BSP_AUDIO_IN_DeInit();
  /* Initialize the Audio codec and all related peripherals (I2S, I2C, IOExpander, IOs...) */  
  if(BSP_AUDIO_OUT_Init(OUTPUT_DEVICE_HEADPHONE, uwVolume, AudioFreq) != AUDIO_OK )
  {
    printf("Player Audio Out Init Failed!!!\n");
    return AUDIO_ERROR;
  }
  else
  {

    BSP_AUDIO_OUT_SetVolume(90);
    printf("Player Audio Out Init Successful\n");
    return AUDIO_OK;
  } 
}


/**
  * @brief  Starts Audio streaming.    
  * @param  None
  * @retval Audio error
  */ 
AUDIO_ErrorTypeDef AUDIO_REC_Start(void)
{
  uint32_t byteswritten = 0;
  uint8_t str[FILEMGR_FILE_NAME_SIZE + 20]; 
  
  char REC_WAVE_NAME[FILEMGR_FILE_NAME_SIZE] = REC_FILENAME_PREFIX;
  char recFileNo[4];
  sprintf(recFileNo, "%02d", (RecFilesNum+1));
  strcat(REC_WAVE_NAME, recFileNo);

  strcat(REC_WAVE_NAME, REC_FILENAME_EXTENSION);

  //uwVolume = 90;

  /* Create a new file system */
  if(f_open(&RecFile, REC_WAVE_NAME, FA_CREATE_ALWAYS | FA_WRITE) == FR_OK)
  {  
    /* Initialize header file */
    WavProcess_EncInit(REC_FREQ_DEFAULT, pHeaderBuff);
    
    /* Write header file */
    if(f_write(&RecFile, pHeaderBuff, 44, (void*)&byteswritten) == FR_OK)
    {
      
      printf("Recording file: %s\n", REC_WAVE_NAME);
      printf("Sample rate : %d Hz\n", (int)REC_FREQ_DEFAULT);
      printf("Channels number : %d\n", (int)DEFAULT_AUDIO_IN_CHANNEL_NBR);
      //sprintf((char *)str,  "Volume : %d ", (int)uwVolume);
      //sprintf((char *)str, "File Size :");
    }
    else
      printf("write rec_wav header failed!\n");
    if(byteswritten != 0)
    {
      BufferCtlIn.fptr = byteswritten;
      //BufferCtlIn.pcm_ptr = 0;
      //BufferCtlIn.offset = 0;
      //BufferCtlIn.wr_state = BUFFER_EMPTY;
      
      printf("rec to wav init success\n");
      return AUDIO_ERROR_NONE;
    }
        
  }
  return AUDIO_ERROR_IO; 
}

/**
  * @brief  Manages Audio Recording process. 
  * @param  None
  * @retval Audio error
  */
AUDIO_ErrorTypeDef AUDIO_REC_Process(void)
{
  uint32_t bytesread, byteswritten;
  AUDIO_ErrorTypeDef audio_error = AUDIO_ERROR_NONE;
  
  
  uint32_t elapsed_time; 
  static uint32_t prev_elapsed_time = 0xFFFFFFFF;
  uint8_t str[16];
  //static TS_StateTypeDef  TS_State={0};
  
  switch(AudioState)
  {

    case AUDIO_STATE_PRERECORD:

      if(AUDIO_PLAYER_Start(FilePos) == AUDIO_ERROR_IO)
      {
        printf("FAIL TO START KTV\n");
        audio_error = AUDIO_ERROR_IO;
      }
      
      if(AUDIO_REC_Start() == AUDIO_ERROR_IO)
      {
        printf("FAIL TO START REC\n");
        audio_error = AUDIO_ERROR_IO;
      }
      if(audio_error == AUDIO_ERROR_NONE)
      {
          
          lv_label_set_text_fmt(ui_StatusVal,"  Recording");
          AudioState = AUDIO_STATE_RECORD;
      }
      break;
      
    case AUDIO_STATE_RECORD:
//      lv_label_set_text_fmt(ui_StatusVal,"  Recording. . ");
//      if (display_update)
//      {
//        display_update = 0;
//      }
      
      if(BufferCtlOut.fptr >= WaveFormat.FileSize)
      {
        AudioState = AUDIO_STATE_STOP;
        break;
      }
    
      /* MAX Recording time reached, so stop audio interface and close file */
      if(BufferCtlIn.fptr >= REC_SAMPLE_LENGTH)
      {
        //display_update = 1;
        AudioState = AUDIO_STATE_STOP;
        break;
      }
      
      if(BufferCtlOut.state == BUFFER_OFFSET_HALF)
      {
        /* f_read( 3:Buffer(Bytes) ) */
        if(f_read(&WavFile, &BufferCtlOut.buff[0], AUDIO_OUT_BUFFER_SIZE, (void *)&bytesread) != FR_OK)
        { 
          return AUDIO_ERROR_IO;       
        }
        
        for(int i=0;i<AUDIO_OUT_BUFFER_SIZE/2;i++)
          if(flagOutputMuted)
            BufferCtlOut.buff[i] = 0;
          else
            BufferCtlOut.buff[i] *= MusicOutVolList[currentMusicOutVolIndex];
        
        if(!flagMicInMuted)
        {
          for(int i=0; i<AUDIO_OUT_BUFFER_SIZE/2; i++)
            BufferCtlOut.buff[i] += BufferCtlIn.pcm_buff[i];
         
        } 
        if(f_write(&RecFile, &BufferCtlOut.buff[0], AUDIO_OUT_BUFFER_SIZE, (void*)&byteswritten)!=FR_OK)
        {
          printf("RECORD FAIL\n");
          return AUDIO_ERROR_IO;
        }  
        BufferCtlIn.fptr += byteswritten;
             
        BufferCtlOut.state = BUFFER_OFFSET_NONE;
        BufferCtlOut.fptr += bytesread; 
      }
    
      if(BufferCtlOut.state == BUFFER_OFFSET_FULL)
      {
        if(f_read(&WavFile, &BufferCtlOut.buff[AUDIO_OUT_BUFFER_SIZE /2], AUDIO_OUT_BUFFER_SIZE, (void *)&bytesread) != FR_OK)
        { 
       
          return AUDIO_ERROR_IO;       
        } 
            
        for(int i=AUDIO_OUT_BUFFER_SIZE/2;i<AUDIO_OUT_BUFFER_SIZE;i++)
          if(flagOutputMuted)
            BufferCtlOut.buff[i] = 0;
          else
            BufferCtlOut.buff[i] *= MusicOutVolList[currentMusicOutVolIndex];
        
        
        if(!flagMicInMuted)
        {
          for(int i=AUDIO_OUT_BUFFER_SIZE/2; i<AUDIO_OUT_BUFFER_SIZE; i++)
            BufferCtlOut.buff[i] += BufferCtlIn.pcm_buff[i];  
        } 
       
        if(f_write(&RecFile, &BufferCtlOut.buff[AUDIO_OUT_BUFFER_SIZE/2], AUDIO_OUT_BUFFER_SIZE, (void*)&byteswritten) != FR_OK)
        {
          printf("RECORD FAIL\n");
          return AUDIO_ERROR_IO;
        }
        BufferCtlIn.fptr += byteswritten;
              
        BufferCtlOut.state = BUFFER_OFFSET_NONE;
        BufferCtlOut.fptr += bytesread; 
      }
    
    
    
      /* Display elapsed time */
//      elapsed_time = BufferCtlIn.fptr / (REC_FREQ_DEFAULT * DEFAULT_AUDIO_IN_CHANNEL_NBR * 2); 
//      if(prev_elapsed_time != elapsed_time)
//      {
//        prev_elapsed_time = elapsed_time;
//        sprintf((char *)str, "[%02d:%02d]", (int)(elapsed_time /60), (int)(elapsed_time%60));

//        sprintf((char *)str, "%4d KB", (int)((int32_t)BufferCtlIn.fptr/1024));

//      }
    break;
    
  case AUDIO_STATE_STOP:
    /* Stop recorder */
    BSP_AUDIO_IN_Stop(CODEC_PDWN_SW);
    BSP_AUDIO_OUT_Stop(CODEC_PDWN_SW);

    display_update = 1;
    HAL_Delay(150);
    if(f_lseek(&RecFile, 0) == FR_OK)
    {
      /* Update the wav file header save it into wav file */
      WavProcess_HeaderUpdate(pHeaderBuff, &RECWaveFormat);
      
      if(f_write(&RecFile, pHeaderBuff, sizeof(WAVE_FormatTypeDef), (void*)&byteswritten) == FR_OK)
      {   
        audio_error = AUDIO_ERROR_EOF;
      }
      else
      {
        audio_error = AUDIO_ERROR_IO;

        printf("RECORD FAIL\n");          
      }
    }
    else
    {
      printf("RECORD FAIL\n");
      audio_error = AUDIO_ERROR_IO;      
    }
    RecFilesNum ++;
    lv_label_set_text_fmt(ui_StatusVal,"  IDLE");
    AudioState = AUDIO_STATE_IDLE;      
    f_close(&RecFile);
    f_close(&WavFile);
    break;
    
  case AUDIO_STATE_PAUSE:
 
    BSP_AUDIO_IN_Pause();
    AudioState = AUDIO_STATE_WAIT;
    break;
    
  case AUDIO_STATE_RESUME:  
    
    BSP_AUDIO_IN_Resume();
    AudioState = AUDIO_STATE_RECORD;
    break;
    
  case AUDIO_STATE_VOLUME_UP:
    if(uwVolume <= 95)
    {
      uwVolume += 5;
    }
    sprintf((char *)str,  "Volume : %d ", (int)uwVolume);

    BSP_AUDIO_IN_SetVolume(uwVolume);
    AudioState = AUDIO_STATE_RECORD;
    break;
    
  case AUDIO_STATE_VOLUME_DOWN:
    if(uwVolume >= 5)
    {
      uwVolume -= 5;
    }
    sprintf((char *)str,  "Volume : %d ", (int)uwVolume);

    BSP_AUDIO_IN_SetVolume(uwVolume);
    AudioState = AUDIO_STATE_RECORD;
    break;
    
  case AUDIO_STATE_NEXT:
    if(++FilePos >= AUDIO_GetWavObjectNumber())
    {
      FilePos = 0; 
    }
    AudioState = AUDIO_STATE_IDLE;
    lv_label_set_text_fmt(ui_FileName,"%s",FileList.file[FilePos].name);
    
    break;    
    
  case AUDIO_STATE_PREVIOUS:
    if(--FilePos < 0)
    {
      FilePos = AUDIO_GetWavObjectNumber() - 1; 
    }
    AudioState = AUDIO_STATE_IDLE;
    lv_label_set_text_fmt(ui_FileName,"%s",FileList.file[FilePos].name);
    break;   
    
  case AUDIO_STATE_WAIT:
  case AUDIO_STATE_IDLE:
    break;
  case AUDIO_STATE_INIT: 
  default:
    /* Do Nothing */
    break;
  }
  return audio_error;
}

/**
  * @brief  Calculates the remaining file size and new position of the pointer.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_TransferComplete_CallBack(void)
{

  BufferCtlIn.pcm_ptr+= AUDIO_IN_PCM_BUFFER_SIZE/2;
  if(BufferCtlIn.pcm_ptr == AUDIO_IN_PCM_BUFFER_SIZE/2)
  {
    BufferCtlIn.wr_state   =  BUFFER_FULL;
    BufferCtlIn.offset  = 0;
  }
  
  if(BufferCtlIn.pcm_ptr >= AUDIO_IN_PCM_BUFFER_SIZE)
  {
    BufferCtlIn.wr_state   =  BUFFER_FULL;
    BufferCtlIn.offset  = AUDIO_IN_PCM_BUFFER_SIZE/2;    
    BufferCtlIn.pcm_ptr = 0;
  }

  int16_t lightLevel;
  lightLevel = (abs(BufferCtlIn.pcm_buff[AUDIO_IN_PCM_BUFFER_SIZE/4*3]))/4+(abs(BufferCtlIn.pcm_buff[AUDIO_IN_PCM_BUFFER_SIZE/2]))/4+(abs(BufferCtlIn.pcm_buff[0]))/4+(abs(BufferCtlIn.pcm_buff[AUDIO_IN_PCM_BUFFER_SIZE-1]))/4;
  
  if(lightLevel<20 || flagMicInMuted)
    lightLevel = 0;
  else
    lightLevel/=2;
  
  if(lightLevel>74)
    lightLevel = 74;
  
  //printf("%d ",lightLevel);
   __HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1,lightLevel);	
  
  
    
  for(int i=0; i < AUDIO_IN_PCM_BUFFER_SIZE ; i++)
  {
    BufferCtlIn.pcm_buff[i] *= MicInVolList[currentMicInVolIndex];
    if(flagMicInMuted)
      BufferCtlIn.pcm_buff[i] = 0; 
  }
  
}

/**
  * @brief  Manages the DMA Half Transfer complete interrupt.
  * @param  None
  * @retval None
  */
void BSP_AUDIO_IN_HalfTransfer_CallBack(void)
{ 
  BufferCtlIn.pcm_ptr += AUDIO_IN_PCM_BUFFER_SIZE/2;
  if(BufferCtlIn.pcm_ptr == AUDIO_IN_PCM_BUFFER_SIZE/2)
  {
    BufferCtlIn.wr_state =  BUFFER_FULL;
    BufferCtlIn.offset   =  0;
  }
  
  if(BufferCtlIn.pcm_ptr >= AUDIO_IN_PCM_BUFFER_SIZE)
  {
    BufferCtlIn.wr_state =  BUFFER_FULL;
    BufferCtlIn.offset   =  AUDIO_IN_PCM_BUFFER_SIZE/2;    
    BufferCtlIn.pcm_ptr  =  0;
  }
  
  for(int i=0; i < AUDIO_IN_PCM_BUFFER_SIZE ; i++)
  {
    BufferCtlIn.pcm_buff[i] *= MicInVolList[currentMicInVolIndex];
    if(flagMicInMuted)
      BufferCtlIn.pcm_buff[i] = 0; 
  }
}


/**
  * @brief  Encoder initialization.
  * @param  Freq: Sampling frequency.
  * @param  pHeader: Pointer to the WAV file header to be written.  
  * @retval 0 if success, !0 else.
  */
static uint32_t WavProcess_EncInit(uint32_t Freq, uint8_t *pHeader)
{  
  /* Initialize the encoder structure */
  RECWaveFormat.SampleRate = Freq;        // Audio sampling frequency 
  RECWaveFormat.NbrChannels = 2;          // Number of channels: 1:Mono or 2:Stereo 
  RECWaveFormat.BitPerSample = 16;        // Number of bits per sample (16, 24 or 32) 
  RECWaveFormat.FileSize = 0x001D4C00;    // Total length of useful audio data (payload) 
  RECWaveFormat.SubChunk1Size = 44;       // The file header chunk size 
  RECWaveFormat.ByteRate = (RECWaveFormat.SampleRate * \
                        (RECWaveFormat.BitPerSample/8) * \
                         RECWaveFormat.NbrChannels);     /* Number of bytes per second  (sample rate * block align)  */
  RECWaveFormat.BlockAlign = RECWaveFormat.NbrChannels * \
                         (RECWaveFormat.BitPerSample/8); /* channels * bits/sample / 8 */
  
  /* Parse the wav file header and extract required information */
  if(WavProcess_HeaderInit(pHeader, &RECWaveFormat))
  {
    return 1;
  }
  return 0;
}

/**
  * @brief  Initialize the wave header file
  * @param  pHeader: Header Buffer to be filled
  * @param  pWaveFormatStruct: Pointer to the wave structure to be filled.
  * @retval 0 if passed, !0 if failed.
  */
static uint32_t WavProcess_HeaderInit(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct)
{
  /* Write chunkID, must be 'RIFF'  ------------------------------------------*/
  pHeader[0] = 'R';
  pHeader[1] = 'I';
  pHeader[2] = 'F';
  pHeader[3] = 'F';
  
  /* Write the file length ---------------------------------------------------*/
  /* The sampling time: this value will be written back at the end of the 
     recording operation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
  pHeader[4] = 0x00;
  pHeader[5] = 0x4C;
  pHeader[6] = 0x1D;
  pHeader[7] = 0x00;
  /* Write the file format, must be 'WAVE' -----------------------------------*/
  pHeader[8]  = 'W';
  pHeader[9]  = 'A';
  pHeader[10] = 'V';
  pHeader[11] = 'E';
  
  /* Write the format chunk, must be'fmt ' -----------------------------------*/
  pHeader[12]  = 'f';
  pHeader[13]  = 'm';
  pHeader[14]  = 't';
  pHeader[15]  = ' ';
  
  /* Write the length of the 'fmt' data, must be 0x10 ------------------------*/
  pHeader[16]  = 0x10;
  pHeader[17]  = 0x00;
  pHeader[18]  = 0x00;
  pHeader[19]  = 0x00;
  
  /* Write the audio format, must be 0x01 (PCM) ------------------------------*/
  pHeader[20]  = 0x01;
  pHeader[21]  = 0x00;
  
  /* Write the number of channels, ie. 0x01 (Mono) ---------------------------*/
  pHeader[22]  = pWaveFormatStruct->NbrChannels;
  pHeader[23]  = 0x00;
  
  /* Write the Sample Rate in Hz ---------------------------------------------*/
  /* Write Little Endian ie. 8000 = 0x00001F40 => byte[24]=0x40, byte[27]=0x00*/
  pHeader[24]  = (uint8_t)((pWaveFormatStruct->SampleRate & 0xFF));
  pHeader[25]  = (uint8_t)((pWaveFormatStruct->SampleRate >> 8) & 0xFF);
  pHeader[26]  = (uint8_t)((pWaveFormatStruct->SampleRate >> 16) & 0xFF);
  pHeader[27]  = (uint8_t)((pWaveFormatStruct->SampleRate >> 24) & 0xFF);
  
  /* Write the Byte Rate -----------------------------------------------------*/
  pHeader[28]  = (uint8_t)((pWaveFormatStruct->ByteRate & 0xFF));
  pHeader[29]  = (uint8_t)((pWaveFormatStruct->ByteRate >> 8) & 0xFF);
  pHeader[30]  = (uint8_t)((pWaveFormatStruct->ByteRate >> 16) & 0xFF);
  pHeader[31]  = (uint8_t)((pWaveFormatStruct->ByteRate >> 24) & 0xFF);
  
  /* Write the block alignment -----------------------------------------------*/
  pHeader[32]  = pWaveFormatStruct->BlockAlign;
  pHeader[33]  = 0x00;
  
  /* Write the number of bits per sample -------------------------------------*/
  pHeader[34]  = pWaveFormatStruct->BitPerSample;
  pHeader[35]  = 0x00;
  
  /* Write the Data chunk, must be 'data' ------------------------------------*/
  pHeader[36]  = 'd';
  pHeader[37]  = 'a';
  pHeader[38]  = 't';
  pHeader[39]  = 'a';
  
  /* Write the number of sample data -----------------------------------------*/
  /* This variable will be written back at the end of the recording operation */
  pHeader[40]  = 0x00;
  pHeader[41]  = 0x4C;
  pHeader[42]  = 0x1D;
  pHeader[43]  = 0x00;
  
  return 0;   // Return 0 if all operations are OK 
}

/**
  * @brief  Initialize the wave header file
  * @param  pHeader: Header Buffer to be filled
  * @param  pWaveFormatStruct: Pointer to the wave structure to be filled.
  * @retval 0 if passed, !0 if failed.
  */
static uint32_t WavProcess_HeaderUpdate(uint8_t* pHeader, WAVE_FormatTypeDef* pWaveFormatStruct)
{
  /* Write the file length ---------------------------------------------------*/
  /* The sampling time: this value will be written back at the end of the 
     recording operation.  Example: 661500 Btyes = 0x000A17FC, byte[7]=0x00, byte[4]=0xFC */
  pHeader[4] = (uint8_t)(BufferCtlIn.fptr);
  pHeader[5] = (uint8_t)(BufferCtlIn.fptr >> 8);
  pHeader[6] = (uint8_t)(BufferCtlIn.fptr >> 16);
  pHeader[7] = (uint8_t)(BufferCtlIn.fptr >> 24);
  /* Write the number of sample data -----------------------------------------*/
  /* This variable will be written back at the end of the recording operation */
  BufferCtlIn.fptr -=44;
  pHeader[40] = (uint8_t)(BufferCtlIn.fptr); 
  pHeader[41] = (uint8_t)(BufferCtlIn.fptr >> 8);
  pHeader[42] = (uint8_t)(BufferCtlIn.fptr >> 16);
  pHeader[43] = (uint8_t)(BufferCtlIn.fptr >> 24); 
  
  return 0;   // Return 0 if all operations are OK 
}
