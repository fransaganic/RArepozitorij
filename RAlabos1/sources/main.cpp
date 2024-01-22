#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <vector>
#include <string>

#include "Object.h"
#include "Render.h"
#include "Camera.h"
#include "Shader.h"
#include "Curve.h"

using namespace std;

bool mozeW = false;
bool mozeS = false;
bool mozeA = false;
bool mozeD = false;
bool mozeQ = false;
bool mozeE = false;

vector<Object> objekti;
static float lastX = 400, lastY = 300;
//oèište mora biti (3,4,1), gledište mora biti (0,0,0) i view-up vektor (0,1,0)
Camera kamera = Camera(glm::vec3(3.0f, 4.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));

Curve krivulja;

bool interpolacijska;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		mozeW = true;
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		mozeS = true;
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		mozeA = true;
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		mozeD = true;
	}
	if (key == GLFW_KEY_Q && action == GLFW_PRESS) {
		mozeQ = true;
	}
	if (key == GLFW_KEY_E && action == GLFW_PRESS) {
		mozeE = true;
	}


	if (key == GLFW_KEY_W && action == GLFW_RELEASE) {
		mozeW = false;
	}
	if (key == GLFW_KEY_S && action == GLFW_RELEASE) {
		mozeS = false;
	}
	if (key == GLFW_KEY_A && action == GLFW_RELEASE) {
		mozeA = false;
	}
	if (key == GLFW_KEY_D && action == GLFW_RELEASE) {
		mozeD = false;
	}
	if (key == GLFW_KEY_Q && action == GLFW_RELEASE) {
		mozeQ = false;
	}
	if (key == GLFW_KEY_E && action == GLFW_RELEASE) {
		mozeE = false;
	}


	/*
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) {

		krivulja.dodajTocku(kamera.ociste);
	}


	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {

		interpolacijska = true;

	}
	
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {

		krivulja.dodajTocku2();

	}
	*/

	
}

void moveIt() {

	if (mozeW)
		kamera.moveForward(0.05f);
	if (mozeS)
		kamera.moveForward(-0.05f);
	if (mozeA)
		kamera.moveRight(-0.05f);
	if (mozeD)
		kamera.moveRight(0.05f);
	if (mozeQ)
		kamera.moveUp(0.05f);
	if (mozeE)
		kamera.moveUp(-0.05f);
}




void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{

	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;

	float sensitivity = 0.005f;
	xoffset *= sensitivity;
	yoffset *= sensitivity;

	kamera.rotate(xoffset, glm::vec3(0.0f, -1.0f, 0.0f));
	kamera.rotate(yoffset, glm::vec3(0.0f, 0.0f, -1.0f));
}


