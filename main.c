#include <GL/glut.h>
#include<stdio.h>
#include <math.h>
#include <string.h>

GLint window,window2,Xsize=1000,Ysize=800,nml=0,day=1,light=1;
float i,theta;
GLfloat xt=0.0,yt=0.0,zt=0.0,xw=0.0,xs=1.0,ys=1.0,zs=1.0,xangle=0.0,yangle=0.0,zangle=0.0,angle=0.0,r=0,g=0,b=1;
int count=1,flg=1,view=0,flag1=0,aflag=1,flag2=0,wheelflag=0;
GLUquadricObj *t;

static void SpecialKeyFunc( int Key, int x, int y )
{
	switch ( Key )
	{
	    case GLUT_KEY_RIGHT:if(!wheelflag)
                               xt += 0.2;
                            if(wheelflag)
                            {
                                angle-=5;
                                xw-=0.2;
		                    }
	                        glutPostRedisplay();
		                    break;
		case GLUT_KEY_LEFT:if(!wheelflag)
                              xt -= 0.2;
                            if(wheelflag)
                            {
                                angle+=5;
                                xw+=0.2;
                            }
                            glutPostRedisplay();
		                    break;
    }
}

void drawSquare(void)
{
    glBegin(GL_POLYGON);
    glVertex2f(0.0f, -1.0f);
    glVertex2f(2.0f, 0.0f);
    glVertex2f(0.0f, 1.0f);
    glVertex2f(-2.0f, 0.0f);
    glEnd();
}

void myDraw1(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glColor3f(0.5, 0.5, 0.5);
    drawSquare();
    glTranslatef(2.0, 3.0, 0.0);
    glRotatef(30, 0.0, 0.0, 1.0);
    glColor3f(0.0, 1.0, 0.0);
    drawSquare();
    glTranslatef(2.0, 3.0, 0.0);
    glRotatef(30, 0.0, 0.0, 1.0);
    glFlush();
}

GLvoid Transform(GLfloat Width, GLfloat Height)
{
    glViewport(0, 0, Width, Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0,Width/Height,0.1,100.0);
    glMatrixMode(GL_MODELVIEW);
}

GLvoid InitGL(GLfloat Width, GLfloat Height)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glLineWidth(2.0);
    Transform( Width, Height );
    t=gluNewQuadric();
    gluQuadricDrawStyle(t, GLU_FILL);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat ambientLight[] = { 0.2f, 0.2f, 0.2f, 1.0f };
    GLfloat diffuseLight[] = { 0.8f, 0.8f, 0.8, 1.0f };
    GLfloat specularLight[] = { 0.5f, 0.5f, 0.5f, 1.0f };GLfloat position[] = { 1.5f, 1.0f, 4.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void init()
{
    glClearColor(0,0,0,0);
	glPointSize(5.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0,900.0,0.0,600.0,50.0,-50.0);
}

void display_string(int x, int y, char *string)
{
    int len,i;
	glRasterPos2f(x, y);
    len = (int) strlen(string);
    for (i = 0; i < len; i++)
        glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24,string[i]);
}

void display1(void)
{
	glClearColor(0.0 ,0.0 ,0.0,0.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,1.0,0.0);
	display_string(320,500,"Car 3D Model Project");
	glColor3f(0.0,1.0,0.0);
	display_string(225,340,"4NM17CS080 - Karthik U Kumar");
	display_string(225,280+30,"4NM17CS081 - Kashyap Hebbar");
	display_string(225,250+30,"4NM17CS082 - Kaushik Agarwal");
	glLineWidth(5);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0,0.0,1.0);
	glVertex2f(300,490);
	glVertex2f(540,490);
	glEnd();
	glBegin(GL_POLYGON);
	glColor3f(1.0,1.0,1.0);
	glVertex2f(730,170);
	glVertex2f(860,170);
	glVertex2f(860,200);
	glVertex2f(730,200);
	glEnd();
	glColor3f(0.0,0.0,1.0);
	display_string(750,180,"View Cars");
	glFlush();
	glutPostRedisplay();
	glutSwapBuffers();
}

