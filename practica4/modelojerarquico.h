#ifndef MODELOJERARQUICO_H_INCLUDED
#define MODELOJERARQUICO_H_INCLUDED

#include "malla.h"
#include "partemodelojerarquico.h"

class ModeloJerarquico : public Malla3D {

public:
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

protected:
  std::vector<ParteModeloJerarquico*> componentes;

};

#endif
