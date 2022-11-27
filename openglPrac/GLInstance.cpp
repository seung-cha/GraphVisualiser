#include "GLInstance.h"

using namespace std;

GLInstance::GLInstance()
{
	window = NULL;
	if (!glfwInit())
	{
		cout << "An error occured while initialising a new GLFW instance" << endl;
		return;
	}
	cout << "Successfully initialised a new instance of GLFW" << endl;
}


GLInstance::GLInstance(int majorVersion, int minorVersion)
{
	GLInstance();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);

	this->majorVersion = majorVersion;
	this->minorVersion = minorVersion;
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void GLInstance::SetMajorVersion(int majorVersion)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, majorVersion);
}

void GLInstance::SetMinorVersion(int minorVersion)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, minorVersion);
}

void GLInstance::SetVersion(int majorVersion, int minorVersion)
{
	SetMajorVersion(majorVersion);
	SetMinorVersion(minorVersion);
}

void GLInstance::SetScreenHeight(int height)
{
	screenHeight = height;
}

void GLInstance::SetScreenWidth(int width)
{
	screenWidth = width;
}

void GLInstance::SetScreenSize(int width, int height)
{
	SetScreenHeight(height);
	SetScreenWidth(width);
}

int GLInstance::InitialiseWindow(const char* title)
{
	if (screenWidth < 0)
	{
		cout << "Width is not defined yet." << endl;
		return 0;
	}

	if (screenHeight < 0)
	{
		cout << "Height is not defined yet." << endl;
		return 0;
	}

	if (majorVersion < 0)
	{
		cout << "Major version is not set yet." << endl;
		return 0;
	}

	if (minorVersion < 0)
	{
		cout << "Minor version is not set yet." << endl;
		return 0;
	}

	window = glfwCreateWindow(screenWidth, screenHeight, title, NULL, NULL);

	if (!window)
	{
		cout << "An error occured while creating a new instance of GLFW window" << endl;
		return 0;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "An error occured while initialising a new GLAD instance" << endl;
		return 0;
	}
	cout << "Successfully initialised a new instance of GLAD" << endl;

	glViewport(0, 0, screenWidth, screenHeight);
	return 1;
}

int GLInstance::InitialiseWindow(int width, int height, const char* title)
{
	SetScreenSize(width, height);
	return InitialiseWindow(title);
}

void GLInstance::CreateVertexBuffer(float arr[], int dimensions, int sizeInByte)
{
	if (vertexArrayObject == NULL)
	{
		cout << "Please create a Vertex Array Object before creating a new Vertex Buffer!" << endl;
		return;
	}

	unsigned int obj;
	glGenBuffers(1, &obj);

	glBindBuffer(GL_ARRAY_BUFFER, obj);
	glBufferData(GL_ARRAY_BUFFER, sizeInByte, arr, GL_STATIC_DRAW);

	glVertexAttribPointer(currentEnabledBuffers, dimensions, GL_FLOAT, GL_FALSE, dimensions * sizeof(float), (void*)0);
	glEnableVertexAttribArray(currentEnabledBuffers);
	currentEnabledBuffers++;
}

void GLInstance::CreateElementBuffer(unsigned int arr[], int sizeInByte)
{
	glGenBuffers(1, &elementBufferObject);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeInByte, arr, GL_STATIC_DRAW);
	

	
}

void GLInstance::CreateVertexShaderFromFile(const char* filePath)
{
	ifstream file;
	string str;
	try
	{
		file.open(filePath);
		stringstream ss;

		ss << file.rdbuf();

		str = ss.str();
		file.close();

	}
	catch (...)
	{
		cout << "An error occurred while reading vertex shader" << endl;
		return;
	}
	const char* items = str.c_str();
	vertexShaderObject = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderObject, 1, &items, NULL);
	glCompileShader(vertexShaderObject);

	


}

void GLInstance::CreateFragmentShaderFromFile(const char* filePath)
{
	ifstream file;
	string str;
	try
	{
		file.open(filePath);
		stringstream ss;

		ss << file.rdbuf();

		str = ss.str();

		file.close();

	}
	catch (...)
	{
		cout << "An error occurred while reading vertex shader" << endl;
		return;
	}
	const char* items = str.c_str();
	fragmentShaderObject = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderObject, 1, &items, NULL);
	glCompileShader(fragmentShaderObject);
}

void GLInstance::CompileShaderObjects()
{
	if (vertexShaderObject == NULL)
	{
		cout << "Vertex Shader Object is not initialised!" << endl;
		return;
	}

	if (fragmentShaderObject == NULL)
	{
		cout << "Fragment Shader Object is not initialised!" << endl;
		return;
	}

	shaderObject = glCreateProgram();
	glAttachShader(shaderObject, vertexShaderObject);
	glAttachShader(shaderObject, fragmentShaderObject);
	glLinkProgram(shaderObject);
}

