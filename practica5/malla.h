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
#include "material.h"
#include "textura.h"

// *****************************************************************************
//
// clase para objetos 3D (mallas indexadas)
//
// *****************************************************************************

typedef enum {POINTS, LINES, SOLID, CHESS} visualizacion;
typedef enum {DIFERIDO, INMEDIATO} dibujado;

#define M_PI 3.14159265358979323846

class Malla3D
{

   private:
   void calcularCoordenadasDeTextura();

   public:

   // dibuja el objeto en modo inmediato
   void draw_ModoInmediato( visualizacion tipoVisualizacion );

   // dibuja el objeto en modo diferido (usando VBOs)
   void draw_ModoDiferido( visualizacion tipoVisualizacion );

   // función que redibuja el objeto
   // está función llama a 'draw_ModoInmediato' (modo inmediato)
   // o bien a 'draw_ModoDiferido' (modo diferido, VBOs)
   void draw( dibujado tipoDibujado, visualizacion tipoVisualizacion ) ;
   void drawLight();

   // Función para asignar un material
   void setMaterial( Material mat );

   // Función para cambiar el color sólido de un objeto
   void setColorSolido( Tupla3f nuevoColor );

   // Función para asignar una textura
   void setTextura( Textura tex );

   protected:

   float calcularYMax();
   float calcularYMin();

   void calcular_normales() ; // calcula tabla de normales de vértices (práctica 3)
   GLuint CrearVBO( GLuint tipo_vbo, GLuint tamanio_bytes, GLvoid * puntero_ram );
   void comprobarVBOsBasicos();

   std::vector<Tupla3f> v ;   // tabla de coordenadas de vértices (una tupla por vértice, con tres floats)
   std::vector<Tupla3i> f ; // una terna de 3 enteros por cada cara o triángulo
   std::vector<Tupla3i> f_chess_impar;  // vector de triangulos para el modo ajedrez (pares)
   std::vector<Tupla3i> f_chess_par;    // vector de triangulos para el modo ajedrez (impares)
   std::vector<Tupla3f> c_points ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_lines ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_solid ; // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_chess_impar;  // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> c_chess_par;  // una terna de 3 floats por cada vértice (color)
   std::vector<Tupla3f> nv;     // Normales de los vértices
   std::vector<Tupla2f> ct;     // Coordenadas de textura

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
   GLuint id_vbo_nv = 0;
   GLuint id_vbo_ct = 0;

   Material * m = nullptr;  // Material
   Textura * textura = nullptr; // Textura

   // Función que devuelve la tabla de normales de las caras, que se utilizará
   // para el cálculo de las normales de los vértices
   std::vector<Tupla3f> CalcularNormalesCaras();

   // Función que calcula la tabla de normales de vértices
   void Calcular_normales( std::vector<Tupla3f> normalesCaras ) ;

   // completar: tabla de colores, tabla de normales de vértices
} ;


#endif
