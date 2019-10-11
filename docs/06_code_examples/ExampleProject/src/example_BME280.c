
#include "bme280_defs.h"
#include "bme280.h"
#include "i2cspm.h"
#include "stdio.h"
#include "one-connect.h"

struct bme280_dev dev;

//functions required by the BME680 sensor
static int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
static int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);
static void user_delay_ms(uint32_t period);

int8_t init_BME280Sensor(void)
{
	int8_t rslt = BME280_E_NULL_PTR;

    dev.dev_id = BME280_I2C_ADDR_PRIM << 1;
    dev.intf = BME280_I2C_INTF;
    dev.read = user_i2c_read;
    dev.write = user_i2c_write;
    dev.delay_ms = user_delay_ms;

    rslt = bme280_init(&dev);

    if(rslt != BME280_OK)
    	printf("[BME280] init sensor: ERROR %i\r\n", rslt);

    if(rslt == BME280_OK)
    {
    	printf("[BME280] init sensor: OK\r\n");
		// Recommended mode of operation: Indoor navigation
		dev.settings.osr_h = BME280_OVERSAMPLING_1X;
		dev.settings.osr_p = BME280_OVERSAMPLING_16X;
		dev.settings.osr_t = BME280_OVERSAMPLING_2X;
		dev.settings.filter = BME280_FILTER_COEFF_16;
		uint8_t settings_sel = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL | BME280_FILTER_SEL;
		rslt = bme280_set_sensor_settings(settings_sel, &dev);
		printf("[BME280] adjust sensor settings: OK\r\n");
    }
    else
    	printf("[BME280] adjust sensor settings: ERROR %i\r\n", rslt);

    return rslt;
}

int8_t get_bme280_data(struct bme280_data* data)
{
    int8_t rslt = bme280_set_sensor_mode(BME280_FORCED_MODE, &dev);
    printf("[BME280] set sensor mode result: %i\r\n", rslt);
    if(rslt == BME280_OK)
    {
    	dev.delay_ms(40); // wait for the measurement to complete
	    rslt = bme280_get_sensor_data(BME280_ALL, data, &dev);
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


