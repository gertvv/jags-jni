package fr.iarc.jags.model;

public class Model {
	/**
	 * Pointer to the corresponding native instance
	 */
	private long d_ptr;

	public Model(int nChains) {
		d_ptr = construct(nChains);
	}

	native public void initialize(boolean datagen);
	native public boolean isInitialized();
	native public void update(int niter);
	native public int getCurrentIteration();
	native public void addMonitor(Monitor m);
	native public void removeMonitor(Monitor m);
	native public int nChains();
	native public boolean setRandomNumberGenerator(String name, int chain);
	native public boolean stopAdapting();
	native public boolean isAdapting();
	
	public void addNode(Node node) {
	}

	native private long construct(int nChains);

	native private void addStochasticNode(
			String distribution,
			Node[] parameters,
			Node lower, Node upper);

	native private void addDeterministicNode(
			String operation,
			Node[] parents);

	native private void addConstantNode(
			int[] dim, double[] value);
}
