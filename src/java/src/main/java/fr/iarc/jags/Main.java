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
