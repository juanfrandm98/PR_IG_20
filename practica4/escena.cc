

#include "aux.h"     // includes de OpenGL/glut/glew, windows, y librería std de C++
#include "escena.h"
#include "malla.h" // objetos: Cubo y otros....
#include "luz.h"  // luces: posicional y direccional
#include "material.h"

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

    // Creación de los materiales
    Material obsidiana = Material(Tupla4f(0.18275,0.17,0.22525,1),Tupla4f(0.332741,0.328634,0.346435,1),Tupla4f(0.05375,0.05,0.06625,1),0.3);
    Material yeso = Material(Tupla4f( 	1,0.829,0.829,1),Tupla4f(0.296648,0.296648,0.296648,1),Tupla4f(0.25,0.20725,0.20725,1),0.088);
    Material oro = Material(Tupla4f(0.75164,0.60648,0.22648,1),Tupla4f(0.628281,0.555802,0.366065,1),Tupla4f(0.24725,0.1995,0.0745,1),0.4);
    Material predefinido = Material(Tupla4f(0.5,0.4,0.4,1),Tupla4f(0.7,0.04,0.04,1),Tupla4f(0.05,0.0,0.0,1),.078125);

    // Creación de las luces
    // Luz direccional inicial
    luzDir = new LuzDireccional( Tupla2f( 0.0, 0.0 ), GL_LIGHT1, Tupla4f( 0.9, 0.9, 0.9, 1 ),
                                 Tupla4f( 1, 1, 1, 1 ), Tupla4f( 0.9, 0.9, 0.9, 1 ) );
    // Luz posicional blanca
    luzPos1 = new LuzPosicional( Tupla3f( 0, 200, 0 ), GL_LIGHT2, Tupla4f( 0.9, 0.9, 0.9, 1 ),
                                 Tupla4f( 1, 1, 1, 1 ), Tupla4f( 0.9, 0.9, 0.9, 1 ) );
    // Luz posicional roja
    luzPos2 = new LuzPosicional( Tupla3f( 0, 100, 0 ), GL_LIGHT3, Tupla4f( 0.9, 0, 0, 1 ),
                                 Tupla4f( 1, 0, 0, 1 ), Tupla4f( 0.9, 0, 0, 1 ) );

    // Creación de los objetos de la escena
    // Cubo=objetosEscena(0)
    Modelo objeto0;
    objeto0.objeto = new Cubo( 100 );
    objeto0.dibujar = false;
    objeto0.posicion = Tupla3f( -250.0, 0.0, -150.0 );
    objeto0.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    objeto0.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    objeto0.objeto->setMaterial( predefinido );
    objetosEscena.push_back( objeto0 );

    // Tetraedro=objetosEscena(1)
    Modelo objeto1;
    objeto1.objeto = new Tetraedro( 100 );
    objeto1.dibujar = false;
    objeto1.posicion = Tupla3f( -100.0, 0.0, -150.0 );
    objeto1.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    objeto1.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    objeto1.objeto->setMaterial( predefinido );
    objetosEscena.push_back( objeto1 );

    // Lingote=objetosEscena(2)
    Modelo objeto2;
    objeto2.objeto = new Cubo( 35 );
    objeto2.dibujar = false;
    objeto2.posicion = Tupla3f( 0.0, 0.0, 0.0 );
    objeto2.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    objeto2.escalado = Tupla3f( 1.0, 0.35, 2.0 );
    objeto2.objeto->setMaterial( oro );
    objetosEscena.push_back( objeto2 );

    // ObjetoPLY=objetosEscena(2)
    Modelo objeto3;
    objeto3.objeto = new ObjPLY( "./plys/big_dodge" );
    objeto3.dibujar = false;
    objeto3.posicion = Tupla3f( -250.0, 0.0, 0.0 );
    objeto3.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    objeto3.escalado = Tupla3f( 10.0, 10.0, 10.0 );
    objeto3.objeto->setMaterial( predefinido );
    objetosEscena.push_back( objeto3 );

    // Cilindro=objetosEscenaConTapas(0)
    ModeloTapas mt0;
    mt0.objeto = new Cilindro( 10, 10, 100, 45);
    mt0.dibujar = false;
    mt0.posicion = Tupla3f( 0.0, 0.0, -150.0 );
    mt0.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt0.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    mt0.objeto->setMaterial( predefinido );
    objetosEscenaConTapas.push_back( mt0 );

    // Esfera=objetosEscenaConTapas(1)
    ModeloTapas mt1;
    mt1.objeto = new Esfera( 20, 20, 45 );
    mt1.dibujar = false;
    mt1.posicion = Tupla3f( 100.0, 0.0, -150.0 );
    mt1.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt1.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    mt1.objeto->setMaterial( predefinido );
    objetosEscenaConTapas.push_back( mt1 );

    // Cono=objetosEscenaConTapas(2)
    ModeloTapas mt2;
    mt2.objeto = new Cono( 10, 10, 100, 45 );
    mt2.dibujar = false;
    mt2.posicion = Tupla3f( 200.0, 0.0, -150.0 );
    mt2.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt2.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    mt2.objeto->setMaterial( predefinido );
    objetosEscenaConTapas.push_back( mt2 );

    // PeonBlanco=objetosEscenaConTapas(3)
    ModeloTapas mt3;
    mt3.objeto = new ObjRevolucion( "./plys/peon", 20, true, true );
    mt3.dibujar = true;
    mt3.posicion = Tupla3f( 150.0, 0.0, 0.0 );
    mt3.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt3.escalado = Tupla3f( 20.0, 20.0, 20.0 );
    mt3.objeto->setMaterial( yeso );
    objetosEscenaConTapas.push_back( mt3 );

    // PeonNegro=objetosEscenaConTapas(4)
    ModeloTapas mt4;
    mt4.objeto = new ObjRevolucion( "./plys/peon_inverso", 20, true, true );
    mt4.dibujar = true;
    mt4.posicion = Tupla3f( -150.0, 0.0, 0.0 );
    mt4.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt4.escalado = Tupla3f( 20.0, 20.0, 20.0 );
    mt4.objeto->setMaterial( obsidiana );
    objetosEscenaConTapas.push_back( mt4 );

    // Luz=objetosEscenaConTapas(5)
    ModeloTapas mt5;
    mt5.objeto = new Esfera(20,20,10);
    mt5.dibujar = false;
    mt5.posicion = luzDir->getPosicion();
    mt5.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt5.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    mt5.objeto->setColorSolido( Tupla3f( 1, 1, 0 ) );
    mt5.objeto->setMaterial( oro );
    objetosEscenaConTapas.push_back( mt5 );

    // ObjetoRevolución=objetosEscenaConTapas(6)
    ModeloTapas mt6;
    mt6.objeto = new ObjRevolucion( "./plys/lata-pcue", 20, true, true );
    mt6.dibujar = false;
    mt6.posicion = Tupla3f( 150.0, 0.0, 0.0 );
    mt6.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt6.escalado = Tupla3f( 20.0, 20.0, 20.0 );
    mt6.objeto->setMaterial( predefinido );
    objetosEscenaConTapas.push_back( mt6 );

    /*
    // Pino1=modelosJerarquicos(0)
    Jerarquico j1;
    j1.objeto = new Pino();
    j1.dibujar = true;
    j1.posicion = Tupla3f( 0.0, 0.0, 0.0 );
    j1.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    j1.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    modelosJerarquicos.push_back( j1 );

    // Pino2=modelosJerarquicos(1)
    Jerarquico j2;
    j2.objeto = new Pino();
    j2.dibujar = true;
    j2.posicion = Tupla3f( 80.0, 0.0, -10.0 );
    j2.orientacion = Tupla3f( 0.0, 45.0, 0.0 );
    j2.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    modelosJerarquicos.push_back( j2 );

    // Pino3=modelosJerarquicos(2)
    Jerarquico j3;
    j3.objeto = new Pino();
    j3.dibujar = true;
    j3.posicion = Tupla3f( -80.0, 0.0, 20.0 );
    j3.orientacion = Tupla3f( 0.0, -32.0, 0.0 );
    j3.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    modelosJerarquicos.push_back( j3 );*/

    // Tractor = modelosJerarquicos(0)
    tractor = new TractorRemolque();


    // Inicialización de los flags
    puntos = false;
    lineas = false;
    solido = true;
    ajedrez = false;
    modoDibujado = INMEDIATO;
    tapa_inferior = true;
    tapa_superior = true;
    modoIluminacion = BASICA;
    variacionLuz = VARALPHA;
    animacionAutomatica = false;
    gradoSeleccionado = ROTARRUEDAS;

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
  glEnable( GL_NORMALIZE );   // para evitar la alteración de la longitud de las normales

	Width  = UI_window_width/10;
	Height = UI_window_height/10;

  change_projection( float(UI_window_width)/float(UI_window_height) );
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

