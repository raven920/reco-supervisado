#ifndef IMAGENCV_H
#define IMAGENCV_H
#include <highgui.h>
#include <cv.h>
#include <qdebug.h>

class ImagenCv
{

public:

    /******************************************************************************************
    Constructores
    ******************************************************************************************/
    ImagenCv();
    ImagenCv(IplImage* pImagen);
    ImagenCv(ImagenCv* pImagen);
    ImagenCv(int pCamara);
    ImagenCv(int pAlto, int pAncho, int pCanales);
    ImagenCv(const char* pArchivo, int pBandera);
    ImagenCv(const char* pArchivo);

    void operator = (ImagenCv pImagen);

    /******************************************************************************************
    Destructores
    ******************************************************************************************/
    ~ImagenCv();
    void destruirVentana();
    void destruirImagen();
    void destruirCaptura();


    /******************************************************************************************
    Setters
    ******************************************************************************************/
    void establecerImagen(IplImage* pImagen);
    void establecerImagen(ImagenCv* pImagen);

    void establecerImagen(IplImage* pImagen, int pInicialX, int pInicialY, int pFinalX, int pFinalY);
    void establecerImagen(ImagenCv* pImagen, int pInicialX, int pInicialY, int pFinalX, int pFinalY);

    void establecerColor(int pX, int pY, int pCanal, int pValor);
    void establecerDepuracion(bool pActivo);


    /******************************************************************************************
    Getters
    ******************************************************************************************/
    IplImage*  obtenerImagen();
    uchar*     obtenerInformacion();
    CvCapture* obtenerCaptura();

    int obtenerColor(int pX, int pY, int pCanal);

    int obtenerCanales();
    int obtenerAlto();
    int obtenerAncho();


    /******************************************************************************************
    Entradas
    ******************************************************************************************/
    void capturarCamara (int pCamara);
    void capturarCamara ();

    void cargarImagen (const char* pArchivo, int pBandera);
    void cargarImagen (const char* pArchivo);
    void cargarVideo (); //Futuro uso

    void crearImagen(ImagenCv* pImagen);
    void crearImagen(IplImage* pImagen);
    void crearImagen(int pAncho, int pAlto, int pNumeroCanales);
    void crearImagen(int pAncho, int pAlto, int pNumeroCanales, int pProfundidad); //Futuro uso


    /******************************************************************************************
    Salidas
    ******************************************************************************************/
    void mostrarImagen(const char* pVentana);
    void guardarImagen(const char* pNombreArchivo);


    /******************************************************************************************
    Conversiones
    ******************************************************************************************/
    void RGBaHSV();
    void RGBaHSV(ImagenCv* pImagen);
    void RGBaHSV(IplImage* pImagen);
    void RGBaGrises(ImagenCv* pImagen);
    void RGBaGrises(IplImage* pImagen);
    void GrisesaRGV(ImagenCv* pImagen);
    void GrisesaRGV(IplImage* pImagen);

    void escalarImagen(IplImage* pImagen);
    void escalarImagen(ImagenCv* pImagen);
    void escalarImagen(IplImage* pImagen, int pAncho, int pAlto);
    void escalarImagen(ImagenCv* pImagen, int pAncho, int pAlto);
    void escalarImagen(int pAncho, int pAlto); //Futuro uso


    /******************************************************************************************
    Filtros
    ******************************************************************************************/
    void filtroForma(int pErosion, int pDilatacion);
    void filtroForma(int pErosion, int pDilatacion, IplImage* pImagen);
    void filtroForma(int pErosion, int pDilatacion, ImagenCv* pImagen);

    void filtroBordes(int pUmbral1, int pUmbral2);
    void filtroBordes(int pUmbral1, int pUmbral2, IplImage* pImagen);
    void filtroBordes(int pUmbral1, int pUmbral2, ImagenCv* pImagen);


    /******************************************************************************************
    //Atributos publicos
    ******************************************************************************************/
    int ancho;
    int alto;
    int canales;


private:

    /******************************************************************************************
    //Metodos privados
    ******************************************************************************************/
    void inicializar(IplImage* pImagen);

    /******************************************************************************************
    //Atributos de la imagen
    ******************************************************************************************/
    IplImage*  imagenCv;
    CvCapture* captura;
    uchar*     datosImagen;

    int canal1;
    int canal2;
    int canal3;

    bool ventana;
    bool modoDepuracion;

};

#endif // IMAGENCV_H
