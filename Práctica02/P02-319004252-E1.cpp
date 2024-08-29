// Práctica 2: índices, mesh, proyecciones, transformaciones geométricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
// Incluyendo las librerías de GLM para manejar matrices y transformaciones geométricas
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
// Incluyendo las clases personalizadas para manejar la creación de meshes, shaders y la ventana
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

// Definiendo constantes para la ventana y la conversión de grados a radianes
const float toRadians = 3.14159265f / 180.0; // Grados a radianes
Window mainWindow; // Objeto de la clase Window para manejar la ventana principal
std::vector<Mesh*> meshList; // Lista de punteros a objetos Mesh
std::vector<MeshColor*> meshColorList; // Lista de punteros a objetos MeshColor
std::vector<Shader> shaderList; // Lista de objetos Shader

// Definiendo los archivos de los shaders de vértices y fragmentos
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

float angulo = 0.0f; // Variable para almacenar el ángulo de rotación

// Definición de color café en RGB (valores de ejemplo): 0.478, 0.255, 0.067

// Función para crear una pirámide triangular regular
void CreaPiramide()
{
    // Aquí se define la creación de una pirámide con vértices e índices
}

// Función para crear los vértices de un cubo
void CrearCubo()
{
    // Aquí se define la creación de un cubo con vértices e índices
}

// Función para crear letras y figuras utilizando colores
void CrearLetrasyFiguras()
{
    // Array que define los vértices y colores para dibujar las letras y figuras
    GLfloat vertices_letras[] = {
        // Letra S en color rosa (RGB: 1.0, 0.75, 0.8)
        // Triángulo 1
        -0.75f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.25f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.75f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 2
        -0.25f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.25f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // Vértice inferior derecho
        -0.75f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 3
        -0.75f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.5f,  0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.75f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 4
        -0.5f,  0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.5f,  0.0f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice inferior derecho
        -0.75f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 5
        -0.75f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.25f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.75f, -0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 6
        -0.75f, -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.25f,  0.0f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.25f, -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 7 
        -0.25f, -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.5f,  -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 8 
        -0.5f,  -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.5f,  -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice inferior derecho
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 9
        -0.75f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.75f, -0.75f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Triángulo 10
        -0.25f, -0.75f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice superior izquierdo
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // Vértice superior derecho
        -0.75f, -0.75f, 0.0f,  1.0f, 0.75f, 0.8f,  // Vértice inferior izquierdo

        // Letra C en color morado (RGB: 0.5, 0.0, 0.5)
        // Triángulo 1: 
        -0.25f,  0.75f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice superior izquierdo 
        0.25f,   0.75f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice superior derecho 
        -0.25f,  0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice inferior izquierdo

        // Triángulo 2: 
        0.25f,   0.75f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice superior derecho 
        0.25f,   0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice inferior derecho
        -0.25f,  0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice inferior izquierdo

        // Triángulo 3: 
        -0.25f,  0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice superior izquierdo
        0.0f,    0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice superior derecho
        -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice inferior izquierdo

        // Triángulo 4: 
        0.0f,    0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice superior derecho
        0.0f,    0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice inferior derecho
        -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice inferior izquierdo

        // Triángulo 5: 
        -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice superior izquierdo
        0.25f,   0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice superior derecho
        -0.25f,  0.0f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice inferior izquierdo

        // Triángulo 6:  
        -0.25f,  0.0f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice superior izquierdo
        0.25f,   0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // Vértice superior derecho
        0.25f,   0.0f, 0.0f,   0.5f, 0.0f, 0.5f,  // Vértice inferior derecho

        // Letra L en color amarillo (RGB: 1.0, 1.0, 0.0)
        // Triángulo 1 
        0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice inferior izquierdo
        0.75f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice inferior derecho
        0.25f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // Vértice superior izquierdo

        // Triángulo 2 
        0.75f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice inferior derecho
        0.75f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // Vértice superior derecho
        0.25f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // Vértice superior izquierdo

        // Triángulo 3 
        0.25f,  0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice superior izquierdo
        0.5f,   0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice superior derecho
        0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice inferior izquierdo

        // Triángulo 4 
        0.5f,   0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice superior derecho
        0.5f,  -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // Vértice inferior derecho
        0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f   // Vértice inferior izquierdo
    };

    // Creando el objeto MeshColor con los vértices y colores definidos
    MeshColor* letras = new MeshColor();
    letras->CreateMeshColor(vertices_letras, sizeof(vertices_letras) / sizeof(vertices_letras[0]));
    meshColorList.push_back(letras); // Añadiendo el mesh a la lista de MeshColor
}

// Función para crear y compilar los shaders
void CreateShaders()
{
    Shader* shader1 = new Shader(); // Shader para usar índices en objetos: cubo y pirámide
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    Shader* shader2 = new Shader(); // Shader para usar color como parte del VAO en letras
    shader2->CreateFromFiles(vShaderColor, fShaderColor);
    shaderList.push_back(*shader2);
}

// Función principal
int main()
{
    mainWindow = Window(800, 600); // Inicializando la ventana con tamaño 800x600
    mainWindow.Initialise(); // Configurando la ventana

    CreaPiramide(); // Creando la pirámide, se almacena en meshList en el índice 0
    CrearCubo(); // Creando el cubo, se almacena en meshList en el índice 1
    CrearLetrasyFiguras(); // Creando letras y figuras, se almacena en meshColorList en el índice 0
    CreateShaders(); // Creando y compilando los shaders

    GLuint uniformProjection = 0; // Variable para almacenar la ubicación de la matriz de proyección en el shader
    GLuint uniformModel = 0; // Variable para almacenar la ubicación de la matriz de modelo en el shader

    // Creando la matriz de proyección para la vista ortográfica (2D)
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    // Loop principal mientras la ventana esté abierta
    while (!mainWindow.getShouldClose())
    {
        glfwPollEvents(); // Procesar eventos de entrada del usuario
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Limpiar la ventana con color negro
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el buffer de color y profundidad

        // Dibujar las letras usando el segundo shader
        shaderList[1].useShader();
        uniformModel = shaderList[1].getModelLocation();
        uniformProjection = shaderList[1].getProjectLocation();

        // Inicializar la matriz de modelo y aplicar la traslación para las letras
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, -4.0f));

        // Enviar las matrices al shader y dibujar los meshes de colores
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshColorList[0]->RenderMeshColor();

        glUseProgram(0); // Desactivar el shader actual
        mainWindow.swapBuffers(); // Intercambiar los buffers de la ventana
    }
    return 0;
}

// inicializar matriz: glm::mat4 model(1.0);
// reestablecer matriz: model = glm::mat4(1.0);
//Traslación
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACIÓN //////////////////
//model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 1.0f, 0.0f));
////////////////  ESCALA ////////////////
//model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
///////////////////// T+R////////////////
/*model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::rotate(model, glm::radians(angulo), glm::vec3(0.0f, 1.0f, 0.0f));
*/
/////////////R+T//////////
/*model = glm::rotate(model, 45 * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
model = glm::translate(model, glm::vec3(valor, 0.0f, 0.0f));
*/