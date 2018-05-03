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
    int nverts;
    float radius;
    float vert[8][3];
    float angle;
    float rotate;
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
    float nverts;
    float radius;
    float vert[8][3];
    float angle;
    float rotate;
    float color[3];
    int health;
    struct Salmonella *prev;
    struct Salmonella *next;
    S_Bullet *sbarr;
    int nSbullets;
    struct timespec sbulletTimer;
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
