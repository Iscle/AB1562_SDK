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


#include "bt.h"
#include "a2dp.h"
#include "App_ResourceManager.h"
#include "App_Connection.h"
#include "App_Interface.h"
#include "A2dp_Interface.h"
#include "App_Avrcp.h"
#include "App_A2dp.h"
#include "Avrcp_Interface.h"
#include "AudioDSP_StreamManager.h"
#include "AudioDSP_Registration.h"
#include "App_State.h"
#include "App_A2dp_NVKeyHandler.h"
#include "App_SniffHandler.h"
#include "App_VolumeManage.h"
#include "App_Nvram_Type.h"
#include "App_Media.h"
#include "App_ReConnection.h"
#include "A2dp_LinkManager.h"
#include "APP_Qos.h"
#include "BtA2dp_Settings.h"
#include "PM_Interface.h"
#include "drv_a2dp.h"
#include "BtSdps.h"
#include "App_LinkKey.h"


#define DBG_LOG_APP_A2DP(_message, arg_cnt, ...)  LOG_MSGID_I(APP_A2DP, _message, arg_cnt, ##__VA_ARGS__)


log_create_module(APP_A2DP, PRINT_LEVEL_INFO);

/**************************************************************************************************
* Type definition
**************************************************************************************************/

/**************************************************************************************************
Function Extern
***************************************************************************************************/

/**************************************************************************************************
* Macro
**************************************************************************************************/

/**************************************************************************************************
* Prototype
**************************************************************************************************/

/**************************************************************************************************
* Extern Variable
**************************************************************************************************/


/**************************************************************************************************
* Static
**************************************************************************************************/
static void app_A2dp_MusicStopped(BD_ADDR_T *pBdAddr, BOOL isStop);
static void app_A2dp_MusicStopClearPara(BD_ADDR_T *pBdAddr);
static void app_A2dp_AcceptStart(BD_ADDR_T *pBdAddr);
static void app_A2dp_RejectStart(BD_ADDR_T *pBdAddr);
static void app_A2dp_MediaPktMemPut(BD_ADDR_T *pBdAddr);
static BOOL app_A2dp_GetAudioDevRegister(BD_ADDR_T *pBdAddr);
static void app_A2dp_SendPause(BD_ADDR_T *pBdAddr, U8 playStatus);
static void app_A2dp_GetPlayStatusToPauseMusicCallBack(BD_ADDR_T *pBdAddr, U8 isSuccessful);
static void app_A2dp_GetPauseMusicCallBack(BD_ADDR_T *pBdAddr, U8 isSuccessful);
static void app_A2dp_RemoveAudioLink(BD_ADDR_T *pBdAddr);
static U32 	app_A2dp_IndHandler(Handler handler, U16 id, void *msg, U32 handler_id);
static U32	app_A2dp_TimerHandler(Handler handler, U16 id, void *msg, U32 handler_id);

/*************************************************************************************************
APP
***************************************************************************************************/

/**************************************************************************************************
* Static Variables (Connection)
**************************************************************************************************/
static const HandlerData gAppA2dpTimerHandle = { app_A2dp_TimerHandler };
static const HandlerData gAppA2dpHandle = { app_A2dp_IndHandler };

/**************************************************************************************************
* Static Functions (Connection)
**************************************************************************************************/
static void app_A2dpStartServiceCfmHandler(A2DP_START_SERVICE_CFM_T *cfm)
{
	DBG_LOG_APP_A2DP( "[APP_A2DP] Start Service Cfm : Status: 0x%x", 1, cfm->status);
}

static void app_A2dpStopServiceCfmHandler(A2DP_STOP_SERVICE_CFM_T *cfm)
{
	DBG_LOG_APP_A2DP( "[APP_A2DP] Stop Service Cfm : Status: 0x%x", 1, cfm->status);
}

static void app_A2dpSignalConnectIndHandler(A2DP_SIGNAL_CONNECT_IND_T *ind)
{
    DBG_LOG_APP_A2DP("[APP_A2DP] Signal Connect Ind : BdAddr : 0x%x%x", 2, FW_bdaddr_to_2U32(&ind->bdAddr, TRUE), FW_bdaddr_to_2U32(&ind->bdAddr, FALSE));
    a2dp_connect_response(&ind->bdAddr, TRUE, ind->channelId, ind->identifier);
}

