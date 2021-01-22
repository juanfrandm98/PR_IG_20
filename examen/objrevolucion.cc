#include "aux.h"
#include "objrevolucion.h"
#include "ply_reader.h"


// *****************************************************************************
//
// Clase ObjRevolucion (práctica 2)
//
// *****************************************************************************


// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un PLY)

ObjRevolucion::ObjRevolucion() {}

void ObjRevolucion::CrearObjeto( std::vector<Tupla3f> perfilOriginal, int num_instancias,
                                 bool tapa_sup, bool tapa_inf, float maxgrados ) {
   // Almacenamiento (si fuera necesario) de los puntos tapa
   Tupla3f punto, puntoSup, puntoInf;
   int contador;
   const float EPSILON = 0.001;
   const float vueltacompleta = 2 * M_PI;
   const float factor_grados_a_radianes = 0.0174533;
   bool ordenAscendente = detectarOrdenAscendente( perfilOriginal );

   if ( maxgrados >= 360 )
      maxgrados = vueltacompleta;
   else if( maxgrados <= 180 )
      maxgrados = vueltacompleta / 2;
   else
      maxgrados *= factor_grados_a_radianes;


   // Almacenamos si el objeto de revolución tiene las tapas
   tiene_tapa_sup = tapa_sup;
   tiene_tapa_inf = tapa_inf;

   // Si el archivo contiene tapa superior, se quita el último punto y se guarda
   if( tapa_sup ) {
     punto = perfilOriginal[ perfilOriginal.size() - 1 ];
     if( fabs( punto(0) ) > EPSILON || fabs( punto(2) ) > EPSILON )
        puntoSup = Tupla3f( 0, punto(1), 0 );
      else {
        perfilOriginal.pop_back();
        puntoSup = punto;
      }
   }

   // Si el archivo contiene tapa inferior, se quita el primer punto y se guarda
   if( tapa_inf ) {
     //puntoInf = perfilOriginal[0];
     //perfilOriginal.erase( perfilOriginal.begin() );
     punto = perfilOriginal[0];
     if( fabs( punto(0) ) > EPSILON || fabs( punto(2) ) > EPSILON )
        puntoInf = Tupla3f( 0, punto(1), 0 );
      else {
        perfilOriginal.erase( perfilOriginal.begin() );
        puntoInf = punto;
      }
   }

   // Si el orden es descentente, hay que cambiar el orden de los puntos para
   // colocar cada tapa en su lugar
   if( !ordenAscendente ) {
     Tupla3f temp = puntoSup;
     puntoSup = puntoInf;
     puntoInf = temp;
   }

   // Ahora creamos las tablas de vértices y triángulos
   crearMalla( perfilOriginal, num_instancias, ordenAscendente, maxgrados );

   // Como hemos duplicado una instancia para utilizar bien texturas, aumentamos
   // el contador de las mismas
   num_instancias++;

   // Creamos las tablas de triángulos para el modo ajedrez
   for( int i = 0; i < f.size(); i++ )
    if( i % 2 == 0 )
      f_chess_par.push_back( f[i] );
    else
      f_chess_impar.push_back( f[i] );

   // Hasta ahora hemos creado los triángulos del cuerpo, por lo que guardamos
   // la última posición para los tres vectores
   final_cuerpo = f.size();
   final_cuerpo_pares = f_chess_par.size();
   final_cuerpo_impares = f_chess_impar.size();

   // Una vez creada la malla, si el objeto tenía tapa inferior, hay que crearla
   if( tapa_inf )
     crearTapa( false, tapa_inf, puntoInf, num_instancias, perfilOriginal.size(), ordenAscendente );

   // Guardamos la última posición de los triángulos de la tapa inferior
   final_tapa_inf = f.size();
   final_tapa_inf_pares = f_chess_par.size();
   final_tapa_inf_impares = f_chess_impar.size();

   // Lo mismo con la tapa superior
   if( tapa_sup )
    crearTapa( true, tapa_inf, puntoSup, num_instancias, perfilOriginal.size(), ordenAscendente );

   // Guardamos la última posición de los triángulos de la tapa inferior
   final_tapa_sup = f.size();
   final_tapa_sup_pares = f_chess_par.size();
   final_tapa_sup_impares = f_chess_impar.size();

   // Finalmente, colocamos los colores para que sean como los de la P1
   for( int i = 0; i < v.size(); i++ )
      c_solid.push_back( Tupla3f( 1, 0, 0 ) );

   for( int i = 0; i < v.size(); i++ )
      c_points.push_back( Tupla3f( 255, 0, 255 ) );

   for( int i = 0; i < v.size(); i++ )
      c_lines.push_back( Tupla3f( 0, 0, 0 ) );

   for( int i = 0; i < v.size(); i++ )
      c_chess_impar.push_back( Tupla3f( 1, 0, 0 ) );

   for( int i = 0; i < v.size(); i++ )
      c_chess_par.push_back( Tupla3f( 0, 1, 0 ) );

  // Calculamos las normales de los vértices
  Calcular_normales( CalcularNormalesCaras() );

  Material predefinido = Material(Tupla4f(0.5,0.4,0.4,1),Tupla4f(0.7,0.04,0.04,1),Tupla4f(0.05,0.0,0.0,1),.078125);
  setMaterial( predefinido );
}

