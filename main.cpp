#include<windows.h>
#include <stdlib.h>
#include<GL/glut.h>
#include<math.h>

void init(void);
void tampil(void);
void mouse (int button, int state, int x,int y);
void keyboard(unsigned char,int,int);
void ukuran(int,int);
void mouseMotion(int x, int y);
void lantai();
void entrance();
void taman();
void tamanDalam();
void tengah_tingkat_1();
void pilar_tengah();
void tengah_tingkat_2();
void seperempatBola(int scaley, int scalex, GLfloat r);
void setengahLingkaran();
void lisSetengahLingkaran();
void lisKacaDome();
void mobil();
void timer();

float x_pos = 0.0f;
float delta = 0.025f;

float xrot = 0.0f;
float yrot = 0.0f;
float xdiff = 0.0f;
float ydiff = 0.0f;
bool mouseDown = false;

int is_depth;


int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(250,80);
    glutCreateWindow("ALPHA FAUSTA IKRAR SETYADI - 672019219");
    init();

    //glutTimerFunc(0, timer, 0);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glutDisplayFunc(tampil);
    glutReshapeFunc(ukuran);

    glutKeyboardFunc(keyboard);

    glutMouseFunc(mouse);
    glutMotionFunc(mouseMotion);

    glLineWidth(2.0);

    glutMainLoop();
    return 0;
}

void init(void){
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);

    // lighting
    //glEnable(GL_LIGHTING);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHT0);

    glEnable(GL_DEPTH_TEST);
    is_depth=1;

    glMatrixMode(GL_MODELVIEW);

    glPointSize(9.0);
    glLineWidth(6.0f);
}

void tampil(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    glRotatef(xrot, 1.0f,0.0f,0.0f);
    glRotatef(yrot, 0.0f, 1.0f,0.0f);
    glTranslatef(-87.50,0.0,-29.0);

    //Fungsi Alpha==========================================================================
    lantai(); //lantai dasar untuk pemetaan
    taman(); //taman depan
    tamanDalam(); //taman area hijau
    entrance();
    tengah_tingkat_1(); //lt 1 di bawah dome
    pilar_tengah();
    tengah_tingkat_2(); //lt2 di bawah dome (sejajar dome)


    glPushMatrix();
    glColor4f(0.95,0.75,0.95,0.95);
    glTranslatef(77.75, 8.0, 15.01);
    glRotatef(270.0, 0.0, 0.0, 0.01);
    setengahLingkaran(); //kaca setengah lingkaran
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.9,0.9,0.9);
    glTranslatef(77.75, 8.0, 15.0);
    glRotatef(90.0, 0.0, 0.0, 0.01);
    lisSetengahLingkaran(); //lis kaca setengah lingkaran
    glPointSize(5);
    glPopMatrix();

    glPushMatrix();
    glColor3f(0.9,0.7,0.5);
    glTranslatef(77.75,8.0,15.0);
    glRotatef(-0.8, 0.01, 0.0, 0);
    glRotatef(179.0, 0, 0.01, 0);
    seperempatBola(100, 100,10.25); //dome
    glPopMatrix();

    lisKacaDome();
    mobil();
    //========================================================================================

    glPopMatrix();
    glutSwapBuffers();
}

void timer(int){
    glutPostRedisplay();
    glutTimerFunc(100/30, timer, 0);
    x_pos += delta;
}

void lantai(){
    //Tanah
    glBegin(GL_QUADS);
    glColor3f(0.8, 0.8, 0.8);
    glVertex3f(00.0, -0.02, 00.0);
    glVertex3f(175.0, -0.02, 00.0);
    glVertex3f(175.0, -0.02, 58.0);
    glVertex3f(00.0, -0.02, 58.0);
    glEnd();

    //Lantai dasar MALL UTAMA
    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(67.50, 0.0, 0.0);
    glVertex3f(67.50, 0.0, 17.0);
    glVertex3f(17.0, 0.0, 17.0);
    glVertex3f(17.0, 0.0, 52.0);
    glVertex3f(0.0, 0.0, 52.0);
    glEnd();

    //Lantai dasar DOME
    glBegin(GL_POLYGON);
    glColor3f(0.6, 0.6, 0.6);
    glVertex3f(67.50, 0.0, 0.0);
    glVertex3f(88.0, 0.0, 0.0);
    glVertex3f(88.0, 0.0, 17.0);
    glVertex3f(67.50, 0.0, 17.0);
    glEnd();

    //Lantai dasar MALL TAMBAHAN
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(88.0, 0.0, 00.0);
    glVertex3f(88.0, 0.0, 17.0);
    glVertex3f(151.0, 0.0, 17.0);
    glVertex3f(151.0, 0.0, 0.0);

    glVertex3f(135.0, 0.0, 17.0);
    glVertex3f(151.0, 0.0, 17.0);
    glVertex3f(151.0, 0.0, 27.0);
    glVertex3f(135.0, 0.0, 27.0);

    glVertex3f(135.0, 0.0, 27.0);
    glVertex3f(172.0, 0.0, 27.0);
    glVertex3f(172.0, 0.0, 44.0);
    glVertex3f(135.0, 0.0, 44.0);
    glEnd();

    //Jalan raya
    glBegin(GL_QUADS);
    glColor3f(0.3, 0.3, 0.3);
    glVertex3f(00.0, 0.0, 67.0);
    glVertex3f(175.0, 0.0, 67.0);
    glVertex3f(175.0, 0.0, 58.0);
    glVertex3f(00.0, 0.0, 58.0);
    glEnd();

    //Marka jalan
    for(int i = 0; i <= 16; i+=2){
        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(00.0+10*i, 0.01, 62.75);
        glVertex3f(10.0+10*i, 0.01, 62.75);
        glVertex3f(10.0+10*i, 0.01, 62.25);
        glVertex3f(00.0+10*i, 0.01, 62.25);
        glEnd();
    }

}

