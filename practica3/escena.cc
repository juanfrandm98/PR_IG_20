

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

    cubo = new Cubo( 100 );
    tetraedro = new Tetraedro( 100 );
    cilindro = new Cilindro( 10, 10, 100, 45);
    esfera = new Esfera( 20, 20, 45 );
    cono = new Cono( 10, 10, 100, 45 );
    luz = new Esfera(20,20,10);
    luz->setColorSolido( Tupla3f( 1, 1, 0 ) );

    puntos = false;
    lineas = false;
    solido = true;
    ajedrez = false;
    modoDibujado = INMEDIATO;
    tapa_inferior = true;
    tapa_superior = true;
    modoIluminacion = BASICA;
    variacionLuz = VARALPHA;

    peonBlanco = new ObjRevolucion( "./plys/peon", 20, true, true );
    peonNegro = new ObjRevolucion( "./plys/peon", 20, true, true );
    lingote = new Cubo( 35 );

    Material obsidiana = Material(Tupla4f(0.18275,0.17,0.22525,1),Tupla4f(0.332741,0.328634,0.346435,1),Tupla4f(0.05375,0.05,0.06625,1),0.3);
    peonNegro->setMaterial( obsidiana );

    Material yeso = Material(Tupla4f( 	1,0.829,0.829,1),Tupla4f(0.296648,0.296648,0.296648,1),Tupla4f(0.25,0.20725,0.20725,1),0.088);
    peonBlanco->setMaterial( yeso );

    Material oro = Material(Tupla4f(0.75164,0.60648,0.22648,1),Tupla4f(0.628281,0.555802,0.366065,1),Tupla4f(0.24725,0.1995,0.0745,1),0.4);
    lingote->setMaterial( oro );

    Material predefinido = Material(Tupla4f(0.5,0.4,0.4,1),Tupla4f(0.7,0.04,0.04,1),Tupla4f(0.05,0.0,0.0,1),.078125);
    cono->setMaterial( predefinido );
    esfera->setMaterial( predefinido );
    cilindro->setMaterial( predefinido );
    tetraedro->setMaterial( predefinido );
    cubo->setMaterial( predefinido );

    // Luz direccional inicial
    luzDir = new LuzDireccional( Tupla2f( 0.0, 0.0 ), GL_LIGHT1, Tupla4f( 0.9, 0.9, 0.9, 1 ),
                                 Tupla4f( 1, 1, 1, 1 ), Tupla4f( 0.9, 0.9, 0.9, 1 ) );
    // Luz posicional blanca
    luzPos1 = new LuzPosicional( Tupla3f( 0, 200, 0 ), GL_LIGHT2, Tupla4f( 0.9, 0.9, 0.9, 1 ),
                                 Tupla4f( 1, 1, 1, 1 ), Tupla4f( 0.9, 0.9, 0.9, 1 ) );
    // Luz posicional roja
    luzPos2 = new LuzPosicional( Tupla3f( 0, 100, 0 ), GL_LIGHT3, Tupla4f( 0.9, 0, 0, 1 ),
                                 Tupla4f( 1, 0, 0, 1 ), Tupla4f( 0.9, 0, 0, 1 ) );

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



// **************************************************************************
//
// función de dibujo de la escena: limpia ventana, fija cámara, dibuja ejes,
// y dibuja los objetos
//
// **************************************************************************

