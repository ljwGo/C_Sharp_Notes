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
		// �ں���ģʽ�£�Ҫ������VAO������opengl��ܾ�������������
		// VAO�Ƚ�����⣬����������˵���ģ�
		// Ϊ����Ⱦһ��ģ�ͣ����Ǳ��봫���ģ�͵Ķ�������(���ܰ�����������)����buffer���Ƶ�gpu��
		// ͬʱ��ҪΪshaderָ����ν�buffer���ݷָ�Ϊ����
		// ���г�ǧ��������ʱ����Ҫִ�кܶ�Ρ�
		// ����ʹ��VAO�����һ������VBO�Ĳ����������л���Ⱦģʽ����ӱ�ݡ�
		
		// �ܷ����л���Ⱦ�Ķ���
		//glBindVertexArray(myShaderProgram.VAO);
		//glBindVertexArray(myShaderProgram.VAO02);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// ��Ҫ��Ⱦ���ģ��(���VBO)����Ҫ�ֱ��VAO, ����ε���glDrawArrays��glDrawElements
		glBindVertexArray(myShaderProgram.VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(myShaderProgram.VAO02);
		glDrawArrays(GL_TRIANGLES, 0, 3);  // 3ָ���Ƕ�����?

		// ����Ϊ�߿�ģʽ
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		// ����Ϊ����ģʽ
		//glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		// ʹ��������������glDrawElements���ơ�
		// VAOҲ�ᱣ��EBO������
		//glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);  // 6ָ����������?

		glfwPollEvents();
		glfwSwapBuffers(win);
	}

	glfwTerminate();
	
	return 0;
}