/* Sample code for drawing box and ball.  
   Much of the basics taken directly from learnopengl.com */

/* Need to install glad, GLFW, and glm first */
/* See learnopengl.com for setting up GLFW and glad */
/* You can just copy the headers from glm, or go through the install */

#include<iostream>

/**
 * OpenGL is only really a standard/specification it is up to the driver manufacturer to implement the specification to a 
 * driver that the specific graphics card supports. Since there are many different versions of OpenGL drivers, the location 
 * of most of its functions is not known at compile-time and needs to be queried at run-time. It is then the task of 
 * the developer to retrieve the location of the functions he/she needs and store them in function pointers for later use. 
 * Retrieving those locations is OS-specific.
 */

#include<glad/glad.h>   //include GLAD before GLFW
#include<GLFW/glfw3.h>  // creating window and rendering 

#include<glm/glm.hpp>
#include<glm/gtc/matrix_transform.hpp>
#include<glm/gtc/type_ptr.hpp>
using namespace std;

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// Hardcoded shaders so we don't need extra files
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"layout (location = 1) in vec3 aColor;\n"
"uniform mat4 model;\n"
"uniform mat4 view;\n"
"uniform mat4 projection;\n"
"out vec3 ourColor;\n"
"void main()\n"
"{\n"
"   gl_Position = projection * view * model * vec4(aPos, 1.0);\n"
"   ourColor = aColor;\n"
"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"in vec3 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(ourColor, 1.0f);\n"
"}\n\0";

// View parameters
float theta = 0.0;
float phi = 0.0;
float camradius = 5.0;
float cameraspeed = 0.02;

float camX = camradius;
float camY = 0.0;
float camZ = 0.0;

// Allow window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
}

// Keyboard input: JKIL for camera motion (also escape to close window)
void processInput(GLFWwindow* window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
    // J key will rotate left
    if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) {
        theta -= cameraspeed;
        if (theta < 0.0) theta += 360.0;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // L key will rotate right
    if (glfwGetKey(window, GLFW_KEY_L) == GLFW_PRESS) {
        theta += cameraspeed;
        if (theta >= 360.0) theta -= 360.0;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // I key will rotate right
    if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) {
        if (phi < 90.0-cameraspeed) phi += cameraspeed;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
    // K key will rotate right
    if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) {
        if (phi > -90.0+cameraspeed) phi -= cameraspeed;
        camX = camradius * cos(glm::radians(phi)) * cos(glm::radians(theta));
        camY = camradius * cos(glm::radians(phi)) * sin(glm::radians(theta));
        camZ = camradius * sin(glm::radians(phi));
    }
}

// Box with different colors for each face
float box[] = {
    // positions         // colors
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f, // bottom
     1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  0.0f, 0.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top
     1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 1.0f, // left
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 1.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f, // right
    -1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  0.0f, 1.0f, 0.0f,
    -1.0f,  1.0f,  1.0f,  1.0f, 0.0f, 0.0f, // back
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f,  1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f, -1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
    -1.0f,  1.0f, -1.0f,  1.0f, 0.0f, 0.0f,
     1.0f, -1.0f,  1.0f,  1.0f, 1.0f, 0.0f, // front
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f,  1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f, -1.0f, -1.0f,  1.0f, 1.0f, 0.0f,
     1.0f,  1.0f,  1.0f,  1.0f, 1.0f, 0.0f
};

// This is a really bad "ball" - just an octahedron
float br = 0.05; // ball radius
float ball[] = {
    // positions         // colors
     br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 1
      0, br,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
      0, br,  0,   1.0f, 1.0f, 1.0f, // triangle 2
    -br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
    -br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 3
      0,-br,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
      0,-br,  0,   1.0f, 1.0f, 1.0f, // triangle 4
     br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0, br,   1.0f, 1.0f, 1.0f,
     br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 5
      0,-br,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
      0,-br,  0,   1.0f, 1.0f, 1.0f, // triangle 6
    -br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
    -br,  0,  0,   1.0f, 1.0f, 1.0f, // triangle 7
      0, br,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
      0, br,  0,   1.0f, 1.0f, 1.0f, // triangle 8
     br,  0,  0,   1.0f, 1.0f, 1.0f,
      0,  0,-br,   1.0f, 1.0f, 1.0f,
};

int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Physically Based Demo", NULL, NULL);
    if (window == NULL) {
        cout << "Failed to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        cout << "Failed to initialize GLAD" << endl;
        return -1;
    }

    glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Enable depth buffering, backface culling
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    glUseProgram(shaderProgram);

    // Set up vertex array object (VAO) and vertex buffers for box and ball
    unsigned int boxbuffer, ballbuffer, VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);
    glGenBuffers(1, &boxbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, boxbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(box), box, GL_STATIC_DRAW);
    glGenBuffers(1, &ballbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, ballbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ball), ball, GL_STATIC_DRAW);

    // Declare model/view/projection matrices
    glm::mat4 model = glm::mat4(1.0f);
    unsigned int modelLoc = glGetUniformLocation(shaderProgram, "model");
    glm::mat4 view = glm::mat4(1.0f);
    unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
    glm::mat4 projection = glm::mat4(1.0f);
    unsigned int projectionLoc = glGetUniformLocation(shaderProgram, "projection");

    // Set Projection matrix
    projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection));

    /* HERE IS INITIAL BALL POSITION, SET AT 0,0,0 FOR DEMO */
    float ballposition[] = {0.0, 0.0, 0.0};

    // Rendering loop0
	while (!glfwWindowShouldClose(window)) {
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Set view matrix
        view = glm::lookAt(glm::vec3(camX, camY, camZ), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 0.0, 1.0));
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
 
        // render the box
        glBindBuffer(GL_ARRAY_BUFFER, boxbuffer);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // draw the box (no model transform needed)
        model = glm::mat4(1.0f);
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 36);

        // render the ball
        glBindBuffer(GL_ARRAY_BUFFER, ballbuffer);
        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // Translate ball to its position and draw
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(ballposition[0], ballposition[1], ballposition[2]));
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
        glDrawArrays(GL_TRIANGLES, 0, 24);

		glfwSwapBuffers(window);
		glfwPollEvents();

        /* HERE YOU CAN ADD YOUR CODE TO COMPUTE THE NEXT SIMULATION UP TO
           THE NEXT DISPLAY FRAME (PROBABLY WANT A FUNCTION CALL) */
        // You want to update ballposition, giving the position of the ball
        // For now, we will have a ball that falls by .0002 in z per frame
        ballposition[2] -= 0.0002;

	}

    // optional: de-allocate all resources once they've outlived their purpose:
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &boxbuffer);
    glDeleteBuffers(1, &ballbuffer);
    glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}