#include <iostream>
#include<cstring>
#include<stack>
#include<queue>
using namespace std;
char print_buf[300][300];
template <class T>
class BinaryTreeNode {
public:
    T info;
    BinaryTreeNode* Left;
    BinaryTreeNode* Right;
    BinaryTreeNode* Parent;
public:
    BinaryTreeNode() :Left(NULL), Right(NULL), Parent(NULL) {
    };
    BinaryTreeNode(const T& ele) {
        info = ele;
        Left = NULL;
        Right = NULL;
        Parent = NULL;
    }
    BinaryTreeNode(const T& ele, BinaryTreeNode<T>* left_, BinaryTreeNode<T>* right_, BinaryTreeNode<T>* parent_) {
        info = ele;
        Left = left_;
        Right = right_;
        Parent = parent_;
    }
    BinaryTreeNode(const T& ele, BinaryTreeNode<T>* parent) {
        Parent = parent;
        info = ele;
    }
    BinaryTreeNode(BinaryTreeNode<T>* parent) {
        Parent = parent;
    }
    bool isLeaf() {
        if (Right == NULL && Left == NULL)
            return true;
        else
            return false;
    }
    BinaryTreeNode<T>* LeftSibling() {
        if (Parent == NULL)
            return nullptr;
        if (Parent->Right == this)
            return Parent->Left;
        else
            return nullptr;
    }
    BinaryTreeNode<T>* RightSibling() {
        if (Parent == NULL)
            return nullptr;
        if (Parent->Left == this)
            return Parent->Right;
        else
            return nullptr;
    }
    ~BinaryTreeNode() {
        DeleteBinaryTree(this);
    }
    friend int num_layer(BinaryTreeNode<T>* p) {
        if (p == NULL)
            return 0;
        int leftnum = num_layer(p->Left);
        int rightnum = num_layer(p->Right);
        return max(leftnum, rightnum) + 1;
    }
    friend void print_launch(BinaryTreeNode<T>* p) {
        int num = num_layer(p);
        print(p, 1 << (num - 1), 0, 1 << (num - 2));
        for (int i = 0; i <= 2 * (num - 1); i++) {
            int pos = (1 << num);
            while (print_buf[pos] == 0)pos--;
            for (int j = 0; j <= pos; j++) {
                if (print_buf[i][j] == 0)
                    cout << " ";
                else
                    cout << print_buf[i][j];
            }
            cout << endl;
        }
    }
    friend void print(BinaryTreeNode<T>* p, int root_x, int root_y, int space) {
        if (p == NULL)
            return;
        print_buf[root_y][root_x] = p->info;
        if (p->Left) {
            print_buf[root_y + 1][root_x - 1] = '/';
            print(p->Left, root_x - space, root_y + 2, space >> 1);
        }
        if (p->Right) {
            print_buf[root_y + 1][root_x + 1] = '\\';
            print(p->Right, root_x + space, root_y + 2, space >> 1);
        }
    }
    friend string PreOrder(BinaryTreeNode<T>* root) {
        if (root == NULL)
            return "";
        string ans;
        ans += root->info;
        ans += PreOrder(root->Left);
        ans += PreOrder(root->Right);
        return ans;
    }
    friend string InOrder(BinaryTreeNode<T>* root) {
        if (root == NULL)
            return "";
        string ans;
        ans += InOrder(root->Left);
        ans += root->info;
        ans += InOrder(root->Right);
        return ans;
    }
    friend string PostOrder(BinaryTreeNode<T>* root) {
        if (root == NULL)
            return "";
        string ans;
        ans += PostOrder(root->Left);
        ans += PostOrder(root->Right);
        ans += root->info;
        return ans;
    }
    friend void DeleteBinaryTree(BinaryTreeNode<T>* root) {
        if (root == NULL)
            return;
        string ans;
        DeleteBinaryTree(root->Left);
        DeleteBinaryTree(root->Right);
        delete root;
    }
    friend string PreOrder_with_stack(BinaryTreeNode<T>* root) {
        stack<BinaryTreeNode<T>*>stack_;
        string ans;
        BinaryTreeNode<T>* cur = root;
        while (1) {
            ans += cur->info;
            if (cur->Right)
                stack_.push(cur->Right);
            if (cur->Left)
                cur = cur->Left;
            else {
                if (stack_.empty())
                    break;
                cur = stack_.top();
                stack_.pop();
            };
        }
        return ans;
    }
    friend string InOrder_with_stack(BinaryTreeNode<T>* root) {
        stack<BinaryTreeNode<T>*>stack_;
        string ans;
        BinaryTreeNode<T>* cur = root;
        while (1) {
            stack_.push(cur);
            if (cur->Left != NULL) {
                cur = cur->Left;
                continue;
            }
            else {
                while (1) {
                    if (stack_.empty())
                        return ans;
                    cur = stack_.top();
                    stack_.pop();
                    ans += cur->info;
                    if (cur->Right != NULL) {
                        cur = cur->Right;
                        break;
                    }
                }
            }
        }
    }
    friend string PostOrder_with_stack(BinaryTreeNode<T>* root) {
        stack<pair<BinaryTreeNode<T>*, int> > stack_;
        BinaryTreeNode<T>* cur = root;
        string ans;
        while (1) {
            if (cur->Left != NULL) {
                stack_.push({ cur,0 });
                cur = cur->Left;
                continue;
            }
            else
            {
                stack_.push({ cur,1 });
                if (cur->Right != NULL)
                {
                    cur = cur->Right;
                    continue;
                }
                else {
                    while (1) {
                        if (stack_.empty())
                            return ans;
                        cur = stack_.top().first;
                        int flag = stack_.top().second;
                        stack_.pop();
                        if (flag == 1)
                            ans += cur->info;
                        else if (cur->Right == NULL) {
                            ans += cur->info;
                        }
                        else {
                            stack_.push({ cur,1 });
                            cur = cur->Right;
                            break;
                        }
                    }
                }
            }
        }
    }
    friend string LeverOrder(BinaryTreeNode<T>* root) {
        queue<BinaryTreeNode<T>*>q;
        q.push(root);
        string ans;
        while (!q.empty()) {
            BinaryTreeNode<T>* cur = q.front();
            q.pop();
            ans += cur->info;
            if (cur->Left)
                q.push(cur->Left);
            if (cur->Right)
                q.push(cur->Right);
        }
        return ans;
    }
};

