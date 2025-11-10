/*
Animación:
Sesión 1:
Simple o básica:Por banderas y condicionales (más de 1 transformación geométrica se ve modificada
Compleja: Por medio de funciones y algoritmos.
Textura Animada
*/
//para cargar imagen
#define STB_IMAGE_IMPLEMENTATION

#include <stdio.h>
#include <string.h>
#include <cmath>
#include <vector>
#include <math.h>

#include <glew.h>
#include <glfw3.h>

#include <glm.hpp>
#include <gtc\matrix_transform.hpp>
#include <gtc\type_ptr.hpp>
//para probar el importer
//#include<assimp/Importer.hpp>

#include "Window.h"
#include "Mesh.h"
#include "Shader_light.h"
#include "Camera.h"
#include "Texture.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

//para iluminación
#include "CommonValues.h"
#include "DirectionalLight.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "Material.h"
const float toRadians = 3.14159265f / 180.0f;

//variables para animación
float angulovaria = 0.0f;



Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;

Texture Letrero;
Texture Puerta;
Texture dadoTexture;
Texture Arco;

Skybox skybox;

Model Arco_M;
Model Letrero_M;
Model PuertaDere_M;
Model PuertaIzq_M;
Model Dado_M;

//materiales
Material Material_brillante;
Material Material_opaco;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;

// luz direccional
DirectionalLight mainLight;
//para declarar varias luces de tipo pointlight
PointLight pointLights[MAX_POINT_LIGHTS];
SpotLight spotLights[MAX_SPOT_LIGHTS];

// Vertex Shader
static const char* vShader = "shaders/shader_light.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_light.frag";


//cálculo del promedio de las normales para sombreado de Phong
void calcAverageNormals(unsigned int* indices, unsigned int indiceCount, GLfloat* vertices, unsigned int verticeCount,
	unsigned int vLength, unsigned int normalOffset)
{
	for (size_t i = 0; i < indiceCount; i += 3)
	{
		unsigned int in0 = indices[i] * vLength;
		unsigned int in1 = indices[i + 1] * vLength;
		unsigned int in2 = indices[i + 2] * vLength;
		glm::vec3 v1(vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]);
		glm::vec3 v2(vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]);
		glm::vec3 normal = glm::cross(v1, v2);
		normal = glm::normalize(normal);

		in0 += normalOffset; in1 += normalOffset; in2 += normalOffset;
		vertices[in0] += normal.x; vertices[in0 + 1] += normal.y; vertices[in0 + 2] += normal.z;
		vertices[in1] += normal.x; vertices[in1 + 1] += normal.y; vertices[in1 + 2] += normal.z;
		vertices[in2] += normal.x; vertices[in2 + 1] += normal.y; vertices[in2 + 2] += normal.z;
	}

	for (size_t i = 0; i < verticeCount / vLength; i++)
	{
		unsigned int nOffset = i * vLength + normalOffset;
		glm::vec3 vec(vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]);
		vec = glm::normalize(vec);
		vertices[nOffset] = vec.x; vertices[nOffset + 1] = vec.y; vertices[nOffset + 2] = vec.z;
	}
}


