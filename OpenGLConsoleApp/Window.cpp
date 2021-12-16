#include "Window.h"

Window::Window()
{
	width = 0;
	height = 0;

	bufferWidth = 0;
	bufferHeight = 0;

	xChange = 0.0f;
	yChange = 0.0f;

	lastX = 0.0f;
	lastY = 0.0f;
	mouseFirstMoved = false;

	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	mainWindow = NULL;
}

Window::Window(GLint windowWidth, GLint WindowHeight)
{
	width = windowWidth;
	height = WindowHeight;

	bufferWidth = 0;
	bufferHeight = 0;

	xChange = 0.0f;
	yChange = 0.0f;

	lastX = 0.0f;
	lastY = 0.0f;
	mouseFirstMoved = false;


	for (size_t i = 0; i < 1024; i++)
	{
		keys[i] = 0;
	}

	mainWindow = NULL;
}

Window::~Window()
{
	glfwDestroyWindow(mainWindow);
	glfwTerminate();
	//delete mainWindow;
}

int Window::Initialise()
{
	// initialize GLFW
	if (!glfwInit())
	{
		std::cout << "GLFW initialization failed!" << "\n";
		glfwTerminate();
		return 1;
	}

	// set GLFW window properties
	// OpenGL version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// core profile = no backwards compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// allow forward compatibility
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	mainWindow = glfwCreateWindow(width, height, "Test Window", NULL, NULL);
	if (!mainWindow)
	{
		std::cout << "GLFW window creation failed!" << "\n";
		glfwTerminate();
		return 1;
	}

	// get buffer size information
	glfwGetFramebufferSize(mainWindow, &bufferWidth, &bufferHeight);

	// set the current context
	glfwMakeContextCurrent(mainWindow);

	// handle key + mouse input
	createCallbacks();
	glfwSetInputMode(mainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// allow modern extension features
	glewExperimental = GL_TRUE;

	if (glewInit() != GLEW_OK)
	{
		std::cout << "GLEW initialization failed!" << "\n";
		glfwDestroyWindow(mainWindow);
		glfwTerminate();
		return 1;
	}

	glEnable(GL_DEPTH_TEST);

	// setup viewport size
	glViewport(0, 0, bufferWidth, bufferHeight);

	glfwSetWindowUserPointer(mainWindow, this);
}

GLfloat Window::getXChange()
{
	GLfloat theChange = xChange;
	xChange = 0.0f;
	return theChange;
}

GLfloat Window::getYChange()
{
	GLfloat theChange = yChange;
	yChange = 0.0f;
	return theChange;
}

void Window::createCallbacks()
{
	glfwSetKeyCallback(mainWindow, handleKeys);
	glfwSetCursorPosCallback(mainWindow, handleMouse);
}

void Window::handleKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
		{
			theWindow->keys[key] = true;
			//std::cout << "Pressed: " << key << "\n";
		}
		else if (action == GLFW_RELEASE)
		{
			theWindow->keys[key] = false;
			//std::cout << "Released: " << key << "\n";
		}
	}
}

void Window::handleMouse(GLFWwindow* window, double xPos, double yPos)
{
	Window* theWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
	
	if (theWindow->mouseFirstMoved)
	{
		theWindow->lastX = xPos;
		theWindow->lastY = yPos;
		theWindow->mouseFirstMoved = false;
	}

	theWindow->xChange = xPos - theWindow->lastX;
	theWindow->yChange = theWindow->lastY - yPos;

	theWindow->lastX = xPos;
	theWindow->lastY = yPos;

	//std::cout << "x: " << theWindow->xChange << " ," << "y: " << theWindow->yChange << "\n";


}