ObjRevolucion::ObjRevolucion(const std::string & archivo, int num_instancias, bool tapa_sup, bool tapa_inf, float maxgrados ) {
   // completar ......(práctica 2)

   // En primer lugar, cargamos en perfilOriginal los vértices leídos del archivo argumento
   std::vector<Tupla3f> perfilOriginal;
   ply::read_vertices( archivo, perfilOriginal );

   CrearObjeto( perfilOriginal, num_instancias, tapa_sup, tapa_inf, maxgrados );

}

// *****************************************************************************
// objeto de revolución obtenido a partir de un perfil (en un vector de puntos)


ObjRevolucion::ObjRevolucion(std::vector<Tupla3f> archivo, int num_instancias, bool tapa_sup, bool tapa_inf, float maxgrados ) {

  CrearObjeto( archivo, num_instancias, tapa_sup, tapa_inf, maxgrados );

}

void ObjRevolucion::crearMalla(std::vector<Tupla3f> perfil_original, int num_instancias, bool ordenAscendente, float maxgrados ) {

  // Rellenamos la tabla de vértices
  for( int i = 0; i < num_instancias; i++ )
    if( ordenAscendente )
      for( int j = 0; j < perfil_original.size(); j++ )
        introducirVertice( i, perfil_original[j], num_instancias, maxgrados );
    else
      for( int j = perfil_original.size() - 1; j >= 0; j-- )
        introducirVertice( i, perfil_original[j], num_instancias, maxgrados );

  // Duplicamos el primer perfil
  if( ordenAscendente )
    for( int j = 0; j < perfil_original.size(); j++ )
      introducirVertice( 0, perfil_original[j], num_instancias, maxgrados );
  else
    for( int j = perfil_original.size() - 1; j >= 0; j-- )
      introducirVertice( 0, perfil_original[j], num_instancias, maxgrados );
  num_instancias++;

  int contador = 0;

  // Rellenamos la tabla de triángulos
  for( int i = 0; i < num_instancias; i++ )
    for( int j = 0; j < perfil_original.size() - 1; j++ ) {

      int a = perfil_original.size() * i + j;
      int b = perfil_original.size() * ( ( i + 1 ) % num_instancias ) + j;

      f.push_back( Tupla3i( a, b, b + 1 ) );
      f.push_back( Tupla3i( a, b + 1, a + 1 ) );

    }

    // Calculamos el vector de distancias
    std::vector<float> distancias = calcularVectorDistancias( perfil_original );

    // Rellenamos las coordenadas de textura
    calcularCoordenadasDeTextura( perfil_original.size(), num_instancias, distancias );

}

void ObjRevolucion::draw_cuerpo( dibujado tipoDibujado, visualizacion tipoVisualizacion ) {

  switch( tipoDibujado ) {
    case INMEDIATO:
      draw_cuerpo_inmediato( tipoVisualizacion );
      break;
    case DIFERIDO:
      draw_cuerpo_diferido( tipoVisualizacion );
      break;
  }

}

