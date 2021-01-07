#include "rodillo.h"
#include "partemodelojerarquico.h"
#include "malla.h"

Rodillo::Rodillo() {

  Tupla3f colorNegro = Tupla3f( 0, 0, 0 );
  Tupla3f colorAmarillo = Tupla3f( 1, 1, 0 );
  Material obsidiana = Material(Tupla4f(0.18275,0.17,0.22525,1),Tupla4f(0.332741,0.328634,0.346435,1),Tupla4f(0.05375,0.05,0.06625,1),0.3);
  Material chapa = Material(Tupla4f(0.7,0.7,0.04,1),Tupla4f(0.05,0.05,0.0,1),Tupla4f(0.05,0.05,0.04,1),0.78125);

  rodillo = new Cilindro( 4, 20, 10, 5 );
  rodillo->setColorSolido( colorNegro );
  rodillo->setMaterial( obsidiana );

  sujeccionCentral = new Cilindro( 3, 20, 10, 5 );
  sujeccionCentral->setColorSolido( colorAmarillo );
  sujeccionCentral->setMaterial( chapa );

  sujeccionSuperior = new Cubo( 10 );
  sujeccionSuperior->setColorSolido( colorAmarillo );
  sujeccionSuperior->setMaterial( chapa );

}

void Rodillo::draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  glPushMatrix();
    glTranslatef( 0, 0, desplazamientoRodillo );
    glRotatef( anguloRotacionRodillo, 0, 0, 1 );
    glRotatef( 90, 1, 0, 0 );
    glScalef( 4, 14, 4 );
    rodillo->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glRotatef( 90, 1, 0, 0 );
    glScalef( 4.5, 1, 4.5 );
    sujeccionCentral->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0, 8.75, desplazamientoRodillo );
    glScalef( 1, 2.75, 15 );
    sujeccionSuperior->draw( tipoDibujado, tipoVisualizacion );
  glPopMatrix();

}

void Rodillo::rotarRodillo( float angulo ) {

  anguloRotacionRodillo += angulo;

}

void Rodillo::trasladarRodillo( float cantidad ) {

  desplazamientoRodillo += cantidad;

  if( desplazamientoRodillo < minDesplazamientoRodillo )
    desplazamientoRodillo = minDesplazamientoRodillo;

  if( desplazamientoRodillo > maxDesplazamientoRodillo )
    desplazamientoRodillo = maxDesplazamientoRodillo;

}

bool Rodillo::rodilloTrasladadoAlTope() {

  return ( ( desplazamientoRodillo == minDesplazamientoRodillo ) ||
           ( desplazamientoRodillo == maxDesplazamientoRodillo ) );

}
