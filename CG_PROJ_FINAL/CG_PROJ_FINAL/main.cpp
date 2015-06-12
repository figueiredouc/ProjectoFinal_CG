#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <iostream>

float width=800;
float height=600;

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
    gluLookAt(5.0,25.0,5.0, 0, 0, 0, 0.0, 1.0, 0.0);
    
    /******************************************/
    
    
}

void init() {
    
    Casa house;
    
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