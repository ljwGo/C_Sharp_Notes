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

	//构建数据(同时保存了顶点位置和颜色的数据)
	float vertices[] = {
		// 第一个顶点位置
		-0.5, -0.5, 0.0,
		// 第一个顶点颜色
		1.0, 0.0, 0.0,
		// 第二个顶点位置
		-0.5, 0.5, 0.0,
		// 第二个顶点颜色
		0.0, 1.0, 0.0,
		// 第三个顶点位置
		0.5, -0.5, 0.0,
		// 第三个顶点颜色
		0.0, 0.0, 1.0,
		//第二个三角形，让颜色等于位置，(用这种方式显示位置插值的值)
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

		// 随时间改变alpha
		float time = glfwGetTime();
		ms.SetUniform1f("alpha", (sin(time) + 1.0) * 0.5);
		glDrawArrays(GL_TRIANGLES, 0, 6);  // 第三个向量值enable的顶点数组的indicte分割元素个数

		glfwPollEvents();
		glfwSwapBuffers(win);
	}

	glfwTerminate();
	return 0;
}