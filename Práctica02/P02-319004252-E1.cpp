// Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
// Incluyendo las librer�as de GLM para manejar matrices y transformaciones geom�tricas
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
// Incluyendo las clases personalizadas para manejar la creaci�n de meshes, shaders y la ventana
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"

// Definiendo constantes para la ventana y la conversi�n de grados a radianes
const float toRadians = 3.14159265f / 180.0; // Grados a radianes
Window mainWindow; // Objeto de la clase Window para manejar la ventana principal
std::vector<Mesh*> meshList; // Lista de punteros a objetos Mesh
std::vector<MeshColor*> meshColorList; // Lista de punteros a objetos MeshColor
std::vector<Shader> shaderList; // Lista de objetos Shader

// Definiendo los archivos de los shaders de v�rtices y fragmentos
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

float angulo = 0.0f; // Variable para almacenar el �ngulo de rotaci�n

// Definici�n de color caf� en RGB (valores de ejemplo): 0.478, 0.255, 0.067

// Funci�n para crear una pir�mide triangular regular
void CreaPiramide()
{
    // Aqu� se define la creaci�n de una pir�mide con v�rtices e �ndices
}

// Funci�n para crear los v�rtices de un cubo
void CrearCubo()
{
    // Aqu� se define la creaci�n de un cubo con v�rtices e �ndices
}

// Funci�n para crear letras y figuras utilizando colores
void CrearLetrasyFiguras()
{
    // Array que define los v�rtices y colores para dibujar las letras y figuras
    GLfloat vertices_letras[] = {
        // Letra S en color rosa (RGB: 1.0, 0.75, 0.8)
        // Tri�ngulo 1
        -0.75f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.25f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.75f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 2
        -0.25f,  0.5f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.25f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // V�rtice inferior derecho
        -0.75f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 3
        -0.75f,  0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.5f,  0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.75f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 4
        -0.5f,  0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.5f,  0.0f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice inferior derecho
        -0.75f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 5
        -0.75f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.25f,  0.0f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.75f, -0.25f, 0.0f, 1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 6
        -0.75f, -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.25f,  0.0f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.25f, -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 7 
        -0.25f, -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.5f,  -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 8 
        -0.5f,  -0.25f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.5f,  -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice inferior derecho
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 9
        -0.75f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.75f, -0.75f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Tri�ngulo 10
        -0.25f, -0.75f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice superior izquierdo
        -0.25f, -0.5f, 0.0f,   1.0f, 0.75f, 0.8f,  // V�rtice superior derecho
        -0.75f, -0.75f, 0.0f,  1.0f, 0.75f, 0.8f,  // V�rtice inferior izquierdo

        // Letra C en color morado (RGB: 0.5, 0.0, 0.5)
        // Tri�ngulo 1: 
        -0.25f,  0.75f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice superior izquierdo 
        0.25f,   0.75f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice superior derecho 
        -0.25f,  0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice inferior izquierdo

        // Tri�ngulo 2: 
        0.25f,   0.75f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice superior derecho 
        0.25f,   0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice inferior derecho
        -0.25f,  0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice inferior izquierdo

        // Tri�ngulo 3: 
        -0.25f,  0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice superior izquierdo
        0.0f,    0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice superior derecho
        -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice inferior izquierdo

        // Tri�ngulo 4: 
        0.0f,    0.5f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice superior derecho
        0.0f,    0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice inferior derecho
        -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice inferior izquierdo

        // Tri�ngulo 5: 
        -0.25f,  0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice superior izquierdo
        0.25f,   0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice superior derecho
        -0.25f,  0.0f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice inferior izquierdo

        // Tri�ngulo 6:  
        -0.25f,  0.0f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice superior izquierdo
        0.25f,   0.25f, 0.0f,  0.5f, 0.0f, 0.5f,  // V�rtice superior derecho
        0.25f,   0.0f, 0.0f,   0.5f, 0.0f, 0.5f,  // V�rtice inferior derecho

        // Letra L en color amarillo (RGB: 1.0, 1.0, 0.0)
        // Tri�ngulo 1 
        0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice inferior izquierdo
        0.75f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice inferior derecho
        0.25f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // V�rtice superior izquierdo

        // Tri�ngulo 2 
        0.75f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice inferior derecho
        0.75f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // V�rtice superior derecho
        0.25f, -0.5f, 0.0f,   1.0f, 1.0f, 0.0f,  // V�rtice superior izquierdo

        // Tri�ngulo 3 
        0.25f,  0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice superior izquierdo
        0.5f,   0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice superior derecho
        0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice inferior izquierdo

        // Tri�ngulo 4 
        0.5f,   0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice superior derecho
        0.5f,  -0.25f, 0.0f,  1.0f, 1.0f, 0.0f,  // V�rtice inferior derecho
        0.25f, -0.25f, 0.0f,  1.0f, 1.0f, 0.0f   // V�rtice inferior izquierdo
    };

    // Creando el objeto MeshColor con los v�rtices y colores definidos
    MeshColor* letras = new MeshColor();
    letras->CreateMeshColor(vertices_letras, sizeof(vertices_letras) / sizeof(vertices_letras[0]));
    meshColorList.push_back(letras); // A�adiendo el mesh a la lista de MeshColor
}

// Funci�n para crear y compilar los shaders
void CreateShaders()
{
    Shader* shader1 = new Shader(); // Shader para usar �ndices en objetos: cubo y pir�mide
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    Shader* shader2 = new Shader(); // Shader para usar color como parte del VAO en letras
    shader2->CreateFromFiles(vShaderColor, fShaderColor);
    shaderList.push_back(*shader2);
}

// Funci�n principal
int main()
{
    mainWindow = Window(800, 600); // Inicializando la ventana con tama�o 800x600
    mainWindow.Initialise(); // Configurando la ventana

    CreaPiramide(); // Creando la pir�mide, se almacena en meshList en el �ndice 0
    CrearCubo(); // Creando el cubo, se almacena en meshList en el �ndice 1
    CrearLetrasyFiguras(); // Creando letras y figuras, se almacena en meshColorList en el �ndice 0
    CreateShaders(); // Creando y compilando los shaders

    GLuint uniformProjection = 0; // Variable para almacenar la ubicaci�n de la matriz de proyecci�n en el shader
    GLuint uniformModel = 0; // Variable para almacenar la ubicaci�n de la matriz de modelo en el shader

    // Creando la matriz de proyecci�n para la vista ortogr�fica (2D)
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    // Loop principal mientras la ventana est� abierta
    while (!mainWindow.getShouldClose())
    {
        glfwPollEvents(); // Procesar eventos de entrada del usuario
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Limpiar la ventana con color negro
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpiar el buffer de color y profundidad

        // Dibujar las letras usando el segundo shader
        shaderList[1].useShader();
        uniformModel = shaderList[1].getModelLocation();
        uniformProjection = shaderList[1].getProjectLocation();

        // Inicializar la matriz de modelo y aplicar la traslaci�n para las letras
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
//Traslaci�n
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -5.0f));
//////////////// ROTACI�N //////////////////
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