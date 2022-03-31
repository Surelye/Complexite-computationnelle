#include <iostream>

using namespace std;

struct point
{
    int data;
    point * left;
    point * right;
};

point * Tree(int n, point * p)
{
    point * r;
    int nl, nr;

    if (n == 0) 
    { 
        p = NULL; 
        return p;
    }

    nl = n / 2;
    nr = n - nl - 1;
    r = new point;

    cin >> r->data;

    r->left = Tree(nl, r->left);
    r->right = Tree(nr, r->right);
    p = r;

    return p;
}

void Run(point * p, int level)
{
    if (p)
    {
        Run(p->left, level + 1);

        for (int i = 0; i < level; i++) 
            cout << "  ";

        cout << p->data << "\n";
        Run(p->right, level + 1);
    }
}
int main()
{
    point * p = 0;
    int n;

    cout << "INPUT THE NUMBER OF ELEMENTS:\n";
    cin >> n;

    p = Tree(n, p);
    Run(p, n);

    return (EXIT_SUCCESS);
}