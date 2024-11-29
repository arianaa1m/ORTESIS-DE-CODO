# ORTESIS-DE-CODO
Órtesis de flexo-extensión para el codo
## Grupo conformado por: Ariana Muñoz, Tatiana Kitay-Gora y Fabiana Antonella Pelaez
## Código en Arduino IDE (propósito del código)

El propósito de este código en el proyecto es **medir y procesar datos de orientación y movimiento** utilizando dos sensores **LSM6DS3**, que son **acelerómetros** y **giroscopios** de seis ejes. El código tiene como objetivo principal obtener la inclinación y la rotación de un objeto en tres dimensiones (3D), proporcionando información precisa sobre la orientación del dispositivo o sistema en el que se encuentren instalados los sensores.

Este tipo de medición y procesamiento es crucial en aplicaciones donde se necesita controlar o monitorear la posición y el movimiento de un objeto. Aquí se describe más específicamente cómo este código contribuye al proyecto:

1. **Medición de la Orientación 3D**: 
   El código permite calcular los ángulos de inclinación (en los ejes X, Y y Z) de un objeto con dos sensores LSM6DS3. Al combinar la información del **acelerómetro** (que mide la gravedad y la inclinación) y del **giroscopio** (que mide la velocidad angular o la rotación), el código obtiene una medición más precisa y confiable de la orientación del objeto.

2. **Compensación de Errores en las Lecturas**:
   Gracias al **filtro complementario**, el código fusiona los datos del acelerómetro y el giroscopio para obtener un ángulo más preciso. El acelerómetro es estable a largo plazo pero puede verse afectado por ruidos o vibraciones, mientras que el giroscopio es preciso a corto plazo pero acumula errores con el tiempo. El filtro complementario logra equilibrar estas dos fuentes de información para proporcionar un valor de ángulo más exacto y confiable.

3. **Aplicaciones en Robótica y Sistemas de Control**:
   Este código es muy útil en **proyectos de robótica**, **sistemas de navegación de drones**, **dispositivos portátiles de seguimiento de movimiento** o **sistemas de control de orientación**. Al calcular y seguir en tiempo real los ángulos de inclinación y rotación, el proyecto puede ser utilizado para controlar el movimiento de un robot, ajustar la dirección de un dron o incluso monitorear la postura de un usuario en aplicaciones de salud.

4. **Mediciones Continuas y en Tiempo Real**:
   Con el uso de la función `millis()`, el código garantiza que las lecturas de los sensores se tomen de manera continua y en intervalos regulares (300ms), lo que es fundamental para aplicaciones donde se necesita información en tiempo real sobre el movimiento o la orientación del dispositivo.