package fr.iarc.jags.model;

public class Monitor {
	private long d_ptr;

	private Monitor(long ptr) {
		d_ptr = ptr;
	}

	/**
	 * @return The iteration# at which monitoring started.
	 */
	native public int getFirstIteration();
	/**
	 * @return The last monitored iteration.
	 */
	native public int getLastIteration();
	/**
	 * @return The thinning interval of the monitor.
	 */
	native public int getThinningInterval();
	/**
	 * @return The number of monitored iterations.
	 */
	native public int getIterationCount();
	/**
	 * @return The type of monitor.
	 */
	native public String getType();
	/**
	 * The number of parallel chains of the monitor. This does not have to
	 * coincide with the number of chains in the model: a monitor may
	 * summarize data from multiple parallel chains in a single vector.
	 * @return The number of parallel chains.
	 */
	native public int nChains();
	/**
	 * @return The dimension of the value vector for a single chain.
	 */
	native public int[] dim();
	/**
	 * @return The vector of monitored values for the given chain
	 */
	native public double[] value(int chain);
}
