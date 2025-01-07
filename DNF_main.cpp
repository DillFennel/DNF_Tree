#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
#include <bitset>
#include <cassert>

using namespace std;
/*
Дано - дерево, обозначающее ДНФ
Результат - сбалансированное дерево
Шаги:
1) Преобразовать таблицу ДНФ в дерево
2) По правилам сократить количество вершин
Ключ вершины - это результаты функции при всех возможных переменных, то есть последний столбец в таблице истиности
*/
unsigned degree_of_two(int n){//Функция для получения степеней двойки (натуральных или 0)
    if(n<0){
        cerr<<"Error: не работает с отрицательными степянями";
        exit(1);
    }
    return 1 << n;
}
unsigned get_mask(unsigned number_of_variables){//Получение маски для заданого количества переменных (Нужны, чтобы обрезать ключи до нужного размера)
    return ((1 << degree_of_two(number_of_variables)) - 1);
}
unsigned get_opposite_key(unsigned key, unsigned number_of_variables){//По ключу находим его обратный. То есть, заменяем 0 на 1, 1 на 0. Подается указатель на ключ и количество переменных
    return (~key&get_mask(number_of_variables));
}

bool check_equal_keys(unsigned key1, unsigned key2){ //Проверяет, эквивалентны ли выражения. Сравниваем по ключу
    return (key1 == key2);
}
bool check_opposite_keys(unsigned key1, unsigned key2, unsigned number_of_variables){//Проверяет, обратны ли выражения. Сравниваем по ключу. Также указываем количество переменных
    return (key1 == get_opposite_key(key2, number_of_variables));
}