void CreateObjects()
{
	unsigned int indices[] = {
		0, 3, 1,
		1, 3, 2,
		2, 3, 0,
		0, 1, 2
	};

	GLfloat vertices[] = {
		//	x      y      z			u	  v			nx	  ny    nz
			-1.0f, -1.0f, -0.6f,	0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, -1.0f, 1.0f,		0.5f, 0.0f,		0.0f, 0.0f, 0.0f,
			1.0f, -1.0f, -0.6f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,		0.5f, 1.0f,		0.0f, 0.0f, 0.0f
	};

	unsigned int floorIndices[] = {
		0, 2, 1,
		1, 2, 3
	};

	GLfloat floorVertices[] = {
		-10.0f, 0.0f, -10.0f,	0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, -10.0f,	10.0f, 0.0f,	0.0f, -1.0f, 0.0f,
		-10.0f, 0.0f, 10.0f,	0.0f, 10.0f,	0.0f, -1.0f, 0.0f,
		10.0f, 0.0f, 10.0f,		10.0f, 10.0f,	0.0f, -1.0f, 0.0f
	};
	unsigned int vegetacionIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	   4,5,6,
	   4,6,7
	};

	GLfloat vegetacionVertices[] = {
		-0.5f, -0.5f, 0.0f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, -0.5f, 0.0f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		-0.5f, 0.5f, 0.0f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,

		0.0f, -0.5f, -0.5f,		0.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, -0.5f, 0.5f,		1.0f, 0.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, 0.5f,		1.0f, 1.0f,		0.0f, 0.0f, 0.0f,
		0.0f, 0.5f, -0.5f,		0.0f, 1.0f,		0.0f, 0.0f, 0.0f,


	};

	unsigned int AdvTimeIndices[] = {
		0, 1, 2,
		0, 2, 3,
	};

	GLfloat AdvTimeVertices[] = {
		//   X      Y      Z     U       V        Nx    Ny    Nz
		-0.5f, 0.0f,  0.5f,   0.1f,   0.98f,   0.0f, -1.0f, 0.0f, // arriba dere  
		 0.5f, 0.0f,  0.5f,   0.01f,     0.98f,   0.0f, -1.0f, 0.0f, // arriba izq
		 0.5f, 0.0f, -0.5f,   0.01f,     0.9f,  0.0f, -1.0f, 0.0f, // abajo izq
		-0.5f, 0.0f, -0.5f,   0.1f,   0.9f,  0.0f, -1.0f, 0.0f  // abajo der
	};

	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);

	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(vegetacionVertices, vegetacionIndices, 64, 12);
	meshList.push_back(obj4);

	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(AdvTimeVertices, AdvTimeIndices, 32, 6);
	meshList.push_back(obj5);
}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
}

void setLetterUV(float* vertices, int col, int row)
{
	float uStep = 1.0f / 9.0f;  // 9 columnas
	float vStep = 1.0f / 3.0f;  // 3 filas
	float u0 = col * uStep;
	float v0 = 1.0f - (row + 1) * vStep;
	float u1 = u0 + uStep;
	float v1 = v0 + vStep;

	// Actualiza las coordenadas UV del plano
	// (cada vértice tiene 8 floats, U,V en posiciones 3 y 4)
	vertices[3] = u0; vertices[4] = v1;  // arriba izq
	vertices[11] = u1; vertices[12] = v1;  // arriba der
	vertices[19] = u1; vertices[20] = v0;  // abajo der
	vertices[27] = u0; vertices[28] = v0;  // abajo izq
}


