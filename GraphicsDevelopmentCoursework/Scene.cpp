#include "Scene.h"

using namespace std;
using namespace glm;

// public
	// constructors
		Scene::Scene(string name, unsigned int height, unsigned int width)
			: window(nullptr), openGLContext(nullptr), glew(0), mainCondition(false), events(SDL_Event()),
			objects(map<string, Object>()), viewports(vector<shared_ptr<Viewport>>()), shaders(map<string, Shader>()),
			colors(map<string, vector<float>>()) {

			if(SDLInitialization() && windowCreation(name, width, height) && contextCreation() && glewInitialization())
				mainCondition = true;
		}
		Scene::Scene(const Scene& other)
			: window(other.window), openGLContext(other.openGLContext), events(other.events), glew(other.glew),
			mainCondition(other.mainCondition), objects(other.objects), viewports(other.viewports), shaders(other.shaders),
			colors(other.colors) {}
		Scene::Scene(Scene&& other) noexcept
			: window(other.window), openGLContext(other.openGLContext), events(other.events), glew(other.glew),
			mainCondition(other.mainCondition), objects(other.objects), viewports(other.viewports), shaders(other.shaders),
			colors(other.colors) {

			SDL_GL_DeleteContext(other.openGLContext);
			SDL_DestroyWindow(other.window);
		}
	// destructor
		Scene::~Scene() {
			SDL_GL_DeleteContext(openGLContext);
			SDL_DestroyWindow(window);
		}
	// operators
		Scene& Scene::operator=(const Scene& other) { return (*this = move(Scene(other))); }
		Scene& Scene::operator=(Scene&& other) noexcept {
			if(this == &other)
				return *this;

			SDL_GL_DeleteContext(openGLContext);
			SDL_DestroyWindow(window);

			openGLContext = other.openGLContext;
			window = other.window;
			events = other.events;
			glew = other.glew;
			mainCondition = other.mainCondition;
			objects = other.objects;
			viewports = other.viewports;
			shaders = other.shaders;
			colors = other.colors;

			return *this;
		}
	// program loop
		bool Scene::mainLoop() {
			// colors, objects, shaders, viewports
				createPalette();
				createObjects();
				createAndLoadshaders();
				createViewports();

			while(mainCondition) {
				auto start = SDL_GetTicks();

				eventsHandler();

				// clear screen
					glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

				// preparing objects to display and their matrices
					list<pair<Object, optional<list<glm::mat4>>>> datalist {
						make_pair(
							objects.at("cube"),
							optional<list<glm::mat4>>()
						),
						make_pair(
							objects.at("chair"),
							optional<list<glm::mat4>>()
						),
						make_pair(
							objects.at("fan"),
							optional<list<glm::mat4>>()
						),
						make_pair(
							objects.at("table"),
							optional<list<glm::mat4>>()
						),
						make_pair(
							objects.at("wallfb"),
							optional<list<glm::mat4>>()
						),
						make_pair(
							objects.at("wallrl"),
							optional<list<glm::mat4>>()
						),
						make_pair(
							objects.at("floor"),
							optional<list<glm::mat4>>({ rotate(mat4(), (float)radians(90.0), vec3(1, 0, 0)) })
						)
					};

				displayobjects(datalist);

				// actualize display
					SDL_GL_SwapWindow(window);

				// reduce processor charge
					auto end = SDL_GetTicks();
					if(auto elapsedTime = end - start; elapsedTime < framerate)
						SDL_Delay(framerate - elapsedTime);

			}

			return false;
		}
