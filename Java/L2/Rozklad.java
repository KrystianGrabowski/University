public class Rozklad{
	public static void main(String[] args){

		int d = args.length;
		if (d == 0)
		{
			System.err.println("Podaj parametry do programu !");
		
		}
		for (int o=0; o<d; o++)
		{
			long x = Long.parseLong(args[o], 10);
			long[] tab = LiczbyPierwsze.naCzynnikiPierwsze(x);
			System.out.print(x);
			System.out.print(" = ");
			for (int i = 0; i < 64; i++) 
			{
				if (tab[i] == 0 && i != 0)
				{
					break;
				}
				
				System.out.print(tab[i]);
				if (i+1 < 64 && tab[i + 1] != 0) 
				{
					System.out.print("*");
				}
			
			}
			System.out.println();

			
		}

	}
}