void Escena::dibujar()
{
  using namespace std;
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); // Limpiar la pantalla
	change_observer();
  ejes.draw();

  if( modoIluminacion == BASICA ) {
    switch( objeto ) {

      // VISUALICACIÓN DEL OBJETO PLY
      case PLY:
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
        break;

      // VISUALIZACIÓN TODOS A LA VEZ P1
      case P1:
        if( ajedrez ) {
          glPushMatrix();
            glTranslatef( -75, 0, 0 );
            cubo->draw( modoDibujado, CHESS );
          glPopMatrix();
          glPushMatrix();
            glTranslatef( 50, 0, 0 );
            tetraedro->draw( modoDibujado, CHESS );
          glPopMatrix();
        } else {
          if( puntos ) {
            glPushMatrix();
              glTranslatef( -75, 0, 0 );
              cubo->draw( modoDibujado, POINTS );
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 50, 0, 0 );
              tetraedro->draw( modoDibujado, POINTS );
            glPopMatrix();
          }

          if( lineas ) {
            glPushMatrix();
              glTranslatef( -75, 0, 0 );
              cubo->draw( modoDibujado, LINES );
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 50, 0, 0 );
              tetraedro->draw( modoDibujado, LINES );
            glPopMatrix();
          }

          if( solido ) {
            glPushMatrix();
              glTranslatef( -75, 0, 0 );
              cubo->draw( modoDibujado, SOLID );
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 50, 0, 0 );
              tetraedro->draw( modoDibujado, SOLID );
            glPopMatrix();
          }
        break;

      // VISUALIZACIÓN DEL CILINDRO, LA ESFERA Y EL CONO
      case TODASREV:
        if( ajedrez ) {
          glPushMatrix();
            glTranslatef( -100, 0, 0 );
            if( tapa_superior and tapa_inferior )
              cilindro->draw( modoDibujado, CHESS );
            else {
              cilindro->draw_cuerpo( CHESS );
              if( tapa_superior or tapa_inferior )
                cilindro->draw_tapas( CHESS, tapa_superior, tapa_inferior );
            }
          glPopMatrix();
          if( tapa_superior and tapa_inferior )
            esfera->draw( modoDibujado, CHESS );
          else {
            esfera->draw_cuerpo( CHESS );
            if( tapa_superior or tapa_inferior )
              esfera->draw_tapas( CHESS, tapa_superior, tapa_inferior );
          }
          glPushMatrix();
            glTranslatef( 100, 0, 0 );
            if( tapa_superior and tapa_inferior )
              cono->draw( modoDibujado, CHESS );
            else {
              cono->draw_cuerpo( CHESS );
              if( tapa_superior or tapa_inferior )
                cono->draw_tapas( CHESS, tapa_superior, tapa_inferior );
            }
          glPopMatrix();
        } else {
          if( puntos ) {
            glPushMatrix();
              glTranslatef( -100, 0, 0 );
              if( tapa_superior and tapa_inferior )
                cilindro->draw( modoDibujado, POINTS );
              else {
                cilindro->draw_cuerpo( POINTS );
                if( tapa_superior or tapa_inferior )
                  cilindro->draw_tapas( POINTS, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
            if( tapa_superior and tapa_inferior )
              esfera->draw( modoDibujado, POINTS );
            else {
              esfera->draw_cuerpo( POINTS );
              if( tapa_superior or tapa_inferior )
                esfera->draw_tapas( POINTS, tapa_superior, tapa_inferior );
            }
            glPushMatrix();
              glTranslatef( 100, 0, 0 );
              if( tapa_superior and tapa_inferior )
                cono->draw( modoDibujado, POINTS );
              else {
                cono->draw_cuerpo( POINTS );
                if( tapa_superior or tapa_inferior )
                  cono->draw_tapas( POINTS, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }

          if( lineas ) {
            glPushMatrix();
              glTranslatef( -100, 0, 0 );
              if( tapa_superior and tapa_inferior )
                cilindro->draw( modoDibujado, LINES );
              else {
                cilindro->draw_cuerpo( LINES );
                if( tapa_superior or tapa_inferior )
                  cilindro->draw_tapas( LINES, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
            if( tapa_superior and tapa_inferior )
              esfera->draw( modoDibujado, LINES );
            else {
              esfera->draw_cuerpo( LINES );
              if( tapa_superior or tapa_inferior )
                esfera->draw_tapas( LINES, tapa_superior, tapa_inferior );
            }
            glPushMatrix();
              glTranslatef( 100, 0, 0 );
              if( tapa_superior and tapa_inferior )
                cono->draw( modoDibujado, LINES );
              else {
                cono->draw_cuerpo( LINES );
                if( tapa_superior or tapa_inferior )
                  cono->draw_tapas( LINES, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }

          if( solido ) {
            glPushMatrix();
              glTranslatef( -100, 0, 0 );
              if( tapa_superior and tapa_inferior )
                cilindro->draw( modoDibujado, SOLID );
              else {
                cilindro->draw_cuerpo( SOLID );
                if( tapa_superior or tapa_inferior )
                  cilindro->draw_tapas( SOLID, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
            if( tapa_superior and tapa_inferior )
              esfera->draw( modoDibujado, SOLID );
            else {
              esfera->draw_cuerpo( SOLID );
              if( tapa_superior or tapa_inferior )
                esfera->draw_tapas( SOLID, tapa_superior, tapa_inferior );
            }
            glPushMatrix();
              glTranslatef( 100, 0, 0 );
              if( tapa_superior and tapa_inferior )
                cono->draw( modoDibujado, SOLID );
              else {
                cono->draw_cuerpo( SOLID );
                if( tapa_superior or tapa_inferior )
                  cono->draw_tapas( SOLID, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }
        }
        break;

      // VISUALIZACIÓN DE LA ESCENA DE PRUEBA DE LA PRÁCTICA 3
      case P3:
        if( ajedrez ) {
          glPushMatrix();
            glTranslatef( -100, 0, 0 );
            glScalef( 50, 50, 50 );
            if( tapa_superior and tapa_inferior )
              peonNegro->draw( modoDibujado, CHESS );
            else {
              peonNegro->draw_cuerpo( CHESS );
              if( tapa_superior or tapa_inferior )
                peonNegro->draw_tapas( CHESS, tapa_superior, tapa_inferior );
            }
          glPopMatrix();
          glPushMatrix();
            glTranslatef( 0, -75, 0 );
            glScalef( 1, 1, 2.5 );
            lingote -> draw( modoDibujado, CHESS );
          glPopMatrix();
          glPushMatrix();
            glTranslatef( 100, 0, 0 );
            glScalef( 50, 50, 50 );
            if( tapa_superior and tapa_inferior )
              peonBlanco->draw( modoDibujado, CHESS );
            else {
              peonBlanco->draw_cuerpo( CHESS );
              if( tapa_superior or tapa_inferior )
                peonBlanco->draw_tapas( CHESS, tapa_superior, tapa_inferior );
            }
          glPopMatrix();
        } else {
          if( puntos ) {
            glPushMatrix();
              glTranslatef( -100, 0, 0 );
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                peonNegro->draw( modoDibujado, POINTS );
              else {
                peonNegro->draw_cuerpo( POINTS );
                if( tapa_superior or tapa_inferior )
                  peonNegro->draw_tapas( POINTS, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 0, -75, 0 );
              glScalef( 1, 1, 2.5 );
              lingote -> draw( modoDibujado, POINTS );
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 100, 0, 0 );
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                peonBlanco->draw( modoDibujado, POINTS );
              else {
                peonBlanco->draw_cuerpo( POINTS );
                if( tapa_superior or tapa_inferior )
                  peonBlanco->draw_tapas( POINTS, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }

          if( lineas ) {
            glPushMatrix();
              glTranslatef( -100, 0, 0 );
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                peonNegro->draw( modoDibujado, LINES );
              else {
                peonNegro->draw_cuerpo( LINES );
                if( tapa_superior or tapa_inferior )
                  peonNegro->draw_tapas( LINES, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 0, -75, 0 );
              glScalef( 1, 1, 2.5 );
              lingote -> draw( modoDibujado, LINES );
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 100, 0, 0 );
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                peonBlanco->draw( modoDibujado, LINES );
              else {
                peonBlanco->draw_cuerpo( LINES );
                if( tapa_superior or tapa_inferior )
                  peonBlanco->draw_tapas( LINES, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }

          if( solido ) {
            glPushMatrix();
              glTranslatef( -100, 0, 0 );
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                peonNegro->draw( modoDibujado, SOLID );
              else {
                peonNegro->draw_cuerpo( SOLID );
                if( tapa_superior or tapa_inferior )
                  peonNegro->draw_tapas( SOLID, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 0, -75, 0 );
              glScalef( 1, 1, 2.5 );
              lingote -> draw( modoDibujado, SOLID );
            glPopMatrix();
            glPushMatrix();
              glTranslatef( 100, 0, 0 );
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                peonBlanco->draw( modoDibujado, SOLID );
              else {
                peonBlanco->draw_cuerpo( SOLID );
                if( tapa_superior or tapa_inferior )
                  peonBlanco->draw_tapas( SOLID, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }
        }
        break;

      // VISUALIZACIÓN DEL OBJETO DE REVOLUCIÓN PLY
      case REVOLUCION:
        if( ajedrez ) {
          glPushMatrix();
            glScalef( 50, 50, 50 );
            if( tapa_superior and tapa_inferior )
              objetoRevolucion->draw( modoDibujado, CHESS );
            else {
              objetoRevolucion->draw_cuerpo( CHESS );
              if( tapa_superior or tapa_inferior )
                objetoRevolucion->draw_tapas( CHESS, tapa_superior, tapa_inferior );
            }
          glPopMatrix();
        } else {
          if( puntos ) {
            glPushMatrix();
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                objetoRevolucion->draw( modoDibujado, POINTS );
              else {
                objetoRevolucion->draw_cuerpo( POINTS );
                if( tapa_superior or tapa_inferior )
                  objetoRevolucion->draw_tapas( POINTS, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }

          if( lineas ) {
            glPushMatrix();
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                objetoRevolucion->draw( modoDibujado, LINES );
              else {
                objetoRevolucion->draw_cuerpo( LINES );
                if( tapa_superior or tapa_inferior )
                  objetoRevolucion->draw_tapas( LINES, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }

          if( solido ) {
            glPushMatrix();
              glScalef( 50, 50, 50 );
              if( tapa_superior and tapa_inferior )
                objetoRevolucion->draw( modoDibujado, SOLID );
              else {
                objetoRevolucion->draw_cuerpo( SOLID );
                if( tapa_superior or tapa_inferior )
                  objetoRevolucion->draw_tapas( SOLID, tapa_superior, tapa_inferior );
              }
            glPopMatrix();
          }
        }
        break;

      // VISUALICACIÓN DEL CILINDRO
      case CILINDRO:
        if( ajedrez ) {
          if( tapa_superior and tapa_inferior )
            cilindro->draw( modoDibujado, CHESS );
          else {
            cilindro->draw_cuerpo( CHESS );
            if( tapa_superior or tapa_inferior )
              cilindro->draw_tapas( CHESS, tapa_superior, tapa_inferior );
          }
        } else {
          if( puntos ) {
            if( tapa_superior and tapa_inferior )
              cilindro->draw( modoDibujado, POINTS );
            else {
              cilindro->draw_cuerpo( POINTS );
              if( tapa_superior or tapa_inferior )
                cilindro->draw_tapas( POINTS, tapa_superior, tapa_inferior );
            }
          }
          if( lineas ) {
            if( tapa_superior and tapa_inferior )
              cilindro->draw( modoDibujado, LINES );
            else {
              cilindro->draw_cuerpo( LINES );
              if( tapa_superior or tapa_inferior )
                cilindro->draw_tapas( LINES, tapa_superior, tapa_inferior );
            }
          }
          if( solido ) {
            if( tapa_superior and tapa_inferior )
              cilindro->draw( modoDibujado, SOLID );
            else {
              cilindro->draw_cuerpo( SOLID );
              if( tapa_superior or tapa_inferior )
                cilindro->draw_tapas( SOLID, tapa_superior, tapa_inferior );
            }
          }
        }
        break;

      // VISUALICACIÓN DE LA ESFERA
      case ESFERA:
        if( ajedrez ) {
          if( tapa_superior and tapa_inferior )
            esfera->draw( modoDibujado, CHESS );
          else {
            esfera->draw_cuerpo( CHESS );
            if( tapa_superior or tapa_inferior )
              esfera->draw_tapas( CHESS, tapa_superior, tapa_inferior );
          }
        } else {
          if( puntos ) {
            if( tapa_superior and tapa_inferior )
              esfera->draw( modoDibujado, POINTS );
            else {
              esfera->draw_cuerpo( POINTS );
              if( tapa_superior or tapa_inferior )
                esfera->draw_tapas( POINTS, tapa_superior, tapa_inferior );
            }
          }
          if( lineas ) {
            if( tapa_superior and tapa_inferior )
              esfera->draw( modoDibujado, LINES );
            else {
              esfera->draw_cuerpo( LINES );
              if( tapa_superior or tapa_inferior )
                esfera->draw_tapas( LINES, tapa_superior, tapa_inferior );
            }
          }
          if( solido ) {
            if( tapa_superior and tapa_inferior )
              esfera->draw( modoDibujado, SOLID );
            else {
              esfera->draw_cuerpo( SOLID );
              if( tapa_superior or tapa_inferior )
                esfera->draw_tapas( SOLID, tapa_superior, tapa_inferior );
            }
          }
        }
        break;

      // VISUALICACIÓN DEL CONO
      case CONO:
      if( ajedrez ) {
        if( tapa_superior and tapa_inferior )
          cono->draw( modoDibujado, CHESS );
        else {
          cono->draw_cuerpo( CHESS );
          if( tapa_superior or tapa_inferior )
            cono->draw_tapas( CHESS, tapa_superior, tapa_inferior );
        }
      } else {
        if( puntos ) {
          if( tapa_superior and tapa_inferior )
            cono->draw( modoDibujado, POINTS );
          else {
            cono->draw_cuerpo( POINTS );
            if( tapa_superior or tapa_inferior )
              cono->draw_tapas( POINTS, tapa_superior, tapa_inferior );
          }
        }
        if( lineas ) {
          if( tapa_superior and tapa_inferior )
            cono->draw( modoDibujado, LINES );
          else {
            cono->draw_cuerpo( LINES );
            if( tapa_superior or tapa_inferior )
              cono->draw_tapas( LINES, tapa_superior, tapa_inferior );
          }
        }
        if( solido ) {
          if( tapa_superior and tapa_inferior )
            cono->draw( modoDibujado, SOLID );
          else {
            cono->draw_cuerpo( SOLID );
            if( tapa_superior or tapa_inferior )
              cono->draw_tapas( SOLID, tapa_superior, tapa_inferior );
          }
        }
      }
      break;

      }
    }
  } else {    // Visualización con iluminación

    if( glIsEnabled( GL_LIGHT1 ) ) {
      Tupla3f luzpos = luzDir->getPosicion();
      float x = luzpos(0);
      float y = luzpos(1);
      float z = luzpos(2);

      glPushMatrix();
        glTranslatef( x, y, z );
        luz->draw( modoDibujado, SOLID );
      glPopMatrix();
    }

    glEnable( GL_LIGHTING );

    if( modoIluminacion == PLANA )
      glShadeModel( GL_FLAT );
    else
      glShadeModel( GL_SMOOTH );

    if( glIsEnabled( GL_LIGHT1 ) )
      luzDir->aplicar();
    if( glIsEnabled( GL_LIGHT2 ) )
      luzPos1->aplicar();
    if( glIsEnabled( GL_LIGHT3 ) )
      luzPos2->aplicar();

    switch( objeto ) {
      case P1:
        glPushMatrix();
          glTranslatef( -75, 0, 0 );
          cubo->draw( modoDibujado, SOLID );
        glPopMatrix();
        glPushMatrix();
          glTranslatef( 50, 0, 0 );
          tetraedro->draw( modoDibujado, SOLID );
        glPopMatrix();
        break;

      case TODASREV:
        glPushMatrix();
          glTranslatef( -100, 0, 0 );
          if( tapa_superior and tapa_inferior )
            cilindro->draw( modoDibujado, SOLID );
          else {
            cilindro->draw_cuerpo( SOLID );
            if( tapa_superior or tapa_inferior )
              cilindro->draw_tapas( SOLID, tapa_superior, tapa_inferior );
          }
        glPopMatrix();
        if( tapa_superior and tapa_inferior )
          esfera->draw( modoDibujado, SOLID );
        else {
          esfera->draw_cuerpo( SOLID );
          if( tapa_superior or tapa_inferior )
            esfera->draw_tapas( SOLID, tapa_superior, tapa_inferior );
        }
        glPushMatrix();
          glTranslatef( 100, 0, 0 );
          if( tapa_superior and tapa_inferior )
            cono->draw( modoDibujado, SOLID );
          else {
            cono->draw_cuerpo( SOLID );
            if( tapa_superior or tapa_inferior )
              cono->draw_tapas( SOLID, tapa_superior, tapa_inferior );
          }
        glPopMatrix();
        break;

      case P3:
        glPushMatrix();
          glTranslatef( -100, 0, 0 );
          glScalef( 50, 50, 50 );
          if( tapa_superior and tapa_inferior )
            peonNegro->draw( modoDibujado, SOLID );
          else {
            peonNegro->draw_cuerpo( SOLID );
            if( tapa_superior or tapa_inferior )
              peonNegro->draw_tapas( SOLID, tapa_superior, tapa_inferior );
          }
        glPopMatrix();
        glPushMatrix();
          glTranslatef( 0, -75, 0 );
          glScalef( 1, 1, 2.5 );
          lingote -> draw( modoDibujado, SOLID );
        glPopMatrix();
        glPushMatrix();
          glTranslatef( 100, 0, 0 );
          glScalef( 50, 50, 50 );
          if( tapa_superior and tapa_inferior )
            peonBlanco->draw( modoDibujado, SOLID );
          else {
            peonBlanco->draw_cuerpo( SOLID );
            if( tapa_superior or tapa_inferior )
              peonBlanco->draw_tapas( SOLID, tapa_superior, tapa_inferior );
          }
        glPopMatrix();
        break;

      case PLY:
        glPushMatrix();
          glScalef( 10, 10, 10 );
          objetoPLY->draw( modoDibujado, SOLID );
        glPopMatrix();
        break;

      case REVOLUCION:
        glPushMatrix();
          glScalef( 50, 50, 50 );
          if( tapa_superior and tapa_inferior )
            objetoRevolucion->draw( modoDibujado, SOLID );
          else {
            objetoRevolucion->draw_cuerpo( SOLID );
            if( tapa_superior or tapa_inferior )
              objetoRevolucion->draw_tapas( SOLID, tapa_superior, tapa_inferior );
          }
        glPopMatrix();
        break;

      case CILINDRO:
        if( tapa_superior and tapa_inferior )
          cilindro->draw( modoDibujado, SOLID );
        else {
          cilindro->draw_cuerpo( SOLID );
          if( tapa_superior or tapa_inferior )
            cilindro->draw_tapas( SOLID, tapa_superior, tapa_inferior );
        }
        break;

      case ESFERA:
        if( tapa_superior and tapa_inferior )
          esfera->draw( modoDibujado, SOLID );
        else {
          esfera->draw_cuerpo( SOLID );
          if( tapa_superior or tapa_inferior )
            esfera->draw_tapas( SOLID, tapa_superior, tapa_inferior );
        }
        break;

      case CONO:
        if( tapa_superior and tapa_inferior )
          cono->draw( modoDibujado, SOLID );
        else {
          cono->draw_cuerpo( SOLID );
          if( tapa_superior or tapa_inferior )
            cono->draw_tapas( SOLID, tapa_superior, tapa_inferior );
        }
        break;
    }


    glDisable( GL_LIGHTING );

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
        default:
          cout << "ERROR - opciones disponibles:\n'O': Cambiar objeto\n"
               << "'V': Cambiar modo de visualización\n'D': Cambiar modo de dibujado\n"
               << "'T': Cambiar visualización de tapas\n'Q': Salir\n";
          break;
      }

      break;

    case SELOBJETO:

      switch( toupper( tecla ) ) {
        case 'Q':
          modoMenu = NADA;
          break;
        case '1':
          objeto = P1;
          modoMenu = NADA;
          break;
        case '2':
          objeto = TODASREV;
          modoMenu = NADA;
          break;
        case '3':
          objeto = P3;
          modoMenu = NADA;
          break;
        case 'A':
          objeto = CILINDRO;
          modoMenu = NADA;
          break;
        case 'B':
          objeto = ESFERA;
          modoMenu = NADA;
          break;
        case 'C':
          objeto = CONO;
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
          cout << "ERROR - opciones disponibles:\n'1': Práctica 1\n'2': Práctica 2\n"
               << "'3': Práctica 3\n'A': Cilindro\n'B': Esfera\n'C': Cono\n"
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
