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
 
 
#ifndef __APP_NVKEY_KEYMAP_HH__
	#define __APP_NVKEY_KEYMAP_HH__
/**************************************************************************************************
* Define
**************************************************************************************************/


#if 0//for generate xml value

#define KEY_TAP_ACTION	\
		{KEY1, KEY_ACPCALL,(KEY_MAP_APP_HFP_INCOMMING)},															\
		{KEY1, KEY_ENDCALL, (KEY_MAP_APP_HFP_CALLACTIVE|KEY_MAP_APP_HFP_CALLACTIVE_WITHOUT_SCO)},					\
		{KEY5, KEY_RECONNECT_USER_INIT, (KEY_MAP_APP_CONDISCABLE|KEY_MAP_APP_CONNECTABLE|KEY_MAP_APP_CONNECTED|		\
											KEY_MAP_APP_MP3)},														\
		{KEY5, KEY_CNLOUTGOING, (KEY_MAP_APP_HFP_OUTGOING|KEY_MAP_APP_HFP_CAOGG)},									\
		{KEY3, KEY_VOICEUP, (KEY_MAP_APP_CONNECTED|KEY_MAP_APP_HFP_INCOMMING|										\
							KEY_MAP_APP_HFP_OUTGOING|KEY_MAP_APP_HFP_CALLACTIVE|									\
							KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAOGG|											\
							KEY_MAP_APP_HFP_CAMULTY|KEY_MAP_APP_LINE_IN|KEY_MAP_APP_MP3)},							\
		{KEY4, KEY_VOICEDN, (KEY_MAP_APP_CONNECTED|KEY_MAP_APP_HFP_INCOMMING|										\
							KEY_MAP_APP_HFP_OUTGOING|KEY_MAP_APP_HFP_CALLACTIVE|									\
							KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAOGG|											\
							KEY_MAP_APP_HFP_CAMULTY|KEY_MAP_APP_LINE_IN|KEY_MAP_APP_MP3)},							\
																													\
		/* A2DP */																									\
		{KEY6, KEY_AVRCP_PLAY, KEY_MAP_APP_CONNECTED},																\
		{KEY7, KEY_AVRCP_FORWARD, KEY_MAP_APP_CONNECTED},															\
		/* MP3 */																									\
		{KEY6, KEY_MP3_PLAY, KEY_MAP_APP_MP3},																		\
		{KEY7, KEY_MP3_FORWARD, KEY_MAP_APP_MP3},																	\
		/* 3 way calling */																							\
		{KEY6, KEY_3WAYRELNACP,(KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAMULTY)},									\
		{KEY7, KEY_3WAYHOLDNACP, (KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAMULTY)},									\
		/* Test mode */																								\
		{KEY1, KEY_SWITCH_TEST_MODE_STATE, KEY_MAP_APP_TEST_MODE},													\
		{KEY5, KEY_SWITCH_TEST_MODE_TX_PACKET_TYPE, KEY_MAP_APP_TEST_MODE},											\
		{KEY6, KEY_MICUP, KEY_MAP_APP_HFP_CALLACTIVE},																\
		{KEY7, KEY_MICDN, KEY_MAP_APP_HFP_CALLACTIVE},

#define KEY_PRESS_ACTION	\
		{KEY5, KEY_REJCALL, KEY_MAP_APP_HFP_INCOMMING},																\
		{KEY5, KEY_ONHOLD_CALL, KEY_MAP_APP_HFP_CALLACTIVE|KEY_MAP_APP_HFP_CALLACTIVE_WITHOUT_SCO},					\
		{KEY5, KEY_MEDIA_TRIGGER_1, (KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CALLACTIVE)},							\
		{KEY6, KEY_3WAYRELNUDUB, (KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAMULTY) },									\

#define KEY_PRESS_RELEASE_ACTION	\
		{KEY1, KEY_RESET,(KEY_MAP_APP_EEPROM_UPDATING)},															\

#define KEY_LONG_PRESS_ACTION	\
		{KEY5, KEY_SET_VOICE_RECOGNITION, KEY_MAP_APP_CONNECTED|KEY_MAP_APP_MP3},													\
		{KEY1, KEY_POWER_ON, (KEY_MAP_APP_FAKEOFF|KEY_MAP_APP_FAKEON)},												\
		{KEY1, KEY_POWER_OFF, KEY_MAP_APP_ALL_STATES & ~(KEY_MAP_APP_OFF|KEY_MAP_APP_FAKEOFF|						\
								KEY_MAP_APP_EEPROM_UPDATED_OK|KEY_MAP_APP_EEPROM_UPDATED_FAIL|						\
								KEY_MAP_APP_EEPROM_UPDATING|KEY_MAP_APP_DETACHING_LINK)},							\
		{KEY6, KEY_VOICE_COMMAND_ENABLE, (KEY_MAP_APP_CONDISCABLE|KEY_MAP_APP_CONNECTABLE|							\
											KEY_MAP_APP_CONNECTED)},												\
		{KEY7, KEY_MP3_POWERON, KEY_MAP_APP_FAKEON|KEY_MAP_APP_CONNECTABLE|KEY_MAP_APP_CONDISCABLE|KEY_MAP_APP_CONNECTED},				\
		{KEY7, KEY_MP3_POWEROFF, KEY_MAP_APP_MP3},																	\

#define KEY_LONG_PRESS_RELEASE_ACTION	\
		{KEY1, KEY_RECONNECT_AFTER_POWER_ON, KEY_MAP_APP_CONNECTABLE|KEY_MAP_APP_FAKEON},							\

