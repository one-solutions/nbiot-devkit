/*
 * test_BME160.cpp
 *
 *  Created on: Sep 11, 2019
 *      Author: GrazynaPalecka
 */
#include "example_BMI160.h"

#include "stdio.h"
#include "bmi160_defs.h"
#include "bmi160.h"
#include "i2cspm.h"
#include <math.h>

#include "one-connect.h"

#define ACCEL_LSB_2 	16384.0
#define GYRO_LSB_2000 	16.4

struct bmi160_dev sensor;


static int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
static int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
static void user_delay_ms(uint32_t period);


int8_t init_BMI160Sensor()
{
	int rslt = BMI160_E_NULL_PTR;

	sensor.id = BMI160_I2C_ADDR << 1;
	sensor.interface = BMI160_I2C_INTF;
	sensor.read = user_i2c_read;
	sensor.write = user_i2c_write;
	sensor.delay_ms = user_delay_ms;

	rslt = bmi160_init(&sensor);

	 if(rslt != BMI160_OK)
	     printf("[BMI160] init sensor: ERROR %i\r\n", rslt);

	 if(rslt == BMI160_OK)
	 {
		 printf("[BMI160] init sensor: OK\r\n");
		 // Configure accelerometer sensor
		 sensor.accel_cfg.odr = BMI160_ACCEL_ODR_1600HZ;
		 sensor.accel_cfg.range = BMI160_ACCEL_RANGE_2G;
		 sensor.accel_cfg.bw = BMI160_ACCEL_BW_NORMAL_AVG4;
		 sensor.accel_cfg.power = BMI160_ACCEL_NORMAL_MODE;
		 //Configure gyroscope
		 sensor.gyro_cfg.odr = BMI160_GYRO_ODR_3200HZ;
		 sensor.gyro_cfg.range = BMI160_GYRO_RANGE_2000_DPS;
		 sensor.gyro_cfg.bw = BMI160_GYRO_BW_NORMAL_MODE;
		 sensor.gyro_cfg.power = BMI160_GYRO_NORMAL_MODE;

		 rslt = bmi160_set_sens_conf(&sensor);
		 printf("[BMI160] config accel & gyro: OK\r\n");
	 }
	 else
		 printf("[BMI160] config accel & gyro: ERROR %i\r\n", rslt);

	 return rslt;
}

/*Return scaled results
 * -> Acceleration raw data is scaled for 2G
 * -> Gyroscope raw data is scaled for 2000 DPS*/
int8_t get_bmi160_data(int16_t *accel, int16_t *gyro)
{
	struct bmi160_sensor_data accel_data;
	struct bmi160_sensor_data gyro_data;
	int8_t rslt = bmi160_get_sensor_data((BMI160_ACCEL_SEL | BMI160_GYRO_SEL), &accel_data, &gyro_data, &sensor);
	if(rslt == BMI160_OK)
	{
		//use 2 decimal point precision
		accel[0] = (int16_t)((accel_data.x / ACCEL_LSB_2)*100);
		accel[1] = (int16_t)((accel_data.y / ACCEL_LSB_2)*100);
		accel[2] = (int16_t)((accel_data.z / ACCEL_LSB_2)*100);
		gyro[0] =  (int16_t)((gyro_data.x / GYRO_LSB_2000)*100);
		gyro[1] =  (int16_t)((gyro_data.y / GYRO_LSB_2000)*100);
		gyro[2] =  (int16_t)((gyro_data.z / GYRO_LSB_2000)*100);
		//printf("[BMI160] raw accel values: x=%i y=%i z=%i, raw gyro values: x=%i y=%i z=%i\r\n", accel_data.x, accel_data.y, accel_data.z, gyro_data.x, gyro_data.y, gyro_data.z);
	}
	return rslt;
}

static int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
   I2C_TransferSeq_TypeDef seq;
   I2C_TransferReturn_TypeDef ret;

   seq.addr = dev_id;
   seq.flags = I2C_FLAG_WRITE_READ;
   seq.buf[0].data = &reg_addr;
   seq.buf[0].len = 1;
   seq.buf[1].data = data;
   seq.buf[1].len = len;

   ret = I2CSPM_Transfer(I2C0, &seq);
   if (ret != i2cTransferDone)
   {
      return ((int8_t)ret);
   }

   return 0;
}

static int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len)
{
   I2C_TransferSeq_TypeDef seq;
   I2C_TransferReturn_TypeDef ret;

   seq.addr = dev_id;
   seq.flags = I2C_FLAG_WRITE_WRITE;
   seq.buf[0].data = &reg_addr;
   seq.buf[0].len = 1;
   seq.buf[1].data = data;
   seq.buf[1].len = len;

   ret = I2CSPM_Transfer(I2C0, &seq);
   if (ret != i2cTransferDone)
   {
      return ((int8_t)ret);
   }

   return 0;
}

static void user_delay_ms(uint32_t period)
{
   uint32_t startTime = radio_get_millis();
   while (1)
   {
      if ((radio_get_millis() - startTime) >= period)
         break;
   }
}



