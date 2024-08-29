#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
#include <stdlib.h>
#include <time.h>

// Dimensiones de la ventana
const int WIDTH = 1500, HEIGHT = 1000;
GLuint VAO, VBO, shaderProgram;

// Vertex Shader 
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
void main() {
    gl_Position = vec4(aPos, 1.0);
}
)";

// Fragment Shader 
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
uniform vec4 bgColor;
void main() {
    FragColor = bgColor;
}
)";

// Funciones para crear los triángulos
void createTriangle() {
    GLfloat vertices[] = {
        // S
        // Triángulo 1
       // Triángulo 1
        -2.75f,  0.5f, 0.0f,  // Vértice superior izquierdo
        -2.25f,  0.5f, 0.0f,  // Vértice superior derecho
        -2.75f,  0.25f, 0.0f, // Vértice inferior izquierdo

        // Triángulo 2
        -2.25f,  0.5f, 0.0f,  // Vértice superior derecho
        -2.25f,  0.25f, 0.0f, // Vértice inferior derecho
        -2.75f,  0.25f, 0.0f, // Vértice inferior izquierdo

        // Triángulo 3
        -2.75f,  0.25f, 0.0f, // Vértice superior izquierdo
        -2.5f,   0.25f, 0.0f,  // Vértice superior derecho
        -2.75f,  0.0f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 4
        -2.5f,   0.25f, 0.0f,  // Vértice superior derecho
        -2.5f,   0.0f, 0.0f,   // Vértice inferior derecho
        -2.75f,  0.0f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 5
        -2.75f,  0.0f, 0.0f,  // Vértice superior izquierdo
        -2.25f,  0.0f, 0.0f,  // Vértice superior derecho
        -2.75f, -0.25f, 0.0f, // Vértice inferior izquierdo

        // Triángulo 6
        -2.75f, -0.25f, 0.0f,  // Vértice superior izquierdo
        -2.25f,  0.0f, 0.0f,   // Vértice superior derecho
        -2.25f, -0.25f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 7 
        -2.25f, -0.25f, 0.0f,  // Vértice superior izquierdo
        -2.5f,  -0.25f, 0.0f,  // Vértice superior derecho
        -2.25f, -0.5f, 0.0f,   // Vértice inferior izquierdo

        // Triángulo 8 
        -2.5f,  -0.25f, 0.0f,  // Vértice superior derecho
        -2.5f,  -0.5f, 0.0f,   // Vértice inferior derecho
        -2.25f, -0.5f, 0.0f,   // Vértice inferior izquierdo

        // Triángulo 9
        -2.75f, -0.5f, 0.0f,   // Vértice superior izquierdo
        -2.25f, -0.5f, 0.0f,   // Vértice superior derecho
        -2.75f, -0.75f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 10
        -2.25f, -0.75f, 0.0f,  // Vértice superior izquierdo
        -2.25f, -0.5f, 0.0f,   // Vértice superior derecho
        -2.75f, -0.75f, 0.0f,  // Vértice inferior izquierdo

        // C
        // Triángulo 1: 
        -0.25f,  0.75f, 0.0f,  // Vértice superior izquierdo 
        0.25f,   0.75f, 0.0f,  // Vértice superior derecho 
        -0.25f,  0.5f, 0.0f,   // Vértice inferior izquierdo
        // Triángulo 2: 
        0.25f,   0.75f, 0.0f,  // Vértice superior derecho 
        0.25f,   0.5f, 0.0f,   // Vértice inferior derecho
        -0.25f,  0.5f, 0.0f,   // Vértice inferior izquierdo

        // Triángulo 3: 
        -0.25f,  0.5f, 0.0f,   // Vértice superior izquierdo
        0.0f,    0.5f, 0.0f,   // Vértice superior derecho
        -0.25f,  0.25f, 0.0f, // Vértice inferior izquierdo

        // Triángulo 4: 
        0.0f,    0.5f, 0.0f,   // Vértice superior derecho
        0.0f,    0.25f, 0.0f, // Vértice inferior derecho
        -0.25f,  0.25f, 0.0f, // Vértice inferior izquierdo

        // Triángulo 5: 
        -0.25f,  0.25f, 0.0f, // Vértice superior izquierdo
        0.25f,   0.25f, 0.0f, // Vértice superior derecho
        -0.25f,  0.0f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 6:  
        -0.25f,  0.0f, 0.0f,  // Vértice superior izquierdo
        0.25f,   0.25f, 0.0f, // Vértice superior derecho
        0.25f,   0.0f, 0.0f,   // Vértice inferior derecho

        // L
        // Triángulo 1 
        2.25f, -0.25f, 0.0f,  // Vértice inferior izquierdo
        2.75f, -0.25f, 0.0f,  // Vértice inferior derecho
        2.25f, -0.5f, 0.0f,   // Vértice superior izquierdo

        // Triángulo 2 
        2.75f, -0.25f, 0.0f,  // Vértice inferior derecho
        2.75f, -0.5f, 0.0f,   // Vértice superior derecho
        2.25f, -0.5f, 0.0f,   // Vértice superior izquierdo

        // Triángulo 3 
        2.25f,  0.25f, 0.0f,  // Vértice superior izquierdo
        2.5f,   0.25f, 0.0f,  // Vértice superior derecho
        2.25f, -0.25f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 4 
        2.5f,   0.25f, 0.0f,  // Vértice superior derecho
        2.5f,  -0.25f, 0.0f,  // Vértice inferior derecho
        2.25f, -0.25f, 0.0f   // Vértice inferior izquierdo
    };

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glBindVertexArray(0);
}

// Funciones para compilar shaders
GLuint compileShader(const char* shaderSource, GLenum shaderType) {
    GLuint shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, NULL);
    glCompileShader(shader);

    GLint success;
    GLchar infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        printf("Error compiling shader: %s\n", infoLog);
    }
    return shader;
}

//
void createShaderProgram() {
    GLuint vertexShader = compileShader(vertexShaderSource, GL_VERTEX_SHADER);
    GLuint fragmentShader = compileShader(fragmentShaderSource, GL_FRAGMENT_SHADER);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);

    GLint success;
    GLchar infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("Error linking program: %s\n", infoLog);
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

int main() {
    // Initialize GLFW
    if (!glfwInit()) {
        printf("Failed to initialize GLFW\n");
        return -1;
    }

    // Configura GLFW
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Random Background Color", NULL, NULL);
    if (!window) {
        printf("Failed to create GLFW window\n");
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    // Inicializa GLEW
    if (glewInit() != GLEW_OK) {
        printf("Failed to initialize GLEW\n");
        return -1;
    }

    glViewport(0, 0, WIDTH, HEIGHT);

    // Crear triangulos
    createTriangle();
    createShaderProgram();

    srand((unsigned int)time(NULL));

    // Variables de color
    float lastTime = (float)glfwGetTime();
    float r = (float)rand() / (float)RAND_MAX;
    float g = (float)rand() / (float)RAND_MAX;
    float b = (float)rand() / (float)RAND_MAX;

    // Main loop
    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        if (currentTime - lastTime >= 2.0f) {
            // Update background color every 2 seconds
            r = (float)rand() / (float)RAND_MAX;
            g = (float)rand() / (float)RAND_MAX;
            b = (float)rand() / (float)RAND_MAX;
            lastTime = currentTime;
        }

        glUseProgram(shaderProgram);
        GLint bgColorLocation = glGetUniformLocation(shaderProgram, "bgColor");
        glUniform4f(bgColorLocation, r, g, b, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 100);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