static void app_A2dpSignalConnectCfmHandler(A2DP_SIGNAL_CONNECT_CFM_T *cfm)
{
    DBG_LOG_APP_A2DP("[APP_A2DP] Signal Connect Cfm : BdAddr : 0x%x%x, Status:0x%x", 3, FW_bdaddr_to_2U32(&cfm->bdAddr, TRUE), FW_bdaddr_to_2U32(&cfm->bdAddr, FALSE), cfm->status);

    if (cfm->status != BT_STATUS_BUSY) {
        APP_ReConn_DeleteProfileMask(&cfm->bdAddr, PROFILE_A2DP, cfm->status);
        APP_ReConn_DeleteProfileMask(&cfm->bdAddr, PROFILE_AVRCP, cfm->status);
		APP_LinkKey_UpdateHistory((BD_ADDR_T*)&cfm->bdAddr,TRUE);
    }
}

static void app_A2dpSignalDisconnectCfmHandler(A2DP_SIGNAL_DISCONNECT_CFM_T *cfm)
{
    DBG_LOG_APP_A2DP("[APP_A2DP] Signal Disconnect Cfm : BdAddr : 0x%x%x, Status:0x%x", 3, FW_bdaddr_to_2U32(&cfm->bdAddr, TRUE), FW_bdaddr_to_2U32(&cfm->bdAddr, FALSE), cfm->status);
}

static void app_A2dpMediaConnectCfmHandler(A2DP_MEDIA_CONNECT_CFM_T *cfm)
{
	DBG_LOG_APP_A2DP( "[APP_A2DP] Media Connect Cfm : BdAddr : 0x%x%x, Status:0x%x", 3, FW_bdaddr_to_2U32(&cfm->bdAddr, TRUE), FW_bdaddr_to_2U32(&cfm->bdAddr, FALSE), cfm->status);

	#ifdef AIR_CODEC_SWITCH_WORKAROUND_SONY_XPERIA_ENABLE
	if( bt_sdps_pnp_is_sony_xperia((BD_ADDR_T*)&cfm->bdAddr.addr[0]) )
	{
		if(!cfm->status && bt_a2dp_get_reconfigure_status((BD_ADDR_T*)&cfm->bdAddr.addr[0]))
		{
			DBG_LOG_APP_A2DP( "[APP_A2DP] [Codec Work-Around] app media cfm", 0);
				
			APP_Avrcp_SetTimer((BD_ADDR_T*)&cfm->bdAddr.addr[0], APP_AVRCP_TIMER_CHECK_STREAMING_WORK_AROUND1, (3*ONE_SEC), 
				(U32)AVRCP_PLAYBACK_STATUS_PLAYING);
		}
	}
	#endif
}

static void app_A2dpMediaDisconnectCfmHandler(A2DP_MEDIA_DISCONNECT_CFM_T *cfm)
{
    DBG_LOG_APP_A2DP("[APP_A2DP] Media Disconnect Cfm: BdAddr : 0x%x%x, Status:0x%x", 3, FW_bdaddr_to_2U32(&cfm->bdAddr, TRUE), FW_bdaddr_to_2U32(&cfm->bdAddr, FALSE), cfm->status);
    app_A2dp_MusicStopped(&cfm->bdAddr, TRUE);
}

