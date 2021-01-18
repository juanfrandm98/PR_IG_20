#include "tractor.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Tractor::Tractor() {

  chasis     = new Chasis();
  habitaculo = new Habitaculo();
  techo      = new Techo();
  asiento    = new Asiento();

}

void Tractor::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    chasis->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 40, 30, 0 );
    habitaculo->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 27.5, 57.5, 0 );
    techo->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 30, 25, 0 );
    asiento->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void Tractor::cambiarAnguloGiro( float angulo ) {

  chasis->cambiarAnguloGiro(angulo);

}

void Tractor::rotarRuedas( float angulo ) {

  chasis->rotarRuedas(angulo);

}

bool Tractor::ruedasAlTope() {

  return chasis->ruedasAlTope();

}

void Tractor::setColorSeleccion( Tupla3f color ) {
  chasis->setColorSeleccion(color);
  habitaculo->setColorSeleccion(color);
  techo->setColorSeleccion(color);
  asiento->setColorSeleccion(color);
}

void Tractor::setMaterialSeleccion( Material mat ) {
  chasis->setMaterialSeleccion(mat);
  habitaculo->setMaterialSeleccion(mat);
  techo->setMaterialSeleccion(mat);
  asiento->setMaterialSeleccion(mat);
}
