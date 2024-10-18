typedef enum {
  IDDLE,
  LECTURAEMG,
  PROCESAMIENTOEMG,
  ACTUADORES,
  CONFIG
}fsm;
fsm maquina = IDDLE;

void loop() {
  switch (maquina){
    case IDDLE:
    //código funciones
    //esperaboton();
    //if (BOTON PRESIONADO){maquina= LECTURAEMG;}
    //if (botón con pulsacion prolongada){maquina= CONFIG;}
    maquina = LECTURAEMG;
    break;
  case LECTURAEMG:
    //código funciones
    maquina= PROCESAMIENTOEMG;
    break;
  case PROCESAMIENTOEMG:
    //código funciones
    maquina= ACTUADORES;
    break;
  case ACTUADORES:
    //código funciones
    maquina= LECTURAEMG;
  case CONFIG:
    //código funciones
    maquina= IDDLE;
    break;
  }
}

void setup() {
  
}