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
float movCoche;
float movOffset;
float rotllanta;
float rotllantaOffset;
bool avanza;
float toffsetflechau = 0.0f;
float toffsetflechav = 0.0f;
float toffsetnumerou = 0.0f;
float toffsetnumerov = 0.0f;
float toffsetnumerocambiau = 0.0;
float angulovaria = 0.0f;

//Variables para el letrero
int estado;
float duracionFase;
float faseTiempo;
float rotacionLetrero;
float velocidadRotacion;

float toffsetLetreroNullu = 0.0f;
float toffsetLetreroNullv = 0.0f;

float toffsetLetrerobaseu = 0.0f;
float toffsetLetrerobasev = 0.0f;
//Estado 1
float toffsetLetrero1u = 0.0f;
float toffsetLetrero1v = 0.0f;
//Estado 2
float toffsetLetrero2u = 0.0f;
float toffsetLetrero2v = 0.0f;
//Estado 3
float toffsetLetrero3u = 0.0f;
float toffsetLetrero3v = 0.0f;
//Estado 4
float toffsetLetrero4u = 0.0f;
float toffsetLetrero4v = 0.0f;
//Estado 5
float toffsetLetrero5u = 0.0f;
float toffsetLetrero5v = 0.0f;
//Estado 6
float toffsetLetrero6u = 0.0f;
float toffsetLetrero6v = 0.0f;
//Estado 7
float toffsetLetrero7u = 0.0f;
float toffsetLetrero7v = 0.0f;
//Estado 8
float toffsetLetrero8u = 0.0f;
float toffsetLetrero8v = 0.0f;
 
float Auxiliaru = 0.0f;
float Auxiliarv = 0.0f;

//Variebles para el dragon
float anguloAla = 20.0f;  //Inicio de angulo
float velocidadAla = 2.0f;
bool alaArriba = false; //Bandera que comienza con ala arriba

float posicionD = 0.0f; //Posición inicial del dragon
float velocidadD = 0.4f;
bool avanzaD = false; //Bandera de dirección del movimiento
float giroDragon; //Orientación del dragon

//Variables para el mmovimiento de las cabezas
float offsetCabeza1X = 0.0f;
float offsetCabeza1Y = 0.0f;
float offsetCabeza1Z = 0.0f;

float offsetCabeza2X = 0.0f;
float offsetCabeza2Y = 0.0f;
float offsetCabeza2Z = 0.0f;

float offsetCabeza3X = 0.0f;
float offsetCabeza3Y = 0.0f;
float offsetCabeza3Z = 0.0f;

float offsetCabeza4X = 0.0f;
float offsetCabeza4Y = 0.0f;
float offsetCabeza4Z = 0.0f;

float offsetCabeza5X = 0.0f;
float offsetCabeza5Y = 0.0f;
float offsetCabeza5Z = 0.0f;

Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

Texture brickTexture;
Texture dirtTexture;
Texture plainTexture;
Texture pisoTexture;
Texture AgaveTexture;
Texture FlechaTexture;
Texture NumerosTexture;
Texture Numero1Texture;
Texture Numero2Texture;
Texture LetreroTex;


Model Kitt_M;
Model Llanta_M;
Model Dragon_M;
Model Tiamat_M;
Skybox skybox;

//Puerta
Model Arco;
Model Letrero;
Model PuertaIzq;
Model PuertaDer;

//Dragon
Model CuerpoD;
Model AlaDerecha;
Model AlaIzquierda;
Model Cabeza1;
Model Cabeza2;
Model Cabeza3;
Model Cabeza4;
Model Cabeza5;

//materiales
Material Material_brillante;
Material Material_opaco;


