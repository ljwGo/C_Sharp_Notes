#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "MyShader.h"

#define WINDOW_HEIGHT 600
#define WINDOW_WIDTH 800

int main(void) {

	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* win = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "variable type", NULL, NULL);
	if (win == NULL) {
		glfwTerminate();
		return -2;
	}

	glfwMakeContextCurrent(win);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		glfwTerminate();
		return -3;
	}

	glClearColor(0, 0, 0, 1.0);
	
	MyShader ms("./vertexShader.vs", "./fragmentShader.fs");
	ms.SetUniform1f("alpha", 0.5);
	ms.Use();

	//��������(ͬʱ�����˶���λ�ú���ɫ������)
	float vertices[] = {
		// ��һ������λ��
		-0.5, -0.5, 0.0,
		// ��һ��������ɫ
		1.0, 0.0, 0.0,
		// �ڶ�������λ��
		-0.5, 0.5, 0.0,
		// �ڶ���������ɫ
		0.0, 1.0, 0.0,
		// ����������λ��
		0.5, -0.5, 0.0,
		// ������������ɫ
		0.0, 0.0, 1.0,
		//�ڶ��������Σ�����ɫ����λ�ã�(�����ַ�ʽ��ʾλ�ò�ֵ��ֵ)
		0.6, 0.6, 0.0,
		0.6, 0.6, 0.0,
		0.9, 0.9, 0.0,
		0.9, 0.9, 0.0,
		0.6, 0.9, 0.0,
		0.6, 0.9, 0.0,
	};

	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	
	while (!glfwWindowShouldClose(win)) {

		glClear(GL_COLOR_BUFFER_BIT);

		// ��ʱ��ı�alpha
		float time = glfwGetTime();
		ms.SetUniform1f("alpha", (sin(time) + 1.0) * 0.5);
		glDrawArrays(GL_TRIANGLES, 0, 6);  // ����������ֵenable�Ķ��������indicte�ָ�Ԫ�ظ���

		glfwPollEvents();
		glfwSwapBuffers(win);
	}

	glfwTerminate();
	return 0;
}