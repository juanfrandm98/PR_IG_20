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
#include "modelojerarquico.h"
#include "tractorremolque.h"
#include "pino.h"
#include "camara.h"

typedef enum {NADA, SELOBJETO,SELVISUALIZACION,SELDIBUJADO,TAPAS,ILUMINACION,ANIMACIONAUTO,ANIMACIONMANUAL,COLORLUZ} menu;
typedef enum {BASICA, SUAVE, PLANA} iluminacion;
typedef enum {VARALPHA, VARBETA} variacion;
typedef enum {TODOS, ROTARRUEDAS, GIRARRUEDASDEL, INCLINARREMOLQUE, GIRARREMOLQUE, TRASLADARRODILLO} gradosTractor;
typedef enum {PULSADO, SUELTO} estadoBoton;

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

struct Jerarquico {
  ModeloJerarquico * objeto;
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

   // Función que anima el tractor en función del grado y del sentido
   // seleccionado
   void animarGradoTractor( gradosTractor gradoSeleccionado, float sentido );

   // Función que cambia la velocidad de la animación
   void cambiarVelocidadAnimacion( gradosTractor grado, bool incrementar );

   // Función que comprueba que todas las velocidades están en el rango correcto
   void comprobarVelocidadesEnRango();

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
   std::vector<Jerarquico> modelosJerarquicos;
   TractorRemolque * tractor = nullptr;
   Cubo * suelo = nullptr;

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
   bool animacionAutomatica;
   gradosTractor gradoSeleccionado;
   std::vector<float> velocidades;
   const float minVelocidad = 0.01;
   const float maxVelocidad = 0.1;
   bool sumandoGiroRuedas;
   bool sumandoGiroRemolque;
   bool sumandoInclinacion;
   float timerInclinacionRemolque;
   bool sumandoMovimientoRodillo;
   bool texturas;

   // Luces
   LuzPosicional * luzPos1 = nullptr;
   LuzPosicional * luzPos2 = nullptr;
   LuzDireccional * luzDir = nullptr;

   // Camaras
   std::vector<Camara *> camaras;
   int camaraActiva;

   // Botones del ratón
   estadoBoton botonIzq;
   estadoBoton botonDer;

   public:

    Escena();
	void inicializar( int UI_window_width, int UI_window_height );
	void redimensionar( int newWidth, int newHeight ) ;

	// Dibujar
	void dibujar() ;

	// Interacción con la escena
	bool teclaPulsada( unsigned char Tecla1, int x, int y ) ;
	void teclaEspecial( int Tecla1, int x, int y );

  // Función que anima el tractor de forma automática
  void animarModeloJerarquico();

  // Funciones que gestionan las cámaras en función de la utilización del ratón
  void clickRaton( int boton, int estado, int x, int y );
  void ratonMovido( int x, int y );

};
#endif