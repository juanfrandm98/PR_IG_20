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

class Malla3D
{
   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato( bool puntos, bool lineas, bool solido, bool ajedrez );

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido( bool puntos, bool lineas, bool solido, bool ajedrez );

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw( bool puntos, bool lineas, bool solido, bool ajedrez ) ;

   protected:

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3f> c_points ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_lines ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_solid ; // una terna de 3 floats por cada vértice (color)

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
