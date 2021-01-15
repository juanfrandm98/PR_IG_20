#ifndef RUEDA_DELANTERA_H_INCLUDED
#define RUEDA_DELANTERA_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cilindro.h"

class RuedaDelantera : public ParteModeloJerarquico {

private:
  Malla3D * rueda = nullptr;

public:
  RuedaDelantera();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void setColorSeleccion( Tupla3f color );

};

#endif
