class Gbola {
public:
	float pos[3];
	float vel[3];
	int health;
public:
	Gbola(float, float);
};

class Salmonella {
public:
	float pos[3];
	float vel[3];
	float angle;
	float rotate;
	int health;
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
