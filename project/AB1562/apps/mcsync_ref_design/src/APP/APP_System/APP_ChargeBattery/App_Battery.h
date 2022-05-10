/* Copyright Statement:
 *
 * (C) 2019  Airoha Technology Corp. All rights reserved.
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

#ifndef _APP_BATTERY_H_
#define _APP_BATTERY_H_

/**************************************************************************************************
* Structure
**************************************************************************************************/
typedef struct
{
	U8 batStatus;
	U8 currentLedDuration;
	U8 statePowerOff;
	BOOL isDoingRHO;
	U16 statusDuringDelay;
	U8 smartCaseBatLevel;
}APP_BAT_INFO_STRU;
/**************************************************************************************************
* Public Functions
**************************************************************************************************/
void APP_ChgBat_UpdateBatStatus(U8 batStatus);
void APP_ChgBat_PushBatChgMediaEvt(void);
void APP_ChgBat_SetDelayChgCplMediaEvt(void);
void APP_ChgBat_ReleaseDelayChgCplMediaEvt(void);
void APP_ChgBat_SetTimeOutDectionTimer(void);
void APP_ChgBat_SetBatterMonitorTimer(void);
void APP_ChgBat_CheckCurrentBatLevel(void);
U8 APP_ChgBat_GetLevelInQuarter(void);
U8 APP_ChgBat_GetPwrOnLowBatAction(void);
U16 APP_Battery_GetBatInThousandPercent(void);
void APP_ChgBat_ReleaseSwitchOffInLowBatTimer(void);
void APP_ChgBat_ReleaseTimeOutDectionTimer(void);
void APP_ChgBat_CheckBatStatus(void);//MMI_PollingBatStatus(void)
BOOL APP_Battery_IsBelowInitBat(void);
BOOL APP_Battery_IsBelowLowLevel(void);
U8 APP_ChgBat_GetBatStatus(void);
void APP_ChgBat_SetBatStatus(U8 batStatus);
BOOL APP_Battery_IsBelowShutDownLevel(void);
void APP_ChgBat_ReportBatteryStatus(void);
void APP_ChgBat_ResetTimeOutDectionTimer(void);

void APP_ChgBat_SetDoingRHO(void);
void APP_ChgBat_SetRHOFinished(void);
BOOL APP_ChgBat_IsRHOForChgCase(void);
U8 APP_ChgBat_GetPowerOffState(void);
void APP_ChgBat_SetPowerOffState(U8 statePowerOff);
void APP_Battery_ReadInformationConfig(void);
void APP_Battery_Init(void);
U8 APP_Battery_GetSmartCaseBatLevel(void);
void APP_Battery_SetSmartCaseBatLevel(U8 batLevel);

#endif //_APP_BATTERY_H_
