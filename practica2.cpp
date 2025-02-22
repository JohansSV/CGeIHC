//Práctica 2: índices, mesh, proyecciones, transformaciones geométricas //bien
#include <stdio.h>
#include <string.h>
#include<cmath>
#include<vector>
#include <glew.h>
#include <glfw3.h>
//glm
#include<glm.hpp>
#include<gtc\matrix_transform.hpp>
#include<gtc\type_ptr.hpp> //sirve para enviar datos de variables uniform, glm al shader
//clases para dar orden y limpieza al código
#include"Mesh.h" //includes para el uso de clases
#include"Shader.h"
#include"Window.h"
//Dimensiones de la ventana
const float toRadians = 3.14159265f / 180.0; //grados a radianes
Window mainWindow;
std::vector<Mesh*> meshList; //LISTAS para hacer push y pop de datos
std::vector<MeshColor*> meshColorList;
std::vector<Shader>shaderList;
//Vertex Shader
static const char* vShader = "shaders/shader.vert";
static const char* fShader = "shaders/shader.frag";
static const char* vShaderColor = "shaders/shadercolor.vert";
static const char* fShaderColor = "shaders/shadercolor.frag";
//shaders nuevos se crearían acá
//azul para triangulo
static const char* vTriazul = "shaders/vTriazul.vert";
static const char* fTriazul = "shaders/fTriazul.frag";
//verde para ventana y puerta
static const char* vVerde = "shaders/vVerde.vert";
static const char* fVerde = "shaders/fVerde.frag";
//verdoso para piramide
static const char* vVerdoso = "shaders/vVerdoso.vert";
static const char* fVerdoso = "shaders/fVerdoso.frag";
//cafe para piramide
static const char* vCafe = "shaders/vCafe.vert";
static const char* fCafe = "shaders/fCafe.frag";
float angulo = 0.0f;

//color café en RGB : 0.478f, 0.255f, 0.067f

//Pirámide triangular regular
void CreaPiramide()
{
	unsigned int indices[] = {
		0,1,2,
		1,3,2,
		3,0,2,
		1,0,3

	};
	GLfloat vertices[] = {
		-0.5f, -0.5f,0.0f,	//0
		0.5f,-0.5f,0.0f,	//1
		0.0f,0.5f, -0.25f,	//2
		0.0f,-0.5f,-0.5f,	//3

	};
	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 12, 12);
	meshList.push_back(obj1);
}

