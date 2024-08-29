// Pr�ctica 2: Uso de �ndices, generaci�n de mallas, proyecciones y transformaciones geom�tricas

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <glew.h>
#include <glfw3.h>

// Librer�as de GLM para trabajar con matrices y transformaciones geom�tricas
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

// Clases que encapsulan funcionalidad para manejar mallas, shaders y ventanas
#include "Mesh.h"
#include "Shader.h"
#include "Window.h"

// Constante para convertir grados a radianes
const float toRadians = 3.14159265f / 180.0;

// Instancia de la ventana principal
Window mainWindow;

// Listas para almacenar mallas y shaders
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader> shaderList;

// Declaraci�n de rutas para los archivos de shaders
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";

// Nuevos shaders para colores espec�ficos
static const char* fShaderRojo = "shaders/rojo.frag";
static const char* fShaderVerdeObs = "shaders/verdeObs.frag";
static const char* fShaderAzul = "shaders/azul.frag";
static const char* fShaderCafe = "shaders/cafe.frag";
static const char* fShaderVerde = "shaders/verde.frag";

// Variable para controlar la rotaci�n
float angulo = 0.0f;

// Funci�n para crear una pir�mide triangular regular
void CreaPiramide()
{
    unsigned int indices[] = {
        0, 1, 2,
        1, 3, 2,
        3, 0, 2,
        1, 0, 3
    };

    GLfloat vertices[] = {
        -0.5f, -0.5f, 0.0f,  // V�rtice 0
        0.5f, -0.5f, 0.0f,   // V�rtice 1
        0.0f, 0.5f, -0.25f,  // V�rtice 2
        0.0f, -0.5f, -0.5f,  // V�rtice 3
    };

    // Crear la malla para la pir�mide y a�adirla a la lista de mallas
    Mesh* obj1 = new Mesh();
    obj1->CreateMesh(vertices, indices, 12, 12);
    meshList.push_back(obj1);
}

// Funci�n para crear un cubo
void CrearCubo()
{
    unsigned int cubo_indices[] = {
        // Caras del cubo
        0, 1, 2,  2, 3, 0,  // Cara frontal
        1, 5, 6,  6, 2, 1,  // Cara derecha
        7, 6, 5,  5, 4, 7,  // Cara trasera
        4, 0, 3,  3, 7, 4,  // Cara izquierda
        4, 5, 1,  1, 0, 4,  // Cara inferior
        3, 2, 6,  6, 7, 3   // Cara superior
    };

    GLfloat cubo_vertices[] = {
        // V�rtices del cubo (front y back)
        -0.5f, -0.5f,  0.5f,   0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,  -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,   0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,  -0.5f,  0.5f, -0.5f
    };

    // Crear la malla para el cubo y a�adirla a la lista de mallas
    Mesh* cubo = new Mesh();
    cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
    meshList.push_back(cubo);
}

// Funci�n para crear figuras y letras en colores espec�ficos
void CrearLetrasyFiguras()
{
    GLfloat vertices_triangulorojo[] = {
        // Coordenadas y color para un tri�ngulo rojo
        //X			Y			Z			R		G		B
        -1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
        1.0f,	-1.0f,		0.5f,			1.0f,	0.0f,	0.0f,
        0.0f,	1.0f,		0.5f,			1.0f,	0.0f,	0.0f,

    };

    MeshColor* triangulorojo = new MeshColor();
    triangulorojo->CreateMeshColor(vertices_triangulorojo, 18);
    meshColorList.push_back(triangulorojo);

    GLfloat vertices_cuadradoverde[] = {
        // Coordenadas y color para un cuadrado verde
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
         0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
        -0.5f,  0.5f, 0.5f,   0.0f, 1.0f, 0.0f,
    };

    MeshColor* cuadradoverde = new MeshColor();
    cuadradoverde->CreateMeshColor(vertices_cuadradoverde, 36);
    meshColorList.push_back(cuadradoverde);
}

// Funci�n para crear y compilar shaders a partir de archivos
void CreateShaders()
{
    // Shader est�ndar para mallas usando �ndices
    Shader* shader1 = new Shader();
    shader1->CreateFromFiles(vShader, fShader);
    shaderList.push_back(*shader1);

    // Shader que incluye color en los v�rtices
    Shader* shader2 = new Shader();
    shader2->CreateFromFiles(vShaderColor, fShaderColor);
    shaderList.push_back(*shader2);

    // Shaders espec�ficos para diferentes colores
    Shader* shaderRojo = new Shader();
    shaderRojo->CreateFromFiles("shaders/shader.vert", "shaders/rojo.frag");
    shaderList.push_back(*shaderRojo);

    Shader* shaderVerdeObs = new Shader();
    shaderVerdeObs->CreateFromFiles("shaders/shader.vert", "shaders/verdeObs.frag");
    shaderList.push_back(*shaderVerdeObs);

    Shader* shaderAzul = new Shader();
    shaderAzul->CreateFromFiles("shaders/shader.vert", "shaders/azul.frag");
    shaderList.push_back(*shaderAzul);

    Shader* shaderCafe = new Shader();
    shaderCafe->CreateFromFiles("shaders/shader.vert", "shaders/cafe.frag");
    shaderList.push_back(*shaderCafe);

    Shader* shaderVerde = new Shader();
    shaderVerde->CreateFromFiles("shaders/shader.vert", "shaders/verde.frag");
    shaderList.push_back(*shaderVerde);
}


