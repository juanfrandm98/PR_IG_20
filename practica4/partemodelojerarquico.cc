#include "partemodelojerarquico.h"
#include "malla.h"

void ParteModeloJerarquico::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  for( int i = 0; i < componentes.size(); i++ ) {
    glPushMatrix();
      glTranslatef( componentes[i].posicion(0), componentes[i].posicion(1), componentes[i].posicion(2) );
      glRotatef( componentes[i].orientacion(0), 1, 0, 0 );
      glRotatef( componentes[i].orientacion(1), 0, 1, 0 );
      glRotatef( componentes[i].orientacion(2), 0, 0, 1 );
      glScalef( componentes[i].escalado(0), componentes[i].escalado(1), componentes[i].escalado(2) );
      componentes[i].objeto->draw( tipoDibujado, tipoVisualizacion );
    glPopMatrix();
  }

  for( int i = 0; i < partes.size(); i++ )
    partes[i]->draw( tipoDibujado, tipoVisualizacion );

}
