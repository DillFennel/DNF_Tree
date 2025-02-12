#include "dnf_tests.h"
#include <iostream>
#include "dnf_tree.h"
#include <cassert>
#include <bitset>
#include <fstream>

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
void test_dnf_file(){ //Тест работы с файлом
    std::ofstream fout("dnf.txt");
    fout<<"0010\n2002\n0020\n2002"<<std::endl;
    fout.close();

    Tree t;
    make_tree_from_dnf(&t);
    assert(t.print() == "(c+(!a*!d)+!c+(!a*!d))" && "Проверка print до оптимизации");
    assert(t.get_key() == 65535 && "Проверка key до оптимизации");
    assert(t.get_value() == '+' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "1" && "Проверка print после оптимизации");
    assert(t.get_key() == 65535 && "Проверка key после оптимизации");
    assert(t.get_value() == '1' && "Проверка value после оптимизации");

    std::cout<<"Тесты работы с файлом пройдены"<<std::endl;
}
 
void test_two_not(){ //Тест работы с ДНФ - Два отрицания
    Tree t('!', new Tree('!', new Tree('a')));
    assert(t.print() == "!!a" && "Проверка print до оптимизации");
    assert(t.get_key() == 65280 && "Проверка key до оптимизации");
    assert(t.get_value() == '!' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "a" && "Проверка print после оптимизации");
    assert(t.get_key() == 65280 && "Проверка key после оптимизации");
    assert(t.get_value() == 'a' && "Проверка value после оптимизации");

    std::cout<<"Тесты работы с двумя отрицаниями"<<std::endl;
} 
void test_three_not(){ //Тест работы с ДНФ - Три отрицания
    Tree t('!', new Tree('!', new Tree('!', new Tree('a'))));
    assert(t.print() == "!!!a" && "Проверка print до оптимизации");
    assert(t.get_key() == 255 && "Проверка key до оптимизации");
    assert(t.get_value() == '!' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "!a" && "Проверка print после оптимизации");
    assert(t.get_key() == 255 && "Проверка key после оптимизации");
    assert(t.get_value() == '!' && "Проверка value после оптимизации");
    
    std::cout<<"Тесты работы с тремя отрицаниями пройдены"<<std::endl;
}

