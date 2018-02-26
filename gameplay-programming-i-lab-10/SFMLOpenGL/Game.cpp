#include <Game.h>

static bool flip;

Game::Game() : window(VideoMode(800, 600), "OpenGL Cube Vertex and Fragment Shaders")
{
	newmat.setA11(1);
	newmat.setA12(1);
	newmat.setA13(1);

	newmat.setA21(1);
	newmat.setA22(1);
	newmat.setA23(1);

	newmat.setA31(1);
	newmat.setA32(1);
	newmat.setA33(1);

	bottomLeft.setX(-0.5f);
	bottomLeft.setY(-0.5f);
	bottomLeft.setZ(0.0f);

	topLeft.setX(-0.5f);
	topLeft.setY(0.5f);
	topLeft.setZ(0.0f);

	topRight.setX(0.5f);
	topRight.setY(0.5f);
	topRight.setZ(0.0f);

	bottomRight.setX(0.5f);
	bottomRight.setY(-0.5f);
	bottomRight.setZ(0.0f);
}

Game::~Game() {}

void Game::run()
{

	initialize();

	Event event;

	while (isRunning) {

#if (DEBUG >= 2)
		DEBUG_MSG("Game running...");
#endif

		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				isRunning = false;
			}
		}
		update();
		render();
	}

}

typedef struct
{
	float coordinate[3];
	float color[4];
} Vertex;

Vertex vertex[6];
GLubyte triangles[6];

/* Variable to hold the VBO identifier and shader data */
GLuint	index, //Index to draw
		vsid, //Vertex Shader ID
		fsid, //Fragment Shader ID
		progID, //Program ID
		vao = 0, //Vertex Array ID
		vbo[1], // Vertex Buffer ID
		positionID, //Position ID
		colorID; // Color ID


void Game::initialize()
{
	isRunning = true;
	GLint isCompiled = 0;
	GLint isLinked = 0;

	glewInit();

	/* Vertices counter-clockwise winding */
	vertex[0].coordinate[0] = bottomLeft.getX();
	vertex[0].coordinate[1] = bottomLeft.getY();
	vertex[0].coordinate[2] = bottomLeft.getZ();

	vertex[1].coordinate[0] = topLeft.getX();
	vertex[1].coordinate[1] = topLeft.getY();
	vertex[1].coordinate[2] = topLeft.getZ();

	vertex[2].coordinate[0] = topRight.getX();
	vertex[2].coordinate[1] = topRight.getY();
	vertex[2].coordinate[2] = topRight.getZ();

	vertex[3].coordinate[0] = topRight.getX();
	vertex[3].coordinate[1] = topRight.getY();
	vertex[3].coordinate[2] = topRight.getZ();

	vertex[4].coordinate[0] = bottomRight.getX();
	vertex[4].coordinate[1] = bottomRight.getY();
	vertex[4].coordinate[2] = bottomRight.getZ();

	vertex[5].coordinate[0] = bottomLeft.getX();
	vertex[5].coordinate[1] = bottomLeft.getY();
	vertex[5].coordinate[2] = bottomLeft.getZ();

	vertex[0].color[0] = 0.0f;
	vertex[0].color[1] = 0.0f;
	vertex[0].color[2] = 0.0f;
	vertex[0].color[3] = 1.0f;

	vertex[1].color[0] = 0.0f;
	vertex[1].color[1] = 0.0f;
	vertex[1].color[2] = 0.0f;
	vertex[1].color[3] = 1.0f;

	vertex[2].color[0] = 0.0f;
	vertex[2].color[1] = 0.0f;
	vertex[2].color[2] = 0.0f;
	vertex[2].color[3] = 1.0f;

	vertex[3].color[0] = 0.0f;
	vertex[3].color[1] = 0.0f;
	vertex[3].color[2] = 0.0f;
	vertex[3].color[3] = 1.0f;

	vertex[4].color[0] = 0.0f;
	vertex[4].color[1] = 0.0f;
	vertex[4].color[2] = 0.0f;
	vertex[4].color[3] = 1.0f;

	vertex[5].color[0] = 0.0f;
	vertex[5].color[1] = 0.0f;
	vertex[5].color[2] = 0.0f;
	vertex[5].color[3] = 1.0f;


	/*Index of Poly / Triangle to Draw */
	triangles[0] = 0;   triangles[1] = 1;   triangles[2] = 2;
	triangles[3] = 3;   triangles[4] = 4;   triangles[5] = 5;

	/* Create a new VBO using VBO id */
	glGenBuffers(1, vbo);

	/* Bind the VBO */
	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

	/* Upload vertex data to GPU */
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glGenBuffers(1, &index);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLubyte) * 6, triangles, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	/* Vertex Shader which would normally be loaded from an external file */
	const char* vs_src = "#version 400\n\r"
		"in vec4 sv_position;"
		"in vec4 sv_color;"
		"out vec4 color;"
		"void main() {"
		"	color = sv_color;"
		"	gl_Position = sv_position;"
		"}"; //Vertex Shader Src

	DEBUG_MSG("Setting Up Vertex Shader");

	vsid = glCreateShader(GL_VERTEX_SHADER); //Create Shader and set ID
	glShaderSource(vsid, 1, (const GLchar**)&vs_src, NULL); // Set the shaders source
	glCompileShader(vsid); //Check that the shader compiles

	//Check is Shader Compiled
	glGetShaderiv(vsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Vertex Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Vertex Shader Compilation Error");
	}

	/* Fragment Shader which would normally be loaded from an external file */
	const char* fs_src = "#version 400\n\r"
		"in vec4 color;"
		"out vec4 fColor;"
		"void main() {"
		"	fColor = vec4(0.0f, 1.0f, 0.0f, 1.0f);"
		"}"; //Fragment Shader Src

	DEBUG_MSG("Setting Up Fragment Shader");

	fsid = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fsid, 1, (const GLchar**)&fs_src, NULL);
	glCompileShader(fsid);
	//Check is Shader Compiled
	glGetShaderiv(fsid, GL_COMPILE_STATUS, &isCompiled);

	if (isCompiled == GL_TRUE) {
		DEBUG_MSG("Fragment Shader Compiled");
		isCompiled = GL_FALSE;
	}
	else
	{
		DEBUG_MSG("ERROR: Fragment Shader Compilation Error");
	}

	DEBUG_MSG("Setting Up and Linking Shader");
	progID = glCreateProgram();	//Create program in GPU
	glAttachShader(progID, vsid); //Attach Vertex Shader to Program
	glAttachShader(progID, fsid); //Attach Fragment Shader to Program
	glLinkProgram(progID);

	//Check is Shader Linked
	glGetProgramiv(progID, GL_LINK_STATUS, &isLinked);

	if (isLinked == 1) {
		DEBUG_MSG("Shader Linked");
	}
	else
	{
		DEBUG_MSG("ERROR: Shader Link Error");
	}

	// Use Progam on GPU
	// https://www.opengl.org/sdk/docs/man/html/glUseProgram.xhtml
	glUseProgram(progID);

	// Find variables in the shader
	// https://www.khronos.org/opengles/sdk/docs/man/xhtml/glGetAttribLocation.xml
	positionID = glGetAttribLocation(progID, "sv_position");
	colorID = glGetAttribLocation(progID, "sv_color");
}

