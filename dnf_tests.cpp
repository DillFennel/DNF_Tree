#include "dnf_tests.h"
#include <iostream>
#include "dnf_tree.h"
#include <cassert>
#include <bitset>

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
    std::cout<<"Тесты степеней двойки пройдены"<<std::endl;
}
void test_dnf(){ //Тест работы с ДНФ
    make_dnf();
    Tree t;
    make_tree_from_dnf(&t);
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
}
 
void test_two_not(){ //Тест работы с ДНФ - Два отрицания
    Tree t('!', new Tree('!', new Tree('a')));
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::bitset <16> y(t.get_key());
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<y<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
} 
void test_three_not(){ //Тест работы с ДНФ - Три отрицания
    Tree t('!', new Tree('!', new Tree('!', new Tree('a'))));
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::bitset <16> y(t.get_key());
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<y<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
}

void test_three_inversions_2(){ //Тест работы с ДНФ - Тест с тройной инверсией 2
    Tree t('!', new Tree('!', new Tree('!', new Tree('+', new Tree('a'), new Tree('b')))));
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::bitset <16> y(t.get_key());
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<y<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
}
void test_three_inversions_3(){ //Тест работы с ДНФ - Тест с тройной инверсией 3
    Tree t('!', new Tree('!', new Tree('!', new Tree('*', new Tree('a'), new Tree('b')))));
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::bitset <16> y(t.get_key());
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<y<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
}
void test_three_inversions_4(){ //Тест работы с ДНФ - Тест с тройной инверсией 4
    Tree t('!', new Tree('!', new Tree('!', new Tree('*', new Tree('a'), new Tree('+', new Tree('b'), new Tree('c'))))));
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::bitset <16> y(t.get_key());
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<y<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
} 
void test_three_inversions_5(){ //Тест работы с ДНФ - Тест с тройной инверсией 5
    Tree t('!', new Tree('!', new Tree('!', new Tree('*', new Tree('a'), new Tree('+', new Tree('b'), new Tree('b'))))));
    std::bitset <16> x(t.get_key());
    std::cout<<"Получившаяся ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<x<<std::endl<<"Значение в вершине до оптимизации: "<<t.get_value()<<std::endl;
    t.optimize();
    std::bitset <16> y(t.get_key());
    std::cout<<"Оптимизированный ДНФ: "<<t.print()<<std::endl<<"Ключ дерева: "<<t.get_key()<<" : "<<y<<std::endl<<"Значение в вершине после оптимизации: "<<t.get_value()<<std::endl;
}

void test_tree_optimization(){ //Пример оптимизации дерева
    Tree t = Tree('+', new Tree('a'), new Tree('+', new Tree('b'), new Tree('+', new Tree('c'), new Tree('d'))));
    std::cout<<"Дерево до оптимизации: "<<t.print()<<std::endl;
    t.optimize();
    std::cout<<"Дерево после оптимизации: "<<t.print()<<std::endl;
    std::bitset <16> x(t.get_key());
    std::cout<<"Ключ дерева: "<<t.get_key()<<" или "<<x<<std::endl;
}

