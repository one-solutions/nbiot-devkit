#ifndef SRC_EXAMPLE_BME280_H_
#define SRC_EXAMPLE_BME280_H_

#include "bme280_defs.h"

int8_t init_BME280Sensor();
int8_t get_bme280_data(struct bme280_data* data);


#endif /* SRC_EXAMPLE_BME280_H_ */
