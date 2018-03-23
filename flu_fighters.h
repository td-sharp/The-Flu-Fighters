typedef float Flt;
typedef float Vec[3];

class Bullet {
public:
	Vec pos;
	Vec vel;
	float color[3];
	struct timespec time;
public:
	Bullet();
};

class Asteroid {
	public:
		Vec pos;
		Vec vel;
		int nverts;
		Flt radius;
		Vec vert[8];
		float angle;
		float rotate;
		float color[3];
		struct Asteroid *prev;
		struct Asteroid *next;
	public:
		Asteroid();
};

class Ship {
	public:
		Vec dir;
		Vec pos;
		Vec vel;
		float angle;
		float color[3];
	public:
		Ship();
}; 

class Game {
public:
	Ship ship;
	Asteroid *ahead;
	Gbola *gbhead;
	Bullet *barr;
	int nasteroids;
	int nGbola;
	int nbullets;
	struct timespec bulletTimer;
	struct timespec mouseThrustTimer;
	bool mouseThrustOn;
public:
	Game();
	~Game();
};
