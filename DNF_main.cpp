#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
#include <list>
#include <map>
#include <set>
using namespace std;
/*
Дано - дерево, обозначающее ДНФ
Результат - сбалансированное дерево
Шаги:
1) Преобразовать таблицу ДНФ в дерево
2) По правилам сократить количество вершин
Ключ вершины - это результаты функции при всех возможных переменных, то есть последний столбец в таблице истиности
*/
string get_opposite_key(string key){//По ключу находим его обратный. То есть, заменяем 0 на 1, 1 на 0
    string ret;
    for(int i=0; i<16; i++){
        if(key[i] == '0'){
            ret+='1';
        }
        else{
            ret+='0';
        }
    }
    return ret;
}
char simbols [11] = {'0', '1', 'a', 'b', 'c', 'd', '!', '*', '+', '>', '='};//Все возможные значения в вершине
class Tree{
    public:
        string get_key(){ //
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
            if(n<0 or n>=n_children){
                cout<<n<<' '<<n_children<<endl;
                cout<<"Ошибка: Такого ребенка нет"<<endl;
            }
            return children[n];
        }
        int get_n(){//Возвращает количество детей у вершины
            return n_children;
        }
        void set_value(int v){//Позволяет установить значение в вершине
            value = v;
        }
        int get_value(){//Позволяет получить значение, установленное в вершине
            return value;
        }
        bool add_child(Tree * t){//Позволяет добавить ребенка вершине
            if (value < 6){
                cout<<"Ошибка: Нельзя добавить детей переменной"<<endl;
                return false;
            }
            if (value == 6 and n_children >0){
                cout<<"Ошибка: У операции отрицания может быть только 1 ребенок"<<endl;
                return false;
            }
            if (value == 10 and n_children == 2){
                cout<<"Ошибка: У операции эквивалентности может быть максимум 2 ребенка"<<endl;
                return false;
            }
            
            n_children ++;
            children.push_back(t);
            switch(value){
                case 6:{//Работаем с отрицанием
                    key = t->get_key();
                    for(int i = 0; i<16; i++){
                        if(key[i] =='0'){
                            key[i] = '1';
                        }
                        else{
                            key[i] = '0';
                        }
                    }
                    break;
                }
                case 7:{//Работаем с умножением (И)
                    string child_key = t->get_key();
                    for(int i=0; i<16; i++){
                        if(child_key[i]=='1' and key[i]=='1'){
                            key[i] = '1';
                        }
                        else{
                            key[i] = '0';
                        }
                    }
                    break;
                }
                case 8:{//Работаем с суммой (ИЛИ)
                    string child_key = t->get_key();
                    for(int i=0; i<16; i++){
                        if(child_key[i]=='1' or key[i]=='1'){
                            key[i] = '1';
                        }
                        else{
                            key[i] = '0';
                        }
                    }
                    break;
                }
                case 9:{//Работаем с импликацией (->)
                    string child_key = t->get_key();
                    for(int i=0; i<16; i++){
                        if(child_key[i]=='0' and key[i]=='1'){
                            key[i] = '0';
                        }
                        else{
                            key[i] = '1';
                        }
                    }
                    break;
                }
                case 10:{//Работаем с эквивалентностью (==)
                    string child_key = t->get_key();
                    for(int i=0; i<16; i++){
                        if(child_key[i]==key[i]){
                            key[i] = '1';
                        }
                        else{
                            key[i] = '0';
                        }
                    }
                    break;
                }
            }
            return true;
        }
        Tree(){value=8;}//По умолчанию величина в вершине равна 8, то есть по умолчанию стоит операция суммы
        Tree(int v){
            if(v<0 or v>10){
                cout<<"Ошибка: величина не может быть такой";
                exit(1);
            }
            value = v;
            switch(v){
                case 0:{
                    key = string(16, '0');
                    break;
                }
                case 2:{
                    key = string(8, '0')+string(8, '1');
                    break;
                }
                case 3:{
                    key = (string(4, '0')+string(4, '1'))+(string(4, '0')+string(4, '1'));
                    break;
                }
                case 4:{
                    key = "";
                    for (int i = 0; i<4; i++){
                        key += string(2, '0')+string(2, '1');
                    }
                    break;
                }
                case 5:{
                    key = "";
                    for(int i = 0; i<8; i++){
                        key += "01";
                    }
                    break;
                }
                case 8:{
                    key = string(16, '0');
                    break;
                }
                default:{
                    key = string(16, '1');
                    break;
                }
            }
        }
        Tree(int v, Tree* child){
            if(v<0 or v>10){
                cout<<"Ошибка: не может быть такой величины";
                exit(1);
            }
            if(v<6){
                 cout<<"Ошибка: у переменных не может быть детей";
                exit(1);
            }
            n_children = 1;
            children.push_back(child);
            value = v;
            key = child->get_key();
            if(v == 6){
                for(int i = 0; i<16; i++){
                    if(key[i] =='0'){
                        key[i] = '1';
                    }
                    else{
                        key[i] = '0';
                    }
                }
            number_of_children = 1;
            children.push_back(child);
            value = v;
        }
        Tree(int v, Tree* child1, Tree* child2){
            if(v<0 or v>10){
                cout<<"Ошибка: не может быть такой величины";
                exit(1);
            }
            if(v<6){
                 cout<<"Ошибка: у переменных не может быть детей";
                exit(1);
            }
            if(v==6){
                 cout<<"Ошибка: у операции отрицания может быть только один ребенок";
                exit(1);
            }
            value = v;
            n_children = 2;
            children.push_back(child1);
            children.push_back(child2);
            string child1_key = child1->get_key();
            string child2_key = child2->get_key();
            switch(v){
                case 7:{//Работаем с умножением (И)
                    for(int i = 0; i<16; i++){
                        if(child1_key[i] == '1' and child2_key[i] == '1'){
                            key[i] = '1';
                        }
                    }
                    break;
                }
                case 8:{//Работаем с суммой (ИЛИ)
                    for(int i = 0; i<16; i++){
                        if(child1_key[i] == '1' or child2_key[i] == '1'){
                            key[i] = '1';
                        }
                    }
                    break;
                }
                case 9:{//Работаем с импликацией (->)
                    for(int i = 0; i<16; i++){
                        if(not(child1_key[i] == '1' and child2_key[i] == '0')){
                            key[i] = '1';
                        }
                    }
                    break;
                }
                case 10:{//Работаем с эквивалентностью (==)
                    for(int i = 0; i<16; i++){
                        if(child1_key[i] == child2_key[i]){
                            key[i] = '1';
                        }
                    }
                    break;
                }
            }
        }
        string print(){//Позволяет получить выражение, хранящиеся в дереве, в понятном виде
            if(value < 6){
                return string(1, simbols[value]);
            }
            else{
                if(value == 6){
                    return "!"+children[0]->print();
                }
                else{
                    string ret = "";
                    ret+=children[0]->print();
                    for (int i=1; i<n_children; i++){
                        ret+=simbols[value]+children[i]->print();
                    }
                    if (n_children == 1){
                        return ret;
                    }
                    return "("+ret+")";
                }
            }
                
        }
        bool optimize(){//Оптимизация дерева
            if (value < 6){ //Значит вершина - просто переменная или 0 или 1, ее уже никак не упростить
                return false;
            }
            if (value == 6){ //Значит вершина - операция отрицания
                if(n_children == 0){
                    return false;
                }
                if(children[0]->get_value() == 6){//Убираем множественное отрицание
                    Tree *node = children[0];
                    int not_count = 1;//Считаем, сколько раз встречалось отрицание
                    do{
                        not_count ++;
                        node = node->get_child(0);
                    } while(node->get_value() == 6);
                    if (not_count%2){ //Если число операций отрицания нечетно, можно заменить их на одну операцию отрицания
                        children[0] = new Tree(6, node);
                    }
                    else{//Если число операций отрицания четно, это эквивалентно отсутствию отрицания.
                        value = node->get_value();
                        n_children = node->get_n();
                        children.clear();
                        for(int i=0; i<n_children; i++){
                            add_child(node->get_child(i));
                        }
                        key = node->get_key();
                        children[0] = node;
                    }
                    return true;
                }
                return children[0]->optimize();
            }
            //Если дошли до сюда, значит мы имеем дело с И, ИЛИ, Импликацией или Эквивалентностью. То есть у операции может быть несколько детей
            if(n_children > 1){ 
                switch(value){
                    case 7:{//Работаем с умножением (И)
                        set <string> keys_found;//Храним ключи, которые уже встречались
                        for(int i = n_children-1; i>=0; i--){//Идем справа нелево, чтобы индексы элементов, которые будем брать дальше, не менялись
                            if(children[i]->get_value() == 7){//Используем правило A*(B*C)=A*B*C
                                children[i]->optimize();
                                n_children--;
                                for(int grand_child=0; grand_child<children[i]->get_n(); grand_child++){
                                    if(not(keys_found.contains(children[i]->get_child(grand_child)->get_key()) or children[i]->get_child(grand_child)->get_key() == string(16, '1'))){//Убираем A*A=A и A*1=A
                                        if(keys_found.contains(get_opposite_key(children[i]->get_key())) or children[i]->get_key() == string(16, '0')){
                                            to_null();
                                            return true;
                                        }
                                        keys_found.insert(children[i]->get_child(grand_child)->get_key());
                                        n_children++;
                                        children[i]->get_child(grand_child)->optimize();//Оптимизируем уникальные поддеревья
                                        children.push_back(children[i]->get_child(grand_child));
                                    }
                                }
                                children.erase(children.begin()+i);
                                continue;
                            }
                            if(keys_found.contains(children[i]->get_key()) or children[i]->get_key() == string(16, '1')){//Убираем A*A=A и A*1=A
                                children.erase(children.begin()+i);
                                n_children --;
                            }
                            else{
                                if(keys_found.contains(get_opposite_key(children[i]->get_key())) or children[i]->get_key() == string(16, '0')){
                                    to_null();
                                    return true;
                                }
                                keys_found.insert(children[i]->get_key());
                                children[i]->optimize();//Оптимизируем уникальные поддеревья
                            }
                        }
                        break;  
                    }
                    case 8:{//Работаем с суммой (ИЛИ)
                        set <string> keys_found;//Храним ключи, которые уже встречались
                        for(int i = n_children-1; i>=0; i--){
                            if(children[i]->get_value() == 8){//Используем правило A+(B+C)=A+B+C
                                children[i]->optimize();
                                n_children--;
                                for(int grand_child=0; grand_child<children[i]->get_n(); grand_child++){
                                   if(not(keys_found.contains(children[i]->get_key()) or children[i]->get_key() == string(16, '0'))){//Убираем A+A=A и A+0=A
                                        if(keys_found.contains(get_opposite_key(children[i]->get_child(grand_child)->get_key())) or  children[i]->get_child(grand_child)->get_key() == string(16, '1')){
                                            to_one();
                                            return true;
                                        }
                                        keys_found.insert(children[i]->get_child(grand_child)->get_key());
                                        n_children++;
                                        children[i]->get_child(grand_child)->optimize();//Оптимизируем уникальные поддеревья
                                        children.push_back(children[i]->get_child(grand_child));
                                   }
                                }
                                children.erase(children.begin()+i);
                                continue;
                            }
                            if(keys_found.contains(children[i]->get_key()) or children[i]->get_key() == string(16, '0')){//Убираем A+A=A и A+0=A
                                children.erase(children.begin()+i);
                                n_children --;
                            }
                            else{
                                if(keys_found.contains(get_opposite_key(children[i]->get_key())) or  children[i]->get_key() == string(16, '1')){
                                    to_one();
                                    return true;
                                }
                                keys_found.insert(children[i]->get_key());
                                children[i]->optimize();//Оптимизируем уникальные поддеревья
                            }
                        }
                        break;  
                    }
                    case 9:{//Работаем с импликацией (->)
                        children[0]->optimize();
                        children[1]->optimize();
                        break;  
                    }
                    case 10:{//Работаем с эквивалентностью (==)
                        children[0]->optimize();
                        children[1]->optimize();
                        return true;
                    }
                }
                return true;
            }
            if(n_children == 0){//Заменяем на 0
                to_null();
                return true;
            }
            if(n_children == 1){//Заменяем на ребенка
                value = 8;
                for(int i=0; i<children[0]->get_n(); i++){
                    children.push_back(children[0]->get_child(i));
                }
                n_children = children[0]->get_n();
                value = children[0]->get_value();
                key = children[0]->get_key();
                children.erase(children.begin());
                return true;
            }
            return true;
        }
        void to_null(){//Превращает вершину в 0
            value = 0;
            n_children = 0;
            children.clear();
            key = string(16, '0');
        }
        void to_one(){//Превращает вершину в 1
            value = 1;
            n_children = 0;
            children.clear();
            key = string(16, '1');
        }
    private:
        int value; //Значение, хранящиеся в узле
        /*
        Значение   Что значит
        0          0
        1          1
        [2-5]      переменная (a, b, c или d)
        [6-10]     операции [не, и, или, импликация, эквивалент]
        
        То есть, значени может быть в диапазоне [0, 10]
        Если в узле лежит переменная, то у нее не может быть детей
        */
        int n_children = 0; //Количество детей у узла
        vector<Tree*> children; //Храним указатели на вершины детей
        string key = string(16, '0'); //Ключ, по умолчанию всё 0
};

bool equal_tree(Tree* t1, Tree* t2){ //Эквивалентны ли выражения. Сравниваем по ключу
    if(t1->get_key() == t2->get_key()){
        return true;
    }
    else{
        return false;
    }
}

bool oposite_tree(Tree* t1, Tree* t2){//Обратны ли выражения. Сравниваем по ключу
    string key1 = t1->get_key();
    string key2 = t2->get_key();
    for(int i=0; i<16; i++){
        if(key1[i]==key2[i]){
            return false;
        }
    }
    return true;
}

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
bool make_tree_from_dnf(Tree* t){//Из ДНФ из файла делает дерево
    if(t->get_n()!=0 or t->get_key()!=string(16, '0')){
        t->to_null();
    }
    if(t->get_value() != 8){
        t->set_value(8);
    }
    string elem_kon;//Одна строчка из файла или одна элементарная коньюкция
    ifstream fin("dnf.txt");
    Tree *node; //Дерево из элементарной коньюкции, которое будем присоединять к t
    Tree * not_elem; //Дерево с отрицанием, которое входит в элементарную коньюкцию
    while(getline(fin, elem_kon)){
        node = new Tree(7);
        for(int i=0; i<4; i++){
            switch(elem_kon[i]){
                case '1':{
                    node->add_child(new Tree(i+2));
                    break;
                }
                case '2':{
                    node->add_child(new Tree(6, new Tree(i+2)));
                    break;
                }
            }
        }
        if(node->get_n()==1){//Если в элементарной коньюкции один элемент, добавим только его
            t->add_child(node->get_child(0));
        }
        else{
            t->add_child(node);
        }
    }
    fin.close();
    return true;
}
int main()
{
    /*
    //Тест работы с ДНФ
    make_dnf();
    Tree t;
    make_tree_from_dnf(&t);
    cout<<"Получившаяся ДНФ: "<<t.print()<<endl<<"Ключ дерева: "<<t.get_key()<<endl<<"Знаение в вершине до оптимизации: "<<t.get_value()<<endl;
    
    t.optimize();
    cout<<"Оптимизированный ДНФ: "<<t.print()<<endl<<"Знаение в вершине после оптимизации: "<<t.get_value()<<endl;
    */
    
    /*
    //Пример оптимизации дерева
    Tree t = Tree(7, new Tree(2), new Tree(7, new Tree(3), new Tree(7, new Tree(4), new Tree(5))));
    cout<<"Дерево до оптимизации: "<<t.print()<<endl;
    t.optimize();
    cout<<"Дерево после оптимизации: "<<t.print()<<endl;
    cout<<"Ключ дерева: "<<t.get_key()<<endl;
    */
    
    /*
    //Пример работы с разными деревьями
    Tree a = Tree(2); //Дерево a
    Tree b = Tree(3); //Дерево b
    Tree c = Tree(4); //Дерево c
    Tree d = Tree(5); //Дерево d
    Tree n1 = Tree(6, new Tree(2)); //Дерево НЕ(a)
    Tree n2 = Tree(6, new Tree(3)); //Дерево НЕ(b)
    Tree n3 = Tree(6, new Tree(4)); //Дерево НЕ(c)
    Tree n4 = Tree(6, new Tree(5)); //Дерево НЕ(d)
    Tree nn1 = Tree(6, new Tree(6, new Tree(2))); //Дерево НЕ(НЕ(a))
    Tree nn2 = Tree(6, new Tree(6, new Tree(3))); //Дерево НЕ(НЕ(b))
    Tree nn3 = Tree(6, new Tree(6, new Tree(4))); //Дерево НЕ(НЕ(c))
    Tree nn4 = Tree(6, new Tree(6, new Tree(5))); //Дерево НЕ(НЕ(d))
    Tree qnn1 = Tree(7, new Tree(6, new Tree(2)), new Tree(2)); //Дерево НЕ(a) И a
    Tree qnn2 = Tree(7, new Tree(6, new Tree(3)), new Tree(3)); //Дерево НЕ(b) И b
    Tree qnn3 = Tree(7, new Tree(6, new Tree(4)), new Tree(4)); //Дерево НЕ(c) И c
    Tree qnn4 = Tree(7, new Tree(6, new Tree(5)), new Tree(5)); //Дерево НЕ(d) И d
    
    cout<<"Дерево a: "<<a.print()<<endl<<"Дерево b: "<<b.print()<<endl<<"Дерево c: "<<c.print()<<endl<<"Дерево d: "<<d.print()<<endl;
    cout<<"Дерево НЕ(a): "<<n1.print()<<endl<<"Дерево НЕ(b): "<<n2.print()<<endl<<"Дерево НЕ(c): "<<n3.print()<<endl<<"Дерево НЕ(d): "<<n4.print()<<endl;
    cout<<"Дерево НЕ(НЕ(a)): "<<nn1.print()<<endl<<"Дерево НЕ(НЕ(b)): "<<nn2.print()<<endl<<"Дерево НЕ(НЕ(c)): "<<nn3.print()<<endl<<"Дерево НЕ(НЕ(d)): "<<nn4.print()<<endl;
    cout<<"Дерево НЕ(a) И a: "<<qnn1.print()<<endl<<"Дерево НЕ(b) И b: "<<qnn2.print()<<endl<<"Дерево НЕ(c) И c: "<<qnn3.print()<<endl<<"Дерево НЕ(d) И d: "<<qnn4.print()<<endl;
    
    cout<<"Оптимизируем  все деревья"<<endl;
    a.optimize();
    b.optimize();
    c.optimize();
    d.optimize();
    n1.optimize();
    n2.optimize();
    n3.optimize();
    n4.optimize();
    nn1.optimize();
    nn2.optimize();
    nn3.optimize();
    nn4.optimize();
    qnn1.optimize();
    qnn2.optimize();
    qnn3.optimize();
    qnn4.optimize();
    
    cout<<"Дерево a: "<<a.print()<<endl<<"Дерево b: "<<b.print()<<endl<<"Дерево c: "<<c.print()<<endl<<"Дерево d: "<<d.print()<<endl;
    cout<<"Дерево НЕ(a): "<<n1.print()<<endl<<"Дерево НЕ(b): "<<n2.print()<<endl<<"Дерево НЕ(c): "<<n3.print()<<endl<<"Дерево НЕ(d): "<<n4.print()<<endl;
    cout<<"Дерево НЕ(НЕ(a)): "<<nn1.print()<<endl<<"Дерево НЕ(НЕ(b)): "<<nn2.print()<<endl<<"Дерево НЕ(НЕ(c)): "<<nn3.print()<<endl<<"Дерево НЕ(НЕ(d)): "<<nn4.print()<<endl;
    cout<<"Дерево НЕ(a) И a: "<<qnn1.print()<<endl<<"Дерево НЕ(b) И b: "<<qnn2.print()<<endl<<"Дерево НЕ(c) И c: "<<qnn3.print()<<endl<<"Дерево НЕ(d) И d: "<<qnn4.print()<<endl;
    
    cout<<endl<<"Равны ли деревья"<<endl;
    cout<<"Дерево a и Дерево a: "<<equal_tree(&a, &a)<<endl;
    cout<<"Дерево b и Дерево b: "<<equal_tree(&b, &b)<<endl;
    cout<<"Дерево c и Дерево c: "<<equal_tree(&c, &c)<<endl;
    cout<<"Дерево d и Дерево d: "<<equal_tree(&d, &d)<<endl;
    cout<<"Дерево a и Дерево НЕ(НЕ(a)): "<<equal_tree(&a, &nn1)<<endl;
    cout<<"Дерево b и Дерево НЕ(НЕ(b)): "<<equal_tree(&b, &nn2)<<endl;
    cout<<"Дерево c и Дерево НЕ(НЕ(c)): "<<equal_tree(&c, &nn3)<<endl;
    cout<<"Дерево d и Дерево НЕ(НЕ(d)): "<<equal_tree(&d, &nn4)<<endl;
    cout<<"Дерево a и Дерево НЕ(a) И a: "<<equal_tree(&a, &qnn1)<<endl;
    cout<<"Дерево b и Дерево НЕ(b): "<<equal_tree(&b, &n2)<<endl;
    cout<<"Дерево c и Дерево d: "<<equal_tree(&c, &d)<<endl;
    cout<<"Дерево d и Дерево НЕ(НЕ(a)): "<<equal_tree(&d, &nn1)<<endl;
    
    cout<<endl<<"Обратны ли деревья"<<endl;
    cout<<"Дерево a и Дерево НЕ(a): "<<oposite_tree(&a, &n1)<<endl;
    cout<<"Дерево b и Дерево НЕ(b): "<<oposite_tree(&b, &n2)<<endl;
    cout<<"Дерево c и Дерево НЕ(c): "<<oposite_tree(&c, &n3)<<endl;
    cout<<"Дерево d и Дерево НЕ(d): "<<oposite_tree(&d, &n4)<<endl;
    cout<<"Дерево a и Дерево НЕ(НЕ(a)): "<<oposite_tree(&a, &nn1)<<endl;
    cout<<"Дерево b и Дерево НЕ(НЕ(b)): "<<oposite_tree(&b, &nn2)<<endl;
    cout<<"Дерево c и Дерево НЕ(НЕ(c)): "<<oposite_tree(&c, &nn3)<<endl;
    cout<<"Дерево d и Дерево НЕ(НЕ(d)): "<<oposite_tree(&d, &nn4)<<endl;
    cout<<"Дерево a и Дерево НЕ(a) И a: "<<oposite_tree(&a, &qnn1)<<endl;
    cout<<"Дерево b и Дерево b: "<<oposite_tree(&b, &b)<<endl;
    cout<<"Дерево c и Дерево d: "<<oposite_tree(&c, &d)<<endl;
    cout<<"Дерево d и Дерево НЕ(НЕ(a)): "<<oposite_tree(&d, &nn1)<<endl;
    */
    return 0;
}