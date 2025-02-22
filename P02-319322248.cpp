//Pr�ctica 2: �ndices, mesh, proyecciones, transformaciones geom�tricas
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp>
//clases para dar orden y limpieza al c�digo
#include"Mesh.h"
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crear�an ac�

float angulo = 0.5f;

//color caf� en RGB : 0.478, 0.255, 0.067

//Pir�mide triangular regular
void CreaPiramide()
{
	//TECHO
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.6f, -0.5f,0.0f,	//0
		0.6f,-0.5f,0.0f,	//1
		0.0f,0.2f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);

	//�RBOL IZQUIERDO
	unsigned int arbolIzquierdo[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices_arbolIzquierdo[] = {
		-0.2f, -0.4f,0.0f,
		0.2f,-0.4f,0.0f,
		0.0f, 0.2f, -0.25f,
		0.0f,-0.4f,-0.5f,

	};
	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices_arbolIzquierdo, arbolIzquierdo, 12, 12);
	meshList.push_back(obj2);

	//�RBOL DERECHO
	unsigned int arbolDerecho[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices_arbolDerecho[] = {
		-0.2f, -0.4f,0.0f,
		0.2f,-0.4f,0.0f,
		0.0f, 0.2f, -0.25f,
		0.0f,-0.4f,-0.5f,

	};
	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(vertices_arbolDerecho, arbolDerecho, 12, 12);
	meshList.push_back(obj3);
}

