// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Malla3D.h
// -- declaraciones de clase Malla3D (mallas indexadas) y derivados
//
// #############################################################################

#ifndef MALLA3D_H_INCLUDED
#define MALLA3D_H_INCLUDED

#include "aux.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {POINTS, LINES, SOLID, CHESS} visualizacion;
typedef enum {DIFERIDO, INMEDIATO} dibujado;

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato( visualizacion tipoVisualizacion );

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido( visualizacion tipoVisualizacion );

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) ;

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_chess_impar;  // vector de triangulos para el modo ajedrez (pares)
   std::vector<Tupla3i> f_chess_par;    // vector de triangulos para el modo ajedrez (impares)
   std::vector<Tupla3f> c_points ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_lines ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_solid ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_chess_impar;  // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_chess_par;  // una terna de 3 floats por cada vértice (color)

   // Identificadores de tablas VBO
   GLuint id_vbo_v = 0;
   GLuint id_vbo_f = 0;
   GLuint id_vbo_f_impares = 0;
   GLuint id_vbo_f_pares = 0;
   GLuint id_vbo_c_puntos = 0;
   GLuint id_vbo_c_lineas = 0;
   GLuint id_vbo_c_solido = 0;
   GLuint id_vbo_c_chess_impares = 0;
   GLuint id_vbo_c_chess_pares = 0;

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
