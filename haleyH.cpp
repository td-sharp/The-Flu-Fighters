
class G_coli {
public: 
	Vec pos;
	Vec vel;
	int health;
};

void buildG_coli(G_coli *gc)
{
	float factor = rand() % 5 + 3;

	gc->pos[0] = (float)rand() % gl.xres/2 - 300;
	gc->pos[1] = (float)rand() % gl.yres/2 + 150;
	gc->pos[2] = 0.00;

	gc->vel[0] = factor;
	gc->vel[1] = -factor / 1.5;
	gc->vel[2] = 0.00;

}

void moveG_coli(G_coli *gc)
{
	gc->pos[0] += gc->vel[0];
	gc->pos[1] += gc->vel[1];

	if ((gc->pos[0] < -600/2 && gc->vel[0] < 0) || 
	    (gc->pos[0] > 600/2 && gc->vel[0] > 0))
		gc->vel[0] = -gc->vel[0]; 
}
