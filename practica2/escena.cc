

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....

//**************************************************************************
// constructor de la escena (no puede usar ordenes de OpenGL)
//**************************************************************************

Escena::Escena()
{
    Front_plane       = 50.0;
    Back_plane        = 2000.0;
    Observer_distance = 4*Front_plane;
    Observer_angle_x  = 0.0 ;
    Observer_angle_y  = 0.0 ;

    ejes.changeAxisSize( 5000 );

    //objetoVisible = CUBO;

    // crear los objetos de la escena....
    // .......completar: ...
    // .....

    cubo = new Cubo( 100 );
    tetraedro = new Tetraedro( 100 );
    cilindro = new Cilindro( 1, 10, 100, 25);
    esfera = new Esfera( 10, 10, 100 );

    puntos = false;
    lineas = false;
    solido = true;
    ajedrez = false;
    modoDibujado = INMEDIATO;

}

//**************************************************************************
// inicialización de la escena (se ejecuta cuando ya se ha creado la ventana, por
// tanto sí puede ejecutar ordenes de OpenGL)
// Principalmemnte, inicializa OpenGL y la transf. de vista y proyección
//**************************************************************************

void Escena::inicializar( int UI_window_width, int UI_window_height )
{
	glClearColor( 1.0, 1.0, 1.0, 1.0 );// se indica cual sera el color para limpiar la ventana	(r,v,a,al)

	glEnable( GL_DEPTH_TEST );	// se habilita el z-bufer
  glEnable( GL_CULL_FACE );   // se habilita el cull-face

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

  change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  ejes.draw();

  /*
  // VISUALIZACIÓN UNO A UNO P1
  switch( objeto ) {
    case CUBO:
      if( ajedrez )
        cubo->draw( modoDibujado, CHESS );
      else {
        if( puntos )
          cubo->draw( modoDibujado, POINTS );
        if( lineas )
          cubo->draw( modoDibujado, LINES );
        if( solido )
          cubo->draw( modoDibujado, SOLID );
      }
      break;
    case TETRAEDRO:
      if( ajedrez )
        tetraedro->draw( modoDibujado, CHESS );
      else {
        if( puntos )
          tetraedro->draw( modoDibujado, POINTS );
        if( lineas )
          tetraedro->draw( modoDibujado, LINES );
        if( solido )
          tetraedro->draw( modoDibujado, SOLID );
      }
      break;
    case PLY:
      if( ajedrez )
        objetoPLY->draw( modoDibujado, CHESS );
      else {
        if( puntos )
          objetoPLY->draw( modoDibujado, POINTS );
        if( lineas )
          objetoPLY->draw( modoDibujado, LINES );
        if( solido )
          objetoPLY->draw( modoDibujado, SOLID );
      }
      break;
  }*/

  /*
  // VISUALIZACIÓN TODOS A LA VEZ P1
  if( ajedrez ) {
    glPushMatrix();
      glTranslatef( -200, 0, 0 );
      cubo->draw( modoDibujado, CHESS );
    glPopMatrix();
    glPushMatrix();
      glTranslatef( 200, 0, 0 );
      tetraedro->draw( modoDibujado, CHESS );
    glPopMatrix();
  } else {
    if( puntos ) {
      glPushMatrix();
        glTranslatef( -200, 0, 0 );
        cubo->draw( modoDibujado, POINTS );
      glPopMatrix();
      glPushMatrix();
        glTranslatef( 200, 0, 0 );
        tetraedro->draw( modoDibujado, POINTS );
      glPopMatrix();
    }

    if( lineas ) {
      glPushMatrix();
        glTranslatef( -200, 0, 0 );
        cubo->draw( modoDibujado, LINES );
      glPopMatrix();
      glPushMatrix();
        glTranslatef( 200, 0, 0 );
        tetraedro->draw( modoDibujado, LINES );
      glPopMatrix();
    }

    if( solido ) {
      glPushMatrix();
        glTranslatef( -200, 0, 0 );
        cubo->draw( modoDibujado, SOLID );
      glPopMatrix();
      glPushMatrix();
        glTranslatef( 200, 0, 0 );
        tetraedro->draw( modoDibujado, SOLID );
      glPopMatrix();
    }
  }*/
  if( objeto == PLY ) {
    if( ajedrez ) {
      glPushMatrix();
        glScalef( 10, 10, 10 );
        objetoPLY->draw( modoDibujado, CHESS );
      glPopMatrix();
    } else {
      if( puntos ) {
        glPushMatrix();
          glScalef( 10, 10, 10 );
          objetoPLY->draw( modoDibujado, POINTS );
        glPopMatrix();
      }

      if( lineas ) {
        glPushMatrix();
          glScalef( 10, 10, 10 );
          objetoPLY->draw( modoDibujado, LINES );
        glPopMatrix();
      }

      if( solido ) {
        glPushMatrix();
          glScalef( 10, 10, 10 );
          objetoPLY->draw( modoDibujado, SOLID );
        glPopMatrix();
      }
    }
  }

  if( objeto == REVOLUCION ) {
    if( ajedrez ) {
      glPushMatrix();
        glScalef( 50, 50, 50 );
        objetoRevolucion->draw( modoDibujado, CHESS );
      glPopMatrix();
    } else {
      if( puntos ) {
        glPushMatrix();
          glScalef( 50, 50, 50 );
          objetoRevolucion->draw( modoDibujado, POINTS );
        glPopMatrix();
      }

      if( lineas ) {
        glPushMatrix();
          glScalef( 50, 50, 50 );
          objetoRevolucion->draw( modoDibujado, LINES );
        glPopMatrix();
      }

      if( solido ) {
        glPushMatrix();
          glScalef( 50, 50, 50 );
          objetoRevolucion->draw( modoDibujado, SOLID );
        glPopMatrix();
      }
    }
  }

  if( objeto == CILINDRO ) {
    if( ajedrez )
      cilindro->draw( modoDibujado, CHESS );
    else {
      if( puntos )
        cilindro->draw( modoDibujado, POINTS );
      if( lineas )
        cilindro->draw( modoDibujado, LINES );
      if( solido )
        cilindro->draw( modoDibujado, SOLID );
    }
  }

  if( objeto == ESFERA ) {
    if( ajedrez )
      esfera->draw( modoDibujado, CHESS );
    else {
      if( puntos )
        esfera->draw( modoDibujado, POINTS );
      if( lineas )
        esfera->draw( modoDibujado, LINES );
      if( solido )
        esfera->draw( modoDibujado, SOLID );
    }
  }

}