void GLInstance::FreeShaders()
{
	glDeleteProgram(vertexShaderObject);
	glDeleteProgram(fragmentShaderObject);
}

void GLInstance::UseShader()
{
	if (shaderObject == NULL)
	{
		cout << "Shader Object is not initialised yet!" << endl;
		return;
	}

	glUseProgram(shaderObject);
}

void GLInstance::SwapBuffers()
{
	glfwSwapBuffers(window);
}

void GLInstance::PollEvents()
{
	glfwPollEvents();
}

int GLInstance::ShouldWindowClose()
{
	return glfwWindowShouldClose(window);
}

void GLInstance::CreateVertexArray()
{
	glGenVertexArrays(1, &vertexArrayObject);
	glBindVertexArray(vertexArrayObject);
}

void GLInstance::BindVertexArray()
{
	glBindVertexArray(vertexArrayObject);
}

void GLInstance::Draw(bool usingEBO, int noVertices, int GLDrawMode)
{
	if (usingEBO)
	{
		glDrawElements(GLDrawMode, noVertices, GL_UNSIGNED_INT, 0);
		return;
	}

	glDrawArrays(GL_TRIANGLES, 0, noVertices);
}

int GLInstance::FindUniformPosition(const char* name)
{
	return glGetUniformLocation(shaderObject, name);
}

void GLInstance::UniformVecFloat(const char* name, float val1)
{
	int pos = FindUniformPosition(name);
	glUniform1f(pos, val1);
}

void GLInstance::UniformVecFloat(const char* name, float val1, float val2)
{
	int pos = FindUniformPosition(name);
	glUniform2f(pos, val1, val2);
}

void GLInstance::UniformVecFloat(const char* name, float val1, float val2, float val3)
{
	int pos = FindUniformPosition(name);
	glUniform3f(pos, val1, val2, val3);
}

void GLInstance::UniformVecFloat(const char* name, float val1, float val2, float val3, float val4)
{
	int pos = FindUniformPosition(name);
	glUniform4f(pos, val1, val2, val3, val4);
}

void GLInstance::CreateTexture(const char* path, const char* name)
{
	stbi_set_flip_vertically_on_load(true);
	int width, height, nrChannels;

	unsigned char* img = stbi_load(path, &width, &height, &nrChannels, 0);

	if (img == NULL)
	{
		cout << "Image path is invalid!" << endl;
		return;
	}

	unsigned int texture;
	glActiveTexture(GL_TEXTURE0 + currentActiveTextures);
	glGenTextures(1, &texture);

	glBindTexture(GL_TEXTURE_2D, texture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, img);
	glGenerateMipmap(GL_TEXTURE_2D);

	glUniform1i(FindUniformPosition(name), currentActiveTextures);
	glBindTexture(GL_TEXTURE_2D, texture);
	stbi_image_free(img);

	currentActiveTextures++;
}

void GLInstance::CloseWindow()
{
	glfwSetWindowShouldClose(window, true);
}

void GLInstance::OnScreenSizeChanged(GLFWframebuffersizefun func)
{
	glfwSetFramebufferSizeCallback(window, func);
}

bool GLInstance::IsKeyPressed(int GLFWKey)
{
	return glfwGetKey(window, GLFWKey) == GLFW_PRESS;
}

void GLInstance::UniformMatVec4(const char* name, mat4 matrix, bool transpose)
{
	if (transpose)
		glUniformMatrix4fv(FindUniformPosition(name), 1, GL_TRUE, value_ptr(matrix));
	else
		glUniformMatrix4fv(FindUniformPosition(name), 1, GL_FALSE, value_ptr(matrix));
}

void GLInstance::UniformMatVec3(const char* name, mat3 matrix, bool transpose)
{
	if (transpose)
		glUniformMatrix3fv(FindUniformPosition(name), 1, GL_TRUE, value_ptr(matrix));
	else
		glUniformMatrix3fv(FindUniformPosition(name), 1, GL_FALSE, value_ptr(matrix));
}

void GLInstance::UniformMatVec2(const char* name, mat2 matrix, bool transpose)
{
	if (transpose)
		glUniformMatrix2fv(FindUniformPosition(name), 1, GL_TRUE, value_ptr(matrix));
	else
		glUniformMatrix2fv(FindUniformPosition(name), 1, GL_FALSE, value_ptr(matrix));
}