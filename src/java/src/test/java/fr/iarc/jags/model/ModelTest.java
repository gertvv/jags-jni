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