void taman(){
    //Dasar=====================================================================================================================
    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUADS);
        glVertex3f(17.0, 0.0, 17.0);
        glVertex3f(135.0, 0.0, 17.0);
        glVertex3f(135.0, 0.0, 58.0);
        glVertex3f(17.0, 0.0, 58.0);
    glEnd();

    //Dasar=====================================================================================================================
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
        glVertex3f(27.0, 0.01, 18.0);
        glVertex3f(125.0, 0.01, 18.0);
        glVertex3f(125.0, 0.01, 20.5);
        glVertex3f(27.0, 0.01, 20.5);
    glEnd();

    //Kolam 1==================================================================================================================
    glColor4f(0.0, 0.0, 1.0, 0.7);
    glPushMatrix();
    glTranslatef(0.0, 0.0, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(19.5, 0.2, 32.0);
        glVertex3f(24.5, 0.2, 32.0);
        glVertex3f(24.5, 0.2, 42.0);
        glVertex3f(19.5, 0.2, 42.0);
    glEnd();
    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
        glVertex3f(19.5, 0.3, 42.0);
        glVertex3f(19.5, 0.0, 42.0);
        glVertex3f(24.5, 0.0, 42.0);
        glVertex3f(24.5, 0.3, 42.0);

        glVertex3f(19.5, 0.3, 32.0);
        glVertex3f(19.5, 0.0, 32.0);
        glVertex3f(24.5, 0.0, 32.0);
        glVertex3f(24.5, 0.3, 32.0);

        glVertex3f(19.5, 0.3, 32.0);
        glVertex3f(19.5, 0.0, 32.0);
        glVertex3f(19.5, 0.0, 42.0);
        glVertex3f(19.5, 0.3, 42.0);

        glVertex3f(24.5, 0.3, 32.0);
        glVertex3f(24.5, 0.0, 32.0);
        glVertex3f(24.5, 0.0, 42.0);
        glVertex3f(24.5, 0.3, 42.0);
    glEnd();
    glPopMatrix();

    //Kolam 2,3,4==============================================================================================================
    for(int i = 0; i < 3; i++){
        //Pohon=============================================
        glColor3f(0.0, 0.8, 0.0);
        glPushMatrix();
        glTranslatef(44+i*32, 1.8, 21.5);
        glutSolidSphere(0.8, 10, 10);
        glPopMatrix();
        glColor3f(106/255.f, 73/255.f, 64/255.f);
        glBegin(GL_QUADS);
            glVertex3f(44.2+i*32, 1.8, 21.3);
            glVertex3f(43.8+i*32, 1.8, 21.3);
            glVertex3f(43.8+i*32, 0.0, 21.3);
            glVertex3f(44.2+i*32, 0.0, 21.3);

            glVertex3f(44.2+i*32, 1.8, 21.7);
            glVertex3f(43.8+i*32, 1.8, 21.7);
            glVertex3f(43.8+i*32, 0.0, 21.7);
            glVertex3f(44.2+i*32, 0.0, 21.7);

            glVertex3f(43.8+i*32, 1.8, 21.7);
            glVertex3f(43.8+i*32, 1.8, 21.3);
            glVertex3f(43.8+i*32, 0.0, 21.3);
            glVertex3f(43.8+i*32, 0.0, 21.7);

            glVertex3f(44.2+i*32, 1.8, 21.7);
            glVertex3f(44.2+i*32, 1.8, 21.3);
            glVertex3f(44.2+i*32, 0.0, 21.3);
            glVertex3f(44.2+i*32, 0.0, 21.7);
        glEnd();

        glPushMatrix();
            glTranslatef(5.5, 0, 0);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44+i*32, 1.8, 21.5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.3);

                glVertex3f(44.2+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 0.0, 21.7);
                glVertex3f(44.2+i*32, 0.0, 21.7);

                glVertex3f(43.8+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.7);

                glVertex3f(44.2+i*32, 1.8, 21.7);
                glVertex3f(44.2+i*32, 1.8, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.7);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(5.5, 0, 4.5);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44+i*32, 1.8, 21.5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.3);

                glVertex3f(44.2+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 0.0, 21.7);
                glVertex3f(44.2+i*32, 0.0, 21.7);

                glVertex3f(43.8+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.7);

                glVertex3f(44.2+i*32, 1.8, 21.7);
                glVertex3f(44.2+i*32, 1.8, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.7);
            glEnd();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0.0, 0, 4.5);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44+i*32, 1.8, 21.5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.3);

                glVertex3f(44.2+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 0.0, 21.7);
                glVertex3f(44.2+i*32, 0.0, 21.7);

                glVertex3f(43.8+i*32, 1.8, 21.7);
                glVertex3f(43.8+i*32, 1.8, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.3);
                glVertex3f(43.8+i*32, 0.0, 21.7);

                glVertex3f(44.2+i*32, 1.8, 21.7);
                glVertex3f(44.2+i*32, 1.8, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.3);
                glVertex3f(44.2+i*32, 0.0, 21.7);
            glEnd();
        glPopMatrix();


        //Air============================================
        glColor4f(0.0, 0.0, 1.0, 0.7);
        glBegin(GL_QUADS);
            glVertex3f(44.5+i*32, 0.2, 22.0);
            glVertex3f(48.5+i*32, 0.2, 22.0);
            glVertex3f(48.5+i*32, 0.2, 25.5);
            glVertex3f(44.5+i*32, 0.2, 25.5);
        glEnd();

        //Kolam========================================
        glColor3f(0.8, 0.8, 0.8);
        glBegin(GL_QUADS);
            glVertex3f(44.5+i*32, 0.3, 22.0);
            glVertex3f(48.5+i*32, 0.3, 22.0);
            glVertex3f(48.5+i*32, 0.0, 22.0);
            glVertex3f(44.5+i*32, 0.0, 22.0);

            glVertex3f(44.5+i*32, 0.3, 25.5);
            glVertex3f(48.5+i*32, 0.3, 25.5);
            glVertex3f(48.5+i*32, 0.0, 25.5);
            glVertex3f(44.5+i*32, 0.0, 25.5);

            glVertex3f(44.5+i*32, 0.3, 25.5);
            glVertex3f(44.5+i*32, 0.3, 22.0);
            glVertex3f(44.5+i*32, 0.0, 22.0);
            glVertex3f(44.5+i*32, 0.0, 25.5);

            glVertex3f(48.5+i*32, 0.3, 25.5);
            glVertex3f(48.5+i*32, 0.3, 22.0);
            glVertex3f(48.5+i*32, 0.0, 22.0);
            glVertex3f(48.5+i*32, 0.0, 25.5);
        glEnd();
    }


}

