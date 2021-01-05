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

void TractorRemolque::cambiarAnguloGiro( float angulo ) {

  tractor->cambiarAnguloGiro(angulo);

}

void TractorRemolque::rotarRuedas( float angulo ) {

  tractor->rotarRuedas(angulo);

}

bool TractorRemolque::ruedasAlTope() {

  return tractor->ruedasAlTope();

}