// protected
	// initializations
		bool Scene::SDLInitialization() {
			if(SDL_Init(SDL_INIT_VIDEO) < 0) {
				cout << "Erreur lors de l'initialisation de la SDL : " << SDL_GetError() << endl;
				SDL_Quit();
				return false;
			}
			return true;
		}
		void Scene::setOpenGLAttributes() {
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
			SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
			SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
			SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
		}
		bool Scene::windowCreation(string name, unsigned int width, unsigned int height) {
			setOpenGLAttributes();
			// create the window
			window = SDL_CreateWindow(
				name.c_str(),
				SDL_WINDOWPOS_CENTERED,
				SDL_WINDOWPOS_CENTERED,
				width,
				height,
				SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
			);
			// check window
			if(window == nullptr) {
				cerr << "Error during the window creation : " << SDL_GetError() << endl;
				SDL_Quit();
				return false;
			}
			return true;
		}
		bool Scene::contextCreation() {
			if(openGLContext = SDL_GL_CreateContext(window); openGLContext == nullptr) {
				cout << "Error during the context creation : " << SDL_GetError() << endl;
				SDL_DestroyWindow(window);
				return false;
			}
			return true;
		}
		bool Scene::glewInitialization() {
			glewExperimental = GL_TRUE; // for OpenGL 3.0 (and later) features
			if(glew = glewInit(); glew != GLEW_OK) {
				cout << "Error during the initialization of GLEW : " << glewGetErrorString(glew) << endl;
				SDL_GL_DeleteContext(openGLContext);
				SDL_DestroyWindow(window);
				return false;
			}
			glEnable(GL_DEPTH_TEST); // depth buffer
			return true;
		}
	// set up colors and objects
		void Scene::createPalette() {
			colors.insert_or_assign("blue1", vector<float>({
				0.0, (float)(204.0 / 255.0), 1.0,
				0.0, (float)(204.0 / 255.0), 1.0,
				0.0, (float)(204.0 / 255.0), 1.0
			}));
			colors.insert_or_assign("multicolor1", vector<float>({
				1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,
				0.0, 0.0, 1.0
			}));
			colors.insert_or_assign("cubeColor3D", vector<float>({
				1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
				1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
				0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
				0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
				1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
				1.0, 0.0, 0.0,   1.0, 0.0, 0.0,   1.0, 0.0, 0.0,
				0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
				0.0, 1.0, 0.0,   0.0, 1.0, 0.0,   0.0, 1.0, 0.0,
				0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0,
				0.0, 0.0, 1.0,   0.0, 0.0, 1.0,   0.0, 0.0, 1.0
			}));
		}
		void Scene::createObjects() {
			// initilizations
			list<string> filesToImport = { "chair.txt", "fan.txt", "floor.txt", "table.txt", "wallfb.txt", "wallrl.txt" };
			vector<float> buffer = vector<float>();
			// imports files matching the names
			for(const auto& element : filesToImport) {
				if(buffer.clear(); import3DSMaxFile(element, buffer))
					objects.emplace(element.substr(0, element.size() - 4), Object(buffer));
				else
					cerr << "Error importing file " + element << endl;
			}
			// create test object
			objects.emplace("cube", Object(
				vector<float>({
					-1.0, -1.0, -1.0,	 1.0, -1.0, -1.0,	 1.0,  1.0, -1.0,
					-1.0, -1.0, -1.0,	-1.0,  1.0, -1.0,	 1.0,  1.0, -1.0,
					 1.0, -1.0,  1.0,	 1.0, -1.0, -1.0,	 1.0,  1.0, -1.0,
					 1.0, -1.0,  1.0,	 1.0,  1.0,  1.0,	 1.0,  1.0, -1.0,
					-1.0, -1.0,  1.0,	 1.0, -1.0,  1.0,	 1.0, -1.0, -1.0,
					-1.0, -1.0,  1.0,	-1.0, -1.0, -1.0,	 1.0, -1.0, -1.0,
					-1.0, -1.0,  1.0,	 1.0, -1.0,  1.0,	 1.0,  1.0,  1.0,
					-1.0, -1.0,  1.0,	-1.0,  1.0,  1.0,	 1.0,  1.0,  1.0,
					-1.0, -1.0, -1.0,	-1.0, -1.0,  1.0,	-1.0,  1.0,  1.0,
					-1.0, -1.0, -1.0,	-1.0,  1.0, -1.0,	-1.0,  1.0,  1.0,
					-1.0,  1.0,  1.0,	 1.0,  1.0,  1.0,	 1.0,  1.0, -1.0,
					-1.0,  1.0,  1.0,	-1.0,  1.0, -1.0,	 1.0,  1.0, -1.0
				}),
				colors.at("cubeColor3D")
			));
		}
		void Scene::createAndLoadshaders() {
			// load shader for color on 3D objects
			shaders.insert_or_assign("color3D", Shader("color3D.vert", "color3D.frag"));
			// loads all stored shaders
			for(auto& [key, value] : shaders)
				value.load();
		}
		void Scene::createViewports() {
			auto width = SDL_GetWindowSurface(window)->w, height = SDL_GetWindowSurface(window)->h;
			// emplacing viewports in the container
			viewports.emplace_back(
				make_shared<Viewport>(
					vec2(0, 0),
					vec2(width / 2, height),
					perspective(70.0, (width / 2.0) / height, 1.0, 100.0),
					lookAt(vec3(1, 100, 0), vec3(0, 0, 0), vec3(0, 1, 0))
				)
			);
			viewports.emplace_back(
				make_shared<Viewport>(
					vec2(width / 2, 0),
					vec2(width / 2, height),
					perspective(70.0, (width / 2.0) / height, 1.0, 100.0),
					lookAt(vec3(45, 45, 45), vec3(0, 0, 0), vec3(0, 1, 0))
				)
			);
		}
	// other
		bool Scene::import3DSMaxFile(string filename, vector<float>& output) {
			// get file content
			auto file_content = extractFileContent("C:/temp/" + filename);
			if(!file_content)
				return false;
			// preparing reading
			stringstream fileStream = stringstream(*file_content);
			string buffer;
			unsigned int verticesCount = 0, facesCount = 0;
			float x = 0.0, y = 0.0, z = 0.0;
			// get and store data
			while(!fileStream.eof()) {
				if(fileStream >> buffer; buffer == "*MESH_NUMVERTEX")
					fileStream >> verticesCount;
				else if(buffer == "*MESH_NUMFACES")
					fileStream >> facesCount;
				else if(buffer == "*MESH_VERTEX") {
					fileStream >> buffer >> x >> y >> z;
					cout << x << '\t' << y << '\t' << z << endl;
					try {
						output.push_back(x);
						output.push_back(y);
						output.push_back(z);
					}
					catch(bad_alloc &memoryAllocationException) {
						cerr << "Exception occurred: " << memoryAllocationException.what() << endl;
					}
				}
			}

			return verticesCount == output.size() / 3;
		}
		void Scene::eventsHandler() {
			// async events catcher
			SDL_PollEvent(&events);
			// find key pressed
			switch(events.type) {
				case SDL_WINDOWEVENT:
					switch(events.window.event) {
						case SDL_WINDOWEVENT_CLOSE:
							mainCondition = false;
							break;
						case SDL_WINDOWEVENT_RESIZED:
							// automatic, for I work from the window dimensions given by SDL ( SDL_GetWindowSurface(window) )
							break;
					}
					break;
				case SDL_KEYDOWN:
					// get the key actually pressed, regardless the keyboard layout
					switch(events.key.keysym.sym) {
						case SDLK_1:
							cout << "1" << endl;
							break;
						case SDLK_2:
							cout << "2" << endl;
							break;
						case SDLK_3:
							cout << "3" << endl;
							break;
						case SDLK_4:
							cout << "4" << endl;
							break;
						case SDLK_s:
							cout << "s" << endl;
							break;
						case SDLK_d:
							cout << "d" << endl;
							break;
						case SDLK_z:
							cout << "z" << endl;
							break;
						case SDLK_t:
							cout << "t" << endl;
							break;
						case SDLK_r:
							cout << "r" << endl;
							break;
						case SDLK_b:
							cout << "b" << endl;
							break;
						case SDLK_f:
							cout << "f" << endl;
							break;
					}
					break;
			}
		}
		void Scene::displayobjects(list<pair<Object, optional<list<glm::mat4>>>> objects_to_display) {
			// iterate through pairs
			for(auto& [object, alterations] : objects_to_display) {
				// iterate through viewports
				for(const auto& viewport : viewports) {
					// if transformation matrices are found or not
					if(alterations)
						object.draw(viewport, shaders.at("color3D"), accumulate(
							alterations->begin(),
							alterations->end(),
							viewport->getModelview(),
							multiplies<mat4>()
						));
					else
						object.draw(viewport, shaders.at("color3D"));
				}
			}
		}