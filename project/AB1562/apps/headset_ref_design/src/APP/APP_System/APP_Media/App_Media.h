/* Copyright Statement:
 *
 * (C) 2017  Airoha Technology Corp. All rights reserved.
 *
 * This software/firmware and related documentation ("Airoha Software") are
 * protected under relevant copyright laws. The information contained herein
 * is confidential and proprietary to Airoha Technology Corp. ("Airoha") and/or its licensors.
 * Without the prior written permission of Airoha and/or its licensors,
 * any reproduction, modification, use or disclosure of Airoha Software,
 * and information contained herein, in whole or in part, shall be strictly prohibited.
 * You may only use, reproduce, modify, or distribute (as applicable) Airoha Software
 * if you have agreed to and been bound by the applicable license agreement with
 * Airoha ("License Agreement") and been granted explicit permission to do so within
 * the License Agreement ("Permitted User").  If you are not a Permitted User,
 * please cease any access or use of Airoha Software immediately.
 * BY OPENING THIS FILE, RECEIVER HEREBY UNEQUIVOCALLY ACKNOWLEDGES AND AGREES
 * THAT AIROHA SOFTWARE RECEIVED FROM AIROHA AND/OR ITS REPRESENTATIVES
 * ARE PROVIDED TO RECEIVER ON AN "AS-IS" BASIS ONLY. AIROHA EXPRESSLY DISCLAIMS ANY AND ALL
 * WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE OR NONINFRINGEMENT.
 * NEITHER DOES AIROHA PROVIDE ANY WARRANTY WHATSOEVER WITH RESPECT TO THE
 * SOFTWARE OF ANY THIRD PARTY WHICH MAY BE USED BY, INCORPORATED IN, OR
 * SUPPLIED WITH AIROHA SOFTWARE, AND RECEIVER AGREES TO LOOK ONLY TO SUCH
 * THIRD PARTY FOR ANY WARRANTY CLAIM RELATING THERETO. RECEIVER EXPRESSLY ACKNOWLEDGES
 * THAT IT IS RECEIVER'S SOLE RESPONSIBILITY TO OBTAIN FROM ANY THIRD PARTY ALL PROPER LICENSES
 * CONTAINED IN AIROHA SOFTWARE. AIROHA SHALL ALSO NOT BE RESPONSIBLE FOR ANY AIROHA
 * SOFTWARE RELEASES MADE TO RECEIVER'S SPECIFICATION OR TO CONFORM TO A PARTICULAR
 * STANDARD OR OPEN FORUM. RECEIVER'S SOLE AND EXCLUSIVE REMEDY AND AIROHA'S ENTIRE AND
 * CUMULATIVE LIABILITY WITH RESPECT TO AIROHA SOFTWARE RELEASED HEREUNDER WILL BE,
 * AT AIROHA'S OPTION, TO REVISE OR REPLACE AIROHA SOFTWARE AT ISSUE,
 * OR REFUND ANY SOFTWARE LICENSE FEES OR SERVICE CHARGE PAID BY RECEIVER TO
 * AIROHA FOR SUCH AIROHA SOFTWARE AT ISSUE.
 */


#ifndef _APP_MEDIA_H_
#define _APP_MEDIA_H_

#include "bt.h"
#include "Media_Event_Nvkey.h"

#define VOICE_PROMPT_BEFORE_RINGTONE_BIT		0x80 //in overwriteTime
#define EVENT_LED_FG_TIMEOUT_MASK				0x7F//for overwriteTime unit: 10ms
#define	MEDIA_EVT_DELAY_SEND_MS		100

#define MEDIA_EVT_Q_NUM		20

#undef EVENT_NAME
#define EVENT_NAME(name) MEDIA_EVT_KEY_##name,

enum
{
	//0x0X
	NO_MEDIA = 0,
	MEDIA_EVT_KEY_BASE	= 0x0001,

