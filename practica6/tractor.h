#ifndef TRACTOR_H_INCLUDED
#define TRACTOR_H_INCLUDED

#include "partemodelojerarquico.h"
#include "chasis.h"
#include "habitaculo.h"
#include "techo.h"
#include "asiento.h"

class Tractor : public ParteModeloJerarquico {

private:
  Chasis * chasis         = nullptr;
  Habitaculo * habitaculo = nullptr;
  Techo * techo           = nullptr;
  Asiento * asiento       = nullptr;

public:
  Tractor();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void cambiarAnguloGiro( float angulo );
  void rotarRuedas( float angulo );
  bool ruedasAlTope();
  void setColorSeleccion( Tupla3f color );
  void setMaterialSeleccion( Material mat );

};

#endif
