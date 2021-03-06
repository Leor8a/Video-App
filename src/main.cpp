#include <stdio.h>
#include <GLFW/glfw3.h>


int main(int argc, const char** argv){
	GLFWwindow* window;

	if (!glfwInit()) {
		printf("Couldn't init GLFW\n");
		return 1;
	}

	window = glfwCreateWindow(648, 480, "Jurassic Snap", NULL, NULL);
	if(!window) {
		printf("Couldn't open window\n");
		return 1;
	}

	//Creating Buffers:
	//Each pixel has 3 bytes
    //Render data on the screen
	unsigned char* data = new unsigned char[100 * 100 * 3];
	for (int y = 0; y < 100 ; ++y) {
		for (int x = 0; x < 100 ; ++x){
			data[ y * 100 * 3 + x * 3    ] = 0xff;
			data[ y * 100 * 3 + x * 3 + 1] = 0x00;
			data[ y * 100 * 3 + x * 3 + 2] = 0x00;

		}
	}

	for (int y = 25; y < 75 ; ++y) {
		for (int x = 25; x < 75 ; ++x){
			data[ y * 100 * 3 + x * 3    ] = 0x00;
			data[ y * 100 * 3 + x * 3 + 1] = 0x00;
			data[ y * 100 * 3 + x * 3 + 2] = 0xff;

		}
	}
    glfwMakeContextCurrent(window); 
    
	GLuint tex_handle;
    int tex_width = 100;
    int tex_height = 100;
    
	glGenTextures(1, &tex_handle);
	glBindTexture(GL_TEXTURE_2D, tex_handle); //this use it right now
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_width, tex_height, 0, GL_RGB , GL_UNSIGNED_BYTE, data);

	
	while(!glfwWindowShouldClose(window)){

		//Render Stuff in here between glf..ShouldClose and glfwWaitevents()
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		
		//Setup orthographic proyection
		//GLFW nos dice el width y el height del contexto...
		int window_width, window_height;
		glfwGetFramebufferSize(window, &window_width , &window_height);

		glMatrixMode(GL_PROJECTION);
		//Hay 2 matrices en opengl, la proyección y la del model view
		//Si quieres cambiar la manera en que las cosas se ven se cambia la matriz de proyección
		//Si quieres añadir una cosa despues de establecer la cámara, o cosas en el mundo ..se usa la model view
		glLoadIdentity();//Resetea a una matriz identidad
		glOrtho(0, window_width, 0, window_height, -1, 1);
		glMatrixMode(GL_MODELVIEW);

		//Render whatever you want...
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, tex_handle);
		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex2i(0,0);
			glTexCoord2d(1,0); glVertex2i(tex_width,0);
			glTexCoord2d(1,1); glVertex2i(tex_width,tex_height);
			glTexCoord2d(0,1); glVertex2i(0,tex_height);
		glEnd();
		glDisable(GL_TEXTURE_2D);


		glfwSwapBuffers(window);
		glfwWaitEvents();

	}

	return 0;
}





