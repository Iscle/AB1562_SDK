################################################################################
# Makefile Define
################################################################################
ifeq ($(FEATURE_FILE_SYSTEM),y)
ifeq ($(AB1532),y)
else
CCFLAG      +=  -DFEATURE_FILE_SYSTEM
endif
endif

################################################################################
# Syslog
################################################################################
ifeq ($(MTK_SYSLOG_VERSION_2),y)
CCFLAG      +=  -DMTK_SYSLOG_VERSION_2
endif

ifeq ($(MTK_SYSLOG_SUB_FEATURE_STRING_LOG_SUPPORT),y)
CCFLAG      +=  -DMTK_SYSLOG_SUB_FEATURE_STRING_LOG_SUPPORT
endif

ifeq ($(MTK_SYSLOG_SUB_FEATURE_BINARY_LOG_SUPPORT), y)
CCFLAG += -DMTK_SYSLOG_SUB_FEATURE_BINARY_LOG_SUPPORT
endif

ifeq ($(MTK_SYSLOG_SUB_FEATURE_MSGID_TO_STRING_LOG_SUPPORT), y)
CFLAGS += -DMTK_SYSLOG_SUB_FEATURE_MSGID_TO_STRING_LOG_SUPPORT
endif

ifeq ($(MTK_SYSLOG_SUB_FEATURE_OFFLINE_DUMP_ACTIVE_MODE), y)
CCFLAG += -DMTK_SYSLOG_SUB_FEATURE_OFFLINE_DUMP_ACTIVE_MODE
endif

ifeq ($(MTK_DEBUG_PLAIN_LOG_ENABLE),y)
CCFLAG      +=  -DMTK_DEBUG_PLAIN_LOG_ENABLE
endif

ifeq ($(MTK_PORT_SERVICE_ENABLE),y)
CCFLAG += -DMTK_PORT_SERVICE_ENABLE
endif

ifeq ($(MTK_CPU_NUMBER_0),y)
CCFLAG      +=  -DMTK_CPU_NUMBER_0
CCFLAG      +=  -DMTK_MAX_CPU_NUMBER_1
endif

MTK_DEBUG_LEVEL ?= debug

ifeq ($(MTK_DEBUG_LEVEL),)
CCFLAG += -DMTK_DEBUG_LEVEL_DEBUG
CCFLAG += -DMTK_DEBUG_LEVEL_INFO
CCFLAG += -DMTK_DEBUG_LEVEL_WARNING
CCFLAG += -DMTK_DEBUG_LEVEL_ERROR
endif

ifeq ($(MTK_DEBUG_LEVEL),error)
CCFLAG += -DMTK_DEBUG_LEVEL_ERROR
endif

ifeq ($(MTK_DEBUG_LEVEL),warning)
CCFLAG += -DMTK_DEBUG_LEVEL_WARNING
CCFLAG += -DMTK_DEBUG_LEVEL_ERROR
endif

ifeq ($(MTK_DEBUG_LEVEL),info)
CCFLAG += -DMTK_DEBUG_LEVEL_INFO
CCFLAG += -DMTK_DEBUG_LEVEL_WARNING
CCFLAG += -DMTK_DEBUG_LEVEL_ERROR
endif

ifeq ($(MTK_DEBUG_LEVEL),debug)
CCFLAG += -DMTK_DEBUG_LEVEL_DEBUG
CCFLAG += -DMTK_DEBUG_LEVEL_INFO
CCFLAG += -DMTK_DEBUG_LEVEL_WARNING
CCFLAG += -DMTK_DEBUG_LEVEL_ERROR
endif

ifeq ($(MTK_DEBUG_LEVEL),printf)
CCFLAG += -DMTK_DEBUG_LEVEL_PRINTF
endif

ifeq ($(MTK_DEBUG_LEVEL),none)
CCFLAG += -DMTK_DEBUG_LEVEL_NONE
endif

LDFLAG += -wrap=printf
LDFLAG += -u _printf_float

ifeq ($(MTK_SAVE_LOG_TO_FLASH_ENABLE),y)
CCFLAG += -DMTK_SAVE_LOG_TO_FLASH_ENABLE
endif

################################################################################
# Exception
################################################################################
ifeq ($(MTK_FULLDUMP_ENABLE),y)
CCFLAG      +=  -DMTK_FULLDUMP_ENABLE
endif

ifeq ($(MTK_MINIDUMP_ENABLE),y)
CCFLAG      +=  -DMTK_MINIDUMP_ENABLE
endif

ifeq ($(MTK_OFFLINELOG_ENABLE),y)
CCFLAG      +=  -DMTK_OFFLINELOG_ENABLE
endif
################################################################################
# Audio
################################################################################
ifeq ($(AIR_TXNR_MODE),mode_2)
CCFLAG      +=  -DAIR_TXNR_1_MIC_INEAR_ENABLE
endif

ifeq ($(AIR_TXNR_MODE),mode_3)
CCFLAG      +=  -DAIR_TXNR_2_MIC_INEAR_ENABLE
endif

ifeq ($(AIR_TXNR_MODE),mode_4)
CCFLAG      +=  -DAIR_TXNR_INTELLIGO_1MIC_ENABLE
endif

ifeq ($(AIR_TXNR_MODE),mode_6)
CCFLAG      +=  -DAIR_TXNR_3RD_PARTY_ENABLE
endif

ifeq ($(MTK_OPUS_ENCODER_ENABLE),y)
CCFLAG      +=  -DMTK_OPUS_ENCODER_ENABLE
endif