int main()
{
    // Crear una ventana de 800x600 p�xeles e inicializarla
    mainWindow = Window(800, 600);
    mainWindow.Initialise();

    // Crear las mallas necesarias: una pir�mide y un cubo
    CreaPiramide(); // Se almacena en el �ndice 0 de meshList
    CrearCubo();    // Se almacena en el �ndice 1 de meshList
    CrearLetrasyFiguras(); // Se a�aden a meshColorList

    // Crear y compilar los shaders para aplicar color y efectos
    CreateShaders();

    // Variables para almacenar ubicaciones de uniformes en los shaders
    GLuint uniformProjection = 0;
    GLuint uniformModel = 0;

    // Matriz de proyecci�n ortogonal para ver en 2D
    glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);

    // Inicializar la matriz de modelo con la identidad (sin transformaciones)
    glm::mat4 model(1.0);

    // Bucle principal que sigue ejecut�ndose mientras la ventana est� abierta
    while (!mainWindow.getShouldClose())
    {
        // Procesar eventos de entrada del usuario (teclado, rat�n, etc.)
        glfwPollEvents();

        // Limpiar la ventana con un color de fondo blanco
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Configuraci�n y renderizado del cubo que forma la casa (con shader rojo)
        shaderList[2].useShader(); // Usar el shader rojo
        uniformModel = shaderList[0].getModelLocation(); // Obtener ubicaci�n del uniforme 'model' del shader
        uniformProjection = shaderList[0].getProjectLocation(); // Obtener ubicaci�n del uniforme 'projection' del shader

        // Aplicar transformaciones al cubo: escalado y traslaci�n
        model = glm::mat4(1.0f); // Inicializar la matriz de modelo
        model = glm::scale(model, glm::vec3(0.8f, 0.9f, 0.9f)); // Escalar el cubo
        model = glm::translate(model, glm::vec3(0.0f, -0.6f, -4.0f)); // Trasladar el cubo en el espacio
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model)); // Enviar la matriz de modelo al shader
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection)); // Enviar la matriz de proyecci�n al shader
        meshList[1]->RenderMesh();  // Renderizar el cubo (�ndice 1 en meshList)

        // Configuraci�n y renderizado de la pir�mide que forma el techo (con shader azul)
        shaderList[4].useShader(); // Usar el shader azul
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();

        // Aplicar transformaciones a la pir�mide: escalado y traslaci�n
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.9f, 0.7f, 0.9f)); // Escalar la pir�mide
        model = glm::translate(model, glm::vec3(0.0f, 0.37f, -4.0f)); // Trasladar la pir�mide
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();  // Renderizar la pir�mide (�ndice 0 en meshList)

        // Configuraci�n y renderizado de ventanas y puertas (con shader verde claro)
        shaderList[6].useShader(); // Usar el shader verde claro
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();

        // Ventana derecha
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.25f, 0.3, 0.3f)); // Escalar la ventana
        model = glm::translate(model, glm::vec3(0.7f, -1.1f, -4.0f)); // Posicionar la ventana derecha
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();  // Renderizar el cubo que representa la ventana (�ndice 1 en meshList)

        // Ventana izquierda
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.25f, 0.3, 0.3f)); // Escalar la ventana
        model = glm::translate(model, glm::vec3(-0.7f, -1.1f, -4.0f)); // Posicionar la ventana izquierda
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // Puerta centrada
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.25f, 0.3, 0.3f)); // Escalar la puerta
        model = glm::translate(model, glm::vec3(0.0f, -2.8f, -4.0f)); // Posicionar la puerta en el centro
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // Configuraci�n y renderizado de los �rboles (tronco y hojas con shaders correspondientes)
        // �rbol derecho - tronco
        shaderList[5].useShader(); // Usar el shader caf� para el tronco
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.15f, 0.2, 0.2f)); // Escalar el tronco
        model = glm::translate(model, glm::vec3(4.8f, -4.45f, -4.0f)); // Posicionar el tronco derecho
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // �rbol derecho - hojas
        shaderList[3].useShader(); // Usar el shader verde oscuro para las hojas
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.4f, 0.6, 0.4f)); // Escalar las hojas
        model = glm::translate(model, glm::vec3(1.8f, -.82f, -4.0f)); // Posicionar las hojas sobre el tronco derecho
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        // �rbol izquierdo - tronco
        shaderList[5].useShader(); // Usar el shader caf� para el tronco
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.15f, 0.2, 0.2f)); // Escalar el tronco
        model = glm::translate(model, glm::vec3(-4.8f, -4.45f, -4.0f)); // Posicionar el tronco izquierdo
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[1]->RenderMesh();

        // �rbol izquierdo - hojas
        shaderList[3].useShader(); // Usar el shader verde oscuro para las hojas
        uniformModel = shaderList[0].getModelLocation();
        uniformProjection = shaderList[0].getProjectLocation();
        model = glm::mat4(1.0f);
        model = glm::scale(model, glm::vec3(0.4f, 0.6, 0.4f)); // Escalar las hojas
        model = glm::translate(model, glm::vec3(-1.8f, -.82f, -4.0f)); // Posicionar las hojas sobre el tronco izquierdo
        glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
        meshList[0]->RenderMesh();

        // Desactivar el uso del programa de shaders
        glUseProgram(0);

        // Intercambiar los buffers para mostrar el siguiente frame
        mainWindow.swapBuffers();
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