	MEDIA_EVT_SYSTEM_BASE = 0x9000,
	MEDIA_EVT_CONNECTION_BASE = 0xA000,
	MEDIA_EVT_SHARE_MODE_BASE = 0xA050,
	//MEDIA EVENT KEY START
	//0x0001
	MEDIA_EVT_INVALID = NO_MEDIA,
	#include "App_KeyEvent.h"
    MEDIA_EVT_KEY_INTERNAL_TOTAL_NO,
	MEDIA_EVT_KEY_FOR_AE_START = 0x0500,
	#include "App_KeyEventReserved.h"
	MEDIA_EVT_KEY_TOTAL_NO,
	//MEDIA EVENT KEY END

	//0x900X	Battery
	MEDIA_EVT_BAT_LOW = MEDIA_EVT_SYSTEM_BASE, // low battery
	MEDIA_EVT_BAT_FULL, //battery voltage is over full_voltage, i.e., fake charge-complete signal
	MEDIA_EVT_BAT_CHGCPL, //charge complete
	MEDIA_EVT_BAT_RECHG, //recharge
	MEDIA_EVT_BAT_CHGROUT, //charger pull out
	MEDIA_EVT_BAT_CHGRIN, //charger plug in
	MEDIA_EVT_BAT_CHGTO,	//charge TO
	MEDIA_EVT_BAT_HW_CHGTO,	//hw detects charging TO
	MEDIA_EVT_BATTERY_INTERVAL_0,
	MEDIA_EVT_BATTERY_INTERVAL_1,
	MEDIA_EVT_BATTERY_INTERVAL_2,
	MEDIA_EVT_BATTERY_INTERVAL_3,
	MEDIA_EVT_BAT_LOW_LED,
	MEDIA_EVT_BAT_LOW_RING,
	MEDIA_EVT_BAT_SECURE_TEMP,
	MEDIA_EVT_BAT_RISKY_TEMP,

	//0x901X
	MEDIA_EVT_BAT_OK,
	MEDIA_EVT_BAT_DISCOUNT_TEMP,
	MEDIA_EVT_POWER_ON,
	MEDIA_EVT_POWER_ON_UNDER_CHECKPOINT1,
	MEDIA_EVT_POWER_OFF,
	MEDIA_EVT_POWER_OFF_UNDER_CHECKPOINT1,
	MEDIA_EVT_POWER_OFF_IN_SHUTDOWN_LOW_BAT,
	MEDIA_EVT_MUTE_REMINDER,
	MEDIA_EVT_ENTER_TESTMODE_STATE,
	MEDIA_EVT_OFF_STATE,
	MEDIA_EVT_FG_LED_DISPLAY_OVER,
	MEDIA_EVT_RESET_COMPLETE,
	MEDIA_EVT_FM_VOLUME_REACH_MAX,
	MEDIA_EVT_FM_VOLUME_REACH_MIN,
	MEDIA_EVT_FM_NOT_BUSY,
	MEDIA_EVT_LINEIN_VOLUME_REACH_MAX,

	//0x902X
	MEDIA_EVT_LINEIN_VOLUME_REACH_MIN,
	MEDIA_EVT_VOICE_PROMPT_LANG_CHANGE,
	MEDIA_EVT_VOICE_PROMPT_LANG_SELECT,
	MEDIA_EVT_VOICE_PROMPT_LANG_CONFIRM,
	MEDIA_EVT_ENTER_LINE_IN_MODE,
	MEDIA_EVT_EXIT_LINE_IN_MODE,
	MEDIA_EVT_MUTE_ON,
	MEDIA_EVT_MUTE_OFF,
	MEDIA_EVT_FM_MUTE_ON,
	MEDIA_EVT_FM_MUTE_OFF,
	MEDIA_EVT_FM_ENABLE,
	MEDIA_EVT_POWER_OFF_UNDER_CHECKPOINT2,
	MEDIA_EVT_POWER_OFF_UNDER_CHECKPOINT3,
	MEDIA_EVT_POWER_ON_UNDER_CHECKPOINT2,
	MEDIA_EVT_POWER_ON_UNDER_CHECKPOINT3,
	MEDIA_EVT_VOICE_COMMAND_FAIL,

