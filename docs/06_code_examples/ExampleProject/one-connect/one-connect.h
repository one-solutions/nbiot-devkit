#ifndef ONECONNECT_H_
#define ONECONNECT_H_

#include <stdint.h>
#include <stdbool.h>

enum psm_modes
{
   DRX, PSM, eDRX
};

enum encryption_modes
{
   NONE, DTLS, DTLS_PLUS
};

enum notification_modes
{
   NOTIFY_NEVER = 0,
   NOTIFY_NETREG = 1,
   NOTIFY_PSM = 2,
   NOTIFY_LWM2M_STATUS = 4,
   NOTIFY_LWM2M_DATA_STATUS = 8
};

enum reboot_reasons
{
   REBOOT_CAUSE_NO_REBOOT,
   REBOOT_CAUSE_SECURITY_RESET_UNKNOWN,
   REBOOT_CAUSE_SECURITY_SYSRESETREQ,
   REBOOT_CAUSE_SECURITY_WATCHDOG,
   REBOOT_CAUSE_SECURITY_SELF,
   REBOOT_CAUSE_SECURITY_ALTBOOT,
   REBOOT_CAUSE_SECURITY_REG_0,
   REBOOT_CAUSE_SECURITY_REG_3,
   REBOOT_CAUSE_SECURITY_STANDARD_CHIP_WATCHDOG,
   REBOOT_CAUSE_SECURITY_UPDATER_CHIP_WATCHDOG,
   REBOOT_CAUSE_SEUCRITY_SCAN_ENTER_EXIT,
   REBOOT_CAUSE_SECURITY_PMU_POWER_ON_RESET,
   REBOOT_CAUSE_SECURITY_RESET_PIN,
   REBOOT_CAUSE_SECURITY_REGIONS_UPDATED,
   REBOOT_CAUSE_SECURITY_FOTA_UPGRADE,
   REBOOT_CAUSE_PROTOCOL_SYSRESETREQ,
   REBOOT_CAUSE_PROTOCOL_WATCHDOG,
   REBOOT_CAUSE_PROTOCOL_MONITOR_REBOOT_REQ,
   REBOOT_CAUSE_PROTOCOL_RPC_TIMEOUT,
   REBOOT_CAUSE_APPLICATION_SYSRESETREQ,
   REBOOT_CAUSE_APPLICATION_WATCHDOG,
   REBOOT_CAUSE_APPLICATION_AT,
   REBOOT_CAUSE_APPLICATION_RPC_TIMEOUT,
   REBOOT_CAUSE_PROTOCOL_IMSI_UPDATE,
   REBOOT_CAUSE_UNKNOWN
};

enum error_codes
{
   NO_ERROR = 0,
   RADIO_INIT_BAUDRATE_ERR = 600,
   RADIO_INIT_CFUN_ERR,
   RADIO_INIT_NCONFIG_ERR,
   RADIO_INIT_REBOOT_ERR,
   RADIO_INIT_NCDP_ERR,
   RADIO_INIT_QREGSWT_ERR,
   RADIO_INIT_DRX_MODE_ERR,
   RADIO_INIT_PSM_MODE_ERR,
   RADIO_INIT_CMEE_ERR,
   RADIO_INIT_CEREG_ERR,
   RADIO_INIT_CSCON_ERR,
   RADIO_INIT_NNMI_ERR,
   RADIO_INIT_NPSMR_ERR,
   RADIO_INIT_CGSN_ERR,
   RADIO_INIT_NCCID_ERR,
   RADIO_INIT_CIMI_ERR,
   RADIO_INIT_CGDCONT_ERR,
   RADIO_INIT_ENCRYPTION_MODE_ERR,
   RADIO_CONNECT_INIT_NOT_DONE_ERR,
   RADIO_CONNECT_CFUN_ERR,
   RADIO_CONNECT_COPS_ERR,
   RADIO_SEND_TO_MUCH_DATA_ERR,
   RADIO_SEND_IN_PROGRESS_ERR,
   RADIO_SEND_OBSRV19_ERR,
   RADIO_SEND_NOT_REGISTERED_ERR,
   RADIO_SEND_ERR,
   RADIO_NETSTATS_NOT_IDLE_ERR,
   RADIO_NETSTATS_ERR,
   RADIO_SET_POWERMODE_ERR,
   RADIO_SOFT_REBOOT_ERR,
   RADIO_HARD_REBOOT_ERR
};

