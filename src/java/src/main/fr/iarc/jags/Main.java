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

		Node n = model.addConstantNode(new int[]{1}, new double[]{8.8});
		Node l = model.addDeterministicNode("log", new Node[]{n});

		model.initialize(true);
		model.stopAdapting();
		Monitor m = model.addTraceMonitor(n);
		model.update(10);
		System.out.println("Current iteration: " + model.getCurrentIteration());
		System.out.println("Dim  : ");
		for (int i : m.dim()) {
			System.out.println(i);
		}
		System.out.println("Value: ");
		for (double d : m.value(0)) {
			System.out.println(d);
		}
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