//**************************************************************************
//
// función que se invoca cuando se pulsa una tecla
// Devuelve true si se ha pulsado la tecla para terminar el programa (Q),
// devuelve false en otro caso.
//
//**************************************************************************

bool Escena::teclaPulsada( unsigned char tecla, int x, int y )
{
  using namespace std ;
  cout << "Tecla pulsada: '" << tecla << "'" << endl;
  bool salir=false;

  switch( modoMenu ) {

    case NADA:

      switch( toupper( tecla ) ) {
        case 'Q':
          salir = true;
          break;
        case 'O' :
          modoMenu=SELOBJETO;
          break ;
        case 'V' :
          modoMenu=SELVISUALIZACION;
          break ;
        case 'D' :
          modoMenu=SELDIBUJADO;
          break ;
        default:
          cout << "ERROR - opciones disponibles:\n'Q': Salir\n'O': Cambiar objeto\n"
               << "'V': Cambiar modo de visualización\n'D': Cambiar modo de dibujado\n";
          break;
      }

      break;

    case SELOBJETO:

      switch( toupper( tecla ) ) {
        case 'Q':
          modoMenu = NADA;
          break;
        case 'C':
          objeto = CUBO;
          modoMenu = NADA;
          break;
        case 'T':
          objeto = TETRAEDRO;
          modoMenu = NADA;
          break;
        case 'P':

          cout << "Introduzca la ruta del archivo PLY: ";

          char nombreArchivoPLY[100];

          scanf( "%[^\n]", nombreArchivoPLY );
          while( ( getchar() ) != '\n');

          objetoPLY = new ObjPLY( nombreArchivoPLY );

          objeto = PLY;
          modoMenu = NADA;
          cout << endl;
          break;
        case 'R':

          cout << "Introduzca la ruta del archivo PLY: ";

          char nombreArchivoRev[100];
          scanf( "%[^\n]", nombreArchivoRev );
          while( ( getchar() ) != '\n');

          cout << "\nIntroduzca el número de instancias: ";

          int num_instancias;
          scanf( "%d", &num_instancias );
          while( ( getchar() ) != '\n');

          char eleccion;
          bool tapa_sup, tapa_inf;

          do {
            cout << "\n¿Tiene tapa superior (S - Sí, N - No)? ";
            eleccion = getchar();
            cout << "Eleccion " << eleccion;
            while( ( getchar() ) != '\n');
          } while( toupper( eleccion ) != 'S' && toupper( eleccion ) != 'N' );

          if( toupper( eleccion ) == 'S' )
            tapa_sup = true;
          else
            tapa_sup = false;

          do {
            cout << "\n¿Y tapa inferior (S - Sí, N - No)? ";
            eleccion = getchar();
            while( ( getchar() ) != '\n');
          } while( toupper( eleccion ) != 'S' && toupper( eleccion ) != 'N' );

          if( toupper( eleccion ) == 'S' )
            tapa_inf = true;
          else
            tapa_inf = false;

          objetoRevolucion = new ObjRevolucion( nombreArchivoRev, num_instancias, tapa_sup, tapa_inf );

          objeto = REVOLUCION;
          modoMenu = NADA;
          cout << endl;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'C': Cubo\n'T': Tetraedro\n"
               << "'P': Objeto PLY\n'R': Objeto Revolución";
          break;
      }

      break;

    case SELVISUALIZACION:

      switch( toupper( tecla ) ) {
        case 'Q':
          modoMenu = NADA;
          break;
        case 'P':
          if( puntos )
            puntos = false;
          else
            puntos = true;
          break;
        case 'L':
          if( lineas )
            lineas = false;
          else
            lineas = true;
          break;
        case 'S':
          if( solido )
            solido = false;
          else
            solido = true;
          break;
        case 'A':
          if( ajedrez )
            ajedrez = false;
          else
            ajedrez = true;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'L': Línea\n'P': Puntos\n'S': Sólido\n'A': Ajedrez\n";
          break;
      }

      break;

    case SELDIBUJADO:

      switch( toupper( tecla ) ) {
        case 'Q':
          modoMenu = NADA;
          break;
        case 'I':
          modoMenu = NADA;
          modoDibujado = INMEDIATO;
          break;
        case 'D':
          modoMenu = NADA;
          modoDibujado = DIFERIDO;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'I': Modo Inmediato\n'D': Modo Diferido\n";
          break;
      }

      break;

    default:
      cout << "ERROR EN EL MENU\n";
      modoMenu = NADA;
      break;
  }

  if( !salir ) {
    switch( modoMenu ) {
      case NADA: cout << "\nMenú Principal.\n"; break;
      case SELOBJETO: cout << "\nMenú de selección de objeto.\n"; break;
      case SELVISUALIZACION: cout << "\nMenú de visualización.\n"; break;
      case SELDIBUJADO: cout << "\nMenú de dibujado.\n"; break;
    }
  }

  return salir;
}
//**************************************************************************

