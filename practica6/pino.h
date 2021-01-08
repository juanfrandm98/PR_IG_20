#ifndef PINO_H_INCLUDED
#define PINO_H_INCLUDED

#include "modelojerarquico.h"
#include "tronco.h"
#include "copa.h"

class Pino : public ModeloJerarquico {

public:
  Pino();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );

private:
  Tronco * tronco = nullptr;
  Copa * copa = nullptr;

};

#endif