GLvoid DrawGLScene()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    if(view==0)
    {
        init();
        display1();
    }
    else
    {
        if(count==1)
            InitGL(Xsize,Ysize);
        if(aflag==1)
            glClearColor(1,1,1,1);
        else
            glClearColor(0.1,0.1,0.1,0);
    glPushMatrix();
    glLoadIdentity();
    glTranslatef(-1.0,0.0,-3.5);
    glRotatef(xangle,1.0,0.0,0.0);
    glRotatef(yangle,0.0,1.0,0.0);
    glRotatef(zangle,0.0,0.0,1.0);
    glTranslatef(xt,yt,zt);
    glScalef(xs,ys,zs);
    glEnable(GL_COLOR_MATERIAL);
    if(flag2==1)
    {
        GLfloat fogcolour[4]={1.0,1.0,1.0,1.0};
        glFogfv(GL_FOG_COLOR,fogcolour);
        glFogf(GL_FOG_DENSITY,0.1);
        glFogi(GL_FOG_MODE,GL_EXP);
        glFogf(GL_FOG_START,3.0);
        glFogf(GL_FOG_END,100.0);
        glHint(GL_FOG_HINT, GL_FASTEST);
        glEnable(GL_FOG);
    }
    if(flag2==0)
	  glDisable(GL_FOG);
    if(!aflag)
    {
        glBegin(GL_POINTS);
        glColor3f(1,1,1);
        glPointSize(200.0);
        int ccount=0;
        float x=10,y=10;
        while(ccount<20)
        {
            glVertex2f(x,y);
            x+=10;
	        y+=10;
	        if(y>Ysize)
                y-=10;
            if(x>Xsize)
                x-=10;
	        ccount++;
        }
        glEnd();
    }
    glColor3f(1.0,.75,0.0);
    glPointSize(30.0);
    glBegin(GL_POINTS);
    glVertex3f(0.2,0.3,0.3);
    glVertex3f(0.2,0.3,0.5);
    glEnd();
    glPointSize(200.0);
    glBegin(GL_QUADS);

    glColor3f(r,g,b);
    glVertex3f( 0.2, 0.4,0.6);
    glVertex3f(0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);

    glVertex3f( 0.2,0.4,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f( 0.2,0.2,0.2);

    glVertex3f( 0.2,0.2,0.6);
    glVertex3f(0.2, 0.4,0.6);
    glVertex3f(0.2,0.4,0.2);
    glVertex3f( 0.2,0.2,0.2);

    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.6,0.5,0.2);
    glVertex3f( 0.6,0.2,0.2);

    glVertex3f(0.2,0.2,0.6);
    glVertex3f(0.6,0.2,0.6);
    glVertex3f(0.6,0.5,0.6);
    glVertex3f(0.2,0.4,0.6);

    glVertex3f(0.2,0.2,0.2);
    glVertex3f( 0.6,0.2,0.2);
    glVertex3f( 0.6,0.5,0.2);
    glVertex3f( 0.2,0.4,0.2);
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.2);
    glVertex3f(1.7,0.65,0.6);

    glColor3f(r,g,b);
    glVertex3f( 1.8, 0.5,0.6);
    glVertex3f(1.8, 0.5,0.2);
    glVertex3f(2.1, 0.4, 0.2);
    glVertex3f(2.1,0.4,0.6);

    glVertex3f( 2.1,0.2,0.6);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(1.8,0.2,0.6);
    glVertex3f( 1.8,0.2,0.6);

    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);
    glVertex3f(2.1,0.2,0.6);

    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(2.1,0.4,0.2);
    glVertex3f(2.1,0.2,0.2);

    glVertex3f(1.8,0.2,0.6);
    glVertex3f(1.8,0.5,0.6);
    glVertex3f(2.1,0.4,0.6);
    glVertex3f(2.1,0.2,0.6);

    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.2,0.6);
    glVertex3f(1.8, 0.2, 0.6);
    glVertex3f(1.8,0.5,0.6);

    glVertex3f( 0.6,0.2,0.6);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f( 1.8,0.2,0.6);

    glVertex3f(0.6,0.5,0.2);
    glVertex3f(0.6,0.2,0.2);
    glVertex3f(1.8,0.2,0.2);
    glVertex3f(1.8,0.5,0.2);

    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.2);
    glVertex3f(0.75, 0.5,0.2);
    glVertex3f(1.2, 0.5, 0.2);
    glVertex3f( 1.22,0.63,0.2);
    glVertex3f(1.27,0.63,.2);
    glVertex3f(1.25,0.5,0.2);
    glVertex3f(1.65,0.5,0.2);
    glVertex3f(1.67,0.63,0.2);
    glColor3f(r,g,b);
    glVertex3f(0.7,0.65,0.2);
    glVertex3f(0.7,0.5,.2);
    glVertex3f(0.75,0.5,0.2);
    glVertex3f(0.77,0.65,0.2);
    glVertex3f(1.2,0.65,0.2);
    glVertex3f(1.2,0.5,.2);
    glVertex3f(1.25,0.5,0.2);
    glVertex3f(1.27,0.65,0.2);
    glVertex3f(1.65,0.65,0.2);
    glVertex3f(1.65,0.5,.2);
    glVertex3f(1.7,0.5,0.2);
    glVertex3f(1.7,0.65,0.2);
    glVertex3f( 0.75, 0.65,0.2);
    glVertex3f(0.75, 0.63,0.2);
    glVertex3f(1.7, 0.63, 0.2);
    glVertex3f( 1.7,0.65,0.2);
    glVertex3f( 0.75, 0.65,0.6);
    glVertex3f(0.75, 0.63,0.6);
    glVertex3f(1.7, 0.63, 0.6);
    glVertex3f( 1.7,0.65,0.6);
    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.77, 0.63,0.6);
    glVertex3f(0.75, 0.5,0.6);
    glVertex3f(1.2, 0.5, 0.6);
    glVertex3f( 1.22,0.63,0.6);
    glVertex3f(1.27,0.63,.6);
    glVertex3f(1.25,0.5,0.6);
    glVertex3f(1.65,0.5,0.6);
    glVertex3f(1.67,0.63,0.6);
    glColor3f(r,g,b);
    glVertex3f(0.7,0.65,0.6);
    glVertex3f(0.7,0.5,.6);
    glVertex3f(0.75,0.5,0.6);
    glVertex3f(0.77,0.65,0.6);
    glVertex3f(1.2,0.65,0.6);
    glVertex3f(1.2,0.5,.6);
    glVertex3f(1.25,0.5,0.6);
    glVertex3f(1.27,0.65,0.6);
    glVertex3f(1.65,0.65,0.6);
    glVertex3f(1.65,0.5,.6);
    glVertex3f(1.7,0.5,0.6);
    glVertex3f(1.7,0.65,0.6);
    glEnd();
    glBegin(GL_QUADS);

    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f(0.6, 0.5,0.2);
    glVertex3f(0.7, 0.65, 0.2);
    glVertex3f( 0.7,0.65,0.6);
    glVertex3f(1.7,0.65,.6);
    glVertex3f(1.7,0.65,0.2);
    glVertex3f(1.8,0.5,0.2);
    glVertex3f(1.8,0.5,0.6);

    if(flag1)
    {
        glPushMatrix();
	    glTranslatef(xw,0,0);
        glColor3f(0,1,0);
        glVertex3f(-100,0.1,-100);
        glVertex3f(-100,0.1,0);
        glVertex3f(100,0.1,0);
        glVertex3f(100,0.1,-100);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-100,0.1,0);
        glVertex3f(-100,0.1,0.45);
        glVertex3f(100,0.1,0.45);
        glVertex3f(100,0.1,0);
        glColor3f(1.0,0.75,0.0);
        glVertex3f(-100,0.1,0.45);
        glVertex3f(-100,0.1,0.55);
        glVertex3f(100,0.1,0.55);
        glVertex3f(100,0.1,0.45);
        glColor3f(0.7,0.7,0.7);
        glVertex3f(-100,0.1,0.55);
        glVertex3f(-100,0.1,1);
        glVertex3f(100,0.1,1);
        glVertex3f(100,0.1,0.55);
        glColor3f(0,1,0);
        glVertex3f(-100,0.1,1);
        glVertex3f(-100,0.1,100);
        glVertex3f(100,0.1,100);
        glVertex3f(100,0.1,1);
        glPopMatrix();
    }
    glEnd();

    glBegin(GL_TRIANGLES);

    glColor3f(0.3,0.3,0.3);
    glVertex3f( 0.6, 0.5,0.6);
    glVertex3f( 0.7,0.65,0.6);
    glVertex3f(0.7,0.5,0.6);
    glVertex3f( 0.6, 0.5,0.2);
    glVertex3f( 0.7,0.65,0.2);
    glVertex3f(0.7,0.5,0.2);
    glVertex3f( 1.7, 0.65,0.2);
    glVertex3f( 1.8,0.5,0.2);
    glVertex3f( 1.7,0.5,0.2);
    glVertex3f( 1.7, 0.65,0.6);
    glVertex3f( 1.8,0.5,0.6);
    glVertex3f(1.7,0.5,0.6);
    glEnd();

    glPushMatrix();
    glColor3f(0.3,0.3,0.7);
    glTranslatef(1.65,0.2,0.3);
    glRotatef(90.0,0,1,0);
    gluCylinder(t,0.02,0.03,.5,10,10);
    glPopMatrix();

    glColor3f(0.7,0.7,0.7);
    glPushMatrix();
    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(0.6,0.2,0.62);
        glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(0.6,0.2,0.18);
        glVertex3f(0.6+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(1.7,0.2,0.18);
        glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.18);
    }
    glEnd();
    glBegin(GL_LINE_STRIP);
    for(theta=0;theta<360;theta=theta+40)
    {
        glVertex3f(1.7,0.2,0.62);
        glVertex3f(1.7+(0.08*(cos(((theta+angle)*3.14)/180))),0.2+(0.08*(sin(((theta+angle)*3.14)/180))),0.62);
    }
    glEnd();
    glTranslatef(0.6,0.2,0.6);
    glColor3f(0,0,0);
    glutSolidTorus(0.025,0.07,10,25);
    glTranslatef(0,0,-0.4);
    glutSolidTorus(0.025,0.07,10,25);
    glTranslatef(1.1,0,0);
    glutSolidTorus(0.025,0.07,10,25);
    glTranslatef(0,0,0.4);
    glutSolidTorus(0.025,0.07,10,25);
    glPopMatrix();
    glPopMatrix();
    glEnable(GL_DEPTH_TEST);
    glEnd();
    glFlush();
    glutPostRedisplay();
    glutSwapBuffers();
   }
}

