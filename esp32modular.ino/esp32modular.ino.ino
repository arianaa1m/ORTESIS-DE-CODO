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