//Vértices de un cubo
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
		-0.5f, -0.5f,  0.5f,
		0.5f, -0.5f,  0.5f,
		0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
		// back
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f
	};
	Mesh* cubo = new Mesh();
	cubo->CreateMesh(cubo_vertices, cubo_indices, 24, 36);
	meshList.push_back(cubo);
}
void CrearLetrasyFiguras()
{
	GLfloat verticesj[] = {
		//J
		//X		Y	 Z			R	G	B
		-0.9f, 0.4f, 0.0f,     1.0f,0.0f,0.0f,
		-0.7f, 0.4f, 0.0f,     1.0f,0.0f,0.0f,
		-0.7f, 0.3f, 0.0f,     1.0f,0.0f,0.0f,

		-0.9f, 0.4f, 0.0f,     1.0f,0.0f,0.0f,
		-0.9f,0.3f,0.0f,     1.0f,0.0f,0.0f,
		-0.7f,0.3f,0.0f,     1.0f,0.0f,0.0f,

		-0.7f,0.3f,0.0f,     1.0f,0.0f,0.0f,
		-0.7f,0.4f,0.0f,     1.0f,0.0f,0.0f,
		-0.5f,0.4f,0.0f,     1.0f,0.0f,0.0f,

		-0.5f,0.4f,0.0f,     1.0f,0.0f,0.0f,
		-0.5f,0.3f,0.0f,     1.0f,0.0f,0.0f,
		-0.7f,0.3f,0.0f,     1.0f,0.0f,0.0f,

		-0.65f,0.3f,0.0f,     1.0f,0.0f,0.0f,
		-0.65f,0.0f,0.0f,     1.0f,0.0f,0.0f,
		-0.75f,0.3f,0.0f,     1.0f,0.0f,0.0f,

		-0.75f,0.3f,0.0f,     1.0f,0.0f,0.0f,
		-0.65f,0.0f,0.0f,     1.0f,0.0f,0.0f,
		-0.75,0.0f,0.0f,      1.0f,0.0f,0.0f,

		-0.75f,0.0f,0.0f,     1.0f,0.0f,0.0f,
		-0.65f,0.0f,0.0f,     1.0f,0.0f,0.0f,
		-0.65f,-0.1f,0.0f,    1.0f,0.0f,0.0f,

		-0.75f,0.0f,0.0f,     1.0f,0.0f,0.0f,
		-0.75f,-0.1f,0.0f,    1.0f,0.0f,0.0f,
		-0.65f,-0.1f,0.f,     1.0f,0.0f,0.0f,

		-0.75f,0.0f,0.0f,     1.0f,0.0f,0.0f,
		-0.75f,-0.1f,0.0f,    1.0f,0.0f,0.0f,
		-0.9f,0.0f,0.0f,      1.0f,0.0f,0.0f,

		-0.9f,0.0f,0.0f,	  1.0f,0.0f,0.0f,
		-0.9f,-0.1f,0.0f,     1.0f,0.0f,0.0f,
		-0.75f,-0.1f,0.0f,    1.0f,0.0f,0.0f,
	};
	MeshColor* jota = new MeshColor();
	jota->CreateMeshColor(verticesj, 180);
	meshColorList.push_back(jota);

	//S
	GLfloat verticesS[] = {
		-0.2f,0.3f,0.0f,     0.0f,0.5f,0.0f,
		-0.2f,0.2f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,0.3f,0.0f,     0.0f,0.5f,0.0f,

		0.0f,0.3f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,0.2f,0.0f,     0.0f,0.5f,0.0f,
		-0.2f,0.2f,0.0f,     0.0f,0.5f,0.0f,

		0.0f,0.3f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.2f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,0.2f,0.0f,     0.0f,0.5f,0.0f,

		-0.2f,0.2f,0.0f,     0.0f,0.5f,0.0f,
		-0.1f,0.2f,0.0f,     0.0f,0.5f,0.0f,
		-0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,

		-0.2f,0.2f,0.0f,     0.0f,0.5f,0.0f,
		-0.2f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		-0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,

		-0.1f,0.175f,0.0f,     0.0f,0.5f,0.0f,
		0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		-0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,

		-0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.1f,0.025f,0.0f,     0.0f,0.5f,0.0f,

		0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.0f,0.0f,     0.0f,0.5f,0.0f,

		0.1f,0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.0f,0.0f,     0.0f,0.5f,0.0f,
		0.1f,0.0f,0.0f,     0.0f,0.5f,0.0f,

		0.2f,0.0f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,-0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,-0.1f,0.0f,     0.0f,0.5f,0.0f,

		0.0f,-0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,0.0f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.0f,0.0f,     0.0f,0.5f,0.0f,

		-0.2f,0.0f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,-0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,0.0f,0.0f,     0.0f,0.5f,0.0f,

		0.0f,0.3f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.3f,0.0f,     0.0f,0.5f,0.0f,
		0.2f,0.2f,0.0f,     0.0f,0.5f,0.0f,

		-0.2f,0.0f,0.0f,     0.0f,0.5f,0.0f,
		-0.2f,-0.1f,0.0f,     0.0f,0.5f,0.0f,
		0.0f,-0.1f,0.0f,     0.0f,0.5f,0.0f,
	};
	MeshColor* ese = new MeshColor();
	ese->CreateMeshColor(verticesS, 252);
	meshColorList.push_back(ese);

	GLfloat verticesV[] = {
		0.5f,0.4f,0.0f,     0.5f,0.5f,0.0f,
		0.6f,0.4f,0.0f,     0.5f,0.5f,0.0f,
		0.5f,0.2f,0.0f,     0.5f,0.5f,0.0f,

		0.5f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.6f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.6f,0.4f,0.0f,     0.5f,0.5f,0.0f,

		0.6f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.6f,0.1f,0.0f,     0.5f,0.5f,0.0f,
		0.5f,0.2f,0.0f,     0.5f,0.5f,0.0f,

		0.5f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.5f,0.1f,0.0f,     0.5f,0.5f,0.0f,
		0.7f,0.025f,0.0f,     0.5f,0.5f,0.0f,

		0.5f,0.1f,0.0f,     0.5f,0.5f,0.0f,
		0.7f,0.025f,0.0f,     0.5f,0.5f,0.0f,
		0.7f,-0.1f,0.0f,     0.5f,0.5f,0.0f,

		0.7f,0.025f,0.0f,     0.5f,0.5f,0.0f,
		0.7f,-0.1f,0.0f,     0.5f,0.5f,0.0f,
		0.9f,0.1f,0.0f,     0.5f,0.5f,0.0f,

		0.7f,0.025f,0.0f,     0.5f,0.5f,0.0f,
		0.9f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.9f,0.1f,0.0f,     0.5f,0.5f,0.0f,

		0.8f,0.1f,0.0f,     0.5f,0.5f,0.0f,
		0.8f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.9f,0.2f,0.0f,     0.5f,0.5f,0.0f,

		0.8f,0.4f,0.0f,     0.5f,0.5f,0.0f,
		0.9f,0.4f,0.0f,     0.5f,0.5f,0.0f,
		0.8f,0.2f,0.0f,     0.5f,0.5f,0.0f,

		0.9f,0.4f,0.0f,     0.5f,0.5f,0.0f,
		0.9f,0.2f,0.0f,     0.5f,0.5f,0.0f,
		0.8f,0.2f,0.0f,     0.5f,0.5f,0.0f,
	};
	MeshColor* uve = new MeshColor();
	uve->CreateMeshColor(verticesV, 180);
	meshColorList.push_back(uve);
}

