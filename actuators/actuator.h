#ifndef ACTUATOR_H
#define ACTUATOR_H

/**
 * @file actuator.h
 * @brief Generic and polymorphic interface for actuators.
 */

/**
 * @brief Forward declaration of the Actuator structure.
 */
typedef struct Actuator Actuator;

/**
 * @brief Represents a generic actuator.
 *
 * This structure provides a polymorphic interface for different types of actuators.
 */
struct Actuator {
    /**
     * @brief Parameters specific to the actuator.
     *
     * This pointer can be used to store actuator-specific configuration or state.
     */
    void *params;

    /**
     * @brief Activates the actuator.
     *
     * This function pointer should point to the implementation of the activation logic
     * for the specific actuator.
     *
     * @param self A pointer to the Actuator instance.
     */
    void (*activate)(Actuator *self);

    /**
     * @brief Deactivates the actuator.
     *
     * This function pointer should point to the implementation of the deactivation logic
     * for the specific actuator.
     *
     * @param self A pointer to the Actuator instance.
     */
    void (*deactivate)(Actuator *self);

    /**
     * @brief Retrieves the status of the actuator.
     *
     * This function pointer should point to the implementation of the status retrieval logic
     * for the specific actuator.
     *
     * @param self A pointer to the Actuator instance.
     * @return An integer representing the status of the actuator.
     */
    int (*status)(Actuator *self);
};

#endif // ACTUATOR_H