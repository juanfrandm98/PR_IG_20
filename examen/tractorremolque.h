#ifndef TRACTORREMOLQUE_H_INCLUDED
#define TRACTORREMOLQUE_H_INCLUDED

#include "modelojerarquico.h"
#include "tractor.h"
#include "remolque.h"
#include "objrevolucion.h"

class TractorRemolque : public ModeloJerarquico {

private:
  Tractor * tractor   = nullptr;
  Remolque * remolque = nullptr;
  ObjRevolucion * marcador = nullptr;

  Tupla3f pos = Tupla3f( 300, 17.5, 0 );

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
  void setColorSeleccion( Tupla3f color );
  void setMaterialSeleccion( Material mat );
  Tupla3f getCentro();
  Tupla3f getPos();
  void retrocederX( float cantidad );

};

#endif
