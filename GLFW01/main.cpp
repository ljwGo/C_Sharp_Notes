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

	//��Ҫ�ĳ�ʼ��
	glfwInit();

	//Ϊglfw����ѡ��
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// ��������
	GLFWwindow* window = glfwCreateWindow(800, 600, "learnOpenGL", NULL, NULL);

	if (window == NULL) {
		std::cout << "faild to create windwo" << std::endl;
		glfwTerminate();
		return -1;
	}

	// �����ڰ�Ϊopengl��������
	glfwMakeContextCurrent(window);

	// ʹ��glad����opengl����ָ�룬�����ʼ��glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// �����ӿ�, opengl���ӿڴ���Ⱦ
	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//  ˫����--ǰ���屣�������������ͼ����������Ļ����ʾ�������еĵ���Ⱦָ����ں󻺳��ϻ��ơ������е���Ⱦָ��ִ����Ϻ����ǽ���(Swap)ǰ����ͺ󻺳壬����ͼ����������Գ���
	while (!glfwWindowShouldClose(window))
	{
		// ������ջ��������ֵ
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		// �����һ֡����ɫ����(����һЩ��̬������������ɫ����ȿ�������ı䣬��˿���ʹ�û���)
		glClear(GL_COLOR_BUFFER_BIT);

		processInput(window);
		// glfwPollEvents���������û�д���ʲô�¼�������������롢����ƶ��ȣ������´���״̬�������ö�Ӧ�Ļص�����������ͨ���ص������ֶ����ã�
		glfwPollEvents();

		//�����ύ����ɫ���壨����һ��������GLFW����ÿһ��������ɫֵ�Ĵ󻺳壩��������һ�����б��������ƣ����ҽ�����Ϊ�����ʾ����Ļ��
		glfwSwapBuffers(window);
	}

	// �ͷ�������Դ
	glfwTerminate();

	return 0;
}