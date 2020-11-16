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
typedef enum {NINGUNO, P1, PLY, REVOLUCION, CILINDRO, TODASREV, ESFERA, CONO, P3} objetoVisible;
typedef enum {BASICA, SUAVE, PLANA} iluminacion;

class Escena
{

   private:



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
   objetoVisible objeto = CILINDRO;
   // Objetos de la escena
   Ejes ejes;
   Cubo * cubo = nullptr ; // es importante inicializarlo a 'nullptr'
   Tetraedro * tetraedro = nullptr ; // es importante inicializarlo a 'nullptr'
   ObjPLY * objetoPLY = nullptr;
   ObjRevolucion * objetoRevolucion = nullptr;
   Cilindro * cilindro = nullptr;
   Cono * cono = nullptr;
   Esfera * esfera = nullptr;
   ObjRevolucion * peonBlanco = nullptr;
   ObjRevolucion * peonNegro = nullptr;
   Cubo * lingote = nullptr;

   // FLAGS para el dibujado
   bool puntos;
   bool lineas;
   bool solido;
   bool ajedrez;
   dibujado modoDibujado;
   bool tapa_superior;
   bool tapa_inferior;
   iluminacion modoIluminacion;

   // Luces
   Luz * luzPos1 = nullptr;
   Luz * luzPos2 = nullptr;
   Luz * luzDir = nullptr;

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
