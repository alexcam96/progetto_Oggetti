#include "Attempt.h"


Attempt::Attempt()
{
}


Attempt::~Attempt()
{
}


void Attempt::left()
{
	swap(34,0,14,46);
	swap(21,8,28,41);
	swap(1,13,47,33);
	swap(35,2,15,48);
	swap(22,9,29,42);
	return;
}

void Attempt::right()
{
	swap(6,38,52,18);
	swap(24,44,31,11);
	swap(39,51,19,5);
	swap(7,40,53,20);
	swap(25,45,32,12);
}

void Attempt::up()
{
	swap(38,7,0,35);
	swap(34,39,6,1);
	swap(37,24,4,21);
	swap(36,25,3,22);
	swap(33,40,5,2);
}

void Attempt::down()
{
	swap(13,20,51,48);
	swap(16,32,49,29);
	swap(18,53,46,15);
	swap(14,19,52,47);
	swap(17,31,50,28);
}

void Attempt::back()
{
	swap(39,35,47,53);
	swap(37,42,50,45);
	swap(34,48,52,40);
	swap(38,33,46,51);
	swap(36,41,49,44);
}

void Attempt::front()
{
	swap(1,7,19,15);
	swap(4,12,17,9);
	swap(6,20,14,2);
	swap(0,5,18,13);
	swap(3,11,16,8);
}

void Attempt::moveType(int s1, int s2, int angolo)
{
	angolo = angolo / 90;
	if (s1 == 0)
		if (s2 == 1)
		{
			for(int i=0; i<angolo; i++)
				left();
		}
		else 
		{
			for (int i = 0; i<angolo; i++)
				right();
		}
	else if(s1==1)
		if (s2 == 1)
		{
			for (int i = 0; i<angolo; i++)
				front();
		}
		else
		{
			for (int i = 0; i<angolo; i++)
				back();
		}
	else if (s1 == 2)
		if (s2 == 1)
		{
			for (int i = 0; i<angolo; i++)
				up();
		}
		else
		{
			for (int i = 0; i<angolo; i++)
				down();
		}
			
}

void Attempt::swap(int one, int two, int three, int four)
{
	int app;
	app = att[four];
	att[four] = att[three];
	att[three] = att[two];
	att[two] = att[one];
	att[one] = app;
}

bool Attempt::test()
{
	//funzione per controllare se il cubo è risolto, controlla che il vettore att sia ordinato. True=cubo completo
	for (int i = 0; i < 54; i++)
		if (att[i] != i)
			return false;

	return true;
}