void Escena::DrawMode( visualizacion tipo ) {

  for( int i = 0; i < objetosEscena.size(); i++ ) {
    if( objetosEscena[i].dibujar ) {
      glPushMatrix();
        glTranslatef( objetosEscena[i].posicion(0), objetosEscena[i].posicion(1), objetosEscena[i].posicion(2) );
        glRotatef( objetosEscena[i].orientacion(0), 1, 0, 0 );
        glRotatef( objetosEscena[i].orientacion(1), 0, 1, 0 );
        glRotatef( objetosEscena[i].orientacion(2), 0, 0, 1 );
        glScalef( objetosEscena[i].escalado(0), objetosEscena[i].escalado(1), objetosEscena[i].escalado(2) );
        objetosEscena[i].objeto->draw( modoDibujado, tipo );
      glPopMatrix();
    }
  }

  for( int i = 0; i < objetosEscenaConTapas.size(); i++ ) {
    if( objetosEscenaConTapas[i].dibujar ) {
      glPushMatrix();
        glTranslatef( objetosEscenaConTapas[i].posicion(0), objetosEscenaConTapas[i].posicion(1), objetosEscenaConTapas[i].posicion(2) );
        glRotatef( objetosEscenaConTapas[i].orientacion(0), 1, 0, 0 );
        glRotatef( objetosEscenaConTapas[i].orientacion(1), 0, 1, 0 );
        glRotatef( objetosEscenaConTapas[i].orientacion(2), 0, 0, 1 );
        glScalef( objetosEscenaConTapas[i].escalado(0), objetosEscenaConTapas[i].escalado(1), objetosEscenaConTapas[i].escalado(2) );
        if( tapa_superior and tapa_inferior )
          objetosEscenaConTapas[i].objeto->draw( modoDibujado, tipo );
        else {
          objetosEscenaConTapas[i].objeto->draw_cuerpo( tipo );
          objetosEscenaConTapas[i].objeto->draw_tapas( tipo, tapa_superior, tapa_inferior );
        }
      glPopMatrix();
    }
  }

  for( int i = 0; i < modelosJerarquicos.size(); i++ ) {
    if( modelosJerarquicos[i].dibujar ) {
      glPushMatrix();
        glTranslatef( modelosJerarquicos[i].posicion(0), modelosJerarquicos[i].posicion(1), modelosJerarquicos[i].posicion(2) );
        glRotatef( modelosJerarquicos[i].orientacion(0), 1, 0, 0 );
        glRotatef( modelosJerarquicos[i].orientacion(1), 0, 1, 0 );
        glRotatef( modelosJerarquicos[i].orientacion(2), 0, 0, 1 );
        glScalef( modelosJerarquicos[i].escalado(0), modelosJerarquicos[i].escalado(1), modelosJerarquicos[i].escalado(2) );
        modelosJerarquicos[i].objeto->draw( modoDibujado, tipo );
      glPopMatrix();
    }
  }

  tractor->draw( modoDibujado, tipo );

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

  if( modoIluminacion != BASICA ) {
    // Activamos la iluminación
    glEnable( GL_LIGHTING );

    // Seleccionamos el modo de iluminación
    if( modoIluminacion == PLANA )
      glShadeModel( GL_FLAT );
    else
      glShadeModel( GL_SMOOTH );

    // Si la luz direccional está activada, la aplicamos y dibujamos la esfera
    // para ayudar a ver la dirección
    if( glIsEnabled( GL_LIGHT1 ) ) {
      //objetosEscenaConTapas[5].posicion = luzDir->getPosicion();
      luzDir->aplicar();
    }

    // Comprobamos si necesitamos aplicar el resto de luces
    if( glIsEnabled( GL_LIGHT2 ) )
      luzPos1->aplicar();
    if( glIsEnabled( GL_LIGHT3 ) )
      luzPos2->aplicar();

    // Dibujamos los objetos
    DrawMode( SOLID );

  } else {

    glDisable( GL_LIGHTING );

    if( ajedrez ) {
      DrawMode( CHESS );
    } else {
      if( puntos )
        DrawMode( POINTS );
      if( lineas )
        DrawMode( LINES );
      if( solido )
        DrawMode( SOLID );
    }

  }

}

