#include <bits/stdc++.h>
using namespace std;
class node {
    public :
    char c;
    unsigned long long  freq;
    node *l, *r; 
    node(char c, unsigned long long freq)
    {
        this->c = c;
        this->freq = freq;
        l = r = NULL;
    }
};
class myComparator {
    public:
    bool operator()(node* l, node* r)
 
    {
        return (l->freq > r->freq);
    }
};
void writecodes(struct node* root, string str,fstream& writefile,map<char, vector<bool> >& table)
{
 
    if (!root)
        return;
 
    if (root->c != '~')
    {
        writefile << root->c << " " << str << "\n";
        for(int i=0;i<str.length();++i)
            table[root->c].push_back(str[i]=='1');
        /*cout<<endl<< root->c;
         for(vector<bool> :: const_iterator i=table[root->c].begin();i!=table[root->c].end();++i)
        cout << *i;*/

        
    }
 
    writecodes(root->l, str + "0",writefile,table);
    writecodes(root->r, str + "1",writefile,table);
}

void huffmancodegenerator(unsigned long long  *a,fstream& writefile,map<char, vector<bool> >& table)
{
    struct node *left, *right, *top;
 
    priority_queue<node*, vector<node*>, myComparator> pq;

    for (int i = 0; i < 256; ++i)
        if(a[i]!=0)
        pq.push(new node((char)i, a[i]));
 
       while (pq.size() != 1) {

        left = pq.top();
        pq.pop();
 
        right = pq.top();
        pq.pop();
        top = new node('~', left->freq + right->freq);
        top->l = left;
        top->r = right;
 
        pq.push(top);
    }
    writecodes(pq.top(), "",writefile,table);

}
/*void createmap(fstream& readfile)
{
    readfile >> noskipws;

    map<char, vector<bool> > table;
    char c;
    while(readfile >> c)
    cout <<c;
    vector<bool> t;
    while(getline(readfile,s))
    {
        cout<<s;
        c = s[0];
        for(int i=2;i<s.length();i++)
            t.push_back(bool(s[i]));
        cout<<"here";
        table[c]=t;
        t.clear();
    }

    for(vector<bool> :: const_iterator i=table[c].begin();i!=table[c].end();++i)
        cout << *i;
}
*/

void huffmancompress(fstream& writefile,map<char, vector<bool> >& table)
{
    writefile << "@@@###$$$";
    char c;
    fstream readfile;
    readfile.open("compressed.txt", ios::in);
    while(readfile >> c)
        for(vector<bool> :: const_iterator i=table[c].begin();i!=table[c].end();++i)
            writefile << *i;   

}
 
int main()
{
 
    fstream readfile, writefile;
    writefile.open("compressedhuff.txt",ios :: out);
    readfile.open("compressed.txt", ios::in);
    readfile >> noskipws;
    char c;
    unsigned long long a[256] = {0};
    while(readfile >> c)
        a[c]++;
    map<char, vector<bool> > table;
    huffmancodegenerator(a,writefile,table);
    huffmancompress(writefile,table);
    return 0;
}