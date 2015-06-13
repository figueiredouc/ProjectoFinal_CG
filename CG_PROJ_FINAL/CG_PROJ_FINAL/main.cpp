#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>


 GLfloat GREEN[] = {1, 0, 0};

float width=800;
float height=600;


class Bola{
    
    double raio;
    GLfloat* cor;

    public:double x;
    double y;
    double z;
    int direction;
    
    
public:
    Bola(double raio, GLfloat* cor, double x, double y,double z):
        raio(raio),
        cor(cor),
        direction(-1),
        x(x),
        y(y),
        z(z) {}

    
    void update(){
        
        x+=0.1;
       
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor);
        glTranslated(x, y, z);
        glutSolidSphere(raio, 30, 30);
        glPopMatrix();
    }
    
};



class Casa{
    
    int altura;
    int comprimento;
    int largura;
    
public:
    
    void set_values(int a,int c,int l){
        
        altura=a;
        comprimento=c;
        largura=l;
        
    }
    
    int area(){
        return comprimento*largura;
    }
    
    void draw(){
        
        glColor4f(1.0, 1.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, 8.0);
        glVertex3f(8.0, 0.0, 8.0);
        glVertex3f(8.0, 0.0, 0.0);
        
        glEnd();
        
    }
    
};

// provisório



//Declaração de Objectos

Bola bola = Bola(1,GREEN,0.0,0.0,0.0);





void projection(){
    
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
    
    /********** Janela de Visualisação *********/
    
    glViewport(0, 0, width, height);
    
    /*******************************************/
    
    /*************** Prespectiva ***************/
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0,width/height, 1.0,100.0);
    
    /*******************************************/
    
    
    /*************** Observador ***************/
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(5.0,5.0,5.0, 0, 0, 0, 0.0, 1.0, 0.0);
    
    /******************************************/
    
    glutSwapBuffers();

}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    bola.update();
    printf("bola.x -> %f \n",bola.x);
    glutSwapBuffers();
}

void init() {
    projection();
    }

void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(width,height);
    glutCreateWindow("Projecto Final CG");
    glEnable(GL_DEPTH_TEST);
    glutTimerFunc(100, timer, 0);
    init();
    glutDisplayFunc(display);
    
    
    glutMainLoop();
}