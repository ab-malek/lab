package first;

import java.util.ArrayList;
import java.util.Collections;

public class Malek {
	public static void main(String args[]) {
//		ArrayList<Integer> car = new ArrayList<Integer>();
		
		ArrayList<Integer> binary = new ArrayList<Integer>();
		
		int n = 11;
		
		while(n>0) {
			int rem = n%2;
			binary.add(rem);
			n /= 2;
		}
		
		for(int i = binary.size()-1;i>=0;i--) {
			System.out.print(binary.get(i));
		}
		
	}
}
