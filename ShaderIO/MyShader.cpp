#include "MyShader.h"

MyShader::MyShader(std::string vertexShaderPath, std::string fragmentShaderPath) {

	// ֻ�����ļ�������
	std::ifstream vsFile, fsFile;
	// ȷ���ļ���ȡ�׳�����
	vsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fsFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	// �����ַ�����������
	std::stringstream vsStream, fsStream;
	std::string vsCode, fsCode;

	try {
		vsFile.open(vertexShaderPath);
		fsFile.open(fragmentShaderPath);

		vsStream << vsFile.rdbuf();
		fsStream << fsFile.rdbuf();
	}
	catch (std::ifstream::failure e) {
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
		std::cout << e.what() << std::endl;
	}

	vsCode = vsStream.str();
	fsCode = fsStream.str();

	unsigned int vsId, fsId;
	vsId = CreateShader(GL_VERTEX_SHADER, vsCode.c_str());
	fsId = CreateShader(GL_FRAGMENT_SHADER, fsCode.c_str());

	programId = glCreateProgram();
	glAttachShader(programId, vsId);
	glAttachShader(programId, fsId);
	glLinkProgram(programId);

	int success;
	char log[512];
	glGetProgramiv(programId, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(programId, 512, NULL, log);
		std::cout << "program link failed!" << std::endl;
		std::cout << log << std::endl;
	}
}

void MyShader::SetUniform4f(std::string uName, float x, float y, float z, float w) {
	glUseProgram(programId);
	// ����ͨ�����������ҵ���Ӧuniform������λ��
	int location = glGetUniformLocation(programId, uName.c_str());
	// ������uniformȫ�ֱ���ǰ���ǵñ���ָ������
	glUniform4f(location, x, y, z, w);
}

void MyShader::SetUniform1f(std::string uName, float val) {
	glUseProgram(programId);
	int location = glGetUniformLocation(programId, uName.c_str());
	glUniform1f(location, val);
};

void MyShader::Use() {
	glUseProgram(programId);
}

unsigned int MyShader::CreateShader(GLenum shaderType, const char* src) {
	unsigned int shaderId = glCreateShader(shaderType);
	glShaderSource(shaderId, 1, &src, NULL);
	glCompileShader(shaderId);

	int success;
	char log[512];
	glGetShaderiv(shaderId, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(shaderId, 512, NULL, log);
		std::cout << "shader compile failed!" << std::endl;
		std::cout << log << std::endl;
		return 0;
	}
	return shaderId;
}

void MyShader::DeleteShader(unsigned int id) {
	glDeleteShader(id);
}