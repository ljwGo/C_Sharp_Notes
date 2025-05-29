#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "UseShader.h"

using namespace std;

#define MY_WINDOW_WIDTH 800
#define MY_WINDOW_HEIGHT 600

void framebufferSizeChange(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

void getKeyDown(GLFWwindow* window, int key, int scancode, int action, int mods) {
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void) {

	if (glfwInit() == GLFW_FALSE) {
		glfwTerminate();
		cout << "init glfw failed!" << endl;
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(MY_WINDOW_WIDTH, MY_WINDOW_HEIGHT, "How to use opengl to draw a triangle!", NULL, NULL);
	if (win == NULL) {
		cout << "create window failed!" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, MY_WINDOW_WIDTH, MY_WINDOW_HEIGHT);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	UseShader myShaderProgram;
	myShaderProgram.CreateVAO();
	myShaderProgram.CreateVAO02();
	myShaderProgram.AssignVertices02();
	//myShaderProgram.AssignVerticesAndIndex();
	myShaderProgram.CreateVertexShader();
	myShaderProgram.CreateFragmentShader();
	myShaderProgram.CreateProgram();
	myShaderProgram.UseProgram();

	// register callback
	glfwSetFramebufferSizeCallback(win, framebufferSizeChange);
	glfwSetKeyCallback(win, getKeyDown);

	while (!glfwWindowShouldClose(win)) {
		glClear(GL_COLOR_BUFFER_BIT);
		// 在核心模式下，要求必须绑定VAO；否则opengl会拒绝绘制所有内容
		// VAO比较难理解，例子是这样说明的：
		// 为了渲染一个模型，我们必须传入该模型的顶点数据(可能包括其他数据)，用buffer复制到gpu。
		// 同时需要为shader指明如何将buffer数据分割为属性
		// 当有成千上万物体时，需要执行很多次。
		// 可以使用VAO保存对一个或多个VBO的操作，这样切换渲染模式会更加便捷。
		
		// 很方便切换渲染的对象
		//glBindVertexArray(myShaderProgram.VAO);
		//glBindVertexArray(myShaderProgram.VAO02);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// 想要渲染多个模型(多个VBO)，需要分别绑定VAO, 并多次调用glDrawArrays或glDrawElements
		glBindVertexArray(myShaderProgram.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(myShaderProgram.VAO02);
		glDrawArrays(GL_TRIANGLES, 0, 3);  // 3指的是顶点数?

		// 设置为线框模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// 设置为正常模式
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// 使用索引，必须用glDrawElements绘制。
		// VAO也会保存EBO的设置
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // 6指的是索引数?

		glfwPollEvents();
		glfwSwapBuffers(win);
	}

	glfwTerminate();
	
	return 0;
}