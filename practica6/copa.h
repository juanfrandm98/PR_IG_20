#ifndef COPA_H_INCLUDED
#define COPA_H_INCLUDED

#include "partemodelojerarquico.h"
#include "malla.h"
#include "objrevolucion.h"
#include "cono.h"

class Copa : public ParteModeloJerarquico {

private :
  Malla3D * cono = nullptr;

public:
  Copa();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  void setColorSeleccion( Tupla3f color );
};

#endif
