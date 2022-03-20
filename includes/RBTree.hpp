#ifndef RBTREE_HPP
#define RBTREE_HPP
#include <__tree>
#include <exception>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <queue>
#include <utility>
#include <vector>

#include "RBTree_iterator.hpp"
#include "etc.hpp"

namespace ft
{

template <class T, class Compare = std::less<T>, class Node = ft::rb_node<T>, class Alloc = std::allocator<Node> >
class rb_tree
{
  public:
    typedef unsigned long size_type;
    typedef Alloc allocator_type;
    typedef Compare compare_type;
    typedef ft::rb_tree_iterator<Node> iterator;

  private:
    Node *_root;
    Node _end;

    size_type _size;
    allocator_type _alloc;
    compare_type _comp;
    bool _is_nil;

  public:
    rb_tree(const allocator_type &alloc = allocator_type(), const compare_type &comp = Compare())
        : _root(nullptr), _alloc(alloc), _comp(comp), _is_nil(false)
    {
        // _nil = _alloc.allocate(1);
        // _alloc.construct(_nil, Node());
    }

    rb_tree(const rb_tree &x, const allocator_type &alloc = allocator_type(), const compare_type &comp = Compare())
        : _root(nullptr), _alloc(alloc), _comp(x._comp), _is_nil(false)
    {
    }

    ~rb_tree()
    {
        delete_tree(_root);
        // _alloc.deallocate(_nil, 1);
    }

    Node *create_node(T data)
    {
        Node *temp = _alloc.allocate(1);
        _alloc.construct(temp, Node(data));
        return temp;
    }

    Node *create_nil()
    {
        Node *temp = _alloc.allocate(1);
        _alloc.construct(temp, Node());
        _is_nil = true;
        return temp;
    }

    void set_color(Node *node, int color)
    {
        if (node == nullptr)
            return;
        node->color = color;
    }

    int get_color(Node *node) const
    {
        if (node == nullptr)
            return BLACK;
        return node->color;
    }

    void rotate_left(Node *Parent)
    {
        Node *right_child = Parent->right;
        Parent->right = right_child->left;

        if (Parent->right != nullptr)
            Parent->right->parent = Parent;

        right_child->parent = Parent->parent;

        if (Parent->parent == nullptr)
            _root = right_child;
        else if (Parent == Parent->parent->left)
            Parent->parent->left = right_child;
        else
            Parent->parent->right = right_child;
        right_child->left = Parent;
        Parent->parent = right_child;
    }

    void rotate_right(Node *Parent)
    {
        Node *left_child = Parent->left;
        Parent->left = left_child->right;

        if (Parent->left != nullptr)
            Parent->left->parent = Parent;

        left_child->parent = Parent->parent;

        if (Parent->parent == nullptr || Parent->parent == &_end)
            _root = left_child;
        else if (Parent == Parent->parent->left)
            Parent->parent->left = left_child;
        else
            Parent->parent->right = left_child;
        left_child->right = Parent;
        Parent->parent = left_child;
    }

    void insert_node(Node *&root, Node *new_node)
    {
        if (root == nullptr)
        {
            root = new_node;
        }
        if (_comp(new_node->data, root->data))
        {
            if (root->left == nullptr)
            {
                root->left = new_node;
                new_node->parent = root;
            }
            else
                insert_node(root->left, new_node);
        }
        else if (_comp(root->data, new_node->data))
        {
            if (root->right == nullptr)
            {
                root->right = new_node;
                new_node->parent = root;
            }
            else
                insert_node(root->right, new_node);
        }
    }

    void rebuild_insert(Node *new_node)
    {
        Node *parent;
        Node *grand_parent;
        Node *uncle;
        while (new_node != _root && get_color(new_node->parent) == RED)
        {
            parent = new_node->parent;
            grand_parent = parent->parent;
            if (parent == grand_parent->left)
            {
                uncle = grand_parent->right;
                if (get_color(uncle) == RED)
                {
                    set_color(parent, BLACK);
                    set_color(uncle, BLACK);
                    set_color(grand_parent, RED);
                }
                else
                {
                    if (new_node == parent->right)
                    {
                        rotate_left(parent);
                        parent = new_node;
                    }
                    rotate_right(grand_parent);
                    std::swap(parent->color, grand_parent->color);
                }
            }
            else
            {
                uncle = grand_parent->left;
                if (get_color(uncle) == RED)
                {
                    set_color(parent, BLACK);
                    set_color(uncle, BLACK);
                    set_color(grand_parent, RED);
                }
                else
                {
                    if (new_node == parent->left)
                    {
                        rotate_right(parent);
                        parent = new_node;
                    }
                    rotate_left(grand_parent);
                    std::swap(parent->color, grand_parent->color);
                }
            }
        }
        set_color(_root, BLACK);
    }

    void insert_value(T data)
    {
        Node *new_node = create_node(data);
        insert_node(_root, new_node);
        rebuild_insert(new_node);

        _end.parent = _root;
        _end.right = _root;
        _end.left = _root;
        if (_root)
        _root->parent = &_end;
    }

    Node *search_node(Node *root, T data) const
    {
        if (root == nullptr || root == nullptr)
            return nullptr;
        if (_comp(data, root->data))
            return search_node(root->left, data);
        else if (_comp(root->data, data))
            return search_node(root->right, data);
        else
            return root;
    }

    Node *min_node(Node *node) const
    {
        if (node == nullptr)
            return nullptr;
        if (node->left == nullptr)
            return node;
        else
            return min_node(node->left);
    }