void tamanDalam(){
    //Area hijau===============================================================================================================
    glColor3f(0.0, 0.9, 0.0);
    glBegin(GL_QUADS);
        glVertex3f(27.0, 0.01, 27.0);
        glVertex3f(125.0, 0.01, 27.0);
        glVertex3f(125.0, 0.01, 58.0);
        glVertex3f(27.0, 0.01, 58.0);
    glEnd();

    //Area dalam================================================================================================================
    glColor3f(0.9, 0.9, 0.9);
    glBegin(GL_QUADS);
        glVertex3f(32.0, 0.02, 40.0);
        glVertex3f(118.0, 0.02, 40.0);
        glVertex3f(118.0, 0.02, 55.0);
        glVertex3f(32.0, 0.02, 55.0);

        glVertex3f(32.0, 0.02, 40.0);
        glVertex3f(52.0, 0.02, 40.0);
        glVertex3f(52.0, 0.02, 32.0);
        glVertex3f(32.0, 0.02, 32.0);

        glVertex3f(118.0, 0.02, 40.0);
        glVertex3f(98.0, 0.02, 40.0);
        glVertex3f(98.0, 0.02, 32.0);
        glVertex3f(118.0, 0.02, 32.0);
    glEnd();


    //Pohon pinggir taman belakang=============================================================================================================
    for(int i = 0; i < 20; i++){
        glPushMatrix();
            glTranslatef(-16, 0, 7);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44+i*5, 1.8, 21.5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2+i*5, 1.8, 21.3);
                glVertex3f(43.8+i*5, 1.8, 21.3);
                glVertex3f(43.8+i*5, 0.0, 21.3);
                glVertex3f(44.2+i*5, 0.0, 21.3);

                glVertex3f(44.2+i*5, 1.8, 21.7);
                glVertex3f(43.8+i*5, 1.8, 21.7);
                glVertex3f(43.8+i*5, 0.0, 21.7);
                glVertex3f(44.2+i*5, 0.0, 21.7);

                glVertex3f(43.8+i*5, 1.8, 21.7);
                glVertex3f(43.8+i*5, 1.8, 21.3);
                glVertex3f(43.8+i*5, 0.0, 21.3);
                glVertex3f(43.8+i*5, 0.0, 21.7);

                glVertex3f(44.2+i*5, 1.8, 21.7);
                glVertex3f(44.2+i*5, 1.8, 21.3);
                glVertex3f(44.2+i*5, 0.0, 21.3);
                glVertex3f(44.2+i*5, 0.0, 21.7);
            glEnd();
        glPopMatrix();
    }

    //Pohon pinggir taman depan=============================================================================================================
    for(int i = 0; i < 20; i++){
        glPushMatrix();
            glTranslatef(-16, 0, 35);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44+i*5, 1.8, 21.5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2+i*5, 1.8, 21.3);
                glVertex3f(43.8+i*5, 1.8, 21.3);
                glVertex3f(43.8+i*5, 0.0, 21.3);
                glVertex3f(44.2+i*5, 0.0, 21.3);

                glVertex3f(44.2+i*5, 1.8, 21.7);
                glVertex3f(43.8+i*5, 1.8, 21.7);
                glVertex3f(43.8+i*5, 0.0, 21.7);
                glVertex3f(44.2+i*5, 0.0, 21.7);

                glVertex3f(43.8+i*5, 1.8, 21.7);
                glVertex3f(43.8+i*5, 1.8, 21.3);
                glVertex3f(43.8+i*5, 0.0, 21.3);
                glVertex3f(43.8+i*5, 0.0, 21.7);

                glVertex3f(44.2+i*5, 1.8, 21.7);
                glVertex3f(44.2+i*5, 1.8, 21.3);
                glVertex3f(44.2+i*5, 0.0, 21.3);
                glVertex3f(44.2+i*5, 0.0, 21.7);
            glEnd();
        glPopMatrix();
    }

    //Pohon pinggir taman kiri=============================================================================================================
    for(int i = 0; i < 5; i++){
        glPushMatrix();
            glTranslatef(-16, 0, 11);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44, 1.8, 21.5+i*5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2, 1.8, 21.3+i*5);
                glVertex3f(43.8, 1.8, 21.3+i*5);
                glVertex3f(43.8, 0.0, 21.3+i*5);
                glVertex3f(44.2, 0.0, 21.3+i*5);

                glVertex3f(44.2, 1.8, 21.7+i*5);
                glVertex3f(43.8, 1.8, 21.7+i*5);
                glVertex3f(43.8, 0.0, 21.7+i*5);
                glVertex3f(44.2, 0.0, 21.7+i*5);

                glVertex3f(43.8, 1.8, 21.7+i*5);
                glVertex3f(43.8, 1.8, 21.3+i*5);
                glVertex3f(43.8, 0.0, 21.3+i*5);
                glVertex3f(43.8, 0.0, 21.7+i*5);

                glVertex3f(44.2, 1.8, 21.7+i*5);
                glVertex3f(44.2, 1.8, 21.3+i*5);
                glVertex3f(44.2, 0.0, 21.3+i*5);
                glVertex3f(44.2, 0.0, 21.7+i*5);
            glEnd();
        glPopMatrix();
    }

    //Pohon pinggir taman kanan=============================================================================================================
    for(int i = 0; i < 5; i++){
        glPushMatrix();
            glTranslatef(79, 0, 11);
            glColor3f(0.0, 0.8, 0.0);
            glPushMatrix();
            glTranslatef(44, 1.8, 21.5+i*5);
            glutSolidSphere(0.8, 10, 10);
            glPopMatrix();

            glColor3f(106/255.f, 73/255.f, 64/255.f);
            glBegin(GL_QUADS);
                glVertex3f(44.2, 1.8, 21.3+i*5);
                glVertex3f(43.8, 1.8, 21.3+i*5);
                glVertex3f(43.8, 0.0, 21.3+i*5);
                glVertex3f(44.2, 0.0, 21.3+i*5);

                glVertex3f(44.2, 1.8, 21.7+i*5);
                glVertex3f(43.8, 1.8, 21.7+i*5);
                glVertex3f(43.8, 0.0, 21.7+i*5);
                glVertex3f(44.2, 0.0, 21.7+i*5);

                glVertex3f(43.8, 1.8, 21.7+i*5);
                glVertex3f(43.8, 1.8, 21.3+i*5);
                glVertex3f(43.8, 0.0, 21.3+i*5);
                glVertex3f(43.8, 0.0, 21.7+i*5);

                glVertex3f(44.2, 1.8, 21.7+i*5);
                glVertex3f(44.2, 1.8, 21.3+i*5);
                glVertex3f(44.2, 0.0, 21.3+i*5);
                glVertex3f(44.2, 0.0, 21.7+i*5);
            glEnd();
        glPopMatrix();
    }

    //Kolam 5==============================================================================================================
    glPushMatrix();
    glTranslatef(25, 0, 8);
    glBegin(GL_QUADS);
        glColor3f(0.6, 0.6, 0.6);
        glVertex3f(78.5, 0.03, 33.0);
        glVertex3f(85.0, 0.03, 33.0);
        glVertex3f(85.0, 0.03, 39.0);
        glVertex3f(78.5, 0.03, 39.0);

        glColor4f(0.0, 0.0, 1.0, 0.7);
        glVertex3f(78.5, 0.2, 33.0);
        glVertex3f(85.0, 0.2, 33.0);
        glVertex3f(85.0, 0.2, 39.0);
        glVertex3f(78.5, 0.2, 39.0);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
        glVertex3f(78.5, 0.3, 33.0);
        glVertex3f(78.5, 0.0, 33.0);
        glVertex3f(85.0, 0.0, 33.0);
        glVertex3f(85.0, 0.3, 33.0);

        glVertex3f(78.5, 0.3, 39.0);
        glVertex3f(78.5, 0.0, 39.0);
        glVertex3f(85.0, 0.0, 39.0);
        glVertex3f(85.0, 0.3, 39.0);

        glVertex3f(78.5, 0.3, 33.0);
        glVertex3f(78.5, 0.0, 33.0);
        glVertex3f(78.5, 0.0, 39.0);
        glVertex3f(78.5, 0.3, 39.0);

        glVertex3f(85, 0.3, 33.0);
        glVertex3f(85, 0.0, 33.0);
        glVertex3f(85, 0.0, 39.0);
        glVertex3f(85, 0.3, 39.0);
    glEnd();
    glPopMatrix();

    //Kolam 6==============================================================================================================
    glPushMatrix();
    glTranslatef(-40, 0, 8);
    glBegin(GL_QUADS);
        glColor3f(0.6, 0.6, 0.6);
        glVertex3f(78.5, 0.03, 33.0);
        glVertex3f(85.0, 0.03, 33.0);
        glVertex3f(85.0, 0.03, 39.0);
        glVertex3f(78.5, 0.03, 39.0);

        glColor4f(0.0, 0.0, 1.0, 0.7);
        glVertex3f(78.5, 0.2, 33.0);
        glVertex3f(85.0, 0.2, 33.0);
        glVertex3f(85.0, 0.2, 39.0);
        glVertex3f(78.5, 0.2, 39.0);
    glEnd();

    glColor3f(0.8, 0.8, 0.8);
    glBegin(GL_QUADS);
        glVertex3f(78.5, 0.3, 33.0);
        glVertex3f(78.5, 0.0, 33.0);
        glVertex3f(85.0, 0.0, 33.0);
        glVertex3f(85.0, 0.3, 33.0);

        glVertex3f(78.5, 0.3, 39.0);
        glVertex3f(78.5, 0.0, 39.0);
        glVertex3f(85.0, 0.0, 39.0);
        glVertex3f(85.0, 0.3, 39.0);

        glVertex3f(78.5, 0.3, 33.0);
        glVertex3f(78.5, 0.0, 33.0);
        glVertex3f(78.5, 0.0, 39.0);
        glVertex3f(78.5, 0.3, 39.0);

        glVertex3f(85, 0.3, 33.0);
        glVertex3f(85, 0.0, 33.0);
        glVertex3f(85, 0.0, 39.0);
        glVertex3f(85, 0.3, 39.0);
    glEnd();
    glPopMatrix();
}

