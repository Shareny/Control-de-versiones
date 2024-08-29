#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>
//Dimensiones de la ventana
const int WIDTH = 800, HEIGHT = 600;
GLuint VAO, VBO, shader;
int currentColorIndex = 0;  // Para rastrear el color actual
float colorChangeInterval = 1.0f; // Intervalo en segundos para cambiar el color
float elapsedTime = 0.0f;  // Tiempo transcurrido desde el último cambio
double lastTime = 0.0;    // Tiempo en el último frame


//Vertex Shader
//recibir color, salida Vcolor
static const char* vShader = "						\n\
#version 330										\n\
layout (location =0) in vec3 pos;					\n\
void main()											\n\
{													\n\
gl_Position=vec4(pos.x,pos.y,pos.z,1.0f); 			\n\
}";
//recibir Vcolor y dar de salida color
static const char* fShader = "						\n\
#version 330										\n\
out vec4 color;										\n\
void main()											\n\
{													\n\
	color = vec4(1.0f,0.0f,0.0f,1.0f);	 			\n\
}";



void CrearTriangulo()
{
	GLfloat vertices[] = {
		-1.0f, -1.0f,0.0f,
		1.0f,-1.0f, 0.0f,
		0.0f,1.0f,0.0f
	};
	glGenVertexArrays(1, &VAO); //generar 1 VAO
	glBindVertexArray(VAO);//asignar VAO

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //pasarle los datos al VBO asignando tamano, los datos y en este caso es estático pues no se modificarán los valores

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GL_FLOAT), (GLvoid*)0);//Stride en caso de haber datos de color por ejemplo, es saltar cierta cantidad de datos
	glEnableVertexAttribArray(0);
	//agregar valores a vèrtices y luego declarar un nuevo vertexAttribPointer
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) //Función para agregar los shaders a la tarjeta gráfica
//the Program recibe los datos de theShader


