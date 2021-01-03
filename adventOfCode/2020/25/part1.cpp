#include <iostream>

using namespace std;

int64_t transform(int64_t num, int64_t subject_num){
    constexpr int64_t mod = 20201227;
    return (num * subject_num) % mod;
}

int decode(int64_t pk) {
    int loop = 0;
    int64_t enc = 1, subject_num = 7;
    while (enc != pk){
        enc = transform(enc, subject_num);
        ++loop;
    }
    return loop;
}

int64_t getEncryption(int loop, int64_t subject_num){
    int64_t enc = 1;
    for (int i = 0; i < loop; ++i){
        enc = transform(enc, subject_num);
    }
    return enc;
}


int main(){
    int64_t pk_door = 0, pk_card = 0, enc = 7;
    cin >> pk_card >> pk_door;
    auto card_loop = decode(pk_card), door_loop = decode(pk_door);
    cout << "Card loop: " << card_loop << ", Door loop: " << door_loop << endl;
    auto enc_card = getEncryption(card_loop, pk_door), enc_door = getEncryption(door_loop, pk_card);
    if (enc_card != enc_door){
        cout << "ERROR, encryptions are not equal! " << endl << enc_card << endl << enc_door << endl;
        return 1;
    }
    cout << enc_card << endl;

}
