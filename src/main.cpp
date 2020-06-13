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

	glfwMakeContextCurrent(window);

	while(!glfwWindowShouldClose(window)){

		//Render Stuff in here between glf..ShouldClose and glfwWaitevents()
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glDrawPixels(100, 100, GL_RGB, GL_UNSIGNED_BYTE, data);
		glfwSwapBuffers(window);

		glfwWaitEvents();

	}

	return 0;
}