//char simbols [11] = {'0', '1', 'a', 'b', 'c', 'd', '!', '*', '+', '>', '='};//Все возможные значения в вершине
char simbols[4] = {'a', 'b', 'c', 'd'};
class Tree{
    public:
        unsigned get_key(){ //
        /*
        Ниже представленно, чему соответствует каждый элемент ключа вершины в таблице истиности.
            a b c d   f(a, b, c, d)
            0 0 0 0   k[0]
            0 0 0 1   k[1]
            0 0 1 0   k[2]
            0 0 1 1   k[3]
            0 1 0 0   k[4]
            0 1 0 1   k[5]
            0 1 1 0   k[6]
            0 1 1 1   k[7]
            1 0 0 0   k[8]
            1 0 0 1   k[9]
            1 0 1 0   k[10]
            1 0 1 1   k[11]
            1 1 0 0   k[12]
            1 1 0 1   k[13]
            1 1 1 0   k[14]
            1 1 1 1   k[15]
            
        */
            return key;
        }
        Tree * get_child(int n){//Возвращает ребенка вершины под указанным номером
            if(n<0 or n>=number_of_children){
                cerr<<n<<' '<<number_of_children<<endl;
                cerr<<"Ошибка: Такого ребенка нет (Пытаемся получить ребенка под номером "<<n<<", а всего детей "<<number_of_children<<").";
                exit(5);
            }
            return children[n];
        }
        unsigned get_number_of_children(){//Возвращает количество детей у вершины
            return number_of_children;
        }
        void set_value(int v){//Позволяет установить значение в вершине
        //Добавить условия для значений
            value = v;
        }
        char get_value(){//Позволяет получить значение, установленное в вершине
            return value;
        }
        bool add_child(Tree * new_child){//Позволяет добавить ребенка вершине
            switch (value){
                case '0':
                case '1':
                case 'a':
                case 'b':
                case 'c':
                case 'd':{
                    cant_have_children();
                }
                case '!':{
                    if(number_of_children > 0){
                        too_many_children();
                    }
                    key = get_opposite_key(new_child->get_key(), number_of_variables);
                    break;
                }
                case '*':{
                    key = key & new_child->get_key();
                    break;
                }
                case '+':{
                    key = key | new_child->get_key();
                    break;
                }
                case '>':{
                    key = get_opposite_key(key, number_of_variables) | new_child->get_key();
                    break;
                }
                case '=':{
                    if(number_of_children > 0){
                        too_many_children();
                    }
                    key = key&new_child->get_key() | get_opposite_key(key, number_of_variables)&get_opposite_key(new_child->get_key(), number_of_variables);
                    break;
                }
                default:{
                    something_wrong();
                }
            }
            number_of_children++;
            children.push_back(new_child);
            return true;
        }
        void delete_child(int ind_child){
            delete children[ind_child];
            children.erase(children.begin() + ind_child);
            number_of_children--;
        }
        void wrong_value(){
            cerr<<"Ошибка: Такое значение невозможно.";
            exit(1);
        }
        void cant_have_children(){
            cerr<<"Ошибка: у переменных не может быть детей.";
            exit(2);
        }
        void too_many_children(){
            cerr<<"Ошибка: слишком много детей для операции.";
            exit(3);
        }
        void something_wrong(){
            cerr<<"Ошибка.";
            exit(4);
        }
        Tree(unsigned n=4){//По умолчанию величина в вершине равна 8, то есть по умолчанию стоит операция суммы
            number_of_variables=n;}
        Tree(char v, unsigned n=4){
            switch(v){
                case '0':
                case '!':
                case '+':{
                    key = 0b0000000000000000;
                    break;
                }
                case '1':
                case '*':
                case '>':
                case '=':{
                    key = 0b1111111111111111;
                    break;
                }
                case 'a':{
                    key = 0b1111111100000000;
                    break;
                }
                case 'b':{
                    key = 0b1111000011110000;
                    break;
                }
                case 'c':{
                    key = 0b1100110011001100;
                    break;
                }
                case 'd':{
                    key = 0b1010101010101010;
                    break;
                }
                default:{
                    wrong_value();
                }
            }
            number_of_variables=n;
            value = v;
        }
        Tree(char v, Tree* child, unsigned n=4){     
            switch (v){
                case '0':
                case '1':
                case 'a':
                case 'b':
                case 'c':
                case 'd':{
                    cant_have_children();
                }
                case '!':{
                    key = get_opposite_key(child->get_key(), n);
                    break;
                }
                case '*':
                case '+':
                case '>':
                case '=':{
                    key = child->get_key();
                    break;
                }
                default:{
                    wrong_value();
                }
            }
            number_of_variables=n;
            number_of_children = 1;
            children.push_back(child);
            value = v;
        }
        Tree(char v, Tree* child1, Tree* child2, unsigned n=4){
            cout<<'@'<<endl;
            switch(v){
                case '0':
                case '1':
                case 'a':
                case 'b':
                case 'c':
                case 'd':{
                    cant_have_children();
                }
                case '!':{
                    too_many_children();
                }
                case '*':{
                    key = child1->get_key() & child2->get_key();
                    break;
                }
                case '+':{
                    key = child1->get_key() | child2->get_key();
                    break;
                }
                case '>':{
                    key = get_opposite_key(child1->get_key(), n) | child2->get_key();
                    break;
                }
                case '=':{
                    key = (child1->get_key() & child2->get_key()) | (get_opposite_key(child1->get_key(), n) & get_opposite_key(child2->get_key(),n));
                    break;
                }
                default:{
                    wrong_value();
                }
            }
            number_of_variables=n;
            value = v;
            number_of_children = 2;
            children.push_back(child1);
            children.push_back(child2);
        }
        string print(){//Позволяет получить выражение, хранящиеся в дереве, в понятном виде
            switch(value){
                case '0':
                case '1':
                case 'a':
                case 'b':
                case 'c':
                case 'd':{
                    return string(1, value);
                }
                case '!':{
                    return "!"+children[0]->print();
                }
                case '*':
                case '+':
                case '>':
                case '=':{
                    string ret = "";
                    ret+=children[0]->print();
                    for (int i=1; i<number_of_children; i++){
                        ret+=value+children[i]->print();
                    }
                    if (number_of_children == 1){
                        return ret;
                    }
                    return "("+ret+")";
                }
                default:{
                    something_wrong();
                    return "";
                }
            }           
        }
        bool optimize(){//Оптимизация дерева
            switch(value){
                case '0':
                case 'a':
                case 'b':
                case 'c':
                case 'd':{//Значит вершина - просто переменная или 0 или 1, ее уже никак не упростить
                    return false;
                }
                case '!':{
                    if(number_of_children>0){
                        children[0]->optimize();
                    }
                    if(number_of_children = 0){
                        to_null();
                        return true;
                    }
                    if(children[0]->get_value() == '!'){
                        value = children[0]->children[0]->get_value();
                        key = children[0]->children[0]->get_key();
                        for(int ind_child = 0; ind_child < children[0]->children[0]->get_number_of_children(); ind_child++){
                            add_child(children[0]->children[0]->get_child(ind_child));
                        }
                        delete children[0]->children[0];
                        delete_child(0);
                    }
                    break;
                }
                case '*':{
                    for(auto child: children){
                        child->optimize();
                    }
                    if(number_of_children==0){
                        to_null();
                        return true;
                    }
                    if(number_of_children==1){
                        value = children[0]->get_value();
                        key = children[0]->get_key();
                        for(int ind_child = 0; ind_child < children[0]->get_number_of_children(); ind_child++){
                            add_child(children[0]->get_child(ind_child));
                        }
                        delete_child(0);
                        return true;
                    }
                    set <int> keys_found;//Храним ключи, которые уже встречались
                    for(int i = number_of_children-1; i>=0; i--){//Идем справа нелево, чтобы индексы элементов, которые будем брать дальше, не менялись
                        if(children[i]->get_value() == '*'){//Используем правило A*(B*C)=A*B*C
                            number_of_children--;
                            for(int grand_child=0; grand_child<children[i]->get_number_of_children(); grand_child++){
                                if(not(keys_found.find(children[i]->get_child(grand_child)->get_key())!=keys_found.end() || children[i]->get_child(grand_child)->get_key() == 0b1111111111111111)){//Убираем A*A=A и A*1=A
                                    if(keys_found.find(get_opposite_key(children[i]->get_key(), number_of_variables))!=keys_found.end() or children[i]->get_key() == 0){
                                        to_null();
                                        return true;
                                    }
                                    keys_found.insert(children[i]->get_child(grand_child)->get_key());
                                    number_of_children++;
                                    children.push_back(children[i]->get_child(grand_child));
                                }
                            }
                            delete_child(i);
                            continue;
                        }
                        if(keys_found.find(children[i]->get_key())!=keys_found.end() || children[i]->get_key() == 0b1111111111111111){//Убираем A*A=A и A*1=A
                            delete_child(i);
                        }
                        else{
                            if(keys_found.find(get_opposite_key(children[i]->get_key(), number_of_variables))!=keys_found.end() || children[i]->get_key() == 0){
                                to_null();
                                return true;
                            }
                            keys_found.insert(children[i]->get_key());
                        }
                    }
                    break; 
                }
                /*
                case '*':{
                    if(number_of_children==0){
                        to_null();
                        return true;
                    }
                    if(number_of_children==1){
                        value = children[0]->get_value();
                        key = children[0]->get_key();
                        for(int ind_child = 0; ind_child < children[0]->get_number_of_children(); ind_child++){
                            add_child(children[0]->get_child(ind_child));
                        }
                        delete children[0];
                        delete_child(0);
                    }
                    set <int> keys_found;//Храним ключи, которые уже встречались
                    for(int i = number_of_children-1; i>=0; i--){//Идем справа нелево, чтобы индексы элементов, которые будем брать дальше, не менялись
                        if(children[i]->get_value() == '*'){//Используем правило A*(B*C)=A*B*C
                            children[i]->optimize();
                            number_of_children--;
                            for(int grand_child=0; grand_child<children[i]->get_number_of_children(); grand_child++){
                                if(not(keys_found.find(children[i]->get_child(grand_child)->get_key())!=keys_found.end() || children[i]->get_child(grand_child)->get_key() == 0b1111111111111111)){//Убираем A*A=A и A*1=A
                                    if(keys_found.find(get_opposite_key(children[i]->get_key(), number_of_variables))!=keys_found.end() or children[i]->get_key() == 0){
                                        to_null();
                                        return true;
                                    }
                                    keys_found.insert(children[i]->get_child(grand_child)->get_key());
                                    number_of_children++;
                                    children[i]->get_child(grand_child)->optimize();//Оптимизируем уникальные поддеревья
                                    children.push_back(children[i]->get_child(grand_child));
                                }
                            }
                            delete_child(i);
                            continue;
                        }
                        if(keys_found.find(children[i]->get_key())!=keys_found.end() || children[i]->get_key() == 0b1111111111111111){//Убираем A*A=A и A*1=A
                            children.erase(children.begin()+i);
                            number_of_children --;
                        }
                        else{
                            if(keys_found.find(get_opposite_key(children[i]->get_key(), number_of_variables))!=keys_found.end() || children[i]->get_key() == 0){
                                to_null();
                                return true;
                            }
                            keys_found.insert(children[i]->get_key());
                            children[i]->optimize();//Оптимизируем уникальные поддеревья
                        }
                    }
                    break; 
                }
                */
                case '+':{
                    if(number_of_children==0){
                        to_null();
                        return true;
                    }
                    if(number_of_children==1){
                        value = children[0]->get_value();
                        key = children[0]->get_key();
                        for(int ind_child = 0; ind_child < children[0]->get_number_of_children(); ind_child++){
                            add_child(children[0]->get_child(ind_child));
                        }
                        delete_child(0);
                    }
                    set <int> keys_found;//Храним ключи, которые уже встречались
                    for(int i = number_of_children-1; i>=0; i--){
                        if(children[i]->get_value() == '+'){//Используем правило A+(B+C)=A+B+C
                            children[i]->optimize();
                            number_of_children--;
                            for(int grand_child=0; grand_child<children[i]->get_number_of_children(); grand_child++){
                               if(not(keys_found.find(children[i]->get_key())!=keys_found.end() || children[i]->get_key() == 0)){//Убираем A+A=A и A+0=A
                                    if(keys_found.find(get_opposite_key(children[i]->get_child(grand_child)->get_key(), number_of_variables))!=keys_found.end() || children[i]->get_child(grand_child)->get_key() == 0b1111111111111111){
                                        to_one();
                                        return true;
                                }
                                    keys_found.insert(children[i]->get_child(grand_child)->get_key());
                                    number_of_children++;
                                    children[i]->get_child(grand_child)->optimize();//Оптимизируем уникальные поддеревья
                                    children.push_back(children[i]->get_child(grand_child));
                               }
                            }
                            delete_child(i);
                            continue;
                        }
                        if(keys_found.find(children[i]->get_key())!=keys_found.end() or children[i]->get_key() == 0){//Убираем A+A=A и A+0=A
                            children.erase(children.begin()+i);
                            number_of_children --;
                        }
                        else{
                            if(keys_found.find(get_opposite_key(children[i]->get_key(), number_of_variables))!=keys_found.end() or  children[i]->get_key() == 0b1111111111111111){
                                to_one();
                                return true;
                            }
                            keys_found.insert(children[i]->get_key());
                            children[i]->optimize();//Оптимизируем уникальные поддеревья
                        }
                    }
                    break;
                }
                case '>':
                case '=':{
                    if(number_of_children==0){
                        to_null();
                        return true;
                    }
                    if(number_of_children==1){
                        value = children[0]->get_value();
                        key = children[0]->get_key();
                        for(int ind_child = 0; ind_child < children[0]->get_number_of_children(); ind_child++){
                            add_child(children[0]->get_child(ind_child));
                        }
                        delete_child(0);
                    }
                    children[0]->optimize();
                    children[1]->optimize();
                    break; 
                }
                default:{
                    something_wrong();
                }
                return true;
            }
            return true;
        }
        void to_null(){//Превращает вершину в 0
            value = '0';
            number_of_children = 0;
            children.clear();
            key = 0;
        }
        void to_one(){//Превращает вершину в 1
            value = '1';
            number_of_children = 0;
            children.clear();
            key = 0b1111111111111111;
        }
    private:
        char value = '+'; //Значение, хранящиеся в узле
        /*
        Значение   Что значит
        0          0
        1          1
        [2-5]      переменная (a, b, c или d)
        [6-10]     операции [не, и, или, импликация, эквивалент]
        
        То есть, значени может быть в диапазоне [0, 10]
        Если в узле лежит переменная, то у нее не может быть детей
        */
        unsigned number_of_children = 0; //Количество детей у узла
        vector<Tree*> children; //Храним указатели на вершины детей
        unsigned key = 0; //Ключ, по умолчанию всё 0
        unsigned number_of_variables = 0;
};

