#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>


 GLfloat GREEN[] = {1, 0, 0};

float width=800;
float height=600;


class Camera{
    
    double teta;
    double y;
    double dTeta;
    double dY;
    
public:
    
    void set_values(double t,double yp,double dt,double dyp){
        
        teta=t;
        y=yp;
        dTeta=dt;
        dY=dyp;
        
    }
    
    double getX(){
        return 10 * cos(teta);
    }
    
    double getY(){
        return y;
    }
    
    double getZ(){
        return 10 * sin(teta);
    }
    
    void moveRight(){
        teta += dTeta;
    }
    
    void moveLeft(){
        teta -= dTeta;
    }
    void moveUp(){
        y += dY;
    }
    void moveDown(){
        if (y>dY)
            y -= dY;
    }
};

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
        
        y += direction * 0.05;
        
        if (y > 5) {
            y = 5; direction = -1;
        } else if (y < raio) {
            y = raio; direction = 1;
        }
       
        glPushMatrix();
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, cor);
        glTranslated(x, y, z);
        glutSolidSphere(raio, 30, 30);
        glPopMatrix();
    }
    
};

class Casa{
    
    float altura;
    float comprimento;
    float largura;
    
public:
    
    void set_values(float a,float c,float l){
        
        altura=a;
        comprimento=c;
        largura=l;
        
    }
    
    int area(){
        return comprimento*largura;
    }
    
    void draw(){
        
        glColor4f(1.0, 0.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, 0.0, largura);
        glVertex3f(comprimento, 0.0, largura);
        glVertex3f(comprimento, 0.0, 0.0);
        
        glEnd();
        
        
        glColor4f(0.0, 1.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, altura, 0.0);
        glVertex3f(comprimento, altura, 0.0);
        glVertex3f(comprimento, 0.0, 0.0);
        
        glEnd();
        
        
        glColor4f(0.0, 0.0, 1.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(0.0, 0.0, 0.0);
        glVertex3f(0.0, altura, 0.0);
        glVertex3f(0.0, altura, largura);
        glVertex3f(0.0, 0.0, largura);
        
        glEnd();
        
        glColor4f(0.0, 0.0, 1.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(comprimento, 0.0, 0.0);
        glVertex3f(comprimento, altura, 0.0);
        glVertex3f(comprimento, altura, largura);
        glVertex3f(comprimento, 0.0, largura);
        
        glEnd();
        
        glColor4f(0.0, 1.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(0.0, 0.0, largura);
        glVertex3f(0.0, altura, largura);
        glVertex3f(comprimento, altura, largura);
        glVertex3f(comprimento, 0.0, largura);
        
        glEnd();
        
        glColor4f(1.0, 0.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(0.0, altura, 0.0);
        glVertex3f(0.0, altura, largura);
        glVertex3f(comprimento, altura, largura);
        glVertex3f(comprimento, altura, 0.0);
        
        glEnd();
        
    }
    
};

// provisório



//Declaração de Objectos

Bola bola = Bola(1,GREEN,0.0,0.0,0.0);

Casa house;

Camera cam;


void projection(){
    
    glLoadIdentity();

    gluLookAt(cam.getX(),cam.getY(),cam.getZ(), 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    
    

}

void reshape(GLint w, GLint h){
    
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(40.0, GLfloat(w)/GLfloat(h), 1.0, 150.0);
    glMatrixMode(GL_MODELVIEW);
}

void display(){
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    projection();
    house.draw();
    bola.update();
    glutSwapBuffers();
}

void init() {

    cam.set_values(0, 10, 0.04, 0.2);
    
    
    
    house.set_values(8.0, 8.0, 8.0);
    

}

void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

void special(int key, int, int) {
    switch (key) {
        case GLUT_KEY_LEFT: cam.moveLeft();  break;
        case GLUT_KEY_RIGHT: cam.moveRight(); break;
        case GLUT_KEY_UP: cam.moveUp(); break;
        case GLUT_KEY_DOWN: cam.moveDown(); break;
       /* case 'a' : look_to_left(); break;
        case 's' : look_to_down(); break;
        case 'd' : look_to_righ(); break;
        case 'w' : look_to_up(); break;*/
    }
    glutPostRedisplay();
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
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    
    glutMainLoop();
}