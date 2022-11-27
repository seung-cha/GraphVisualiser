#include "GLInstance.h"


//Create Camera
vec3 camPos = vec3(0, 0, 3);
vec3 camFront = vec3(0, 0, -1);
vec3 camUp = vec3(0, 1, 0);


vec3 camDir = normalize(camPos - vec3(0, 0, 0));
vec3 camRight = normalize(cross(vec3(0, 1, 0), camDir));
//vec3 camUp = cross(camDir, camRight);

float deltaTime = 0.0f;
float lastFrame = 0.0f;



void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void receiveKeys(GLInstance instance)
{
	if (instance.IsKeyPressed(GLFW_KEY_ESCAPE))
	{
		instance.CloseWindow();
	}


	float camSpeed = 25.0f * deltaTime;

	//std::cout << "Coordinates: " << camPos.x << " | " << camPos.y << " | " << camPos.z << " " << std::endl;
	if (instance.IsKeyPressed(GLFW_KEY_W))
	{
		camPos += camSpeed * camFront;
	}

	if (instance.IsKeyPressed(GLFW_KEY_S))
	{
		camPos -= camSpeed * camFront;
	}

	if (instance.IsKeyPressed(GLFW_KEY_A))
	{
		camPos -= normalize(cross(camFront, camUp)) * camSpeed;
	}

	if (instance.IsKeyPressed(GLFW_KEY_A))
	{
		camPos += normalize(cross(camFront, camUp)) * camSpeed;
	}

}


int main()
{

	/*
	float vertices[] =
	{
	-0.5f, -0.5f, -0.5f,
	0.5f, -0.5f, -0.5f,
	0.5f, 0.5f, -0.5f,
   -0.5f, 0.5f, -0.5f,
   -0.5f, -0.5f, 0.5f,
	0.5f, -0.5f, 0.5f,
	0.5f, 0.5f, 0.5f,
   -0.5f, 0.5f, 0.5f


	};
	*/

	float vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};

	float textureCoords[] =
	{
		-1.0f, -1.0f,
		1.0f, -1.0f,
		1.0f, 1.0f,
		-1.0f, 1.0f,
	};

	/*
	unsigned int indices[] =
	{
		 0, 1, 3, 3, 1, 2, // Front face.
	0, 1, 4, 4, 5, 1, // Bottom face.
	1, 2, 5, 5, 6, 2, // Right face.
	2, 3, 6, 6, 7, 3, // Top face.
	3, 7, 4, 4, 3, 0, // Left face.
	4, 5, 7, 7, 6, 5, // Rear face.

	};
	*/

	unsigned int indices[] =
	{
		0,1,2,
		0,2,3,
	};

	GLInstance glInstance(3, 3);
	
	glInstance.InitialiseWindow(600, 400, "Hallo Walrd");
	glInstance.OnScreenSizeChanged(framebuffer_size_callback);

	glInstance.CreateVertexShaderFromFile
	("C:\\Users\\pro gamer\\source\\repos\\openglPrac\\openglPrac\\VertexSource.txt");

	glInstance.CreateFragmentShaderFromFile
	("C:\\Users\\pro gamer\\source\\repos\\openglPrac\\openglPrac\\FragmentSource.txt");
	glInstance.CompileShaderObjects();
	glInstance.UseShader();
	glInstance.FreeShaders();


	glInstance.CreateVertexArray();
	glInstance.CreateVertexBuffer(vertices, 3, sizeof(vertices));


	glInstance.CreateTexture
	("C:\\Users\\pro gamer\\source\\repos\\openglPrac\\openglPrac\\CAPY.jpg", "txt");
	glInstance.CreateTexture
	("C:\\Users\\pro gamer\\source\\repos\\openglPrac\\openglPrac\\texttexture.jpg", "txt1");

	glInstance.CreateVertexBuffer(textureCoords, 2, sizeof(textureCoords));
	glInstance.CreateElementBuffer(indices, sizeof(indices));

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	//Temp
	glEnable(GL_PROGRAM_POINT_SIZE);

	float angle = 0.0f;
	bool ping = false;

	while (!glInstance.ShouldWindowClose())
	{	

		deltaTime = glfwGetTime() - lastFrame;
		lastFrame = glfwGetTime();

		receiveKeys(glInstance);

		/*
		float camX = sin(glfwGetTime()) * 10;
		float camZ = cos(glfwGetTime()) * 10;

		mat4 view = lookAt(camPos, camPos+camFront, camUp);		

		glInstance.UniformMatVec4("view", view, false);
		*/


		
		if (!ping)
		{
			angle += 300 * deltaTime;
		}
		else
		{
			angle -= 300 * deltaTime;
		}

		if (angle >= 30 && !ping)
		{
			ping = true;
		}

		if (angle <= 0 && ping)
		{
			ping = false;
		}
		
		
		mat2 matrix(1);
		matrix[0] = vec2(cos(radians(angle)), sin(radians(angle)));
		matrix[1] = vec2(-sin(radians(angle)), cos(radians(angle)));



		//matrix = rotate(matrix, (float)glfwGetTime(), vec3(1, 1, 1));
		glInstance.UniformMatVec4("transform", matrix, false);


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
		

		glInstance.UniformVecFloat("uniformColour", (sin(glfwGetTime())/2) + 0.5f, (cos(glfwGetTime()) / 2) + 0.5f, ((cos(glfwGetTime()*2) + 1) / 2) + 0.5f, 1);
		
		
		glInstance.Draw(true , 3, GL_TRIANGLES);
		glInstance.SwapBuffers();
		glInstance.PollEvents();	
	}
	return 0;
}



