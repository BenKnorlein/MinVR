/*
 * Copyright Regents of the University of Minnesota, 2015.  This software is released under the following license: http://opensource.org/licenses/GPL-2.0.
 * Source code originally developed at the University of Minnesota Interactive Visualization Lab (http://ivlab.cs.umn.edu).
 *
 * Code author(s):
 * 		Dan Orban (dtorban)
 */

#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <plugin/VRPlugin.h>
#include <display/VRWindowToolkit.h>
#include "VRGLFWWindowToolkit.h"



namespace MinVR {



class VRGLFWPlugin : public VRPlugin {
public:
	PLUGIN_API VRGLFWPlugin() {
		std::cout << "GlfwPlugin created." << std::endl;
	}

	PLUGIN_API virtual ~VRGLFWPlugin() {
		std::cout << "GlfwPlugin destroyed." << std::endl;
	}

	PLUGIN_API bool registerWithMinVR(VRMainInterface *vrMain)
	{
		std::cout << "Registering VRGLFWPlugin." << std::endl;
		vrMain->getFactory()->addSubFactory(new VRGLFWWindowToolkitFactory());
		return true;
	}

	PLUGIN_API bool unregisterWithMinVR(VRMainInterface *vrMain)
	{
		std::cout << "Unregistering GlfwPlugin." << std::endl;
		// TODO
		return true;
	}
};

} // end namespace


extern "C"
{
	PLUGIN_API MinVR::Plugin* createPlugin() {
		return new MinVR::VRGLFWPlugin();
	}
}

