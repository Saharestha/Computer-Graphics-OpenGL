#include<GL/glut.h>
#include <stdio.h>
float y_axis=1.0;                                           // For interactive Keyboard
float angle =0;                                             // For Function animation
float Autorun = 350;                                        // For Movement Autorun
float up=0;                                                 //For the bubbles to move up
float xs=1, ys=1;                                           //For scaling the image
bool paused=false;                                          //to pause the animation
float Autorun1 = 450;

/* this function is handler for idle function which helps the fish to move from
right to left and bubbles from down to up continuously when not paused */
void Auto(void)
{
    //if pause value is false
    if(paused==false)
    {
        if(Autorun<=350 && Autorun>-450)                      //translte from 400 to -500 units x-axis
            Autorun = Autorun-0.07;                           //movement of fish in x_axis by 0.07
        else                                                  //if x-axis less than-450
            Autorun = 350;                                    //change to initial value

        if(Autorun1<=450 && Autorun1>-380)                      //translte from 400 to -500 units x-axis
            Autorun1 = Autorun1-0.20;                           //movement of fish in x_axis by 0.07
        else                                                  //if x-axis less than-450
            Autorun1 = 450;

        if(up>=0 && up<600)
            up +=0.05;
        else                                                    //if y-axis >600
            up = 0;                                             //change to initial value
        glutPostRedisplay();                                    //redraw the output window
    }
}

/*this function is handler for key press function in order to move the fish
up, down, left, right using w,s,a and d respectively*/
void keyboard(GLubyte key, int x, int y)
{
    switch ( key )
    {
        case 'd':                                       //if you press key d
            Autorun += 10.0;                             //move right by 10 units in x-axis
            glutPostRedisplay();                        //redraw the output screen
            break;

        case 'a':                                       //if you press a
            Autorun -= 4.0;                              //move left by 4 units in x-axis
            glutPostRedisplay();                        //redraw the output screen
            break;

        case 's':                                       //if you press s
            Autorun -= 2.0;                              //move 2 units left in x-axis
            y_axis -= 10.0;                             //moves 10 units down in y-axis
            angle+=1.5;                                 //rotates by 1.5 degrees anti-clockwise
            glutPostRedisplay();                        //redraw the output screen
            break;

        case 'w':                                       //if you press w
            Autorun -= 2.0;                              //move 2 units left in x-axis
            y_axis += 10.0;                             //moves 10 units up in y-axis
            angle-=1.5;                                 //rotates by 1.5 degrees clockwise
            glutPostRedisplay();                        //redraw the output screen
            break;

        default:
            break;
    }
}
/*this function is handler for special key function which helps to scale the fish
up and down using the up and down arrow key respectively*/
void scaling(int key, int x, int y)
{
    switch(key)
    {
        case GLUT_KEY_DOWN:
            xs-=0.1;
            ys-=0.1;
            glutPostRedisplay();
            break;

        case GLUT_KEY_UP:
            xs+=0.1;
            ys+=0.1;

            glutPostRedisplay();
            break;
    }
}

/*function to reshape the window without changing the orientation of the image
by taking the width and height of the reshaped window*/
void reshape(GLsizei width, GLsizei height)
{
    if (height == 0)                                          //to prevent divide by zero
        height = 1;                                           //change 0 to 1

    GLfloat aspect = width / height;
    glViewport(0, 0, width, height);                          //set the part where the rendered image is appeared
    glMatrixMode(GL_PROJECTION);                              // To operate on the Projection matrix
    glLoadIdentity();
    if (width >= height)
    {
       gluOrtho2D(0, 600 * aspect, 0, 600);                   //multiply left and right parameters with aspect
    }
    else
    {
        gluOrtho2D(0, 600, 0, 600 / aspect);                  //multiply top and bottom parameters with aspect
    }
}

