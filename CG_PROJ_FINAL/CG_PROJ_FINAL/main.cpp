#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>
#include <cmath>

float width=800;
float height=600;

class Camera{
    
    double teta;
    double y;
    double dTeta;
    double dY;
    
public:
    
    Camera(double t,double yp,double dt,double dyp){
        
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
    gluLookAt(8.0,4.0,8.0, 0, 4.0, 0, 0.0, 1.0, 0.0);
    
    /******************************************/
    
    
}

void init() {
    
    Casa house;
    
    house.set_values(8.0, 8.0, 8.0);
    
    projection();
    
    house.draw();
    
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char** argv) {
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(80, 80);
    glutInitWindowSize(width,height);
    glutCreateWindow("Projecto Final CG");
    glEnable(GL_DEPTH_TEST);
   
    glutDisplayFunc(init);
    
    
    glutMainLoop();
}