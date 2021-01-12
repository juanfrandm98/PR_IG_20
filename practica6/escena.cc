

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
    Material hierba = Material(Tupla4f(0.45,0.55,0.45,1),Tupla4f(0.0,0.0,0.0,1),Tupla4f(0.1,0.35,0.1,1),0.25);
    Material predefinido = Material(Tupla4f(0.5,0.4,0.4,1),Tupla4f(0.7,0.04,0.04,1),Tupla4f(0.05,0.0,0.0,1),.078125);

    // Creación de las texturas
    Textura caja = Textura( "./images/text-madera.jpg" );
    Textura grass = Textura( "./images/hierba.jpeg" );
    Textura lata = Textura( "./images/text-lata-1.jpg" );
    Textura skybox = Textura( "./images/skybox.jpeg" );

    // Creación de colores
    Tupla3f colorBlanco = Tupla3f( 1, 1, 1 );
    Tupla3f colorAzul = Tupla3f( 0, 0, 1 );

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
    objeto0.objeto = new Cubo( 10 );
    objeto0.dibujar = true;
    objeto0.posicion = Tupla3f( 50.0, 5.0, 100.0 );
    objeto0.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    objeto0.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    objeto0.objeto->setMaterial( yeso );
    objeto0.objeto->setTextura( caja );
    objeto0.objeto->setColorSolido( Tupla3f( 1, 1, 1 ) );
    objetosEscena.push_back( objeto0 );

    suelo = new Cubo( 500 );
    suelo->setMaterial( hierba );
    suelo->setColorSolido( Tupla3f( 0, 1, 0 ) );
    suelo->setTextura( grass );
    suelo->ubicarTexturaSuperior();

    // ObjetoRevolución=objetosEscenaConTapas(6)
    ModeloTapas mt0;
    mt0.objeto = new ObjRevolucion( "./plys/lata-pcue", 20, true, true );
    mt0.dibujar = true;
    mt0.posicion = Tupla3f( 0.0, 0.0, 80.0 );
    mt0.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt0.escalado = Tupla3f( 30.0, 30.0, 30.0 );
    mt0.objeto->setMaterial( yeso );
    mt0.objeto->setColorSolido( colorBlanco );
    mt0.objeto->setTextura( lata );
    objetosEscenaConTapas.push_back( mt0 );

    ModeloTapas mt1;
    mt1.objeto = new Esfera( 20, 20, 300 );
    mt1.dibujar = true;
    mt1.posicion = Tupla3f( 0.0, 0.0, 0.0 );
    mt1.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    mt1.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    mt1.objeto->setMaterial( yeso );
    mt1.objeto->setColorSolido( colorAzul );
    mt1.objeto->setTextura( skybox );
    mt1.objeto->invertirCaras();
    objetosEscenaConTapas.push_back( mt1 );

    // Pino1=modelosJerarquicos(0)
    Jerarquico j1;
    j1.objeto = new Pino();
    j1.dibujar = true;
    j1.posicion = Tupla3f( 0.0, 0.0, -150.0 );
    j1.orientacion = Tupla3f( 0.0, 0.0, 0.0 );
    j1.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    modelosJerarquicos.push_back( j1 );

    // Pino2=modelosJerarquicos(1)
    Jerarquico j2;
    j2.objeto = new Pino();
    j2.dibujar = true;
    j2.posicion = Tupla3f( 150.0, 0.0, -100.0 );
    j2.orientacion = Tupla3f( 0.0, 45.0, 0.0 );
    j2.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    modelosJerarquicos.push_back( j2 );

    // Pino3=modelosJerarquicos(2)
    Jerarquico j3;
    j3.objeto = new Pino();
    j3.dibujar = true;
    j3.posicion = Tupla3f( -120.0, 0.0, 20.0 );
    j3.orientacion = Tupla3f( 0.0, -32.0, 0.0 );
    j3.escalado = Tupla3f( 1.0, 1.0, 1.0 );
    modelosJerarquicos.push_back( j3 );

    // Tractor = modelosJerarquicos(0)
    tractor = new TractorRemolque();

    // Cámaras
    Tupla3f eye = Tupla3f( -150, 100, 150 );
    Tupla3f at  = Tupla3f( 0, 0, 0 );
    Tupla3f up  = Tupla3f( 0, 1, 0 );

    Camara c0( eye, at, up, PERSPECTIVA, 5, 5, 2, 2, 50, 2000 );
    camaras.push_back(c0);

    Camara c1( eye, at, up, ORTOGONAL, 5, 5, 2, 2, 50, 2000 );
    camaras.push_back(c1);

    eye = Tupla3f( 150, 100, 150 );
    Camara c2( eye, at, up, PERSPECTIVA, 5, 5, 2, 2, 50, 2000 );
    camaras.push_back(c2);

    camaraActiva = 0;


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

    // Las velocidades de los grados de libertad por separado, de esta forma:
    //    - velocidades(0) -> rotación ruedas y rodillo (avance)
    //    - velocidades(1) -> rotación ruedas (giro)
    //    - velocidades(2) -> rotación remolque (vertical)
    //    - velocidades(3) -> rotación remolque (horizontal)
    //    - velocidades(4) -> traslación remolque (horizontal)
    for( int i = 0; i < 5; i++ )
      velocidades.push_back(minVelocidad);

    sumandoGiroRuedas = true;
    sumandoGiroRemolque = true;
    sumandoInclinacion = true;
    timerInclinacionRemolque = -1;
    sumandoMovimientoRodillo = true;
    texturas = false;

    //botonIzq = SUELTO;
    //botonDer = SUELTO;

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

  ajustarCamaras( Width, Height );

  change_projection();
	glViewport( 0, 0, UI_window_width, UI_window_height );
}