void ObjRevolucion::comprobarVBOsRevolucion() {

  if( id_vbo_f_cuerpo == 0 ) {
    std::vector<Tupla3i> cuerpo;
    for( int i = 0; i < final_cuerpo; i++ )
      cuerpo.push_back( f[i] );

    id_vbo_f_cuerpo = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * cuerpo.size() * sizeof(int), cuerpo.data() );
  }

  if( id_vbo_f_cuerpo_pares == 0 ) {
    std::vector<Tupla3i> cuerpo_pares;
    for( int i = 0; i < final_cuerpo_pares; i++ )
      cuerpo_pares.push_back( f_chess_par[i] );

    id_vbo_f_cuerpo_pares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * cuerpo_pares.size() * sizeof(int), cuerpo_pares.data() );
  }

  if( id_vbo_f_cuerpo_impares == 0 ) {
    std::vector<Tupla3i> cuerpo_impares;
    for( int i = 0; i < final_cuerpo_impares; i++ )
      cuerpo_impares.push_back( f_chess_impar[i] );

    id_vbo_f_cuerpo_impares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * cuerpo_impares.size() * sizeof(int), cuerpo_impares.data() );
  }

  if( tiene_tapa_inf ) {

    if( id_vbo_f_tapa_inf == 0 ) {
      std::vector<Tupla3i> tapainf;
      for( int i = final_cuerpo; i < final_tapa_inf; i++ )
        tapainf.push_back( f[i] );

      id_vbo_f_tapa_inf = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * tapainf.size() * sizeof(int), tapainf.data() );
    }

    if( id_vbo_f_tapa_inf_pares == 0 ) {
      std::vector<Tupla3i> tapainf_pares;
      for( int i = final_cuerpo_pares; i < final_tapa_inf_pares; i++ )
        tapainf_pares.push_back( f_chess_par[i] );

      id_vbo_f_tapa_inf_pares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * tapainf_pares.size() * sizeof(int), tapainf_pares.data() );
    }

    if( id_vbo_f_tapa_inf_impares == 0 ) {
      std::vector<Tupla3i> tapainf_impares;
      for( int i = final_cuerpo_impares; i < final_tapa_inf_impares; i++ )
        tapainf_impares.push_back( f_chess_par[i] );

      id_vbo_f_tapa_inf_impares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * tapainf_impares.size() * sizeof(int), tapainf_impares.data() );
    }
  }

  if( tiene_tapa_sup ) {

    if( id_vbo_f_tapa_sup == 0 ) {
      std::vector<Tupla3i> tapasup;
      for( int i = final_tapa_inf; i < final_tapa_sup; i++ )
        tapasup.push_back( f[i] );

      id_vbo_f_tapa_sup = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * tapasup.size() * sizeof(int), tapasup.data() );
    }

    if( id_vbo_f_tapa_sup_pares == 0 ) {
      std::vector<Tupla3i> tapasup_pares;
      for( int i = final_tapa_sup_pares; i < final_tapa_sup_pares; i++ )
        tapasup_pares.push_back( f_chess_par[i] );

      id_vbo_f_tapa_sup_pares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * tapasup_pares.size() * sizeof(int), tapasup_pares.data() );
    }

    if( id_vbo_f_tapa_sup_impares == 0 ) {
      std::vector<Tupla3i> tapasup_impares;
      for( int i = final_tapa_sup_impares; i < final_tapa_sup_impares; i++ )
        tapasup_impares.push_back( f_chess_impar[i] );

      id_vbo_f_tapa_sup_impares = CrearVBO( GL_ELEMENT_ARRAY_BUFFER, 3 * tapasup_impares.size() * sizeof(int), tapasup_impares.data() );
    }
  }

}

void ObjRevolucion::draw_cuerpo_inmediato( visualizacion tipoVisualizacion )
{

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );

  if( glIsEnabled( GL_LIGHTING ) ) {
    glEnableClientState( GL_NORMAL_ARRAY );
    glNormalPointer( GL_FLOAT, 0, nv.data() );
    m->aplicar();
  } else {
    glEnableClientState( GL_COLOR_ARRAY );
  }


  if( textura != nullptr and ct.size() != 0 ) {
    textura->activar();
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer( 2, GL_FLOAT, 0, ct.data() );
    glDisableClientState( GL_COLOR_ARRAY );
  } else {
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
  }

  switch( tipoVisualizacion ) {

    case POINTS:
      glColorPointer( 3, GL_FLOAT, 0, c_points.data() );
      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo, GL_UNSIGNED_INT, f.data() );
      break;

    case LINES:
      glColorPointer( 3, GL_FLOAT, 0, c_lines.data() );
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo, GL_UNSIGNED_INT, f.data() );
      break;

    case SOLID:
      glColorPointer( 3, GL_FLOAT, 0, c_solid.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo, GL_UNSIGNED_INT, f.data() );
      break;

    case CHESS:
      glColorPointer( 3, GL_FLOAT, 0, c_chess_impar.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo_impares, GL_UNSIGNED_INT, f_chess_impar.data() );

      glColorPointer( 3, GL_FLOAT, 0, c_chess_par.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo_pares, GL_UNSIGNED_INT, f_chess_par.data() );
      break;

  }

}

