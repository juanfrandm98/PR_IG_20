#include "tractorremolque.h"
#include "modelojerarquico.h"

TractorRemolque::TractorRemolque() {

  Material oro = Material(Tupla4f(0.75164,0.60648,0.22648,1),Tupla4f(0.628281,0.555802,0.366065,1),Tupla4f(0.24725,0.1995,0.0745,1),0.4);

  tractor  = new Tractor();
  remolque = new Remolque();

  marcador = new ObjRevolucion( "./plys/letra_d", 20, true, true, 220 );
  marcador->setColorSolido( Tupla3f( 1, 1, 0 ) );
  marcador->setMaterial( oro );

}

void TractorRemolque::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    tractor->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 65, 0, 0);
    remolque->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0, 120, 0 );
    glScalef( 2.5, 2.5, 2.5 );
    marcador->draw( tipoDibujado, tipoVisualizacion );
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

void TractorRemolque::setColorSeleccion( Tupla3f color ) {
  tractor->setColorSeleccion(color);
  remolque->setColorSeleccion(color);
}

void TractorRemolque::setMaterialSeleccion( Material mat ) {
  tractor->setMaterialSeleccion(mat);
  remolque->setMaterialSeleccion(mat);
}

Tupla3f TractorRemolque::getCentro() {
  Tupla3f centro = Tupla3f( 0, 40, 0 );
  centro = centro + pos;

  return pos;
}

Tupla3f TractorRemolque::getPos() {
  return pos;
}

void TractorRemolque::retrocederX( float cantidad ) {
  pos(0) -= cantidad;
}
