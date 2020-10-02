import sys, math
from heapq import heappush, heappop

def printMatrix(matrix):
    for row in matrix:
        print(row)
    print()


def main():
    times = []
    index = [0]
    inp = sys.stdin.readline().split()
    cin_num = int(inp[0])
    film_len = int(inp[1])
    distance = [[0] * cin_num for i in range(cin_num)]
    
    for i in range(cin_num):
        inp = sys.stdin.readline().split()
        for j in range(cin_num):
            distance[i][j] = int(inp[j])
            distance[j][i] = int(inp[j])
    for _ in range(cin_num):
        index.append(index[-1] + int(sys.stdin.readline()))
        for x in sys.stdin.readline().split():
            times.append(int(x))
    views = [0 for _ in range(len(times))]
    travel = [10000 for _ in range(len(times))]
    queue = []
    max_views = 0
    traveled_distance = float("inf")
    
    for i in range(cin_num):
        heappush(queue, [times[index[i]], index[i],i]) #[current time, pointer, cinema id]
        travel[index[i]] = 0
    
    while queue:
        #print(queue)
        c = heappop(queue)
        #print("poped {}".format(c))
        t = c[0] + film_len
        for i in range(cin_num):
            tt = distance[i][c[2]] + t
            cur_film = -1
            for j in range(index[i],index[i+1]):
                if times[j] >= tt:
                    cur_film = j
                    #print("for cinema {} found next {}".format(i, times[cur_film]))
                    break
            if cur_film != -1:
                if views[cur_film] < views[c[1]] + 1:
                    views[cur_film] = views[c[1]] + 1
                    travel[cur_film] = travel[c[1]] + distance[i][c[2]]
                if views[cur_film] == views[c[1]] + 1 and travel[cur_film] > travel[c[1]] + distance[i][c[2]]:
                        travel[cur_film] = travel[c[1]] + distance[i][c[2]]

                if max_views < views[cur_film]:
                    max_views = views[cur_film]
                    traveled_distance = travel[cur_film]
                if max_views == views[cur_film] and traveled_distance > travel[cur_film]:
                    traveled_distance = travel[cur_film]

                if i == c[2]:
                    heappush(queue, [times[cur_film], cur_film, i])
        #print("max_views:", max_views)
        #print("traveled_distance:", traveled_distance)
        #print("Views:", views)
        #print("Travel:", travel)
        #print()
    print("{} {}".format(max_views + 1, traveled_distance))

if __name__=="__main__":
    main()
