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
#include "bt_race_command.h"
#include "APP_HfpScoHandler.h"
#include "App_ResourceManager.h"
#include "App_State.h"
#include "AudioDSP_StreamManager.h"
#include "APP_AirApp.h"
#include "App_Hfp.h"

#if 0 /* Unused LOG_PRINT_156X */
#define DBG_LOG_APP_RACE_FOTA(_message, arg_cnt, ...)    printf(_message, ##__VA_ARGS__)
#else	
#define DBG_LOG_APP_RACE_FOTA(_message, arg_cnt, ...)    LOG_MSGID_I(APP_RACE_FOTA, _message, arg_cnt, ##__VA_ARGS__)
#endif
log_create_module(APP_RACE_FOTA, PRINT_LEVEL_INFO);


/**************************************************************************************************
* Variable
**************************************************************************************************/
static U32 APP_RaceCmd_FotaHandler(Handler handler, U16 id, void *msg, U32 handler_id);
static HandlerData gAppRaceCmdFotaHandle = {APP_RaceCmd_FotaHandler};

/**************************************************************************************************
* Static Functions
**************************************************************************************************/
static void app_RaceCmd_FotaStartInd(void)
{
    BD_ADDR_T *pBdAddr;
	DBG_LOG_APP_RACE_FOTA("[APP] FOTA start Ind:%d", 1, APP_AudioIsDspSuspend());
    
    pBdAddr = APP_GetServiceBdAddr();
    if(pBdAddr)
        PM_Sniff_Disable(pBdAddr, PM_SNIFF_OTA);

    if(APP_AudioIsDspSuspend())
        APP_HfpSco_DisconnectAllSco();
}

static void app_RaceCmd_FotaStopInd(void)
{
	BD_ADDR_T *pBdAddr = APP_GetServiceBdAddr();
	
	DBG_LOG_APP_RACE_FOTA("[APP] FOTA stop Ind:%d", 1, APP_AirApp_FOTA_Reconnect());
    
<<<<<<< HEAD
=======
    if (APP_AudioIsDspSuspend())
		APP_AudioDSPRealtimeResume();

>>>>>>> db20e11 (second commit)
    if(pBdAddr)
        PM_Sniff_Enable(pBdAddr, PM_SNIFF_OTA);

	if(pBdAddr && !APP_AirApp_FOTA_Reconnect() && APP_State_CheckLinkInCallActiveState(pBdAddr))
	{
		if (APP_IsActiveLink(pBdAddr))
		{
			if (!APP_SCO_EXISTS(pBdAddr))
			{
				//logPrint(LOG_APP_SYSTEM, PRINT_LEVEL_INFO, APP_RaceCmdFotaStopReconnectScoLogString, 0);
				APP_HFP_CreateAudioConnection(pBdAddr, TRUE);
			}
		}
	}
}

static U32 APP_RaceCmd_FotaHandler(Handler handler, U16 id, void *msg, U32 handler_id)
{

    UNUSED(handler);
	UNUSED(msg);
	UNUSED(handler_id);

	switch(id)
	{
		case MSG_ID_RACE_TO_APP_FOTA_START:
			app_RaceCmd_FotaStartInd();
			break;

		case MSG_ID_RACE_TO_APP_FOTA_STOP:
			app_RaceCmd_FotaStopInd();
			break;
	}

	return 0;
}

/**************************************************************************************************
* Public Functions
**************************************************************************************************/
void APP_RaceCmd_FotaInit()
{
	RACE_App_Fota_RegisterHandler(&gAppRaceCmdFotaHandle);
}
