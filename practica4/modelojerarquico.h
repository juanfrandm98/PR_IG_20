#ifndef MODELOJERARQUICO_H_INCLUDED
#define MODELOJERARQUICO_H_INCLUDED

#include "malla.h"
#include "partemodelojerarquico.h"

class ModeloJerarquico : public Malla3D {

public:
  virtual void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) = 0;

};

#endif