{
	GLuint theShader = glCreateShader(shaderType);//theShader es un shader que se crea de acuerdo al tipo de shader: vertex o fragment
	const GLchar* theCode[1];
	theCode[0] = shaderCode;//shaderCode es el texto que se le pasa a theCode
	GLint codeLength[1];
	codeLength[0] = strlen(shaderCode);//#include <stdio.h>
#include <string.h>
#include <glew.h>
#include <glfw3.h>

    // Dimensiones de la ventana
    const int WIDTH = 800, HEIGHT = 600;
    GLuint VAO_Cuadrado, VBO_Cuadrado, EBO_Cuadrado;
    GLuint VAO_Rombo, VBO_Rombo, EBO_Rombo;
    GLuint shader;
    int currentColorIndex = 0;  // Para rastrear el color actual
    float colorChangeInterval = 1.0f; // Intervalo en segundos para cambiar el color
    float elapsedTime = 0.0f;  // Tiempo transcurrido desde el último cambio
    double lastTime = 0.0;    // Tiempo en el último frame

    // Datos de vértices e índices para el cuadrado
    GLfloat verticesCuadrado[] = {
        -0.5f,  0.5f, 0.0f,  // Esquina superior izquierda
         0.5f,  0.5f, 0.0f,  // Esquina superior derecha
        -0.5f, -0.5f, 0.0f,  // Esquina inferior izquierda
         0.5f, -0.5f, 0.0f   // Esquina inferior derecha
    };

    GLuint indicesCuadrado[] = {
        0, 1, 2,  // Primer triángulo
        1, 2, 3   // Segundo triángulo
    };

    // Datos de vértices e índices para el rombo
    GLfloat verticesRombo[] = {
        0.0f,  0.5f, 0.0f,  // Parte superior
        0.5f,  0.0f, 0.0f,  // Parte derecha
        0.0f, -0.5f, 0.0f,  // Parte inferior
       -0.5f,  0.0f, 0.0f   // Parte izquierda
    };

    GLuint indicesRombo[] = {
        0, 1, 2,  // Primer triángulo
        0, 2, 3   // Segundo triángulo
    };

    void configurarForma(GLfloat * vertices, GLuint * indices, GLuint & VAO, GLuint & VBO, GLuint & EBO, size_t tamanoVertices, size_t tamanoIndices) {
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, tamanoVertices, vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, tamanoIndices, indices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
    }

    void AddShader(GLuint theProgram, const char* shaderCode, GLenum shaderType) {
        GLuint theShader = glCreateShader(shaderType);
        const GLchar* theCode[1];
        theCode[0] = shaderCode;
        GLint codeLength[1];
        codeLength[0] = strlen(shaderCode);
        glShaderSource(theShader, 1, theCode, codeLength);
        glCompileShader(theShader);
        GLint result = 0;
        GLchar eLog[1024] = { 0 };
        glGetShaderiv(theShader, GL_COMPILE_STATUS, &result);
        if (!result) {
            glGetShaderInfoLog(theShader, sizeof(eLog), NULL, eLog);
            printf("Error al compilar el shader %d: %s\n", shaderType, eLog);
            return;
        }
        glAttachShader(theProgram, theShader);
    }

    void CompileShaders() {
        shader = glCreateProgram();
        if (!shader) {
            printf("Error creando el shader\n");
            return;
        }
        AddShader(shader, vShader, GL_VERTEX_SHADER);
        AddShader(shader, fShader, GL_FRAGMENT_SHADER);
        GLint result = 0;
        GLchar eLog[1024] = { 0 };
        glLinkProgram(shader);
        glGetProgramiv(shader, GL_LINK_STATUS, &result);
        if (!result) {
            glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
            printf("Error al linkear el shader: %s\n", eLog);
            return;
        }
        glValidateProgram(shader);
        glGetProgramiv(shader, GL_VALIDATE_STATUS, &result);
        if (!result) {
            glGetProgramInfoLog(shader, sizeof(eLog), NULL, eLog);
            printf("Error al validar el shader: %s\n", eLog);
            return;
        }
    }

    void setUniform3f(GLuint program, const char* name, float v0, float v1, float v2) {
        GLint loc = glGetUniformLocation(program, name);
        if (loc != -1) {
            glUniform3f(loc, v0, v1, v2);
        }
        else {
            printf("Error: uniform '%s' no encontrado\n", name);
        }
    }

    int main() {
        // Inicialización de GLFW
        if (!glfwInit()) {
            printf("Error al inicializar GLFW\n");
            glfwTerminate();
            return 1;
        }

        // Configuración de GLFW
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        // Crear ventana
        GLFWwindow* mainWindow = glfwCreateWindow(WIDTH, HEIGHT, "Ventana OpenGL", NULL, NULL);
        if (!mainWindow) {
            printf("Error al crear la ventana con GLFW\n");
            glfwTerminate();
            return 1;
        }

        // Obtener tamaño de Buffer
        int BufferWidth, BufferHeight;
        glfwGetFramebufferSize(mainWindow, &BufferWidth, &BufferHeight);

        // Asignar el contexto
        glfwMakeContextCurrent(mainWindow);

        // Permitir nuevas extensiones
        glewExperimental = GL_TRUE;
        if (glewInit() != GLEW_OK) {
            printf("Error al inicializar GLEW\n");
            glfwDestroyWindow(mainWindow);
            glfwTerminate();
            return 1;
        }

        // Configurar viewport
        glViewport(0, 0, BufferWidth, BufferHeight);

        // Configurar cuadrado
        configurarForma(verticesCuadrado, indicesCuadrado, VAO_Cuadrado, VBO_Cuadrado, EBO_Cuadrado, sizeof(verticesCuadrado), sizeof(indicesCuadrado));

        // Configurar rombo
        configurarForma(verticesRombo, indicesRombo, VAO_Rombo, VBO_Rombo, EBO_Rombo, sizeof(verticesRombo), sizeof(indicesRombo));

        // Compilar shaders
        CompileShaders();

        // Bucle principal
        while (!glfwWindowShouldClose(mainWindow)) {
            // Calcular el tiempo transcurrido
            double currentTime = glfwGetTime();
            float deltaTime = static_cast<float>(currentTime - lastTime);
            lastTime = currentTime;

            // Actualizar el tiempo transcurrido
            elapsedTime += deltaTime;

            // Cambiar el color si el intervalo ha pasado
            if (elapsedTime >= colorChangeInterval) {
                elapsedTime = 0.0f;
                currentColorIndex = (currentColorIndex + 1) % 3;
            }

            // Determinar el color de fondo
            float r = 0.0f, g = 0.0f, b = 0.0f;
            switch (currentColorIndex) {
            case 0: r = 1.0f; break; // Rojo
            case 1: g = 1.0f; break; // Verde
            case 2: b = 1.0f; break; // Azul
            }

            // Limpiar la ventana
            glClearColor(r, g, b, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Usar el programa de shaders
            glUseProgram(shader);

            // Configurar y enviar el color del cuadrado
            setUniform3f(shader, "shapeColor", 1.0f, 0.0f, 0.0f); // Rojo para el cuadrado
            glBindVertexArray(VAO_Cuadrado);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // Configurar y enviar el color del rombo
            setUniform3f(shader, "shapeColor", 0.0f, 1.0f, 0.0f); // Verde para el rombo
            glBindVertexArray(VAO_Rombo);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

            // Desvincular VAO
            glBindVertexArray(0);

            // Intercambiar buffers
            glfwSwapBuffers(mainWindow);

            // Procesar eventos
            glfwPollEvents();
        }

        // Limpiar recursos
        glDeleteVertexArrays(1, &VAO_Cuadrado);
        glDeleteBuffers(1, &VBO_Cuadrado);
        glDeleteBuffers(1, &EBO_Cuadrado);

        glDeleteVertexArrays(1, &VAO_Rombo);
        glDeleteBuffers(1, &VBO_Rombo);
        glDeleteBuffers(1, &EBO_Rombo);

        glfwDestroyWindow(mainWindow);
        glfwTerminate();

        return 0;
    }
