
#ifndef SRC_EXAMPLE_BMI160_H_
#define SRC_EXAMPLE_BMI160_H_

#include "bmi160_defs.h"

int8_t init_BMI160Sensor();
int8_t get_bmi160_data(int16_t *accel, int16_t *gyro);

#endif /* SRC_EXAMPLE_BMI160_H_ */
