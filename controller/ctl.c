/**
 * @file ctl.c
 * @brief Main controller loop integrating the sensor and actuators.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#include "sensor.h"
#include "actuator.h"

// --- Declaraciones Externas ---
extern Actuator* create_led_actuator(void);
extern Actuator* create_buzzer_actuator(void);

// --- Constantes ---
#define THRESHOLD 75.0
#define LOOP_DELAY_US 100000 // 100 ms

// --- Secuencias de Escape ANSI para Control de la Terminal ---
#define CLEAR_SCREEN "\033[2J" // Limpia toda la pantalla
#define CURSOR_HOME "\033[H"   // Mueve el cursor a la esquina superior izquierda

int main(void) {
    // --- Inicialización ---
    sensor_init();
    Actuator *led = create_led_actuator();
    Actuator *buzzer = create_buzzer_actuator();

    if (!led || !buzzer) {
        fprintf(stderr, "Error: Failed to create actuators.\n");
        return 1;
    }

    struct timespec last_deactivated = {0};
    int buzzer_timer_active = 0;
    int led_timer_active = 0;

    // --- Bucle Principal ---
    while (1) {
        // Limpia la pantalla de la terminal y mueve el cursor al inicio
        printf(CLEAR_SCREEN CURSOR_HOME);

        struct timespec current_time;
        clock_gettime(CLOCK_MONOTONIC, &current_time);

        double sensor_value = sensor_read();

        if (sensor_value >= THRESHOLD) {
            // Umbral superado: activar todo y cancelar temporizadores
            led->activate(led);
            buzzer->activate(buzzer);
            buzzer_timer_active = 0;
            led_timer_active = 0;
        } else {
            // Umbral no superado: gestionar desactivación temporizada
            if (buzzer->status(buzzer) || led->status(led)) {
                 if (!buzzer_timer_active && !led_timer_active) {
                    // Si es la primera vez que baja del umbral, registrar el tiempo
                    last_deactivated = current_time;
                    buzzer_timer_active = 1;
                    led_timer_active = 1;
                }
            }

            // Comprobar si ha pasado 1 segundo para apagar el buzzer
            if (buzzer_timer_active && (current_time.tv_sec - last_deactivated.tv_sec >= 1)) {
                buzzer->deactivate(buzzer);
                buzzer_timer_active = 0;
            }

            // Comprobar si han pasado 5 segundos para apagar el LED
            if (led_timer_active && (current_time.tv_sec - last_deactivated.tv_sec >= 5)) {
                led->deactivate(led);
                led_timer_active = 0;
            }
        }

        // --- Log Mejorado y Estático ---
        printf("--- Controlador de Lazo Cerrado ---\n\n");
        printf("  Timestamp:    %ld.%09ld\n", current_time.tv_sec, current_time.tv_nsec);
        printf("  Valor Sensor: %.2f (Umbral: %.1f)\n", sensor_value, THRESHOLD);
        printf("\n");
        printf("  Estado LED:   %s\n", led->status(led) ? "ON " : "OFF");
        printf("  Estado Buzzer:%s\n", buzzer->status(buzzer) ? "ON " : "OFF");
        printf("\n-------------------------------------\n");
        printf("Presione Ctrl+C para salir.\n");
        fflush(stdout); // Asegura que la salida se imprima en la terminal inmediatamente

        usleep(LOOP_DELAY_US);
    }

    // --- Limpieza (aunque el bucle es infinito, es buena práctica) ---
    free(led->params);
    free(led);
    free(buzzer->params);
    free(buzzer);

    return 0;
}