void entrance(){
    glPushMatrix();
        glRotatef(45, 0, 0.01, 0);
        glTranslatef(-23.8, 0, 5);
        //Lantai
        for(int i = 0; i < 6; i += 2){
            glBegin(GL_QUADS);
            glColor3f(0.8, 0.8, 0.8);
            glVertex3f(26.0, 0.01, 22.0+2*i); //atas
            glVertex3f(22.0, 0.01, 22.0+2*i);
            glVertex3f(22.0, 0.01, 24.0+2*i);
            glVertex3f(26.0, 0.01, 24.0+2*i);
        glEnd();
        }

        //atas
        glBegin(GL_QUADS);
            glColor3f(133/255.f,115/255.f,115/255.f);
            glVertex3f(27.0, 3.8, 27.0); //atas
            glVertex3f(21.0, 3.8, 27.0);
            glVertex3f(21.0, 3.8, 27.2);
            glVertex3f(27.0, 3.8, 27.2);

            glVertex3f(27.0, 3.0, 27.0); //bawah
            glVertex3f(21.0, 3.0, 27.0);
            glVertex3f(21.0, 3.0, 27.2);
            glVertex3f(27.0, 3.0, 27.2);

            glColor3f(123/255.f,105/255.f,105/255.f);
            glVertex3f(27.0, 3.8, 27.0); //belakang
            glVertex3f(21.0, 3.8, 27.0);
            glVertex3f(21.0, 3.0, 27.0);
            glVertex3f(27.0, 3.0, 27.0);

            glVertex3f(27.0, 3.8, 27.2); //depan
            glVertex3f(21.0, 3.8, 27.2);
            glVertex3f(21.0, 3.0, 27.2);
            glVertex3f(27.0, 3.0, 27.2);
        glEnd();
        //pilar kanan
        glBegin(GL_QUADS);
            glColor3f(133/255.f,115/255.f,115/255.f);
            glVertex3f(27.0, 3.8, 27.2); //kanan 1
            glVertex3f(27.0, 3.8, 27.0);
            glVertex3f(27.0, 0.0, 27.0);
            glVertex3f(27.0, 0.0, 27.2);

            glVertex3f(26.0, 3.0, 27.2); //kiri
            glVertex3f(26.0, 3.0, 27.0);
            glVertex3f(26.0, 0.0, 27.0);
            glVertex3f(26.0, 0.0, 27.2);

            glColor3f(123/255.f,105/255.f,105/255.f);
            glVertex3f(26.0, 3.0, 27.0); //depan
            glVertex3f(27.0, 3.0, 27.0);
            glVertex3f(27.0, 0.0, 27.0);
            glVertex3f(26.0, 0.0, 27.0);

            glVertex3f(26.0, 3.0, 27.2); //belakang
            glVertex3f(27.0, 3.0, 27.2);
            glVertex3f(27.0, 0.0, 27.2);
            glVertex3f(26.0, 0.0, 27.2);
        glEnd();

        glPushMatrix();
            glTranslatef(-5, 0, 0);
            glBegin(GL_QUADS);
            glColor3f(133/255.f,115/255.f,115/255.f);
            glVertex3f(27.0, 3.0, 27.2); //kanan 1
            glVertex3f(27.0, 3.0, 27.0);
            glVertex3f(27.0, 0.0, 27.0);
            glVertex3f(27.0, 0.0, 27.2);

            glVertex3f(26.0, 3.8, 27.2); //kiri
            glVertex3f(26.0, 3.8, 27.0);
            glVertex3f(26.0, 0.0, 27.0);
            glVertex3f(26.0, 0.0, 27.2);

            glColor3f(123/255.f,105/255.f,105/255.f);
            glVertex3f(26.0, 3.0, 27.0); //depan
            glVertex3f(27.0, 3.0, 27.0);
            glVertex3f(27.0, 0.0, 27.0);
            glVertex3f(26.0, 0.0, 27.0);

            glVertex3f(26.0, 3.0, 27.2); //belakang
            glVertex3f(27.0, 3.0, 27.2);
            glVertex3f(27.0, 0.0, 27.2);
            glVertex3f(26.0, 0.0, 27.2);
        glEnd();
        glPopMatrix();

    glPopMatrix();
}

