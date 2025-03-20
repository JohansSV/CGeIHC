/*
Práctica 5: Optimización y Carga de Modelos
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
#include "Shader_m.h"
#include "Camera.h"
#include "Sphere.h"
#include"Model.h"
#include "Skybox.h"

const float toRadians = 3.14159265f / 180.0f;
//float angulocola = 0.0f;
Window mainWindow;
std::vector<Mesh*> meshList;
std::vector<Shader> shaderList;

Camera camera;

/* Modelos ejercicio
Model Goddard_M;
Model Mandibula_M;
Model Cuerpo_M;
Model Cabeza_M;
Model patadelder_M;
Model patadelizq_M;
Model patatrasder_M;
Model patatrasizq_M;
*/
//modelos práctica
Model cuerpo_bus;
Model capo_bus;
Model llanta_del_izq;
Model llanta_del_der;
Model llanta_tras_izq;
Model llanta_tras_der;

Skybox skybox;

//Sphere cabeza = Sphere(0.5, 20, 20);
GLfloat deltaTime = 0.0f;
GLfloat lastTime = 0.0f;
static double limitFPS = 1.0 / 60.0;


// Vertex Shader
static const char* vShader = "shaders/shader_m.vert";

// Fragment Shader
static const char* fShader = "shaders/shader_m.frag";


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


	Mesh* obj1 = new Mesh();
	obj1->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj1);

	Mesh* obj2 = new Mesh();
	obj2->CreateMesh(vertices, indices, 32, 12);
	meshList.push_back(obj2);

	Mesh* obj3 = new Mesh();
	obj3->CreateMesh(floorVertices, floorIndices, 32, 6);
	meshList.push_back(obj3);


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

	camera = Camera(glm::vec3(0.0f, 0.5f, 7.0f), glm::vec3(0.0f, 1.0f, 0.0f), -60.0f, 0.0f, 0.3f, 1.0f);

	/* Importados para el ejercicio
	Goddard_M = Model();
	Goddard_M.LoadModel("Models/cuerpog_obj.obj");

	Cuerpo_M = Model();
	Cuerpo_M.LoadModel("Models/solocuerpog_obj.obj");

	Mandibula_M = Model(); //Creamos modelo
	Mandibula_M.LoadModel("Models/mandibulag_obj.obj");

	Cabeza_M = Model(); //Creamos modelo
	Cabeza_M.LoadModel("Models/cabezag_obj.obj");

	patadelder_M = Model(); //Creamos modelo
	patadelder_M.LoadModel("Models/patag_delantera_der.obj");

	patadelizq_M = Model(); //Creamos modelo
	patadelizq_M.LoadModel("Models/patag_delantera_izq.obj");

	patatrasder_M = Model(); //Creamos modelo
	patatrasder_M.LoadModel("Models/patag_trasera_der.obj");

	patatrasizq_M = Model(); //Creamos modelo
	patatrasizq_M.LoadModel("Models/patag_trasera_izq.obj");
	*/

	//IMPORTADOS PARA EJERCICIO DE PRÁCTICA
	cuerpo_bus = Model(); //Creamos modelo
	cuerpo_bus.LoadModel("Models/cuerpo_bus.obj");
	capo_bus = Model(); //Creamos modelo
	capo_bus.LoadModel("Models/capo_bus.obj");
	llanta_del_izq = Model(); //Creamos modelo
	llanta_del_izq.LoadModel("Models/llanta_del_izq.obj");
	llanta_del_der = Model(); //Creamos modelo
	llanta_del_der.LoadModel("Models/llanta_del_der.obj");
	llanta_tras_der = Model(); //Creamos modelo
	llanta_tras_der.LoadModel("Models/llanta_tras_der.obj");
	llanta_tras_izq = Model(); //Creamos modelo
	llanta_tras_izq.LoadModel("Models/llanta_tras_izq.obj");

	std::vector<std::string> skyboxFaces;
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_rt.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_lf.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_dn.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_up.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_bk.tga");
	skyboxFaces.push_back("Textures/Skybox/cupertin-lake_ft.tga");

	skybox = Skybox(skyboxFaces);

	GLuint uniformProjection = 0, uniformModel = 0, uniformView = 0, uniformEyePosition = 0,
		uniformSpecularIntensity = 0, uniformShininess = 0;
	GLuint uniformColor = 0;
	glm::mat4 projection = glm::perspective(45.0f, (GLfloat)mainWindow.getBufferWidth() / mainWindow.getBufferHeight(), 0.1f, 1000.0f);


	glm::mat4 model(1.0);
	glm::mat4 modelaux(1.0);
	glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f);

	////Loop mientras no se cierra la ventana
	while (!mainWindow.getShouldClose())
	{
		GLfloat now = glfwGetTime();
		deltaTime = now - lastTime;
		deltaTime += (now - lastTime) / limitFPS;
		lastTime = now;

		//Recibir eventos del usuario
		glfwPollEvents();
		camera.keyControl(mainWindow.getsKeys(), deltaTime);
		camera.mouseControl(mainWindow.getXChange(), mainWindow.getYChange());

		// Clear the window
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//Se dibuja el Skybox
		skybox.DrawSkybox(camera.calculateViewMatrix(), projection);

		shaderList[0].UseShader();
		uniformModel = shaderList[0].GetModelLocation();
		uniformProjection = shaderList[0].GetProjectionLocation();
		uniformView = shaderList[0].GetViewLocation();
		uniformColor = shaderList[0].getColorLocation();

		glUniformMatrix4fv(uniformProjection, 1, GL_FALSE, glm::value_ptr(projection));
		glUniformMatrix4fv(uniformView, 1, GL_FALSE, glm::value_ptr(camera.calculateViewMatrix()));
		// INICIA DIBUJO DEL PISO
		color = glm::vec3(0.5f, 0.5f, 0.5f); //piso de color gris
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -2.0f, 0.0f));
		model = glm::scale(model, glm::vec3(30.0f, 1.0f, 30.0f));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		meshList[2]->RenderMesh();

		/* INICIA EJERCICIO------
		//------------*INICIA DIBUJO DE NUESTROS DEMÁS OBJETOS-------------------*
		//Goddard
		color = glm::vec3(0.0f, 0.0f, 0.0f); //modelo de goddard de color negro
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, 0.3f, -1.5f));
		//se guarda el modelo del cuerpo con su traslación, para luego en la jerarquía seguir con cabeza y patas.
		modelaux = model;
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cuerpo_M.RenderModel();//modificar por el modelo sin las 4 patas y sin cola
		//En sesión se separara una parte del modelo de Goddard y se unirá por jeraquía al cuerpo
		model = modelaux;
		//cabeza
		color = glm::vec3(0.0f, 0.5f, 0.0f);
		model = glm::translate(model, glm::vec3(1.35f, 0.8f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Cabeza_M.RenderModel();//modificar por el modelo de mandibula
		//mandibula unida a cabeza
		color = glm::vec3(0.0f, 0.f, 0.5f);
		model = glm::translate(model, glm::vec3(1.25f, 0.3f, 0.0f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion2()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		Mandibula_M.RenderModel();//modificar por el modelo de mandibula
		model = modelaux; //se regresa al cuerpo para seguir con las patotas
		//Siguientes modelos
		 Ejercicio:
		1.- Separar las 4 patas de Goddard del modelo del cuerpo, unir por medio de jerarquía cada pata al cuerpo de Goddard
		2.- Hacer que al presionar una tecla cada pata pueda rotar un máximo de 45° "hacia adelante y hacia atrás"


		//pata delantera derecha
		//h adelante j atras
		color = glm::vec3(0.0f, 0.0f, 0.5f);
		model = glm::translate(model, glm::vec3(1.1f, -0.15f, 0.6f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patadelder_M.RenderModel();//modificar por el modelo de pata
		model = modelaux;

		// pata delantera izquierda
		//k adelante l atras
		color = glm::vec3(0.0f, 0.0f, 0.5f);
		model = glm::translate(model, glm::vec3(1.15f, -0.32f, -0.6f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion4()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patadelizq_M.RenderModel();//modificar por el modelo de pata
		model = modelaux;

		//pata trasera derecha
		//z adelante x atras
		color = glm::vec3(0.0f, 0.0f, 0.5f);
		model = glm::translate(model, glm::vec3(-0.6f, -0.85f, 0.6f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion5()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patatrasder_M.RenderModel();//modificar por el modelo de pata
		model = modelaux;

		//pata trasera izquierda
		//c adelante v atras
		color = glm::vec3(0.0f, 0.0f, 0.5f);
		model = glm::translate(model, glm::vec3(-0.6f, -0.925f, -0.6f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion6()), glm::vec3(0.0f, 0.0f, 1.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		patatrasizq_M.RenderModel();//modificar por el modelo de pata
		model = modelaux;

		Model cuerpo_bus;
Model capo_bus;
Model llanta_del_izq;
Model llanta_del_der;
Model llanta_tras_izq;
Model llanta_tras_der;
		*/

		//INICIA EJERCICIO DE PRÁCTICA
		//Bus
		color = glm::vec3(0.0f, 0.0f, 1.0f);
		model = glm::mat4(1.0);
		model = glm::translate(model, glm::vec3(0.0f, -0.8f, -1.5f));
		//Movimiento usando K para adelante y L para atras, además llantas se mueven al avanzar o retroceder.
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, mainWindow.getarticulacion4()));
		modelaux = model; //se guarda traslación
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		cuerpo_bus.RenderModel();//crear cuerpo de bus
		//capo
		color = glm::vec3(0.0f, 0.0f, 0.5f);
		model = glm::translate(model, glm::vec3(0.0f, 0.0f, 3.4f));
		//articulación para el capo
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion1()), glm::vec3(-1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		capo_bus.RenderModel();//capo
		model = modelaux; //volvemos a cuerpo
		//llanta izq del
		color = glm::vec3(0.5f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.7f, -0.8f, 2.1f));
		//Se usa misma variable para rotar todas las llantas
		//H hacia adelante y J hacia atrás
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_del_izq.RenderModel();//llanta adelatne izq
		model = modelaux; //volvemos a cuerpo
		//llanta izq del
		color = glm::vec3(0.5f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(-0.7f, -0.8f, 2.1f));
		//H hacia adelante y J hacia atrás
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_del_der.RenderModel();//llanta adelatne der
		model = modelaux; //volvemos a cuerpo
		//llanta izq tras
		color = glm::vec3(0.5f, 0.0f, 0.0f);
		model = glm::translate(model, glm::vec3(0.5f, -0.8f, -1.55f));
		//H hacia adelante y J hacia atrás
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_tras_izq.RenderModel();//llanta adelatne der
		model = modelaux; //volvemos a cuerpo
		//llanta der tras
		color = glm::vec3(0.5f, 0.0f, 0.0f);
		//H hacia adelante y J hacia atrás
		model = glm::translate(model, glm::vec3(-0.5f, -0.8f, -1.55f));
		model = glm::rotate(model, glm::radians(mainWindow.getarticulacion3()), glm::vec3(1.0f, 0.0f, 0.0f));
		glUniform3fv(uniformColor, 1, glm::value_ptr(color));
		glUniformMatrix4fv(uniformModel, 1, GL_FALSE, glm::value_ptr(model));
		llanta_tras_der.RenderModel();//llanta adelatne der

		glUseProgram(0);
		mainWindow.swapBuffers();
	}

	return 0;
}