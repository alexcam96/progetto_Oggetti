#pragma once
#include<array>

/*
	Classe che crea una struttura per poter controllare se il cubo è risolto o meno
	ad ogni mossa viene richiamata una funzione specifica che muove gli elementi della struttura corrispondenti a quelli del cubo
*/

class Attempt
{
public:
	Attempt();												//costruttore
	~Attempt();												//distruttore
	void left();											//gira la faccia sinistra di 90 gradi
	void right();											//gira la faccia destra di 90 gradi
	void up();												//gira la faccia in alto di 90 gradi
	void down();											//gira la faccia in basso di 90 gradi
	void back();											//gira la faccia dietro di 90 gradi
	void front();											//gira la faccia davanti di 90 gradi
	void swap(int one, int two, int three, int four);		//per aggiornare i valori nella struttura dopo la mossa
	void moveType(int s1, int s2, int angolo);				//traduce i valori della mossa del cubo per richiamare la funzione corrispondente
	bool test();											//controlla se il cubo è risolto
private:
	std::array<int, 54> att{ 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53 };
	//att è la struttura per poter tenere conto della situzione del cubo
};