static void app_A2dpStartIndHandler(A2DP_START_IND_T *ind)
{
    BOOL audioDevReg;
    BD_ADDR_T *pBdAddr = &ind->bdAddr;

#ifdef AIR_AVRCP_PROFILE_ENABLE
    APP_AvrcpSetMusicPlay(pBdAddr, TRUE);
    APP_AvrcpResetKeyPlayToggle(pBdAddr);
#endif

    audioDevReg = app_A2dp_GetAudioDevRegister(pBdAddr);

    DBG_LOG_APP_A2DP("[APP_A2DP] Start Ind: BdAddr : 0x%x%x, AudioDevReg:%d, State:%d", 4 , FW_bdaddr_to_2U32(pBdAddr, TRUE), FW_bdaddr_to_2U32(pBdAddr, FALSE), audioDevReg, APP_State_GetTopState(pBdAddr));

    if (audioDevReg) {
        if (APP_State_CheckLinkInCallNotifyState(pBdAddr)) {
            APP_AudioDeviceRegister(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY);
            if (!APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_CALLACTIVE_FEAT)) {
                app_A2dp_AcceptStart(pBdAddr);
            } else {
                app_A2dp_MediaPktMemPut(pBdAddr);
            }
        } else {
            app_A2dp_AcceptStart(pBdAddr);
        }
    } else if (APP_State_CheckLinkInCallNotifyState(pBdAddr) && APP_AudioDeviceRegister(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY)) {
        if (!APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_CALLACTIVE_FEAT)) {
            app_A2dp_AcceptStart(pBdAddr);
        } else {
            app_A2dp_MediaPktMemPut(pBdAddr);
        }
    } else {
        if (APP_IsActiveAudioDevInAUX()) {
            if (APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_LINE_IN_FEAT)) {
                app_A2dp_MediaPktMemPut(pBdAddr);
            } else {
                app_A2dp_RejectStart(pBdAddr);
            }
        } else if (APP_IsActiveAudioDevInCall()) {
            if (APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_CALLACTIVE_FEAT)) {
                app_A2dp_MediaPktMemPut(pBdAddr);
            } else {
                app_A2dp_RejectStart(pBdAddr);
            }
        } else if (APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_OTHER_IN_MUSIC_FEAT) && APP_IsActiveAudioDevInMusic()) {
            app_A2dp_MediaPktMemPut(pBdAddr);
        } else {
            app_A2dp_RejectStart(pBdAddr);
        }
    }
}

static void app_A2dpStartCfmHandler(A2DP_START_CFM_T *cfm)
{
    BOOL audioDevReg;
    BD_ADDR_T *pBdAddr = &cfm->bdAddr;

#ifdef AIR_AVRCP_PROFILE_ENABLE
    APP_AvrcpSetMusicPlay(pBdAddr, TRUE);
    APP_AvrcpResetKeyPlayToggle(pBdAddr);
#endif
    App_SniffDisable(pBdAddr, APP_SNIFF_A2DP_MUSIC);
    audioDevReg = app_A2dp_GetAudioDevRegister(pBdAddr);

    if (cfm->isInt) {
        if (audioDevReg) {
            APP_A2dp_DspPlay(pBdAddr);
        }

        if (APP_State_CheckLinkInCallNotifyState(pBdAddr)) {
            APP_AudioDeviceRegister(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY);
        }
    } else {
        if (audioDevReg) {
            APP_A2dp_DspPlay(pBdAddr);
        }
    }
#ifdef AIR_CODEC_SWITCH_WORKAROUND_SONY_XPERIA_ENABLE
	if(bt_sdps_pnp_is_sony_xperia(pBdAddr))
	{
		DBG_LOG_APP_A2DP( "[APP_A2dp] [Codec Work-Around] Force Play", 0);
		APP_AvrcpDecideOperation(pBdAddr, AVC_OPERATION_FORCE_PLAY);
	}
#endif


}

static void app_A2dpSuspendIndHandler(A2DP_SUSPEND_IND_T *ind)
{
    app_A2dp_MusicStopped(&ind->bdAddr, FALSE);
    bt_a2dp_suspend_cmd_response(&ind->bdAddr, TRUE);
}

static void app_A2dpSuspendCfmHandler(A2DP_SUSPEND_CFM_T *cfm)
{
    app_A2dp_MusicStopped(&cfm->bdAddr, FALSE);
}

static void app_A2dpCloseCfmHandler(A2DP_CLOSE_CFM_T *cfm)
{
    App_ClearProfileInReconnectList(&cfm->bdAddr, PROFILE_AVRCP);
    app_A2dp_MusicStopped(&cfm->bdAddr, TRUE);
}