//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
GLfloat	Tiempo = 0.0f;
GLint Contador = 0;
GLint Fase = 0.0f;
GLboolean actualiza = false;
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


	unsigned int flechaIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat flechaVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int scoreIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat scoreVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		1.0f, 0.0f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		1.0f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int numeroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat numeroVertices[] = {
		-0.5f, 0.0f, 0.5f,		0.0f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, 0.5f,		0.25f, 0.67f,		0.0f, -1.0f, 0.0f,
		0.5f, 0.0f, -0.5f,		0.25f, 1.0f,		0.0f, -1.0f, 0.0f,
		-0.5f, 0.0f, -0.5f,		0.0f, 1.0f,		0.0f, -1.0f, 0.0f,

	};

	unsigned int LetreroIndices[] = {
	   0, 1, 2,
	   0, 2, 3,
	};

	GLfloat LetreroVertices[] = {
		-.5f, 0.0f, 0.5f,		0.0f, 0.844f,		0.0f, -1.0f, 0.0f,
		.5f, 0.0f, 0.5f,		0.125f, 0.844f,		0.0f, -1.0f, 0.0f,
		.5f, 0.0f, -0.5f,		0.125f, 1.0f,		0.0f, -1.0f, 0.0f,
		-.5f, 0.0f, -0.5f,		0.0f, 1.0f,			0.0f, -1.0f, 0.0f,

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
	obj5->CreateMesh(flechaVertices, flechaIndices, 32, 6);
	meshList.push_back(obj5);

	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(scoreVertices, scoreIndices, 32, 6);
	meshList.push_back(obj6);

	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(numeroVertices, numeroIndices, 32, 6);
	meshList.push_back(obj7);

	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(LetreroVertices, LetreroIndices, 32, 6);
	meshList.push_back(obj8);

}