void test_many(){ //Пример работы с разными деревьями
    Tree a = Tree('a'); //Дерево a
    Tree b = Tree('b'); //Дерево b
    Tree c = Tree('c'); //Дерево c
    Tree d = Tree('d'); //Дерево d
    Tree not_a = Tree('!', new Tree('a')); //Дерево НЕ(a)
    Tree not_b = Tree('!', new Tree('b')); //Дерево НЕ(b)
    Tree not_c = Tree('!', new Tree('c')); //Дерево НЕ(c)
    Tree not_d = Tree('!', new Tree('d')); //Дерево НЕ(d)
    Tree not_not_a = Tree('!', new Tree('!', new Tree('a'))); //Дерево НЕ(НЕ(a))
    Tree not_not_b = Tree('!', new Tree('!', new Tree('b'))); //Дерево НЕ(НЕ(b))
    Tree not_not_c = Tree('!', new Tree('!', new Tree('c'))); //Дерево НЕ(НЕ(c))
    Tree not_not_d = Tree('!', new Tree('!', new Tree('d'))); //Дерево НЕ(НЕ(d))
    Tree qnn1 = Tree('*', new Tree('!', new Tree('a')), new Tree('a')); //Дерево НЕ(a) И a
    Tree qnn2 = Tree('*', new Tree('!', new Tree('b')), new Tree('b')); //Дерево НЕ(b) И b
    Tree qnn3 = Tree('*', new Tree('!', new Tree('c')), new Tree('c')); //Дерево НЕ(c) И c
    Tree qnn4 = Tree('*', new Tree('!', new Tree('d')), new Tree('d')); //Дерево НЕ(d) ИЛИ d
    Tree onn1 = Tree('+', new Tree('!', new Tree('a')), new Tree('a')); //Дерево НЕ(a) ИЛИ a
    Tree onn2 = Tree('+', new Tree('!', new Tree('b')), new Tree('b')); //Дерево НЕ(b) ИЛИ b
    Tree onn3 = Tree('+', new Tree('!', new Tree('c')), new Tree('c')); //Дерево НЕ(c) ИЛИ c
    Tree onn4 = Tree('+', new Tree('!', new Tree('d')), new Tree('d')); //Дерево НЕ(d) ИЛИ d
    
    std::cout<<"Дерево a: "<<a.print()<<std::endl<<"Дерево b: "<<b.print()<<std::endl<<"Дерево c: "<<c.print()<<std::endl<<"Дерево d: "<<d.print()<<std::endl;
    std::cout<<"Дерево НЕ(a): "<<n1.print()<<std::endl<<"Дерево НЕ(b): "<<n2.print()<<std::endl<<"Дерево НЕ(c): "<<n3.print()<<std::endl<<"Дерево НЕ(d): "<<n4.print()<<std::endl;
    std::cout<<"Дерево НЕ(НЕ(a)): "<<nn1.print()<<std::endl<<"Дерево НЕ(НЕ(b)): "<<nn2.print()<<std::endl<<"Дерево НЕ(НЕ(c)): "<<nn3.print()<<std::endl<<"Дерево НЕ(НЕ(d)): "<<nn4.print()<<std::endl;
    std::cout<<"Дерево НЕ(a) И a: "<<qnn1.print()<<std::endl<<"Дерево НЕ(b) И b: "<<qnn2.print()<<std::endl<<"Дерево НЕ(c) И c: "<<qnn3.print()<<std::endl<<"Дерево НЕ(d) И d: "<<qnn4.print()<<std::endl;
    std::cout<<"Дерево НЕ(a) ИЛИ a: "<<onn1.print()<<std::endl<<"Дерево НЕ(b) ИЛИ b: "<<onn2.print()<<std::endl<<"Дерево НЕ(c) ИЛИ c: "<<onn3.print()<<std::endl<<"Дерево НЕ(d) ИЛИ d: "<<onn4.print()<<std::endl;
    assert(a.print()=="a" && "Проверка print(a)");
    assert(b.print()=="b" && "Проверка print(b)");
    assert(c.print()=="c" && "Проверка print(c)");
    assert(d.print()=="d" && "Проверка print(d)");
    assert(n1.print()=="!a" && "Проверка print(!a)");
    std::cout<<"Оптимизируем  все деревья"<<std::endl;
    a.optimize();
    b.optimizenn();
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
    onn1.optimize();
    onn2.optimize();
    onn3.optimize();
    onn4.optimize();
    
    std::cout<<"Дерево a: "<<a.print()<<std::endl<<"Дерево b: "<<b.print()<<std::endl<<"Дерево c: "<<c.print()<<std::endl<<"Дерево d: "<<d.print()<<std::endl;
    std::cout<<"Дерево НЕ(a): "<<n1.print()<<std::endl<<"Дерево НЕ(b): "<<n2.print()<<std::endl<<"Дерево НЕ(c): "<<n3.print()<<std::endl<<"Дерево НЕ(d): "<<n4.print()<<std::endl;
    std::cout<<"Дерево НЕ(НЕ(a)): "<<nn1.print()<<std::endl<<"Дерево НЕ(НЕ(b)): "<<nn2.print()<<std::endl<<"Дерево НЕ(НЕ(c)): "<<nn3.print()<<std::endl<<"Дерево НЕ(НЕ(d)): "<<nn4.print()<<std::endl;
    std::cout<<"Дерево НЕ(a) И a: "<<qnn1.print()<<std::endl<<"Дерево НЕ(b) И b: "<<qnn2.print()<<std::endl<<"Дерево НЕ(c) И c: "<<qnn3.print()<<std::endl<<"Дерево НЕ(d) И d: "<<qnn4.print()<<std::endl;
    std::cout<<"Дерево НЕ(a) ИЛИ a: "<<onn1.print()<<std::endl<<"Дерево НЕ(b) ИЛИ b: "<<onn2.print()<<std::endl<<"Дерево НЕ(c) ИЛИ c: "<<onn3.print()<<std::endl<<"Дерево НЕ(d) ИЛИ d: "<<onn4.print()<<std::endl;

    std::cout<<std::endl<<"Равны ли деревья"<<std::endl;
    std::cout<<"Дерево a и Дерево a: "<<(a.get_key() == a.get_key())<<std::endl;
    std::cout<<"Дерево a и Дерево НЕ(НЕ(a)): "<<(a.get_key() == nn1.get_key())<<std::endl;
    std::cout<<"Дерево b и Дерево НЕ(НЕ(b)): "<<(b.get_key() == nn2.get_key())<<std::endl;
    std::cout<<"Дерево c и Дерево НЕ(НЕ(c)): "<<(c.get_key() == nn3.get_key())<<std::endl;
    std::cout<<"Дерево d и Дерево НЕ(НЕ(d)): "<<(d.get_key() == nn4.get_key())<<std::endl;
    std::cout<<"Дерево a и Дерево НЕ(a) И a: "<<(a.get_key() == qnn1.get_key())<<std::endl;
    std::cout<<"Дерево b и Дерево НЕ(b): "<<(b.get_key() == n2.get_key())<<std::endl;
    std::cout<<"Дерево c и Дерево d: "<<(c.get_key() == d.get_key())<<std::endl;
    std::cout<<"Дерево d и Дерево НЕ(НЕ(a)): "<<(d.get_key() == nn1.get_key())<<std::endl;
    
    std::cout<<std::endl<<"Обратны ли деревья"<<std::endl;
    std::cout<<"Дерево a и Дерево НЕ(a): "<<(a.get_key() == get_opposite_key(n1.get_key(), 4))<<std::endl;
    std::cout<<"Дерево b и Дерево НЕ(b): "<<(b.get_key() == get_opposite_key(n2.get_key(), 4))<<std::endl;
    std::cout<<"Дерево c и Дерево НЕ(c): "<<(c.get_key() == get_opposite_key(n3.get_key(), 4))<<std::endl;
    std::cout<<"Дерево d и Дерево НЕ(d): "<<(d.get_key() == get_opposite_key(n4.get_key(), 4))<<std::endl;
    std::cout<<"Дерево a и Дерево НЕ(НЕ(a)): "<<(a.get_key() == get_opposite_key(nn1.get_key(), 4))<<std::endl;
    std::cout<<"Дерево b и Дерево НЕ(НЕ(b)): "<<(b.get_key() == get_opposite_key(nn2.get_key(), 4))<<std::endl;
    std::cout<<"Дерево c и Дерево НЕ(НЕ(c)): "<<(c.get_key() == get_opposite_key(nn3.get_key(), 4))<<std::endl;
    std::cout<<"Дерево d и Дерево НЕ(НЕ(d)): "<<(d.get_key() == get_opposite_key(nn4.get_key(), 4))<<std::endl;
    std::cout<<"Дерево a и Дерево НЕ(a) И a: "<<(a.get_key() == get_opposite_key(qnn1.get_key(), 4))<<std::endl;
    std::cout<<"Дерево b и Дерево b: "<<(b.get_key() == get_opposite_key(b.get_key(), 4))<<std::endl;
    std::cout<<"Дерево c и Дерево d: "<<(c.get_key() == get_opposite_key(d.get_key(), 4))<<std::endl;
    std::cout<<"Дерево d и Дерево НЕ(НЕ(a)): "<<(d.get_key() == get_opposite_key(nn1.get_key(), 4))<<std::endl;
}
bool run_tests(){
    test_degree_of_two();
    test_dnf();
    test_two_not();
    test_three_not();
    test_three_inversions_2();
    test_three_inversions_3();
    test_three_inversions_4();
    test_three_inversions_5();
    test_tree_optimization();
    test_many();
    return true;
}