void tengah_tingkat_1(){
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.9,0.7,0.6);
    glVertex3f(88.0, 0.0, 0.0);
    glVertex3f(88.0, 4.0, 0.0);
    glVertex3f(67.5, 4.0, 0.0);
    glVertex3f(67.5, 0.0, 0.0);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor4f(0.0,0.0,0.0,0.7);
    glVertex3f(88.0, 0.0, 14.0);
    glVertex3f(88.0, 4.0, 14.0);
    glVertex3f(67.5, 4.0, 14.0);
    glVertex3f(67.5, 0.0, 14.0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.9,0.7,0.5);
    glVertex3f(67.5, 0.0, 0.0);
    glVertex3f(67.5, 4.0, 0.0);
    glVertex3f(67.5, 4.0, 14.0);
    glVertex3f(67.5, 0.0, 14.0);
    glEnd();

    //kanan atas
    glBegin(GL_QUADS);
    glColor3f(0.9,0.7,0.5);
    glVertex3f(88.0, 0.0, 0.0);
    glVertex3f(88.0, 4.0, 0.0);
    glVertex3f(88.0, 4.0, 14.0);
    glVertex3f(88.0, 0.0, 14.0);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3f(0.4, 0.4, 0.4);
    glVertex3f(88.0, 4.0, 00.0);
    glVertex3f(88.0, 4.0, 17.0);
    glVertex3f(67.5, 4.0, 17.0);
    glVertex3f(67.5, 4.0, 0.0);
    glEnd();
}

