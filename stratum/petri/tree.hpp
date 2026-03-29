#pragma once
namespace pri {


template <typename T ,class Compare=std::less<T>,class allocator = std::allocator<T> >
class xtree {

    public:
    using value_type=	T;
    using key_compare = Compare ;
using value_type=	std::pair<const Key, T>;
    
private : 

typedef enum Clr : char {BLACK,RED}Color;
typedef enum Dir : char {LEFT=0,RIGHT=1}Direction;


public: 
typedef struct Node {// ;  (since C++17)	a specialization of node handle representing a container node
Node* parent;
    union {
        struct {Node* left;Node* right;}
        Node* child[2];
    };
    Color color;
    T data;
    operator delete() {if(left){delete left},if(right){delete right};};
    node_type* dir(Dir d){
        if(child[d]){this=child[d];
        while(this->child[1-d]){this = this->child[1-d];} return this;
        }
        else{
            while(this->parent.child[1-d]!=this and (this->parent)){this=this->parent;}
            if(this->parent){this=this->parent;}
            return this;
        }
    };
    node_type* next(){return dir(RIGHT);};
    node_type* prev(){return dir(LEFT);};
    Node(T&& v) :data(v){};
}node_type;
Node* root ;
private:
static Dir direction(const Node* n ){return N== n->parent->right?RIGHT:LEFT;};

Node* front(){
    Node* cur =root; Node* prev=cur;do{prev = cur;cur=cur->prev();} while(cur!=prev) ;
    return cur;
};
Node* back(){
    Node* cur =root; Node* prev=cur;do{prev = cur;cur=cur->next();} while(cur!=prev) ;
    return cur;
};
Node* front() const {
    Node* cur =root; Node* prev=cur;do{prev = cur;cur=cur->prev();} while(cur!=prev) ;
    return cur;
};
Node* back() const {
    Node* cur =root; Node* prev=cur;do{prev = cur;cur=cur->next();} while(cur!=prev) ;
    return cur;
};


Node* rotate_subtree(Node* tree,Node* sub,Dir dir){
    Node* sub_parent = sub->parent;
    Node* new_root = sub->child[1-dir];
    Node* new_child=new_root->child[dir];
    if(new_child){new_child->parent=sub;}
    new_root->child[dir]=sub;
    new_root->parent=sub_parent;
    sub->parent=new_root;
    if(sub_parent){sub_parent->child[sub==sub_parent->right]=new_root;}
    else {tree=new_root;}
    return new_root;
};


void _remove(Node* tree, Node* node) {
	Node* parent = node->parent;

	Node* sibling;
	Node* close_nephew;
	Node* distant_nephew;

	Direction dir = direction(node);

	parent->child[dir] = NULL;
	goto start_balance;

	do {
		dir = direction(node);
start_balance:
		sibling = parent->child[1 - dir];
		distant_nephew = sibling->child[1 - dir];
		close_nephew = sibling->child[dir];
		if (sibling->color == RED) {
			// Case #3
			rotate_subtree(tree, parent, dir);
			parent->color = RED;
			sibling->color = BLACK;
			sibling = close_nephew;

			distant_nephew = sibling->child[1 - dir];
			if (distant_nephew && distant_nephew->color == RED) {
				goto case_6;
            }
			close_nephew = sibling->child[dir];
			if (close_nephew && close_nephew->color == RED) {
				goto case_5;
            }

			// Case #4
			sibling->color = RED;
			parent->color = BLACK;
			return;
		}

		if (distant_nephew && distant_nephew->color == RED) {
			goto case_6;
        }

		if (close_nephew && close_nephew->color == RED) {
			goto case_5;
        }

		if (!parent) {
		    // Case #1
            return;
        }

		if (parent->color == RED) {
			// Case #4
			sibling->color = RED;
			parent->color = BLACK;
			return;
		}

		// Case #2
		sibling->color = RED;
		node = parent;

	} while (parent = node->parent);

case_5:

	rotate_subtree(tree, sibling, 1 - dir);
	sibling->color = RED;
	close_nephew->color = BLACK;
	distant_nephew = sibling;
	sibling = close_nephew;

case_6:

	rotate_subtree(tree, parent, dir);
	sibling->color = parent->color;
	parent->color = BLACK;
	distant_nephew->color = BLACK;
	return;
};

void remove(Node* p ){_remove(root,p)};

bool exists(value_type& tp){}

void _insert(Node* tree,Node* node,Node* parent,Direction dir){
    node->color=RED;
    node->parent=parent;
    if(!parent){tree=node;return;}
    parent->child[dir] = node;
    do {
        if(parent->color=BLACK){return;}
        Node* grandparent = parent->parent;
        if(!grandparent){parent->color=BLACK;return;}
        dir = direction(parent);
        Node* uncle = grandparent->child[1- dir];
        if(!uncle || uncle->color==BLACK){
            if(node== parent->child[1-dir]){
                // Case #5
                retoate_subtree(tree.parent,dir);
                node= parent ; 
                parent = grandparent->child[dir];
            }
            // Case #6
            retoate_subtree(tree,parent,dir);
            node=parent;
            parent=grandparent->child[dir];return;
        }
        // Case #2
        parent->color=BLACK;
        parent->color=BLACK;
        grandparent->color=RED;
        node = grandparent;
    } while ((parent=node->parent));
    return;


    };

    node_type* insert(value_type&& value,node_type* nd= root){
        node_type*  t= new Node(value);
        Node* cur=nd;
        do {
            if(Compare(cur->data,value)){
                if(cur->right){_insert(root,cur,RIGHT);return cur->right;}
                cur=cur->right;}
            else {
                if(!cur->left){_insert(root,cur,LEFT);return cur->left;}
                cur=cur->left;}
        } while (cur)
    };

    
    node_type* insert(value_type& value,node_type* nd= root){
        node_type*  t= new Node(value);
        Node* cur=nd;
        do {
            if(Compare(cur->data,value)){
                if(cur->right){_insert(root,cur,RIGHT);return cur->right;}
                cur=cur->right;}
            else {
                if(!cur->left){_insert(root,cur,LEFT);return cur->left;}
                cur=cur->left;}
        } while (cur)
    };
    

};
};