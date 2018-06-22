
public class Main {

	public static void main(String[] args) 
		{
		int[] T = {142,143,144,145,146,147,148,197,196,195,194,564,67,34,98,42,35,113,997,112,141,66,21,20,61,15678,455,29,19,18,22,17,16,88,15,14,98,13,88,77,76,61,62,63,12,21,11,7,5,4,6,2,9999,3,1,0,45,77,112,4912};
	        MergeSort sort = new MergeSort(T, 0, T.length -1); 
	        sort.start();
	        
	        try
	        {
	        	sort.join();
	        }
	        catch(Exception e) {}
	        
	        for(int i = 0; i <T.length; i++) System.out.print(T[i] + " ");
		}
}