void ObjRevolucion::draw_cuerpo_diferido( visualizacion tipoVisualizacion )
{

  comprobarVBOsBasicos();
  comprobarVBOsRevolucion();

  glBindBuffer( GL_ARRAY_BUFFER, id_vbo_v ); // Activar VBO de vértices
  glVertexPointer( 3, GL_FLOAT, 0, 0 ); // Especificar formato y offset (0)
  glBindBuffer( GL_ARRAY_BUFFER, 0 );   // Desactivar VBO de vértices
  glEnableClientState( GL_VERTEX_ARRAY );  // Habilitar tabla de vértices
  glEnableClientState( GL_COLOR_ARRAY );   // Habilitar tabla de colores

  if( glIsEnabled( GL_LIGHTING ) ) {
    glEnableClientState( GL_NORMAL_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_nv );
    glNormalPointer( GL_FLOAT, 0, 0 );
    m->aplicar();
  } else {
    glEnableClientState( GL_COLOR_ARRAY );
  }

  if( textura != nullptr and ct.size() != 0 ) {
    textura->activar();
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ct );
    glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
    glDisableClientState( GL_COLOR_ARRAY );
  } else {
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
  }

  switch( tipoVisualizacion ) {

    case POINTS:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_puntos );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_cuerpo );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo, GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      break;

    case LINES:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_lineas );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_cuerpo );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo, GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      break;

    case SOLID:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_solido );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT, GL_FILL );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_cuerpo );
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo, GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      break;

    case CHESS:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_chess_impares );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT, GL_FILL );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_cuerpo_impares );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo_impares, GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_chess_pares );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT, GL_FILL );

      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_cuerpo_pares );  // Activar VBO de triángulos
      glDrawElements( GL_TRIANGLES, 3 * final_cuerpo_pares, GL_UNSIGNED_INT, 0 );
      glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );   // Desactivar VBO de triángulos
      break;

  }

}

void ObjRevolucion::draw_tapas( dibujado tipoDibujado, visualizacion tipoVisualizacion, bool superior, bool inferior ) {

  switch( tipoDibujado ) {
    case INMEDIATO:
      draw_tapas_inmediato( tipoVisualizacion, superior, inferior );
      break;
    case DIFERIDO:
      draw_tapas_diferido( tipoVisualizacion, superior, inferior );
      break;
  }

}

