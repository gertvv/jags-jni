package fr.iarc.jags;

import fr.iarc.jags.model.*;

public class Main {
	public static void main(String[] args) {
		ModuleManager.loadModule("basemod");
		ModuleManager.loadModule("bugs");

		Model model = new Model(1);
		System.out.println("Created a model with " + model.nChains() +
			" chains");

		ModuleManager.unloadModule("bugs");
		ModuleManager.unloadModule("basemod");
	}
}
