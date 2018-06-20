#ifndef RUBIXCUBE_H_
#define RUBIXCUBE_H_

#include <cstdlib> 
#include <ctime> 
#include <array>
#include "../../game/Game.h"
#include "SmallCube.h"
#include "../../Attempt.h"


class RubixCube : public game::MeshEntity {
    game::Mesh *rubix, *flat;
public:
    RubixCube();
    ~RubixCube();
    void update();
    void select(int axis, GLfloat n);
    void spin(GLfloat ang);
	

	void shuffle();											//mischia il cubo in maniera random
	void resolve();											//risolve il cubo con l'algoritmo
	void placement();										//posiziona il cubo in una configurazione risolvibile

private:

	Attempt tentativo;										
	const static int columns = 3, rows = 35;				//valori di inizializzazione array delle mosse
	bool s{ false }, r{ false }, p{ false };				//variabili di controllo per la selezione delle funzioni resolve e shuffle
	int ctr{ 0 };											//variabile di controllo per la sincronizzazione con l'animazione
	std::array <int,2> selected {-1, -1};					//usato per tenere traccia della selezione da una mossa all'altra
	std::array <int, 2> control{0, 0};						//variabili di controllo per il ciclo di risoluzione	
	std::array <int, 4> ctrl{-1, 0, 0, 34};					//variabili di controllo per la funzione placement
	
	const  std::array<std::array<int, RubixCube::columns>, RubixCube::rows> mosse { 0, 1, 90,			//mosse dell'algoritmo di risoluzione 
																					0, -1, 90,
																					0, -1, 90,
																					1, -1, -90,
																					0, 1, -90,
																					0, -1, -90,
																					2, 1, 90,
																					2, 1, 90,
																					1, 1, 90,
																					1, 1, 90,
																					0, 1, 90,
																					1, -1, -90,
																					2, -1, -90,
																					2, 1, 90,
																					2, 1, 90,
																					1, -1, -90,
																					0, 1, -90,
																					0, -1, 90,
																					0, -1, 90,
																					1, -1, 90,
																					1, -1, 90,
																					0, 1, -90,
																					2, -1, 90,
																					2, -1, 90,
																					2, 1, 90,
																					0, 1, -90,
																					1, -1, 90,
																					1, -1, 90,
																					2, 1, 90,
																					2, 1, 90,
																					0, -1, 90,
																					0, -1, 90,
																					1, -1, -90,
																					2, -1, 90,
																					2, -1, 90
	};
};

#endif
