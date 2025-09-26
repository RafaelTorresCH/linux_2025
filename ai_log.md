# Log de Interacción con IA

## Introducción

A continuación se detallan los prompts enviados al agente de IA para la construcción del proyecto y el razonamiento detrás de cada uno. Este documento sirve como registro del proceso de desarrollo asistido por IA, cumpliendo con uno de los entregables de la tarea.


# Interacción 1: Creación de la Estructura del Proyecto
Mi Prompt:
Hola. Necesito que crees la estructura de archivos completa para un nuevo proyecto en C llamado HOMEWORK2. Por favor, genera los siguientes directorios y archivos vacíos directamente:

HOMEWORK2/
├── Makefile
├── README.md
├── ai_log.md
├── sensor/
│   ├── sensor.h
│   └── sensor.c
├── actuators/
│   ├── actuator.h
│   ├── led_actuator.c
│   └── buzzer_actuator.c
└── controller/
    └── ctl.c

Razón del Prompt:
Para establecer la estructura base del proyecto de acuerdo con los requisitos de la tarea. Empezar con un esqueleto organizado es fundamental para la modularidad y facilita la compilación.



# Interacción 2: Creación de sensor/sensor.h
Mi Prompt:
Ahora, genera el contenido completo para el archivo sensor/sensor.h. Este archivo debe definir la interfaz pública para la biblioteca del sensor. Asegúrate de que incluya:

Guardas de inclusión (#ifndef/#define/#endif).

La declaración de la función void sensor_init(void);.

La declaración de la función double sensor_read(void);.

Comentarios de documentación estilo Doxygen para cada función, explicando brevemente su propósito.

Razón del Prompt:
Para definir el "contrato" o la interfaz pública del módulo del sensor. Es una buena práctica de diseño empezar por las cabeceras antes que la implementación.

# Interacción 3: Creación de sensor/sensor.c
Mi Prompt:
Perfecto. Ahora crea la implementación en sensor/sensor.c. El archivo debe:

Incluir <stdio.h>, <stdlib.h>, <time.h> y su propia cabecera "sensor.h".

Implementar sensor_init(void) para que inicialice el generador de números aleatorios usando srand(time(NULL));.

Implementar sensor_read(void) para que devuelva un valor double aleatorio entre 0.0 y 100.0.

Añadir comentarios internos explicando la lógica.

Razón del Prompt:
Para tener una implementación funcional y simulada del sensor. Esto me permite desarrollar y probar el resto del sistema sin necesidad de hardware real.


# Interacción 4: Creación de actuators/actuator.h
Mi Prompt:
Pasemos al ejercicio 2. Genera el contenido para actuators/actuator.h. Este archivo definirá una interfaz genérica y polimórfica para diferentes actuadores. Debe contener:

Guardas de inclusión.

Una declaración anticipada typedef struct Actuator Actuator;.

La definición de la estructura Actuator, que debe contener:

Un puntero void *params;.

Tres punteros a funciones: void (*activate)(Actuator *self);, void (*deactivate)(Actuator *self); y int (*status)(Actuator *self);.

Comentarios Doxygen para la estructura y cada uno de sus miembros.

Razón del Prompt:
Para demostrar polimorfismo en C, que se logra comúnmente mediante una estructura con punteros a funciones. Este archivo define esa interfaz común.

# Interacción 5: Creación de actuators/led_actuator.c
Mi Prompt:
Ahora, implementa el primer actuador concreto en actuators/led_actuator.c. El código debe seguir este patrón:

Incluir <stdio.h>, <stdlib.h> y "actuator.h".

Definir una estructura privada para el estado del LED (LedParams).

Definir las funciones static que implementarán la lógica del LED: led_activate, led_deactivate, led_status. Por ahora, solo deben imprimir un mensaje en consola (ej: "LED ACTIVATED") y gestionar un estado interno.

Crear una función pública "constructora": Actuator* create_led_actuator();. Esta función debe reservar memoria dinámicamente para la struct Actuator y su params, y luego asignar los punteros a funciones a las implementaciones estáticas del LED.

Razón del Prompt:
Para crear la primera implementación concreta de la interfaz Actuator, demostrando cómo un módulo específico se adhiere al contrato genérico.



# Interacción 6: Creación de actuators/buzzer_actuator.c
Mi Prompt:
De forma similar, crea la implementación para el buzzer en actuators/buzzer_actuator.c. Sigue exactamente el mismo patrón que el actuador LED:

Define una estructura BuzzerParams para el estado.

Define las funciones estáticas buzzer_activate, buzzer_deactivate, buzzer_status que impriman mensajes en consola (ej: "BUZZER: BEEP BEEP").

Crea la función constructora pública Actuator* create_buzzer_actuator();.

Razón del Prompt:
Para crear una segunda implementación de la interfaz y así poder probar que el diseño polimórfico funciona correctamente.



# Interacción 7: Creación de controller/ctl.c
Mi Prompt:
Es hora de integrar todo en controller/ctl.c. Este será el programa principal. El código debe:

Incluir las cabeceras de todos los módulos (sensor.h, actuator.h) y las de C estándar necesarias (<stdio.h>, <unistd.h>, <time.h>).

Declarar las funciones constructoras de los actuadores usando extern.

En main():

Inicializar el sensor.

Crear una instancia del LED y del Buzzer.

Definir un THRESHOLD de 75.0.

Implementar un bucle infinito while(1).

Dentro del bucle:

Usar clock_gettime(CLOCK_MONOTONIC, ...) para la gestión del tiempo.

Leer el sensor.

Implementar la lógica de control: si el valor supera el umbral, activar actuadores; si no, gestionar la desactivación temporizada (buzzer a 1s, LED a 5s) usando el tiempo monotónico, sin usar sleep() para la lógica de temporización.

Imprimir un log en cada iteración con: timestamp, valor del sensor y el estado de cada actuador.

Esperar 100 milisegundos al final del bucle (puedes usar usleep o nanosleep para esta pausa).

Razón del Prompt:
Para implementar el núcleo de la aplicación donde todos los módulos se integran.



# Interacción 8: Creación del Makefile
Mi Prompt:
Finalmente, genera el contenido del Makefile. Debe tener:

Variables para CC, CFLAGS (-Wall -Wextra -std=c11), y LDFLAGS.

Una lista de todos los archivos fuente (.c).

Un objetivo all que por defecto construya ctl64.

Un objetivo ctl64 para compilar un ejecutable de 64 bits.

Un objetivo ctl32 que añada el flag -m32 a CFLAGS y LDFLAGS para compilar un ejecutable de 32 bits.

Un objetivo clean para eliminar los archivos objeto y los ejecutables.

Usar variables automáticas como $@ y $^ para que sea más genérico.

Razón del Prompt:
Para automatizar el proceso de compilación de manera reproducible, que es un requisito clave de la tarea.