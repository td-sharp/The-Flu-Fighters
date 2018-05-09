class S_Bullet {
    public:
        float pos[3];
        float vel[3];
        float color[3];
        struct timespec time;
    public:
        S_Bullet();
};

class Gbola {
public:
    float pos[3];
    float vel[3];
    float radius;
    float color[3];
    int health;
    struct Gbola *prev;
    struct Gbola *next;
    S_Bullet *sbarr;
    int nSbullets;
    struct timespec sbulletTimer;
public:
    Gbola(float, float);    
    ~Gbola();
};

class Salmonella {
public:
    float pos[3];
    float vel[3];
    float xradius;
    float yradius; 
    float color[3];
    int health;
    struct Salmonella *prev;
    struct Salmonella *next;
    S_Bullet *sbarr;
    int nSbullets;
    struct timespec sbulletTimer;
public:
    Salmonella(float, float);
    ~Salmonella();
};

class Cholora {
public:
    float pos[3];
    float vel[3];
    float xdest;
    float ydest;
    float radius;
    float color[3];
    float accelerate;
	int health;
    struct Cholora *prev;
    struct Cholora *next;
    S_Bullet *sbarr;
    int nSbullets;
    struct timespec sbulletTimer;
    struct timespec waitTimer;
public:
    Cholora(float, float, float, float);
    ~Cholora();
};
