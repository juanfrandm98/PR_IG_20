#ifndef RODILLO_H_INCLUDED
#define RODILLO_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cubo.h"

class Rodillo : public ParteModeloJerarquico {

private:
  Cilindro * rodillo          = nullptr;
  Cilindro * sujeccionCentral = nullptr;
  Cubo * sujeccionSuperior    = nullptr;

  float anguloRotacionRodillo = 0;

  float desplazamientoRodillo = 0;
  const float maxDesplazamientoRodillo = 55;
  const float minDesplazamientoRodillo = -55;

public:
  Rodillo();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void rotarRodillo( float angulo );
  void trasladarRodillo( float cantidad );
  bool rodilloTrasladadoAlTope();
  void setColorSeleccion( Tupla3f color );

};

#endif
