#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {PERSPECTIVA, ORTOGONAL} tipoCamara;

class Camara {

private:

  // Parámetros extrínsecos
  Tupla3f eye;  // Posición de la cámara
  Tupla3f at;   // Punto al que mira la cámara
  Tupla3f up;   // Vector perpendicular a la dirección de visualización

  // Parámetros intrínsecos
  tipoCamara tipo;     // Tipo de proyección (ortogonal o perspectiva)
  float left;   // Distancia del centro del primer plano a la izquierda del mismo
  float right;  // Distancia del centro del primer plano a la derecha del mismo
  float top;    // Distancia del centro del primer plano a la parte superior del mismo
  float bottom; // Distancia del centro del primer plano a la parte inferior del mismo
  float near;   // Distancia del observador al plano más cercano (no se ve nada más cerca de near)
  float far;    // Distancia del observador al plano más lejano (no se ve nada más lejos de far)

public:

  Camara( Tupla3f e, Tupla3f a, Tupla3f u, tipoCamara ti, float l, float r,
          float t, float b, float n, float f );

  void setLeft( float nleft );
  void setRight( float nright );
  void setTop( float ntop );
  void setBottom( float nbottom );

  void rotarXExaminar( float angle );
  void rotarYExaminar( float angle );
  void rotarZExaminar( float angle );

  void rotarXFirstPerson( float angle );
  void rotarYFirstPerson( float angle );
  void rotarZFirstPerson( float angle );

  void mover( float x, float y, float z );

  void zoom( float factor );

  void setObservador();
  void setProyeccion();

};

#endif
