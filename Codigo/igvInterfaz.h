#ifndef __IGVINTERFAZ
#define __IGVINTERFAZ

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#endif

#include <string>
#include <playsoundapi.h>
#include <iostream>
using namespace std;

#include "igvEscena3D.h"
#include "igvCamara.h"

using namespace std;

typedef enum {
	visualizar,
	seleccionar
} modoInterfaz;

typedef enum {
	BALA,
	FLECHA,
	ENEMIGOS,
	REYES
} tipoAnimacion;

typedef enum {
	NADA,
	CONSTRUIRCA�ON,
	CONSTRUIRTORRE,
	MEJORARCA�ON,
	MEJORARTORRE,
	VENDERCA�ON,
	VENDERTORRE,
	SALIR
} accionMenu;

typedef enum {
	DISPAROCA�ON,
	DISPAROTORRE,
	MUERTE,
	VICTORIA,
	DERROTA
} tipoSonido;

class igvInterfaz {
protected:
	// Atributos
	int ancho_ventana; // ancho inicial de la ventana de visualizacion
	int alto_ventana;  // alto inicial de la ventana de visualizacion

	unsigned t0;

	modoInterfaz modo;

	int cursorX, cursorY; // pixel de la pantalla sobre el que est� situado el rat�n, por pulsar o arrastrar

	int buscarTerreno(GLubyte pixel[]);
	int buscarTorre(GLubyte pixel[]);

	double tiempoEnTienda; //tiempo que estamos en la tienda

	igvEscena3D escena; // escena que se visualiza en la ventana definida por igvInterfaz
	igvCamara camara; // c�mara que se utiliza para visualizar la escena

	int numOleadas; //numero de oleadas de enemigos;
	int numVidasReyes;  //numero de vidas 
	int dineroActual; // Dinero utilizado

	bool cuatro; // cuatro = true: indica que se debe dividir en 4 , cuatro = false: indica que NO se debe dividir en 4
	bool tienda; // tienda = true: Se abre el menu de Estructuras

	int terrenoSeleccionado; // c�digo del objeto seleccionado, -1 si no hay ninguno
	int estructuraSeleccionada;
	int torreSeleccionada;
	int estructuraDisparo;
	bool boton_retenido; // indica si el bot�n est� pulsado (true) o se ha soltado (false)
	bool colorTorres;

	bool disparoRelizado;

	int menuSelection;

	tipoAnimacion tipoA;

// Valores de la vista panor�mica
	igvPunto3D p0, r, V;

public:
	// Constructores por defecto y destructor
	igvInterfaz();
	~igvInterfaz();

	// Metodos est�ticos
	// callbacks de eventos
	static void set_glutKeyboardFunc(unsigned char key, int x, int y); // metodo para control de eventos del teclado
	static void set_glutReshapeFunc(int w, int h); // m�todo que define la camara de vision y el viewport
													// se llama autom�ticamente cuano se camba el tama�o de la ventana
	static void set_glutDisplayFunc(); // m�todo para visualizar la escena
	static void set_glutMouseFunc(GLint boton, GLint estado, GLint x, GLint y); // control de pulsacion del raton
	static void set_glutMotionFunc(GLint x, GLint y); // control del desplazamiento del raton con boton pulsado
	
	static void reyIdleFunc(); // m�todo para animar al rey
	static void enemigoIdleFunc(); // m�todo para animar al rey
	static void balaCa�onIdleFunc(); // m�todo para animar al rey
	static void flechaTorreIdleFunc(); // m�todo para animar al rey

	static void animacion();

	static void menuHandle(int value);
	void create_menu();

	void reproducirSonido(tipoSonido sonido);

	void setTipoA(tipoAnimacion tipo) {
		tipoA = tipo;
	}

	void incrementarOleada(int val) {
		this->numOleadas = numOleadas + val;
	}

	void quitarVida(int val) {
		this->numVidasReyes = numVidasReyes - val;
	}

	bool getTienda() {
		return tienda;
	}

	void setTienda(bool _tienda) {
		tienda = _tienda;
	}

	void setTiempoEnTienda(double val) {
		tiempoEnTienda = val;
	}
	
	double getTiempoEnTienda() {
		return tiempoEnTienda;
	}

	unsigned int getT0() {
		return t0;
	}

	void setT0(unsigned int _t0) {
		t0 = _t0;
	}

	igvCamara getCamara() {
		return camara;
	}

	igvEscena3D getEscena() {
		return escena;
	}

	int getNumOleada() {
		return this->numOleadas;
	}

	int getNumVidas() {
		return this->numVidasReyes;
	}

	void set_tDisparoFinEscena(clock_t d) {
		escena.set_tDisparoFin(d);
	}

	int getTerrenoSeleccionado() {
		return terrenoSeleccionado;
	}

	int getEstructuraSeleccionada() {
		return estructuraSeleccionada;
	}

	int getDinero() {
		return dineroActual;
	}

	void setDinero(int dinero) {
		this->dineroActual = dinero;
	}

	void incrementarDinero(int dinero) {
		this->dineroActual = dineroActual + dinero;
	}

	int getMenuSelection() {
		return menuSelection;
	}

	void setMenuSelection(int _menuSelection) {
		this->menuSelection = _menuSelection;
	}

	void setColisionadoEscena(bool col) {
		escena.setColisionado(col);
	}

	void setEstructuraDisparo(int _estructuraDisparo) {
		this->estructuraDisparo = _estructuraDisparo;
	}
	 
	int getEstructuraDisparo() {
		return estructuraDisparo;
	}

	void setColorTorres(bool _colorTorres) {
		this->colorTorres = _colorTorres;
	}

	bool getColorTorres() {
		return colorTorres;
	}

	void setDisparoRealizado(bool _disparoRealizado) {
		disparoRelizado = _disparoRealizado;
	}

	bool gradosLibActivos(); //m�todo que devuelve true si hay algun grado de libertad "activado" o false si no.
	// la causa de este m�todo es que la animacion (letra a), solo se podr� activar si no hay
	// ningun grado de libertad "activado"

	// Metodos
	// crea el mundo que se visualiza en la ventana
	void crear_mundo(void);

	// inicializa todos los par�metros para crear una ventana de visualizaci�n
	void configura_entorno(int argc, char** argv, // parametros del main
		int _ancho_ventana, int _alto_ventana, // ancho y alto de la ventana de visualizaci�n
		int _pos_X, int _pos_Y, // posicion inicial de la ventana de visualizaci�n
		string _titulo // t�tulo de la ventan de visualizaci�n
	);
	void inicializa_callbacks(); // inicializa todas los callbacks

	void inicia_bucle_visualizacion(); // visualiza la escena y espera a eventos sobre la interfaz

	// m�todos get_ y set_ de acceso a los p0 = igvPunto3D(-4, 3, 5);atributos
	int get_ancho_ventana() { return ancho_ventana; };
	int get_alto_ventana() { return alto_ventana; };

	void set_ancho_ventana(int _ancho_ventana) { ancho_ventana = _ancho_ventana; };
	void set_alto_ventana(int _alto_ventana) { alto_ventana = _alto_ventana; };
};

#endif
