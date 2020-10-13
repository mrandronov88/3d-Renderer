#include "CApp.h"
#include <iostream>

bool CApp::OnInit()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
	{
		return false;
	}

	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow( 
		"SDL2 Window",
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		1600,
		900,
		SDL_WINDOW_OPENGL
	);

	if (window == NULL)
	{
		std::cout << ("Could not create window : %s\n", SDL_GetError());
		return false;
	}

	StartOpenGLContext();

	return true;
}

bool CApp::StartOpenGLContext()
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );

	mainContext = SDL_GL_CreateContext( window );

	if (mainContext == NULL)
	{
		std::cout << ("Could not create OpenGL context. SDL Error : %s\n", SDL_GetError());
		return false;
	}

	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit();
	if (glewError != GLEW_OK)
	{
		std::cout << ( "Error initializing GLEW. GLEW Error : %s\n", glewGetErrorString( glewError ) );
	}

	// Use vsync
	if ( SDL_GL_SetSwapInterval(1) < 0 )
	{
		std::cout << ( "Unable to set Vsync. SDL Error : %s\n", SDL_GetError() );
	}


	shader.setFragShader("frag.txt");
	shader.init();

	shader2.setFragShader("frag2.txt");
	shader2.init();

	CreateCube();

	// For wireframe mode
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	/*if (!initGL())
	{
		std::cout << ("Unable to initialize Opengl. \n");
		return false;
	}*/

	return true;
}

bool CApp::initGL()
{
	bool success = true;

	shader.init();

	return success;

}

void CApp::CreateCube()
{

	const int squarePoints = 4;

	const GLfloat square[squarePoints][3] =
	{
		// First Triangle
		{ -0.5, 0.25, 0.0 },
		{ -0.75, -0.25, 0.0 },
		{ -0.25, -0.25, 0.0 },	
		{ 0.0, 0.25, 0.0 }
	};

	const GLfloat squareColor[squarePoints][3] =
	{
		{ 1.0, 0.5, 1.0},
		{ 0.5, 1.0, 1.0},
		{ 1.0, 1.0, 0.5},
		{ 1.0, 0.5, 0.5}
	};

	const GLint indices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	//  ~~~~~~~~~~~~~~~~~~~~~~~ Second Shape ~~~~~~~~~~~~~~~~~~~~~~~~
	const GLfloat secondShapeVertices[squarePoints][3] =
	{
		{ 0.5, 0.25, 0.0 },
		{ 0.25, -0.25, 0.0 },
		{ 0.75, -0.25, 0.0 },
		{ 1.0, 0.25, 0.0 }
	};

	const GLfloat secondShapeColor[squarePoints][3] =
	{
		{ 1.0, 1.0, 0.5},
		{ 1.0, 0.5, 1.0},
		{ 0.5, 1.0, 1.0},
		{ 0.5, 0.5, 1.0}
	};

	const GLint secondShapeIndices[] =
	{
		0, 1, 2,
		0, 2, 3
	};

	// Generate VBO
	//const uint32_t countVBOs = 2;
	const uint32_t attributeCount = 4;
	GLuint vbo[ attributeCount ];
	glGenBuffers( attributeCount, vbo );

	// Generate VAO
	glGenVertexArrays(2, vao);
	
	// Generate EBO
	GLuint ebo[2];
	glGenBuffers(2, ebo);

	int sizeInBytes = sizeof(square);

	glBindVertexArray(vao[0]);
	// VBO loading to buffer for the square coordinate positions
	glBindBuffer( GL_ARRAY_BUFFER, vbo[0] );
	glBufferData( GL_ARRAY_BUFFER, sizeInBytes, square, GL_STATIC_DRAW );
	glVertexAttribPointer( 0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// VBO loading to buffer for the colors
	glBindBuffer( GL_ARRAY_BUFFER, vbo[1] );
	glBufferData( GL_ARRAY_BUFFER, sizeInBytes, squareColor, GL_STATIC_DRAW );
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// ~~~~~~ Second Shaping Binding and VAO setup ~~~~~~~~~~~~

	glBindVertexArray(vao[1]);
	// VBO loading to buffer for the square coordinate positions
	glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondShapeVertices), secondShapeVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	// VBO loading to buffer for the colors
	glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondShapeColor), secondShapeColor, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo[1]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(secondShapeIndices), secondShapeIndices, GL_STATIC_DRAW);

	//const uint32_t positionAttributeIndex = 0, colorAttributeIndex = 1;

	// Now start shaders 
}

// https://learnopengl.com/Getting-started/Hello-Triangle

/*const GLfloat square[4][3] =
	{
		// First Triangle
		{ -0.5, 0.5, 0.0 },	// Top Left
		{ -0.5, -0.5, 0.0 },// Bottom Left
		{ 0.5, -0.5, 0.0 },	// Bottom Right
		{ 0.5, 0.5, 0.0 },	// Top Right
	};

	const GLfloat squareColor[4][3] =
	{
		{ 1.0, 0.5, 1.0},
		{ 0.5, 1.0, 1.0},
		{ 1.0, 1.0, 0.5},
		{ 0.5, 0.5, 1.0},
	};

	const GLint indices[] =
	{
		0, 1, 3,
		1, 2, 3
	};
	*/
