#include "imagenCv.h"


/******************************************************************************************
Constructores
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
ImagenCv::ImagenCv()  {
    imagenCv = NULL;
    captura  = NULL;
    ventana  = false;
}

ImagenCv::ImagenCv(ImagenCv* pImagen) {

    ImagenCv::crearImagen(pImagen->obtenerImagen());
    ImagenCv::establecerImagen(pImagen->obtenerImagen());
    ventana = false;
    captura  = NULL;
}

ImagenCv::ImagenCv(IplImage* pImagen) {

    ImagenCv::crearImagen(pImagen);
    ImagenCv::establecerImagen(pImagen);
    ventana = false;
    captura  = NULL;
}

ImagenCv::ImagenCv(int pCamara){

    imagenCv= NULL;
    ventana = false;
    ImagenCv::capturarCamara(pCamara);
}

ImagenCv::ImagenCv(int pAlto, int pAncho, int pCanales){

    imagenCv = cvCreateImage( cvSize( pAlto, pAncho ), IPL_DEPTH_8U, pCanales );
    datosImagen = (uchar*)imagenCv->imageData;
    alto = imagenCv->height;
    ancho = imagenCv->width;
    canales = imagenCv->nChannels;
    ventana = false;
    captura  = NULL;
}

ImagenCv::ImagenCv(const char* pArchivo, int pBandera){

    imagenCv = cvLoadImage(pArchivo,pBandera);
    datosImagen = (uchar*)imagenCv->imageData;
    alto = imagenCv->height;
    ancho = imagenCv->width;
    canales = imagenCv->nChannels;
    ventana = false;
    captura  = NULL;
}

ImagenCv::ImagenCv(const char* pArchivo){

    imagenCv = cvLoadImage(pArchivo,-1);
    datosImagen = (uchar*)imagenCv->imageData;
    alto = imagenCv->height;
    ancho = imagenCv->width;
    canales = imagenCv->nChannels;
    ventana = false;
    captura  = NULL;
}

void ImagenCv::operator = (ImagenCv pImagen) {

    establecerImagen(&pImagen);
}

/******************************************************************************************
Destructores
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/

ImagenCv::~ImagenCv() {

    if(ventana != false){
        cvDestroyAllWindows();
    }

    if(imagenCv != NULL){
        cvReleaseImage(&imagenCv);
    }


    if(captura){
        cvReleaseCapture(&captura);
    }

}

void ImagenCv::destruirVentana(){

    if (!ventana){
        qDebug()<<"No existe una ventana que destruir";
        return;
    }
    cvDestroyAllWindows;
}

void ImagenCv::destruirImagen(){

    if(!imagenCv){
        qDebug()<<"No existe una imagen que destruir";
        return;
    }
    cvReleaseImage(&imagenCv);
}

void ImagenCv::destruirCaptura(){

    if(!captura){
        qDebug()<<"No existe una captura que destruir";
        return;
    }
    cvReleaseCapture(&captura);
}

/******************************************************************************************
Setters
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
void ImagenCv::establecerImagen(ImagenCv* pImagen) {

    ImagenCv::establecerImagen(pImagen->obtenerImagen());
}

void ImagenCv::establecerImagen(IplImage* pImagen) {

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){
        inicializar(pImagen);
    }

    if( ancho != pImagen->width || alto != pImagen->height || canales != pImagen->nChannels){

        qDebug()<<"Las dimensiones no coinciden";
        return;
    }

    cvCopy(pImagen, imagenCv);

}

void ImagenCv::establecerImagen(IplImage* pImagen, int pInicialX, int pInicialY, int pFinalX, int pFinalY){

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){

        ancho= pFinalX-pInicialX+1;
        alto = pFinalY-pInicialY+1;
        canales = pImagen->nChannels;

        crearImagen(ancho, alto, canales);
    }

    if( ancho > pImagen->width || alto > pImagen->height || canales != pImagen->nChannels){

        qDebug()<<"Las dimensiones no coinciden";
        return;
    }

    uchar* datosTemporales  = (uchar*)pImagen->imageData;

    int i1=0;
    int j1=0;

    for (int i= pInicialX; i<= pFinalX; i++){
        for(int j= pInicialY; j<= pFinalY; j++){

            datosImagen     [j1*imagenCv->widthStep + i1*imagenCv->nChannels + 0] =
            datosTemporales [j*pImagen->widthStep   + i*pImagen->nChannels  + 0] ;

            datosImagen     [j1*imagenCv->widthStep + i1*imagenCv->nChannels + 1] =
            datosTemporales [j*pImagen->widthStep   + i*pImagen->nChannels  + 1] ;

            datosImagen     [j1*imagenCv->widthStep + i1*imagenCv->nChannels + 2] =
            datosTemporales [j*pImagen->widthStep   + i*pImagen->nChannels  + 2] ;

            j1++;
        }

        j1=0;
        i1++;
    }


}

void ImagenCv::establecerImagen(ImagenCv* pImagen, int pInicialX, int pInicialY, int pFinalX, int pFinalY){

    establecerImagen( pImagen->obtenerImagen(), pInicialX, pInicialY, pFinalX, pFinalY );
}

void ImagenCv::establecerColor(int pX, int pY, int pCanal, int pValor){

    if (pX < 0 || pY < 0 || pX > imagenCv->width || pY > imagenCv->height || pCanal > canales) {

        pX=0; pY=0;

        if(modoDepuracion == true){

            qDebug()<<"Advertencia X y/o Y tiene(n) un valor por fuera de la imagen";
        }
    }

    datosImagen [pY*imagenCv->widthStep + pX*imagenCv->nChannels + pCanal] = pValor;
}

void ImagenCv::establecerDepuracion(bool pActivo){

    modoDepuracion= pActivo;
}

/******************************************************************************************
Getters
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
IplImage* ImagenCv::obtenerImagen(){

    return imagenCv;
}

uchar* ImagenCv::obtenerInformacion () {

    return datosImagen;
}

CvCapture* ImagenCv::obtenerCaptura(){

    return captura;
}

int ImagenCv::obtenerColor(int pX, int pY, int pCanal){

    if (pX < 0 || pY < 0 || pX > imagenCv->width || pY > imagenCv->height || pCanal > canales) {

        canal1=0;
        if (modoDepuracion == true){

            qDebug()<<"Advertencia no existe información en esta posición";
        }
    }

    canal1 = datosImagen [pY*imagenCv->widthStep + pX*imagenCv->nChannels + pCanal];
    return canal1;

}



/******************************************************************************************
Conversiones
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
void ImagenCv::RGBaHSV() {

    if (imagenCv == NULL){
        qDebug()<<"No se puede convertir una imagen vacia";
        return;
    }
    cvCvtColor ( imagenCv, imagenCv, CV_RGB2HSV);
}

void ImagenCv::RGBaHSV (ImagenCv* pImagen ) {

    ImagenCv::RGBaHSV(pImagen->obtenerImagen());
}

void ImagenCv::RGBaHSV (IplImage* pImagen) {

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){
        ImagenCv::inicializar(pImagen);
    }

    if( ancho != pImagen->width || alto != pImagen->height || canales != pImagen->nChannels){

        qDebug()<<"Las dimensiones no coinciden";
        return;
    }

    cvCvtColor ( pImagen, imagenCv, CV_RGB2HSV);
}

void ImagenCv::RGBaGrises (ImagenCv* pImagen ){

    ImagenCv::RGBaGrises(pImagen->obtenerImagen());
}

void ImagenCv::RGBaGrises (IplImage* pImagen) {

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){

        imagenCv = cvCreateImage( cvGetSize(pImagen), 8, 1 );
        datosImagen = (uchar*)imagenCv->imageData;
        ancho = pImagen->width;
        alto = pImagen->height;
        canales =1;
    }

    if( ancho != pImagen->width || alto != pImagen->height || canales != 1){

        qDebug()<<"Las dimensiones no coinciden";
        return;
    }

    cvCvtColor ( pImagen, imagenCv,  CV_RGB2GRAY);
}

void ImagenCv::GrisesaRGV (ImagenCv* pImagen) {
    GrisesaRGV(pImagen->obtenerImagen());
}


void ImagenCv::GrisesaRGV (IplImage* pImagen) {

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){

        qDebug()<<"Inicializando Gris2RGB";
        imagenCv = cvCreateImage( cvGetSize(pImagen), 8, 3 );
        datosImagen = (uchar*)imagenCv->imageData;
        ancho = pImagen->width;
        alto = pImagen->height;
        canales =3;
    }

    if( ancho != pImagen->width || alto != pImagen->height || canales != 3){

        qDebug()<<"Las dimensiones no coinciden";
        return;
    }

    cvCvtColor ( pImagen, imagenCv,  CV_GRAY2RGB);
}

void ImagenCv::escalarImagen(IplImage* pImagen) {

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){
        ImagenCv::inicializar(pImagen);
    }

    cvResize(pImagen,imagenCv,CV_INTER_CUBIC);
}

void ImagenCv::escalarImagen(ImagenCv* pImagen){

    escalarImagen(pImagen->obtenerImagen());
}

void ImagenCv::escalarImagen(IplImage* pImagen, int pAncho, int pAlto) {

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (imagenCv == NULL){
        crearImagen(pAncho, pAlto, pImagen->nChannels);
    }

    if( ancho != pAncho || alto != pAlto || canales != pImagen->nChannels){

        qDebug()<<"Las dimensiones no coinciden";
        return;
    }

    cvResize(pImagen,imagenCv,CV_INTER_CUBIC);
}

void ImagenCv::escalarImagen(ImagenCv* pImagen, int pAncho, int pAlto) {
    escalarImagen(pImagen->obtenerImagen(), pAncho, pAlto);
}

/******************************************************************************************
Entradas
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
void ImagenCv::capturarCamara(int pCamara){

    if (imagenCv == NULL){

        qDebug()<<"Inicializando camara";
        captura = cvCaptureFromCAM(pCamara);
        if( captura ) {
            qDebug()<<"La cámara ha sido leida con exito";
        } else {
            qDebug()<<"Problemas leyendo la cámara";
            return;
        }

        imagenCv = cvQueryFrame(captura);
        datosImagen = (uchar*)imagenCv->imageData;
        ancho = imagenCv->width;
        alto = imagenCv->height;
        canales = imagenCv->nChannels;
    }

    imagenCv = cvQueryFrame(captura);
}

void ImagenCv::capturarCamara(){

    ImagenCv::capturarCamara(0);

}

void ImagenCv::cargarImagen(const char* pFile, int pBandera){

    imagenCv = cvLoadImage(pFile,pBandera);
    datosImagen = (uchar*)imagenCv->imageData;
    ancho = imagenCv->width;
    alto = imagenCv->height;
    canales = imagenCv->nChannels;
}

void ImagenCv::cargarImagen(const char* pFile){

    imagenCv = cvLoadImage(pFile,-1);
    datosImagen = (uchar*)imagenCv->imageData;
    ancho = imagenCv->width;
    alto = imagenCv->height;
    canales = imagenCv->nChannels;
}

void ImagenCv::crearImagen(ImagenCv* pImagen){

    ImagenCv::crearImagen(pImagen->obtenerImagen());
}

void ImagenCv::crearImagen(IplImage* pImagen){

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    ancho = pImagen->width;
    alto = pImagen->height;
    canales = pImagen->nChannels;

    imagenCv = cvCreateImage( cvGetSize(pImagen), 8, canales );
    datosImagen = (uchar*)imagenCv->imageData;
}

void ImagenCv::crearImagen(int pAncho, int pAlto, int pCanales){

    imagenCv = cvCreateImage( cvSize( pAncho, pAlto ), IPL_DEPTH_8U, pCanales );
    datosImagen = (uchar*)imagenCv->imageData;
    ancho = imagenCv->width;
    alto = imagenCv->height;
    canales = imagenCv->nChannels;
}

void ImagenCv::crearImagen(int pAncho, int pAlto, int pNumeroCanales, int pProfundidad){

    switch (pProfundidad){

        case 1:
        imagenCv = cvCreateImage( cvSize( pAncho, pAlto ), IPL_DEPTH_1U, pNumeroCanales );
        break;

        case 8:
        imagenCv = cvCreateImage( cvSize( pAncho, pAlto ), IPL_DEPTH_8U, pNumeroCanales );
        break;

        case 16:
        imagenCv = cvCreateImage( cvSize( pAncho, pAlto ), IPL_DEPTH_16U, pNumeroCanales );
        break;

        default:
        qDebug()<<"Profundidad no valida";
        return;
    }

    datosImagen = (uchar*)imagenCv->imageData;
    ancho = imagenCv->width;
    alto = imagenCv->height;
    canales = imagenCv->nChannels;

}

/******************************************************************************************
Salidas
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
void ImagenCv::mostrarImagen(const char* pVentana) {

    if (imagenCv == NULL){
        qDebug()<<"No es posible mostrar una imagen vacia";
        return;
    }

    if (ventana = false){
        cvNamedWindow(pVentana, CV_WINDOW_AUTOSIZE);
        ventana = true;
    }

    cvShowImage(pVentana, imagenCv);
}

void ImagenCv::guardarImagen(const char* pNombreArchivo){

    cvSaveImage( pNombreArchivo, imagenCv );
}


/******************************************************************************************
Inicialización
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
void ImagenCv::inicializar(IplImage* pImagen){

    if (pImagen == NULL){
        qDebug()<<"No ha sido posible inicializar debido a que la imagen de entrada esta vacia";
        return;
    }

    ancho = pImagen->width;
    alto = pImagen->height;
    canales =pImagen->nChannels;

    imagenCv = cvCreateImage( cvSize( ancho, alto ), 8, pImagen->nChannels );
    datosImagen = (uchar*)imagenCv->imageData;

}


/******************************************************************************************
Filtros
Autor: Giovanny Espinal Ramirez
Descripcion:
******************************************************************************************/
void ImagenCv::filtroForma(int pErosion, int pDilatacion){

    if (canales != 1){
        qDebug()<<"Solo puede aplicarle el filtro a imagenes monocromaticas o en escala de grises";
        return;
    }

    if (pErosion > 0){
        cvErode  ( imagenCv , imagenCv , 0 , pErosion    );
    }
    if (pDilatacion > 0){
        cvDilate ( imagenCv , imagenCv , 0 , pDilatacion );
    }
}

