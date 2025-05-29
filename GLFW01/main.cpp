#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window) {
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
}

int main(void) {

	//必要的初始化
	glfwInit();

	//为glfw设置选项
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// 创建窗口
	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "faild to create windwo" << std::endl;
		glfwTerminate();
		return -1;
	}

	// 将窗口绑定为opengl的上下文
	glfwMakeContextCurrent(window);

	// 使用glad加载opengl函数指针，这里初始化glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// 设置视口, opengl在视口处渲染
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//  双缓冲--前缓冲保存着最终输出的图像，它会在屏幕上显示；而所有的的渲染指令都会在后缓冲上绘制。当所有的渲染指令执行完毕后，我们交换(Swap)前缓冲和后缓冲，这样图像就立即呈显出来
	while (!glfwWindowShouldClose(window))
	{
		// 设置清空缓存后的填充值
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// 清空上一帧的颜色缓存(对于一些静态场景，它的颜色和深度可能无需改变，因此可以使用缓存)
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);
		// glfwPollEvents函数检查有没有触发什么事件（比如键盘输入、鼠标移动等）、更新窗口状态，并调用对应的回调函数（可以通过回调方法手动设置）
		glfwPollEvents();

		//函数会交换颜色缓冲（它是一个储存着GLFW窗口每一个像素颜色值的大缓冲），它在这一迭代中被用来绘制，并且将会作为输出显示在屏幕上
		glfwSwapBuffers(window);
	}

	// 释放所有资源
	glfwTerminate();

	return 0;
}