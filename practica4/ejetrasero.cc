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
    ruedaDerecha->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0, 0, 45 );
    ruedaIzquierda->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}
