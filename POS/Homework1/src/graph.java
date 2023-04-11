import java.util.HashMap;
import java.util.LinkedList;
import java.util.List;
import java.util.Map;
import java.util.Random;

public class graph {
	
	private int nodes;
	private Map<Integer, List<Integer> > map = new HashMap<>();
	Random rand = new Random();
	
	
	public graph(int n) {
		nodes=n;
		for (int i =0; i<n; i++) {
			map.put(i, new LinkedList<Integer>());
		}
	}
	
	public void addedge(double p) {
		for(int i =0; i <nodes; i++) {
			for(int j=0; j <nodes;j++) {
				if(i!=j) {
					double q=rand.nextDouble();
					if(q<p) {
						if(map.get(i).contains(j)!=true)
							map.get(i).add(j);
						if(map.get(j).contains(i)!=true)
							map.get(j).add(i);
					}
				}
			}
		}
	}
	
	public void printgraph() {
		for(int i=0; i<nodes; i++) {
			System.out.print(i+": ");
			for (int j = 0; j < map.get(i).size(); j++) {
	            System.out.print(map.get(i).get(j) + " ");
	        }
			System.out.println();			
		}
	}
	
	public Map<Integer, List<Integer> > getgraph(){
		return map;
	}
	
	public int getNodes() {
		return nodes;
	}
	
	
	
}