enum send_modes
{
   NACK = 0,
   NACK_RELEASE,
   NACK_RELEASE_AFTER_REPLY,
   ACK,
   ACK_RELEASE_AFTER_REPLY
};

enum reboot_modes
{
   SOFT_NO_RECONNECT,
   SOFT_WITH_RECONNECT,
   HARD_NO_RECONNECT,
   HARD_WITH_RECONNECT,
};

// Suggested default config for radio_config init structure
#define RADIO_CONFIG_INIT_DEFAULT    			  			\
{                                    			  			\
  "alliot.nbiot.at", /* APN name */    			  			\
  "IP",              /* APN type  */    					\
  "10.112.28.10",    /* IoT Gateway IP address */   		\
  "5683",            /* IoT Gateway port */          	 	\
  NONE, 			 /* encryption_mode */        		  	\
  "",   			 /* PSK */                              \
  DRX,               /* PSM mode */                 		\
  0x05, 			 /* PSM activity timer, 10s */        	\
  0x5F, 			 /* extended TAU timer, 310h */         \
  NOTIFY_NEVER, 	 /* notification mode */     			\
  0, 				 /* receive callback */    				\
  0, 				 /* radio notify callback  */     		\
  0                  /* radio notify time callback */       \
}


typedef struct radio_stats
{
   char imsi[16];
   char imei[16];
   char Iccid[25];
   enum reboot_reasons last_reboot_cause;
   uint8_t allocated_psm_activity_timer;
   uint8_t allocated_lp_tau_timer;
   uint8_t allocated_paging_time_window;
   uint8_t allocated_edrx_cycle;
   uint8_t sig_conn_status;
   uint8_t network_reg_status;
   uint8_t psm_status;
   uint8_t lwm2m_event_report;
   uint8_t lwm2m_data_status;
   float signal_power;
   uint32_t last_cellid;
   uint32_t ce_level;
   uint32_t snr;
   uint32_t earfcn;
   float rsrq;
   uint32_t current_band;
   enum notification_modes stats_notify;
} radio_stats_t;

typedef struct radio_config
{
   char apn_name[40];
   char apn_type[5];
   char devmgmt_server_ip[16];
   char devmgmt_server_port[6];

   enum encryption_modes encryption_mode;
   char encryption_psk[33];

   enum psm_modes psm_mode;

   uint8_t psm_activity_timer;
   uint8_t lp_tau_timer;

   enum notification_modes notification_mode; 					// active radio notifications i.e. notificatation_mode = NOTIFY_NETREG | NOTIFY_PSM

   void (*radio_receive_callback)(uint8_t *data, uint16_t len);  // callback function for data receive
   void (*radio_notify)(radio_stats_t *stats); 					 //callback function for notify
   void (*radio_notify_new_time)(uint32_t newTime); 			 //callback function for systime synchronization notification
} radio_config_t;


uint16_t radio_init(radio_config_t *config);
uint16_t radio_connect(radio_config_t *config);
uint16_t radio_send(enum send_modes mode, uint8_t *data, uint16_t len);
uint16_t radio_get_netstats(void);
uint16_t radio_synchtime(void);
uint32_t radio_get_rtc(void); // return system time in seconds
uint32_t radio_get_millis(void);
uint16_t radio_set_power_mode(radio_config_t *rc);
uint16_t radio_reboot(enum reboot_modes mode);


#endif /* ONECONNECT_H_ */