void test_three_inversions_2(){ //Тест работы с ДНФ - Тест с тройной инверсией 2
    Tree t('!', new Tree('!', new Tree('!', new Tree('+', new Tree('a'), new Tree('b')))));
    assert(t.print() == "!!!(a+b)" && "Проверка print до оптимизации");
    assert(t.get_key() == 15 && "Проверка key до оптимизации");
    assert(t.get_value() == '!' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "!(a+b)" && "Проверка print после оптимизации");
    assert(t.get_key() == 15 && "Проверка key после оптимизации");
    assert(t.get_value() == '!' && "Проверка value после оптимизации");
    
    std::cout<<"Тесты работы с тримя отрицаниями - 2 пройдены"<<std::endl;
}
void test_three_inversions_3(){ //Тест работы с ДНФ - Тест с тройной инверсией 3
    Tree t('!', new Tree('!', new Tree('!', new Tree('*', new Tree('a'), new Tree('b')))));
    assert(t.print() == "!!!(a*b)" && "Проверка print до оптимизации");
    assert(t.get_key() == 4095 && "Проверка key до оптимизации");
    assert(t.get_value() == '!' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "!(a*b)" && "Проверка print после оптимизации");
    assert(t.get_key() == 4095 && "Проверка key после оптимизации");
    assert(t.get_value() == '!' && "Проверка value после оптимизации");
    
    std::cout<<"Тесты работы с тримя отрицаниями - 3 пройдены"<<std::endl;
}
void test_three_inversions_4(){ //Тест работы с ДНФ - Тест с тройной инверсией 4
    Tree t('!', new Tree('!', new Tree('!', new Tree('*', new Tree('a'), new Tree('+', new Tree('b'), new Tree('c'))))));
    assert(t.print() == "!!!(a*(b+c))" && "Проверка print до оптимизации");
    assert(t.get_key() == 1023 && "Проверка key до оптимизации");
    assert(t.get_value() == '!' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "!(a*(b+c))" && "Проверка print после оптимизации");
    assert(t.get_key() == 1023 && "Проверка key после оптимизации");
    assert(t.get_value() == '!' && "Проверка value после оптимизации");

    std::cout<<"Тесты работы с тримя отрицаниями - 4 пройдены"<<std::endl;
} 
void test_three_inversions_5(){ //Тест работы с ДНФ - Тест с тройной инверсией 5
    Tree t('!', new Tree('!', new Tree('!', new Tree('*', new Tree('a'), new Tree('+', new Tree('b'), new Tree('b'))))));
    assert(t.print() == "!!!(a*(b+b))" && "Проверка print до оптимизации");
    assert(t.get_key() == 4095 && "Проверка key до оптимизации");
    assert(t.get_value() == '!' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "!(a*b)" && "Проверка print после оптимизации");
    assert(t.get_key() == 4095 && "Проверка key после оптимизации");
    assert(t.get_value() == '!' && "Проверка value после оптимизации");
    
    std::cout<<"Тесты работы с тримя отрицаниями - 5 пройдены"<<std::endl;
}
void test_tree_optimization(){ //Пример оптимизации дерева
    Tree t = Tree('+', new Tree('a'), new Tree('+', new Tree('b'), new Tree('+', new Tree('c'), new Tree('d'))));
    assert(t.print() == "(a+(b+(c+d)))" && "Проверка print до оптимизации");
    std::cout<<t.get_key()<<std::endl;
    assert(t.get_key() == 32767 && "Проверка key до оптимизации");
    assert(t.get_value() == '+' && "Проверка value до оптимизации");
    t.optimize();
    assert(t.print() == "(a+b+c+d)" && "Проверка print после оптимизации");
    assert(t.get_key() == 32767 && "Проверка key после оптимизации");
    assert(t.get_value() == '+' && "Проверка value после оптимизации");
    
    std::cout<<"Тесты работы с оптимизацией сложного дерева пройдены"<<std::endl;
}
void test_simple(){ //Пример работы с разными деревьями
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
    Tree not_a_and_a = Tree('*', new Tree('!', new Tree('a')), new Tree('a')); //Дерево НЕ(a) И a
    Tree not_b_and_b = Tree('*', new Tree('!', new Tree('b')), new Tree('b')); //Дерево НЕ(b) И b
    Tree not_c_and_c = Tree('*', new Tree('!', new Tree('c')), new Tree('c')); //Дерево НЕ(c) И c
    Tree not_d_and_d = Tree('*', new Tree('!', new Tree('d')), new Tree('d')); //Дерево НЕ(d) И d
    Tree not_a_or_a = Tree('+', new Tree('!', new Tree('a')), new Tree('a')); //Дерево НЕ(a) ИЛИ a
    Tree not_b_or_b = Tree('+', new Tree('!', new Tree('b')), new Tree('b')); //Дерево НЕ(b) ИЛИ b
    Tree not_c_or_c = Tree('+', new Tree('!', new Tree('c')), new Tree('c')); //Дерево НЕ(c) ИЛИ c
    Tree not_d_or_d = Tree('+', new Tree('!', new Tree('d')), new Tree('d')); //Дерево НЕ(d) ИЛИ d
    
    assert(a.print()=="a" && "Проверка print a");
    assert(b.print()=="b" && "Проверка print b");
    assert(c.print()=="c" && "Проверка print c");
    assert(d.print()=="d" && "Проверка print d");

    assert(not_a.print()=="!a" && "Проверка print !a");
    assert(not_b.print()=="!b" && "Проверка print !b");
    assert(not_c.print()=="!c" && "Проверка print !c");
    assert(not_d.print()=="!d" && "Проверка print !d");

    assert(not_not_a.print()=="!!a" && "Проверка print !!a");
    assert(not_not_b.print()=="!!b" && "Проверка print !!b");
    assert(not_not_c.print()=="!!c" && "Проверка print !!c");
    assert(not_not_d.print()=="!!d" && "Проверка print !!d");

    assert(not_a_and_a.print()=="(!a*a)" && "Проверка print (!a*a)");
    assert(not_b_and_b.print()=="(!b*b)" && "Проверка print (!b*b)");
    assert(not_c_and_c.print()=="(!c*c)" && "Проверка print (!c*c)");
    assert(not_d_and_d.print()=="(!d*d)" && "Проверка print (!d*d)");

    assert(not_a_or_a.print()=="(!a+a)" && "Проверка print (!a+a)");
    assert(not_b_or_b.print()=="(!b+b)" && "Проверка print (!b+b)");
    assert(not_c_or_c.print()=="(!c+c)" && "Проверка print (!c+c)");
    assert(not_d_or_d.print()=="(!d+d)" && "Проверка print (!d+d)");

    //Проверка равенста деревьев

    //Оптимизируем  все деревья
    a.optimize();
    b.optimize();
    c.optimize();
    d.optimize();
    not_a.optimize();
    not_b.optimize();
    not_c.optimize();
    not_d.optimize();
    not_not_a.optimize();
    not_not_b.optimize();
    not_not_c.optimize();
    not_not_d.optimize();
    not_a_and_a.optimize();
    not_b_and_b.optimize();
    not_c_and_c.optimize();
    not_d_and_d.optimize();
    not_a_or_a.optimize();
    not_b_or_b.optimize();
    not_c_or_c.optimize();
    not_d_or_d.optimize();
    
    assert(a.print()=="a" && "Проверка print a");
    assert(b.print()=="b" && "Проверка print b");
    assert(c.print()=="c" && "Проверка print c");
    assert(d.print()=="d" && "Проверка print d");

    assert(not_a.print()=="!a" && "Проверка print !a");
    assert(not_b.print()=="!b" && "Проверка print !b");
    assert(not_c.print()=="!c" && "Проверка print !c");
    assert(not_d.print()=="!d" && "Проверка print !d");

    assert(not_not_a.print()=="a" && "Проверка print !!a");
    assert(not_not_b.print()=="b" && "Проверка print !!b");
    assert(not_not_c.print()=="c" && "Проверка print !!c");
    assert(not_not_d.print()=="d" && "Проверка print !!d");

    assert(not_a_and_a.print()=="0" && "Проверка print (!a*a)");
    assert(not_b_and_b.print()=="0" && "Проверка print (!b*b)");
    assert(not_c_and_c.print()=="0" && "Проверка print (!c*c)");
    assert(not_d_and_d.print()=="0" && "Проверка print (!d*d)");

    assert(not_a_or_a.print()=="1" && "Проверка print (!a+a)");
    assert(not_b_or_b.print()=="1" && "Проверка print (!b+b)");
    assert(not_c_or_c.print()=="1" && "Проверка print (!c+c)");
    assert(not_d_or_d.print()=="1" && "Проверка print (!d+d)");
    
    //Проверка равенста деревьев
    assert(a.get_key() == a.get_key() && "a == a");
    assert(b.get_key() == b.get_key() && "b == b");
    assert(c.get_key() == c.get_key() && "c == c");
    assert(d.get_key() == d.get_key() && "d == d");
    assert(a.get_key() == not_not_a.get_key() && "a == !!a");
    assert(b.get_key() == not_not_b.get_key() && "b == !!b");
    assert(c.get_key() == not_not_c.get_key() && "c == !!c");
    assert(d.get_key() == not_not_d.get_key() && "d == !!d");

    assert(not_a_and_a.get_key() == not_b_and_b.get_key() && "!a*a == !b*b");
    assert(not_a_and_a.get_key() == not_c_and_c.get_key() && "!a*a == !c*c");
    assert(not_a_and_a.get_key() == not_d_and_d.get_key() && "!a*a == !d*d");
    assert(not_b_and_b.get_key() == not_c_and_c.get_key() && "!b*b == !c*c");
    assert(not_b_and_b.get_key() == not_d_and_d.get_key() && "!b*b == !d*d");
    assert(not_c_and_c.get_key() == not_d_and_d.get_key() && "!c*c == !d*d");

    assert(not_a_or_a.get_key() == not_b_or_b.get_key() && "!a+a == !b+b");
    assert(not_a_or_a.get_key() == not_c_or_c.get_key() && "!a+a == !c+c");
    assert(not_a_or_a.get_key() == not_d_or_d.get_key() && "!a+a == !d+d");
    assert(not_b_or_b.get_key() == not_c_or_c.get_key() && "!b+b == !c+c");
    assert(not_b_or_b.get_key() == not_d_or_d.get_key() && "!b+b == !d+d");
    assert(not_c_or_c.get_key() == not_d_or_d.get_key() && "!c+c == !d+d");
    //Проверка неравенства деревьев
    assert(a.get_key() != not_a.get_key() && "a != !a");
    assert(b.get_key() != not_b.get_key() && "b != !b");
    assert(c.get_key() != not_c.get_key() && "c != !c");
    assert(d.get_key() != not_d.get_key() && "d != !d");
    assert(a.get_key() != not_a_and_a.get_key() && "a != !a*a");
    assert(b.get_key() != not_b_and_b.get_key() && "b != !b*b");
    assert(c.get_key() != not_c_and_c.get_key() && "c != !c*c");
    assert(d.get_key() != not_d_and_d.get_key() && "d != !d*d");

    assert(a.get_key() != b.get_key() && "a != b");
    assert(a.get_key() != c.get_key() && "a != c");
    assert(a.get_key() != d.get_key() && "a != d");
    assert(b.get_key() != c.get_key() && "b != c");
    assert(b.get_key() != d.get_key() && "b != d");
    assert(c.get_key() != d.get_key() && "c != d");
    
    //Проверка, обратны ли деревья
    assert(a.get_key() == get_opposite_key(not_a.get_key(), 4) && "a opposite !a");
    assert(b.get_key() == get_opposite_key(not_b.get_key(), 4) && "b opposite !b");
    assert(c.get_key() == get_opposite_key(not_c.get_key(), 4) && "c opposite !c");
    assert(d.get_key() == get_opposite_key(not_d.get_key(), 4) && "d opposite !d");
    assert(get_opposite_key(a.get_key(), 4) == not_a.get_key() && "a opposite !a");
    assert(get_opposite_key(b.get_key(), 4) == not_b.get_key() && "b opposite !b");
    assert(get_opposite_key(c.get_key(), 4) == not_c.get_key() && "c opposite !c");
    assert(get_opposite_key(d.get_key(), 4) == not_d.get_key() && "d opposite !d");
    
    //Проверка, не обратны ли деревья
    assert(a.get_key() == get_opposite_key(not_a.get_key(), 4) && "a opposite !a");
    assert(b.get_key() == get_opposite_key(not_b.get_key(), 4) && "b opposite !b");
    assert(c.get_key() == get_opposite_key(not_c.get_key(), 4) && "c opposite !c");
    assert(d.get_key() == get_opposite_key(not_d.get_key(), 4) && "d opposite !d");
    assert(get_opposite_key(a.get_key(), 4) == not_a.get_key() && "a opposite !a");
    assert(get_opposite_key(b.get_key(), 4) == not_b.get_key() && "b opposite !b");
    assert(get_opposite_key(c.get_key(), 4) == not_c.get_key() && "c opposite !c");
    assert(get_opposite_key(d.get_key(), 4) == not_d.get_key() && "d opposite !d");

    std::cout<<"Тесты работы с оптимизацией сложного дерева пройдены"<<std::endl;
}
bool run_tests(){
    test_degree_of_two();
    test_dnf_file();
    test_two_not();
    test_three_not();
    test_three_inversions_2();
    test_three_inversions_3();
    test_three_inversions_4();
    test_three_inversions_5();
    //test_tree_optimization();
    test_simple();
    std::cout<<std::endl<<"Все тесты пройдены"<<std::endl;
    return true;
}