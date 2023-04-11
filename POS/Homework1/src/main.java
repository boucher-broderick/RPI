import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.PriorityQueue;
import java.util.Queue;
import java.util.Scanner;


public class main {
	

	static int connected(graph x, int t) {
		Map<Integer, List<Integer> > map = new HashMap<>();
		map = x.getgraph();
		int nodes = x.getNodes();
		int [] visited = new int [nodes];	
		for (int i =0; i <nodes; i++) {
			visited[i]=-1;
		}
		int n =1;
		Queue<Integer> queue = new PriorityQueue<Integer> (); 
		queue.add(0);
		visited[0]=0;
		int temp;
		int counter=1;
		while(n<nodes) {
			if(queue.isEmpty()) {
				for (int i =0; i <nodes; i++) {
					if(visited[i]==-1) {
						queue.add(i);
						visited[i]=0;
						counter=1;
						break;
					}
				}
			}
			temp = queue.remove();
			n++;
			for (int j = 0; j < map.get(temp).size(); j++) {
	            if(visited[map.get(temp).get(j)]==-1) {
	            	queue.add(map.get(temp).get(j));
	            	visited[map.get(temp).get(j)]=counter;
	            	counter++;
	            }
	        }
			
		}
		int largest=0;
		for(int i =0; i<nodes; i++) {
			if(visited[i]>largest) {
				largest=visited[i];
			}
		}
		if(largest>t) {
			return 1;
		}
		else {
			return 0;
		}
		
	}
	
	
	
	
	public static void main(String[]argv) {
		Scanner in = new Scanner(System.in);
		
		//System.out.print("Enter the number of nodes: ");
		//int n = in.nextInt();
		//graph x = new graph(n);
		
		
		//System.out.print("Enter a number between 0 and 1: ");
		//double p = in.nextDouble();
		
		for(double c = .2; c<=3;c+=.2) {
			double p = c/40;
			int counter=0;
			for(int i=0;i<500;i++) {
				graph temp = new graph(40);
				temp.addedge(p);
				int t = connected(temp, 30);
				counter+=t;
			}
			System.out.println(c + "--->"+(double)(counter)/500.0);
		}

		
		
	}
}