int main()
{
	mainWindow = Window(1366, 768); // 1280, 1024 or 1024, 768
	mainWindow.Initialise();

	CreateObjects();
	CreateShaders();

	camera = Camera(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.5f, 0.5f);

	brickTexture = Texture("Textures/brick.png");
	brickTexture.LoadTextureA();
	dirtTexture = Texture("Textures/dirt.png");
	dirtTexture.LoadTextureA();
	plainTexture = Texture("Textures/plain.png");
	plainTexture.LoadTextureA();
	pisoTexture = Texture("Textures/piso.tga");
	pisoTexture.LoadTextureA();
	AgaveTexture = Texture("Textures/Agave.tga");
	AgaveTexture.LoadTextureA();
	Puerta = Texture("Textures/made.jpg");
	Puerta.LoadTextureA();
	dadoTexture = Texture("Textures/Dado.png");
	dadoTexture.LoadTextureA();

	Letrero = Texture("Textures/Letrero.png");
	Letrero.LoadTextureA();

	Arco_M = Model();
	Arco_M.LoadModel("Models/arco.obj");
	Letrero_M = Model();
	Letrero_M.LoadModel("Models/Letrero.fbx");
	PuertaDere_M = Model();
	PuertaDere_M.LoadModel("Models/PuertaDere.obj");
	PuertaIzq_M = Model();
	PuertaIzq_M.LoadModel("Models/PuertaIzq.obj");
	Dado_M = Model();
	Dado_M.LoadModel("Models/Dado.fbx");

	glm::vec2 toffset = glm::vec2(0.0f, 0.0f);
	float toffsetletraU = 0.0f;
	float toffsetletraV = 0.0f;
	
	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	Material_brillante = Material(4.0f, 256);
	Material_opaco = Material(0.3f, 4);


	//luz direccional, sólo 1 y siempre debe de existir
	mainLight = DirectionalLight(1.0f, 1.0f, 1.0f,
		0.3f, 0.3f,
		0.0f, 0.0f, -1.0f);
	//contador de luces puntuales
	unsigned int pointLightCount = 0;
	//Declaración de primer luz puntual
	pointLights[0] = PointLight(1.0f, 0.0f, 0.0f,
		0.0f, 1.0f,
		0.0f, 2.5f, 1.5f,
		0.3f, 0.2f, 0.1f);
	pointLightCount++;

	unsigned int spotLightCount = 0;
	//linterna
	spotLights[0] = SpotLight(1.0f, 1.0f, 1.0f,
		0.0f, 2.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		5.0f);
	spotLightCount++;

	//luz fija
	spotLights[1] = SpotLight(0.0f, 1.0f, 1.0f,
		1.0f, 2.0f,
		5.0f, 10.0f, 0.0f,
		0.0f, -5.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		15.0f);
	spotLightCount++;



	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0, uniformTextureOffset = 0;
	GLuint uniformColor = 0;


	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);

	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	std::vector<glm::vec2> offsets = {
	glm::vec2(0.65f, 0.57f), // P
	glm::vec2(0.88f, 0.57f), // R
	glm::vec2(0.57f, 0.56f), // O
	glm::vec2(0.651f,0.46f), // Y
	glm::vec2(0.45f, 0.67f), // E
	glm::vec2(0.23f, 0.67f), // C
	glm::vec2(0.11f, 0.46f), // T
	glm::vec2(0.57f, 0.56f), // O
	glm::vec2(0.23f, 0.67f), // C
	glm::vec2(0.655f,0.67f), // G
	glm::vec2(0.45f, 0.67f), // E
	glm::vec2(0.86f, 0.67f), // I
	glm::vec2(0.77f, 0.67f), // H
	glm::vec2(0.23f, 0.67f)  // C
	};


	static float tiempoAcumulado = 0.0f;
	static int indiceInicio = 0;          
	int letrasVisibles = 4;               
	float intervaloCambio = 40.0f;        
	glm::vec3 basePos(-12.0f, 2.5f, 9.5f);
	float separacion = 1.5f;
	glm::vec3 escalaLetras(1.5f, 2.0f, 2.0f);

	bool abierta = false;
	float ang = 0.0f;      
	float vel = 90.0f;     
	static bool teclaOPresionada = false; 


	
	bool puertaDerechaAbierta = false;
	bool puertaDerechaAnimando = false;
	bool teclaPPresionada = false;

	float progresoAnim = 0.0f;
	float duracionFase = 1.0f;
	int fase = 0; 
	glm::vec3 puertaDerechaPos(0.0f);

	// ---- Animación del Dado ----

	// Variables de control de estado
	bool dadoAnimando = false;      // Indica si el dado está actualmente en movimiento o animado
	bool teclaIPresionada = false;  // Detecta si la tecla para iniciar la animación fue presionada
	bool dadoEnSuelo = false;       // Determina si el dado ya cayó al suelo y debe detenerse

	// Variables físicas y de transformación
	glm::vec3 posDado(5.0f, 10.0f, -5.0f);   // Posición inicial del dado en el espacio 3D
	glm::vec3 velDado(0.0f, 0.0f, 0.0f);     // Velocidad inicial (sin movimiento al comenzar)
	float gravedad = -9.8f;                  // Valor de la gravedad que afectará al dado
	float rotacionDado = 0.0f;               // Ángulo acumulado de rotación del dado
	glm::vec3 rotDadoActual(0.0f);           // Vector que almacena la rotación actual en los tres ejes
	glm::vec3 rotVelocidad(180.0f, 240.0f, 200.0f); // Velocidad angular del dado en grados por segundo

	// Control de la cara visible del dado
	int caraDado = 0; // Guarda el número de la cara superior del dado (inicialmente 0)

	// Bucle principal de renderizado: se ejecuta mientras la ventana esté abierta
	while (!mainWindow.getShouldClose())
	{
		// Calcula el tiempo transcurrido entre frames para animaciones suaves
		GLfloat now = glfwGetTime();                      // Obtiene el tiempo actual del sistema
		deltaTime = now - lastTime;                       // Calcula la diferencia de tiempo entre cuadros
		deltaTime += (now - lastTime) / limitFPS;         // Ajuste adicional para limitar los FPS
		lastTime = now;                                   // Actualiza el último tiempo registrado

		// Incrementa la variable de ángulo para las animaciones dependientes del tiempo
		angulovaria += 0.5f * deltaTime;                  // Aumenta gradualmente el ángulo según el tiempo

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);
		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformEyePosition = shaderList[0].GetEyePositionLocation();
		uniformColor = shaderList[0].getColorLocation();
		uniformTextureOffset = shaderList[0].getOffsetLocation();

		//información en el shader de intensidad especular y brillo
		uniformSpecularIntensity = shaderList[0].GetSpecularIntensityLocation();
		uniformShininess = shaderList[0].GetShininessLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		glUniform3f(uniformEyePosition, camera.getCameraPosition().x, camera.getCameraPosition().y, camera.getCameraPosition().z);

		// luz ligada a la cámara de tipo flash
		glm::vec3 lowerLight = camera.getCameraPosition();
		lowerLight.y -= 0.3f;
		spotLights[0].SetFlash(lowerLight, camera.getCameraDirection());

		//información al shader de fuentes de iluminación
		shaderList[0].SetDirectionalLight(&mainLight);
		shaderList[0].SetPointLights(pointLights, pointLightCount);
		shaderList[0].SetSpotLights(spotLights, spotLightCount);

		tiempoAcumulado += deltaTime;
		if (tiempoAcumulado >= intervaloCambio) {
			tiempoAcumulado = 0.0f;
			indiceInicio++;
			if (indiceInicio > (int)offsets.size() - letrasVisibles)
				indiceInicio = 0;              
		}

		// Abrir/cerrar con tecla F 
		if (mainWindow.getsKeys()[GLFW_KEY_F]) {
			if (!teclaOPresionada) {
				abierta = !abierta; 
				teclaOPresionada = true;
			}
		}
		else {
			teclaOPresionada = false;
		}

		// ---- Animación ----

		// Define el ángulo objetivo de la puerta según su estado (abierta o cerrada)
		float targetAng = abierta ? -90.0f : 0.0f;

		// Comprueba si el ángulo actual difiere del objetivo (si aún debe moverse)
		if (fabs(ang - targetAng) > 0.1f) {

			// Calcula el incremento del ángulo en función de la velocidad y el tiempo transcurrido
			float step = vel * deltaTime / 10;

			// Si el ángulo actual es menor al objetivo, aumenta gradualmente hasta alcanzarlo
			if (ang < targetAng)
				ang = std::min(ang + step, targetAng);
			// Si es mayor, disminuye hasta llegar al valor deseado
			else
				ang = std::max(ang - step, targetAng);
		}



		// ---- Animación de la Puerta Derecha (abrir/cerrar con tecla G) ----
		if (mainWindow.getsKeys()[GLFW_KEY_G])  // Detecta si se presiona la tecla 'G'
		{
			// Si la tecla no estaba presionada antes y la puerta no está animándose
			if (!teclaPPresionada && !puertaDerechaAnimando)
			{
				puertaDerechaAnimando = true;   // Inicia la animación de apertura o cierre
				teclaPPresionada = true;        // Marca que la tecla ya fue detectada

				// Determina la fase de la animación según el estado de la puerta
				if (!puertaDerechaAbierta)
				{
					fase = 1;   // Fase de apertura
				}
				else
				{
					fase = 3;   // Fase de cierre
				}

				// Reinicia el progreso de animación
				progresoAnim = 0.0f;
			}
		}
		else
		{
			// Si la tecla no está siendo presionada, restablece el estado
			teclaPPresionada = false;
		}

		// ---- Lógica de movimiento de la puerta ----
		if (puertaDerechaAnimando)  // Si la puerta está en proceso de animación
		{
			// Incrementa el progreso de animación de forma proporcional al tiempo
			progresoAnim += deltaTime / 20;

			// Calcula el parámetro de interpolación (va de 0.0 a 1.0)
			float t = progresoAnim / duracionFase;


			// ---- Fase 1: Apertura inicial ----
			if (fase == 1)
			{
				// Mueve la puerta gradualmente hacia la posición de apertura (eje Z)
				puertaDerechaPos.z = glm::min(t, 1.0f) * 0.5f;

				// Si completó la fase, pasa a la siguiente
				if (t >= 1.0f)
				{
					fase = 2;           // Avanza a la fase 2 (apertura completa)
					progresoAnim = 0.0f; // Reinicia el progreso
				}
			}


			// ---- Fase 2: Finaliza apertura ----
			else if (fase == 2)
			{
				// Interpola la puerta hasta el punto final de apertura
				puertaDerechaPos = glm::vec3(glm::min(t, 1.0f) * 4.0f, 0.0f, 1.0f);

				// Si terminó la animación de apertura
				if (t >= 1.0f)
				{
					puertaDerechaAnimando = false;  // Detiene la animación
					puertaDerechaAbierta = true;    // Marca la puerta como abierta
					fase = 0;                       // Reinicia las fases
				}
			}


			// ---- Fase 3: Inicio de cierre ----
			else if (fase == 3)
			{
				// Mueve la puerta en dirección contraria (cierre)
				puertaDerechaPos = glm::vec3((1.0f - glm::min(t, 1.0f)) * 4.0f, 0.0f, 1.0f);

				// Si la fase de cierre inicial termina
				if (t >= 1.0f)
				{
					fase = 4;            // Cambia a la siguiente fase (cierre completo)
					progresoAnim = 0.0f; // Reinicia el contador
				}
			}


			// ---- Fase 4: Finaliza cierre ----
			else if (fase == 4)
			{
				// Ajusta la posición final para que regrese completamente a su punto inicial
				puertaDerechaPos.z = (1.0f - glm::min(t, 1.0f)) * 0.5f;

				// Si ya terminó de cerrarse
				if (t >= 1.0f)
				{
					puertaDerechaAnimando = false;  // Detiene la animación
					puertaDerechaAbierta = false;   // Marca la puerta como cerrada
					fase = 0;                       // Reinicia el ciclo
				}
			}
		}

		// ---- Animación del Dado ----
		if (mainWindow.getsKeys()[GLFW_KEY_L]) // Detecta si se presiona la tecla 'L'
		{
			if (!teclaIPresionada) // Verifica que la tecla no estuviera ya presionada
			{
				teclaIPresionada = true; // Marca que se presionó la tecla

				// Si el dado no está animándose ni en el suelo, inicia la animación
				if (!dadoAnimando && !dadoEnSuelo)
				{
					dadoAnimando = true; // Activa la animación
					velDado = glm::vec3(0.0f, 6.0f, 0.0f); // Asigna velocidad inicial hacia arriba
					rotDadoActual = glm::vec3(0.0f);       // Reinicia la rotación acumulada

					// Asigna velocidades de rotación aleatorias para cada eje (en grados)
					rotVelocidad = glm::vec3(
						180.0f + rand() % 90,
						180.0f + rand() % 90,
						180.0f + rand() % 90
					);

					// Selecciona aleatoriamente una cara del dado (0–8)
					caraDado = rand() % 9;
				}

				// Si el dado está en el suelo, se reinicia para volver a lanzar
				else if (dadoEnSuelo)
				{
					dadoEnSuelo = false;               // Indica que ya no está en el suelo
					dadoAnimando = false;              // Detiene la animación temporalmente
					posDado = glm::vec3(5.0f, 10.0f, -5.0f); // Restaura la posición inicial
					velDado = glm::vec3(0.0f);              // Velocidad en cero
					rotDadoActual = glm::vec3(0.0f);        // Reinicia rotación
				}
			}
		}
		else
		{
			// Si la tecla ya no está presionada, resetea su estado
			teclaIPresionada = false;
		}


		// ---- Actualización del movimiento y rotación del dado ----
		if (dadoAnimando)
		{
			// Aplica la gravedad al dado en el eje Y
			velDado.y += gravedad * deltaTime;

			// Actualiza la posición del dado según su velocidad
			posDado += velDado * deltaTime;

			// Actualiza la rotación del dado en función de la velocidad angular
			rotDadoActual += rotVelocidad * deltaTime;


			// ---- Detección de contacto con el suelo ----
			if (posDado.y <= 0.5f) // Si la posición Y es menor o igual al nivel del suelo
			{
				posDado.y = 0.5f;         // Coloca el dado justo sobre el suelo
				dadoAnimando = false;     // Detiene la animación
				dadoEnSuelo = true;       // Marca que el dado ha caído
			}
		}

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[2]->RenderMesh(); // piso

		/*color = glm::vec3(1.0f, 1.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));*/
		//Agave ¿qué sucede si lo renderizan antes del coche y de la pista?
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.5f, -2.0f));
		model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//blending: transparencia o traslucidez
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		AgaveTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);
		meshList[3]->RenderMesh();

		/*
		* Arco con letrero
		*/
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-10.0f, -1.5f, -2.0f));
		model = glm::rotate(model, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		modelaux = model;
		
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Arco.UseTexture();
		Arco_M.RenderModel(); // modelo de arco
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Letrero_M.RenderModel(); // letrero blanco
		

		glm::mat4 letraModel = glm::mat4(1.0f);
		letraModel = glm::rotate(letraModel, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		model = glm::scale(model, glm::vec3(1.5f, 2.0f, 2.0f));
		Letrero.UseTexture();

		for (int i = 0; i < letrasVisibles; i++) {
			
			int idx = (indiceInicio + i) % offsets.size();

			glm::vec2 toffset = offsets[idx];
			glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

			glm::mat4 letraModel = glm::mat4(1.0f);
			letraModel = glm::rotate(letraModel, -90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
			float startX = basePos.x + (letrasVisibles - 1) * separacion;
			letraModel = glm::translate(letraModel,
				glm::vec3(startX - i * separacion, basePos.y, basePos.z));

			letraModel = glm::scale(letraModel, escalaLetras);
			glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(letraModel));

			meshList[4]->RenderMesh();
		}

		//Puertas
		model = modelaux;
		model = glm::translate(model, glm::vec3(-0.2f, 0.0f, 0.0f));
		model = glm::rotate(model, -ang * toRadians, glm::vec3(0.0f, 0.0f, 1.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Puerta.UseTexture();
		PuertaIzq_M.RenderModel(); 
		
		model = modelaux;

		model = glm::translate(model, glm::vec3(puertaDerechaPos.x, puertaDerechaPos.z, 0.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(glm::vec2(0.0f)));
		Puerta.UseTexture();
		PuertaDere_M.RenderModel(); 

		//dado
		model = glm::mat4(1.0);
		model = glm::translate(model, posDado);
		model = glm::rotate(model, glm::radians(40.0f), glm::vec3(1, 0, 0));
		model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 0, 1));


		if (dadoAnimando) {
			model = glm::rotate(model, glm::radians(rotDadoActual.x), glm::vec3(1, 0, 0));
			model = glm::rotate(model, glm::radians(rotDadoActual.y), glm::vec3(0, 1, 0));
			model = glm::rotate(model, glm::radians(rotDadoActual.z), glm::vec3(0, 0, 1));
		}
		else if (dadoEnSuelo) {
			switch (caraDado) {
			case 0: break;
			case 1: model = glm::rotate(model, glm::radians(80.0f), glm::vec3(0, 1, 0));
					model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1));
					break;
			case 2: model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0)); break;
			case 3: model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 1, 0)); 
					model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
					break;
			case 4: model = glm::rotate(model, glm::radians(180.0f), glm::vec3(0, 1, 0));
					model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
					break; 
			case 5: model = glm::rotate(model, glm::radians(90.0f), glm::vec3(0, 0, 1)); break;
			case 6: model = glm::rotate(model, glm::radians(360.0f), glm::vec3(0, 1, 0)); break; 
			case 7: model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0)); break;
			case 8: model = glm::rotate(model, glm::radians(270.0f), glm::vec3(0, 1, 0));
					model = glm::rotate(model, glm::radians(-90.0f), glm::vec3(0, 0, 1));
					break;
			}
		}

		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		dadoTexture.UseTexture();
		Dado_M.RenderModel();
		glDisable(GL_BLEND);
		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}