static U32 app_A2dp_IndHandler(Handler handler, U16 id, void *msg, U32 handler_id)
{
    UNUSED(handler);
    UNUSED(handler_id);
    switch (id) {
        case A2DP_START_SERVICE_CFM:
            app_A2dpStartServiceCfmHandler((A2DP_START_SERVICE_CFM_T *)msg);
            break;
        case A2DP_STOP_SERVICE_CFM:
            app_A2dpStopServiceCfmHandler((A2DP_STOP_SERVICE_CFM_T *)msg);
            break;
        case A2DP_SIGNAL_CONNECT_IND:
            app_A2dpSignalConnectIndHandler((A2DP_SIGNAL_CONNECT_IND_T *)msg);
            break;
        case A2DP_SIGNAL_CONNECT_CFM:
            app_A2dpSignalConnectCfmHandler((A2DP_SIGNAL_CONNECT_CFM_T *)msg);
            break;
        case A2DP_SIGNAL_DISCONNECT_CFM:
            app_A2dpSignalDisconnectCfmHandler((A2DP_SIGNAL_DISCONNECT_CFM_T *)msg);
            break;
        case A2DP_MEDIA_CONNECT_CFM:
            app_A2dpMediaConnectCfmHandler((A2DP_MEDIA_CONNECT_CFM_T *)msg);
            break;
        case A2DP_MEDIA_DISCONNECT_CFM:
            app_A2dpMediaDisconnectCfmHandler((A2DP_MEDIA_DISCONNECT_CFM_T *)msg);
            break;
        case A2DP_START_IND:
            app_A2dpStartIndHandler((A2DP_START_IND_T *)msg);
            break;
        case A2DP_START_CFM:
            app_A2dpStartCfmHandler((A2DP_START_CFM_T *)msg);
            break;
        case A2DP_SUSPEND_IND:
            app_A2dpSuspendIndHandler((A2DP_SUSPEND_IND_T *)msg);
            break;
        case A2DP_SUSPEND_CFM:
            app_A2dpSuspendCfmHandler((A2DP_SUSPEND_CFM_T *)msg);
            break;
        case A2DP_CLOSE_CFM:
            app_A2dpCloseCfmHandler((A2DP_CLOSE_CFM_T *)msg);
            break;

        default:
            DBG_LOG_APP_A2DP("[APP_A2DP] Rx Unknown Message : id: %d", 1, id);
            break;
    }
    return 0;
}

static void app_A2dp_MusicStopped(BD_ADDR_T *pBdAddr, BOOL isStop)
{
#ifdef A2DP_SRC_Profile
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_MUSIC);
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
    //MMI_LineIn_DriverCmd(DRIVER_STOP_LINE_IN_CMD);
#else
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY);
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);

    if (!a2dp_is_resume(pBdAddr) || isStop) {
        APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_MUSIC);
    }
    App_SniffEnable(pBdAddr, APP_SNIFF_A2DP_MUSIC);
    app_A2dp_MusicStopClearPara(pBdAddr);
#ifdef AIR_AVRCP_PROFILE_ENABLE
    APP_Avrcp_ReleaseTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC);
    APP_Avrcp_ReleaseTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC);
    APP_Avrcp_ReleaseTimer(pBdAddr, APP_AVRCP_TIMER_MONITOR_PLAY_STATUS);
#endif
    APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY);
    APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
    APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_MUSIC);
#endif
}

static void app_A2dp_MusicStopClearPara(BD_ADDR_T *pBdAddr)
{
#ifdef AIR_AVRCP_PROFILE_ENABLE
    if (!APP_Avrcp_isDisablePlayStatusMonitor(pBdAddr)) {
        APP_Avrcp_SetPlayStatus(pBdAddr, 0);
    }
    APP_AvrcpSetMusicPlay(pBdAddr, FALSE);
    APP_AvrcpResetKeyPlayToggle(pBdAddr);
#else
    UNUSED(pBdAddr);
#endif
}

static void app_A2dp_AcceptStart(BD_ADDR_T *pBdAddr)
{
    bt_a2dp_start_cmd_response(pBdAddr, TRUE, FALSE);
    APP_A2dp_DspPlay(pBdAddr);
}

static void app_A2dp_RejectStart(BD_ADDR_T *pBdAddr)
{
    APP_INFO_STRU *pLinkInfo = APP_GetAppLinkByBdAddr(pBdAddr);

    bt_a2dp_start_cmd_response(pBdAddr, FALSE, FALSE);
    FW_SetTimer((Handler)&gAppA2dpTimerHandle, APP_A2DP_DELAY_SUSPEND_TIMER, NULL, (U32)pLinkInfo, 1000);
}

