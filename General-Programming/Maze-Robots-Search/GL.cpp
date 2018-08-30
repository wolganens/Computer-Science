#include "GL.h"
#include <sstream>

int GL::width,GL::height;
vector<Point> GL::steps;
int GL::current;
float GL::deltax, GL::deltay;
int GL::dimx, GL::dimy;
Maze* GL::lab;
Robot* GL::rob;
TEX* GL::wallTex;

void GL::drawRect(float x1, float y1, float x2, float y2) {
    glBegin(GL_QUADS);
      glTexCoord2f(0,1);
	  glVertex2f(x1,y1);
      glTexCoord2f(1,1);
      glVertex2f(x2,y1);
      glTexCoord2f(1,0);
      glVertex2f(x2,y2);
      glTexCoord2f(0,0);
      glVertex2f(x1,y2);
	glEnd();
}

void GL::drawTri(float x1, float y1, float x2, float y2, float x3, float y3) {
	glBegin(GL_TRIANGLES);
	  glVertex2f(x1,y1);
	  glVertex2f(x2,y2);
	  glVertex2f(x3,y3);
	glEnd();
}

void GL::drawCirc(float x1, float y1, float r) {

	//float ang;
	//ang = 0;

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1,y1);

	GLint circle_points = 20;
	for (int i = 0; i < circle_points; i++) {
		float angle = 2*3.1415926*i/circle_points;
		glVertex2f(x1+cos(angle)*r, y1+sin(angle)*r);
	}
	glVertex2f(x1+cos(0)*r, y1+sin(0)*r);
	glEnd();
}

void GL::drawLine(float x1, float y1, float x2, float y2) {
	glBegin(GL_LINES);
	  glVertex2f(x1,y1);
	  glVertex2f(x2,y2);
	glEnd();
}

void GL::clear() {
	glClearColor(1,1,1,0);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
}

void GL::init()
{
	int argc = 0;
	char *argv[] = { "gl", 0 };

	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(400,400);
    glutCreateWindow("Assignment 2");
	glutDisplayFunc(draw);
    glutKeyboardFunc (keyboard);
    glutSpecialFunc (keyboardSpecial);

	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0.0,1.0,1.0,0.0);
    glMatrixMode(GL_MODELVIEW);

    wallTex = LoadTexture("img/brick.jpg", true);
}

void GL::setMazeRobot(Maze* l, Robot* robo)
{
    lab = l;
    rob = robo;

    dimx = lab->getWidth();
    dimy = lab->getHeight();
	deltax = 1.0/dimx;
    deltay = 1.0/dimy;

    rob->generateSteps();
    steps = rob->getSteps();
    cout << "Steps: " << steps.size() << endl;

    for(unsigned int i=0; i<steps.size(); i++)
        cout << steps[i].getX() << "," << steps[i].getY() << endl;
    current = 0;
    rob->move(steps[current]);
}

void GL::loop() {
	glutMainLoop();
}

void GL::draw(void)
{
	clear();

	// For other colours, see /etc/X11/rgb.txt

	setColor(200,200,200);	// light gray

	float x,y;
	// Draws the grid
	for(x=0; x<=1; x+=deltax)
		drawLine(x,0,x,1);
	for(y=0; y<=1; y+=deltay)
		drawLine(0,y,1,y);

	// Draws the maze
    glColor3f(1,1,1);
    y = 0.0;
    enableTexture(wallTex->texid);
	for(int l=0; l<dimy; l++, y+=deltay) {
		x = 0.0;
		for(int c=0; c<dimx; c++, x+=deltax) {
            if(!lab->isEmpty(Point(c,l)))
				drawRect(x,y,x+deltax,y+deltay);
		}
    }
    disableTexture();

    // Outputs the current step
    ostringstream aux;
    aux << "Step: " << current+1 << " of " << steps.size();
    glColor3f(0,0,0);
    drawText(0.0615,0.0315, aux.str());
    glColor3f(1,1,0);
    drawText(0.06,0.03, aux.str());

    // Draws the robot
    rob->draw();

	show();
}

void GL::keyboard(unsigned char key, int x, int y)
{
    if (key == 27)		// ESC ?
    {
        FreeTextures();
        exit(0);
    }

	glutPostRedisplay();
}

void GL::drawText(float x, float y, string txt)
{
    glRasterPos2f(x,y);
    unsigned int cont=0;
    while(cont < txt.size())
        glutBitmapCharacter(GLUT_BITMAP_9_BY_15, txt[cont++]);
}

void GL::enableTexture(GLuint texid)
{
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texid);
}

void GL::disableTexture()
{
    glDisable(GL_TEXTURE_2D);
}

void GL::keyboardSpecial(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT &&  current > 0)
            current--;
    else if(key == GLUT_KEY_RIGHT  && current < (int) steps.size()-1)
            current++;

    rob->move(steps[current]);

    glutPostRedisplay();
}
