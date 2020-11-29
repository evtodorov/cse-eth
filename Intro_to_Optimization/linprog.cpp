#include <iostream>
#include <vector>
#include <cstddef>
#include <array>
#include <cassert>

using std::cout;
using std::endl;

typedef std::size_t size_type;
typedef unsigned int index;
typedef double value_type;
typedef std::vector<index> index_vec;
typedef std::vector<value_type> value_vec;
typedef std::vector< std::vector<value_type> > value_mat;

void print(value_mat A)
{
    for (auto r : A){
        for (auto c : r){
            cout << c << "\t";
        }
        cout << endl;
    }
    cout << endl;
}
void print(value_vec v)
{

        for (auto c : v){
            cout << c << "\t";
        }
        cout << endl << endl;
}

inline value_vec operator+ (value_vec& a, value_vec& b)
{
    size_type len = a.size();
    assert(len == b.size());
    value_vec c;
    c.resize(len);

    for (int i=0;i<len;++i)
    {
        c[i] = a[i] + b[i];
    }

    return c;
}
inline value_vec operator- (value_vec& a, value_vec& b)
{
    size_type len = a.size();
    assert(len == b.size());
    value_vec c;
    c.resize(len);

    for (int i=0;i<len;++i)
    {
        c[i] = a[i] - b[i];
    }

    return c;;
}

inline value_vec operator* (value_vec& a, value_type b)
{
    size_type len = a.size();
    value_vec c;
    c.resize(len);

    for (int i=0;i<len;++i)
    {
        c[i] = a[i] * b;
    }

    return c;
}
inline value_vec operator/ (value_vec& a, value_type b)
{
    return a * (1./b);
}

void RREF (value_mat& A)
{
    size_type rows = A.size();
    size_type cols = A[0].size();

    bool running = 1;
    index curRow = 0;
    index curCol = 0;

    while (curCol < rows) //go down
    {
        if(A[curRow][curCol]==0 or curCol >= cols)
        {
            ++ curRow;
            ++ curCol;
            continue;
        }
        A[curRow] = A[curRow] / A[curRow][curCol];

        for (int i=curRow+1; i<rows; ++i){

             if(A[curRow][curCol]==0){continue;}
             cout << "cr " << curRow << endl;
                cout << "i " << i << endl;
            value_vec temp = (A[curRow] * A[i][curCol]);
            A[i] = A[i] - temp;
            //print(A);
        }

        ++ curRow;
        ++ curCol;
    }
    --curRow;--curCol;
    while (curRow > 0) //now go back up
    {
        if(A[curRow][curCol]==0 or curCol >= cols)
        {
            -- curRow;
            -- curCol;
            continue;
        }
         A[curRow] = A[curRow] / A[curRow][curCol];

        for (int i=curRow-1; i>=0; --i){
                if(A[curRow][curCol]==0){continue;}
            value_vec temp = (A[curRow] * A[i][curCol]);
            A[i] = A[i] - temp;
           // print(A);
        }
        -- curRow;
        -- curCol;
    }

}

void push_row

class ShortTableau
{
private:
    value_vec A_; /// A[ROW][COL]
    value_vec b_;
    value_vec c_;
    index_vec x_;
    index_vec basic_;
    index_vec nonBasic_;
public:
    ShortTableau(value_mat& A, value_vec& b, value_vec& c)
    /// A is unsorted
    {
        //shroten A

    };
    void findBase(value_mat& A)
    {
        size_type initRows = A.size();
        size_type initCols = A[0].size();
        value_vec sumCols;
        sumCols.resize(initCols);

    }
};


int main ()
{
    //do stuff
    value_mat A = {{2,4},{4,10},{32,1},{2,4}};
    for (auto r : A){
        for (auto c : r){
            cout << c << "\t";
        }
        cout << endl;
    }

    RREF(A);

    for (auto r : A){
        for (auto c : r){
            cout << c << "\t";
        }
        cout << endl;
    }

    return 0;
}
