#include "RubixCube.h"

RubixCube::RubixCube() {
	rubix = (game::Mesh*)game::ResMgr::load("res/mesh/rubix/rubix-face.obj");
	flat = (game::Mesh*)game::ResMgr::load("res/mesh/rubix/flat-face.obj");
	// initialize faces
	game::Camera *cam = new game::Camera();
	cam->persp();
	game::cameraSet(cam);
	// faces
	for (GLfloat x = -1.f; x <= +1.f; x += 1.f)
		for (GLfloat y = -1.f; y <= +1.f; y += 1.f)
			for (GLfloat z = -1.f; z <= +1.f; z += 1.f)
				if (x != y || y != z || z != 0.f)
					addChild(std::string("cube") + char(childrenCount() + '0'),
						new SmallCube(glm::vec3(x, y, z), flat, rubix));
	scale(glm::vec3(.4f, .4f, .4f));
	game::fogSet(glm::vec4(0, 0, 0, 1), 0);
	//
	game::Light *l1 = new game::Light(glm::vec3(.5f), glm::vec3(.5f));
	game::lights.push_back(l1);
	l1->translate(glm::vec3(10, 0, 10));
	//
	game::Light *l2 = new game::Light(glm::vec3(.5f), glm::vec3(.4f));
	game::lights.push_back(l2);
	l2->translate(glm::vec3(5, 5, 10));
}

RubixCube::~RubixCube() {
    std::vector<std::string> ch = childrenNames();
    for (int i = 0; i < ch.size(); ++i) {
        game::Entity* c = getChild(ch[i]);
        removeChild(ch[i]);
        c->~Entity();
    }
    rubix->~Mesh();
    flat->~Mesh();
}

void RubixCube::update() {
    // camera
    game::Camera* myCamera = game::cameraGet();
    bool speed = game::key_down_[' '];
	if (game::key_down_['w'])
		myCamera->rotate(+(speed * 4 + 1), myCamera->u());
    if (game::key_down_['s'])
        myCamera->rotate(-(speed * 4 + 1), myCamera->u());

    if (game::key_down_['q'])
        myCamera->rotate(+(speed * 4 + 1), myCamera->n());
    if (game::key_down_['e'])
        myCamera->rotate(-(speed * 4 + 1), myCamera->n());

    if (game::key_down_['d'])
        myCamera->rotate(+(speed * 4 + 1), glm::vec3(0, 0, 1));
    if (game::key_down_['a'])
        myCamera->rotate(-(speed * 4 + 1), glm::vec3(0, 0, 1));

    if (game::key_down_['A'])
        myCamera->translate(-myCamera->u() * .1f);
    if (game::key_down_['D'])
        myCamera->translate(myCamera->u() * .1f);
    // select

	
	if (game::key_down_['0'])
	select(-1, -1);
	if (game::key_down_['1'])
	select(0, -1);
	if (game::key_down_['2'])
	select(0, 1);
	if (game::key_down_['3'])
	select(1, -1);
	if (game::key_down_['4'])
	select(1, 1);
	if (game::key_down_['5'])
	select(2, -1);
	if (game::key_down_['6'])
	select(2, 1);

	// move
	if (game::key_down_['z'])
		spin(90);
	if (game::key_down_['x'])
		spin(-90);

	
	//*******************MODIFICHE*********************

	if (game::key_down_['.']) {									//alla pressione del tasto '.' viene interrotta la funzione corrente
		for (GLboolean &k : game::key_down_) {
			k = false;
		}
		s = false;
		r = false;
		p = false;
	}


	if (game::key_down_['S'] or s == true)
		shuffle();												//funzione shuffle()			
	if (game::key_down_['R'] or r == true) 
		resolve();												//funzione resolve()
	if (game::key_down_['P'] or p == true)
		placement();											//funzione placement()
	
	//***********************END**********************
	
    game::MeshEntity::update();


}

void RubixCube::select(int axis, GLfloat n) {


	//*******************MODIFICHE*********************

	selected[0] = axis;									//salvo la selezione per poterla poi passare alla funzione
	selected[1] = static_cast<int>(n);					//moveType dell'oggetto attempt

	//***********************END**********************

    std::vector<std::string> v = childrenNames();
    // de-select
    if (axis == -1) {
        for (int i = 0; i < v.size(); ++i)
            *((SmallCube*)getChild(v[i]))->selected() = false;
    }
    // select
    else {
        glm::vec3 axes[3] = { glm::vec3(1, 0, 0),
                              glm::vec3(0, 1, 0),
                              glm::vec3(0, 0, 1) };
        // check
        std::set<SmallCube*> good;
        bool can = true;
        for (int i = 0; i < v.size() && can; ++i) {
            SmallCube* ch = (SmallCube*)getChild(v[i]);
            glm::vec3 org = ch->o();
            can = abs(ch->spin_ang()) < EPS;
            if (n <= org[axis] + EPS && n >= org[axis] -EPS)
                good.insert(ch);
        }
        // select
        if (can)
            for (int i = 0; i < v.size(); ++i)
                if (good.find((SmallCube*)getChild(v[i])) != good.end())
                    *((SmallCube*)getChild(v[i]))->selected() = true,
                    ((SmallCube*)getChild(v[i]))->set_spin_axis(axes[axis]);
                else
                    *((SmallCube*)getChild(v[i]))->selected() = false;
    }
}

