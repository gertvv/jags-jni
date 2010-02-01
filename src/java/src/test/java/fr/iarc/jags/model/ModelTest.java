package fr.iarc.jags.model;

import fr.iarc.jags.ModuleManager;

import org.junit.Before;
import org.junit.Test;
import static org.junit.Assert.*;

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
}
