#ifndef PARTEMODJER_H_INCLUDED
#define PARTEMODJER_H_INCLUDED

#include "malla.h"

class ParteModeloJerarquico : public Malla3D {

public:
  virtual void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) = 0;

};

#endif
