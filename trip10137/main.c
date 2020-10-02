#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	int n;
	float e[1000], total, mean, exc,rup;
	int i;
	while (scanf("%i", &n) == 1) {
		if (n == 0){
			break;
		}
		total = 0.f;
		exc = 0.f;
		for (i =0; i<n;i++){
			scanf("%f", &e[i]);
			total += e[i];
		}
		total = ceil(total*100);
		rup = (float)((int)(total)%n);
		mean = (total-rup) / (float)(100*n);
		for (i =0;i<n;i++){
			exc = exc + fabsf(e[i]-mean);
		}
		printf("$%4.2f		%.0f	%.4f		%.4f\n", (exc)/2.0-rup/200, total, rup, mean);
	}
	return 0;

}