/*this function is handler for mouse callback function in order to pause and play the
screen with left and right mouse button respectively  */
void draw(int button, int state, int mouse_x, int mouse_y)
{
    if(button==GLUT_LEFT_BUTTON  && state==GLUT_DOWN)           //if left mouse button is presses
    {
        paused=true;                                            //set pause as true to pause the screen
    }
    if(button==GLUT_RIGHT_BUTTON  && state==GLUT_DOWN)          //if left mouse button is presses
    {
        paused=false;                                           //set pause as false to resume the paused screen
    }

    glutPostRedisplay();
}

/*user-defined function to draw the background of the output window using quadrilateral*/
void drawBackGround()
{
    glBegin(GL_QUADS);                                      //create a quadrilateral
        glColor3f(0, 0, 1);                                 //set color to blue
        glVertex2f(0,600);                                  //set 1st vertex
        glVertex2f(600,600);                                //set 2nd vertex
        glColor3f(0, 1, 1);                                 //set color to light blue
        glVertex2f(600, 0);                                 //set 3rd vertex
        glVertex2f(0,0);                                    //set 4th vertex
    glEnd();
}

/*user-defined function to draw bubbles at different points in the window using points*/
void bubbles()
{
    int MatrixA[6][2]={{100, -200},{200, -100},{500, 100},{250, 200},{460, 20},{420, -300}};            //declare matrixA for small bubbles
    glColor3f(0, 1, 1);                                                                                 //set color to light blue
    glPointSize(5);                                                                                     //set size of point to 5
    glBegin(GL_POINTS);
        for(int i=0; i<6; i++)                                                                          //loop to call values in matrixA
            glVertex2d(MatrixA[i][0], MatrixA[i][1]);                                                   //set vertex for creating points
    glEnd();

    int MatrixB[5][2]={{10, 75},{50, 20},{400, -430},{350, 50},{250, -50}};                             //declare MatrixB for small bubbles
    glPointSize(10);                                                                                    //set size to 10
    glBegin(GL_POINTS);
        for(int i=0; i<5; i++)                                                                          //loop to call values from matrixB
        {
            glVertex2d(MatrixB[i][0], MatrixB[i][1]);                                                   //set vertex for creating points
            glVertex2d(MatrixB[i][0]+100, MatrixB[i][1]-275);                                           //set vertex for creating points by changing values in MatrixB
        }
    glEnd();
}