void mouse(int button,int state,int x,int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
       if(x>=799 && x<=942 && y>=499 && y<=534)
       {
            view=1;
            DrawGLScene();
            glutPostRedisplay();
       }
    }
}

void NormalKey(GLubyte key, GLint x, GLint y)
{
    switch ( key )
    {
        case 27 :printf("Escape Pressed.\n");
                 glutDestroyWindow(window);
                 exit(0);
                 break;
        case 13 :view=1;
                 DrawGLScene();
                 break;
        case 'x':xangle += 5.0;
                 glutPostRedisplay();
                 break;
        case 'X':xangle -= 5.0;
                 glutPostRedisplay();
                 break;
        case 'y':yangle += 5.0;
                 glutPostRedisplay();
                 break;
        case 'Y':yangle -= 5.0;
                 glutPostRedisplay();
                 break;
        case 'z':zangle += 5.0;
                 glutPostRedisplay();
                 break;
        case 'Z':zangle -= 5.0;
                 glutPostRedisplay();
                 break;
        case 'U':
        case 'u':yt += 0.2;
                 glutPostRedisplay();
                 break;
        case 'd':
        case  'D':yt -= 0.2;
                  glutPostRedisplay();
                  break;
        case 'F':
        case 'f':zt += 0.2;
                 glutPostRedisplay();
                 break;
        case 'b':
        case 'B':zt -= 0.2;
                 glutPostRedisplay();
                 break;
        default:break;
    }
}

