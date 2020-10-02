#include <stdio.h>

int main(int argc, char **argv)
{
	int n, i, max = 0, len;
	int bot, up, bot1, up1;
	while (scanf("%i %i", &bot, &up) == 2) {
		if (up < bot) {
			up1 = bot;
			bot1 = up;
		} else {
			up1 = up;
			bot1 = bot;
		}
		for (i = bot1; i <= up1; i++) {
			n = i;
			len = 1;
			while (n != 1){
				if (n%2 == 0){
					n /= 2;
				} else {
					n = 3*n +1;
				}
				len += 1;
			}
			if (max < len) {
				max = len;
			}
		}
		printf("%i %i %i\n", bot, up, max);
		max = 0;
	}
}