void Game::update()
{
	elapsed = clock.getElapsedTime();

	if (elapsed.asSeconds() >= 1.0f)
	{
		clock.restart();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
	{
		topLeft = newmat.Translate(2, 2) * topLeft;
		bottomLeft = newmat.Translate(2, 2) * bottomLeft;
		topRight = newmat.Translate(2, 2) * topRight;
		bottomRight = newmat.Translate(2, 2) * bottomRight;
}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		topLeft = newmat.Scale3D(1) * topLeft;
		bottomLeft = newmat.Scale3D(1) * bottomLeft;
		topRight = newmat.Scale3D(1) * topRight;
		bottomRight = newmat.Scale3D(1) * bottomRight;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		topLeft = newmat.Rotation(1) * topLeft;
		bottomLeft = newmat.Rotation(1) * bottomLeft;
		topRight = newmat.Rotation(1) * topRight;
		bottomRight = newmat.Rotation(1) * bottomRight;
	}
	vertex[0].coordinate[0] = bottomLeft.getX();
	vertex[0].coordinate[1] = bottomLeft.getY();
	vertex[0].coordinate[2] = bottomLeft.getZ();

	vertex[1].coordinate[0] = topLeft.getX();
	vertex[1].coordinate[1] = topLeft.getY();
	vertex[1].coordinate[2] = topLeft.getZ();

	vertex[2].coordinate[0] = topRight.getX();
	vertex[2].coordinate[1] = topRight.getY();
	vertex[2].coordinate[2] = topRight.getZ();

	vertex[3].coordinate[0] = topRight.getX();
	vertex[3].coordinate[1] = topRight.getY();
	vertex[3].coordinate[2] = topRight.getZ();

	vertex[4].coordinate[0] = bottomRight.getX();
	vertex[4].coordinate[1] = bottomRight.getY();
	vertex[4].coordinate[2] = bottomRight.getZ();

	vertex[5].coordinate[0] = bottomLeft.getX();
	vertex[5].coordinate[1] = bottomLeft.getY();
	vertex[5].coordinate[2] = bottomLeft.getZ();

#if (DEBUG >= 2)
	DEBUG_MSG("Update up...");
#endif

}

void Game::render()
{

#if (DEBUG >= 2)
	DEBUG_MSG("Drawing...");
#endif

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index);

	/*	As the data positions will be updated by the this program on the
		CPU bind the updated data to the GPU for drawing	*/
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 6, vertex, GL_STATIC_DRAW);

	/*	Draw Triangle from VBO	(set where to start from as VBO can contain
		model components that 'are' and 'are not' to be drawn )	*/

	// Set pointers for each parameter
	// https://www.opengl.org/sdk/docs/man4/html/glVertexAttribPointer.xhtml
	glVertexAttribPointer(positionID, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(colorID, 4, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);

	//Enable Arrays
	glEnableVertexAttribArray(positionID);
	glEnableVertexAttribArray(colorID);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, (char*)NULL + 0);

	window.display();

}

void Game::unload()
{
#if (DEBUG >= 2)
	DEBUG_MSG("Cleaning up...");
#endif
	glDeleteProgram(progID);
	glDeleteBuffers(1, vbo);
}