void myMenu(int id)
{
    if (id==1)
	{
		flag1=0;
		wheelflag=0;
	    glutPostRedisplay();
	}
	if(id ==2)
	{
		flag1=1;
		flag2=0;
		wheelflag=0;
		xangle += 5.0;
		glutPostRedisplay();
	}
	if (id==3)
	{
		 wheelflag=1;
		 glutPostRedisplay();
	}
	if(id==14)
	{
	    aflag=1;
        day=1;
        glClearColor(1,1,1,1);
        glDisable(GL_FOG);
        glutPostRedisplay();
	}
	if(id==15)
	{
	    aflag=0;
        day=0;
        flag2=2;
	    glClearColor(0.1,0.1,0.1,0);
	    GLfloat fogcolour[4]={0.0,0.0,0.0,1.0};
	    glFogfv(GL_FOG_COLOR,fogcolour);
	    glFogf(GL_FOG_DENSITY,0.5);
	    glFogi(GL_FOG_MODE,GL_EXP);
	    glHint(GL_FOG_HINT, GL_FASTEST);
	    glEnable(GL_FOG);
	    glutPostRedisplay();
    }
    if(id==16)
    {
        glutDestroyWindow(window);
        exit(0);
    }
}

void colorMenu(int id)
{
    if (id==4)
	{
		r=g=0;
		b=1;
		glutPostRedisplay();
    }
	if(id ==5)
	{
		r=0.8;
		b=g=0;
		glutPostRedisplay();
	}
	if(id==6)
	{
	    g=1;
		r=b=0;
		glutPostRedisplay();
	}
	if (id==7)
	{
		 r=b=g=0;
		 glutPostRedisplay();
	}
	if(id==8)
	{
		b=0;
		r=g=1;
        glutPostRedisplay();
	}
	if(id==9)
	{
		b=r=g=.7;
        glutPostRedisplay();
	}
	if(id==10){
        r=1.0;
        g=0.5;
        b=0.0;
        glutPostRedisplay();
	}
	if(id==11){
        r=0.0;
        g=b=1.0;
        glutPostRedisplay();
	}
	if(id==12){
        b=r=1.0;
        g=0.0;
        glutPostRedisplay();
	}
	if(id==13){
        r=1.0;
        b=0.5;
        g=0.0;
        glutPostRedisplay();
	}
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB);
  glutInitWindowSize(Xsize,Ysize);
  glutInitWindowPosition(50,50);
  glutCreateWindow("3D CAR ANIMATION");
  glutDisplayFunc(DrawGLScene);
  glutMouseFunc(mouse);
  glutKeyboardFunc(NormalKey);
  glutSpecialFunc( SpecialKeyFunc );
  int submenu=glutCreateMenu(colorMenu);
  glutAddMenuEntry("Blue", 4);
	glutAddMenuEntry("Red", 5);
	glutAddMenuEntry("Green",6);
	glutAddMenuEntry("Black",7);
	glutAddMenuEntry("Yellow",8);
	glutAddMenuEntry("Pink",13);
	glutAddMenuEntry("Grey",9);
	glutAddMenuEntry("Orange",10);
	glutAddMenuEntry("Cyan",11);
	glutAddMenuEntry("Purple",12);

  glutCreateMenu(myMenu);
	glutAddMenuEntry("Car Model Mode", 1);
	glutAddMenuEntry("Driving Mode", 2);
	glutAddMenuEntry("Wheel Effect",3);
	glutAddSubMenu("Colors",submenu);
	glutAddMenuEntry("Day Mode On",14);
	glutAddMenuEntry("Night Mode On",15);
	glutAddMenuEntry("Exit",16);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
  glutMainLoop();
  return 0;
}
