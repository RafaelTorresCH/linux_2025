# Proyecto Controlador

## Descripción
Este proyecto implementa un sistema de control que utiliza un sensor y dos actuadores (LED y Buzzer). El sistema lee valores del sensor y activa o desactiva los actuadores en función de un umbral definido.


## Ejemplo de Ejecución

BUZZER STATUS: ON
--- Controlador de Lazo Cerrado ---

  Timestamp:    558.847792744
  Valor Sensor: 34.27 (Umbral: 75.0)

LED STATUS: ON
  Estado LED:   ON 
BUZZER STATUS: ON
  Estado Buzzer:ON 

-------------------------------------
Presione Ctrl+C para salir.



BUZZER STATUS: ON
--- Controlador de Lazo Cerrado ---

  Timestamp:    558.948097833
  Valor Sensor: 30.66 (Umbral: 75.0)

LED STATUS: ON
  Estado LED:   ON 
BUZZER STATUS: ON
  Estado Buzzer:ON 

-------------------------------------
Presione Ctrl+C para salir.


BUZZER STATUS: ON
BUZZER: SILENT
--- Controlador de Lazo Cerrado ---

  Timestamp:    559.048333513
  Valor Sensor: 2.32 (Umbral: 75.0)

LED STATUS: ON
  Estado LED:   ON 
BUZZER STATUS: OFF
  Estado Buzzer:OFF

-------------------------------------
Presione Ctrl+C para salir.


## Inspección de Binarios
- Use herramientas como `file` o `objdump` para inspeccionar los binarios generados.

file ctl64
ctl64: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=307b1e15e7df2205318e0b0c4c7dfd0d71b8a0b4, for GNU/Linux 3.2.0, not stripped

readelf -h ctl64
ELF Header:
  Magic:   7f 45 4c 46 02 01 01 00 00 00 00 00 00 00 00 00 
  Class:                             ELF64
  Data:                              2's complement, little endian
  Version:                           1 (current)
  OS/ABI:                            UNIX - System V
  ABI Version:                       0
  Type:                              DYN (Position-Independent Executable file)
  Machine:                           Advanced Micro Devices X86-64
  Version:                           0x1
  Entry point address:               0x11e0
  Start of program headers:          64 (bytes into file)
  Start of section headers:          15072 (bytes into file)
  Flags:                             0x0
  Size of this header:               64 (bytes)
  Size of program headers:           56 (bytes)
  Number of program headers:         13
  Size of section headers:           64 (bytes)
  Number of section headers:         31
  Section header string table index: 30

## Reflexión sobre Conceptos
Este proyecto demuestra el uso de sensores y actuadores en un sistema embebido, así como la integración de múltiples módulos en C utilizando un Makefile.