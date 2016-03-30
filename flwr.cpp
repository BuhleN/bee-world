#include <windows.h>
#include <gl/gl.h>
//#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <mmsystem.h>
#define th1 512
#define tw1 512
#define PI 3.14159
static GLubyte texImg[th1][tw1][3];
int rx=0,ry=0,rz=0,var=0;
float alfa=0,ratio=0.5,enable_kb_rot=0;
GLfloat texpts[2][2][2] = {{{0.0, 0.0}, {0.0, 1.0}},
{{1.0, 0.0}, {1.0, 1.0}}};

GLint nNumPoints = 5;
GLfloat ctrlPoints[5][4][3]= {{{ -1.0f, 0.0f, 4.0f},
{ -0.5f, 1.0f, 4.0f},
{ 0.5f, 1.0f, 4.0f},
{ 1.0f, 0.0f, 4.0f }},

{{ -5.0f,2.0f, 3.0f},
{ -4.0f, 6.0f, 3.5f},
{ 4.0f, 6.0f, 3.5f},
{ 5.0f, 2.0f, 3.0f }},

{{ -5.5f, 1.5f, -2.5f},
{ -2.0f, 4.0f, -2.5f},
{ 2.0f, 4.0f, -2.5f},
{ 5.5f, 1.5f, -2.5f }},

{{ -4.5f, 4.0f, -4.0f},
{ -2.0f, 5.5f, -4.0f},
{ 2.0f, 5.5f, -4.0f},
{ 4.5f, 4.0f, -4.0f }},

{{ -3.5f, 4.5f, -3.0f},
{ -2.0f, 5.0f, -2.0f},
{ 2.0f, 5.0f, -2.0f},
{ 3.5f, 4.5f, -3.0f }}};

GLfloat rose[8][5][4][3];

void genRose(void)
{
int i,j,k,l;
float a;
for (i=0;i<8;i++)
{
 a=(float)2*PI/i;
 for (j=0;j<5;j++)
  for (k=0;k<4;k++)
  {
       rose[i][j][k][0]=0.5*a;
  }
}
}

void sfera(float x,float y,float z,float r)
{
float i,j;
glBegin(GL_QUADS);
for (i=0;i<=20;i++)
 for (j=0;j<=20;j++)
  {
  glVertex3f(x+r*sin(PI*i/10)*sin(PI*j/10),y+r*sin(PI*i/10)*cos(PI*j/10),z+r*cos(PI*i/10));
  glVertex3f(x+r*sin(PI*(i+1)/10)*sin(PI*j/10),y+r*sin(PI*(i+1)/10)*cos(PI*j/10),z+r*cos(PI*(i+1)/10));
  glVertex3f(x+r*sin(PI*(i+1)/10)*sin(PI*(j+1)/10),y+r*sin(PI*(i+1)/10)*cos(PI*(j+1)/10),z+r*cos(PI*(i+1)/10));
  glVertex3f(x+r*sin(PI*i/10)*sin(PI*(j+1)/10),y+r*sin(PI*i/10)*cos(PI*(j+1)/10),z+r*cos(PI*i/10));
  }
glEnd();
}

void cilindru(float x1,float y1,float z1,float x2,float y2,float z2,float r1,float r2)
{
 int i;
 /*glBegin(GL_LINE_LOOP);
 for (i=0;i<100;i++)
  glVertex3f(x1+r1*sin(PI*i/50),y1,z1+r1*cos(PI*i/50));
 glEnd();
 glBegin(GL_LINE_LOOP);
 for (i=0;i<100;i++)
  glVertex3f(x2+r2*sin(PI*i/50),y2,z2+r2*cos(PI*i/50));
 glEnd();*/
 glBegin(GL_QUADS);
 for (i=0;i<100;i++)
 {
  glVertex3f(x1+r1*sin(PI*i/50),y1,z1+r1*cos(PI*i/50));
  glVertex3f(x2+r2*sin(PI*i/50),y2,z2+r2*cos(PI*i/50));
  glVertex3f(x2+r2*sin(PI*(i+1)/50),y2,z2+r2*cos(PI*(i+1)/50));
  glVertex3f(x1+r1*sin(PI*(i+1)/50),y1,z1+r1*cos(PI*(i+1)/50));
 }
  glEnd();
}

void DrawPoints(void)
{
int i,j;
glPointSize(5.0f);
glBegin(GL_POINTS);
for(i = 0; i < nNumPoints; i++)
for(j = 0; j < 4; j++)
glVertex3fv(ctrlPoints[i][j]);
glEnd();
}

void progresiv(GLubyte texImg[512][512][3],GLuint h,GLuint w)
{
 int i,j;
for (i=0;i<128;i++)
 for(j=i;j<=128;j++)
  {texImg[2*j][i][0]=255-2*(j-i);
  texImg[2*j+1][i][0]=255-2*(j-i);
  texImg[512-2*j][i][0]=255-2*(j-i);
  texImg[512-2*j+1][i][0]=255-2*(j-i);
  }
}

void lcxGetTex(char *s,GLubyte texImg[512][512][3],GLuint h,GLuint w)
{
FILE *f;
GLuint i,j,k;
GLubyte data;
//f=fopen(s,"rb");
for (i=0;i<w;i++)
 for (j=0;j<h;j++)
 {
 texImg[j][i][0]=255;
 texImg[j][i][1]=(GLubyte)(255*i/w*i/w);
 texImg[j][i][2]=(GLubyte)0;
 }
 progresiv(texImg,h,w);
//fclose(f);
}


