#include "GLHandler.h"

GLHandler::GLHandler() :
	ErrorStateBase()
{
}

/* general OpenGL initialization function */
ErrorStateBase::ErrorCode GLHandler::initGL()
{
    GLenum err = glewInit();
    if (err != GLEW_OK)
    {
    	std::cerr << "Glew initialization failed" << std::endl;
    	errorState = GLEW_INIT_FAILED;
    }

    /* Enable smooth shading */
    glShadeModel( GL_SMOOTH );

    /* Set the background black */
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );

    /* Depth buffer setup */
    glClearDepth( 1.0f );

    /* Enables Depth Testing */
    glEnable( GL_DEPTH_TEST );

    /* The Type Of Depth Test To Do */
    glDepthFunc( GL_LEQUAL );

    /* Really Nice Perspective Calculations */
    glHint( GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST );

    // std::cout << "It begins" << std::endl;
    // /* Create fragment shader */
    // shader_id = glCreateShader(GL_FRAGMENT_SHADER);
    // glShaderSource(shader_id,  1, &source,  0);
     
    // glCompileShader(shader_id);
     
    // GLint isCompiled = 0;
    // glGetShaderiv(shader_id, GL_COMPILE_STATUS, &isCompiled);
    // if(isCompiled == GL_FALSE)
    // {
    //     GLint maxLength = 0;
    //     glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &maxLength);
     
    //     // The maxLength includes the NULL character
    //     std::vector<GLchar> errorLog(maxLength);
    //     glGetShaderInfoLog(shader_id, maxLength, &maxLength, &errorLog[0]);

    //     std::cout << "Error compiling shader" << std::endl;
    //     std::cout << &errorLog[0] << std::endl;
     
    //     // Provide the infolog in whatever manor you deem best.
    //     // Exit with failure.
    //     glDeleteShader(shader_id); // Don't leak the shader.
    // }

    // program_id = glCreateProgram();
    // glAttachShader(program_id, shader_id);
    // std::cout << "glAttachShader " << glGetError() << std::endl;
    // glLinkProgram(program_id);
    // std::cout << "glLinkProgram " << glGetError() << std::endl;

    // GLint link_ok;
    // glGetProgramiv(program_id, GL_LINK_STATUS, &link_ok);
    // if (!link_ok) {
    //     std::cout << "Error linking program" << std::endl;
    // }
    // glUseProgram(program_id);
    // std::cout << "glUseProgram " << glGetError() << std::endl;

    return errorState;
}

void GLHandler::resizeWindow(int width, int height)
{
	std::cout << "resizeWindow" << std::endl;
    /* Height / width ration */
    GLfloat ratio;

    /* Protect against a divide by zero */
    if ( height == 0 )
	height = 1;

    ratio = ( GLfloat )width / ( GLfloat )height;

    /* Setup our viewport. */
    glViewport( 0, 0, ( GLsizei )width, ( GLsizei )height );

    /* change to the projection matrix and set our viewing volume. */
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );

    /* Set our perspective */
    gluPerspective( 45.0f, ratio, 0.1f, 100.0f );

    /* Make sure we're chaning the model view and not the projection */
    glMatrixMode( GL_MODELVIEW );

    /* Reset The View */
    glLoadIdentity( );
}

void GLHandler::drawGLScene()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    /* Move Left 1.5 Units And Into The Screen 6.0 */
    glLoadIdentity();
    gluLookAt(0, 0, 10, 0, 0, 0, 0, 1, 0);

    glBegin( GL_TRIANGLES );             /* Drawing Using Triangles       */
      glColor3f(   1.0f,  0.0f,  0.0f ); /* Red                           */
      glVertex3f(  0.0f,  1.0f,  0.0f ); /* Top Of Triangle               */
      glColor3f(   0.0f,  1.0f,  0.0f ); /* Green                         */
      glVertex3f( -1.0f, -1.0f,  0.0f ); /* Left Of Triangle              */
      glColor3f(   0.0f,  0.0f,  1.0f ); /* Blue                          */
      glVertex3f(  1.0f, -1.0f,  0.0f ); /* Right Of Triangle             */
    glEnd( );                            /* Finished Drawing The Triangle */
}