void ImagenCv::filtroForma(int pErosion, int pDilatacion, IplImage* pImagen){

    if (canales != 1){
        qDebug()<<"Solo puede aplicarle el filtro a imagenes monocromaticas o en escala de grises";
        return;
    }

    if (pErosion > 0){
        cvErode  ( pImagen , imagenCv , 0 , pErosion    );
    }
    if (pDilatacion > 0){
        cvDilate ( pImagen , imagenCv , 0 , pDilatacion );
    }
}

void ImagenCv::filtroForma(int pErosion, int pDilatacion, ImagenCv* pImagen){

    if (canales != 1){
        qDebug()<<"Solo puede aplicarle el filtro a imagenes monocromaticas o en escala de grises";
        return;
    }

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    if (pErosion > 0){
        cvErode  ( pImagen->obtenerImagen() , imagenCv , 0 , pErosion    );
    }
    if (pDilatacion > 0){
        cvDilate ( pImagen->obtenerImagen() , imagenCv , 0 , pDilatacion );
    }
}

void ImagenCv::filtroBordes(int pUmbral1, int pUmbral2){

    if (canales != 1){
        qDebug()<<"Solo puede aplicarle el filtro a imagenes monocromaticas o en escala de grises";
        return;
    }

    cvCanny(imagenCv, imagenCv, pUmbral1, pUmbral2 );
}

void ImagenCv::filtroBordes(int pUmbral1, int pUmbral2, ImagenCv* pImagen){

    ImagenCv::filtroBordes(pUmbral1, pUmbral2, pImagen->obtenerImagen());
}

void ImagenCv::filtroBordes(int pUmbral1, int pUmbral2, IplImage* pImagen){

    if (canales != 1){
        qDebug()<<"Solo puede aplicarle el filtro a imagenes monocromaticas o en escala de grises";
        return;
    }

    if (pImagen == NULL){
        qDebug()<<"La imagen recibida como parametro esta vacia";
        return;
    }

    cvCanny(pImagen, imagenCv, pUmbral1, pUmbral2 );
}

