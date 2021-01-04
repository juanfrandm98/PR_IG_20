#ifndef TRACTORREMOLQUE_H_INCLUDED
#define TRACTORREMOLQUE_H_INCLUDED

#include "modelojerarquico.h"
#include "tractor.h"

class TractorRemolque : public ModeloJerarquico {

private:
  Tractor * tractor = nullptr;

public:
  TractorRemolque();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

};

#endif
