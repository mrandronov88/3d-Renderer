#include <stdlib.h>
#include <stdio.h>
#include <SDL.h>
#define GLEW_STATIC
#include <glew.h>
#include <SDL_opengl.h>
#include <gl/GLU.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Shader
{	

	public:

		const char* fragShaderFile = "";
		int shaderProgram;

		void setFragShader(const char *fragShaderFile)
		{
			this->fragShaderFile = fragShaderFile;
		}

		void useThisShader()
		{
			glUseProgram( shaderProgram );
		}

		void init()
		{
			shaderProgram = glCreateProgram();
			std::cout << "HELLLO WORLD\n";

			int vertID = LoadShader( "vert.txt", GL_VERTEX_SHADER );
			glAttachShader( shaderProgram, vertID );

			// int geomID = LoadShader( "geom.glsl", GL_GEOMETRY_SHADER );
			// glAttachShader( geomID, vertID );

			int fragID = LoadShader( fragShaderFile, GL_FRAGMENT_SHADER );
			glAttachShader( shaderProgram, fragID );

			glLinkProgram( shaderProgram );
			int IsLinked;

			glGetProgramiv(shaderProgram, GL_LINK_STATUS, (int *) &IsLinked);
			if (IsLinked == false)
			{
				std::cout << "Program error!";
				printProgramLog(shaderProgram);
			}

			std::cout << "Program is working correctly.\n";

			glUseProgram( shaderProgram );
		}

	private:

		char* ReadFile( const char *file )
		{
			FILE *filePtr;
			long length;
			char* buf;

			// Open file
			filePtr = fopen(file, "rb");

			if ( !filePtr )
			{
				return NULL;
			}
			std::cout << "The file has been found : " + *file + *("\n");
			
			
			// Find lenght of file and allocate memory for buffer
			// based on length
			fseek( filePtr, 0, SEEK_END );
			length = ftell( filePtr );
			buf = (char*)malloc(length - 1);
			fseek( filePtr, 0, SEEK_SET );

			// Read file into buffer
			fread( buf, length, 1, filePtr );

			// Close the file and null terminator
			fclose( filePtr );
			buf[length] = 0;

			return buf;

		}

		int LoadShader( const char *str, GLenum shaderType)
		{
			// Read file as std::string
			char* src = ReadFile(str);

			// c_str() gives us a const char*, but we need a non-const one
			//std::string* temp = (std::string) src;

			GLint size = strlen(src);

			// Create an empty vertex shader handle
			int shaderID = glCreateShader( shaderType );

			// Send the vertex shader source code to OpenGL
			glShaderSource( shaderID, 1, &src, NULL );

			// Compile the shader
			glCompileShader( shaderID );

			int wasCompiled = 0;
			glGetShaderiv( shaderID, GL_COMPILE_STATUS, &wasCompiled );

			std::string shadeTyp = "~~~";

			if (shaderType == GL_VERTEX_SHADER)
			{
				shadeTyp = "*vertex shader*";
			}
			else
			{
				shadeTyp = "*fragment shader*";
			}

			if (wasCompiled == true)
			{
				std::cout << "The shader :|" + shadeTyp + "| has compiled succesfully\n";
			}
			PrintShaderCompilationError( shaderID );

			return shaderID;

			// https://www.khronos.org/opengl/wiki/Tutorial2:_VAOs,_VBOs,_Vertex_and_Fragment_Shaders_(C_/_SDL)

		}

		void PrintShaderCompilationError(GLuint shaderID)
		{
			// Find length of shader info log
			int maxLength;
			glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

			// Get shader info log
			char* shaderInfoLog = new char[maxLength];
			glGetShaderInfoLog(shaderID, maxLength, &maxLength, shaderInfoLog);

			std::string log = shaderInfoLog;

			if (log.length())
			{
				std::cout << "=======================================\n";
				std::cout << shaderInfoLog << std::endl;
				std::cout << "=======================================\n\n";
			}

			// Print shader info log
			delete shaderInfoLog;
		}

		void printProgramLog(GLuint program)
		{

			int maxLength;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			char* programInfoLog = new char[maxLength];
			glGetProgramInfoLog(program, maxLength, &maxLength, programInfoLog);

			std::string log = programInfoLog;

			if (log.length())
			{
				std::cout << "=======================================\n";
				std::cout << programInfoLog << std::endl;
				std::cout << "=======================================\n\n";
			}

			delete programInfoLog;

		}

};
