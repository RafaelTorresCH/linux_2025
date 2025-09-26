#include <stdio.h>
#include <stdlib.h>
#include "actuator.h"

/**
 * @brief Private structure for Buzzer actuator parameters.
 */
typedef struct {
    int state; // 0 for OFF, 1 for ON
} BuzzerParams;

/**
 * @brief Activates the Buzzer actuator.
 *
 * @param self A pointer to the Actuator instance.
 */
static void buzzer_activate(Actuator *self) {
    BuzzerParams *params = (BuzzerParams *)self->params;
    params->state = 1;
    printf("BUZZER: BEEP BEEP\n");
}

/**
 * @brief Deactivates the Buzzer actuator.
 *
 * @param self A pointer to the Actuator instance.
 */
static void buzzer_deactivate(Actuator *self) {
    BuzzerParams *params = (BuzzerParams *)self->params;
    params->state = 0;
    printf("BUZZER: SILENT\n");
}

/**
 * @brief Retrieves the status of the Buzzer actuator.
 *
 * @param self A pointer to the Actuator instance.
 * @return The current state of the Buzzer (0 for OFF, 1 for ON).
 */
static int buzzer_status(Actuator *self) {
    BuzzerParams *params = (BuzzerParams *)self->params;
    printf("BUZZER STATUS: %s\n", params->state ? "ON" : "OFF");
    return params->state;
}

/**
 * @brief Creates a new Buzzer actuator instance.
 *
 * @return A pointer to the newly created Actuator instance.
 */
Actuator* create_buzzer_actuator() {
    Actuator *buzzer_actuator = (Actuator *)malloc(sizeof(Actuator));
    if (!buzzer_actuator) {
        fprintf(stderr, "Failed to allocate memory for Buzzer actuator\n");
        return NULL;
    }

    BuzzerParams *params = (BuzzerParams *)malloc(sizeof(BuzzerParams));
    if (!params) {
        fprintf(stderr, "Failed to allocate memory for Buzzer parameters\n");
        free(buzzer_actuator);
        return NULL;
    }

    params->state = 0; // Initialize Buzzer as OFF

    buzzer_actuator->params = params;
    buzzer_actuator->activate = buzzer_activate;
    buzzer_actuator->deactivate = buzzer_deactivate;
    buzzer_actuator->status = buzzer_status;

    return buzzer_actuator;
}