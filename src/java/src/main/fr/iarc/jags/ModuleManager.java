package fr.iarc.jags;

public class ModuleManager {
	static {
		System.loadLibrary("jagsjni");
	}

	native static public void loadModule(String name);
	native static public void unloadModule(String name);
}
