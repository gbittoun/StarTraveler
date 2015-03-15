/*
 * This code was created by Jeff Molofee '99 
 * (ported to Linux/SDL by Ti Leggett '01)
 *
 * If you've found this code useful, please let me know.
 *
 * Visit Jeff at http://nehe.gamedev.net/
 * 
 * or for port-specific comments, questions, bugreports etc. 
 * email to leggett@eecs.tulane.edu
 */
 
#include "SDLApplication.h"

/* screen width, height, and bit depth */
#define SCREEN_WIDTH  640
#define SCREEN_HEIGHT 480
#define SCREEN_BPP     16

/* Define our booleans */
#define TRUE  1
#define FALSE 0


// GLchar shader_str[] = "#version 300 es\n"
// "precision highp float;\n"
// "out vec4 fragmentColor;"
// "void main(void)\n"
// "{\n"
//     "if (gl_FragCoord.x < 100.0)"
//     "{"
//         "fragmentColor = vec4(0.0, 0.0, 0.5, 0.0);\n"
//     "}"
//     "else"
//     "{"
//         "fragmentColor = vec4(0.5, 0.0, 0.5, 0.0);\n"
//     "}"
// "}";

// const GLchar *source = (const GLchar *) shader_str;
// GLint shader_length = 1;
// GLuint shader_id;
// GLuint program_id;



// /* Here goes our drawing code */
// int drawGLScene()
// {
//     glOrtho(-1, 1, -1, 1, 0, 100);
//     gluLookAt

//     /* Clear The Screen And The Depth Buffer */
//     glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

//     glBegin(GL_TRIANGLES);
//     glVertex3f(0, 0, 10);
//     glVertex3f(-1, 0, 0);
//     glVertex3f(0, 1, 0);
//     glEnd();

//     glBegin(GL_TRIANGLES);
//     glVertex3f(0, 0, 0);
//     glVertex3f(1, 0, 10);
//     glVertex3f(0, -1, 0);
//     glEnd();

//     /* Draw it to the screen */
//     SDL_GL_SwapBuffers( );

//     return( TRUE );
// }

int main( int argc, char **argv )
{
    SDLApplication app(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP);
    app.init();
    app.mainLoop();

    return 0;
}