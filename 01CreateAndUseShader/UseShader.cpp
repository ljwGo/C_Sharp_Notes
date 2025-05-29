#include "UseShader.h"
#include <glad/glad.h>
#include <iostream>

void UseShader::CreateVertexShader() {
	// ����shader����ָ������
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Ϊshaderָ��Դ����
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	// ����shader
	glCompileShader(vertexShader);

	int success;
	char compileLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "complie vertex shader failed!" << std::endl;
		glGetShaderInfoLog(vertexShader, 512, NULL, compileLog);
		std::cout << "  msg: " << compileLog << std::endl;
	}
}

void UseShader::CreateFragmentShader(){
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
	glCompileShader(fragmentShader);

	int success;
	char compileLog[512];
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		std::cout << "complie fragment shader failed!" << std::endl;
		glGetShaderInfoLog(fragmentShader, 512, NULL, compileLog);
		std::cout << "  msg: " << compileLog << std::endl;
	}
}

void UseShader::CreateMulVBOAndVAO()
{
	unsigned int VAOs[2], VBOs[2];
	// ���е�һ������ָ�����ɵ�����
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
}

void UseShader::CreateProgram()
{
	// ������ɫ������
	programId = glCreateProgram();
	// ���ý�ǰ�洴����shader�󶨵�program��
	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	// ����������
	glLinkProgram(programId);

	int success;
	char log[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, log);
		std::cout << "shader link failed!" << std::endl;
		std::cout << "  msg: " << log << std::endl;
	}
}

void UseShader::UseProgram() {
	//��glUseProgram��������֮��ÿ����ɫ�����ú���Ⱦ���ö���ʹ������������Ҳ����֮ǰд����ɫ��)�ˡ�
	glUseProgram(programId);
}

void UseShader::AssignVerticesAndIndex()
{
	glBindVertexArray(VAO02);

	unsigned int verticesBuffer;
	glGenBuffers(1, &verticesBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, verticesBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices03), vertices03, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	unsigned int verticesIndex;
	glGenBuffers(1, &verticesIndex);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, verticesIndex);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

//�����������ᴢ��������Щ���ݣ�
//glEnableVertexAttribArray��glDisableVertexAttribArray�ĵ��á�
//ͨ��glVertexAttribPointer���õĶ����������á�
//ͨ��glVertexAttribPointer�����붥�����Թ����Ķ��㻺�����
void UseShader::CreateVAO()
{
	glGenVertexArrays(1, &VAO);
}

void UseShader::CreateVAO02()
{
	glGenVertexArrays(1, &VAO02);
}

// ��������vertex buufer���������ö����浽ͬһ��VAO��
// �������ֻ�к�һ�������α�����(ֻ�����һ��VBO�ᱻVAO��¼);
void UseShader::AssignVertices()
{
	// �����ñ��浽VAO��(������ô���뵽��ɫ����)
	glBindVertexArray(VAO);
	// ����buffer
	glGenBuffers(1, &VBO);
	// ��bufferΪGL_ARRAY_BUFFER���͵�buffer, ����buffer���;���GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// �������
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW ���ݼ�������ı�; 
	// GL_DYNAMIC_DRAW ���ݻ�ı�;
	// GL_STREAM_DRAW ���ݿ���Ƶ���ı�
	
	// �������opengl������ɫ������ηָ�buffer�е����ݸ���ɫ������
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	/*��һ������ָ������Ҫ���õĶ������ԡ����ǵ������ڶ�����ɫ����ʹ��layout(location = 0)������position�������Ե�λ��ֵ(Location)�������԰Ѷ������Ե�λ��ֵ����Ϊ0����Ϊ����ϣ�������ݴ��ݵ���һ�����������У������������Ǵ���0��
	�ڶ�������ָ���������ԵĴ�С������������һ��vec3������3��ֵ��ɣ����Դ�С��3��
	����������ָ�����ݵ����ͣ�������GL_FLOAT(GLSL��vec * �����ɸ�����ֵ��ɵ�)��
	�¸��������������Ƿ�ϣ�����ݱ���׼��(Normalize)�������������ΪGL_TRUE���������ݶ��ᱻӳ�䵽0�������з�����signed������ - 1����1֮�䡣���ǰ�������ΪGL_FALSE��
	�����������������(Stride)�������������������Ķ���������֮��ļ���������¸���λ��������3��float֮�����ǰѲ�������Ϊ3 * sizeof(float)��Ҫע�������������֪����������ǽ������еģ���������������֮��û�п�϶������Ҳ��������Ϊ0����OpenGL�������岽���Ƕ��٣�ֻ�е���ֵ�ǽ�������ʱ�ſ��ã���һ�������и���Ķ������ԣ����Ǿͱ����С�ĵض���ÿ����������֮��ļ���������ں���ῴ����������ӣ���ע: �����������˼��˵���Ǵ�������Եڶ��γ��ֵĵط�����������0λ��֮���ж����ֽڣ���
	���һ��������������void * ��������Ҫ���ǽ��������ֵ�ǿ������ת��������ʾλ�������ڻ�������ʼλ�õ�ƫ����(Offset)������λ������������Ŀ�ͷ������������0�����ǻ��ں�����ϸ�������������*/
	glEnableVertexAttribArray(0);
	// ������ɫ����ָ������������(Ĭ���������ʹ��)

	glGenBuffers(1, &VBO02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO02);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices02), vertices02, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// ȡ��VAO��
	glBindVertexArray(0);
}

// ��������vertex buufer�������ñ��浽��ͬ��VAO��
void UseShader::AssignVertices02()
{
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	
	glEnableVertexAttribArray(0);

	glBindVertexArray(VAO02);
	glGenBuffers(1, &VBO02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO02);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices02), vertices02, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}