#ifndef CHASIS_H_INCLUDED
#define CHASIS_H_INCLUDED

#include "partemodelojerarquico.h"
#include "ejedelantero.h"
#include "ejetrasero.h"
#include "cubo.h"

class Chasis : public ParteModeloJerarquico {

private:
  EjeDelantero * ejeDelantero = nullptr;
  EjeTrasero * ejeTrasero     = nullptr;
  Cubo * chasisDelantero      = nullptr;
  Cubo * chasisTrasero        = nullptr;
  Cubo * munionDelantero      = nullptr;

public:
  Chasis();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void cambiarAnguloGiro( float angulo );
  void rotarRuedas( float angulo );
  bool ruedasAlTope();

};

#endif