static void app_A2dp_MediaPktMemPut(BD_ADDR_T *pBdAddr)
{
    bt_a2dp_start_cmd_response(pBdAddr, TRUE, TRUE);
	bt_a2dp_drop_pkt_setting(pBdAddr, TRUE);
}

static U32 app_A2dp_TimerHandler(Handler handler, U16 id, void *msg, U32 handler_id)
{
    APP_INFO_STRU *pLinkInfo;

    UNUSED(handler);
    UNUSED(msg);

    switch (id) {
        case APP_A2DP_DELAY_SUSPEND_TIMER:
            if ((pLinkInfo = (APP_INFO_STRU *)handler_id)) {
                APP_A2dp_SendPauseMusic(&pLinkInfo->bdAddr, FALSE);
            }
            break;
    }

    return 0;
}
/**************************************************************************************************
* Public API
**************************************************************************************************/
void APP_A2dp_RegisterProfile(void)
{
    a2dp_start_service((Handler)&gAppA2dpHandle);
}

void APP_A2dp_StopDSP(BD_ADDR_T *pBdAddr)
{
    bt_a2dp_set_meida_play(pBdAddr, FALSE);
    APP_A2dpDspStop(pBdAddr);
}

void APP_A2dp_SendPauseMusic(BD_ADDR_T *pBdAddr, U8 isCall)
{
    if (a2dp_is_in_streaming(pBdAddr) && !a2dp_is_resume(pBdAddr)) {
        APP_A2dp_StopDSP(pBdAddr);

        if (isCall && APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_CALLACTIVE_FEAT)) {
        }
#ifdef AIR_AVRCP_PROFILE_ENABLE
        else if (App_IsProfileInReconnectList(pBdAddr, PROFILE_AVRCP) || PM_IsProfileIdLoaded(pBdAddr, PROFILE_AVRCP)) {
            if (APP_IsDSPActive(pBdAddr)) {
                if (APP_Avrcp_isDisablePlayStatusMonitor(pBdAddr)) {
                    APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC, 2 * ONE_SEC, (U32)app_A2dp_GetPauseMusicCallBack);
                    APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_QUERY_CURRENT_PLAY_STATUS, 0, (U32)NULL);
                } else {
                    APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC, 0, (U32)app_A2dp_GetPlayStatusToPauseMusicCallBack);
                }
            } else {
                // Wait for AVRCP state transition
                // Just got A2DP connected. waiting for AVRCP
                APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC, HALF_SEC, (U32)app_A2dp_GetPlayStatusToPauseMusicCallBack);
            }
        }
#endif
        else {
            app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_NONE);
        }
    }
}

static BOOL app_A2dp_GetAudioDevRegister(BD_ADDR_T *pBdAddr)
{
    BOOL audioDevReg = APP_AudioDeviceRegister(pBdAddr, AUDIO_DEVICE_MUSIC);

#ifdef AIR_AVRCP_PROFILE_ENABLE
    if (AVRCP_PLAYBACK_STATUS_PLAYING == APP_Avrcp_GetPlayStatus(pBdAddr)) {
        audioDevReg |= APP_AudioDeviceRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
    }
#endif

    return audioDevReg;
}

BOOL APP_a2dp_is_connected(BD_ADDR_T *pBdAddr)
{
    return (a2dp_is_connected(pBdAddr)) ? TRUE : FALSE;
}

BOOL APP_a2dp_is_in_streaming(BD_ADDR_T *pBdAddr)
{
    return (a2dp_is_in_streaming(pBdAddr) && !a2dp_is_resume(pBdAddr)) ? TRUE : FALSE;
}

void APP_A2dp_ClearResumeState(BD_ADDR_T *pBdAddr)
{
    a2dp_set_resume(pBdAddr, FALSE);
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_MUSIC);
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
}

#ifdef AIR_AVRCP_PROFILE_ENABLE
void APP_A2dp_MonitorPlayStatus(BD_ADDR_T *pBdAddr, U8 isSuccessful)
{
    if (isSuccessful) {
        APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_MONITOR_PLAY_STATUS, HALF_SEC, (U32)APP_A2dp_MonitorPlayStatus);
    }
}