void pilar_tengah(){
    glPushMatrix();
    glTranslatef(-23, 0, 0);
    for(int i = 0 ; i<6 ; i++){
        //depan
        glBegin(GL_QUADS);
        glColor3f(0.9,0.7,0.5);
        glVertex3f(90.5+i*4, 0.0, 17.0);
        glVertex3f(90.5+i*4, 4.0, 17.0);
        glVertex3f(91.0+i*4, 4.0, 17.0);
        glVertex3f(91.0+i*4, 0.0, 17.0);
        glEnd();

        //belakang
        glBegin(GL_QUADS);
        glVertex3f(90.5+i*4, 0.0, 16.5);
        glVertex3f(90.5+i*4, 4.0, 16.5);
        glVertex3f(91.0+i*4, 4.0, 16.5);
        glVertex3f(91.0+i*4, 0.0, 16.5);
        glEnd();

        //kiri
        glBegin(GL_QUADS);
        glVertex3f(90.5+i*4, 0.0, 16.5);
        glVertex3f(90.5+i*4, 4.0, 16.5);
        glVertex3f(90.5+i*4, 4.0, 17.0);
        glVertex3f(90.5+i*4, 0.0, 17.0);
        glEnd();

        //kanan
        glBegin(GL_QUADS);
        glVertex3f(91.0+i*4, 0.0, 16.5);
        glVertex3f(91.0+i*4, 4.0, 16.5);
        glVertex3f(91.0+i*4, 4.0, 17.0);
        glVertex3f(91.0+i*4, 0.0, 17.0);
        glEnd();

        for(int i = 0 ; i<6 ; i++){
        //depan
        glBegin(GL_QUADS);
        glColor3f(0.9,0.7,0.5);
        glVertex3f(90.5+i*4, 0.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 0.0, 15.5);
        glEnd();

        //belakang
        glBegin(GL_QUADS);
        glVertex3f(90.5+i*4, 0.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 4.0, 15.0);
        glVertex3f(91.0+i*4, 0.0, 15.0);
        glEnd();

        //kiri
        glBegin(GL_QUADS);
        glVertex3f(90.5+i*4, 0.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.0);
        glVertex3f(90.5+i*4, 0.0, 15.0);
        glEnd();

        //kanan
        glBegin(GL_QUADS);
        glVertex3f(91.0+i*4, 0.0, 15.0);
        glVertex3f(91.0+i*4, 4.0, 15.0);
        glVertex3f(91.0+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 0.0, 15.5);
        glEnd();
    }

    for(int i = 0 ; i<6 ; i++){
        //depan
        glBegin(GL_QUADS);
        glColor3f(0.9,0.7,0.5);
        glVertex3f(90.5+i*4, 0.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 0.0, 15.5);
        glEnd();

        //belakang
        glBegin(GL_QUADS);
        glVertex3f(90.5+i*4, 0.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 4.0, 15.0);
        glVertex3f(91.0+i*4, 0.0, 15.0);
        glEnd();

        //kiri
        glBegin(GL_QUADS);
        glVertex3f(90.5+i*4, 0.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.5);
        glVertex3f(90.5+i*4, 4.0, 15.0);
        glVertex3f(90.5+i*4, 0.0, 15.0);
        glEnd();

        //kanan
        glBegin(GL_QUADS);
        glVertex3f(91.0+i*4, 0.0, 15.0);
        glVertex3f(91.0+i*4, 4.0, 15.0);
        glVertex3f(91.0+i*4, 4.0, 15.5);
        glVertex3f(91.0+i*4, 0.0, 15.5);
        glEnd();
        }
    }

    glPopMatrix();
}

