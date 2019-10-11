#include "em_device.h"
#include "em_chip.h"
#include "em_cmu.h"

#include "stdio.h"
#include "stdlib.h"
#include "retargetserial.h"
#include "i2cspm.h"

#include "one-connect.h"
#include "example_BMI160.h"
#include "example_BME280.h"

void init();
void send_data();
void sensor_measure();

radio_config_t rconfig = RADIO_CONFIG_INIT_DEFAULT;
radio_stats_t *current_rstats;

bool notification = false;
bool send = false;
bool measure = false;

static void notify(radio_stats_t *rs);
static void time_recived(uint32_t newTime);


void init()
{
	CHIP_Init();
	//Conifgure clocks
	CMU_ClockDivSet(cmuClock_HF, cmuClkDiv_2); // Prescale Core clock to be suitable for LEUART 9600 Baud
	CMU_ClockSelectSet(cmuClock_HF, cmuSelect_HFXO ); // Select HFXO as clock source for HFCLK
	CMU_ClockEnable(cmuClock_GPIO, true);
	// Configure PB0 and PB1 buttons as input
	GPIO_PinModeSet(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, gpioModeInputPull, 1);
	GPIO_IntConfig(BSP_GPIO_PB0_PORT, BSP_GPIO_PB0_PIN, false, true, true);
	GPIO_PinModeSet(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, gpioModeInputPull, 1);
	GPIO_IntConfig(BSP_GPIO_PB1_PORT, BSP_GPIO_PB1_PIN, false, true, true);
	// Enable interrupt
	NVIC_ClearPendingIRQ(GPIO_EVEN_IRQn);
	NVIC_EnableIRQ(GPIO_EVEN_IRQn);
	NVIC_ClearPendingIRQ(GPIO_ODD_IRQn);
	NVIC_EnableIRQ(GPIO_ODD_IRQn);

	// Retarget stdio to UART
	RETARGET_SerialInit();
	RETARGET_SerialCrLf(1);

	I2CSPM_Init_TypeDef i2cinit = I2CSPM_INIT_DEFAULT;
	i2cinit.sclPort = gpioPortC;
	i2cinit.sclPin = 1;
	i2cinit.sdaPort = gpioPortC;
	i2cinit.sdaPin = 0;
	i2cinit.portLocation = 4;
	I2CSPM_Init(&i2cinit);

	printf("\n\rBooting...\n\r");

	rconfig.radio_notify = notify;
	rconfig.notification_mode = NOTIFY_NETREG | NOTIFY_LWM2M_DATA_STATUS | NOTIFY_LWM2M_STATUS;
	rconfig.radio_notify_new_time = time_recived;

	uint16_t rrslt = radio_init(&rconfig);
	if(rrslt == NO_ERROR)
		printf("[Main] Radio module init: OK\n\r");
	else
		printf("[Main] Radio module init: ERROR %u\n\r", rrslt);

	int8_t rslt = init_BME280Sensor();
	if(rslt == BME280_OK)
		printf("[Main] init_BME280Sensor(): OK \n\r");
	else
		printf("[Main] init_BME280Sensor(): ERROR %i\n\r", rslt);


	rslt = init_BMI160Sensor();
	if(rslt == BMI160_OK)
			printf("[Main] init_BMI160Sensor(): OK \n\r");
		else
			printf("[Main] init_BMI160Sensor(): ERROR %i\n\r", rslt);

}


int main(void)
{
	init();
	uint16_t rrslt = radio_connect(&rconfig);
	printf("[Main] NBIoT connect result:%d\n\r", rrslt);

    while (1)
    {
      if (notification)
      {
         notification = false;
         if(current_rstats->stats_notify == NOTIFY_NETREG)
        	 printf("[Main] notify for network registration status: %d\n\r", current_rstats->network_reg_status);
         if(current_rstats->stats_notify == NOTIFY_LWM2M_STATUS)
         {
        	 printf("[Main] notify for LWM2M event report: %d\n\r\n\r", current_rstats->lwm2m_event_report);
        	 if(current_rstats->lwm2m_event_report == 3)
        	 {
        		 radio_synchtime();
        		 printf("[Main] connected to IoT gateway, synchronize time\n\r");
        	 }
         }
         if(current_rstats->stats_notify == NOTIFY_LWM2M_DATA_STATUS && current_rstats->lwm2m_data_status == 4)
        	 printf("[Main] received ACK for send message\n\r");
      }
      if(measure)
      {
    	  sensor_measure();
    	  measure= false;
      }
      if (send)
      {
    	  printf("[Main] send data\n\r");
    	  send_data();
    	  send = false;
      }
    }
}

void sensor_measure()
{
	struct bme280_data data;
	int8_t rslt =  get_bme280_data(&data);

	if(rslt == BME280_OK)
		printf("[Main] BME280 measurements: temp= %li.%01i C, pressure= %lu.%01lu hPa, humidity= %lu.%01lu % \r\n",
				(int32_t)(data.temperature/100), abs(data.temperature%100), (uint32_t)(data.pressure/10000), (uint32_t)(data.pressure%10000),
				(uint32_t)(data.humidity/1024), (uint32_t)(data.humidity%1024));
	else
	    printf("[Main] BME280 sensor: ERROR %i\n\r\n\r", rslt);

	int16_t accel[3] = {0};
	int16_t gyro[3] = {0};
	rslt= get_bmi160_data(accel, gyro);
	if(rslt == BMI160_OK)
	   printf("[Main] BMI160 accelerator: x=%i mg y=%i mg z=%i mg, gyroscope: x=%i mdeg/s y=%i mdeg/s z=%i mdeg/s \n\r",
			  accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2]);
	else
	   printf("[Main] BMI160 sensor: ERROR %i\n\r\n\r", rslt);
}

