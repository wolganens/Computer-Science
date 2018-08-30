#include "TestMaze.h"
#include "ArTur.h"
#include "Robby.h"
#include "RobotB9.h"
#include "T800.h"
#include "GL.h"

#include <cstdlib>

using namespace std;

int main(int argc, char **argv){
    if(argc != 4){        
        cerr << "Usage: " << argv[0] << " 1 in/maze<X>.txt <max_steps>" << endl;        
        exit(1);
    }
    int steps = atoi(argv[3]);
    GL::init();
    // Load the test maze
    Maze* lab = new TestMaze();
    if(atoi(argv[1]) == 1)
        lab->loadMaze(argv[2]);
    else
        lab->generateMaze(atoi(argv[2]));
    Point posIni = lab->getIniPos();

    Robot* robot = NULL;

    // Verifica qual robô foi lido do arquivo e instancia o robo adequado
    switch(lab->getRobot()) {
    	case 1:
            cout << "Robby" << endl;
    		robot = new Robby(posIni, lab, steps);
    		break;
    	case 2:
            cout << "ArTur" << endl;
    		robot = new ArTur(posIni, lab, steps);
    		break;
    	case 3:
            cout << "T800" << endl;
            robot = new T800(posIni,lab,steps);
    		break;
        default:
            cout << "RobotB9" << endl;
            robot = new RobotB9(posIni,lab,steps);
    }
    cout << "Width: " << lab->getWidth() << " Height: " << lab->getHeight() << endl;
    cout << "Starting pos: " << posIni.getX() << " , " << posIni.getY() << endl;    

    GL::setMazeRobot(lab, robot);

	GL::loop();
}