	//0x903X
	MEDIA_EVT_VOICE_COMMAND_MULTILAYER_TRIGGER,
	MEDIA_EVT_RESERVED1,
	MEDIA_EVT_MIC_UPDN,
	MEDIA_EVT_CALLER_ID,
	MEDIA_EVT_IMGCALL_MEDIA_NOT_FOUND,
	MEDIA_EVT_NUMBER,

	//0xA00X		Indication Events
	MEDIA_EVT_SLC_CONNECTED = MEDIA_EVT_CONNECTION_BASE,
	MEDIA_EVT_2_SLC_CONNECTED,
	MEDIA_EVT_3_SLC_CONNECTED,
	MEDIA_EVT_4_SLC_CONNECTED,
	MEDIA_EVT_SLC_DISCONNECTED,
	MEDIA_EVT_PAIRING_SUCCESSFUL,
	MEDIA_EVT_PAIRING_FAIL,
	MEDIA_EVT_LINK_LOSS,
	MEDIA_EVT_END_OF_CALL,
	MEDIA_EVT_RINGTONE,
	MEDIA_EVT_RECONNECT_FAILED,  //0xA0
	MEDIA_EVT_NETWORK_NOT_PRESENT,
	MEDIA_EVT_NETWORK_PRESENT,
	MEDIA_EVT_PINCODE_REQUEST,
	MEDIA_EVT_CONFIRMATION_REQUEST,
	MEDIA_EVT_CALL_CONNECTED,

	//0xA01X
	MEDIA_EVT_AUDIO_LINK_OPEN,
	MEDIA_EVT_AUDIO_LINK_CLOSE,
	MEDIA_EVT_CONNECTABLE_TIMEOUT,
	MEDIA_EVT_HFP_ERROR_RECEIVED,
	MEDIA_EVT_REFRESH_ENCRYPTION,
	MEDIA_EVT_ENTER_CTX_TEST_MODE,
	MEDIA_EVT_ENTER_DISCOVERABLE,
	MEDIA_EVT_EXIT_DISCOVERABLE,
	MEDIA_EVT_ENTER_INCOMING,
	MEDIA_EVT_EXIT_INCOMING,
	MEDIA_EVT_PHONE_IS_TOO_FAR_1,
	MEDIA_EVT_PHONE_IS_TOO_FAR_2,
	MEDIA_EVT_RINGTONE_2,
	MEDIA_EVT_VOLUME_REACH_MAX,
	MEDIA_EVT_VOLUME_REACH_MIN,
	MEDIA_EVT_REDIAL_SUCCESSFUL_EVT,

	//0xA02X
	MEDIA_EVT_A2DP_VOLUME_REACH_MAX,
	MEDIA_EVT_A2DP_VOLUME_REACH_MIN,
	MEDIA_RESERVED1,	//MEDIA_EVT_MISSED_CALL_REMINDER1, This is canceled in 1530
	MEDIA_RESERVED2,	//MEDIA_EVT_MISSED_CALL_REMINDER2, This is canceled in 1530
	MEDIA_EVT_A2DP_ENABLE,
	MEDIA_EVT_A2DP_DISABLE,
	MEDIA_EVT_VOICE_DIAL_ENABLE,
	MEDIA_EVT_REDIAL_ENABLE,
	MEDIA_EVT_RINGTONE_IN_CALL,
	MEDIA_EVT_RINGTONE2_IN_CALL,
	MEDIA_EVT_TWS_ENTER_PAIRING,
	MEDIA_EVT_TWS_EXIT_PAIRING,
	MEDIA_EVT_TWS_DURING_PAIRING,
	MEDIA_EVT_TWS_LEFT_CHANNEL,
	MEDIA_EVT_TWS_RIGHT_CHANNEL,
	MEDIA_EVT_TWS_RELAY_ONLY,

