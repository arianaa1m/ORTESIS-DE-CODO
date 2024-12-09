/*.ino*/
typedef enum{  /*Aquí van las macros*/
  IDDLE,
  SENSORLECTURA,
  ACTUACION,
  RESPUESTA
} fsm;
fsm SENSORLECTURA=IDDLE;
int variable=valor;

void loop() {
switch(SENSORLECTURA){
  case IDDLE:
  funcion();
     /*Aquí incluimos el código del cpp que debe realizar*/
    /*añadimos un if para que se vaya a la opcion de configuración
    cuando ocurra una accion como apretar el boton de encendido más tiempo*/
    if (condicion1){
      maquina=LECTURAEMG;
    }
    if (condicion2){
      maquina=CONFIG;
    }
    maquina=LECTURAEMG;
    break;
  case LECTURAEMG:
    /*Codigo del cpp*/
    maquina=PROCYACT;
    break;


/* Trabajamos con máquina de estados*/
#include "funciones.h"

// Definimos estados
typedef enum {
  IDDLE, //separados por ¨,¨
  LECTURA_SENSORES,
  CALCULO,
  FILTRO_COMPLEMENTARIO,
  IMPRIMIR_RESULTADOS
} fsm;

fsm maquina = IDDLE; 
//Definimos el valor de las variables 
unsigned long currTime = 0;
unsigned long prevTimeCap = 0;
int currPeriod = 0;
int maxPeriod = 0;
int cont = 0;

/*usamos un void setup para inicializar una sola vez el sensor con un delay de 10seg.*/
void setup() {
  Serial.begin(115200); //usamos ese tiempo porque trabajamos con un ESP32
  delay(10000);
  iniciarSensores();
}

void loop() {
  currTime = millis();

  switch (maquina) {
    case IDDLE:
      // ene esta parte se espera el tiempo establecido para empezar a hacer la lectura
      if (currTime - prevTimeCap >= timePeriod) {
        maquina = LECTURA_SENSORES;
      }
      break; //siempre hacemos un break antes de pasar al siguiente caso

    case LECTURA_SENSORES:
      leerSensores();
      maquina = CALCULO; //cambiamos al siguiente caso después de leer los valores del sensor
      break;

    case CALCULO:
      calcularAngulos();
      maquina = FILTRO_COMPLEMENTARIO;
      break;

    case FILTRO_COMPLEMENTARIO:
      // Usamos un filtro digital complementario para que haya una mejor lectura 
      aplicarFiltroComplementario();
      maquina = IMPRIMIR_RESULTADOS;
      break;

    case IMPRIMIR_RESULTADOS:
      imprimirResultados();
      cont++;
      prevTimeCap = currTime;
      maquina = IDDLE;  // volvemos al estado IDDLE para que se cumpla el loop
      break;
  }
}