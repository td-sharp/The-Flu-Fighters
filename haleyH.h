class Gbola {
public:
	float pos[3];
	float vel[3];
	int nverts;
	float radius;
	float vert[8][3];
	float angle;
	float rotate;
	float color[3];
	int health;
	struct Gbola *prev;
	struct Gbola *next;
public:
	Gbola(float, float);	
};

class Salmonella {
public:
	float pos[3];
	float vel[3];
	float nverts;
	float radius;
	float vert[8][3];
	float angle;
	float rotate;
	float color[3];
	int health;
	struct Salmonella *prev;
	struct Salmonella *next;
public:
	Salmonella(float, float, float);
};

class Cholera {
public:
	float pos[3];
	float vel[3];
	float angle;
	float rotate;
	float accelerate;
	int health;
public:
	Cholera(float, float, float, float);
};