void Escena::animarTractor( gradosTractor gradoSeleccionado, int sentido ) {

  switch ( gradoSeleccionado ) {

    case ROTARRUEDAS:
      tractor->rotarRuedas(sentido);
      break;

    case GIRARRUEDASDEL:
      tractor->cambiarAnguloGiro(sentido);
      break;

    default:
      std::cout << "Grado seleccionado no manejado\n";
      break;

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
        case 'T':
          modoMenu = TAPAS;
          break;
        case 'A':
          modoMenu = ANIMACIONAUTO;
          animacionAutomatica = true;
          break;
        case 'M':
          modoMenu = ANIMACIONMANUAL;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'O': Cambiar objeto\n"
               << "'V': Cambiar modo de visualización\n'D': Cambiar modo de dibujado\n"
               << "'T': Cambiar visualización de tapas\n'A': Animación Automática\n"
               << "'M': Animación Manual\nQ': Salir\n";
          break;
      }

      break;

    case SELOBJETO:

      switch( toupper( tecla ) ) {

        case 'Q':
          modoMenu = NADA;
          break;

        case '0':
          cout << "Cambiando la visualización del Cubo.\n";
          if( objetosEscena[0].dibujar )
            objetosEscena[0].dibujar = false;
          else
            objetosEscena[0].dibujar = true;
          break;

        case '1':
          cout << "Cambiando la visualización del Tetraedro.\n";
          if( objetosEscena[1].dibujar )
            objetosEscena[1].dibujar = false;
          else
            objetosEscena[1].dibujar = true;
          break;

        case '2':
          cout << "Cambiando la visualización del Cilindro.\n";
          if( objetosEscenaConTapas[0].dibujar )
            objetosEscenaConTapas[0].dibujar = false;
          else
            objetosEscenaConTapas[0].dibujar = true;
          break;

        case '3':
          cout << "Cambiando la visualización de la Esfera.\n";
          if( objetosEscenaConTapas[1].dibujar )
            objetosEscenaConTapas[1].dibujar = false;
          else
            objetosEscenaConTapas[1].dibujar = true;
          break;

        case '4':
          cout << "Cambiando la visualización del Cono.\n";
          if( objetosEscenaConTapas[2].dibujar )
            objetosEscenaConTapas[2].dibujar = false;
          else
            objetosEscenaConTapas[2].dibujar = true;
          break;

        case '5':
          cout << "Cambiando la visualización del Objeto PLY.\n";
          if( objetosEscena[3].dibujar )
            objetosEscena[3].dibujar = false;
          else
            objetosEscena[3].dibujar = true;
          break;

        case '6':
          cout << "Cambiando la visualización del Objeto de Revolución.\n";
          if( objetosEscenaConTapas[6].dibujar )
            objetosEscenaConTapas[6].dibujar = false;
          else
            objetosEscenaConTapas[6].dibujar = true;
          break;

        case '7':
          cout << "Cambiando la visualización del Peón Blanco.\n";
          if( objetosEscenaConTapas[3].dibujar )
            objetosEscenaConTapas[3].dibujar = false;
          else
            objetosEscenaConTapas[3].dibujar = true;
          break;

        case '8':
          cout << "Cambiando la visualización del Peón Negro.\n";
          if( objetosEscenaConTapas[4].dibujar )
            objetosEscenaConTapas[4].dibujar = false;
          else
            objetosEscenaConTapas[4].dibujar = true;
          break;

        case '9':
          cout << "Cambiando la visualización del Lingote.\n";
          if( objetosEscena[2].dibujar )
            objetosEscena[2].dibujar = false;
          else
            objetosEscena[2].dibujar = true;
          break;

        case 'J':
          cout << "Cambiando la visualización de los modelos jerárquicos.\n";
          if( modelosJerarquicos[0].dibujar )
            for( int i = 0; i < modelosJerarquicos.size(); i++ )
              modelosJerarquicos[i].dibujar = false;
          else
            for( int i = 0; i < modelosJerarquicos.size(); i++ )
              modelosJerarquicos[i].dibujar = true;
          break;

        case 'P':

          cout << "Cambiando el Objeto PLY, introduzca la ruta del nuevo: ";

          char nombreArchivoPLY[100];

          scanf( "%[^\n]", nombreArchivoPLY );
          while( ( getchar() ) != '\n');

          objetosEscena[3].objeto = new ObjPLY( nombreArchivoPLY );
          objetosEscena[3].dibujar = true;

          cout << endl;
          break;

        case 'R':

          cout << "Cambiando el Objeto de Revolución, introduzca la ruta del nuevo: ";

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

          objetosEscenaConTapas[6].objeto = new ObjRevolucion( nombreArchivoRev, num_instancias, tapa_sup, tapa_inf );
          objetosEscenaConTapas[6].dibujar = true;

          cout << endl;
          break;


        default:
          cout << "ERROR - opciones disponibles:\n'0': Cubo\n'1': Tetraedro\n"
               << "'2': Cilindro\n'3': Esfera\n'4': Cono\n'5': Objeto PLY\n"
               << "'6': Objeto de Revolución\n'7': Peón Blanco\n"
               << "'8': Peón Negro (Invertido)\n'9': Lingote\n'P': Cambiar el Objeto PLY\n"
               << "'R': Cambiar el Objeto de Revolución\n'J': Pinos\n'Q': Salir\n\n";
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
        case 'I':
          modoMenu = ILUMINACION;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'L': Línea\n'P': Puntos\n"
               << "'S': Sólido\n'A': Ajedrez\n'I': Cambiar Iluminación\n";
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

    case TAPAS:

      switch( toupper( tecla ) ) {

        case 'Q':
          modoMenu = NADA;
          break;

        case 'S':
          tapa_superior = !tapa_superior;
          break;

        case 'I':
          tapa_inferior = !tapa_inferior;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n'S': Poner/Quitar tapa superior\n"
               << "'I': Poner/Quitar tapa inferior\n'Q': Volver al menú principal\n";
          break;

      }

      break;

    case ILUMINACION:

      switch( toupper( tecla ) ) {

        case '0':
          if( glIsEnabled( GL_LIGHT0 ) ) {
            glDisable( GL_LIGHT0 );
            cout << "Luz 0 desactivada.\n";
          } else {
            glEnable( GL_LIGHT0 );
            cout << "Luz 0 activada.\n";
          }
          break;

          case '1':
            if( glIsEnabled( GL_LIGHT1 ) ) {
              glDisable( GL_LIGHT1 );
              cout << "Luz 1 desactivada.\n";
            } else {
              glEnable( GL_LIGHT1 );
              cout << "Luz 1 activada.\n";
            }
            break;

          case '2':
            if( glIsEnabled( GL_LIGHT2 ) ) {
              glDisable( GL_LIGHT2 );
              cout << "Luz 2 desactivada.\n";
            } else {
              glEnable( GL_LIGHT2 );
              cout << "Luz 2 activada.\n";
            }
            break;

          case '3':
            if( glIsEnabled( GL_LIGHT3 ) ) {
              glDisable( GL_LIGHT3 );
              cout << "Luz 3 desactivada.\n";
            } else {
              glEnable( GL_LIGHT3 );
              cout << "Luz 3 activada.\n";
            }
            break;

        case '<':
          if( variacionLuz == VARALPHA )
            luzDir->variarAnguloAlpha(-1);
          else
            luzDir->variarAnguloBeta(-1);
          if( glIsEnabled( GL_LIGHT1 ) )
            luzDir->aplicar();
          break;

        case '>':
          if( variacionLuz == VARALPHA )
            luzDir->variarAnguloAlpha(1);
          else
            luzDir->variarAnguloBeta(1);
          if( glIsEnabled( GL_LIGHT1 ) )
            luzDir->aplicar();
          break;

        case 'A':
          variacionLuz = VARALPHA;
          cout << "Modo variación del ángulo alpha\n";
          break;

        case 'B':
          variacionLuz = VARBETA;
          cout << "Modo variación del ángulo beta\n";
          break;

        case 'N':
          modoIluminacion = BASICA;
          cout << "Modo de iluminación establecido: básico.\n";
          break;

        case 'S':
          modoIluminacion = SUAVE;
          cout << "Modo de iluminación establecido: suave.\n";
          break;

        case 'P':
          modoIluminacion = PLANA;
          cout << "Modo de iluminación establecido: plano.\n";
          break;

        case 'Q':
          modoMenu = SELVISUALIZACION;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n'N': Modo básico\n'S': Iluminación suave\n"
               << "'P': Iluminación plana\n'Q': Salir\n";
          break;

      }

      break;

    case ANIMACIONAUTO:

      switch( toupper( tecla ) ) {

        case 'Q':
          animacionAutomatica = false;
          modoMenu = NADA;
          break;

      }

      break;

    case ANIMACIONMANUAL:

      switch( toupper( tecla ) ) {

        case '0':
          gradoSeleccionado = ROTARRUEDAS;
          cout << "Se ha seleccionado \"Rotar Ruedas\"\n";
          break;

        case '1':
          gradoSeleccionado = GIRARRUEDASDEL;
          cout << "Se ha seleccionado \"Girar Ruedas Delanteras\"\n";
          break;

        case '+':
          animarTractor( gradoSeleccionado, 1 );
          break;

        case '-':
          animarTractor( gradoSeleccionado, -1 );
          break;

        case 'Q':
          modoMenu = NADA;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n'0': Rotar Ruedas\n"
               << "'1': Girar Ruedas Delanteras\n"
               << "'+': Aumentar grado seleccionado\n"
               << "'-': Disminuir grado seleccionado\n"
               << "'Q': Salir\n";

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
      case TAPAS: cout << "\nMenú de visualización de tapas.\n"; break;
      case ILUMINACION: cout << "\nMenú de iluminación.\n"; break;
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
