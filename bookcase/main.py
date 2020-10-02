import sys, math



class Book():
    def __init__(self, width, height):
        self.width = width
        self.height = height

    def __repr__(self):
        return str(self.height)+ ' ' + str(self.width) 

def gready(books, length):
    cost = 0
    shelf_height = 0
    shelf_width = 0
    for b in books:
        if shelf_width + b.width > length:
            cost += shelf_height
            shelf_height = 0
            shelf_width = 0
        shelf_height = max(b.height, shelf_height)
        shelf_width += b.width
    cost+= shelf_height
    return cost


def optimalHeight(books, length):
    cost = [0 for _ in range(len(books)+1)]
    width = [0 for _ in range(len(books)+1)]
    for i in range(len(books)-1, -1, -1):
        last = i
        shelf_width = books[last].width
        shelf_height = books[last].height
        best = float("inf")
        bw = max(length-shelf_width, width[last+1])
        while True:
            if best > shelf_height + cost[last+1]:
                bw = max(length - shelf_width, width[last+1])
            elif best == shelf_height + cost[last+1]:
                bw = min(bw, max(length - shelf_width, width[last+1]))
 
            best = min(best, shelf_height + cost[last+1])
            last += 1
            if last == len(books):
                break
            shelf_width += books[last].width
            if shelf_width > length:
                shelf_width -= books[last].width
                break
            #print("i best last_best last bw:",i, best,last_best, last, bw)
            shelf_height = max(shelf_height, books[last].height)
        cost[i] = best
        width[i] = bw 

    return cost[0], width[0]


def main():
    n, l = map(int, sys.stdin.readline().split())
    books = []
    for _ in range(n):
        h, w = map(int, sys.stdin.readline().split())
        books.append(Book(w, h))
    g = gready(books, l)
    o, gap = optimalHeight(books, l)
    print(g, o, gap)

if __name__=="__main__":
    main()