	//0xA03X
	MEDIA_EVT_TWS_FOLLOWER,
	MEDIA_EVT_SIRI_STARTING,
	MEDIA_EVT_SIRI_CONTINUE,
	MEDIA_EVT_SIRI_END,
	MEDIA_EVT_KEY_FIND_MY_ACCESSORY,
	MEDIA_EVT_TWS_DISCONNECTED,
	MEDIA_EVT_AG_CNLOUTGOING,
	MEDIA_EVT_INCOMING_CALL_ENDED,
	MEDIA_EVT_ANC_ON,
	MEDIA_EVT_ANC_OFF,
	MEDIA_EVT_MP3_POWERON,
	MEDIA_EVT_SPECIAL_CONNECTED,
	MEDIA_EVT_SPECIAL_DISCONNECTED,
	MEDIA_EVT_PLAYING_BEEP_SYNC,
	MEDIA_EVT_LEAKAGE_DETECTION,
    MEDIA_EVT_GVA_MIC_OPEN,

    //0xA04X
    MEDIA_EVT_GVA_MIC_CLOSE,
    MEDIA_EVT_GVA_MIC_NOT_CONNECTED,
	MEDIA_EVT_ANC_CAL_SZ,
	MEDIA_EVT_PRESSURE_SENSOR, //A043
	MEDIA_EVT_FORCE_TOUCH_PRESS,  //A044, 
	MEDIA_EVT_FORCE_TOUCH_RELEASE, //A045
	MEDIA_EVT_XIAOAI_EVT0,
	MEDIA_EVT_XIAOAI_EVT1,
	MEDIA_EVT_XIAOAI_EVT2,
	MEDIA_EVT_XIAOAI_EVT3,//A049
	
	MEDIA_EVT_TWS_EXIT_MCSYNC_SHARE_PAIRING = MEDIA_EVT_SHARE_MODE_BASE,
	MEDIA_EVT_SHARE_MODE_START,
	MEDIA_EVT_SHARE_MODE_STOP,
	MEDIA_EVT_SHARE_MODE_CONTINUE,
	MEDIA_EVT_SHARE_MODE_FOLLOWER,
	MEDIA_EVT_SHARE_MODE_SHORT_PATTERN,
	
	//0xA06X
	MEDIA_EVT_A3_ASSISTANT_1 = 0xA060,
	MEDIA_EVT_A3_ASSISTANT_2,
	MEDIA_EVT_A3_ASSISTANT_3,
	
	//reserve for UART cmd to play voice prompt
	MEDIA_EVT_UART_CMD_RESERVE,
	MEDIA_EVT_KEY_FIND_MY_SINGLE_ACCESSORY,
};

enum
{
	MEDIA_STATE_END,
	MEDIA_STATE_START,
	MEDIA_STATE_SYNC_PLAY,
};

typedef struct
{
	U16 mediaEvtNum;
	U16 mediaEvtLockNum;
	U8 *pMediaData;
	U8 *pMediaLockTbl;
	U8 isDataOk;
	U8 mediaState;
	U8 mediaQNum;
	U16 mediaQ[MEDIA_EVT_Q_NUM];
	U16 mediaEvtFilterNum;
	U8 *pMediaFilter;
}MEDIA_EVT_CTL_STRU;

BOOL APP_Media_PushMediaEvent(U16 mediaEventId); //MMI_PushMediaEvent
BOOL APP_Media_SendFakeMediaCmd(U16 mediaEventId); //MMI_DRV_SendFakeMediaCmd
BOOL APP_Media_IsSubSinkQBufFull(void);
BOOL APP_Media_IsMediaEvtLock(U16 evtCode);
void APP_Media_StopMediaEvt(U16 EvtIndex);
void APP_Media_ClearAllMediaEvt(void);
void APP_Media_Init(void);

void APP_Media_PowerOffHandle(BOOL isReset);

#endif
