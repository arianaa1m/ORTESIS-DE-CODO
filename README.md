ortesis_fabi
# ORTESIS-DE-CODO
Código para funcionamiento de órtesis de codo para tratar rigidez de codo.
# DESCRIPCIÓN
Este repositorio contiene el código fuente desarrollado para el control y monitoreo de una órtesis de codo. El objetivo del software es gestionar los sensores, actuadores y la lógica de retroalimentación que permiten asistir y actuar de acuerdo a los movimientos del brazo del usuario.
## COMPONENTES RELACIONADOS
  Microcontrolador: Arduino UNO.
  Sensores: Sensor de Electromiografía.
  Actuadores: Servomotor para asistencia de movimientos.
## FUNCIONALIDADES IMPLEMENTADAS 
  Monitoreo de fuerza aplicada en tiempo real.
  Control del movimiento asistido según la fuerza detectada.
  Comunicación serial para depuración y análisis de datos.
  Sistema antirrebote para botones físicos de inicio/pausa.
## TECNOLOGÍAS
  Lenguaje de programación: C++ para Arduino.
  IDE: Arduino IDE.
  Librerías: Servo.h para el control del servomotor.
## INSTRUCCIONES DE USO
Clone este repositorio:
  **bash** 
  **git clone https://github.com/usuario/ortesis-codo.git**  
Abra el archivo ortesis_codo.ino en Arduino IDE.
Conecte los componentes según el esquema físico (adjunto al proyecto).
Suba el código al microcontrolador y monitoree la salida en la consola serial para pruebas.
## Grupo conformado por: Ariana Muñoz, Tatiana Kitay-Gora y Fabiana Pelaez
main
