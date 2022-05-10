/* Copyright Statement:
 *
 * (C) 2020  Airoha Technology Corp. All rights reserved.
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
#include "race_cmd.h"
#include "Peq_NvkeyHandler.h"
#include "App_PeqProcess.h"
#include "AudioDSP_Vp.h"
#include "drv_sco.h"

static U32 app_racecmd_hostaudio_handler(Handler app, U16 id, void *msg, U32 id_ext);
static const HandlerData gAppRaceCmdHostAudioHandle = { app_racecmd_hostaudio_handler };

static U32 app_racecmd_hostaudio_handler(Handler app, U16 id, void *msg, U32 id_ext)
{
    HOST_AUDIO_MODULE_T *cmd = (HOST_AUDIO_MODULE_T *)msg;
    switch(id)
    {
        case MODULE_PEQ_GROUP_INDEX:
<<<<<<< HEAD
            APP_PeqProc_SetIndex(PEQ_A2DP, cmd->peq.peq_group_index);
=======
            APP_PeqNvkey_Init();
            APP_PeqProc_SetIndex(PEQ_A2DP, cmd->peq.peq_group_index);
            APP_PeqProc_Load(PEQ_A2DP);
>>>>>>> db20e11 (second commit)
            break;
        case MODULE_LINE_IN_PEQ_GROUP_INDEX:
            APP_PeqProc_SetIndex(PEQ_LINE_IN, cmd->peq.peq_group_index);
            break;
<<<<<<< HEAD
            
        case MODULE_VP_ON_OFF:
            if(cmd->vp_on_off.vp_status == VP_ON)   
=======

        case MODULE_VP_ON_OFF:
            if(cmd->vp_on_off.vp_status == VP_ON)
>>>>>>> db20e11 (second commit)
            {
                APP_VpEnableVoicePrompt();
            }
            else
            {
                APP_VpDisableVoicePrompt();
            }
            break;
        case MODULE_VP_LANGUAGE:
        case MODULE_VP_GET:
        case MODULE_ANC_STATUS:
        case MODULE_GAME_MODE:
        case MODULE_PASSTHRU_GAIN:
            // not - support
            break;
        case MODULE_VP_SET:
            APP_VpSetLanguage(cmd->vp_lang.lang_id);
            break;
<<<<<<< HEAD
            
        case MODULE_ECNR:
            drv_sco_set_ecnr_off((cmd->is_ecnr_on) ? TRUE : FALSE);
            break;
            
=======

        case MODULE_ECNR:
            drv_sco_set_ecnr_off((cmd->is_ecnr_on) ? TRUE : FALSE);
            break;

>>>>>>> db20e11 (second commit)
        case MODULE_MIC_SWAP:
            drv_sco_mic_switch((cmd->is_main_mic) ? 0 : 1);
            break;
    }
    UNUSED(id_ext);
    UNUSED(app);
    return 0;
}

/******************************************************************************
* Public Functions
*******************************************************************************/

void app_racecmd_hostaudio_init(void)
{
    race_hostaudio_register_handler((Handler)&gAppRaceCmdHostAudioHandle);
}
