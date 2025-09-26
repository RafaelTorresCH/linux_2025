#ifndef SENSOR_H
#define SENSOR_H

/**
 * @file sensor.h
 * @brief Public interface for the sensor library.
 */

/**
 * @brief Initializes the sensor.
 *
 * This function sets up the sensor for operation. It must be called
 * before any other sensor functions are used.
 */
void sensor_init(void);

/**
 * @brief Reads data from the sensor.
 *
 * This function retrieves the current reading from the sensor.
 *
 * @return The current sensor reading as a double.
 */
double sensor_read(void);

#endif // SENSOR_H