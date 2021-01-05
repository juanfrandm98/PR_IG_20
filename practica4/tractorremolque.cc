#include "tractorremolque.h"
#include "modelojerarquico.h"

TractorRemolque::TractorRemolque() {

  tractor  = new Tractor();
  remolque = new Remolque();

}

void TractorRemolque::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    tractor->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 65, 0, 0);
    remolque->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void TractorRemolque::cambiarAnguloGiro( float angulo ) {

  tractor->cambiarAnguloGiro(angulo);

}

void TractorRemolque::simularAvance( float angulo ) {

  tractor->rotarRuedas(angulo);
  remolque->rotarRodillo(angulo);

}

bool TractorRemolque::ruedasAlTope() {

  return tractor->ruedasAlTope();

}

void TractorRemolque::inclinarRemolque( float angulo ) {

  remolque->inclinarRemolque(angulo);

}

void TractorRemolque::girarRemolque( float angulo ) {

  remolque->girarRemolque(angulo);

}

bool TractorRemolque::inclinacionAlTope() {

  return remolque->inclinacionAlTope();

}

bool TractorRemolque::remolqueGiradoAlTope() {

  return remolque->remolqueGiradoAlTope();

}

void TractorRemolque::trasladarRodillo( float cantidad ) {

  remolque->trasladarRodillo(cantidad);

}

bool TractorRemolque::rodilloTrasladadoAlTope() {

  return remolque->rodilloTrasladadoAlTope();

}