ifeq ($(MTK_DSP_HWVAD_ENABLE),y)
CCFLAG      +=  -DMTK_DSP_HWVAD_ENABLE
endif

ifeq ($(MTK_DSP_MULTI_MIC_ENABLE),y)
CCFLAG      +=  -DMTK_DSP_MULTI_MIC_ENABLE
endif

ifeq ($(MTK_LOW_LATENCY_VP_WITH_48K_FS),y)
CCFLAG      +=  -DMTK_LOW_LATENCY_VP_ENABLE
endif

ifeq ($(AIROHA_WWE_ENABLE),y)
CCFLAG      +=  -DAIROHA_WWE_ENABLE
endif

ifeq ($(AMAZON_AMA_ENABLE),y)
CCFLAG      +=  -DAMAZON_AMA_ENABLE
endif

ifeq ($(GOOGLE_GVA_ENABLE),y)
CCFLAG      +=  -DGOOGLE_GVA_ENABLE
endif

CCFLAG      +=  -DADMA_SUPPORT_STEREO_OUTPUT

ifeq ($(AIR_MP3_VOICE_PROMPT_AUDIO_CTRL_ENABLE),y)
CCFLAG      +=  -DAIR_MP3_VOICE_PROMPT_AUDIO_CTRL_ENABLE
endif

################################################################################
# Profile
################################################################################
ifeq ($(PROFILE_AMA_ENABLE),y)
CCFLAG      +=  -DPROFILE_AMA_ENABLE
endif

ifeq ($(AIR_GFP_ENABLE),y)
CCFLAG      +=  -DAIR_GFP_ENABLE
endif

ifeq ($(AIR_SWIFT_ENABLE),y)
CCFLAG      +=  -DAIR_SWIFT_ENABLE
endif

ifeq ($(AIR_HEADSET_PROFILE_ENABLE),y)
CCFLAG      +=  -DAIR_HEADSET_PROFILE_ENABLE	
endif

################################################################################
# Project Feature config
################################################################################
ifeq ($(LINEIN_ENABLE),y)
CCFLAG      +=  -DLINEIN_ENABLE
endif

ifeq ($(APP_GAME_MODE),y)
CCFLAG      +=  -DAPP_GAME_MODE
endif

ifeq ($(MODULE_LOG_FEATURE),y)
CCFLAG      +=  -DMODULE_LOG_FEATURE
endif

ifeq ($(A2DP_PACKET_ASSEMBLE),y)
CCFLAG      +=  -DA2DP_PACKET_ASSEMBLE
endif

ifeq ($(LOG_PRINT_156X),y)
CCFLAG      +=  -DLOG_PRINT_156X
endif

ifeq ($(AIR_AVRCP_PROFILE_ENABLE),y)
CCFLAG      +=  -DAIR_AVRCP_PROFILE_ENABLE
endif

ifeq ($(AIR_A2DP_PROFILE_ENABLE),y)
CCFLAG      +=  -DAIR_A2DP_PROFILE_ENABLE
endif

ifeq ($(AIR_GATT_OVER_BREDR_ENABLE),y)
CCFLAG      +=  -DAIR_GATT_OVER_BREDR_ENABLE
endif

ifeq ($(MP3_LOCAL_PLAYBACK),y)
CCFLAG      +=  -DMP3_LOCAL_PLAYBACK
endif

ifeq ($(MP3_LOCAL_PLAYBACK_MMI_CTRL),y)
CCFLAG      +=  -DMP3_LOCAL_PLAYBACK_MMI_CTRL
endif

ifeq ($(CHANNEL_SELECTION_ENABLE),y)
CCFLAG      +=  -DCHANNEL_SELECTION_ENABLE
endif

ifeq ($(ANC_FF_MMI_CTRL),y)
CCFLAG      +=  -DANC_FF_MMI_CTRL
endif

ifeq ($(APP_OPUS_ENCODER),y)
CCFLAG      +=  -DAPP_OPUS_ENCODER
endif

ifeq ($(AIROHA_BT_SPP_ENABLE),y)
CCFLAG      +=  -DAIROHA_BT_SPP_ENABLE
endif

ifeq ($(AIROHA_BT_HID_ENABLE),y)
CCFLAG      +=  -DAIROHA_BT_HID_ENABLE
endif

ifeq ($(AIROHA_BT_LE_ENABLE),y)
CCFLAG      +=  -DAIROHA_BT_LE_ENABLE
endif

ifeq ($(DO_RHO_IMMEDIATELY),y)
CCFLAG      +=  -DDO_RHO_IMMEDIATELY
endif

ifeq ($(AIR_CODEC_SWITCH_WORKAROUND_MI9_ENABLE),y)
CCFLAG      +=  -DAIR_CODEC_SWITCH_WORKAROUND_MI9_ENABLE
endif

ifeq ($(SPECIAL_WHITE_LIST_HANDLE),y)
CCFLAG      +=  -DSPECIAL_WHITE_LIST_HANDLE
endif

ifeq ($(AIR_CODEC_SWITCH_WORKAROUND_SONY_XPERIA_ENABLE),y)
CCFLAG      +=  -DAIR_CODEC_SWITCH_WORKAROUND_SONY_XPERIA_ENABLE
endif

ifeq ($(AMA_IAP2_SUPPORT_ENABLE),y)
CCFLAG      +=  -DAMA_IAP2_SUPPORT_ENABLE
endif

ifeq ($(MTK_MINIDUMP_ENHANCE_ENABLE),y)
CCFLAG      +=  -DMTK_MINIDUMP_ENHANCE_ENABLE
endif
