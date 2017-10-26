#include <stdio.h>

int main(int argc, char const *argv[])
{
	double serial = 0.020336;
	for (int i = 1; i < 10; ++i)
	{
		double tempo;
		scanf("%lf",&tempo);
		printf("%lf\t%d\n",tempo/serial, i);
	}
	return 0;
}

// bubble    	6.11745   	50000 ok
// selection 	2.677745  	50000 ok
// comb      	0.014175  	50000 ok
// bubble    	25.171356 	100000 ok
// selection 	10.771524 	100000 ok
// comb      	0.020336  	100000