void Escena::ajustarCamaras( float width, float height ) {

  for( int i = 0; i < camaras.size(); i++ ) {
    /*
    camaras[i].setLeft( width / 2 );
    camaras[i].setRight( width / 2 );
    camaras[i].setTop( height / 2 );
    camaras[i].setBottom( height / 2 );
    */
    camaras[i].setLeft( -width );
    camaras[i].setRight( width );
    camaras[i].setTop( height );
    camaras[i].setBottom( -height );
  }

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
          objetosEscenaConTapas[i].objeto->draw_cuerpo( modoDibujado, tipo );
          objetosEscenaConTapas[i].objeto->draw_tapas( modoDibujado, tipo, tapa_superior, tapa_inferior );
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

  glPushMatrix();
    glTranslatef( 0, 17.5, 0 );
    glScalef( 0.5, 0.5, 0.5 );
    tractor->draw( modoDibujado, tipo );
  glPopMatrix();

  glPushMatrix();
    glTranslatef( 0.0, 0.5, 0.0 );
    glScalef( 1, 0.002, 1 );
    suelo->draw( modoDibujado, tipo );
  glPopMatrix();

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

  if( texturas )
    glEnable( GL_TEXTURE_2D );
  else
    glDisable( GL_TEXTURE_2D );

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

// **************************************************************************
//
// funciones para controlar la animación del modelo jerárquico principal
//
// **************************************************************************

void Escena::animarGradoTractor( gradosTractor gradoSeleccionado, float sentido ) {

  switch ( gradoSeleccionado ) {

    case ROTARRUEDAS:
      tractor->simularAvance(sentido);
      break;

    case GIRARRUEDASDEL:
      tractor->cambiarAnguloGiro(sentido);
      break;

    case INCLINARREMOLQUE:
      tractor->inclinarRemolque(sentido);
      break;

    case GIRARREMOLQUE:
      tractor->girarRemolque(sentido);
      break;

    case TRASLADARRODILLO:
      tractor->trasladarRodillo(sentido);
      break;

    default:
      std::cout << "Grado seleccionado no manejado\n";
      break;

  }

}

void Escena::animarModeloJerarquico() {

  if( animacionAutomatica ) {

    animarGradoTractor( ROTARRUEDAS, velocidades[0] );

    if( sumandoGiroRuedas ) {
      animarGradoTractor( GIRARRUEDASDEL, velocidades[1] );
      if( tractor->ruedasAlTope() )
        sumandoGiroRuedas = false;
    } else {
      animarGradoTractor( GIRARRUEDASDEL, -velocidades[1] );
      if( tractor->ruedasAlTope() )
        sumandoGiroRuedas = true;
    }

    if( sumandoInclinacion ) {
      if( timerInclinacionRemolque < 0 ) {
        animarGradoTractor( INCLINARREMOLQUE, velocidades[2] );
        if( tractor->inclinacionAlTope() )
          sumandoInclinacion = false;
      } else
        timerInclinacionRemolque -= velocidades[2];
    } else {
      animarGradoTractor( INCLINARREMOLQUE, -velocidades[2] );
      if( tractor->inclinacionAlTope() ) {
        sumandoInclinacion = true;
        timerInclinacionRemolque = 1000;
      }
    }

    if( sumandoGiroRemolque ) {
      animarGradoTractor( GIRARREMOLQUE, velocidades[3] );
      if( tractor->remolqueGiradoAlTope() )
        sumandoGiroRemolque = false;
    } else {
      animarGradoTractor( GIRARREMOLQUE, -velocidades[3] );
      if( tractor->remolqueGiradoAlTope() )
        sumandoGiroRemolque = true;
    }

    if( sumandoMovimientoRodillo ) {
      animarGradoTractor( TRASLADARRODILLO, velocidades[4] );
      if( tractor->rodilloTrasladadoAlTope() )
        sumandoMovimientoRodillo = false;
    } else {
      animarGradoTractor( TRASLADARRODILLO, -velocidades[4] );
      if( tractor->rodilloTrasladadoAlTope() )
        sumandoMovimientoRodillo = true;
    }

  }

}

void Escena::comprobarVelocidadesEnRango() {

  for( int i = 0; i < velocidades.size(); i++ )
    if( velocidades[i] > maxVelocidad )
      velocidades[i] = maxVelocidad;
    else if( velocidades[i] < minVelocidad )
      velocidades[i] = minVelocidad;

}

void Escena::cambiarVelocidadAnimacion( gradosTractor grado, bool incrementar ) {

  float incremento = minVelocidad;

  if( !incrementar )
    incremento *= -1;

  switch( grado ) {

    case TODOS:
      for( int i = 0; i < velocidades.size(); i++ )
        velocidades[i] += incremento;
      break;

    case ROTARRUEDAS:
      velocidades[0] += incremento;
      break;

    case GIRARRUEDASDEL:
      velocidades[1] += incremento;
      break;

    case INCLINARREMOLQUE:
      velocidades[2] += incremento;
      break;

    case GIRARREMOLQUE:
      velocidades[3] += incremento;
      break;

    case TRASLADARRODILLO:
      velocidades[4] += incremento;
      break;

    default:
      std::cout << "Grado de libertad inexistente.\n";

  }

  comprobarVelocidadesEnRango();

}

// **************************************************************************
//
// funciones para controlar el movimiento de la cámara
//
// **************************************************************************

void Escena::clickRaton( int boton, int estado, int x, int y ) {



}

void Escena::ratonMovido( int x, int y ) {
/*
  if( botonDer == PULSADO ) {
    camaras[camaraActiva].girar( x - xant, y - yant );
    xant = x;
    yant = y;
  }
*/
}


void Escena::cambiarCamara( int numCamara ) {

  if( numCamara >= 0 and numCamara < camaras.size() ) {
    camaraActiva = numCamara;
    std::cout << "Cámara #" << camaraActiva << " seleccionada.\n";
    change_projection();
    change_observer();
  } else {
    std::cout << "ERROR - intentando cambiar a cámara no existente.\n";
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
          gradoSeleccionado = TODOS;
          animacionAutomatica = true;
          break;
        case 'M':
          modoMenu = ANIMACIONMANUAL;
          gradoSeleccionado = TODOS;
          break;
        case 'C':
          modoMenu = CAMARAS;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'O': Cambiar objeto\n"
               << "'V': Cambiar modo de visualización\n'D': Cambiar modo de dibujado\n"
               << "'T': Cambiar visualización de tapas\n'A': Animación Automática\n"
               << "'M': Animación Manual\n'C': Cámaras\n'Q': Salir\n";
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
        case 'T':
          if( texturas )
            texturas = false;
          else
            texturas = true;
          break;
        default:
          cout << "ERROR - opciones disponibles:\n'L': Línea\n'P': Puntos\n"
               << "'S': Sólido\n'A': Ajedrez\n'I': Cambiar Iluminación\n"
               << "'T': Cambiar Utilización de Texturas\n";
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

        case 'C':
          modoMenu = COLORLUZ;
          cout << "Cambiando el color de la luz puntual.\n";
          break;

        case 'Q':
          modoMenu = SELVISUALIZACION;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n'N': Modo básico\n"
               << "'S': Iluminación suave\n'P': Iluminación plana\n"
               << "'A': Cambiar ángulo alfa\n'B': Cambiar ángulo beta\n"
               << "'<': Disminuir ángulo seleccionado\n"
               << "'>': Aumentar ángulo seleccionado\n"
               << "'C': Cambiar el color de la luz puntual (3)\n'Q': Salir\n";
          break;

      }

      break;

    case COLORLUZ:

      switch( toupper( tecla ) ) {

        case 'R':
          luzPos2->setColores(Tupla4f( 0.9, 0, 0, 1 ), Tupla4f( 1, 0, 0, 1 ), Tupla4f( 0.9, 0, 0, 1 ));
          cout << "Luz cambiada a Rojo\n";
          break;

        case 'G':
          luzPos2->setColores(Tupla4f( 0, 0.9, 0, 1 ), Tupla4f( 0, 1, 0, 1 ), Tupla4f( 0, 0.9, 0, 1 ));
          cout << "Luz cambiada a Verde\n";
          break;

        case 'B':
          luzPos2->setColores(Tupla4f( 0, 0, 0.9, 1 ), Tupla4f( 0, 0, 1, 1 ), Tupla4f( 0, 0, 0.9, 1 ));
          cout << "Luz cambiada a Azul\n";
          break;

        case 'Q':
          modoMenu = ILUMINACION;
          break;

        default:
          cout << "Error - opciones disponibles:\n'R': Luz Roja\n"
               << "'G': Luz Verde\n'B': Luz Azul\n'Q': Volver al menú anterior\n";

      }

      break;

    case ANIMACIONAUTO:

      switch( toupper( tecla ) ) {

        case '0':
          gradoSeleccionado = TODOS;
          cout << "Cambiando velocidad general.\n";
          break;

        case '1':
          gradoSeleccionado = ROTARRUEDAS;
          cout << "Cambiando velocidad de la rotación de las ruedas.\n";
          break;

        case '2':
          gradoSeleccionado = GIRARRUEDASDEL;
          cout << "Cambiando velocidad del giro de las ruedas delanteras.\n";
          break;

        case '3':
          gradoSeleccionado = INCLINARREMOLQUE;
          cout << "Cambiando velocidad de la inclinación del remolque.\n";
          break;

        case '4':
          gradoSeleccionado = GIRARREMOLQUE;
          cout << "Cambiando velocidad del giro del remolque.\n";
          break;

        case '5':
          gradoSeleccionado = TRASLADARRODILLO;
          cout << "Cambiando velocidad de la traslación del rodillo.\n";
          break;

        case '+':
          cambiarVelocidadAnimacion( gradoSeleccionado, true );
          cout << "Aumentando velocidad...\n";
          break;

        case '-':
          cambiarVelocidadAnimacion( gradoSeleccionado, false );
          cout << "Disminuyendo velocidad...\n";
          break;

        case 'Q':
          animacionAutomatica = false;
          modoMenu = NADA;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n"
               << "'0': Cambiar velocidad general\n"
               << "'1': Cambiar velocidad de la rotación de las ruedas\n"
               << "'2': Cambiar velocidad del giro de las ruedas delanteras\n"
               << "'3': Cambiar velocidad de la inclinación del remolque\n"
               << "'4': Cambiar velocidad del giro del remolque\n"
               << "'5': Cambiar velocidad de la traslación del rodillo\n"
               << "'+': Aumentar grado seleccionado\n"
               << "'-': Disminuir grado seleccionado\n"
               << "'Q': Salir\n";

      }

      break;

    case ANIMACIONMANUAL:

      switch( toupper( tecla ) ) {

        case '0':
          gradoSeleccionado = TODOS;
          cout << "Se ha seleccionado\"Animar todo\"\n";
          break;

        case '1':
          gradoSeleccionado = ROTARRUEDAS;
          cout << "Se ha seleccionado \"Rotar Ruedas\"\n";
          break;

        case '2':
          gradoSeleccionado = GIRARRUEDASDEL;
          cout << "Se ha seleccionado \"Girar Ruedas Delanteras\"\n";
          break;

        case '3':
          gradoSeleccionado = INCLINARREMOLQUE;
          cout << "Se ha seleccionado \"Inclinar Remolque\"\n";
          break;

        case '4':
          gradoSeleccionado = GIRARREMOLQUE;
          cout << "Se ha seleccionado \"Girar Remolque\"\n";
          break;

        case '5':
          gradoSeleccionado = TRASLADARRODILLO;
          cout << "Se ha seleccionado \"Trasladar Rodillo\"\n";
          break;

        case '+':
          animarGradoTractor( gradoSeleccionado, 1 );
          break;

        case '-':
          animarGradoTractor( gradoSeleccionado, -1 );
          break;

        case 'Q':
          modoMenu = NADA;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n'0': Animar todo\n"
               << "'1': Rotar Ruedas\n"
               << "'2': Girar Ruedas Delanteras\n"
               << "'3': Inclinar Remolque\n"
               << "'4': Girar Remolque\n"
               << "'5': Trasladar rodillo\n"
               << "'+': Aumentar grado seleccionado\n"
               << "'-': Disminuir grado seleccionado\n"
               << "'Q': Salir\n";

      }

      break;

    case CAMARAS:

      switch( toupper( tecla ) ) {

        case '0':
          cambiarCamara(0);
          break;

        case '1':
          cambiarCamara(1);
          break;

        case '2':
          cambiarCamara(2);
          break;

        case 'Q':
          modoMenu = NADA;
          break;

        default:
          cout << "ERROR - opciones disponibles:\n'0': Cámara 0\n"
               << "'1': Cámara 1\n'Q': Salir\n";

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
      case ANIMACIONAUTO: cout << "\nMenú de la animación automática.\n"; break;
      case ANIMACIONMANUAL: cout << "\nMenú de la animación manual.\n"; break;
      case COLORLUZ: cout << "\nMenú de cambio de color de la luz puntual (3).\n"; break;
      case CAMARAS: cout << "\nMenú de selección de cámara.\n"; break;
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
         camaras[camaraActiva].rotarYExaminar(-0.0174533);
         break;
	   case GLUT_KEY_RIGHT:
         camaras[camaraActiva].rotarYExaminar(0.0174533);
         break;
	   case GLUT_KEY_UP:
         camaras[camaraActiva].rotarXExaminar(-0.0174533);;
         break;
	   case GLUT_KEY_DOWN:
         camaras[camaraActiva].rotarXExaminar(0.0174533);;
         break;
	   case GLUT_KEY_F1:
         camaras[camaraActiva].zoom(0.8);
         break;
	   case GLUT_KEY_F2:
         camaras[camaraActiva].zoom(1.2);
         break;
	}

	change_projection();
}

//**************************************************************************
// Funcion para definir la transformación de proyeccion
//
// ratio_xy : relacción de aspecto del viewport ( == ancho(X) / alto(Y) )
//
//***************************************************************************

void Escena::change_projection()
{
   camaras[camaraActiva].setProyeccion();
}
//**************************************************************************
// Funcion que se invoca cuando cambia el tamaño de la ventana
//***************************************************************************

void Escena::redimensionar( int newWidth, int newHeight )
{
   Width  = newWidth/10;
   Height = newHeight/10;

   ajustarCamaras( Width, Height );

   change_projection();
   glViewport( 0, 0, newWidth, newHeight );
}

//**************************************************************************
// Funcion para definir la transformación de vista (posicionar la camara)
//***************************************************************************

void Escena::change_observer()
{
   // posicion del observador
   camaras[camaraActiva].setObservador();
}