/*Handler for window-paint event called in response
to a window-paint request. */
void Display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    drawBackGround();                                       //call user-defined function to make background

    glPushMatrix();                                         //save model-matrix setting
    glScalef(xs, ys, 1);
    glRotatef(angle,0,0,1);                                 //to move fish up and down in an angle
    glTranslatef(Autorun, y_axis, 0);                         //to move fish from right to left
                                   //to move the fish up, down, left and right.

    //to draw the body of the fish
    glBegin(GL_POLYGON);
        glColor3f(1 ,0.65 ,0);                              //set color to orange
        glVertex2i(240,300);                                //set 1st vertex
        glVertex2i(320,380);                                //set 2nd vertex
        glVertex2i(520,300);                                //set 3rd vertex
        glVertex2i(300,260);                                //set 4th vertex
    glEnd();

    //To draw the eye of the fish
    glPointSize(8);                                         //set point size to 8
    glBegin(GL_POINTS);
        glColor3f(0,0,0);                                   //set color to black
        glVertex2f(300,320);                                //set vertex for point on the body
    glEnd();

    //To draw the tail of the fish
    glBegin(GL_POLYGON);
        glColor3f(1, 0.65, 0);                              //to set color to orange
        glVertex2i(520,300);                                //set 1st vertex
        glVertex2i(560,340);                                //set 2nd vertex
        glVertex2i(540,300);                                //set 3rd vertex
        glVertex2i(560,260);                                //set 4th vertex
        glVertex2i(520,300);                                //set 5th vertex
    glEnd();

    //to draw the upper fin
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);                                 //set the color to red
        glVertex2i(320,380);                                //set 1st vertex
        glVertex2i(340,400);                                //set 2nd vertex
        glVertex2i(480,316);                                //set 3rd vertex
        glVertex2i(320,380);                                //set 4th vertex
    glEnd();

    //to draw the lower fin
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);                                 //set color to red
        glVertex2i(300,260);                                //set 1st vertex
        glVertex2i(340,300);                                //set 2nd vertex
        glVertex2i(320,264);                                //set 3rd vertex
        glVertex2i(300,260);                                //set 4th vertex
    glEnd();

    glPopMatrix();                                          //restore the model matrix setting



    //Draw a new fish
    glPushMatrix();
    //movement
    glTranslatef(Autorun1, 0,0);
    glColor3f(1,1,1);
    //draw body of 1st fish
    glBegin(GL_POLYGON);
    {
        glVertex2i(180,500);                                //set 1st vertex
        glVertex2i(230,530);                                //set 2nd vertex
        glVertex2i(280,500);                                //set 3rd vertex
        glVertex2i(240,470);                                //set 4th vertex
    }
    glEnd();
    //draw tail
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);                              //to set color to orange
        glVertex2i(280,500);                                //set 1st vertex
        glVertex2i(300,530);                                //set 2nd vertex
        glVertex2i(285,500);                                //set 3rd vertex
        glVertex2i(290,470);                                //set 4th vertex
        glVertex2i(280,500);                                //set 5th vertex
    glEnd();
    //draw eye
    glColor3f(0, 0, 0);
    glPointSize(3);
    glBegin(GL_POINTS);
        glVertex2f(190, 501);
    glEnd();

    //draw body of second fish
    glColor3f(0,1,0);
    glBegin(GL_POLYGON);
    {
        glVertex2i(200,200);                                //set 1st vertex
        glVertex2i(250,230);                                //set 2nd vertex
        glVertex2i(310,200);                                //set 3rd vertex
        glVertex2i(240,170);                                //set 4th vertex
    }
    glEnd();
    //draw tail
    glBegin(GL_POLYGON);
        glColor3f(1, 0, 0);                              //to set color to orange
        glVertex2i(310,200);                                //set 1st vertex
        glVertex2i(330,230);                                //set 2nd vertex
        glVertex2i(315,200);                                //set 3rd vertex
        glVertex2i(320,170);                                //set 4th vertex
        glVertex2i(310,200);                                //set 5th vertex
    glEnd();

    //draw eye
    glColor3f(0, 0, 0);
    glPointSize(3);
    glBegin(GL_POINTS);
        glVertex2f(230, 201);
    glEnd();
    glPopMatrix();

    glPushMatrix();                                         //save model-matrix setting

    glTranslatef(0,up,0);                                   //to move the bubbles up the y=axis
    bubbles();                                              //call user-defined function to make bubbles
    glPopMatrix();                                          //restore the model matrix setting
    glutSwapBuffers();                                      //to swap front and back buffers


}


int main(int a,char ** b)
{
    glutInit(&a,b);                             // Initialize GLUT
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);  //to enable double buffering and RGB
    glutInitWindowPosition(200,50);             //to set the position from top-left corner
    glutInitWindowSize(600,600);                //to set the size of output window
    glutCreateWindow("Moving Fish");            //create window with given title
    glClearColor(1 , 1, 1,0);                   //set background color to white
    glShadeModel(GL_SMOOTH);                    //set the shading to smooth
    glEnable(GL_POINT_SMOOTH);                  //to remove rough edges from point
    glutReshapeFunc(reshape);                   // Register display callback handler for window re-shaping
    glutDisplayFunc(Display);                   // Register display callback handler for window re-paint
    glutIdleFunc(Auto);                         // Register callback handler if no other event being handled
    glutKeyboardFunc(keyboard);                 // Register callback handler for keyboard event
    glutSpecialFunc(scaling);                   // Register callback handler for special key event
    glutMouseFunc(draw);                        // Register callback handler for mouse event
    glutMainLoop();                             // Enter the event-processing loop
}
