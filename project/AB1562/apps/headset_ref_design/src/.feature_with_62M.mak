################################################################################
# NVKEY control
################################################################################
NVKEY_XML       =  nvkey_headset.xml
NVKEY_FOTA_XML  =  nvkey_fota_headset.xml
SYSKEY_FOTA_XML =  AB1530B_syskey_fota_headset.xml
SYSKEY_XML      =  AB1530B_syskey_headset.xml
FILE_XML        =  FileManagement_4M.xml

################################################################################
# Feature control
################################################################################
FEATURE_FILE_SYSTEM                                      = y

################################################################################
# Logging config
################################################################################
MTK_SYSLOG_VERSION_2                                    ?= y
MTK_DEBUG_PLAIN_LOG_ENABLE                              ?= n
MTK_SYSLOG_SUB_FEATURE_STRING_LOG_SUPPORT                = y
MTK_SYSLOG_SUB_FEATURE_BINARY_LOG_SUPPORT                = y
MTK_SYSLOG_SUB_FEATURE_OFFLINE_DUMP_ACTIVE_MODE          = n
MTK_SYSLOG_SUB_FEATURE_MSGID_TO_STRING_LOG_SUPPORT      ?= n

MTK_MUX_ENABLE                                          ?= y
MTK_PORT_SERVICE_ENABLE                                 ?= y
MTK_CPU_NUMBER_0                                        ?= y
FPGA_ENV                                                ?= n

################################################################################
# Exception config
################################################################################
MTK_FULLDUMP_ENABLE                                     ?= y
MTK_MINIDUMP_ENABLE                                     ?= y
MTK_MINIDUMP_ENHANCE_ENABLE                             ?= y
MTK_OFFLINELOG_ENABLE                                   ?= y

################################################################################
# Bootreason config
################################################################################
MTK_BOOTREASON_CHECK_ENABLE                             ?= y

################################################################################
# System hang tracer
################################################################################
MTK_SYSTEM_HANG_TRACER_ENABLE                           ?= y

################################################################################
# Audio Feature config
################################################################################
## Below TXNR options is mutually exclusive. Please only select one of them.
##
## AIR_TXNR_MODE
## Brief: This option is used to select different mode for NR process.
## Note:  None
## Usage: Select only one TXNR mode from below mode list.
##        mode_1 : enable 1 or 2 MIC only NR
##        mode_2 : enable 1 + 1 NR
##        mode_3 : enable 2 + 1 NR
##        mode_4 : enable INTELLIGO 1 MIC NR
##        mode_6 : enable 3rd party NR
## Dependency:  None
##
AIR_TXNR_MODE                                            = mode_1
MTK_OPUS_ENCODER_ENABLE                                 ?= y
MTK_DSP_HWVAD_ENABLE                                    ?= y
MTK_DSP_MULTI_MIC_ENABLE                                ?= y
MTK_LOW_LATENCY_VP_WITH_48K_FS                          ?= n
AIROHA_WWE_ENABLE                                       ?= y
AMAZON_AMA_ENABLE                                       ?= n
GOOGLE_GVA_ENABLE                                       ?= n

##
## AIR_MP3_VOICE_PROMPT_AUDIO_CTRL_ENABLE
## Brief: This option is used to enable MP3 voice prompt feature.
## Usage: Enable the feature by configuring it as y.
##        y : feature enable
##        n : feature disable
## Dependency:  None
##

AIR_MP3_VOICE_PROMPT_AUDIO_CTRL_ENABLE                  ?= y


################################################################################
# Profile Feature config
################################################################################
PROFILE_AMA_ENABLE                                      ?= y

##
## AIR_GPF_ENABLE
## Brief: This option is used to enable Google Fast Pair feature.
## Usage: Enable the feature by configuring it as y.
##        y : Google Fast Pair enable
##        n : Google Fast Pair disable
## Dependency:  None
##

AIR_GFP_ENABLE                                          ?= y

##
## AIR_SWIFT_ENABLE
## Brief: This option is used to enable Microsoft Swift Pair feature.
## Usage: Enable the feature by configuring it as y.
##        y : Microsoft Swift Pair enable
##        n : Microsoft Swift Pair disable
## Dependency:  None
##

AIR_SWIFT_ENABLE                                        ?= n

AMA_IAP2_SUPPORT_ENABLE                                 ?= y

##
## AIR_HEADSET_PROFILE_ENABLE
## Brief: This option is used to enable BT Headset Profile feature.
## Usage: Enable the feature by configuring it as y.
##        y : Headset Profile enable
##        n : Headset Profile disable
## Dependency:  None
##

AIR_HEADSET_PROFILE_ENABLE                              ?= y

##
## AIR_AVRCP_PROFILE_ENABLE
## Brief: This option is used to enable BT AVRCP Profile feature.
## Usage: Enable the feature by configuring it as y.
##        y : AVRCP Profile enable
##        n : AVRCP Profile disable
## Dependency:  None
##

AIR_AVRCP_PROFILE_ENABLE                                ?= y

##
## AIR_A2DP_PROFILE_ENABLE
## Brief: This option is used to enable BT A2DP Profile feature.
## Usage: Enable the feature by configuring it as y.
##        y : A2DP Profile enable
##        n : A2DP Profile disable
## Dependency:  None
##

AIR_A2DP_PROFILE_ENABLE                                 ?= y

AIR_GATT_OVER_BREDR_ENABLE                              ?= n
LINEIN_ENABLE                                           ?= y
APP_GAME_MODE                                           ?= y
MODULE_LOG_FEATURE                                      ?= y
A2DP_PACKET_ASSEMBLE                                    ?= y
LOG_PRINT_156X                                          ?= n
CHANNEL_SELECTION_ENABLE                                ?= y
ANC_FF_MMI_CTRL                                         ?= y
APP_OPUS_ENCODER                                        ?= n
AIROHA_BT_SPP_ENABLE                                    ?= n
AIROHA_BT_HID_ENABLE                                    ?= n
AIROHA_BT_LE_ENABLE                                     ?= n
SPECIAL_WHITE_LIST_HANDLE                               ?= y

##
## AIR_CODEC_SWITCH_WORKAROUND_SONY_XPERIA_ENABLE
## Brief: This option is used to support codec switch of engineer mode by SONY XPERIA.
## Usage: Enable the feature by configuring it as y.
##        y : feature enable
##        n : feature disable
## Dependency:  None
##

AIR_CODEC_SWITCH_WORKAROUND_SONY_XPERIA_ENABLE          ?= y

##
## AIR_CODEC_SWITCH_WORKAROUND_MI9_ENABLE
## Brief: This option is used to support codec switch of engineer mode by MI9 .
## Usage: Enable the feature by configuring it as y.
##        y : feature enable
##        n : feature disable
## Dependency:  None
##

AIR_CODEC_SWITCH_WORKAROUND_MI9_ENABLE                  ?= n

