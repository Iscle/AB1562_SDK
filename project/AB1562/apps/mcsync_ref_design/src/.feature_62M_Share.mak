################################################################################
# NVKEY control
################################################################################
NVKEY_XML       =  nvkey.xml
NVKEY_FOTA_XML  =  nvkey_fota.xml
SYSKEY_FOTA_XML =  AB1530B_syskey_fota.xml
SYSKEY_XML      =  AB1530B_syskey.xml
FILE_XML        =  FileManagement_4M.xml
################################################################################
# Feature control
################################################################################

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
MTK_LEAKAGE_DETECTION_ENABLE                            ?= n
MTK_DSP_MULTI_MIC_ENABLE                                ?= y
MTK_LOW_LATENCY_VP_WITH_48K_FS                          ?= n

##
## AIR_MP3_VOICE_PROMPT_AUDIO_CTRL_ENABLE
## Brief: This option is used to enable MP3 voice prompt feature.
## Usage: Enable the feature by configuring it as y.
##        y : feature enable
##        n : feature disable
## Dependency:  None
##

AIR_MP3_VOICE_PROMPT_AUDIO_CTRL_ENABLE                  ?= y

AIROHA_WWE_ENABLE                                       ?= y
AMAZON_AMA_ENABLE                                       ?= n
GOOGLE_GVA_ENABLE                                       ?= n
XIAOAI_DEVELOPMENT                                      ?= n
XIAOAI_TWO_STAGE_OTA                                    ?= n
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

AMA_IAP2_SUPPORT_ENABLE                                 ?= n
AIR_GATT_OVER_BREDR_ENABLE                              ?= n

APP_GAME_MODE                                           ?= y
A2DP_LOW_LATENCY                                        ?= n
MODULE_LOG_FEATURE                                      ?= y
A2DP_PACKET_ASSEMBLE                                    ?= y
LOG_PRINT_156X                                          ?= n
SMART_CHG_CSE_DEVELOPMENT                               ?= y
SMART_CHG_CSE_LIDON_RECONNECT                           ?= y
SMART_CHG_CSE_AUTO_AIR_PAIRING                          ?= n
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

##
## AIR_TAKE_OVER_LINK_ENABLE
## Brief: This option is used to take over the link from a connected phone.
## Usage: Enable the feature by configuring it as y.
##        y : tahke over link feature enable
##        n : tahke over link feature disable
## Dependency:  None
##

AIR_TAKE_OVER_LINK_ENABLE                               ?= n

##
## AIR_MCSYNC_SHARE_MODE_ENABLE
## Brief: This option is used to enable McSync Share Mode feature.
## Usage: Enable the feature by configuring it as y.
##        y : McSync Share Mode enable
##        n : McSync Share Mode disable
## Dependency:  None
##

AIR_MCSYNC_SHARE_MODE_ENABLE                            ?= y

##
## AIR_TILE_ADV_ENABLE
## Brief: This option is used to enable Tile ADV feature.
## Usage: Enable the feature by configuring it as y.
##        y : Tile ADV enable
##        n : Tile ADV disable
## Dependency:  None
##

AIR_TILE_ADV_ENABLE                                     ?= n

##
## AIR_CAPTOUCH_PRESSURE_SENSOR_ENABLE
## Brief: This option is used to enable internal captouch pressure sensor feature.
## Usage: Enable the feature by configuring it as y.
##        y : captouch pressure sensor enable
##        n : captouch pressure sensor disable
## Dependency:  None
##

AIR_CAPTOUCH_PRESSURE_SENSOR_ENABLE                     ?= n

##
## AIR_AGENT_RECOVERY_MODE_AFTER_DISCONNECTION_FROM_PHONE_ENABLE
## Brief: This option is used to let agent enter recovery mode after disconnection from phone.
## Usage: Enable the feature by configuring it as y.
##        y : feature enable
##        n : feature disable
## Dependency:  None
##

AIR_AGENT_RECOVERY_MODE_AFTER_DISCONNECTION_FROM_PHONE_ENABLE    ?= n
