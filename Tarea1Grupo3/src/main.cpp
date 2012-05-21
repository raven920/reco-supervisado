#include <QtGui/QApplication>
#include "mainwindow.h"
#include "Imagen/imagenCv.h"

int main(int argc, char *argv[])
{
    //Instruccion propia del qt.
    QApplication a(argc, argv);

    //Se crean los objetos tipo ImagenCv que guardaran la captura de la camara y el fondo por el que se debe cambiar
    ImagenCv captura1;
    ImagenCv cambio;

    //Se carga la imagen que se va a utilizar para cambiar los pixeles
    cambio.cargarImagen("imagen.jpg");

    //Se crea un ciclo infinito para actualizar la info de la camara
    while( 1 ) {

        //Se captura la camara en cada ciclo del while para actualizarla
        captura1.capturarCamara();

        //Se recorre cada pixel de cada fotograma por medio de un ciclo anidado
        for (int i = 0; i < captura1.ancho; i++) {
            for (int j = 0; j < captura1.alto; j++) {

                //Se obtiene el valor de los 3 colores de cada pixel y se guarda en variables
                int valorCaptura0 = captura1.obtenerColor(i,j,0);
                int valorCaptura1 = captura1.obtenerColor(i,j,1);
                int valorCaptura2 = captura1.obtenerColor(i,j,2);

                //Se compara si la combinacion de los colores hacen un tono entre los valores indicados
                if(valorCaptura0 > 120 && valorCaptura1 < 100 && valorCaptura2 > 100){
                    int x = i%cambio.ancho;
                    int y = j%cambio.alto;
                    //Si es verdadero se toman los colores de la posicion actual en el fondo que vamos a poner adelante
                    int valorFondo0 = cambio.obtenerColor(x,y,0);
                    int valorFondo1 = cambio.obtenerColor(x,y,1);
                    int valorFondo2 = cambio.obtenerColor(x,y,2);

                    //Luego de tomar los valores se remplazan por el color del pixel que ha sido seleccionado
                    captura1.establecerColor(i,j,0,valorFondo0);
                    captura1.establecerColor(i,j,1,valorFondo1);
                    captura1.establecerColor(i,j,2,valorFondo2);

                }//Fin del if

            }//Fin del ciclo que recorre las Y
        }//Fin del ciclo que recorre las X

        //Se muestra la imagen en la pantalla y se crea un delay de 33.
        captura1.mostrarImagen("Captura");
        cvWaitKey( 33 );
    }//Fin del ciclo de actualizacion
}//Fin del main
