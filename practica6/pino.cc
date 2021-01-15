#include "pino.h"
#include "modelojerarquico.h"

Pino::Pino() {

  tronco = new Tronco();
  copa = new Copa();

}

void Pino::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 25, 0 );
    tronco->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();
  glPushMatrix();
    glTranslatef( 0, 100, 0 );
    copa->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void Pino::setColorSeleccion( Tupla3f color ) {
  tronco->setColorSeleccion(color);
  copa->setColorSeleccion(color);
}

Tupla3f Pino::getCentro() {

  return Tupla3f( 0, 50, 0 );

}
