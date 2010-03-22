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

package net.sourceforge.jags.model;

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
