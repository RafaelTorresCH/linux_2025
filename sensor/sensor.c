#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "sensor.h"

/**
 * @brief Initializes the sensor.
 *
 * This function initializes the random number generator using the current time
 * as the seed. This simulates the initialization of a sensor.
 */
void sensor_init(void) {
    srand(time(NULL)); // Seed the random number generator with the current time
}

/**
 * @brief Reads data from the sensor.
 *
 * This function generates a random double value between 0.0 and 100.0 to
 * simulate a sensor reading.
 *
 * @return A random double value between 0.0 and 100.0.
 */
double sensor_read(void) {
    return (double)rand() / RAND_MAX * 100.0; // Generate a random value between 0.0 and 100.0
}