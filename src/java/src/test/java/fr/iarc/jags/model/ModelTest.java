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

import fr.iarc.jags.ModuleManager;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

import org.apache.commons.math.stat.inference.*;
import org.apache.commons.math.stat.descriptive.*;
import org.apache.commons.math.random.*;
import org.apache.commons.math.MathException;

public class ModelTest {
	private Model model;

	@Before public void setUp() {
		ModuleManager.loadModule("basemod");
		ModuleManager.loadModule("bugs");
		model = new Model(1);
	}

	@Test public void testConstructModel() {
		assertEquals(1, model.nChains());
		assertEquals(0, model.getCurrentIteration());
		assertFalse(model.isInitialized());
	}

	@Test public void testConstructMultiChainModel() {
		model = new Model(3);
		assertEquals(3, model.nChains());
	}

	@Test public void testInitialize() {
		model.initialize(false);
		assertTrue(model.isInitialized());
	}

	@Test public void testConstantNode() {
		Node n = model.addConstantNode(new int[]{1}, new double[]{8.8});
		model.initialize(true);
		model.stopAdapting();
		Monitor m = model.addTraceMonitor(n);
		model.update(10);

		assertEquals(10, model.getCurrentIteration());
		assertEquals(1, m.dim()[0]); // Node dimension
		assertEquals(10, m.dim()[1]); // Iterations dimension
		assertEquals(1, m.dim()[2]); // Chains dimension
		assertEquals(10, m.value(0).length);
		for (double v : m.value(0)) {
			assertEquals(8.8, v, 0.00001);
		}
	}

	@Test public void testDeterministicNode() {
		Node n = model.addConstantNode(new int[]{1}, new double[]{8.8});
		Node l = model.addDeterministicNode("log", new Node[]{n});
		model.initialize(true);
		model.stopAdapting();
		Monitor m = model.addTraceMonitor(l);
		model.update(10);

		assertEquals(10, model.getCurrentIteration());
		assertEquals(1, m.dim()[0]); // Node dimension
		assertEquals(10, m.dim()[1]); // Iterations dimension
		assertEquals(1, m.dim()[2]); // Chains dimension
		assertEquals(10, m.value(0).length);
		for (double v : m.value(0)) {
			assertEquals(Math.log(8.8), v, 0.00001);
		}
	}

	@Test public void testAggregateNode() {
		Node n = model.addConstantNode(new int[]{2}, new double[]{8.8, 8.0});
		Node g = model.addAggregateNode(new int[]{2},
			new Node[]{n, n}, new int[]{1, 0});
		model.initialize(true);
		model.stopAdapting();
		Monitor m = model.addTraceMonitor(g);
		model.update(10);

		assertEquals(10, model.getCurrentIteration());
		assertEquals(2, m.dim()[0]); // Node dimension
		assertEquals(10, m.dim()[1]); // Iterations dimension
		assertEquals(1, m.dim()[2]); // Chains dimension
		assertEquals(20, m.value(0).length);
		for (int i = 0; i < m.value(0).length / 2; ++i) {
			assertEquals(8.0, m.value(0)[2 * i], 0.00001);
			assertEquals(8.8, m.value(0)[2 * i + 1], 0.00001);
		}
	}

	@Test public void testUnobservedStochasticNode() throws MathException {
		Node mu = model.addConstantNode(new int[]{1}, new double[]{0});
		Node tau = model.addConstantNode(new int[]{1}, new double[]{1});
		int N = 1000;
		Node n = model.addStochasticNode("dnorm", new Node[]{mu, tau},
			null, null, null);
		model.initialize(true);
		model.stopAdapting();
		Monitor m = model.addTraceMonitor(n);
		model.update(N);
		assertEquals(N, model.getCurrentIteration());
		assertEquals(N, m.dim()[1]); // Iterations dimension

		DescriptiveStatistics stats = new DescriptiveStatistics();
		for (double v: m.value(0)) {
			stats.addValue(v);
		}
		TTest test = new TTestImpl();
		assertFalse(test.tTest(0, m.value(0), 0.05));
	}

	static double[] normalSample() {
		MersenneTwister rng = new MersenneTwister();
		double rval[] = new double[1000];
		for (int i = 0; i < rval.length; ++i) {
			rval[i] = rng.nextGaussian();
		}
		return rval;
	}

	@Test public void testObservedStochasticNode() throws MathException {
		double[] data = normalSample();
		Node mu = model.addConstantNode(new int[]{1}, new double[]{1});
		Node tau = model.addConstantNode(new int[]{1}, new double[]{.001});
		Node n = model.addStochasticNode("dnorm", new Node[]{mu, tau},
			null, null, new double[]{0});

		model.initialize(true);
		model.update(1000);

		int N = 1000;
		model.stopAdapting();
		Monitor m = model.addTraceMonitor(n);
		model.update(N);
		assertEquals(N, m.dim()[1]); // Iterations dimension

		DescriptiveStatistics stats = new DescriptiveStatistics();
		for (double v: m.value(0)) {
			stats.addValue(v);
		}
		TTest test = new TTestImpl();
		assertFalse(test.tTest(0, m.value(0), 0.05));
	}
}