int main(int argc, char* argv[])
{
	glfwInit();

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "Vjezba 5a", NULL, NULL);
	if (window == NULL)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glViewport(0, 0, 800, 600);
	glfwSetFramebufferSizeCallback(window, [](GLFWwindow* window, int width, int height) {
		glViewport(0, 0, width, height);
		});

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	string path(argv[0]);
	string dirPath(path, 0, path.find_last_of("\\/"));
	string resPath(dirPath);
	resPath.append("\\resources"); //za linux pretvoriti u forwardslash
	string objPath(resPath);
	objPath.append("\\medo.obj"); //za linux pretvoriti u forwardslash

	Object objekt = Object(objPath.c_str());
	objekti.push_back(objekt);
	Render renderer = Render(objekti);

	Shader sjen = Shader();
	string vertexSource = "/Users/Fran/Documents/GitHub/IRG/irglab/irgLab/vjezba7/shaders/shader1.vert";
	string fragmentSource = "/Users/Fran/Documents/GitHub/IRG/irglab/irgLab/vjezba7/shaders/shader1.frag";
	string geometrySource = "/Users/Fran/Documents/GitHub/IRG/irglab/irgLab/vjezba7/shaders/shader1.geom";

	sjen = Shader(vertexSource.c_str(), fragmentSource.c_str(), geometrySource.c_str());

	glUseProgram(sjen.ID);




	//sjen.setMat4("projection", perspektivnaMatrica);
	//sjen.setMat4("view", matricaPogleda);


	glfwSetKeyCallback(window, key_callback);
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, cursor_position_callback);

	GLint eyeuniformlocation = glad_glGetUniformLocation(renderer.getShader().ID, "eye");

	glfwSetKeyCallback(window, key_callback);

	krivulja.ucitajBuffere();

	int interpolacijskeTocke = 0;

	

	Assimp::Importer importer1;

	std::string path1(argv[0]);
	std::string dirPath1(path1, 0, path1.find_last_of("\\/"));
	std::string resPath1(dirPath1);
	resPath1.append("\\resources"); //za linux pretvoriti u forwardslash
	std::string objPath1(resPath1);
	objPath1.append("\\tocke.obj"); //za linux pretvoriti u forwardslash

	const aiScene* scene1 = importer1.ReadFile(objPath1.c_str(),
		aiProcess_CalcTangentSpace |
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices |
		aiProcess_SortByPType);

	if (!scene1) {
		std::cerr << importer1.GetErrorString();
		return false;
	}

	vector<glm::vec3> tockeOpruge;

	if (scene1->HasMeshes()) {

		aiMesh* mesh1 = scene1->mMeshes[0];

		std::cout << "ucitana poligonalna mreza" << std::endl;

		std::cout << "prvih 12 tocaka:" << std::endl;
		//popis svih tocaka u modelu s x, y, z koordinatama
		for (int i = 0; i < 12 && i < mesh1->mNumVertices; i++) {
			std::cout << mesh1->mVertices[i].x << " " << mesh1->mVertices[i].y << " " << mesh1->mVertices[i].z << std::endl;
			glm::vec3 tocka = glm::vec3(mesh1->mVertices[i].x, mesh1->mVertices[i].y, mesh1->mVertices[i].z);
			tockeOpruge.push_back(tocka);
		}
	}
	
	cout << "Tocke su:" << endl;

	for (int i = 0; i < 12; i++) {
		cout << tockeOpruge[i].x << " " << tockeOpruge[i].y << " " << tockeOpruge[i].z << endl;
		krivulja.dodajTocku2(glm::vec3(tockeOpruge[i].x, tockeOpruge[i].y, tockeOpruge[i].z));
	}

	
	cout << "Ulazim u while loop." << endl;

	while (!glfwWindowShouldClose(window))
	{

		

		vector<glm::mat4> matricePogleda = kamera.getPerspectiveMatrix(800, 600);
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(1, 1, 1, 1);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		Shader sjencar = renderer.getShader();
		sjencar.setMat4("projection", matricePogleda[1]);
		sjencar.setMat4("view", matricePogleda[0]);
		sjencar.setMat4("model", matricePogleda[2]);

		


		glUniform3f(eyeuniformlocation, kamera.ociste.x, kamera.ociste.y, kamera.ociste.z);

		moveIt();



		renderer.draw();


		sjen.setMat4("view", matricePogleda[0]);
		sjen.setMat4("projection", matricePogleda[1]);

		
		//krivulja.points = tockeOpruge;
		if (krivulja.points.size() > 0) {

			//krivulja.draw_Interpolacijska();
			krivulja.iscrtajKrivulje(sjen);

		}
		

		/*
		if (interpolacijska) {

			kamera.ociste = krivulja.tockeInterpolacijskeKrivulje[interpolacijskeTocke];
			kamera.glediste = glm::vec3(0.0, 0.0, 0.0);
			interpolacijskeTocke += 1;

			if (interpolacijskeTocke == krivulja.tockeInterpolacijskeKrivulje.size()) {
				interpolacijska = false;
				interpolacijskeTocke = 0;
			}

		}
		*/

		
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	return 0;
}
		

		