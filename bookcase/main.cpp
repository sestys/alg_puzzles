#include <bits/stdc++.h>

using namespace std;

struct book_t{
	int height;
	int widht;
	book_t(int h, int w){
		height = h;
		widht = w;
	}		
};


int fastscan()
{
        char c;
        int number = 0;
        c = getchar();
        while(c>=58 || c<=47) c=getchar();
        // Keep on extracting characters if they are integers
        // i.e ASCII Value lies from '0'(48) to '9' (57)
        for (; (c>47 && c<58); c=getchar())
                number = number *10 + c - 48;
        return number;
}

int greedy(vector<book_t> books, int l){
	int cost = 0, shelf_height = 0, shelf_width = 0;
	for (book_t b : books){
		if (shelf_width + b.widht > l){
			cost += shelf_height;
			shelf_height = 0;
			shelf_width = 0;
		}
		shelf_height = max(b.height, shelf_height);
		shelf_width += b.widht;
	}
	return cost + shelf_height;
}

void optimal(vector<book_t> books, int l, int &c, int &g){
	vector<int> cost(books.size() + 1, 0);
	vector<int> widht(books.size() + 1, 0);
	int i, last, shelf_height, shelf_width, best, bw;
	for (i = books.size()-1; i >= 0; i--){
		last = i;
		shelf_width = books[i].widht;
		shelf_height = books[i].height;
		best = INT_MAX;
//		bw = max(l - shelf_width, widht[last+1]);
		while (shelf_width <= l){
			if (best > shelf_height + cost[last+1]){
				bw = max(l - shelf_width, widht[last+1]);
			} else if (best == shelf_height + cost[last+1]){
				bw = min(bw, max(l - shelf_width, widht[last+1]));
			}
			best = min(best, shelf_height + cost[last+1]);
			last++;
			if (last == books.size()){
				break;
			}
			shelf_width += books[last].widht;
			shelf_height = max(shelf_height, books[last].height);
		}
		cost[i] = best;
		widht[i] = bw;
	}
	c = cost[0];
	g = widht[0];
}



int main(){
	vector<book_t> books;
	int c, g, gr,i, n, l, h, w;
	n = fastscan();
	l = fastscan();
	for (i = 0; i < n; i++){
		h = fastscan();
		w = fastscan();
		books.push_back(book_t(h, w));
	}
	gr =greedy(books, l);
	optimal(books, l, c, g);
	printf("%i %i %i\n", gr, c, g);
}
