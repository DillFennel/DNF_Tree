#include <iostream>

using namespace std;

int main(){
    for(int a = 1; a>-1; a--){
        for(int b = 1; b>-1; b--){
            for(int c = 1; c>-1; c--){
                for(int d = 1; d>-1; d--){
                    cout<<((a&c)|((a==0)&c&d)|(d==0));
                }
            }
        }
    }
    return 0;
}
