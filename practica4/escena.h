#ifndef _ESCENA_H
#define _ESCENA_H

#include "ejes.h"
#include "malla.h"
#include "cubo.h"
#include "tetraedro.h"
#include "objply.h"
#include "objrevolucion.h"
#include "cilindro.h"
#include "cono.h"
#include "esfera.h"
#include "luz.h"
#include "luzdireccional.h"
#include "luzposicional.h"
#include "material.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,TAPAS,ILUMINACION} menu;
typedef enum {BASICA, SUAVE, PLANA} iluminacion;
typedef enum {VARALPHA, VARBETA} variacion;

struct Modelo {
  Malla3D * objeto;
  bool dibujar;
  Tupla3f posicion;
  Tupla3f orientacion;
  Tupla3f escalado;
};

struct ModeloTapas {
  ObjRevolucion * objeto;
  bool dibujar;
  Tupla3f posicion;
  Tupla3f orientacion;
  Tupla3f escalado;
};

class Escena
{

   private:

   // Función que manda dibujar a todos los objetos de la escena de una
   // determinada manera (ajedrez, sólidos, líneas o puntos)
   void DrawMode( visualizacion tipo );

 // ** PARÁMETROS DE LA CÁMARA (PROVISIONAL)

       // variables que definen la posicion de la camara en coordenadas polares
   GLfloat Observer_distance;
   GLfloat Observer_angle_x;
   GLfloat Observer_angle_y;

   // variables que controlan la ventana y la transformacion de perspectiva
   GLfloat Width, Height, Front_plane, Back_plane;

    // Transformación de cámara
	void change_projection( const float ratio_xy );
	void change_observer();



   void clear_window();

   menu modoMenu=NADA;
   // Objetos de la escena
   Ejes ejes;
   std::vector<Modelo> objetosEscena;
   std::vector<ModeloTapas> objetosEscenaConTapas;

   // FLAGS para el dibujado
   bool puntos;
   bool lineas;
   bool solido;
   bool ajedrez;
   dibujado modoDibujado;
   bool tapa_superior;
   bool tapa_inferior;
   iluminacion modoIluminacion;
   variacion variacionLuz;

   // Luces
   LuzPosicional * luzPos1 = nullptr;
   LuzPosicional * luzPos2 = nullptr;
   LuzDireccional * luzDir = nullptr;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

};
#endif
