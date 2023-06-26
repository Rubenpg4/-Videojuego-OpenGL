#include "TerrenoEstructuras.h"

TerrenoEstructuras::TerrenoEstructuras() {
	posicion.set(0, 0, 0);
	color = new GLfloat[3];
	color[0] = 0.0;
	color[1] = 0.0;
	color[2] = 0.0;
	seleccionado = false;
	defensaCa�on = nullptr;
	defensaTorre = nullptr;
	myMenu = new MenuEstructuras();
	myMenu->setTerreno(this);
	tipo = NINGUNA;
	numeroLuz = 0;
}

TerrenoEstructuras::TerrenoEstructuras(float r, float g, float b, igvPunto3D pos) {
	posicion = pos;
	color = new GLfloat[3];
	color[0] = r;
	color[1] = g;
	color[2] = b;
	seleccionado = false;
	defensaCa�on = nullptr;
	defensaTorre = nullptr;
	myMenu = new MenuEstructuras();
	myMenu->setTerreno(this);
	tipo = NINGUNA;
	numeroLuz = 0;
}

TerrenoEstructuras::TerrenoEstructuras(const TerrenoEstructuras& orig) {
	posicion = orig.posicion;
	color = orig.color;
	seleccionado = orig.seleccionado;
	defensaCa�on = orig.defensaCa�on;
	defensaTorre = orig.defensaTorre;
	myMenu = orig.myMenu;
	myMenu->setTerreno(orig.myMenu->getTerreno());
	tipo = orig.tipo;
	numeroLuz = orig.numeroLuz;
}

TerrenoEstructuras::~TerrenoEstructuras() {
	delete []color;
	delete myMenu;
	defensaCa�on = nullptr;
	defensaTorre = nullptr;
}


GLfloat* TerrenoEstructuras::getColor() {
	return color;
}

GLubyte* TerrenoEstructuras::getColorByte() {
	GLubyte colorubyte[3];
	colorubyte[0] = (GLubyte)(color[0] * 255);
	colorubyte[1] = (GLubyte)(color[1] * 255);
	colorubyte[2] = (GLubyte)(color[2] * 255);

	return colorubyte;
}

void TerrenoEstructuras::visualizar() {
	glMaterialfv(GL_FRONT, GL_EMISSION, color);
	glColor3fv(color);
	glTranslated(posicion.c[0], posicion.c[1], posicion.c[2]);
	glScaled(0.25, 0.2, 0.5);
	glutSolidCube(2);
}

void TerrenoEstructuras::anadirEstructura(Ca�on* _ca�on) {
	defensaCa�on = _ca�on;
	tipo = CA�ON;
	//defensaCa�on->setTerreno(this);
}

void TerrenoEstructuras::anadirEstructura(Torre* _torre) {
	defensaTorre = _torre;
	tipo = TORRE;
	//defensaTorre->setTerreno(this)
}

void TerrenoEstructuras::quitarEstructura() {
	defensaCa�on = nullptr;
	defensaTorre = nullptr;
	myMenu->setCa�on(new Ca�on());
	myMenu->setTorre(new Torre());
	tipo = NINGUNA;
}

