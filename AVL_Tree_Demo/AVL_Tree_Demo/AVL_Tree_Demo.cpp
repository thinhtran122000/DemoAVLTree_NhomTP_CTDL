#include<iostream>
#include<conio.h>
using namespace std;

struct avl_node
{
    int data;
    struct avl_node* left;
    struct avl_node* right;
}*root;

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    else {
        return b;
    }
}

class avlTree
{
public:

    avlTree()
    {
        root = NULL;
    }

    // Chiều cao của cây
    int height(avl_node* temp)
    {
        int h = 0;
        if (temp != NULL)
        {
            int l_height = height(temp->left);
            int r_height = height(temp->right);
            int max_height = max(l_height, r_height);
            h = max_height + 1;
        }
        return h;
    }
    // Hệ số cân bằng
    int diff(avl_node* temp)
    {
        int l_height = height(temp->left);
        int r_height = height(temp->right);
        int b_factor = l_height - r_height;
        return b_factor;
    }

    // Quay phải
    avl_node* rr_rotation(avl_node* parent)
    {
        avl_node* temp;
        temp = parent->right;
        parent->right = temp->left;
        temp->left = parent;
        return temp;
    }

    // Quay trái
    avl_node* ll_rotation(avl_node* parent)
    {
        avl_node* temp;
        temp = parent->left;
        parent->left = temp->right;
        temp->right = parent;
        return temp;
    }

    // Quay trái-phải
    avl_node* lr_rotation(avl_node* parent)
    {
        avl_node* temp;
        temp = parent->left;
        parent->left = rr_rotation(temp);
        return ll_rotation(parent);
    }

    // Quay phải-trái
    avl_node* rl_rotation(avl_node* parent)
    {
        avl_node* temp;
        temp = parent->right;
        parent->right = ll_rotation(temp);
        return rr_rotation(parent);
    }

    // Cân bằng cây
    avl_node* balance(avl_node* temp)
    {
        int bal_factor = diff(temp);
        if (bal_factor > 1)
        {
            if (diff(temp->left) > 0)
                temp = ll_rotation(temp);
            else
                temp = lr_rotation(temp);
        }
        else if (bal_factor < -1)
        {
            if (diff(temp->right) > 0)
                temp = rl_rotation(temp);
            else
                temp = rr_rotation(temp);
        }
        return temp;
    }

    // Thêm node
    avl_node* insert(avl_node* root, int value)
    {
        if (root == NULL)
        {
            root = new avl_node;
            root->data = value;
            root->left = NULL;
            root->right = NULL;
            return root;
        }
        else if (value < root->data)
        {
            root->left = insert(root->left, value);
            root = balance(root);
        }
        else if (value >= root->data)
        {
            root->right = insert(root->right, value);
            root = balance(root);
        }
        return root;
    }
    // Xóa node
    avl_node* deleteNode(avl_node* root, int value)
    {
        if (root == NULL)
            return root;
        if (value < root->data)
            root->left = deleteNode(root->left, value);
        else if (value > root->data)
            root->right = deleteNode(root->right, value);

        else
        {
            if ((root->left == NULL) || (root->right == NULL))
            {
                avl_node* temp = root->left ? root->left : root->right;
                if (temp == NULL)
                {
                    temp = root;
                    root = NULL;
                }
                else
                {
                    *root = *temp;
                }
                free(temp);
            }
            else
            {
                avl_node* temp = maxValueLeftNode(root->left);
                root->data = temp->data;
                root->left = deleteNode(root->left, temp->data);
            }
        }
        if (root == NULL) return root;
        root = balance(root);

        //avl_node* bl = balance(root);

        // Nếu cây bị mất cân bằng
        // Có 4 trường hợp

        // Trường hợp trái-trái
        if (diff(root) > 1 && balance(root->left) >= 0)
            return rr_rotation(root);

        // Trường hợp trái-phải
        if (diff(root) > 1 && balance(root->left) < 0)
        {
            root->left = ll_rotation(root->left);
            return rr_rotation(root);
            //return rl_rotation(root);
        }

        // Trường hợp phải-phải
        if (diff(root) < -1 && balance(root->right) <= 0)
            return ll_rotation(root);

        // Trường hợp phải-trái
        if (diff(root) < -1 && balance(root->right) > 0)
        {
            root->right = rr_rotation(root->right);
            return ll_rotation(root);
            //return lr_rotation(root);
        }
        return root;
    }

