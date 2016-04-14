#include <string>
#include <iostream>

#include <main/VRMain.h>
#include <main/VREventHandler.h>
#include <main/VRRenderHandler.h>

class MyVRApp : public VREventHandler, public VRRenderHandler {
	MyVRApp(const std::string &configFile, const std::string vrSetups) : _vrMain(NULL), _quit(false) {
		_vrMain = new VRMain();
		_vrMain->initialize(argv[1], argv[2]);
		_vrMain->addEventHandler(this);
		_vrMain->addRenderHandler(this);
	}

	virtual ~MyVRApp() {
		_vrMain->shutdown();
		delete _vrMain;
	}

	// Callback for event handling, inherited from VREventHandler
	virtual void onVREvent(const std::string &eventName, VRDataIndex *eventData) {
		std::cout << "Event: " << eventName << std::endl;
		if (eventName == "ESC_down") {
			_quit = true;
		}
	}

	// Callback for rendering, inherited from VRRenderHandler
	virtual void onVRRenderScene(VRDataIndex *renderState, VRDisplayNode *callingNode) {
		if (renderState->exists("IsConsole")) {
			VRConsoleNode *console = dynamic_cast<VRConsoleNode>(callingNode);
			console->println("Console output...");
		}
		else {
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			VRMatrix4 P = renderState->getValue("ProjectionMatrix", "/");
			glLoadMatrix(P.m);

			glBegin(GL_QUADS);              // Begin drawing the color cube with 6 quads
			// Top face (y = 1.0f)
			glColor3f(0.0f, 0.5f, 0.0f);    // Green
			glVertex3f( 1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);
			glVertex3f(-1.0f, 1.0f,  1.0f);
			glVertex3f( 1.0f, 1.0f,  1.0f);

			// Bottom face (y = -1.0f)
			glColor3f(0.5f, 0.25f, 0.0f);    // Orange
			glVertex3f( 1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f( 1.0f, -1.0f, -1.0f);

			// Front face  (z = 1.0f)
			glColor3f(0.5f, 0.0f, 0.0f);     // Red
			glVertex3f( 1.0f,  1.0f, 1.0f);
			glVertex3f(-1.0f,  1.0f, 1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);
			glVertex3f( 1.0f, -1.0f, 1.0f);

			// Back face (z = -1.0f)
			glColor3f(0.5f, 0.5f, 0.0f);     // Yellow
			glVertex3f( 1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f( 1.0f,  1.0f, -1.0f);

			// Left face (x = -1.0f)
			glColor3f(0.0f, 0.0f, 0.5f);     // Blue
			glVertex3f(-1.0f,  1.0f,  1.0f);
			glVertex3f(-1.0f,  1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);
			glVertex3f(-1.0f, -1.0f,  1.0f);

			// Right face (x = 1.0f)
			glColor3f(0.5f, 0.0f, 0.5f);     // Magenta
			glVertex3f(1.0f,  1.0f, -1.0f);
			glVertex3f(1.0f,  1.0f,  1.0f);
			glVertex3f(1.0f, -1.0f,  1.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);
			glEnd();                         // End of drawing color-cube
		}
	}

	void run() {
		while (!_quit) {
			_vrMain->mainloop();
		}
	}

protected:
	VRMain *_vrMain;
	bool _quit;
};



int main(int argc, char **argv) {

	if ((argc < 2) || (argc > 3) || ((argc==1) && (std::string(argv[1]) == "-h"))) {
		std::cout << "Usage:" << std::endl;
		std::cout << "vrexample <config-file-name.xml> [vrsetup-name]" << std::endl;
		std::cout << "     <config-file-name.xml> is required and is the name of a MinVR config file." << std::endl;
		std::cout << "     [vrsetup-name] is optional and is a comma-separated list of VRSetups" << std::endl;
		std::cout << "     to load in this process.  If more than one VRSetup is listed, new" << std::endl;
		std::cout << "     processes will be forked." << std::endl;
	}

	MyVRApp app(argv[1], argv[2]);
	app.run();

	exit(0);
}