    void rebuild_delete(Node *root, Node *successor)
    {
        Node *sibling;
        while (successor->parent && get_color(successor) == BLACK)
        {
            if (successor == successor->parent->left)
            {
                sibling = successor->parent->right;
                if (get_color(sibling) == RED)
                {
                    set_color(sibling, BLACK);
                    set_color(successor->parent, RED);
                    rotate_left(successor->parent);
                }
                else
                {
                    if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
                    {
                        set_color(sibling, RED);
                        successor = successor->parent;
                    }
                    else
                    {
                        if (get_color(sibling->left) == RED)
                        {
                            set_color(sibling->left, BLACK);
                            set_color(sibling, RED);
                            rotate_right(sibling);
                            sibling = sibling->parent->right;
                        }
                        set_color(sibling, successor->parent->color);
                        set_color(successor->parent, BLACK);
                        set_color(sibling->right, BLACK);
                        rotate_left(successor->parent);
                        successor = root;
                    }
                }
            }
            else
            {
                sibling = successor->parent->left;
                if (get_color(sibling) == RED)
                {
                    set_color(sibling, BLACK);
                    set_color(successor->parent, RED);
                    rotate_right(successor->parent);
                }
                else
                {
                    if (get_color(sibling->left) == BLACK && get_color(sibling->right) == BLACK)
                    {
                        set_color(sibling, RED);
                        successor = successor->parent;
                    }
                    else
                    {
                        if (get_color(sibling->right) == RED)
                        {
                            set_color(sibling->right, BLACK);
                            set_color(sibling, RED);
                            rotate_left(sibling);
                            sibling = sibling->parent->left;
                        }
                        set_color(sibling, successor->parent->color);
                        set_color(successor->parent, BLACK);
                        set_color(sibling->left, BLACK);
                        rotate_left(successor->parent);
                        successor = root;
                    }
                }
            }
        }
        set_color(successor, BLACK);
    }

    void delete_value(T data)
    {
        Node *target = search_node(_root, data);
        Node *remove;
        Node *successor;

        if (target == nullptr)
            return;
        if (target->left == nullptr || target->right == nullptr)
            remove = target;
        else
        {
            remove = min_node(target->right);
            target->data = remove->data;
        }
        if (remove->left)
            successor = remove->left;
        else if (remove->right)
            successor = remove->right;
        else
            successor = create_nil();
        successor->parent = remove->parent;
        if (remove->parent == nullptr)
            _root = successor;
        else
        {
            if (remove == remove->parent->left)
                remove->parent->left = successor;
            else
                remove->parent->right = successor;
        }
        if (get_color(remove) == BLACK)
            rebuild_delete(_root, successor);
        if (_is_nil == true)
        {
            if (successor == successor->parent->left)
                successor->parent->left = nullptr;
            else
                successor->parent->right = nullptr;
            delete_node(successor);
            _is_nil = false;
        }
        delete_node(remove);
    }

    // void node_info(Node *node) const
    // {
    //     if (node == nullptr)
    //         return;
    //     std::cout << "node:" << std::setw(3) << node->data << BLUE "|" NC;
    //     if (get_color(node) == RED)
    //         std::cout << std::setw(15) << RED_C "RED" NC << BLUE "|" NC;
    //     else if (get_color(node) == BLACK)
    //         std::cout << std::setw(15) << BLACK_C "BLACK" NC << BLUE "|" NC;
    //     if (node->left)
    //     {
    //         std::cout << "left_node:" << std::setw(4) << node->left->data << BLUE "|" NC;
    //     }
    //     else
    //     {
    //         std::cout << "left_node:" << std::setw(4) << " " << BLUE "|" NC;
    //     }
    //     if (node->right)
    //     {
    //         std::cout << "right_node:" << std::setw(4) << node->right->data << BLUE "|" NC;
    //     }
    //     else
    //     {
    //         std::cout << "right_node:" << std::setw(4) << " " << BLUE "|" NC;
    //     }
    //     std::cout << std::endl;
    // }

    void node_info(Node *node) const
    {
        if (node == nullptr)
            return;
        std::cout << "node:" << std::setw(3) << node->data << BLUE "|" NC;
        if (get_color(node) == RED)
            std::cout << std::setw(15) << RED_C "RED" NC << BLUE "|" NC;
        else if (get_color(node) == BLACK)
            std::cout << std::setw(15) << BLACK_C "BLACK" NC << BLUE "|" NC;
        if (node->left)
        {
            std::cout << "left_node:" << std::setw(4) << node->left->data << BLUE "|" NC;
        }
        else
        {
            std::cout << "left_node:" << std::setw(4) << " " << BLUE "|" NC;
        }
        if (node->right)
        {
            std::cout << "right_node:" << std::setw(4) << node->right->data << BLUE "|" NC;
        }
        else
        {
            std::cout << "right_node:" << std::setw(4) << " " << BLUE "|" NC;
        }
        std::cout << std::endl;
    }

    void print_tree() const
    {
        std::queue<Node *> q;
        if (_root)
            q.push(_root);
        while (!q.empty())
        {
            Node *node = q.front();
            q.pop();
            node_info(node);
            if (node->left)
                q.push(node->left);
            if (node->right)
                q.push(node->right);
        }
    }

    void delete_node(Node *node)
    {
        _alloc.destroy(node);
        _alloc.deallocate(node, 1);
    }

    void delete_tree(Node *&root)
    {
        if (root == nullptr)
            return;
        if (root->left)
            delete_tree(root->left);
        if (root->right)
            delete_tree(root->right);
        delete_node(root);
        root = nullptr;
    }

    Node* begin(){
        return min_node(_root);
    }

    Node* end(){
        return &_end;
    }

};

} // namespace ft

#endif