int main() {
    BinaryTreeNode<char>* tree[10];
    tree[1] = new BinaryTreeNode<char>('a');
    tree[1]->Left = new BinaryTreeNode<char>('b');
    tree[1]->Left->Left = new BinaryTreeNode<char>('c');
    tree[1]->Left->Right = new BinaryTreeNode<char>('e');
    tree[1]->Left->Right->Left = new BinaryTreeNode<char>('f');
    tree[1]->Left->Left->Left = new BinaryTreeNode<char>('d');
    tree[1]->Right = new BinaryTreeNode<char>('g');
    tree[1]->Right->Left = new BinaryTreeNode<char>('h');
    tree[1]->Right->Left->Right = new BinaryTreeNode<char>('I');
    tree[1]->Right->Left->Left = new BinaryTreeNode<char>('J');
    tree[1]->Right->Left->Right->Right = new BinaryTreeNode<char>('K');

    tree[2] = new BinaryTreeNode<char>('1');

    tree[3] = new BinaryTreeNode<char>('1');
    tree[3]->Left = new BinaryTreeNode<char>('2');
    tree[3]->Right = new BinaryTreeNode<char>('3');

    tree[4] = new BinaryTreeNode<char>('a');
    tree[4]->Left = new BinaryTreeNode<char>('c');
    tree[4]->Right = new BinaryTreeNode<char>('b');
    tree[4]->Right->Right = new BinaryTreeNode<char>('d');
    tree[4]->Right->Left = new BinaryTreeNode<char>('e');
    tree[4]->Right->Left->Right = new BinaryTreeNode<char>('f');
    tree[4]->Left->Right = new BinaryTreeNode<char>('g');
    tree[4]->Left->Right->Left = new BinaryTreeNode<char>('m');
    tree[4]->Left->Right->Right = new BinaryTreeNode<char>('n');
    tree[4]->Right->Right->Right = new BinaryTreeNode<char>('h');
    tree[4]->Right->Right->Right->Right = new BinaryTreeNode<char>('i');
    tree[4]->Right->Right->Right->Left = new BinaryTreeNode<char>('k');
    tree[4]->Left->Left = new BinaryTreeNode<char>('j');
    tree[4]->Left->Left->Right = new BinaryTreeNode<char>('l');

    tree[5] = new BinaryTreeNode<char>('a');
    tree[5]->Right = new BinaryTreeNode<char>('b');
    tree[5]->Right->Right = new BinaryTreeNode<char>('c');
    tree[5]->Right->Right->Left = new BinaryTreeNode<char>('d');
    tree[5]->Right->Right->Right = new BinaryTreeNode<char>('f');

    tree[6] = new BinaryTreeNode<char>('a');
    tree[6]->Right = new BinaryTreeNode<char>('b');
    tree[6]->Left = new BinaryTreeNode<char>('c');
    tree[6]->Left->Right = new BinaryTreeNode<char>('d');
    tree[6]->Left->Left = new BinaryTreeNode<char>('e');
    tree[6]->Left->Left->Right = new BinaryTreeNode<char>('f');
    tree[6]->Left->Left->Left = new BinaryTreeNode<char>('g');
    tree[6]->Left->Left->Right = new BinaryTreeNode<char>('h');
    tree[6]->Right->Left = new BinaryTreeNode<char>('i');
    tree[6]->Right->Left->Right = new BinaryTreeNode<char>('j');
    tree[6]->Right->Left->Right->Left = new BinaryTreeNode<char>('k');
    tree[6]->Right->Left->Right->Right = new BinaryTreeNode<char>('l');
    for (int i = 1; i <= 6; i++) {
        memset(print_buf, 0, sizeof(print_buf));
        print_launch(tree[i]);
        cout << PreOrder(tree[i]) << endl;
        cout << PreOrder_with_stack(tree[i]) << endl;
        cout << InOrder(tree[i]) << endl;
        cout << InOrder_with_stack(tree[i]) << endl;
        cout << PostOrder(tree[i]) << endl;
        cout << PostOrder_with_stack(tree[i]) << endl;
        cout << LeverOrder(tree[i]) << endl;
        cout << endl;
    }

}
