public class LiczbyRzymskie{
	private static String[] rzymskie = {"M", "CM", "D", "CD", "C","XC", "L", "XL", "X", "IX", "V", "IV", "I"};
	private static int[] arabskie = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};

	public static void main(String[] args){
	int d = args.length;
	for (int o=0; o<d; o++)
	{
	int x = new Integer(args[o]);
	if (x <= 0 || x >= 5000)
	{
		throw new IllegalArgumentException("liczba " + x + " spoza zakresu 1-4999");
	} 
	else
	{
		System.out.println(x + " " + bin2rzym(x));	
	}	
	}

	}
	
	public static String bin2rzym(int L)
	{
	String RZ = "";
	int i = 0;
	if (L<4000)
	{
		while(L>0)
		{
			if (arabskie[i] <= L)
			{
				RZ = RZ + rzymskie[i];
				L = L - arabskie[i];
			}
			else
			{
				i = i + 1;
			}
		}
	}
	
	else
	{
		String RZ4 = bin2rzym(L/100);
		return "|" + RZ4 + "|" + bin2rzym(L - (100 * (L/100)));
	}
	
	return RZ;
	}
	

}