    //Tìm giá trị lớn nhất bên trái
    avl_node* maxValueLeftNode(avl_node* node)
    {
        avl_node* current = node;
        while (current->right != NULL) {
            current = current->right;
        }
        return current;
    }
    // Cấu hình cây AVL
    void display(avl_node* ptr, int level)
    {
        int i;
        if (ptr != NULL)
        {
            display(ptr->right, level + 1);
            cout << endl;
            if (ptr == root)
                cout << "Root -> ";
            for (i = 0; i < level && ptr != root; i++)
                cout << "        ";
            cout << ptr->data;
            display(ptr->left, level + 1);
        }
    }

    // Duyệt cây L-N-R
    void inorder(avl_node* tree)
    {
        if (tree == NULL) {
            return;
        }         
        inorder(tree->left);
        cout << tree->data << "  ";
        inorder(tree->right);
    }

    // Duyệt cây N-L-R
    void preorder(avl_node* tree)
    {
        if (tree == NULL)
            return;
        cout << tree->data << "  ";
        preorder(tree->left);
        preorder(tree->right);

    }

    // Duyệt cây L-R-N
    void postorder(avl_node* tree)
    {
        if (tree == NULL)
            return;
        postorder(tree->left);
        postorder(tree->right);
        cout << tree->data << "  ";
    }
};


int main()
{
    int choice, item;
    avlTree avl;
    //clrscr();
    while (1)
    {
        cout << "\n---------------------------------------\n" << endl;
        cout << "        AVL Tree Implementation            " << endl;
        cout << "\n---------------------------------------\n" << endl;
        cout << "   [1. Insert element into the tree]       " << endl;
        cout << "   [2. Insert available AVL Tree   ]       " << endl;
        cout << "   [3. Delete element in the tree  ]       " << endl;
        cout << "   [4. Display balanced AVL Tree   ]       " << endl;
        cout << "   [5. InOrder traversal           ]       " << endl;
        cout << "   [6. PreOrder traversal          ]       " << endl;
        cout << "   [7. PostOrder traversal         ]       " << endl;
        cout << "   [8. Exit                        ]       " << endl << endl;
        cout << "   Enter your choice:. . . .:     ";
        cin >> choice;
        cout << "\n--------------------------------------\n";
        switch (choice)
        {
        case 1: // Nhập từng node
            cout << "\nHow many node you want to insert: ";
            cin >> choice;
            for (int x = 0; x < choice; x++) {
                cout << "\nEnter value to be inserted: ";
                cin >> item;
                root = avl.insert(root, item);
            }
            cout << "\nInsert successfully\n" << endl;
            break;
        case 2: // Nhập cây AVL có sẵn
            root = avl.insert(root, 3);
            root = avl.insert(root, 8);
            root = avl.insert(root, 5);
            root = avl.insert(root, 13);
            root = avl.insert(root, 15);
            root = avl.insert(root, 30);
            root = avl.insert(root, 25);
            root = avl.insert(root, 19);
            root = avl.insert(root, 11);
            cout << "\nInsert successfully\n" << endl;
            break;
        case 3: // Xóa node bất kì
            cout << "\nElement you want to delete: ";
            cin >> item;
            if (root == NULL)
            {
                cout << "\nElement is not available !\n" << endl;
                continue;
            }
            else {
                root = avl.deleteNode(root, item);
                cout << "\nDelete successfully \n" << endl;
            }
            break;
        case 4: // Hiển thị cây đã được cân bằng
            if (root == NULL)
            {
                cout << "\nTree is Empty !\n" << endl;
                continue;
            }
            cout << "\nBalanced AVL Tree:" << endl;
            avl.display(root, 1);
            break;
        case 5: // Duyệt cây L-N-R
            if (root == NULL) {
                cout << "\nTree is Empty !\n" << endl;
                continue;
            }
            else {
                cout << "\nInorder Traversal:" << endl;
                avl.inorder(root);
                cout << endl;
                break;
            }
        case 6: // Duyệt cây N-L-R
            if (root == NULL) {
                cout << "\nTree is Empty !\n" << endl;
                continue;
            }
            else
            {
                cout << "\nPreorder Traversal:" << endl;
                avl.preorder(root);
                cout << endl;
                break;
            }
        case 7: // Duyệt cây L-R-N
            if (root == NULL) {
                cout << "\nTree is Empty !\n" << endl;
                continue;
            }
            else
            {
                cout << "\nPostorder Traversal:" << endl;
                avl.postorder(root);
                cout << endl;
                break;
            }
        case 8: // Thoát chương trình
            exit(1);
            break;
        default:
            cout << "\nChoose again !\n" << endl;
        }
    }
}