//V�rtices de un cubo
void CrearCubo()
{
	unsigned int cubo_indices[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat cubo_vertices[] = {
		// front
		-0.5f, -0.8f,  0.5f,
		0.5f, -0.8f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.8f, -0.5f,
		0.5f, -0.8f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* obj4 = new Mesh();
	obj4->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(obj4);

	//Ventana Izquierda
	unsigned int ventanaIzquierda[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat vertices_ventanaIzquierda[] = {
		// front
		-0.17f, -0.17f,  0.5f,
		0.17f, -0.17f,  0.5f,
		0.17f,  0.17f,  0.5f,
		-0.17f,  0.17f,  0.5f,
		// back
		-0.17f, -0.17f, -0.5f,
		0.17f, -0.17f, -0.5f,
		0.17f,  0.17f, -0.5f,
		-0.17f,  0.17f, -0.5f
	};
	Mesh* obj5 = new Mesh();
	obj5->CreateMesh(vertices_ventanaIzquierda, ventanaIzquierda, 24, 36);
	meshList.push_back(obj5);

	//Ventana Derecha
	unsigned int ventanaDerecha[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat vertices_ventanaDerecha[] = {
		// front
		-0.17f, -0.17f,  0.5f,
		0.17f, -0.17f,  0.5f,
		0.17f,  0.17f,  0.5f,
		-0.17f,  0.17f,  0.5f,
		// back
		-0.17f, -0.17f, -0.5f,
		0.17f, -0.17f, -0.5f,
		0.17f,  0.17f, -0.5f,
		-0.17f,  0.17f, -0.5f
	};
	Mesh* obj6 = new Mesh();
	obj6->CreateMesh(vertices_ventanaDerecha, ventanaDerecha, 24, 36);
	meshList.push_back(obj6);

	//Puerta
	unsigned int puerta[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat vertices_puerta[] = {
		// front
		-0.18f, -0.25f,  0.5f,
		0.18f, -0.25f,  0.5f,
		0.18f,  0.18f,  0.5f,
		-0.18f,  0.18f,  0.5f,
		// back
		-0.18f, -0.25f, -0.5f,
		0.18f, -0.25f, -0.5f,
		0.18f,  0.18f, -0.5f,
		-0.18f,  0.18f, -0.5f
	};
	Mesh* obj7 = new Mesh();
	obj7->CreateMesh(vertices_puerta, puerta, 24, 36);
	meshList.push_back(obj7);

	//Tronco Izquierdo
	unsigned int troncoIzquierdo[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat vertices_troncoIzquierdo[] = {
		// front
		-0.11f, -0.14f,  0.5f,
		0.11f, -0.14f,  0.5f,
		0.11f,  0.11f,  0.5f,
		-0.11f,  0.11f,  0.5f,
		// back
		-0.11f, -0.14f, -0.5f,
		0.11f, -0.14f, -0.5f,
		0.11f,  0.11f, -0.5f,
		-0.11f,  0.11f, -0.5f
	};
	Mesh* obj8 = new Mesh();
	obj8->CreateMesh(vertices_troncoIzquierdo, troncoIzquierdo, 24, 36);
	meshList.push_back(obj8);

	//Tronco Derecho
	unsigned int troncoDerecho[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// right
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// left
		4, 0, 3,
		3, 7, 4,
		// bottom
		4, 5, 1,
		1, 0, 4,
		// top
		3, 2, 6,
		6, 7, 3
	};

	GLfloat vertices_troncoDerecho[] = {
		// front
		-0.11f, -0.14f,  0.5f,
		0.11f, -0.14f,  0.5f,
		0.11f,  0.11f,  0.5f,
		-0.11f,  0.11f,  0.5f,
		// back
		-0.11f, -0.14f, -0.5f,
		0.11f, -0.14f, -0.5f,
		0.11f,  0.11f, -0.5f,
		-0.11f,  0.11f, -0.5f
	};
	Mesh* obj9 = new Mesh();
	obj9->CreateMesh(vertices_troncoDerecho, troncoDerecho, 24, 36);
	meshList.push_back(obj9);
}

void CrearLetras()
{
	GLfloat vertices_letraA[] = {
		//X			Y		Z			 R		  G		 B
		-0.7f,	0.3f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.6f,	0.3f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.9f,	-0.2f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.6f,	0.3f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.9f,	-0.2f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.8f,	-0.2f,	0.0f,			0.4f,	0.172f,	0.8f,

		-0.6f,	0.3f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.7f,	0.3f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.4f,	-0.2f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.7f,	0.3f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.4f,	-0.2f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.5f,	-0.2f,	0.0f,			0.4f,	0.172f,	0.8f,

		-0.8f,	0.0f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.8f,	-0.1f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.5f,	0.0f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.5f,	0.0f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.5f,	-0.1f,	0.0f,			0.4f,	0.172f,	0.8f,
		-0.8f,	-0.1f,	0.0f,			0.4f,	0.172f,	0.8f,

	};
	MeshColor* letraA = new MeshColor();
	letraA->CreateMeshColor(vertices_letraA, 108);
	meshColorList.push_back(letraA);

	GLfloat vertices_letraV[] = {
		//X			Y		Z			  R	 	  G		 B
		-0.3f,	0.3f,	0.0f,			0.172f,	0.709f,	0.8f,
		-0.2f,	0.3f,	0.0f,			0.172f,	0.709f,	0.8f,
		0.0f,	-0.2f,	0.0f,			0.172f,	0.709f,	0.8f,
		0.0f,	-0.2f,	0.0f,			0.172f,	0.709f,	0.8f,
		-0.1f,	-0.2f,	0.0f,			0.172f,	0.709f,	0.8f,
		-0.3f,	0.3f,	0.0f,			0.172f,	0.709f,	0.8f,

		0.1f,	0.3f,	0.0f,			0.172f,	0.709f,	0.8f,
		0.2f,	0.3f,	0.0f,			0.172f,	0.709f,	0.8f,
		-0.1f,	-0.2f,	0.0f,			0.172f,	0.709f,	0.8f,
		-0.1f,	-0.2f,	0.0f,			0.172f,	0.709f,	0.8f,
		0.0f,	-0.2f,	0.0f,			0.172f,	0.709f,	0.8f,
		0.2f,	0.3f,	0.0f,			0.172f,	0.709f,	0.8f,
	};

	MeshColor* letraV = new MeshColor();
	letraV->CreateMeshColor(vertices_letraV, 72);
	meshColorList.push_back(letraV);

	GLfloat vertices_letraM[] = {
		//X			Y		Z			  R	 	  G		 B
		0.4f,	-0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.5f,	-0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.4f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.4f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.5f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.5f,	-0.2f,	0.0f,			0.905f,	0.423f,	0.149f,

		0.4f,	0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.5f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.7f,	0.1f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.7f,	0.1f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.65f,	0.0f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.4f,	0.2f,	0.0f,			0.905f,	0.423f,	0.149f,

		0.8f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.9f,	0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.6f,	0.1f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.6f,	0.1f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.65f,	0.0f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.9f,	0.2f,	0.0f,			0.905f,	0.423f,	0.149f,

		0.8f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.9f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.8f,	-0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.8f,	-0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.9f,	-0.2f,	0.0f,			0.905f,	0.423f,	0.149f,
		0.9f,	0.3f,	0.0f,			0.905f,	0.423f,	0.149f,
	};

	MeshColor* letraM = new MeshColor();
	letraM->CreateMeshColor(vertices_letraM, 144);
	meshColorList.push_back(letraM);


}


void CreateShaders()
{
	/*Shader* shader1 = new Shader(); //shader para usar �ndices: objetos: cubo y  pir�mide
	shader1->CreateFromFiles(vShader, fShader);
	shaderList.push_back(*shader1);*/

	/*Shader *shader2 = new Shader();//shader para usar color como parte del VAO: letras
	shader2->CreateFromFiles(vShaderColor, fShaderColor);
	shaderList.push_back(*shader2);*/

	// Shader verdeArbol
	Shader* shaderVerdeArbol = new Shader();
	shaderVerdeArbol->CreateFromFiles("shaders/shader.vert", "shaders/verdeArbol.frag");
	shaderList.push_back(*shaderVerdeArbol);

	// Shader verde
	Shader* shaderVerde = new Shader();
	shaderVerde->CreateFromFiles("shaders/shader.vert", "shaders/verde.frag");
	shaderList.push_back(*shaderVerde);

	// Shader rojo
	Shader* shaderRojo = new Shader();
	shaderRojo->CreateFromFiles("shaders/shader.vert", "shaders/rojo.frag");
	shaderList.push_back(*shaderRojo);

	// Shader cafe
	Shader* shaderCafe = new Shader();
	shaderCafe->CreateFromFiles("shaders/shader.vert", "shaders/cafe.frag");
	shaderList.push_back(*shaderCafe);

	// Shader azul
	Shader* shaderAzul = new Shader();
	shaderAzul->CreateFromFiles("shaders/shader.vert", "shaders/azul.frag");
	shaderList.push_back(*shaderAzul);
}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide();
	CrearCubo();
	CrearLetras(); //usa MeshColor, �ndices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//Projection: Matriz de Dimensi�n 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
	//glm::mat4 projection = glm::perspective(glm::radians(60.0f)	,mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensi�n 4x4 en la cual se almacena la multiplicaci�n de las transformaciones geom�tricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad

		//----------------------------------LETRAS---------------------------------------------------------------------------------------------											
		//Para las letras hay que usar el segundo set de shaders con �ndice 1 en ShaderList 
		/*shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();*/

		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas

		//LETRA A-------------------------------------------------
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();*/

		//LETRA V-------------------------------------------------
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();*/

		////LETRA M-------------------------------------------------
		/*model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se env�an al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();*/

		//-------------------------------------------------CASA----------------------------------------------------------------------------------

		//TECHO-----------------------------------------------------------------------------------
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.8f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//�RBOL IZQUIERDO-----------------------------------------------------------------------------------
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.35f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//�RBOL DERECHO-----------------------------------------------------------------------------------
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.35f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[2]->RenderMesh();

		//CUERPO CASA-----------------------------------------------------------------------------------
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.2f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[3]->RenderMesh();

		//VENTANA IZQUIERDA-----------------------------------------------------------------------------------
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		//VENTANA DERECHA-----------------------------------------------------------------------------------
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, 0.0f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[4]->RenderMesh();

		//PUERTA-----------------------------------------------------------------------------------
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.75f, -2.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[6]->RenderMesh();

		//TRONCO IZQUIERDO-----------------------------------------------------------------------------------
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.8f, -0.86f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[7]->RenderMesh();

		//TRONCO DERECHO-----------------------------------------------------------------------------------
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		angulo += 0.01;
		//Inicializar matriz de dimensi�n 4x4 que servir� como matriz de modelo para almacenar las transformaciones geom�tricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.8f, -0.86f, -3.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[8]->RenderMesh();

		glUseProgram(0);
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
