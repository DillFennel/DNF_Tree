#include <iostream>
#include <bitset>

using namespace std;
int degree_of_two(int n){
    int x = 0b1;
    if(n<0){
        cerr<<"Error: не работает с отрицательными степянями";
        exit(1);
    }
    return x << n;
}
int get_opposite_key(int* key, int n){//По ключу находим его обратный. То есть, заменяем 0 на 1, 1 на 0. Подается указатель на ключ и его длина
    int ret = ~*key;
    return ret;
}
int main(){
    int key = 0b1;
    bitset<4> x(get_opposite_key(&key, 5));
    cout<<key<<endl<<get_opposite_key(&key, 5)<<endl<<x;
}