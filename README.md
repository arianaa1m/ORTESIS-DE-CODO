
# ORTESIS-DE-CODO
Órtesis de flexo-extensión para el codo
## Grupo conformado por: Ariana Muñoz, Tatiana Kitay-Gora y Fabiana Antonella Pelaez
## Código en Arduino IDE (propósito del código)


El propósito de este código en el proyecto es **medir y procesar datos de orientación y movimiento** utilizando dos sensores **LSM6DS3**, que son **acelerómetros** y **giroscopios** de seis ejes. El código tiene como objetivo principal obtener la inclinación y la rotación de un objeto en tres dimensiones (3D), proporcionando información precisa sobre la orientación del dispositivo o sistema en el que se encuentren instalados los sensores.

Este tipo de medición y procesamiento es crucial en aplicaciones donde se necesita controlar o monitorear la posición y el movimiento de un objeto. 

1. **Medición de la Orientación 3D**: 
   El código permite calcular los ángulos de inclinación (en los ejes X, Y y Z) de un objeto con dos sensores LSM6DS3. Al combinar la información del **acelerómetro** (que mide la gravedad y la inclinación) y del **giroscopio** (que mide la velocidad angular o la rotación), el código obtiene una medición más precisa y confiable de la orientación del objeto.

2. **Compensación de Errores en las Lecturas**:
   Gracias al **filtro complementario**, el código fusiona los datos del acelerómetro y el giroscopio para obtener un ángulo más preciso. El acelerómetro es estable a largo plazo pero puede verse afectado por ruidos o vibraciones, mientras que el giroscopio es preciso a corto plazo pero acumula errores con el tiempo. El filtro complementario logra equilibrar estas dos fuentes de información para proporcionar un valor de ángulo más exacto y confiable.

3. **Aplicaciones en Robótica y Sistemas de Control**:
   Este código es muy útil en **proyectos de robótica**, **sistemas de navegación de drones**, **dispositivos portátiles de seguimiento de movimiento** o **sistemas de control de orientación**. Al calcular y seguir en tiempo real los ángulos de inclinación y rotación, el proyecto puede ser utilizado para controlar el movimiento de un robot, ajustar la dirección de un dron o incluso monitorear la postura de un usuario en aplicaciones de salud.

4. **Mediciones Continuas y en Tiempo Real**:
   Con el uso de la función `millis()`, el código garantiza que las lecturas de los sensores se tomen de manera continua y en intervalos regulares (300ms), lo que es fundamental para aplicaciones donde se necesita información en tiempo real sobre el movimiento o la orientación del dispositivo.

   # Diagrama: Funcionamiento del proyecto

```mermaid
graph TD;
    RESET-->ESTADO_1_INIT;
    ESTADO_1_INIT-->ESTADO_2_IDLE;
    ESTADO_2_IDLE-->ESTADO_3_LECTURA_EMG;
    ESTADO_3_LECTURA_EMG-->ESTADO_4_PROCESAMIENTO_SEÑAL;
    ESTADO_4_PROCESAMIENTO_SEÑAL-->ESTADO_5_RESPUESTA_ORTESIS;

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
