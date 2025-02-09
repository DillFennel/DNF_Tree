#include <string>
#include <vector>
#include <set>
#ifndef DNF_TREE_H
#define DNF_TREE_H
 
unsigned degree_of_two(int n);
unsigned get_mask(unsigned number_of_variables);
unsigned get_opposite_key(unsigned key, unsigned number_of_variables);
class Tree
{
public:
    unsigned get_key();
    Tree * get_child(int n);
    unsigned get_number_of_children();
    void set_value(int v);
    char get_value();
    bool add_child(Tree * new_child);
    void delete_child(int ind_child);
    void wrong_value();
    void cant_have_children();
    void too_many_children();
    void something_wrong();
    Tree(unsigned n=4);
    Tree(char v, unsigned n=4);
    Tree(char v, Tree* child, unsigned n=4);
    Tree(char v, Tree* child1, Tree* child2, unsigned n=4);
    std::string print();
    bool optimize_equal_operations(unsigned value_to_value, unsigned value_to_const, int index_child, std::set<unsigned> *keys_found);
    void optimize_from_one_child();
    bool optimization_for_multiple_child_cases();
    bool optimize();
    void to_null();
    void to_one();
private:
    char value;
    unsigned number_of_children;
    std::vector<Tree*> children;
    unsigned key;
    unsigned number_of_variables;
};
void make_dnf();
bool make_tree_from_dnf(Tree* tree);
 
#endif