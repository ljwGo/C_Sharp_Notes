#include "UseShader.h"
#include <glad/glad.h>
#include <iostream>

void UseShader::CreateVertexShader() {
	// 创建shader，并指定类型
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// 为shader指定源代码
	glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
	// 编译shader
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
	// 其中第一个参数指定生成的数量
	glGenBuffers(2, VBOs);
	glGenVertexArrays(2, VAOs);
}

void UseShader::CreateProgram()
{
	// 创建着色器程序
	programId = glCreateProgram();
	// 设置将前面创建的shader绑定到program上
	glAttachShader(programId, vertexShader);
	glAttachShader(programId, fragmentShader);
	// 最后进行链接
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
	//在glUseProgram函数调用之后，每个着色器调用和渲染调用都会使用这个程序对象（也就是之前写的着色器)了。
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

//顶点数组对象会储存以下这些内容：
//glEnableVertexAttribArray和glDisableVertexAttribArray的调用。
//通过glVertexAttribPointer设置的顶点属性配置。
//通过glVertexAttribPointer调用与顶点属性关联的顶点缓冲对象。
void UseShader::CreateVAO()
{
	glGenVertexArrays(1, &VAO);
}

void UseShader::CreateVAO02()
{
	glGenVertexArrays(1, &VAO02);
}

// 创建两个vertex buufer，并将配置都保存到同一个VAO中
// 结果导致只有后一个三角形被绘制(只有最后一个VBO会被VAO记录);
void UseShader::AssignVertices()
{
	// 将配置保存到VAO中(数据怎么传入到着色器中)
	glBindVertexArray(VAO);
	// 创建buffer
	glGenBuffers(1, &VBO);
	// 绑定buffer为GL_ARRAY_BUFFER类型的buffer, 顶点buffer类型就是GL_ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	// 填充数据
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	// GL_STATIC_DRAW 数据几乎不会改变; 
	// GL_DYNAMIC_DRAW 数据会改变;
	// GL_STREAM_DRAW 数据可能频繁改变
	
	// 必须告诉opengl，在着色器中如何分割buffer中的数据给着色器属性
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	/*第一个参数指定我们要配置的顶点属性。还记得我们在顶点着色器中使用layout(location = 0)定义了position顶点属性的位置值(Location)吗？它可以把顶点属性的位置值设置为0。因为我们希望把数据传递到这一个顶点属性中，所以这里我们传入0。
	第二个参数指定顶点属性的大小。顶点属性是一个vec3，它由3个值组成，所以大小是3。
	第三个参数指定数据的类型，这里是GL_FLOAT(GLSL中vec * 都是由浮点数值组成的)。
	下个参数定义我们是否希望数据被标准化(Normalize)。如果我们设置为GL_TRUE，所有数据都会被映射到0（对于有符号型signed数据是 - 1）到1之间。我们把它设置为GL_FALSE。
	第五个参数叫做步长(Stride)，它告诉我们在连续的顶点属性组之间的间隔。由于下个组位置数据在3个float之后，我们把步长设置为3 * sizeof(float)。要注意的是由于我们知道这个数组是紧密排列的（在两个顶点属性之间没有空隙）我们也可以设置为0来让OpenGL决定具体步长是多少（只有当数值是紧密排列时才可用）。一旦我们有更多的顶点属性，我们就必须更小心地定义每个顶点属性之间的间隔，我们在后面会看到更多的例子（译注: 这个参数的意思简单说就是从这个属性第二次出现的地方到整个数组0位置之间有多少字节）。
	最后一个参数的类型是void * ，所以需要我们进行这个奇怪的强制类型转换。它表示位置数据在缓冲中起始位置的偏移量(Offset)。由于位置数据在数组的开头，所以这里是0。我们会在后面详细解释这个参数。*/
	glEnableVertexAttribArray(0);
	// 开启着色器中指定索引的属性(默认情况不能使用)

	glGenBuffers(1, &VBO02);
	glBindBuffer(GL_ARRAY_BUFFER, VBO02);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices02), vertices02, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// 取消VAO绑定
	glBindVertexArray(0);
}

// 创建两个vertex buufer，将配置保存到不同的VAO中
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