void RubixCube::spin(GLfloat ang) {
	
	//*******************MODIFICHE*********************

	if (ang < 0) {															//passo alla funzione moveType la selezione della faccia e l'angolo di rotazione
		tentativo.moveType(selected[0], selected[1], 360 + ang);
	}	
	else {
		tentativo.moveType(selected[0], selected[1], ang);
	}

	//***********************END**********************
	
	if (ang < 0) {
		tentativo.moveType(selected[0], selected[1], 360 + ang);
	}
	else {
		tentativo.moveType(selected[0], selected[1],ang);
	}

    std::vector<std::string> v = childrenNames();
    std::set<SmallCube*> good;
    bool can = true;
    for (int i = 0; i < v.size() && can; ++i) {
        SmallCube* ch = (SmallCube*)getChild(v[i]);
        glm::vec3 org = ch->o();
        can = abs(ch->spin_ang()) < EPS;
    }
    if (can)
        for (int i = 0; i < v.size(); ++i)
            if (*((SmallCube*)getChild(v[i]))->selected())
                ((SmallCube*)getChild(v[i]))->set_spin_ang(ang);
}

//*******************MODIFICHE*********************

void RubixCube::shuffle() {									//Funzione shuffle
	s = true;
	int i{ (rand() % 3) };									//seleziono in maniera random la faccia da ruotare
	int j{ (rand() % 3) - 1 };

	select(i, j);
	spin(90);

	game::MeshEntity::update();
}


void RubixCube::resolve() {									//funzione resolve
		int n1, n2, row;
		r = true;											//mi permette di continuare a rientrare nella funzione ad ogni reiterazione del loop
	if (ctr == 0) {
		row = control[0];									//algoritmo di risoluzione

		n1 = mosse[row][0];
		n2 = mosse[row][1];

		select(n1, n2);
		spin(mosse[row][2]);

		if (row >= 34) {
			control[1] ++;
			control[0] = 0;
		}
		else {
			control[0]++;
		}

		if (tentativo.test()) {
			std::cout << "il cubo \x8a risolto\n";
			control[1] = 3;
		}

		if (control[1] >= 3) {
			game::key_down_['.'] = true;					//uscita dalla funzione
			control[0] = 0;
			control[1] = 0;
			if (!tentativo.test()) {
				std::cout << "il cubo non \x8a risolvibile con questo algoritmo\n";
			}
		}
		//std::cout << n1 << ' ' << n2 << ' ' << mosse[row][2] << std::endl;
 		game::MeshEntity::update();	
	}
	ctr++;
	if (ctr >= 15) { ctr = 0; }
}




void RubixCube::placement() {
		int n1, n2, angle, m;
		p = true;
		if (ctr == 0) {
			if (ctrl[0]<0) {
				ctrl[3] = 34;
				ctrl[0] = rand() % 80 + 11;								//numero di mosse da fare per il placement
				ctrl[1] = ctrl[0] / ctrl[3];							//numero di giri completi da fare
				ctrl[2] = ctrl[0] % ctrl[3];							//mosse rimanenti dell'ultimo giro
				if (ctrl[2] == 0) {
					ctrl[2] = -1;
				}
			}
			m = ctrl[3];

			if (ctrl[2] >= 0) {
				n1 = mosse[ctrl[2]][0];
				n2 = mosse[ctrl[2]][1];
				angle = -mosse[ctrl[2]][2];
				
				select(n1, n2);
				spin(angle);
				
				ctrl[2]--;
			}
			else if (ctrl[1]>0) { 
				n1 = mosse[m][0];
				n2 = mosse[m][1];
				angle = -mosse[m][2];

				select(n1, n2);
				spin(angle);
	
				if (m == 0) {
					ctrl[3] = 34;
					ctrl[1]--;
				}
				else {
					ctrl[3]--;
				}
			}
			if (ctrl[1] == 0 and ctrl[2] < 0) {							//uscita dalla funzione
				ctrl[0] = -1;
				game::key_down_['.'] = true;
			}
			//std::cout << n1 << ' ' << n2 << ' ' << angle << std::endl;
			game::MeshEntity::update();		
		}
		ctr++;
		if (ctr >= 15) { ctr = 0; }
}

//***********************END**********************