void Escena::teclaEspecial( int Tecla1, int x, int y )
{
   switch ( Tecla1 )
   {
	   case GLUT_KEY_LEFT:
         Observer_angle_y-- ;
         break;
	   case GLUT_KEY_RIGHT:
         Observer_angle_y++ ;
         break;
	   case GLUT_KEY_UP:
         Observer_angle_x-- ;
         break;
	   case GLUT_KEY_DOWN:
         Observer_angle_x++ ;
         break;
	   case GLUT_KEY_PAGE_UP:
         Observer_distance *=1.2 ;
         break;
	   case GLUT_KEY_PAGE_DOWN:
         Observer_distance /= 1.2 ;
         break;
	}

	//std::cout << Observer_distance << std::endl;
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection( const float ratio_xy )
{
   glMatrixMode( GL_PROJECTION );
   glLoadIdentity();
   const float wx = float(Height)*ratio_xy ;
   glFrustum( -wx, wx, -Height, Height, Front_plane, Back_plane );
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;
   change_projection( float(newHeight)/float(newWidth) );
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
   glTranslatef( 0.0, 0.0, -Observer_distance );
   glRotatef( Observer_angle_y, 0.0 ,1.0, 0.0 );
   glRotatef( Observer_angle_x, 1.0, 0.0, 0.0 );
}