void CreateShaders()
{
	Shader* shader1 = new Shader();
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);
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
	FlechaTexture = Texture("Textures/flechas.tga");
	FlechaTexture.LoadTextureA();
	NumerosTexture = Texture("Textures/numerosbase.tga");
	NumerosTexture.LoadTextureA();
	Numero1Texture = Texture("Textures/numero1.tga");
	Numero1Texture.LoadTextureA();
	Numero2Texture = Texture("Textures/numero2.tga");
	Numero2Texture.LoadTextureA();
	LetreroTex = Texture("Textures/LetreroTex.tga");
	LetreroTex.LoadTextureA();


	Kitt_M = Model();
	Kitt_M.LoadModel("Models/kitt_optimizado.obj");
	Llanta_M = Model();
	Llanta_M.LoadModel("Models/llanta_optimizada.obj");
	Dragon_M = Model();
	Dragon_M.LoadModel("Models/17174_Tiamat_new.obj");

	//Puerta
	Arco = Model();
	Arco.LoadModel("Models/Arco.obj");
	Letrero = Model();
	Letrero.LoadModel("Models/Letrero.obj");
	PuertaIzq = Model();
	PuertaIzq.LoadModel("Models/PuertaIzq.obj");
	PuertaDer = Model();
	PuertaDer.LoadModel("Models/PuertaDer.obj");

	//Dragon
	CuerpoD = Model();
	CuerpoD.LoadModel("Models/CuerpoD.obj");
	AlaDerecha = Model();
	AlaDerecha.LoadModel("Models/AlaDerecha.obj");
	AlaIzquierda = Model();
	AlaIzquierda.LoadModel("Models/AlaIzquierda.obj");
	Cabeza1 = Model();
	Cabeza1.LoadModel("Models/Cabeza1.obj");
	Cabeza2 = Model();
	Cabeza2.LoadModel("Models/Cabeza2.obj");
	Cabeza3 = Model();
	Cabeza3.LoadModel("Models/Cabeza3.obj");
	Cabeza4 = Model();
	Cabeza4.LoadModel("Models/Cabeza4.obj");
	Cabeza5 = Model();
	Cabeza5.LoadModel("Models/Cabeza5.obj");



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
	spotLights[1] = SpotLight(0.0f, 0.0f, 1.0f,
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

	movCoche = 0.0f;
	movOffset = 0.01f;
	rotllanta = 0.0f;
	rotllantaOffset = 10.0f;

	Contador = 0;
	Fase = 0.0;
	toffsetLetrerobaseu = 0.875;
	toffsetLetrerobasev = 0.0;
	toffsetLetreroNullu = 0.0;
	toffsetLetreroNullv = 3 * -0.1562;
	toffsetLetrero1u = toffsetLetrero2u = toffsetLetrero3u = toffsetLetrero4u = toffsetLetrero5u = toffsetLetrero6u = toffsetLetrero7u = toffsetLetrero8u = toffsetLetreroNullu;
	toffsetLetrero1v = toffsetLetrero2v = toffsetLetrero3v = toffsetLetrero4v = toffsetLetrero5v = toffsetLetrero6v = toffsetLetrero7v = toffsetLetrero8v = toffsetLetreroNullv;


	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//PARA EJERCICIO DRAGON-----------------------------------------------------------------------
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		angulovaria += 1.8f * deltaTime;

		if (movCoche < 30.0f)
		{
			movCoche -= movOffset * deltaTime;
			//printf("avanza%f \n ",movCoche);
			rotllanta += rotllantaOffset * deltaTime;
		}

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		//--------------------------------------------------------------------------------------------

		//PARA EJERCICIO LETRERO ---------------------------------------------------------------------
		//GLfloat now = glfwGetTime();
		//deltaTime = now - lastTime;
		//Tiempo += now - lastTime;  // contador de tiempo
		//lastTime = now;

		////Actualizar el tiempo de la fase actual
		//faseTiempo += deltaTime;

		////Calcular el progreso de la fase actual
		//float progresoFase = faseTiempo / duracionFase;

		//if (Tiempo >= 0.25f) {
		//	actualiza = true;
		//	Tiempo = 0;
		//	Contador++;

		//	if (Contador % 8 == 0) {
		//		Fase++;
		//		if (Fase > 2) {
		//			Fase = 0;

		//		}
		//	}

		//}
		//else {
		//	actualiza = false;
		//}

		////Recibir eventos del usuario
		//glfwPollEvents();
		//float velocidadCamara = 20.0f; //Incrementar velocidad
		//camera.keyControl(mainWindow.getsKeys(), deltaTime * velocidadCamara);
		//camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());
		//-------------------------------------------------------------------------------------------

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

		glm::mat4 model(1.0);
		glm::mat4 modelaux(1.0);
		glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);
		glm::vec2 toffset = glm::vec2(0.0f, 0.0f);

		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		pisoTexture.UseTexture();
		Material_opaco.UseMaterial(uniformSpecularIntensity, uniformShininess);

		meshList[2]->RenderMesh();

		//EJERCICIO UNO----------------------------------------------------------------------------------------------------------

		//glm::vec2 originalOffset = toffset;

		//glEnable(GL_BLEND);
		//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		//if (actualiza) {
		//	if (toffsetLetrerobaseu < 0.0 && Fase == 1) {
		//		toffsetLetrerobaseu = 0.875;
		//		toffsetLetrerobasev = -0.3124;
		//	}
		//	else if (toffsetLetrerobaseu < 0.0 && Fase == 2) {
		//		toffsetLetrerobaseu = 0.875;
		//		toffsetLetrerobasev = -0.1562;
		//	}
		//	else if (toffsetLetrerobaseu < 0.0 && Fase == 0) {
		//		toffsetLetrerobaseu = 0.875;
		//		toffsetLetrerobasev = 0.0;
		//	}

		//	//Guardar la última letra
		//	float Auxiliaru = toffsetLetrero1u;
		//	float Auxiliarv = toffsetLetrero1v;

		//	//Desplazar todas las letras hacia la derecha
		//	toffsetLetrero8u = toffsetLetrero7u;
		//	toffsetLetrero8v = toffsetLetrero7v;

		//	toffsetLetrero7u = toffsetLetrero6u;
		//	toffsetLetrero7v = toffsetLetrero6v;

		//	toffsetLetrero6u = toffsetLetrero5u;
		//	toffsetLetrero6v = toffsetLetrero5v;

		//	toffsetLetrero5u = toffsetLetrero4u;
		//	toffsetLetrero5v = toffsetLetrero4v;

		//	toffsetLetrero4u = toffsetLetrero3u;
		//	toffsetLetrero4v = toffsetLetrero3v;

		//	toffsetLetrero3u = toffsetLetrero2u;
		//	toffsetLetrero3v = toffsetLetrero2v;

		//	toffsetLetrero2u = toffsetLetrero1u;
		//	toffsetLetrero2v = toffsetLetrero1v;

		//	// Asignar el valor de la base de la textura a la primera casilla
		//	toffsetLetrero1u = toffsetLetrerobaseu;
		//	toffsetLetrero1v = toffsetLetrerobasev;

		//	// Actualizar la base de la textura para la siguiente letra
		//	toffsetLetrerobaseu -= 0.125;

		//}

		//toffset = glm::vec2(toffsetLetrero2u, toffsetLetrero2v);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(3.5f - (6 * 1.0), 13.5f, -49.2f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//LetreroTex.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[7]->RenderMesh();
		//
		//toffset = glm::vec2(toffsetLetrero3u, toffsetLetrero3v);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(3.5f - (5 * 1.0), 13.5f, -49.2f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//LetreroTex.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[7]->RenderMesh();
		//
		//toffset = glm::vec2(toffsetLetrero4u, toffsetLetrero4v);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(3.5f - (4 * 1.0), 13.5f, -49.2f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//LetreroTex.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[7]->RenderMesh();
		//
		//toffset = glm::vec2(toffsetLetrero5u, toffsetLetrero5v);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(3.5f - (3 * 1.0), 13.5f, -49.2f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//LetreroTex.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[7]->RenderMesh();
		//
		//toffset = glm::vec2(toffsetLetrero6u, toffsetLetrero6v);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(3.5f - (2 * 1.0), 13.5f, -49.2f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//LetreroTex.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[7]->RenderMesh();
		//
		//toffset = glm::vec2(toffsetLetrero7u, toffsetLetrero7v);
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(3.5f - (1 * 1.0), 13.5f, -49.2f));
		//model = glm::rotate(model, 90 * toRadians, glm::vec3(1.0f, 0.0f, 0.0f));
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//color = glm::vec3(1.0f, 1.0f, 1.0f);
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//LetreroTex.UseTexture();
		//Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		//meshList[7]->RenderMesh();

		//toffset = originalOffset;
		//glUniform2fv(uniformTextureOffset, 1, glm::value_ptr(toffset));

		////ARCO--------------------------------------------------------------------------------------------------
		//model = glm::mat4(1.0);
		//model = glm::translate(model, glm::vec3(0.0f, 6.15f, -50.0f));
		//modelaux = model;
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Arco.RenderModel();

		////LETRERO		
		//model = glm::translate(modelaux, glm::vec3(0.0f, 7.4f, 0.5f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//Letrero.RenderModel();

		////PUERTA DERECHA
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(-7.5f, -1.3f, 0.05f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//PuertaDer.RenderModel();

		////PUERTA IZQUIERDA
		//model = modelaux;
		//model = glm::translate(model, glm::vec3(7.6f, -1.24f, 0.09f));
		//glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		//glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		//PuertaIzq.RenderModel();

		//EJERCICIO DOS--------------------------------------------------------------------------------------------
		if (avanzaD) {
			posicionD += velocidadD * deltaTime;
			if (posicionD >= 270.0f) {
				avanzaD = false; //Cambiar dirección
			}
		}
		else {
			posicionD -= velocidadD * deltaTime;
			if (posicionD <= -270.0f) {
				avanzaD = true; //Cambiar dirección
			}
		}
		//Rotando
		if (avanzaD) {
			giroDragon = 180.0f;
		}
		else {
			giroDragon = 0.0f;
		}

		//DRAGON------------------------------------------------------------------------------------------------
		//CUERPO DRAGON
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(posicionD, 5.0f + 4*sin(glm::radians(angulovaria)), 6.0));
		model = glm::translate(model, glm::vec3(0.0f, 5.0f, 6.0));
		model = glm::rotate(model, glm::radians(giroDragon), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
		modelaux = model;
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		CuerpoD.RenderModel();

		// Cabeza 1: Movimiento senoidal 
		float maxRangoCabeza1 = 1.0f; // Rango máximo de movimiento
		offsetCabeza1X = maxRangoCabeza1 * sin(glm::radians(angulovaria));
		offsetCabeza1Z = 0.7f * maxRangoCabeza1 * cos(glm::radians(angulovaria * 0.7f));

		// Cabeza 2: Movimiento de arco
		float maxAngleCabeza2 = 45.0f; // Ángulo máximo de giro
		float arcoCabeza2 = maxAngleCabeza2 * sin(glm::radians(angulovaria * 0.5f));
		float radioCabeza2 = 1.2f;
		offsetCabeza2X = radioCabeza2 * sin(glm::radians(arcoCabeza2));
		offsetCabeza2Z = radioCabeza2 * (1.0f - cos(glm::radians(arcoCabeza2)));

		// Cabeza 3: Movimiento en forma de corazón
		float tCorazon = glm::radians(angulovaria * 0.4f);
		float maxRangoCorazon = 1.5f; // Rango máximo de movimiento
		// Ecuación paramétrica del corazón
		float factorCorazon = maxRangoCorazon * 0.2f; // Factor de escala
		offsetCabeza3X = factorCorazon * 16.0f * pow(sin(tCorazon), 3.0f);
		offsetCabeza3Z = factorCorazon * (13.0f * cos(tCorazon) - 5.0f * cos(2.0f * tCorazon) - 2.0f * cos(3.0f * tCorazon) - cos(4.0f * tCorazon));

		// Cabeza 4: Movimiento en 8
		float tInfinito = glm::radians(angulovaria * 0.3f);
		float maxRangoInfinito = 1.4f;
		// Movimiento
		offsetCabeza4X = maxRangoInfinito * sin(tInfinito);
		offsetCabeza4Z = maxRangoInfinito * sin(tInfinito) * cos(tInfinito);
		// Agregamos movimiento vertical sincronizado
		offsetCabeza4Y = 0.7f * sin(2.0f * tInfinito);

		// Cabeza 5: Movimiento elíptico suave y limitado con oscilación vertical suave
		float maxRangoCabeza5X = 1.2f;
		float maxRangoCabeza5Z = 0.8f;
		float maxRangoCabeza5Y = 0.6f;
		offsetCabeza5X = maxRangoCabeza5X * sin(glm::radians(angulovaria * 0.6f));
		offsetCabeza5Z = maxRangoCabeza5Z * cos(glm::radians(angulovaria * 0.6f));
		offsetCabeza5Y = maxRangoCabeza5Y * sin(glm::radians(angulovaria * 1.2f));

		//CABEZA 1
		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.4f + offsetCabeza1X, 11.8f, 2.9f + offsetCabeza1Z));
		// Rotación 
		float rotCabeza1 = glm::radians(15.0f * sin(glm::radians(angulovaria * 0.5f)));
		model = glm::rotate(model, rotCabeza1, glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza1.RenderModel();

		//CABEZA 2
		model = modelaux;
		model = glm::translate(model, glm::vec3(-10.7f + offsetCabeza2X, 16.8f, 1.8f + offsetCabeza2Z));
		// Rotación 
		model = glm::rotate(model, glm::radians(arcoCabeza2), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza2.RenderModel();

		//CABEZA 3
		model = modelaux;
		model = glm::translate(model, glm::vec3(-10.8f + offsetCabeza3X, 17.0f, -3.98f + offsetCabeza3Z));
		// Rotación
		// Calculamos la tangente a la curva para orientar la cabeza
		float dxCorazon = 16.0f * 3.0f * pow(sin(tCorazon), 2.0f) * cos(tCorazon);
		float dzCorazon = -13.0f * sin(tCorazon) + 5.0f * sin(2.0f * tCorazon) +
			2.0f * sin(3.0f * tCorazon) + sin(4.0f * tCorazon);
		float anguloCorazon = atan2(dzCorazon, dxCorazon);
	
		float maxRotCorazon = 30.0f;
		float rotCorazon = glm::clamp(glm::degrees(anguloCorazon), -maxRotCorazon, maxRotCorazon);
		model = glm::rotate(model, glm::radians(rotCorazon), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza3.RenderModel();

		//CABEZA 4
		model = modelaux;
		model = glm::translate(model, glm::vec3(-12.5f + offsetCabeza4X, 12.78f + offsetCabeza4Y, -1.0f + offsetCabeza4Z));
		// Rotación compuesta para seguir el movimiento
		float anguloXZ = atan2(offsetCabeza4Z, offsetCabeza4X);
		float anguloY = atan2(offsetCabeza4Y, sqrt(offsetCabeza4X * offsetCabeza4X + offsetCabeza4Z * offsetCabeza4Z));
		float maxRotInfinito = 25.0f;
		float rotXZ = glm::clamp(glm::degrees(anguloXZ), -maxRotInfinito, maxRotInfinito);
		float rotY = glm::clamp(glm::degrees(anguloY), -maxRotInfinito / 2.0f, maxRotInfinito / 2.0f);
		// Aplicamos rotación horizontal y luego inclinación vertical
		model = glm::rotate(model, glm::radians(rotXZ), glm::vec3(0.0f, 1.0f, 0.0f));
		model = glm::rotate(model, glm::radians(rotY), glm::vec3(1.0f, 0.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza4.RenderModel();

		//CABEZA 5
		model = modelaux;
		model = glm::translate(model, glm::vec3(-11.7f + offsetCabeza5X, 11.4f + offsetCabeza5Y, -4.8f + offsetCabeza5Z));
		// Rotación
		float anguloCabeza5 = atan2(offsetCabeza5Z, offsetCabeza5X);
		float rotMax5 = 25.0f; // Máxima rotación
		float rotCabeza5 = glm::clamp(glm::degrees(anguloCabeza5), -rotMax5, rotMax5) * 0.4f;
		model = glm::rotate(model, glm::radians(rotCabeza5), glm::vec3(0.0f, 1.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza5.RenderModel();

		//Movimiento de las alas
		if (alaArriba) {
			anguloAla += velocidadAla * deltaTime;
			if (anguloAla >= 20.0f) {
				anguloAla = 20.0f;
				alaArriba = false; //Cambiar la dirección para bajar
			}
		}
		else {
			anguloAla -= velocidadAla * deltaTime;
			if (anguloAla <= -65.0f) {
				anguloAla = -65.0f;
				alaArriba = true; //Cambiar la dirección para subir
			}
		}

		//ALA DERECHA
		model = modelaux;
		model = glm::translate(model, glm::vec3(-3.0f, 12.0f, -3.0f));
		model = glm::rotate(model, glm::radians(anguloAla), glm::vec3(1.0f, 0.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaDerecha.RenderModel();

		//ALA IZQUIERDA
		model = modelaux;
		model = glm::translate(model, glm::vec3(-5.0f, 12.0f, -1.0f));
		model = glm::rotate(model, glm::radians(-anguloAla), glm::vec3(1.0f, 0.0f, 0.0f));
		Material_brillante.UseMaterial(uniformSpecularIntensity, uniformShininess);
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		AlaIzquierda.RenderModel();


		glDisable(GL_BLEND);

		glUseProgram(0);

		mainWindow.swapBuffers();
	}

	return 0;
}
