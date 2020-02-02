
public class Main {

	public static void main(String[] args) 
		{
		int[] T = {21,20,19,18,22,17,16,88,15,14,13,12,21,11,7,5,4,6,2,9999,3,1};
	        MergeSort sort = new MergeSort(T, 0, T.length -1); 
	        sort.start();
	        
	        try
	        {
	        	sort.join();
	        }
	        catch(Exception e) {}
	        
	        for(int i = 0; i <T.length; i++) System.out.print(T[i] + "| ");
		}
}
