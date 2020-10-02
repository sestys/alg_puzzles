#include <iostream>
#include <string>
#include <vector>



class Block {
    private:
        int id;
        int position;
        Block* previous;
        Block* next;
    public:
        Block(){
            id = -1;
            position = -1;
            previous = NULL;
            next = NULL;
        }
        Block(int i){
            id = i;
            position = i;
            previous = NULL;
            next = NULL;
        }
        int getId(){
            return id;
        }
        void setId(int i){
            id = i;
            position = i;
        }
        int getPosition(){
            return position;
        }
        void setPosition(int i){
            position = i;
        }
        Block* getPrevious(){
            return previous;
        }
        void setPrevious(Block* block){
            previous = block;
        }
        Block* getNext(){
            return next;
        }
        void setNext(Block* block){
            next = block;
        }
};
void move(Block* block);
// global
std::vector<Block*> positions;

int main(int argc, char const *argv[]) {
    int n; //number of blocks
    int a, b; //block specifier
    std::string comnd, type; //what to do
    std::cin >> n; //get number of blocks
    std::vector<Block> blocks(n);

    for(int i = 0; i<n; i++){
        blocks.at(i).setId(i);
        positions.push_back(&blocks.at(i));
    }
    while(1){
        std::cin >> comnd;
        if(comnd == "quit"){
            break;
        }
        //get rest of command
        std::cin >> a;
        std::cin >> type;
        std::cin >> b;
        // if command is illegal continue to the next one
        if(blocks.at(a).getPosition() == blocks.at(b).getPosition()){
            continue;
        }
        Block* tmp;
        // set the previous block
        if(blocks.at(a).getPrevious() == NULL){
            positions.at(blocks.at(a).getId()) = NULL;
        } else {
            blocks.at(a).getPrevious()->setNext(NULL);
        }
        // comands concernig a
        if(comnd == "move"){
            tmp = &blocks.at(a);
            if(tmp->getNext() != NULL){
                move(tmp->getNext());
            }
            tmp->setNext(NULL);
        } else {} // comnd == "pile"
        // comands concernig b
        tmp = &blocks.at(b);
        if(type == "onto"){
            if(tmp->getNext() != NULL){
                move(tmp->getNext());
            }
        } else { // type == "over"
            while(tmp->getNext() != NULL){
                tmp = tmp->getNext();
            }
        }
        tmp->setNext(&blocks.at(a));
        blocks.at(a).setPrevious(tmp);
        blocks.at(a).setPosition(tmp->getPosition());
        Block* tmp2;
        tmp2 = blocks.at(a).getNext();
        while(tmp2 != NULL){
            tmp2->setPosition(tmp->getPosition());
            tmp2 = tmp2->getNext();
        }

    }
    // final print
    for(int i = 0; i < n; i++){
        std::cout << i << ':';
        if(positions.at(i) != NULL){
            std::cout << " " << positions.at(i)->getId();
            Block* tmp = positions.at(i);
            while(tmp->getNext() != NULL){
                std::cout << " " << tmp->getNext()->getId();
                tmp = tmp->getNext();
            }
        }
        std::cout << std::endl;
    }
    return 0;
}

void move(Block* block){
    if(block->getNext() != NULL){
        move(block->getNext());
    }
    block->setPosition(block->getId());
    block->setNext(NULL);
    block->setPrevious(NULL);
    positions.at(block->getPosition()) = block;
}
