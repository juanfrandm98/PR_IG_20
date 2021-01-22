#include "ejetrasero.h"
#include "partemodelojerarquico.h"
#include "malla.h"

EjeTrasero::EjeTrasero() {

  ruedaIzquierda = new RuedaTrasera();
  ruedaDerecha   = new RuedaTrasera();

}

void EjeTrasero::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 0, -45 );
    glRotatef( anguloRotacion, 0, 0, 1 );
    ruedaDerecha->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0, 0, 45 );
    glRotatef( anguloRotacion, 0, 0, 1 );
    ruedaIzquierda->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void EjeTrasero::rotarRuedas( float angulo ) {

  anguloRotacion += angulo;

}

void EjeTrasero::setColorSeleccion( Tupla3f color ) {
  ruedaDerecha->setColorSeleccion(color);
  ruedaIzquierda->setColorSeleccion(color);
}

void EjeTrasero::setMaterialSeleccion( Material mat ) {
  ruedaDerecha->setMaterialSeleccion(mat);
  ruedaIzquierda->setMaterialSeleccion(mat);
}
