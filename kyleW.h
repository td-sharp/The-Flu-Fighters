/* Aurthor: Kyle Werts
 * Date: 2/23/2018
 *
 * Comments:
 * Flu Fighters Power up and ammo file 
 * For now the file will only render a square object to the screen
 * to meet the lab requirments.
 */ 
#define wobble 50

class BigBadBoss {
	public:
		enum gameSkill {

		}
		float pos[3];
		float vel[3];
		float nverts;
		float radius;
		float vert[8][3];
		float angle;
		float rotate;
		float color[3];
		int health 1000;
		static int frame;

		//Will eventually make this adjustable upon moving to next wave
		float gameSkill = 1.0;

		struct BigBadBoss *prev;
		struct BigbadBoss *next;

		float *getPos();
		void update();

		BigBadBoss();

		//Destructor
		~BigBadBoss();

		friend class Salmonella;
		friend class Cholera;
		friend class Gbola;
	protected:
		void move();
		virtual void calcShootInterval();

	public:
		BigbadBoss(float, float, float, float, float);
}

class PowerUps
{
	public:
		//Looking to add Supershield and repiar in the future
		enum Type { 
			Shields, 
			NumPowerUps 
		};

	PowerUps();

	//Destructor
	~PowerUps();

	void update();
	void drawGL();
	void clear();

	private:
		float speed;
		float wobble[wobble];

		//There should never be more than two powers on the screen at a time
		int activeCount;
}
class BossAmmo
{
	public:
		BossAmmo();
		~BossAmmo();
	
	void addAmmo(int type, float pos[3], float vel[3]);
	void updateAmmo();

}

