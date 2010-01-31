package fr.iarc.jags;

import fr.iarc.jags.model.*;

public class Main {
	public static void makeModel() {
		Model model = new Model(1);
		System.out.println("Created a model with " + model.nChains() +
			" chains");
		System.out.println("Current iteration " + model.getCurrentIteration());
		System.out.println("Initialized " + model.isInitialized());
		System.out.println("Adapting " + model.isAdapting());

		model.addConstantNode(new int[]{1}, new double[]{8.8});
	}

	public static void main(String[] args) {
		ModuleManager.loadModule("basemod");
		ModuleManager.loadModule("bugs");

		makeModel();
		System.gc();

		ModuleManager.unloadModule("bugs");
		ModuleManager.unloadModule("basemod");
	}
}
