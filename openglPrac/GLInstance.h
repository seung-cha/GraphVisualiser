#ifndef GLINSTANCE_H
#define GLINSTANCE_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include "stb_image.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

using namespace glm;

class GLInstance
{
public:
	/// <summary>
	/// Initialise a new GLFW Instance.
	/// Does not initialise a GLFW window, however.
	/// </summary>
	GLInstance();
	/// <summary>
	/// Initialise a new GLFW Instance and set major and minor versions.
	/// Does not initialise a GLFW window, however.
	/// </summary>
	/// <param name="majorVersion"></param>
	/// <param name="minorVersion"></param>
	GLInstance(int majorVersion, int minorVersion);
	void SetMajorVersion(int majorVersion);
	void SetMinorVersion(int minorVersion);
	void SetVersion(int majorVersion, int minorVersion);
	void SetScreenWidth(int width);
	void SetScreenHeight(int height);
	void SetScreenSize(int width, int height);

	void CreateElementBuffer(unsigned int arr[], int sizeInByte);

	/// <summary>
	/// Create a new vertex buffer to the current instance of GLAD,
	/// Assumed the array is always tightly packed.
	/// 
	/// Note that a Vertex Array Object must be created beforehand.
	/// </summary>
	/// <param name="arr"> Array containing vertices info</param>
	/// <param name="dimensions"> Dimension of the arr (example: 3 (vec3) or 4 (vec4))</param>
	/// <param name="sizeInByte"> Size of the array in byte. That is, sizeof(arr)</param>
	void CreateVertexBuffer(float arr[], int dimensions, int sizeInByte);

	void CreateVertexArray();

	/// <summary>
	/// Create a new instance of GLFW window.
	/// </summary>
	/// <param name="title"></param>
	/// <returns></returns>
	int InitialiseWindow(const char* title);
	/// <summary>
	/// Create a new instance of GLFW window.
	/// </summary>
	/// <param name="width"></param>
	/// <param name="height"></param>
	/// <param name="title"></param>
	/// <returns></returns>
	int InitialiseWindow(int width, int height, const char* title);

	void CreateVertexShaderFromFile(const char* filePath);
	void CreateFragmentShaderFromFile(const char* filePath);
	void CompileShaderObjects();
	void FreeShaders();
	void UseShader();

	void SwapBuffers();
	void PollEvents();

	void CreateTexture(const char* path, const char* name);

	int ShouldWindowClose();

	void BindVertexArray();


	void Draw(bool usingEBO, int noVertices, int GLDrawMode);


	void UniformVecFloat(const char* name, float val1);
	void UniformVecFloat(const char* name, float val1, float val2);
	void UniformVecFloat(const char* name, float val1, float val2, float val3);
	void UniformVecFloat(const char* name, float val1, float val2, float val3, float val4);


	void UniformMatVec4(const char* name, mat4 matrix, bool transpose);
	void UniformMatVec3(const char* name, mat3 matrix, bool transpose);
	void UniformMatVec2(const char* name, mat2 matrix, bool transpose);

	void CloseWindow();
	void OnScreenSizeChanged(GLFWframebuffersizefun func);

	/// <summary>
	/// Returns if a key is pressed.
	/// </summary>
	/// <param name="GLFWKEY">GLFW macro, wrriten as GLFW_KEY_{keyType}</param>
	/// <returns></returns>
	bool IsKeyPressed(int GLFWKEY);



private:
	int majorVersion = -1;
	int minorVersion = -1;
	int screenWidth = -1;
	int screenHeight = -1;
	int currentEnabledBuffers = 0;
	int currentActiveTextures = 0;
	GLFWwindow* window = NULL;
	unsigned int vertexShaderObject = NULL;
	unsigned int fragmentShaderObject = NULL;
	unsigned int shaderObject = NULL;
	unsigned int vertexArrayObject = NULL;
	unsigned int elementBufferObject = NULL;

	int FindUniformPosition(const char* name);



};



#endif