#define KEY_DOUBLE_ACTION	\
		{KEY1, KEY_RDIAL, KEY_MAP_APP_CONNECTED|KEY_MAP_APP_MP3},																	\
		{KEY5, KEY_MIC_MUTE_TOGGLE, (KEY_MAP_APP_HFP_CALLACTIVE|KEY_MAP_APP_HFP_CAMULTY)},							\
		/*{KEY6, KEY_AVRCP_STOP, KEY_MAP_APP_CONNECTED},*/															\
		/*{KEY6, KEY_MP3_STOP, KEY_MAP_APP_MP3},*/																		\
		{KEY7, KEY_AVRCP_BACKWARD, KEY_MAP_APP_CONNECTED},															\
		{KEY7, KEY_MP3_BACKWARD, KEY_MAP_APP_MP3},															\
		{KEY7, KEY_3WAYADD, (KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAMULTY)},										\
		{KEY6, KEY_3WAYCALLTRANSFER, (KEY_MAP_APP_HFP_CAIMG|KEY_MAP_APP_HFP_CAMULTY)},								\
		{KEY5, KEY_PEQ_GROUP_CHANGE, KEY_MAP_APP_CONNECTED| KEY_MAP_APP_LINE_IN | KEY_MAP_APP_MP3},									\
        {KEY4, KEY_SCO_SWITCH, KEY_MAP_APP_HFP_INCOMMING| KEY_MAP_APP_HFP_OUTGOING| KEY_MAP_APP_HFP_CALLACTIVE		\
								KEY_MAP_APP_HFP_CAIMG| KEY_MAP_APP_HFP_CAOGG| KEY_MAP_APP_HFP_CAMULTY},				\

#define KEY_TRIPLE_ACTION	\
		{KEY1, KEY_ENTER_TESTMODE,KEY_MAP_APP_CONDISCABLE},															\
		{KEY5, KEY_AUDIO_TRANSFER,( KEY_MAP_APP_HFP_CALLACTIVE|KEY_MAP_APP_HFP_INCOMMING|KEY_MAP_APP_HFP_OUTGOING|	\
									KEY_MAP_APP_HFP_CALLACTIVE_WITHOUT_SCO|KEY_MAP_APP_HFP_CAIMG|					\
									KEY_MAP_APP_HFP_CAOGG|KEY_MAP_APP_HFP_CAMULTY)},								\
		{KEY7, KEY_ANC_SWITCH,(KEY_MAP_APP_FAKEON|KEY_MAP_APP_CONNECTABLE|KEY_MAP_APP_CONDISCABLE|KEY_MAP_APP_CONNECTED|KEY_MAP_APP_MP3|KEY_MAP_APP_HFP_CALLACTIVE)},	\
		{KEY6, KEY_CONNECTED_TO_DISCOVERABLE, KEY_MAP_APP_CONNECTED|KEY_MAP_APP_HFP_INCOMMING|						\
												KEY_MAP_APP_HFP_OUTGOING|KEY_MAP_APP_HFP_CALLACTIVE|				\
												KEY_MAP_APP_HFP_CALLACTIVE_WITHOUT_SCO|KEY_MAP_APP_HFP_CAIMG|		\
												KEY_MAP_APP_HFP_CAOGG|KEY_MAP_APP_HFP_CAMULTY|KEY_MAP_APP_MP3},		\

#define KEY_LONG_LONG_PRESS_ACTION	\
		{KEY1, KEY_DISCOVERABLE, KEY_MAP_APP_CONNECTABLE|KEY_MAP_APP_CONNECTED|										\
									KEY_MAP_APP_CONDISCABLE},														\

#define KEY_REPEAT_ACTION																							\
		{KEY3, KEY_VOICEUP,(KEY_MAP_MMI_CONNECTED|KEY_MAP_MMI_HFP_INCOMMING|										\
							KEY_MAP_MMI_HFP_OUTGOING|KEY_MAP_MMI_HFP_CALLACTIVE|									\
							KEY_MAP_MMI_HFP_CAIMG|KEY_MAP_MMI_HFP_CAOGG|											\
							KEY_MAP_MMI_HFP_CAMULTY|KEY_MAP_MMI_LINE_IN)},											\
		{KEY4, KEY_VOICEDN,(KEY_MAP_MMI_CONNECTED|KEY_MAP_MMI_HFP_INCOMMING|										\
							KEY_MAP_MMI_HFP_OUTGOING|KEY_MAP_MMI_HFP_CALLACTIVE|									\
							KEY_MAP_MMI_HFP_CAIMG|KEY_MAP_MMI_HFP_CAOGG|											\
							KEY_MAP_MMI_HFP_CAMULTY|KEY_MAP_MMI_LINE_IN)},											\

#endif

#define maxSettingNum 5

/*NvkeyDefine NVKEYID_APP_KEY_ACTION_TAP*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_PRESS*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_PRESS_RELEASE*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_LONG_PRESS*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_LONG_PRESS_RELEASE*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_DOUBLE*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_TRIPLE*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_LONG_LONG_PRESS*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_LONGLONGPRESS_RELEASE*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_EXTREMELY_LONGPRESS*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_EXTREMELY_LONGPRESS_RELEASE*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_REPEAT*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_DOWN*/
/*NvkeyDefine NVKEYID_APP_KEY_ACTION_UP*/
typedef struct
{
	U8 keyCode;
	U16 appKeyEvent;
	U32 keySupportedState;
}PACKED AppKeyMapType;

typedef struct
{
	U8 action;
	AppKeyMapType KeyMapType;
}PACKED UserKey;

#endif //__APP_NVKEY_KEYMAP_HH__

