#include "tractorremolque.h"
#include "modelojerarquico.h"

TractorRemolque::TractorRemolque() {

  tractor = new Tractor();

}

void TractorRemolque::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    //glTranslatef( 0, 35, 0);
    tractor->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}
