#include "CApp.h"

void CApp::OnRender()
{

	glClearColor( r, g, b, 1.0 );
	glClear(GL_COLOR_BUFFER_BIT);

	
	/*for (int i = 0; i < 2; i++)
	{
		glBindVertexArray(vao[i]);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	}*/

	shader.useThisShader();
	glBindVertexArray(vao[0]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	shader2.useThisShader();
	glBindVertexArray(vao[1]);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	

	SDL_GL_SwapWindow(window);


}