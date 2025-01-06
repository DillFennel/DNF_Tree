#include <iostream>

using namespace std;

//((b*!c)+(a*b*c*d)+(a*c))
int main(){
    for(int a=1; a!=-1; a--){
        for(int b=1; b!=-1; b--){
            for(int c=1; c!=-1; c--){
                for(int d=1; d!=-1; d--){
                    //cout<<a<<' '<<b<<' '<<c<<' '<<d<<" = "<<((b&!c)|(a&b&c&d)|(a&c))<<endl;
                    cout<<((b&!c)|(a&b&c&d)|(a&c));
                }
            }
        }
    }
    return 0;
}