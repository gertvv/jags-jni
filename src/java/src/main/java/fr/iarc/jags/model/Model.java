/*
 * This file is part of JAGS-JNI (JNI wrapper for the JAGS MCMC sampler).
 * JAGS-JNI is distributed from http://github.com/gertvv/jags-jni/.
 * Copyright (C) 2010  Gert van Valkenhoef.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

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
