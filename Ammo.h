/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 * Flu Fighters Power up and ammo file 
 */ 
#ifndef AMMO_H
#define AMMO_H


class ActiveAmmo
{
public:
    ActiveAmmo();
    ~ActiveAmmo();

    void init(float p[3], float v[3], float d);
    inline void updatePos()
    {
        pos[0] += vel[0];
        pos[1] += vel[1];
        pos[2] += vel[2];
    }

    float pos[3];
    float vel[3];
    float damage;

    ActiveAmmo *next;
    ActiveAmmo *prev;

private:
    static int ammoCount;
};

#endif //AMMO_H