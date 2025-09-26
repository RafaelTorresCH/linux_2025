#include <stdio.h>
#include <stdlib.h>
#include "actuator.h"

/**
 * @brief Private structure for LED actuator parameters.
 */
typedef struct {
    int state; // 0 for OFF, 1 for ON
} LedParams;

/**
 * @brief Activates the LED actuator.
 *
 * @param self A pointer to the Actuator instance.
 */
static void led_activate(Actuator *self) {
    LedParams *params = (LedParams *)self->params;
    params->state = 1;
    printf("LED ACTIVATED\n");
}

/**
 * @brief Deactivates the LED actuator.
 *
 * @param self A pointer to the Actuator instance.
 */
static void led_deactivate(Actuator *self) {
    LedParams *params = (LedParams *)self->params;
    params->state = 0;
    printf("LED DEACTIVATED\n");
}

/**
 * @brief Retrieves the status of the LED actuator.
 *
 * @param self A pointer to the Actuator instance.
 * @return The current state of the LED (0 for OFF, 1 for ON).
 */
static int led_status(Actuator *self) {
    LedParams *params = (LedParams *)self->params;
    printf("LED STATUS: %s\n", params->state ? "ON" : "OFF");
    return params->state;
}

/**
 * @brief Creates a new LED actuator instance.
 *
 * @return A pointer to the newly created Actuator instance.
 */
Actuator* create_led_actuator() {
    Actuator *led_actuator = (Actuator *)malloc(sizeof(Actuator));
    if (!led_actuator) {
        fprintf(stderr, "Failed to allocate memory for LED actuator\n");
        return NULL;
    }

    LedParams *params = (LedParams *)malloc(sizeof(LedParams));
    if (!params) {
        fprintf(stderr, "Failed to allocate memory for LED parameters\n");
        free(led_actuator);
        return NULL;
    }

    params->state = 0; // Initialize LED as OFF

    led_actuator->params = params;
    led_actuator->activate = led_activate;
    led_actuator->deactivate = led_deactivate;
    led_actuator->status = led_status;

    return led_actuator;
}