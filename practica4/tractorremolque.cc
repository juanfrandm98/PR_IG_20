#include "tractorremolque.h"
#include "modelojerarquico.h"

TractorRemolque::TractorRemolque() {

  chasis = new Chasis();

}

void TractorRemolque::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 35, 0);
    chasis->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}
