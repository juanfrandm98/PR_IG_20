// #############################################################################
//
// Informática Gráfica (Grado Informática)
//
// Archivo: Cubo.h

//
// #############################################################################

#ifndef OBJREVOLUCION_H_INCLUDED
#define OBJREVOLUCION_H_INCLUDED

#include "aux.h"
#include "malla.h"

// *****************************************************************************
//
// clases derivadas de Malla3D (definen constructores específicos)
//
// *****************************************************************************

// *****************************************************************************
// Cubo con centro en el origen y lado unidad por defecto
// (tiene 9 vertices y 6 caras)

#define M_PI 3.14159265358979323846

class ObjRevolucion : public Malla3D
{
   public:
     ObjRevolucion();
     ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;
     ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup=true, bool tapa_inf=true) ;

     // Funciones para cambiar el dibujado de las tapas en tiempo de ejecución
     void draw_cuerpo( dibujado tipoDibujado, visualizacion tipoVisualizacion );
     void draw_tapas( dibujado tipoDibujado, visualizacion tipoVisualizacion, bool superior, bool inferior );

   private:
     void comprobarVBOsRevolucion();
     void draw_cuerpo_inmediato( visualizacion tipoVisualizacion );
     void draw_cuerpo_diferido( visualizacion tipoVisualizacion );
     void draw_tapas_inmediato( visualizacion tipoVisualizacion, bool superior, bool inferior );
     void draw_tapas_diferido( visualizacion tipoVisualizacion, bool superior, bool inferior );
     void calcularCoordenadasDeTextura( int num_puntos_perfil, int num_perfiles, std::vector<float> distancias );
     std::vector<float> calcularVectorDistancias( std::vector<Tupla3f> vector_original );
     void crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool ordenAscendente);
     bool detectarOrdenAscendente( std::vector<Tupla3f> perfil_original );
     void crearTapa( bool superior, bool hayTapaInf, Tupla3f centro, int num_instancias, int perfil_size, bool ordenAscendente );
     void introducirVertice( int i, Tupla3f punto, int num_instancias );

     // Variables para cambiar el dibujado de las tapas en tiempo de ejecución
     bool tiene_tapa_sup;
     bool tiene_tapa_inf;
     int final_cuerpo;
     int final_tapa_sup;
     int final_tapa_inf;
     int final_cuerpo_pares;
     int final_tapa_sup_pares;
     int final_tapa_inf_pares;
     int final_cuerpo_impares;
     int final_tapa_sup_impares;
     int final_tapa_inf_impares;

     GLuint id_vbo_f_cuerpo = 0;
     GLuint id_vbo_f_tapa_sup = 0;
     GLuint id_vbo_f_tapa_inf = 0;

     GLuint id_vbo_f_cuerpo_pares = 0;
     GLuint id_vbo_f_tapa_sup_pares = 0;
     GLuint id_vbo_f_tapa_inf_pares = 0;

     GLuint id_vbo_f_cuerpo_impares = 0;
     GLuint id_vbo_f_tapa_sup_impares = 0;
     GLuint id_vbo_f_tapa_inf_impares = 0;

   protected:
      void CrearObjeto( std::vector<Tupla3f> perfilOriginal, int num_instancias,
                        bool tapa_sup, bool tapa_inf );
} ;




#endif
