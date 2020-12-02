#include "luz.h"

void Luz::aplicar() {

  // Configuramos los colores de la fuente de luz
  glLightfv( id, GL_POSITION, posicion );
  glLightfv( id, GL_AMBIENT,  colorAmbiente );
  glLightfv( id, GL_DIFFUSE,  colorDifuso );
  glLightfv( id, GL_SPECULAR, colorEspecular );

  // Encendemos la luz
  glEnable( id );

}

Tupla3f Luz::getPosicion() {
  Tupla3f resultado;
  resultado(0) = posicion(0);
  resultado(1) = posicion(1);
  resultado(2) = posicion(2);
  return resultado;
}
