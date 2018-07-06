import static java.lang.Math.*;

public final class LiczbyPierwsze{

	
	private final static int POTEGA2 = 21 ;
	private final static int[] SITO = new int[1<<POTEGA2] ;
	// ... potrzebny jest blok inicjalizacyjny dla sita ...
	static
	{
		int i,j,k;
		int wielkosc = (int)pow(2,21);

	
		for (i = 2; i < wielkosc; i = i + 1)
		{
			SITO[i] = i;
		}
		
		for (j = 2; j * j < wielkosc; j = j + 1)
		{
			if (SITO[j] == j)
			{
				for (k = j * j; k < wielkosc; k = k + j)
				{
					if (SITO[k] == k)
					{
						SITO[k] = j;
					}
				}
			}
		}
		
	}
	private LiczbyPierwsze() {}
	public static boolean czyPierwsza (long x)
	{
		if (x < 2)
		{
			return false;
		}
		
		if (x < (int) pow(2,21))
		{

			if (SITO[(int)x] == x)
			{
				return true;
			}
			else 
			{
				return false;
			}
			
		}
		else
		{
			long i;
			long pierwiastek = (long) sqrt(x);
			for (i = 2; i <= pierwiastek; i = i + 1)
			{
				if (x % i == 0)
				{
					return false;
				}
			}
		} 
		return true;
			
	}
	public static long[] naCzynnikiPierwsze (long x)
	{
		long[] T = new long[64];
		if (x < -1)
		{
			T[0] = -1;
			long[] T1 = naCzynnikiPierwsze(x * (-1));
			for (int i = 1; i < 64; i = i + 1)
			{
				if (T1[i-1] == 0)
				{
					break;
				}
				T[i] = T1[i-1];
			}
			return T;
		}
		if (x == 1 || x == 0 || x == -1)
		{
			T[0] = x;
			return T;	
		}
		
		if (x < (int)pow(2,21) && x > 0)
		{
			if (SITO[(int)x] == x)
			{
				T[0] = x;
				return T;	
			}
			else
			{
				long p ;
				int l = 0;
				while(x != 1)
				{
					p = SITO[(int)x];
					T[l] = p;
					x = x / p;
					l = l + 1;
				}

				return T;
			
			}
		}
		else
		{
			long i = 2;
			if (czyPierwsza(x))
			{
				T[0] = x;
				return T;
			}
			else
			{
				while (i != sqrt(x))
				{
					if (x % i == 0)
					{
						T[0] = i;
						long[] T1 = naCzynnikiPierwsze(x / i);
						for (int k = 1; k < 64; k = k + 1)
						{
							if (T1[k-1] == 0)
							{
								break;
							}
							T[k] = T1[k-1];
						}
						return T;						
					}
					i = i + 1;
				}				
			}

			
		}
		return T;
	
	
	
	
	
	 }
}