void make_dnf()//Ввод ДНФ, запись его в файл
{
    int n;
    cout<<"Начат ввод ДНФ"<<endl<<"Введите кол-во элементарных конъюкций в ДНФ: ";
    cin>>n;
    ofstream fout("dnf.txt");
    int resp = 0;
    cout<<"Коэфиценты могут принимать значения 0, 1 и -1."<<endl;
    for(int i=0; i<n; i++){
        cout<<"Введите по очереди индексы в элементарной конъюкции №"<<i<<endl;
        for(int x=0; x<4; x++){
            do{
                cout<<"Коэффицент №"<<x<<": ";
                cin>>resp;
            } while(resp<-1 or resp>1);
            switch(resp){
                case 0:{
                    fout<<0;
                    break;
                }
                case 1:{
                    fout<<1;
                    break;
                }
                case -1:{
                    fout<<2;
                }
            }
            /*
            Справка: 
            0 означает, что переменной нет,
            1 - что она есть с положительным коэффицентом,
            2 - что она есть с отрицательным коэффицентом
            */
        }
        fout<<endl;
    }
    fout.close();
}
bool make_tree_from_dnf(Tree* tree){//Из ДНФ из файла делает дерево
    if(tree->get_number_of_children()!=0 or tree->get_key()!=0){
        tree->to_null();
    }
    if(tree->get_value() != '+'){
        tree->set_value('+');
    }
    string elem_kon;//Одна строчка из файла или одна элементарная коньюкция
    ifstream fin("dnf.txt");
    Tree *node; //Дерево из элементарной коньюкции, которое будем присоединять к t
    Tree * not_elem; //Дерево с отрицанием, которое входит в элементарную коньюкцию
    while(getline(fin, elem_kon)){
        node = new Tree('*');
        for(int i=0; i<4; i++){
            switch(elem_kon[i]){
                case '1':{
                    node->add_child( new Tree(simbols[i]));
                    break;
                }
                case '2':{
                    node->add_child(new Tree('!', new Tree(simbols[i])));
                    break;
                }
            }
        }
        if(node->get_number_of_children()==1){//Если в элементарной коньюкции один элемент, добавим только его
            tree->add_child(node->get_child(0));
        }
        else{
            tree->add_child(node);
        }
    }
    fin.close();
    return true;
}

//Тесты

void test_degree_of_two(){//Тесты для функции по получению степеней двойки 
    assert(degree_of_two(0) == 1);
    assert(degree_of_two(1) == 2);
    assert(degree_of_two(2) == 4);
    assert(degree_of_two(3) == 8);
    assert(degree_of_two(4) == 16);
    assert(degree_of_two(5) == 32);
    assert(degree_of_two(6) == 64);
    assert(degree_of_two(7) == 128);
    assert(degree_of_two(8) == 256);
    assert(degree_of_two(9) == 512);
    assert(degree_of_two(10) == 1024);
}

int main()
{
    
    //Тест работы с ДНФ
    //make_dnf();
    Tree t;
    make_tree_from_dnf(&t);
    bitset <16> x(t.get_key());
    cout<<"Получившаяся ДНФ: "<<t.print()<<endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<endl<<"Знаение в вершине до оптимизации: "<<t.get_value()<<endl;
    
    t.optimize();
    cout<<"Оптимизированный ДНФ: "<<t.print()<<endl<<"Знаение в вершине после оптимизации: "<<t.get_value()<<endl;
    return 0;
}