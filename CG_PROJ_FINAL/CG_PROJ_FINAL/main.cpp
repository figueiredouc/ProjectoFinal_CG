#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>
#include "RgbImage.h"
# define PI 3.14159265358979323846

GLfloat GREEN[] = {1, 0, 0};
GLuint texture;

float width=800;
float height=600;



class Camera{
    
    double teta;
    double y;
    double dTeta;
    double dY;
    double raio;
    
public:
    
    void set_values(double t,double yp,double dt,double dyp,double r){
        
        teta=t;
        y=yp;
        dTeta=dt;
        dY=dyp;
        raio=r;
        
    }
    
    double getX(){
        return raio * cos(teta);
    }
    
    double getY(){
        return y;
    }
    
    double getZ(){
        return raio * sin(teta);
    }
    
    void moveRight(){
        if(teta<1.4)
            teta += dTeta;
    }
    
    void moveLeft(){
        if(teta>0.1)
            teta -= dTeta;
    }
    void moveUp(){
        //if(y<raio)
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

class Caixa{
    
    float lado;
    float x;
    float z;
    float direction;
    float max;
    
public:
    
    void set_values(float l,float a, float b, float maxZ){
        
        lado=l;
        x=a;
        z=b;
        max=maxZ;
        direction=-1;
    }
    
    void drawBox(){
        
        glColor4f(0.0, 0.0, 0.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(x-(lado/2), 1, z+(lado/2));
        glVertex3f(x+(lado/2), 1.0, z+(lado/2));
        glVertex3f(x+(lado/2), 1.0, z-(lado/2));
        glVertex3f(x-(lado/2), 1.0, z-(lado/2));
        
        glEnd();
        
        
        glColor4f(0.0, 1.0, 1.0, 0.0);
        
        glBegin(GL_QUADS);
        
        glVertex3f(x-(lado/2), 1.0, z+(lado/2));
        glVertex3f(x-(lado/2), lado+1, z+(lado/2));
        glVertex3f(x+(lado/2), lado+1, z+(lado/2));
        glVertex3f(x+(lado/2), 1.0, z+(lado/2));
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        glVertex3f(x+(lado/2), 1.0, z+(lado/2));
        glVertex3f(x+(lado/2), lado+1, z+(lado/2));
        glVertex3f(x+(lado/2), lado+1, z-(lado/2));
        glVertex3f(x+(lado/2), 1.0, z-(lado/2));
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        glVertex3f(x-(lado/2), 1.0, z-(lado/2));
        glVertex3f(x-(lado/2), lado+1, z-(lado/2));
        glVertex3f(x+(lado/2), lado+1, z-(lado/2));
        glVertex3f(x+(lado/2), 1.0, z-(lado/2));
        
        glEnd();
        
        glBegin(GL_QUADS);
        
        glVertex3f(x-(lado/2), 1.0, z+(lado/2));
        glVertex3f(x-(lado/2), lado+1, z+(lado/2));
        glVertex3f(x-(lado/2), lado+1, z-(lado/2));
        glVertex3f(x-(lado/2), 1.0, z-(lado/2));
        
        glEnd();
        
    }
    
    void update(){
        
        z += direction * 0.05;
        
        printf("z:%f\n",z);
        
        if ((z+lado/2) > max) {
            printf("entra");
            z = max-lado/2;
            direction = -1;
        }
        else if ((z-lado/2) < 0) {
            z = 0+lado/2;
            direction = 1;
        }
        
        glPushMatrix();
        glTranslated(0, 0, z);
        drawBox();
        glPopMatrix();
    }
};

class Casa{
    
    float lado;
    
public:
    
    void set_values(float raio){
        
        lado=raio;
        
    }
    
    float getLado(){
        return lado;
    }
    
    void draw(){
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, 0.0, lado);
        glTexCoord2f(1.0, 1.0); glVertex3f(lado, 0.0, lado);
        glTexCoord2f(0.0, 1.0); glVertex3f(lado, 0.0, 0.0);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, lado, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(lado, lado, 0.0);
        glTexCoord2f(0.0, 1.0); glVertex3f(lado, 0.0, 0.0);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, lado, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(0.0, lado, lado);
        glTexCoord2f(0.0, 1.0); glVertex3f(0.0, 0.0, lado);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0, 0.0); glVertex3f(lado, 0.0, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(lado, lado, 0.0);
        glTexCoord2f(1.0, 1.0); glVertex3f(lado, lado, lado);
        glTexCoord2f(0.0, 1.0); glVertex3f(lado, 0.0, lado);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
       
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, 0.0, lado);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, lado, lado);
        glTexCoord2f(1.0, 1.0); glVertex3f(lado, lado, lado);
        glTexCoord2f(0.0, 1.0); glVertex3f(lado, 0.0, lado);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
        
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glBegin(GL_QUADS);
        
        
        glTexCoord2f(0.0, 0.0); glVertex3f(0.0, lado, 0.0);
        glTexCoord2f(1.0, 0.0); glVertex3f(0.0, lado, lado);
        glTexCoord2f(1.0, 1.0); glVertex3f(lado, lado, lado);
        glTexCoord2f(0.0, 1.0); glVertex3f(lado, lado, 0.0);
        
        glEnd();
        glDisable(GL_TEXTURE_2D);
    }
    
};

//Declaração de Objectos

Bola bola = Bola(1,GREEN,0.0,0.0,0.0);

Casa house;

Camera cam;

Caixa box;

bool inicialSet=true;



void projection(){
    
    glLoadIdentity();
    
    gluLookAt(cam.getX(),cam.getY(),cam.getZ(), 25.0, 5.0, 50.0, 0.0, 1.0, 0.0);
    
    
    //printf("camera(%f,%f,%f)\n",cam.getX(),cam.getY(),cam.getZ());
    
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
    box.update();
    
    glBegin(GL_LINES);
    
    glVertex3f(25.0, 0, 50);
    glVertex3f(25.0, 1000, 50);
    glEnd();
    
    glutSwapBuffers();
}

void criaTextura(){
    
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    RgbImage imag("/Users/gabrieloliveira/Documents/UC/CG/ProjectoFinal_CG/mamas.bmp");
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imag.GetNumCols(), imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
    
}

void init() {
    
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_TEXTURE_2D);
    
    criaTextura();
    house.set_values(50.0);
    cam.set_values(PI/4, house.getLado()-5, 0.04, 0.5,house.getLado());
    box.set_values(10, 25, 25,house.getLado());
    
    printf("camera(%f,%f,%f)\n",cam.getX(),cam.getY(),cam.getZ());
    
    

}

void timer(int v) {
    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, v);
}

void special(int key, int, int) {
    switch (key) {
        case GLUT_KEY_RIGHT: cam.moveLeft(); break;
        case GLUT_KEY_LEFT: cam.moveRight(); break;
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
    
    glutTimerFunc(100, timer, 0);
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutSpecialFunc(special);
    
    glutMainLoop();
}