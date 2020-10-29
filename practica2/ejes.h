#ifndef _EJES_H
#define _EJES_H

class Ejes {

private:
	float axisSize;
	float vertexArray[18];	// 18 porque hay 6 vértices con 3 coordenadas
	float colorArray[18];

public:
	Ejes();
	void changeAxisSize( float newSize );
	void draw();

private:
	void createArrayData();

};
#endif