void tengah_tingkat_2(){
    //belakang
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(67.5, 4.0, 0.0);
    glVertex3f(67.5, 8.0, 0.0);
    glVertex3f(88.0, 8.0, 0.0);
    glVertex3f(88.0, 4.0, 0.0);
    glEnd();

    //depan
    glBegin(GL_QUADS);
    glColor4f(0.95,0.75,0.95,0.95);
    glVertex3f(67.5, 4.0, 15.0);
    glVertex3f(67.5, 8.0, 15.0);
    glVertex3f(88.0, 8.0, 15.0);
    glVertex3f(88.0, 4.0, 15.0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(67.5, 4.0, 0.0);
    glVertex3f(67.5, 8.0, 0.0);
    glVertex3f(67.5, 8.0, 15.0);
    glVertex3f(67.5, 4.0, 15.0);
    glEnd();

    //kiri
    glBegin(GL_QUADS);
    glColor3f(0.0, 0.0, 0.0);
    glVertex3f(88, 4.0, 0.0);
    glVertex3f(88, 8.0, 0.0);
    glVertex3f(88, 8.0, 15.0);
    glVertex3f(88, 4.0, 15.0);
    glEnd();

    //atas
    glBegin(GL_QUADS);
    glColor3f(0.87,0.65,0.4);
    glVertex3f(67.5, 8.0, 00.0);
    glVertex3f(67.5, 8.0, 15.0);
    glVertex3f(88.0, 8.0, 15.0);
    glVertex3f(88.0, 8.0, 0.0);
    glEnd();
}

void seperempatBola(int scaley, int scalex, GLfloat r) {
   int i, j;
   GLfloat v[scalex*scaley][10];

   for (i=0; i<scalex; ++i) {
     for (j=0; j<scaley; ++j) {
       v[i*scaley+j][0]=r*cos(j*1*M_PI/scaley)*cos(i*M_PI/(2*scalex));
       v[i*scaley+j][1]=r*sin(i*M_PI/(2*scalex));
       v[i*scaley+j][2]=r*sin(j*1*M_PI/scaley)*cos(i*M_PI/(2*scalex));
     }
   }

   glBegin(GL_QUADS);
     for (i=0; i<scalex-1; ++i) {
       for (j=0; j<scaley; ++j) {
         glVertex3fv(v[i*scaley+j]);
         glVertex3fv(v[i*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+(j+1)%scaley]);
         glVertex3fv(v[(i+1)*scaley+j]);
       }
     }
   glEnd();
 }

void setengahLingkaran(){
    float radius = 10.25;
    float twoPI = 2 * M_PI;

    glBegin(GL_TRIANGLE_FAN);

    for (float i = M_PI; i <= twoPI; i += 0.001)
        glVertex2f((sin(i)*radius), (cos(i)*radius));

    glEnd();
    glFlush();
}

void lisKacaDome(){
    glColor4f(0.4, 0.4, 0.4, 0.7);
    glBegin(GL_QUADS);
        glVertex3f(67.5, 5.0, 15.02);
        glVertex3f(67.5, 6.0, 15.02);
        glVertex3f(88.0, 6.0, 15.02);
        glVertex3f(88.0, 5.0, 15.02);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(67.5, 8.0, 15.02);
        glVertex3f(67.55, 9.0, 15.02);
        glVertex3f(87.95, 9.0, 15.02);
        glVertex3f(88.0, 8.0, 15.02);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(68.0, 11.0, 15.02);
        glVertex3f(68.3, 12.0, 15.02);
        glVertex3f(87.2, 12.0, 15.02);
        glVertex3f(87.5, 11.0, 15.02);
    glEnd();

    glBegin(GL_QUADS);
        glVertex3f(69.5, 14.0, 15.02);
        glVertex3f(70.3, 15.0, 15.02);
        glVertex3f(85.2, 15.0, 15.02);
        glVertex3f(86.0, 14.0, 15.02);
    glEnd();

    //Lis samping
    glColor3f(0.9,0.9,0.9);
    glLineWidth(5);
    glBegin(GL_LINES);
        glVertex3f(67.5, 4.0, 15.0);
        glVertex3f(67.5, 8.0, 15.0);
        glVertex3f(88.0, 8.0, 15.0);
        glVertex3f(88.0, 4.0, 15.0);
    glEnd();

    //Kanopi depan
    glColor3f(0.5,0.5,0.5);
    glLineWidth(5);
    glBegin(GL_POLYGON);
        glVertex3f(74.5, 6.0, 15.0);
        glVertex3f(74.5, 6.0, 17.0);
        glVertex3f(81.0, 6.0, 17.0);
        glVertex3f(81.0, 6.0, 15.0);
    glEnd();

    //Lis depan
    glColor3f(0.7,0.7,0.7);
    glLineWidth(5);
    glBegin(GL_QUADS);
        glVertex3f(68.5, 9.0, 15.0);
        glVertex3f(68.5, 9.0, 17.0);
        glVertex3f(75.0, 9.0, 17.0);
        glVertex3f(75.0, 9.0, 15.0);

        glVertex3f(68.5, 9.5, 15.0);
        glVertex3f(68.5, 9.5, 17.0);
        glVertex3f(75.0, 9.5, 17.0);
        glVertex3f(75.0, 9.5, 15.0);

        glColor3f(0.75,0.75,0.75);

        glVertex3f(68.5, 9.5, 17.0);
        glVertex3f(68.5, 9.0, 17.0);
        glVertex3f(75.0, 9.0, 17.0);
        glVertex3f(75.0, 9.5, 17.0);

        glColor3f(0.78,0.78,0.78);

        glVertex3f(75.0, 9.5, 15.0);
        glVertex3f(75.0, 9.0, 15.0);
        glVertex3f(75.0, 9.0, 17.0);
        glVertex3f(75.0, 9.5, 17.0);

        glVertex3f(68.5, 9.5, 15.0);
        glVertex3f(68.5, 9.0, 15.0);
        glVertex3f(68.5, 9.0, 17.0);
        glVertex3f(68.5, 9.5, 17.0);
    glEnd();

}

void lisSetengahLingkaran(){
    float radius = 10.26;
    float twoPI = 2 * M_PI;

    glBegin(GL_POINTS);

    for (float i = 0.0; i <= twoPI / 2; i += 0.001)
        glVertex2f((sin(i)*radius), (cos(i)*radius));

    glEnd();
    glFlush();
}

void mobil(){


glPushMatrix();
    glPushMatrix();
    glTranslated(140.0-x_pos, 1.0, 60.0);
    glScalef(2.0, 2.0, 2.0);
    glPushMatrix();
        glColor3f(0.9, 0.9, 0.9);              // body
        glScalef(4,1,2);
        glutSolidCube(.5);
        glTranslatef(-.05,.3,0);
        glColor3f(0.9, 0.9, 0.9);
        glScalef(0.6,3,2);
        glutSolidCube(.25);
        glTranslatef(-.12,.001,-.001);
        glScalef(1,1.8,2.48);
        glRotatef(230, 0, 0, 250);
        glutSolidCube(.1);
        glPopMatrix();
        glTranslatef(0,0,.5);
        glPushMatrix();
        glTranslatef(-.4,-.2,0);
        glColor3f(0.4, 0.4, 0.4);
        glutSolidTorus(.1,.2,8,8);       // wheel
        glTranslatef(1,0,0);
        glutSolidTorus(.1,.2,8,8);       // wheel
        glPopMatrix();
        glTranslatef(0,0,-1);
        glPushMatrix();
        glTranslatef(-.4,-.2,0);
        glutSolidTorus(.1,.2,8,8);       // wheel
        glTranslatef(1,0,0);
        glutSolidTorus(.1,.2,8,8);       // wheel
        glPopMatrix();
        glPopMatrix();
glPopMatrix();
glFlush();
}

void idle(){
    if(!mouseDown){
        xrot += 0.3f;
        yrot += 0.4f;
    }
    glutPostRedisplay();
}

void keyboard(unsigned char key, int x, int y){
    switch(key){
        case 'w':
        case 'W':
            glTranslatef(0.0,0.0,3.0);
            break;
        case 'd':
        case 'D':
            glTranslatef(3.0,0.0,0.0);
            break;
        case 's':
        case 'S':
            glTranslatef(0.0,0.0,-3.0);
            break;
        case 'a':
        case 'A':
            glTranslatef(-3.0,0.0,0.0);
            break;
        case '7':
            glTranslatef(0.0,3.0,0.0);
            break;
        case '9':
            glTranslatef(0.0,-3.0,0.0);
            break;
        case '2':
            glRotatef(2.0,1.0,0.0,0.0);
            break;
        case '8':
            glRotatef(-2.0,1.0,0.0,0.0);
            break;
        case '6':
            glRotatef(2.0,0.0,1.0,0.0);
            break;
        case '4':
            glRotatef(-2.0,0.0,1.0,0.0);
            break;
        case '1':
            glRotatef(2.0,0.0,0.0,1.0);
            break;
        case '3':
            glRotatef(-2.0,0.0,0.0,1.0);
            break;
        case '5':
            if(is_depth){
                is_depth=0;
                glDisable(GL_DEPTH_TEST);
            } else{
                is_depth=1;
                glEnable(GL_DEPTH_TEST);
            }
    }
    tampil();
}

void mouse(int button, int state, int x, int y){
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
        mouseDown = true;
        xdiff = x-yrot;
        ydiff = -y + xrot;
    } else{
        mouseDown = false;
    }
}

void mouseMotion(int x, int y){
    if(mouseDown){
        yrot = x-xdiff;
        xrot = y+ydiff;

        glutPostRedisplay();
    }
}

void ukuran(int lebar, int tinggi){
    if(tinggi == 0) tinggi = 1;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(50.0, lebar/tinggi,5.0,500.0);
    glTranslatef(0.0,-5.0,-150.0);
    glMatrixMode(GL_MODELVIEW);
}
