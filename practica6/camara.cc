#include "camara.h"

void Camara::setObservador() {

  gluLookAt( eye(0), eye(1), eye(2),      // Posición del "ojo"
              at(0),  at(1),  at(2),      // Posición de referencia
              up(0),  up(1),  up(2) );    // Dirección del vector "up"

}