void CreateShaders()
{
	//shader para cuadrado rojo
	Shader* shader1 = new Shader(); //shader para usar índices: objetos: cubo y  pirámide
	shader1->CreateFromFiles(vShader, fShader); //indice 0 
	shaderList.push_back(*shader1);

	Shader* shader2 = new Shader();//shader para usar color como parte del VAO: letras 
	shader2->CreateFromFiles(vShaderColor, fShaderColor); //índice 1
	shaderList.push_back(*shader2);

	//CREACIÓN de SHADERS figuras 3d con color
	//shader para triangulo azul 
	Shader* shader3 = new Shader();
	shader3->CreateFromFiles(vTriazul, fTriazul); //índice 2
	shaderList.push_back(*shader3);
	//shader para cuadrado verde
	Shader* shader4 = new Shader();
	shader4->CreateFromFiles(vVerde, fVerde);//índice 3
	shaderList.push_back(*shader4);
	//shader para triangulo verde 
	Shader* shader5 = new Shader();
	shader5->CreateFromFiles(vVerdoso, fVerdoso);//índice 4
	shaderList.push_back(*shader5);
	//shader para cuadrado café 
	Shader* shader6 = new Shader();
	shader6->CreateFromFiles(vCafe, fCafe);//índice 5
	shaderList.push_back(*shader6);

}


int main()
{
	mainWindow = Window(800, 600);
	mainWindow.Initialise();
	CreaPiramide(); //índice 0 en MeshList
	CrearCubo();//índice 1 en MeshList
	CrearLetrasyFiguras(); //usa MeshColor, índices en MeshColorList
	CreateShaders();
	GLuint uniformProjection = 0;
	GLuint uniformModel = 0;
	//GLuint uniformColor = 0;
	//Projection: Matriz de Dimensión 4x4 para indicar si vemos en 2D( orthogonal) o en 3D) perspectiva
	glm::mat4 projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f); //left, right, bottom, up ,near,far
	//glm::mat4 projection = glm::perspective(glm::radians(30.0f), mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 100.0f);

	//Model: Matriz de Dimensión 4x4 en la cual se almacena la multiplicación de las transformaciones geométricas.
	glm::mat4 model(1.0); //fuera del while se usa para inicializar la matriz con una identidad

	//Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		//Recibir eventos del usuario
		glfwPollEvents();
		//Limpiar la ventana
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //Se agrega limpiar el buffer de profundidad


		//Para las letras hay que usar el segundo set de shaders con índice 1 en ShaderList 
		shaderList[1].useShader();
		uniformModel = shaderList[1].getModelLocation();
		uniformProjection = shaderList[1].getProjectLocation();

		/*
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		//Generando J
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[0]->RenderMeshColor();
		//Generando S
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[1]->RenderMeshColor();
		//Generando V
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, -0.4f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA y se envían al shader como variables de tipo uniform
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshColorList[2]->RenderMeshColor();
		*/

		//Para el cubo rojo
		shaderList[0].useShader();
		uniformModel = shaderList[0].getModelLocation();
		uniformProjection = shaderList[0].getProjectLocation();
		//uniformColor = shaderList[0].getColorLocation(); //uso de color propio.
		//glUniform3f(uniformColor, 1.0f, 0.0f, 0.0f);
		//angulo += 0.1;
		//Inicializar matriz de dimensión 4x4 que servirá como matriz de modelo para almacenar las transformaciones geométricas
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.4f, -5.0f));
		model = glm::scale(model, glm::vec3(1.0, 1.3f, 1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));//FALSE ES PARA QUE NO SEA TRANSPUESTA
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PARA DIBUJAR A LA piramide azul
		shaderList[2].useShader();
		uniformModel = shaderList[2].getModelLocation();
		uniformProjection = shaderList[2].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.55, -4.0f));
		model = glm::scale(model, glm::vec3(1.2f, 0.75f, 1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//PARA DIBUJAR A LA piramide verde derecha
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.5, -4.0f));
		model = glm::scale(model, glm::vec3(0.35, 0.6f, -1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//PARA DIBUJAR A LA piramide verde izquierda
		shaderList[4].useShader();
		uniformModel = shaderList[4].getModelLocation();
		uniformProjection = shaderList[4].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.5, -4.0f));
		model = glm::scale(model, glm::vec3(0.35, 0.6f, -1.0));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[0]->RenderMesh();

		//PARA DIBUJAR ventana verde izquierda
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.25f, -0.08f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3, 0.4f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PARA DIBUJAR ventana verde derecha
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.25f, -0.08f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3, 0.4f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PARA DIBUJAR puerta verde
		shaderList[3].useShader();
		uniformModel = shaderList[3].getModelLocation();
		uniformProjection = shaderList[3].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -4.0f));
		model = glm::scale(model, glm::vec3(0.3, 0.4f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PARA DIBUJAR cuadrado cafe izquierda
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(-0.75f, -0.9f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15, 0.20f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		//PARA DIBUJAR cuadrado cafe derecha
		shaderList[5].useShader();
		uniformModel = shaderList[5].getModelLocation();
		uniformProjection = shaderList[5].getProjectLocation();
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.75f, -0.9f, -4.0f));
		model = glm::scale(model, glm::vec3(0.15, 0.20f, 0.25f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		meshList[1]->RenderMesh();

		glUseProgram(0);
		mainWindow.swapBuffers();
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