void send_data()
{
	uint8_t sendBuf[34];

	uint32_t timestamp = radio_get_rtc();

	sendBuf[0]= 0x01;

	sendBuf[1]= (timestamp >> 24) & 0xFF;
	sendBuf[2]= (timestamp >> 16) & 0xFF;
	sendBuf[3]= (timestamp >> 8) & 0xFF;
	sendBuf[4]= timestamp;
	printf("[Main] send current timestamp in ms:  %lu\n\r", timestamp);

	uint16_t rrslt = radio_get_netstats();
	if(rrslt == NO_ERROR)
	{
		int16_t rsrp= (int16_t)(current_rstats->signal_power*10);
		int16_t rsrq= (int16_t)(current_rstats->rsrq*10);
		printf("[Main] send netstats:  signal_power =%i, signal_quality=%i, ce_level= %lu\n\r", rsrp, rsrq, current_rstats->ce_level);
		sendBuf[5]= (rsrp >> 8) & 0xFF;
		sendBuf[6]= rsrp;
		sendBuf[7]= (rsrq >> 8) & 0xFF;
		sendBuf[8]= rsrq;
		sendBuf[9]= current_rstats->ce_level;
	}
	else
	{
		printf("[Main] cannot get radio module statistics: ERROR %i\n\r\n\r", rrslt);
		return;
	}

	int16_t accel[3] = {0.0};
	int16_t gyro[3] = {0.0};
	int8_t rslt= get_bmi160_data(accel, gyro);
	if(rslt == BMI160_OK)
	{
		 printf("[Main] send BMI160 data, accelerator: x=%i mg y=%i mg z=%i mg, gyroscope: x=%i mdeg/s y=%i mdeg/s z=%i mdeg/s \n\r",
					  accel[0], accel[1], accel[2], gyro[0], gyro[1], gyro[2]);

		sendBuf[10]= (accel[0] >> 8) & 0xFF;
		sendBuf[11]= accel[0];
		sendBuf[12]= (accel[1] >> 8) & 0xFF;
		sendBuf[13]= accel[1];
		sendBuf[14]= (accel[2] >> 8) & 0xFF;
		sendBuf[15]= accel[2];
		sendBuf[16]= (gyro[0] >> 8) & 0xFF;
		sendBuf[17]= gyro[0];
		sendBuf[18]= (gyro[1] >> 8) & 0xFF;
		sendBuf[19]= gyro[1];
		sendBuf[20]= (gyro[2] >> 8) & 0xFF;
		sendBuf[21]= gyro[2];
	}
	else
	{
		printf("[Main] cannot get BMI160 sensor data: ERROR %i\n\r\n\r", rslt);
		return;
	}

	struct bme280_data data;
	rslt =  get_bme280_data(&data);
	if(rslt == BME280_OK)
	{
		printf("[Main] send BME280 measurements: temp= %li.%01i C, pressure= %lu.%01lu hPa, humidity= %lu.%01lu %\r\n",
				data.temperature/100, abs(data.temperature%100), data.pressure/10000, data.pressure%10000, data.humidity/1024, data.humidity%1024);

	   sendBuf[22]= (data.temperature >> 24) & 0xFF;
	   sendBuf[23]= (data.temperature >> 16) & 0xFF;
	   sendBuf[24]= (data.temperature >> 8) & 0xFF;
	   sendBuf[25]= data.temperature;
	   sendBuf[26]= (data.humidity >> 24) & 0xFF;
	   sendBuf[27]= (data.humidity >> 16) & 0xFF;
	   sendBuf[28]= (data.humidity >> 8) & 0xFF;
	   sendBuf[29]= data.humidity;
	   sendBuf[30]= (data.pressure >> 24) & 0xFF;
	   sendBuf[31]= (data.pressure >> 16) & 0xFF;
	   sendBuf[32]= (data.pressure >> 8) & 0xFF;
	   sendBuf[33]= data.pressure;
	}
	else
	{
		printf("[Main] cannot get BME280 sensor data: ERROR %i\n\r\n\r", rslt);
	    return;
	}

	rrslt = radio_send(ACK_RELEASE_AFTER_REPLY, sendBuf, 34);
	if(rrslt == NO_ERROR)
		printf("[Main] send data: OK\n\r\n\r");
	else
		printf("[Main] send data: ERROR %i\n\r\n\r", rslt);
}

//callback function for radio notifications
static void notify(radio_stats_t *rs)
{
   current_rstats = rs;
   notification = true;
}

static void time_recived(uint32_t newTime)
{
	printf("[Main] received new time from IoT-Gateway!");
}


/* GPIO Interrupt handler for odd pins */
void GPIO_ODD_IRQHandler(void)
{
   // Get and clear all pending GPIO interrupts.
   uint32_t interruptMask = GPIO_IntGet();
   GPIO_IntClear(interruptMask);

   // Act on interrupts.
   if (interruptMask & (1 << BSP_GPIO_PB0_PIN))
   {
	   send = true;
   }

}

/* GPIO Interrupt handler for even pins */
void GPIO_EVEN_IRQHandler(void)
{
	// Get and clear all pending GPIO interrupts.
	uint32_t interruptMask = GPIO_IntGet();
	GPIO_IntClear(interruptMask);

	if (interruptMask & (1 << BSP_GPIO_PB1_PIN))
	{
	   measure = true;
	}
}
