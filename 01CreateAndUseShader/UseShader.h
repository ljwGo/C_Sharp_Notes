#pragma once
class UseShader
{
public:

	float vertices[9]{
		-0.5, -0.5, 0.0,
		0.5, -0.5, 0.0,
		0.0, 0.5, 0.0
	};

	float vertices02[9]{
		0.8, 0.8, 0.0,
		1.0, 1.0, 0.0,
		0.8, 1.0, 0.0
	};

	// 使用索引方式，避免顶点数据重复，复用数据创建多个三角形
	float vertices03[12]{
		-0.5, -0.5, 0.0,
		-0.5, 0.5, 0.0,
		0.5, 0.5, 0.0,
		0.5, -0.5, 0.0,
	};

	unsigned int index[6]{
		0, 1, 2,
		0, 2, 3
	};

	// 我理解它为buffer的地址
	unsigned int VBO;
	unsigned int VBO02;
	unsigned int VAO;
	unsigned int VAO02;

	unsigned int vertexShader;
	const char* vertexShaderSource = 
		"#version 460 core\n\
		 layout(location = 0) in vec3 vertexPos;\n\
		 void main(){\n\
		   gl_Position = vec4(vertexPos, 1.0);\n\
		 }";

	unsigned int fragmentShader;
	const char* fragmentShaderSource = 
		"#version 460 core\n\
		 out vec4 FragColor;\n\
		 void main(){\n\
			FragColor = vec4(0.5, 0.5, 0.0, 1.0);\n\
		}";

	unsigned int programId;

	void CreateVAO();
	void CreateVAO02();
	void CreateMulVBOAndVAO();
	void AssignVertices();
	void AssignVertices02();
	void AssignVerticesAndIndex();
	void CreateVertexShader();
	void CreateFragmentShader();
	void CreateProgram();
	void UseProgram();
};

