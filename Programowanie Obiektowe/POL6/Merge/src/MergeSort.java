
public class MergeSort extends Thread
{
	int[] tab;
	int poczatek, koniec;
	public MergeSort(int[] x, int a, int b)
	{
		tab = x;
		poczatek = a;
		koniec = b;
		
	}

	public void scal(int[] pomoc,int p, int s, int k)
	{
		
		int l1,l2,l3,l;
		l1 = p;
		l2 = s + 1;
		l3 = k;
		l = 0;
		while ((l1 <= s)&&(l2 <= k))
		{
			
			if (tab[l2] < tab[l1])
				{
					pomoc[l] = tab[l2];
					l2 = l2 + 1;
					l = l + 1; 
				}
			else
				{
					pomoc[l] = tab[l1];
					l1 = l1 + 1;
					l = l + 1; 
				}
		}
			if (l1 <= s)
				while(l1 <= s)
				{
					
					
					pomoc[l] = tab[l1];
					l1 = l1 + 1;
					l = l + 1;
				}
			else
			{
				while (l2 <= l3)
				{
					pomoc[l] = tab[l2];
					l2 = l2 + 1;
					l = l + 1;
							
				}
				
			}
			l1 = 0;
			while (p + l1 <= k)
			{
				tab[p+l1] = pomoc [l1];
				l1 = l1 + 1;
			}
			
			
		
	}
	public void dwa()
	{	

		int j;

		if (koniec - poczatek == 1 )
		{
			if (tab[poczatek] > tab[koniec] )
			{
				j = tab[koniec];
				tab[koniec] = tab[poczatek];
				tab[poczatek] = j;
			}

		}
	}
	public void run()
	{
		if (koniec - poczatek < 2)
		{
			dwa();
		}
		else
		{

			int[] pom = new int[koniec + 1];
			int srodek = (koniec + poczatek) /2;



			MergeSort left = new MergeSort(tab,poczatek,srodek);
			MergeSort right = new MergeSort(tab,srodek + 1,koniec);
			
			left.start();
			right.start();
			try
			{
				left.join();
				right.join();
				
			}
			catch (Exception e) {}
			/*for (int y=0; y<left.tab.length; y++){
				System.out.print(left.tab[y]);
			}
			for (int y=0; y<right.tab.length; y++){
				System.out.print(right.tab[y]);
			}
			System.out.print("\n");*/
			scal(pom, poczatek, srodek, koniec);
		}

		
	}
}
