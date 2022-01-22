#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glut.h>
#endif

#include <iostream>
#include <ctime>
#include <sys/time.h>
#include <cstring>
#include <stack>
using namespace std;
float R,G,B;
int width=10,height=10;
int size_grid = 100;
int up = 0,down = 1,right = 2,left = 3;
struct Cell{
	bool up;
	bool down;
	bool right;
	bool left;
};
struct Cell grid[100] = {false,false,false,false};
bool visit[100]={false};
int visited = 0;
/*for(int i=0;i<width*height;i++)
{
	grid[i].up=false;
	grid[i].down=false;
	grid[i].right=false;
	grid[i].left=false;
}*/
int move_to_neighbour(int present)
{
	int movable = 0,cell_array_x[4],cell_array_y[4];
	int x=present%10;
	int y=present/10;
	if(x-1 < 10 && x-1 >=0)
	{
		if(visit[y*10 + x - 1] == false)
		{
			cell_array_x[movable] = x-1;
			cell_array_y[movable] = y;
			movable++;
		}
	}
	if(x+1 < 10 && x+1 >=0)
	{
		if(visit[y*10 + x + 1] == false)
		{
			cell_array_x[movable] = x+1;
			cell_array_y[movable] = y;
			movable++;
		}
	}
	if(y-1 < 10 && y-1 >=0)
	{
		if(visit[(y-1)*10 + x] == false)
		{
			cell_array_x[movable] = x;
			cell_array_y[movable] = y-1;
			movable++;
		}
	}
	if(y+1 < 10 && y+1 >=0)
	{
		if(visit[(y+1)*10 + x] == false)
		{
			cell_array_x[movable] = x;
			cell_array_y[movable] = y+1;
			movable++;
		}
	}
	if(movable == 0)
		return -1;
	else
	{
		int index = rand()%movable;
		int next_x = cell_array_x[index];
		int next_y = cell_array_y[index];
		int next = next_x + next_y*10;
		visit[next] = true;
		visited ++;
		if(x-next_x == 1)
		{
			grid[present].left = true;
			grid[next].right = true;
		}
		if(next_x-x == 1)
		{
			grid[present].right = true;
			grid[next].left = true;
		}
		if(y-next_y == 1)
		{
			grid[present].down = true;
			grid[next].up = true;
		}
		if(next_y-y == 1)
		{
			grid[present].up = true;
			grid[next].down = true;
		}
		return next;
	}
	
}
void pathfinding()
{
	stack <int> path;
	int start = rand()%10;
	int exit = 90 + rand()%10;
	visit[start]=true;
	grid[start].down = true;
	grid[exit].up = true;
	visited++;
	path.push(start);
	while(visited<100)
	{
		int top = path.top();
		int next = move_to_neighbour(top);
		if(next >= 0)
		{
			path.push(next);
		}
		else
		{
			path.pop();
		}
	}
	//cout << "Remaining number of elements in the stack "<< path.size() << "\n";
	//cout << "Last cell visited " << path.top() << "\n"; 
}
void erase_wall( int x, int y, int dest ){

	glColor3f( R, G, B );
	glBegin( GL_LINES );
	
	switch( dest ){

	case 0:
		glVertex2f( (x+1)*10+0.02, (y+2)*10 );
		glVertex2f( (x+2)*10-0.02, (y+2)*10 );
		break;

	case 1:
		glVertex2f( (x+1)*10+0.02, (y+1)*10 );
		glVertex2f( (x+2)*10-0.02, (y+1)*10 );
		break;

	case 2:
		glVertex2f( (x+2)*10, (y+1)*10+0.02 );
		glVertex2f( (x+2)*10, (y+2)*10-0.02 );
		break;

	case 3:
		glVertex2f( (x+1)*10, (y+1)*10+0.02 );
		glVertex2f( (x+1)*10, (y+2)*10-0.02 );
		break;
	}


	glEnd();
}
void draw_maze(){

	int i;
	int x, y;
	for( i = 0 ; i < width*height ; i++ ){
		x = i % width;
		y = i / width;
		if(grid[i].up == true)erase_wall( x, y, 0 );
		if(grid[i].down == true)erase_wall( x, y, 1 );
		if(grid[i].right == true)erase_wall( x, y, 2 );
		if(grid[i].left == true)erase_wall( x, y, 3 ); 
	}
}
/*void display()
{
	double x;

	glClearColor( R, G, B, 0.0 );
	glClear( GL_COLOR_BUFFER_BIT );
	glColor3f( 1-R, 1-G, 1-B );	// the color is the negative of background color

	// draw default(unmaden) maze
	glLoadIdentity();
	glBegin( GL_LINES );
	for( x = 0 ; x < width+2 ; x++ ){
		glVertex2f( x*10, 10.0 );
		glVertex2f( x*10, height*10+10.0 );
	}
	for( x = 0 ; x < height+2; x++ ){
		glVertex2f( 10.0 , x*10 );
		glVertex2f( width*10+10.0 , x*10 );
	}
	glEnd();
	pathfinding();
	draw_maze();
	if(gb_finder != NULL) {
		const double SHIFTFACTOR_X = -10.0;
		const double SHIFTFACTOR_Y = -11.5;

		glLoadIdentity();
		glTranslatef(gb_finder->CurrentX() + SHIFTFACTOR_X, gb_finder->CurrentY() + SHIFTFACTOR_Y, 0);
		glScalef(0.1, 0.1, 1);
		gb_finder->Draw();
	}

//	glutSwapBuffers();
}*/
/*void reshape(int w,int h)
{
	int size = ( width > height )? width : height;
	double move = ( width > height )? ( width-height )/2.0 : ( height-width )/2.0;
	 glViewport(0,0,(GLsizei)w,(GLsizei)h);
	 glMatrixMode(GL_PROJECTION);
	 glLoadIdentity();
	 int view_Left,view_Right,view_Bottom,view_Up;
	 if( width == size ){
			view_Left = 0.0;
			view_Right = 20 + size*10;
			view_Bottom = 0.0 - move*10;
			view_Up = size*10 + 20 - move*10;
		}
		else{
			view_Left = 0.0 - move*10;
			view_Right = 20 + size*10 - move*10;
			view_Bottom = 0.0;
			view_Up = size*10 + 20;
		}
	//gluOrtho2D( view_Left, view_Right, view_Bottom, view_Up );
	 glOrtho(view_Left,view_Right,view_Bottom,view_Up,-1.0,1.0);
	 glMatrixMode((GL_MODELVIEW));
	 glLoadIdentity();
}*/
int main(int argc,char ** argv)
{
	srand( ( unsigned )time( NULL ) );
    glutInit( &argc, argv );
    R = (rand()%256)/ 255.0;
	G =	(rand()%256)/ 255.0;
	B = (rand()%256)/ 255.0;
    glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB );
	glutInitWindowSize ( 500, 500 );
	glutInitWindowPosition (100, 100);
	glutCreateWindow ("miro");
	glutDisplayFunc( display );
	glutReshapeFunc(reshape);
    glutMainLoop();
    return 0;
}