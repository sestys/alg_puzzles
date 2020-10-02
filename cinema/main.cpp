#include <bits/stdc++.h>

using namespace std;

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

class Entry {
public:
	int curr_time;
	int index_pointer;
	int cinema_id;
	vector<int> last_film;
	Entry(int c, int p, int i, vector<int> l){
		curr_time = c;
		index_pointer = p;
		cinema_id = i;
		last_film = l;
	}
};

struct comparator{
	bool operator()(Entry &a, Entry &b) const{
		return a.curr_time > b.curr_time;
	}
};
void printVector(vector<int> v){
	for (auto i : v){
		cout << i << ' ';
	}
	cout << endl;
}

int main(){
	vector<int> times;
	vector<int> index;
	vector<int> distance;
	vector<Entry> queue;
	bool next;
	int cin_num, film_len, curr_film, i, j, t, tt, tmp, max_views = 0, traveled_distance;
	traveled_distance = numeric_limits<int>::max();
	cin_num = fastscan();
	film_len = fastscan();
	
	for (i = 0; i < cin_num * cin_num; i++){
		distance.push_back(fastscan());
	}
	index.push_back(0);
	for (i = 0; i < cin_num; i++){
		tmp = fastscan();
		index.push_back(index.back() + tmp);
		for (j = 0; j < tmp; j++){
			times.push_back(fastscan());
		}
	}
	vector<int> views(index.back(), 0);
	vector<int> travel(index.back(), 10000000);
	for (i = 0; i < cin_num; i++){
		queue.push_back(Entry(times[index[i]], index[i], i, index));
		push_heap(queue.begin(), queue.end(), comparator());
		travel[index[i]] = 0;
	}
	while (!queue.empty()){
		Entry e = queue.front();

		pop_heap(queue.begin(), queue.end(), comparator()); queue.pop_back();
		next = false;
		t = e.curr_time + film_len;


		for (i = 0; i < cin_num; i++){
			tt = distance[i * cin_num + e.cinema_id] + t;
			curr_film = -1;
			for (j = e.last_film[i]; j < index[i+1]; j++){
				if (times[j] >= tt){
					e.last_film[i] = curr_film = j;
					break;
				}
			}	
			if (curr_film != -1){
				if (views[curr_film] < views[e.index_pointer] + 1){
					views[curr_film] = views[e.index_pointer] + 1;
					travel[curr_film] = travel[e.index_pointer] + distance[i * cin_num + e.cinema_id];
				} else if ((views[curr_film] == views[e.index_pointer] + 1) && (travel[curr_film] > travel[e.index_pointer] + distance[i*cin_num + e.cinema_id])){
					travel[curr_film] = travel[e.index_pointer] + distance[i*cin_num + e.cinema_id];
				}
				if (max_views < views[curr_film]){
					max_views = views[curr_film];
					traveled_distance = travel[curr_film];
				} else if ((max_views == views[curr_film]) && (traveled_distance > travel[curr_film])){
					traveled_distance = travel[curr_film];
				}
				if (i == e.cinema_id){
					next = true;
				}
			}
		}
		if (next){
			queue.push_back(Entry(times[e.last_film[e.cinema_id]], e.last_film[e.cinema_id], e.cinema_id, e.last_film));
			push_heap(queue.begin(), queue.end(), comparator());			
		}
	}
	printf("%i %i\n", max_views + 1, traveled_distance);
}


