void ptl(int alfax,int alfay,int alfaz,float tx,float ty,float tz)
{
// Enable the evaluator
glPushMatrix();
glTranslatef(tx,ty,tz);
glRotatef(alfay,0,1,0);
glRotatef(alfaz,0,0,1);
glPushMatrix();
glRotatef(alfax,1,0,0);
glEnable(GL_MAP2_VERTEX_3);
glMap2f(GL_MAP2_VERTEX_3,0.0f,10.0f,3,4,0.0f,10.0f,12,5,&ctrlPoints[0][0][0]);
glMap2f(GL_MAP2_TEXTURE_COORD_2,0.0f,10.0f,2,2,0.0f,10.0f,4,2,&texpts[0][0][0]);
glEnable(GL_MAP2_TEXTURE_COORD_2);
glEnable(GL_MAP2_VERTEX_3);
glMapGrid2f(10,0.0f,10.0f,10,0.0f,10.0f);
glEvalMesh2(GL_FILL,0,10,0,10);
glEnable(GL_AUTO_NORMAL);
//Draw the Control Points
//DrawPoints();
glPopMatrix();
glPopMatrix();
}

void flwr()
{
int i;
//glRotatef(20,0,1,0);
for (i=0;i<6;i++)
ptl(0,0,60*i-70,2*cos(PI*i/3),2*sin(PI*i/3),0.0);
glPushMatrix();
//redraw(step);
for (i=0;i<6;i++)
ptl(0,0,60*i-60,1*cos(PI*i/3),1*sin(PI*i/3),-1.0);
glPopMatrix();
}

void coada(float x,float y,float z,float h,float w)
{
 float i;

for (i=0;i<100;i++)
{cilindru(x,y+h*i/100,z,x,y+h*(i+1)/100,z,w*sin(PI/2*i/100),w*sin(PI/2*(i+1)/100));
glColor3f(0,0.6-(float)i/200,0);}
glColor3f(0,0.4,0);
for (i=0;i<100;i++)
 cilindru(x+0.2*(1-cos(PI/2*(float)i/100)),y+0.3-1*i/100,0,x+0.2*(1-cos(PI/2*(float)(i+1)/100)),y+0.3-1*(i+1)/100,0,0.1,0.1);
}

void detalii(float x,float y,float z,float r,float r1,float h)
{
 float i,j;
for (i=0;i<5;i++)
 for (j=0;j<10;j++)
 { glColor3f(0.9+(float)i/20,0.9,0);
  cilindru(x+r*i/5*sin(PI*j/5+PI/2*i/5),y,z+r*i/5*cos(PI*j/5+PI/2*i/5),x+r1*i/5*sin(PI*j/5+PI/2*i/5),y+h+0.2*h*cos(PI*i/5),z+r1*i/5*cos(PI*j/5+PI/2*i/5),0.03,0.009);
 glColor3f(0.7+(float)i/20,1,0);
  sfera(x+r1*i/5*sin(PI*j/5+PI/2*i/5),y+h+0.2*h*cos(PI*(float)i/5),z+r1*i/5*cos(PI*j/5+PI/2*i/5),0.02);
 }
sfera(0,-0.6,0,0.3);
}

void RenderScene(HDC hDC)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glPushMatrix();
glScalef(0.5,0.5,0.5);
if (enable_kb_rot)
 {glRotatef(rx,1,0,0);
glRotatef(ry,0,1,0);
glRotatef(rz,0,0,1);
}
glRotatef(-25,1,0,0.4);
glRotatef(alfa,0,1,0);
glPushMatrix();
glScalef(0.2,0.2,0.2);
glRotatef(90,1,0,0);
glDisable(GL_TEXTURE_2D);
glEnable(GL_TEXTURE_2D);
flwr();
glPopMatrix();
glDisable(GL_TEXTURE_2D);
coada(0,-1.1,0,0.3,0.52);
//sfera(0,0,0,1);
detalii(0,-0.2,0,0.3,0.6,0.5);
glRotatef(20,1,0,0);
glPopMatrix();

SwapBuffers(hDC);
}
void keyboard(unsigned char key,int x,int y)
{
 //rx=0;ry=0;rz=0;
 switch (key)
 {
 case 0x51:rx++;break;//q
 case 0x41:rx--;break;//a
 case 0x57:ry++;break;//w
 case 0x53:ry--;break;//s
 case 0x45:rz++;break;//e
 case 0x44:rz--;break;//d
 case 0x52:ratio+=0.1;break;//r
 case 0x46:ratio-=0.1;break;//f
 case 0x4b:if (enable_kb_rot) enable_kb_rot=0;//k
     else enable_kb_rot=1;break;
 default: break;
 }

glLoadIdentity();
}

void init(void)
{
glClearColor (0.0, 0.0, 0.0, 0.0);
lcxGetTex("3242.raw",texImg,th1,tw1);

glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tw1,th1,0,GL_RGB,GL_UNSIGNED_BYTE,texImg);
glEnable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST);
glShadeModel (GL_FLAT);
}
void idle()
{
 if (alfa>=360) alfa=0;
alfa+=ratio;
//glutPostRedisplay();
}


/**************************
 * Function Declarations
 *
 **************************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{

    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;
    MSG msg;

    BOOL bQuit = FALSE;
    float theta = 0.0f;
    //bQuit=!sndPlaySound("toutput.wav",SND_ASYNC);
    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "OpenGL Sample",
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 400, 400,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);

    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            /* OpenGL animation code goes here */
            if (alfa>=360) alfa=0;
            alfa+=ratio;
            RenderScene(hDC);

            //SwapBuffers (hDC);

        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;


    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        keyboard(wParam,0,0);
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );
    lcxGetTex("3242.raw",texImg,th1,tw1);

    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,tw1,th1,0,GL_RGB,GL_UNSIGNED_BYTE,texImg);
glEnable(GL_TEXTURE_2D);
glEnable(GL_DEPTH_TEST);
glShadeModel (GL_FLAT);


}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}

