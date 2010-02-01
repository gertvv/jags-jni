package fr.iarc.jags.model;

public class Model {
	/**
	 * Pointer to the corresponding native instance
	 */
	private long d_ptr;

	public Model(int nChains) {
		d_ptr = construct(nChains);
	}

	protected void finalize() throws Throwable {
		try {
			destruct();
		} finally {
			super.finalize();
		}
	}

	native public void initialize(boolean datagen);
	native public boolean isInitialized();
	native public void update(int niter);
	native public int getCurrentIteration();
	native public Monitor addTraceMonitor(Node n);
	native public void removeMonitor(Monitor m);
	native public int nChains();
	native public boolean setRandomNumberGenerator(String name, int chain);
	native public boolean stopAdapting();
	native public boolean isAdapting();

	native private long construct(int nChains);
	native private void destruct();

	native public Node addStochasticNode(
			String distribution,
			Node[] parameters,
			Node lower, Node upper,
			double[] data);

	native public Node addDeterministicNode(
			String operation,
			Node[] parents);

	native public Node addConstantNode(
			int[] dim, double[] value);
}
