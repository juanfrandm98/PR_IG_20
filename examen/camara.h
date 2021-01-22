#ifndef CAMARA_H_INCLUDED
#define CAMARA_H_INCLUDED

#include "aux.h"

typedef enum {PERSPECTIVA, ORTOGONAL} tipoCamara;
typedef enum {ROTX,ROTY,ROTZ} ejeRotacion;
typedef enum {ALANTE,ATRAS,IZDA,DCHA,ARRIBA,ABAJO} direccionMovimiento;
#define FACTOR_GRAD_RAD 0.0174533

class Camara {

private:

  // Parámetros extrínsecos
  Tupla3f eye;  // Posición de la cámara
  Tupla3f at;   // Punto al que mira la cámara
  Tupla3f up;   // Vector perpendicular a la dirección de visualización

  // Parámetros intrínsecos
  tipoCamara tipo;     // Tipo de proyección (ortogonal o perspectiva)
  bool objetoSeleccionado;  // Si la cámara tiene un objeto seleccionado o no
  float left;   // Distancia del centro del primer plano a la izquierda del mismo
  float right;  // Distancia del centro del primer plano a la derecha del mismo
  float top;    // Distancia del centro del primer plano a la parte superior del mismo
  float bottom; // Distancia del centro del primer plano a la parte inferior del mismo
  float near;   // Distancia del observador al plano más cercano (no se ve nada más cerca de near)
  float far;    // Distancia del observador al plano más lejano (no se ve nada más lejos de far)

  // Parámetros para regular el zoom
  const float factorZoomIn  = 0.9;
  const float factorZoomOut = 1.1;

  void zoom( float factor );

  Tupla3f calcularDireccion();
  Tupla3f rotarDireccion( Tupla3f direccionOrignial, float angulo );

  void rotarXExaminar( float angle );
  void rotarYExaminar( float angle );
  void rotarZExaminar( float angle );

  void rotarXFirstPerson( float angle );
  void rotarYFirstPerson( float angle );
  void rotarZFirstPerson( float angle );

public:

  Camara( Tupla3f e, Tupla3f a, Tupla3f u, tipoCamara ti, float l, float r,
          float t, float b, float n, float f );

  void setAt( Tupla3f nat );
  void setLeft( float nleft );
  void setRight( float nright );
  void setTop( float ntop );
  void setBottom( float nbottom );
  void setObjetoSeleccionado( bool seleccionado );

  void rotarCamara( ejeRotacion eje, float angle );

  void mover( direccionMovimiento dir );
  void girar( int x, int y );

  void zoomIn();
  void zoomOut();

  void setObservador();
  void setProyeccion();

  void moveAtandEyeX( float cantidad );

};

#endif
