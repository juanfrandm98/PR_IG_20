#include "pino.h"
#include "modelojerarquico.h"

Pino::Pino() {

  tronco = new Tronco();
  componentes.push_back( tronco );

  copa = new Copa();
  componentes.push_back( copa );

}
