package fr.iarc.jags.model;

public class ConstantNode implements Node {
	private int[] d_dim;
	private double[] d_value;

	public ConstantNode(int[] dim, double[] value) {
		if (product(dim) != value.length) {
			throw new IllegalArgumentException();
		}
		d_dim = dim;
		d_value = value;
	}

	public int[] getDim() {
		return d_dim;
	}

	public double[] getValue() {
		return d_value;
	}

	private int product(int[] dim) {
		int p = 1;
		for (int d: dim) {
			p *= d;
		}
		return p;
	}
}
