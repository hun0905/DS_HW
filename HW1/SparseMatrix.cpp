#include<iostream>
using namespace std;
class SparseMatrix;

class MatrixTerm
{
friend SparseMatrix;
private:
    int row,col,value;
};

class SparseMatrix
{
public:
    SparseMatrix(int r =1, int c = 1, int t = 1);
    SparseMatrix FastTranspose();
    SparseMatrix Add(SparseMatrix b);
    SparseMatrix Multiply(SparseMatrix b);
    void Resizing(int NewSize);
    void copy(MatrixTerm* head , MatrixTerm* end , MatrixTerm* OutTerm);
    void NewTerm(const int row, const int col , const int value);
    void GetValue(int pos,int &row , int &col , int &value);
    friend istream &operator>>(istream &is , SparseMatrix &Sm);
    friend ostream &operator<<(ostream &is , SparseMatrix &Sm);
private:
    int rows, cols, terms ,capacity;
    MatrixTerm *smArray;
};
SparseMatrix :: SparseMatrix(int r , int c , int t) 
{
    rows = r;
    cols = c;
    terms = 0;
    capacity = t;
    smArray = new MatrixTerm[capacity];
}
SparseMatrix SparseMatrix::Multiply(SparseMatrix b)
{
    if(cols != b.rows)
        throw"Incompatible matrices";

    SparseMatrix bXpose = b.FastTranspose();
    SparseMatrix d(rows , b.cols );//output matrix
    int currRowIndex = 0,currRowBegin = 0,currRowA = smArray[0].row;

    if(terms == capacity)
       Resizing(terms+1);
    bXpose.Resizing(bXpose.terms+1);
    smArray[terms].row = rows;
    bXpose.smArray[b.terms].row = b.cols;
    bXpose.smArray[b.terms].col = -1;//
    int sum = 0;
    while(currRowIndex < terms)
    {
        int currColB = bXpose.smArray[0].row;
        int currColIndex = 0;
        while (currColIndex <= b.terms)
        {
            if(smArray[currRowIndex].row != currRowA)
            {
                d.NewTerm(currRowA,currColB,sum);
                sum = 0;
                currRowIndex = currRowBegin;
                while(bXpose.smArray[currColIndex].row == currColB)
                    currColIndex++;

                currColB = bXpose.smArray[currColIndex].row;
            }
            else if(bXpose.smArray[currColIndex].row != currColB) //
            {
                d.NewTerm(sum,currRowA,currColB);
                sum = 0;
                currRowIndex = currRowBegin;
                currColB = bXpose.smArray[currColIndex].row;
            }
            else
            {
                if(smArray[currRowIndex].col < bXpose.smArray[currColIndex].col)
                    currRowIndex++;
                else if(smArray[currRowIndex].col == bXpose.smArray[currColIndex].col)
                {
                    sum += smArray[currRowIndex].value*bXpose.smArray[currColIndex].value;
                    currRowIndex++;
                    currColIndex++;
                }
                else
                    currColIndex++;
            }
        }
        while(smArray[currRowIndex].row == currRowA)
            currRowIndex++;
        currRowBegin = currRowIndex;
        currRowA = smArray[currRowIndex].row;
    }
    
    return d;
}
SparseMatrix SparseMatrix::Add(SparseMatrix b)
{
    SparseMatrix tmp(rows,cols);
    int apos=0,bpos=0;
    while(apos < terms || bpos < b.terms)
    {
        if(smArray[apos].col > b.smArray[bpos].col || (smArray[apos].col == b.smArray[bpos].col && smArray[apos].row > b.smArray[bpos].row) || apos == terms )
        {
            tmp.NewTerm(b.smArray[bpos].row,b.smArray[bpos].col,b.smArray[bpos].value);
            bpos++;
        }
        else if(smArray[apos].col == b.smArray[bpos].col  && smArray[apos].row == b.smArray[bpos].row  && bpos!= terms && apos != terms )
        {
            tmp.NewTerm(smArray[apos].row,smArray[apos].col,b.smArray[bpos].value+smArray[apos].value);
            bpos++;
            apos++;
        }
        else
        {
            tmp.NewTerm(smArray[apos].row,smArray[apos].col,smArray[apos].value);
            apos++;
        }
    }
    return tmp;
}
void SparseMatrix::GetValue(int pos,int &row,int &col, int &value)
{
    row = smArray[pos].row;
    col = smArray[pos].col;
    value = smArray[pos].value; 
}
void SparseMatrix::NewTerm(int row,int col , int value)
{
    if(value != 0)
    {
        if(terms >= capacity)
        {
           capacity = terms*2;
           Resizing(capacity);
        }
        smArray[terms].row = row;
        smArray[terms].col = col;
        smArray[terms].value = value;
        terms++;
    }
}
void SparseMatrix::Resizing(int NewSize)
{
    if(NewSize < terms) throw"Error";
    MatrixTerm *temp = new MatrixTerm[NewSize];
    copy(smArray,smArray+terms,temp);
    delete[]smArray;
    smArray = temp;
    capacity = NewSize;
} 
void SparseMatrix::copy(MatrixTerm* head , MatrixTerm* end , MatrixTerm* OutTerm)
{
    int i = 0;
    for(MatrixTerm *t = head; t < end  ; ++t)
    {
        OutTerm[i] = *t;
        i++;
    }
}
SparseMatrix SparseMatrix::FastTranspose()
{
    SparseMatrix b(cols, rows, terms);
    delete []b.smArray;
    b.smArray = new MatrixTerm[terms];
    if(terms > 0)
    {
        int *rowSize = new int[cols];
        int *rowStart = new int[cols];
        for(int i = 0 ; i < cols ; ++i)
            rowSize[i]=0;
        for(int i = 0 ; i <terms ; ++i)
            rowSize[smArray[i].col]++;
        rowStart[0] = 0 ;
        for(int j = 1 ; j <terms ; ++j)
            rowStart[j] = rowStart[j-1]+rowSize[j-1];
        for(int i = 0 ; i < terms ; ++i)
        {
            int j = rowStart[smArray[i].col];
            b.smArray[j].row = smArray[i].col;
            b.smArray[j].col = smArray[i].row;
            b.smArray[j].value = smArray[i].value;
            b.terms++;//add by me
            rowStart[smArray[i].col]++;
        }
        delete [] rowSize;
        delete [] rowStart;
    }
    return b;
}
istream &operator>>(istream &is, SparseMatrix &Sm)
{
    int row=0 , col=0 , value;
    char c;
    bool b = true;
    while((cin.peek()  == '\n' || cin.peek() == 'q'))
        cin.ignore();
    while (b)
	{
        c = cin.peek();
        while(c == ' ')
        {
            cin.ignore(1);
		    c = cin.peek();
        } 
        if(c == 'q')
            break;
        else if(c =='\n')
        {
            cin.ignore(1);
            col=0;
            row++;
            if(row==Sm.rows)
                Sm.rows++;
        }
        c = cin.peek();
        while(c == ' ')
        {
            cin.ignore(1);
		    c = cin.peek();
        } 
        if(c == 'q')
        {
            Sm.rows--;
            break;
        }
        is >> value;	
        if(value != 0)
		    Sm.NewTerm(row,col,value);
        if(row == 0)
            if(col == Sm.cols)
                Sm.cols++;
        if(col < Sm.cols)
            col++;
	}
    return is;
}
ostream &operator<<(ostream &os , SparseMatrix &Sm)
{
    int ArrayPos=0;
    int rowGet,colGet,valueGet;
    Sm.GetValue(0,rowGet,colGet,valueGet);
    for(int i = 0 ; i < Sm.rows ; ++i)
    {
        for(int j = 0 ; j < Sm.cols ; ++j)
        {
            
            if( rowGet == i &&  colGet == j)
            {
                cout<<valueGet;
                ArrayPos++;
                Sm.GetValue(ArrayPos,rowGet,colGet,valueGet);
            }
            else
               cout<<0;
            if(j != Sm.cols)
                cout<<" ";
        }
        cout<<endl;
    }
    return os;
}
int main()
{
    SparseMatrix sm,sm2,result ;
    cout<<"輸入矩陣，結束輸入q"<<endl;
    cin>>sm;
    cout<<"SparseMatrix1: \n"<<sm;  
    cout<<"輸入矩陣,結束輸入q"<<endl;
    cin>>sm2;
    cout<<"SparseMatrix2: \n"<<sm2;
    result = sm.Multiply(sm2);
    cout<<"result of Multiply\n"<<result;
}