static void app_A2dp_GetPlayStatusToPauseMusicCallBack(BD_ADDR_T *pBdAddr, U8 isSuccessful)
{
#ifdef AIR_AVRCP_PROFILE_ENABLE
    if (isSuccessful) {
        APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC, ONE_SEC, (U32)app_A2dp_GetPauseMusicCallBack);
    } else
#else
    UNUSED(isSuccessful);
#endif
    {
        if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
            app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_STOPPED);
        }
    }
}

static void app_A2dp_GetPauseMusicCallBack(BD_ADDR_T *pBdAddr, U8 isSuccessful)
{
    UNUSED(isSuccessful);
    if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
        app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_STOPPED);
    }
}

void APP_A2dp_CheckPlayStatusConsistency(BD_ADDR_T *pBdAddr, U8 playStatus, U8 needDelay)
{
    if (playStatus == AVRCP_PLAYBACK_STATUS_PLAYING) {
        if (a2dp_is_open(pBdAddr)) { //// play status is playing but no AVDTP_START received
            APP_AvrcpCheckStreamingStateLater(pBdAddr, playStatus, needDelay);
        }
    }
}

void APP_A2dp_PlayStatusChanged(BD_ADDR_T *pBdAddr, U8 playStatus)
{
#ifdef AIR_AVRCP_PROFILE_ENABLE
    switch (playStatus) {
        case AVRCP_PLAYBACK_STATUS_PLAYING:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC) || APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
                    app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_PLAYING);
                }
            } else if (a2dp_is_in_streaming(pBdAddr)) {
                BOOL audioDevReg = APP_AudioDeviceRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
                if (APP_State_AllLinksInCallRelatedState()) {
                    if (!APP_State_CheckLinkInCallActiveState(pBdAddr) && !APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_CALLACTIVE_FEAT)) {
                        a2dp_set_resume(pBdAddr, TRUE);
                        app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_PLAYING);
                    }
                } else if (audioDevReg) {
                    APP_A2dp_DspPlay(pBdAddr);
                }
            } else {
                APP_A2dp_CheckPlayStatusConsistency(pBdAddr, playStatus, FALSE);
            }
            break;

        case AVRCP_PLAYBACK_STATUS_STOPPED:
        case AVRCP_PLAYBACK_STATUS_PAUSED:
            APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC) || APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                APP_A2dp_StopDSP(pBdAddr);
            } else {
                APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
            }
            break;
        case AVRCP_PLAYBACK_STATUS_FWD_SEEK:
        case AVRCP_PLAYBACK_STATUS_REV_SEEK:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC, HALF_SEC, (U32)app_A2dp_GetPlayStatusToPauseMusicCallBack);
            }
            break;
        case AVRCP_PLAYBACK_STATUS_REJECT:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
                    app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_PLAYING);
                }
            }
            break;
    }
#else
    UNUSED(pBdAddr);
    UNUSED(playStatus);
#endif
}

void APP_A2dp_PlayStatusTheSame(BD_ADDR_T *pBdAddr, U8 playStatus)
{
#ifdef AIR_AVRCP_PROFILE_ENABLE
    switch (playStatus) {
        case AVRCP_PLAYBACK_STATUS_PLAYING:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC) || APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
                    app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_PLAYING);
                }
            } else if (a2dp_is_in_streaming(pBdAddr)) {
                if (APP_State_AllLinksInCallRelatedState()) {
                    if (!APP_State_CheckLinkInCallActiveState(pBdAddr) && !APP_A2dp_NVKeyIsFeatureOn(APP_A2DP_MEMPUT_WHEN_CALLACTIVE_FEAT)) {
                        a2dp_set_resume(pBdAddr, TRUE);
                        app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_PLAYING);
                    }
                }
            }
            break;

        case AVRCP_PLAYBACK_STATUS_STOPPED:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
                    app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_STOPPED);
                }
            }
        /* fallthrough */
        case AVRCP_PLAYBACK_STATUS_PAUSED:
            APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC);
            //APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC);
            break;
        case AVRCP_PLAYBACK_STATUS_FWD_SEEK:
        case AVRCP_PLAYBACK_STATUS_REV_SEEK:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_SEND_GET_PLAY_STATUS_TO_PAUSE_MUSIC, HALF_SEC, (U32)app_A2dp_GetPlayStatusToPauseMusicCallBack);
            }
            break;
        case AVRCP_PLAYBACK_STATUS_REJECT:
            if (APP_Avrcp_CheckTimer(pBdAddr, APP_AVRCP_TIMER_SEND_PAUSE_MUSIC)) {
                if (!APP_State_CheckLinkInCallActiveState(pBdAddr)) {
                    app_A2dp_SendPause(pBdAddr, AVRCP_PLAYBACK_STATUS_PLAYING);
                }
            }
            break;
    }
