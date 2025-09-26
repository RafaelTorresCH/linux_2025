# Compilador a usar
CC = gcc

# Flags de compilación.
# -D_POSIX_C_SOURCE=199309L activa las funciones de tiempo real como clock_gettime
# -I./sensor y -I./actuators son las rutas de inclusión de cabeceras
CFLAGS = -Wall -Wextra -std=c11 -D_POSIX_C_SOURCE=199309L -I./sensor -I./actuators

# Flags del enlazador (Linker).
# -lrt enlaza la librería de tiempo real (necesaria para clock_gettime)
LDFLAGS = -lrt

# Lista de todos los archivos fuente .c
SOURCES = sensor/sensor.c \
          actuators/led_actuator.c \
          actuators/buzzer_actuator.c \
          controller/ctl.c

# Genera automáticamente la lista de archivos objeto .o a partir de los .c
OBJECTS = $(SOURCES:.c=.o)

# Nombres de los ejecutables finales
TARGET64 = ctl64
TARGET32 = ctl32

# El objetivo por defecto que se ejecuta con 'make'
all: $(TARGET64)

# Regla para construir el ejecutable de 64 bits
$(TARGET64): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET64) $(LDFLAGS)

# Regla para construir el ejecutable de 32 bits
# Nota: La librería de 32 bits (-lrt) también debe estar instalada
ctl32:
	$(CC) -m32 $(OBJECTS) -o $(TARGET32) $(LDFLAGS) -m32

# Regla genérica para compilar cualquier archivo .c a .o
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Regla para limpiar el proyecto
clean:
	rm -f $(OBJECTS) $(TARGET64) $(TARGET32)