void ObjRevolucion::draw_tapas_inmediato( visualizacion tipoVisualizacion, bool superior, bool inferior )
{

  glEnableClientState( GL_VERTEX_ARRAY );
  glVertexPointer( 3, GL_FLOAT, 0, v.data() );

  if( glIsEnabled( GL_LIGHTING ) ) {
    glEnableClientState( GL_NORMAL_ARRAY );
    glNormalPointer( GL_FLOAT, 0, nv.data() );
    m->aplicar();
  } else {
    glEnableClientState( GL_COLOR_ARRAY );
  }


  if( textura != nullptr and ct.size() != 0 ) {
    textura->activar();
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glTexCoordPointer( 2, GL_FLOAT, 0, ct.data() );
    glDisableClientState( GL_COLOR_ARRAY );
  } else {
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
  }

  std::vector<Tupla3i> tapasup, tapainf;
  std::vector<Tupla3i> tapasup_pares, tapainf_pares;
  std::vector<Tupla3i> tapasup_impares, tapainf_impares;

  if( tipoVisualizacion == CHESS ) {
    if( tiene_tapa_inf ) {
      for( int i = final_cuerpo_pares; i < final_tapa_inf_pares; i++ )
        tapainf_pares.push_back( f_chess_par[i] );
      for( int i = final_cuerpo_impares; i < final_tapa_inf_impares; i++ )
        tapainf_impares.push_back( f_chess_impar[i] );
    }
    if( tiene_tapa_sup ) {
      for( int i = final_tapa_inf_pares; i < final_tapa_sup_pares; i++ )
        tapasup_pares.push_back( f_chess_par[i] );
      for( int i = final_tapa_inf_impares; i < final_tapa_sup_impares; i++ )
        tapasup_impares.push_back( f_chess_impar[i] );
    }
  } else {
    if( tiene_tapa_inf )
      for( int i = final_cuerpo; i < final_tapa_inf; i++ )
        tapainf.push_back( f[i] );
    if( tiene_tapa_sup )
      for( int i = final_tapa_inf; i < final_tapa_sup; i++ )
        tapasup.push_back( f[i] );
  }

  switch( tipoVisualizacion ) {

    case POINTS:
      glColorPointer( 3, GL_FLOAT, 0, c_points.data() );
      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );
      if( superior and tiene_tapa_sup )
        glDrawElements( GL_TRIANGLES, 3 * tapasup.size(), GL_UNSIGNED_INT, tapasup.data() );
      if( inferior and tiene_tapa_inf )
        glDrawElements( GL_TRIANGLES, 3 * tapainf.size(), GL_UNSIGNED_INT, tapainf.data() );
      break;

    case LINES:
      glColorPointer( 3, GL_FLOAT, 0, c_lines.data() );
      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );
      if( superior and tiene_tapa_sup )
        glDrawElements( GL_TRIANGLES, 3 * tapasup.size(), GL_UNSIGNED_INT, tapasup.data() );
      if( inferior and tiene_tapa_inf )
        glDrawElements( GL_TRIANGLES, 3 * tapainf.size(), GL_UNSIGNED_INT, tapainf.data() );
      break;

    case SOLID:
      glColorPointer( 3, GL_FLOAT, 0, c_solid.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      if( superior and tiene_tapa_sup )
        glDrawElements( GL_TRIANGLES, 3 * tapasup.size(), GL_UNSIGNED_INT, tapasup.data() );
      if( inferior and tiene_tapa_inf )
        glDrawElements( GL_TRIANGLES, 3 * tapainf.size(), GL_UNSIGNED_INT, tapainf.data() );
      break;

    case CHESS:
      glColorPointer( 3, GL_FLOAT, 0, c_chess_impar.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      if( superior and tiene_tapa_sup )
        glDrawElements( GL_TRIANGLES, 3 * tapasup_impares.size(), GL_UNSIGNED_INT, tapasup_impares.data() );
      if( inferior and tiene_tapa_inf )
        glDrawElements( GL_TRIANGLES, 3 * tapainf_impares.size(), GL_UNSIGNED_INT, tapainf_impares.data() );

      glColorPointer( 3, GL_FLOAT, 0, c_chess_par.data() );
      glPolygonMode( GL_FRONT, GL_FILL );
      if( superior and tiene_tapa_sup )
        glDrawElements( GL_TRIANGLES, 3 * tapasup_pares.size(), GL_UNSIGNED_INT, tapasup_pares.data() );
      if( inferior and tiene_tapa_inf )
        glDrawElements( GL_TRIANGLES, 3 * tapainf_pares.size(), GL_UNSIGNED_INT, tapainf_pares.data() );
      break;

  }

}

void ObjRevolucion::draw_tapas_diferido( visualizacion tipoVisualizacion, bool superior, bool inferior )
{

  comprobarVBOsBasicos();
  comprobarVBOsRevolucion();

  glBindBuffer( GL_ARRAY_BUFFER, id_vbo_v ); // Activar VBO de vértices
  glVertexPointer( 3, GL_FLOAT, 0, 0 ); // Especificar formato y offset (0)
  glBindBuffer( GL_ARRAY_BUFFER, 0 );   // Desactivar VBO de vértices
  glEnableClientState( GL_VERTEX_ARRAY );  // Habilitar tabla de vértices
  glEnableClientState( GL_COLOR_ARRAY );   // Habilitar tabla de colores

  if( glIsEnabled( GL_LIGHTING ) ) {
    glEnableClientState( GL_NORMAL_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_nv );
    glNormalPointer( GL_FLOAT, 0, 0 );
    m->aplicar();
  } else {
    glEnableClientState( GL_COLOR_ARRAY );
  }

  if( textura != nullptr and ct.size() != 0 ) {
    textura->activar();
    glEnableClientState( GL_TEXTURE_COORD_ARRAY );
    glBindBuffer( GL_ARRAY_BUFFER, id_vbo_ct );
    glTexCoordPointer( 2, GL_FLOAT, 0, 0 );
    glDisableClientState( GL_COLOR_ARRAY );
  } else {
    glDisable( GL_TEXTURE_2D );
    glDisable( GL_TEXTURE_COORD_ARRAY );
    glEnableClientState( GL_COLOR_ARRAY );
  }

  switch( tipoVisualizacion ) {

    case POINTS:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_puntos );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPointSize( 7.5 );
      glPolygonMode( GL_FRONT_AND_BACK, GL_POINT );

      if( inferior and tiene_tapa_inf ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_inf );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_inf - final_cuerpo ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }

      if( superior and tiene_tapa_sup ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_sup );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_sup - final_tapa_inf ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }
      break;

    case LINES:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_lineas );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

      if( inferior and tiene_tapa_inf ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_inf );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_inf - final_cuerpo ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }

      if( superior and tiene_tapa_sup ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_sup );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_sup - final_tapa_inf ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }
      break;

    case SOLID:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_solido );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT, GL_FILL );

      if( inferior and tiene_tapa_inf ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_inf );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_inf - final_cuerpo ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }

      if( superior and tiene_tapa_sup ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_sup );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_sup - final_tapa_inf ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }
      break;

    case CHESS:
      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_chess_impares );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT, GL_FILL );

      if( inferior and tiene_tapa_inf ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_inf_impares );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_inf_impares - final_cuerpo_impares ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }

      if( superior and tiene_tapa_sup ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_sup_impares );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_sup_impares - final_tapa_inf_impares ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }

      glBindBuffer( GL_ARRAY_BUFFER, id_vbo_c_chess_pares );
      glColorPointer( 3, GL_FLOAT, 0, 0 );
      glBindBuffer( GL_ARRAY_BUFFER, 0 );

      glPolygonMode( GL_FRONT, GL_FILL );

      if( inferior and tiene_tapa_inf ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_inf_pares );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_inf_pares - final_cuerpo_pares ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }

      if( superior and tiene_tapa_sup ) {
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, id_vbo_f_tapa_sup_impares );
        glDrawElements( GL_TRIANGLES, 3 * ( final_tapa_sup_pares - final_tapa_inf_pares ), GL_UNSIGNED_INT, 0 );
        glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
      }
      break;

  }

}