#else
    UNUSED(pBdAddr);
    UNUSED(playStatus);
#endif
}


#endif

void APP_A2dp_SendResume(BD_ADDR_T *pBdAddr)
{
#ifdef AIR_AVRCP_PROFILE_ENABLE
    if (AVRCP_IsConnected(pBdAddr)) {
        APP_AvrcpDecideOperation(pBdAddr, AVC_OPERATION_PLAY);
        APP_A2dp_ClearResumeState(pBdAddr);
    } else
#endif
    {
        bt_a2dp_start_request(pBdAddr);
    }
}

static void app_A2dp_SendPause(BD_ADDR_T *pBdAddr, U8 playStatus)
{
    bt_a2dp_set_meida_play(pBdAddr, FALSE);

#ifdef AIR_AVRCP_PROFILE_ENABLE
    if (AVRCP_IsConnected(pBdAddr)) {
        switch (playStatus) {
            case AVRCP_PLAYBACK_STATUS_PLAYING:
                APP_AvrcpDecideOperation(pBdAddr, AVC_OPERATION_PAUSE);
                //a2dp_set_resume(pBdAddr, TRUE);

                if (!APP_Avrcp_isDisablePlayStatusMonitor(pBdAddr)) {
                    APP_Avrcp_SetTimer(pBdAddr, APP_AVRCP_TIMER_MONITOR_PLAY_STATUS, 200, (U32)APP_A2dp_MonitorPlayStatus);
                    APP_Avrcp_SetPlayStatus(pBdAddr, AVRCP_PLAYBACK_STATUS_PAUSED);
                }
                break;
            case AVRCP_PLAYBACK_STATUS_STOPPED:
                APP_AvrcpDecideOperation(pBdAddr, AVC_OPERATION_STOP);
                /* fallthrough *//*comment to prevent coverity warning*/
            case AVRCP_PLAYBACK_STATUS_PAUSED:
                break;
            case AVRCP_PLAYBACK_STATUS_FWD_SEEK:
            case AVRCP_PLAYBACK_STATUS_REV_SEEK:
                break;

            default:
                APP_AvrcpDecideOperation(pBdAddr, AVC_OPERATION_STOP);
                break;

        }
    } else
#else
    UNUSED(playStatus);
#endif
    {
        bt_a2dp_suspend_request(pBdAddr);
    }

    // Reset the resume record in other link in case of confusion.

#ifdef SUPPORT_MULTI_POINT
    if (a2dp_is_resume(pBdAddr) && a2dp_is_in_streaming(pBdAddr)) {
        U8 linkIndex = APP_GetLinkIndexByBdAddr(pBdAddr);

        for (U8 nextActiveLink = 0; nextActiveLink < FW_MAX_LINK_IDX; nextActiveLink++) {
            if (nextActiveLink == linkIndex || !APP_IsActiveLink(APP_GetBdAddrByLinkIndex(nextActiveLink))) {
                continue;
            }

            APP_A2dp_ClearResumeState(APP_GetBdAddrByLinkIndex(nextActiveLink));
        }
    }
#endif

}

static void app_A2dp_RemoveAudioLink(BD_ADDR_T *pBdAddr)
{
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY);
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
    APP_AudioDeviceDeRegister(pBdAddr, AUDIO_DEVICE_MUSIC);
    APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_MUSIC_CALL_NOTIFY);
    APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_AVRCP_PLAY);
    APP_ResumeOtherAudioDevice(pBdAddr, AUDIO_DEVICE_MUSIC);
}

