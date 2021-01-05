#ifndef TRACTORREMOLQUE_H_INCLUDED
#define TRACTORREMOLQUE_H_INCLUDED

#include "modelojerarquico.h"
#include "tractor.h"
#include "remolque.h"

class TractorRemolque : public ModeloJerarquico {

private:
  Tractor * tractor   = nullptr;
  Remolque * remolque = nullptr;

public:
  TractorRemolque();
  void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion );
  // Funciones para la animación
  void cambiarAnguloGiro( float angulo );
  void simularAvance( float angulo );
  bool ruedasAlTope();
  void inclinarRemolque( float angulo );
  void girarRemolque( float angulo );
  bool inclinacionAlTope();
  bool remolqueGiradoAlTope();
  void trasladarRodillo( float cantidad );
  bool rodilloTrasladadoAlTope();

};

#endif