bool ObjRevolucion::detectarOrdenAscendente( std::vector<Tupla3f> perfil_original ) {

  if( perfil_original[0](1) <= perfil_original[perfil_original.size() - 1](1) )
    return true;
  else
    return false;

}

void ObjRevolucion::crearTapa( bool superior, bool hayTapaInf, Tupla3f centro, int num_instancias, int perfil_size, bool ordenAscendente ) {

  v.push_back( Tupla3f( 0, centro(1), 0 ) );
  int contador = 0;
  int index0, index1, index2;
  int diferencia;

  if( superior )
    if( hayTapaInf )
     diferencia = 2;
    else
     diferencia = 1;

  for( int i = 0; i < num_instancias; i++ ) {

    if( superior ) {
      index0 = v.size() - 1;
      index1 = perfil_size - 1 + i * perfil_size;
      index2 = ( index1 + perfil_size ) % ( v.size() - diferencia );
    } else {
      index0 = v.size() - 1;
      index1 = ( index1 + perfil_size ) % ( v.size() - 1 );
      index2 = ( i * perfil_size );
    }

    f.push_back( Tupla3i( index0, index1, index2 ) );

    if( ( contador % 2 ) == 0 )
    f_chess_par.push_back( Tupla3i( index0, index1, index2 ) );
    else
    f_chess_impar.push_back( Tupla3i( index0, index1, index2 ) );

    contador++;
  }

}

void ObjRevolucion::introducirVertice( int i, Tupla3f punto, int num_instancias, float maxgrados ) {

  float x, y, z;
  float radio = sqrt( punto(0) * punto(0) + punto(2) * punto(2) );

  x = cos( maxgrados * i / num_instancias ) * radio;
  y = punto(1);
  z = -( sin( maxgrados * i / num_instancias ) * radio );

  v.push_back( Tupla3f( x, y, z ) );

}

void ObjRevolucion::calcularCoordenadasDeTextura( int num_puntos_perfil, int num_perfiles, std::vector<float> distancias ) {

  while( !ct.empty() )
    ct.pop_back();

  for( int i = 0; i < num_perfiles; i++ )
    for( int j = 0; j < distancias.size(); j++ ) {

      float s = i / ( (float)num_perfiles - 1 );
      float t = distancias[j] / distancias[num_puntos_perfil - 1];

      // Como la Y de la textura está al revés de la de la imagen leída,
      t = 1 - t;

      ct.push_back( {s, t} );


    }

}

std::vector<float> ObjRevolucion::calcularVectorDistancias( std::vector<Tupla3f> perfil_original ) {

  std::vector<float> distancias;

  distancias.push_back(0);

  for( int j = 1; j < perfil_original.size(); j++ )
    distancias.push_back( distancias[j-1] + abs(perfil_original[j](1) - perfil_original[j-1](1)) );

  return distancias;

}