static void app_A2dp_DspOn(BD_ADDR_T *pBdAddr)
{
    AUDIO_DSP_START_PARA_STUR audioDspPara;
    U8 sampleRateIndex = 0xFF;
    U8 codec = a2dp_get_codec(pBdAddr);

    if ((sampleRateIndex = bt_a2dp_get_sample_rate_index(pBdAddr, codec)) == UNUSED_SAMPLE_RATE_INDEX) 
    {
        return;
    }

    if (!codec) 
    {
        return;
    }
    
    FW_Memset(&audioDspPara, 0, sizeof(AUDIO_DSP_START_PARA_STUR));
    FW_Memcpy(&audioDspPara.bdAddr, pBdAddr, sizeof(BD_ADDR_T));
    audioDspPara.audioType = AUDIO_A2DP;
    audioDspPara.codec = codec;
    audioDspPara.a2dpPara.scms = a2dp_get_scms(pBdAddr);
    audioDspPara.a2dpPara.sampleRateIndex = sampleRateIndex;
    if (APP_AudioDspPlay(&audioDspPara)) 
    {

        #ifdef AIR_A2DP_PROFILE_ENABLE

        DBG_LOG_APP_A2DP("[APP_A2DP] Audioable BdAddr : 0x%x%x", 2, FW_bdaddr_to_2U32(pBdAddr, TRUE), FW_bdaddr_to_2U32(pBdAddr, FALSE));

        APP_VolManage_SpkVolumeRemoteHandler(pBdAddr, APP_VolManage_GetCurrentA2dpSoundLevel(pBdAddr), COMPONENT_A2DP);
        #else
        UNUSED(pBdAddr);
        #endif
        APP_Qos_SetQos(pBdAddr, QOS_SERVICE_GUARANTEED);
    }
}

void APP_A2dp_ClearCtlData(BD_ADDR_T *pBdAddr)
{
    App_ClearProfileInReconnectList(pBdAddr, PROFILE_AVRCP);
    app_A2dp_RemoveAudioLink(pBdAddr);
    app_A2dp_MusicStopClearPara(pBdAddr);
}

void APP_A2dp_NotifyDSPStatus(BD_ADDR_T *pBdAddr, BOOL isEnable)
{
    if (isEnable) {
        if (APP_IsSetAppLink(pBdAddr)) {
            APP_VolManage_SpkVolumeRemoteHandler(pBdAddr, APP_VolManage_GetCurrentA2dpSoundLevel(pBdAddr), COMPONENT_A2DP);
            bt_a2dp_set_meida_play(pBdAddr, TRUE);
            APP_Media_PushMediaEvent(MEDIA_EVT_A2DP_ENABLE);
        }
    } else {
        bt_a2dp_set_meida_play(pBdAddr, FALSE);
        APP_Media_PushMediaEvent(MEDIA_EVT_A2DP_DISABLE);
    }
}

void APP_A2dp_Init()
{
    APP_A2dp_NVKeyInit();
}

void APP_A2dp_DspPlay(BD_ADDR_T *pBdAddr)
{
	app_A2dp_DspOn(pBdAddr);   
}

void APP_A2dpDspStop(BD_ADDR_T *pBdAddr)
{
    AUDIO_DSP_STOP_PARA_STUR audioDspPara;

    FW_Memset(&audioDspPara, 0, sizeof(AUDIO_DSP_STOP_PARA_STUR));
    FW_Memcpy(&audioDspPara.bdAddr, pBdAddr, sizeof(BD_ADDR_T));
    audioDspPara.audioType = AUDIO_A2DP;
    if (APP_AudioDspStop(&audioDspPara)) {
        APP_Qos_SetQos(pBdAddr, QOS_SERVICE_BEST_EFFORT);
    }
}

void APP_A2dp_GameModeOn(void)
{
#ifdef APP_GAME_MODE
    drv_a2dp_set_game_mode(TRUE);
#endif
}

void APP_A2dp_GameModeOff(void)
{
#ifdef APP_GAME_MODE
    drv_a2dp_set_game_mode(FALSE);
#endif
}

void APP_A2dp_GameModeToggle(void)
{
#ifdef APP_GAME_MODE
	if(drv_a2dp_get_game_mode())
	{
		APP_A2dp_GameModeOff();
	}
	else
	{
		APP_A2dp_GameModeOn();
	}
#endif    
}

