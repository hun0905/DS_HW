#include<iostream>
using namespace std;
struct Triple{int row,col,value;};
class Matrix;
class MatrixNode
{
friend class Matrix;
friend istream&operator>>(istream&,Matrix&);
friend ostream& operator<<(ostream&, Matrix&); 
private:
	MatrixNode *down , *right;
	bool head;
	union {
		MatrixNode *next; 
		Triple triple;
	};
	MatrixNode(bool, Triple*);
};

MatrixNode::MatrixNode(bool b, Triple *t) // constructor 
{
	head = b;
	if (b) 
	{// row/column header node
		right = down = this; 
	}
	else
	{
        triple = *t; // element node
    }
}
class Matrix
{
friend istream& operator>>(istream&, Matrix&); 
friend ostream& operator<<(ostream&, Matrix&); 
friend Triple;
public:
	~Matrix(){;} // destructor 
	Matrix operator+ (const Matrix& b) const;
	Matrix operator* (Matrix& b) const;
	Matrix Transpose();
	void del();
	Matrix(){};
	Matrix(Matrix &b);
private:
    MatrixNode *headnode;
	
};
Matrix::Matrix(Matrix &b)
{
	Triple s;
	s.row = b.headnode->triple.row;
	s.col = b.headnode->triple.col;
	s.value = b.headnode->triple.value;
	int p = max(s.row,s.col);
	headnode = new MatrixNode(false,&s);
	if(p == 0)
	{
		headnode->right = headnode;
	}
	MatrixNode **head = new MatrixNode *[p];
	MatrixNode **head_p  = new MatrixNode *[p];
	
	for(int i = 0 ; i < p ; i++)
	{
		head[i] = new MatrixNode(true,0);
		head_p[i] = head[i];
	}
	for(int i = 0 ; i < p-1 ; i++)
	{
		head[i]->next = head[i+1];
		head[i]->right = head[i];
	}
	head[p-1]->next = headnode;
	headnode->right = head[0];
	MatrixNode *last = head[0];
	int currentRow = 0;
	MatrixNode *tmp ;
	MatrixNode *row_a;
	tmp = b.headnode->right;
	row_a = tmp;

	for(int i = 0 ; i <s.value ;)
	{
		Triple t;
		tmp = tmp->right;
		if(tmp->head == true)
			tmp = tmp->next;
		if(tmp->head == false)
		{
			t.row = tmp->triple.row;
			t.col = tmp->triple.col;
			t.value = tmp->triple.value;
			if (t.row > currentRow) { // end of current row
				last->right = head[currentRow];
				currentRow = t.row;
				last = head[currentRow];
			}
			last->right = new MatrixNode(false, &t);
			last = last->right;
			head_p[t.col]->down = last;
			head_p[t.col] = head_p[t.col]->down;
			i++;
		}
	}
	last->right = head[currentRow];
	for(int i = 0 ; i < s.col ; i++)
		head_p[i]->down = head[i];
	
	
}
void Matrix::del()
{
	MatrixNode *tmp = headnode->right;
	for(MatrixNode *h = tmp ; h->head!=false ;h=h->next)
	{
		for(MatrixNode *n = h->right;n->head!= true ;)
		{
			MatrixNode *del = n;
			n = n->right;
			delete del;
		}
	}
	for(MatrixNode *n =tmp;n->head!= false ;)
	{
		MatrixNode *del = n;
		n = n->next;
		delete del;
	}
	delete headnode;
}
Matrix Matrix::operator*(Matrix& b) const
{
	
	Matrix c; 
	c = b.Transpose();
	if(headnode->triple.col != c.headnode->triple.col)
		throw"cannot multiple";
	MatrixNode* Nodea = headnode->right;
	MatrixNode* Nodec = c.headnode->right;
	int sum = 0 ;
	int term = 0;
	Triple s;
	s.row = headnode->triple.row;
	s.col = c.headnode->triple.row;
	Matrix matrix;	
	int p = max(s.row,s.col);
	matrix.headnode = new MatrixNode(false,&s);
	if(p == 0)
	{
		matrix.headnode->right = matrix.headnode;
		return matrix;
	}
	MatrixNode **head = new MatrixNode *[p];
	MatrixNode **head_p  = new MatrixNode *[p];
	MatrixNode *tmp;
	for(int i = 0 ; i < p ; i++)
	{
		head[i] = new MatrixNode(true,0);
		head_p[i] = head[i];
	}
	for(int i = 0 ; i < p-1 ; i++)
	{
		head[i]->next = head[i+1];
		head[i]->right = head[i];
	}
	
	head[p-1]->next = matrix.headnode;
	matrix.headnode->right = head[0];
	MatrixNode *last = head[0];
	int currentRow = 0;
	MatrixNode *row_a = headnode->right;
	MatrixNode *row_c = c.headnode->right;
	int ra = 0;
	int rc = 0;
	
	while(row_a != headnode)
	{
		Triple t;
		Nodea = row_a->right;
		Nodec = row_c->right;
		sum = 0;
		while(Nodea->head !=true && Nodec->head != true)
		{
		 	if(Nodea->triple.col == Nodec->triple.col)
			{
		 		sum+= Nodea->triple.value*Nodec->triple.value;
		 		Nodea = Nodea->right;
				Nodec = Nodec->right;
			}
			else if(Nodea->triple.col < Nodec->triple.col)
		 		Nodea = Nodea->right;
		 	else
				Nodec = Nodec->right;
		}
		if(sum != 0)
		{
			term++;
			t.row = ra;
			t.col = rc;
			t.value = sum;
			if (t.row > currentRow) { // end of current row
				last->right = head[currentRow];
				currentRow = t.row;
				last = head[currentRow];
			}
			last->right = new MatrixNode(false, &t);
			last = last->right;
			head_p[t.col]->down = last;
			head_p[t.col] = head_p[t.col]->down;
		}	
		row_c = row_c->next;
		rc++;
		if(row_c == c.headnode)
		{
			ra++;
			rc = 0;
			row_a = row_a->next;
			row_c = row_c->right;
		}
	}
	last->right = head[currentRow];
	for(int i = 0 ; i < s.col ; i++)
		head_p[i]->down = head[i];
	matrix.headnode->triple.value = term;
	return matrix;
}

Matrix Matrix::Transpose()
{
	
	Matrix matrix;
	Triple s;
	s.row = headnode->triple.col ; s.col = headnode->triple.row; s.value = headnode->triple.value;
	int p = max(s.row,s.col);
	matrix.headnode = new MatrixNode(false,&s);
	if(p == 0)
	{
		matrix.headnode->right = matrix.headnode;
		return matrix;
	}
	MatrixNode **head = new MatrixNode *[p];
	MatrixNode **head_p  = new MatrixNode *[p];
	
	for(int i = 0 ; i < p ; i++)
	{
		head[i] = new MatrixNode(true,0);
		head_p[i] = head[i];
	}
	for(int i = 0 ; i < p-1 ; i++)
	{
		head[i]->next = head[i+1];
		head[i]->right = head[i];
	}
	head[p-1]->next = matrix.headnode;
	matrix.headnode->right = head[0];
	MatrixNode *last = head[0];
	int currentRow = 0;
	MatrixNode *tmp;
	tmp = headnode->right;
	int term = 0;;
	while(term < headnode->triple.value)
	{
		
		if(tmp->down->head == true)
			tmp = tmp->down->next->down;
		else 
			tmp = tmp->down;
		if(tmp->head == false)
		{
			term++;
			Triple t;
			t.row = tmp->triple.col;
			t.col = tmp->triple.row;
			t.value = tmp->triple.value;
			if (t.row > currentRow) { // end of current row
				last->right = head[currentRow];
				currentRow = t.row;
				last = head[currentRow];
			}
			last->right = new MatrixNode(false, &t);
			last = last->right;
			head_p[t.col]->down = last;
			head_p[t.col] = head_p[t.col]->down;
		}
	}
	last->right = head[currentRow];
	for(int i = 0 ; i < s.col ; i++)
	head_p[i]->down = head[i];
	
	return matrix;
}
Matrix Matrix::operator+(const Matrix& b) const 
{
	int v = 0;
	Matrix matrix;
	if(headnode == 0)
		throw"SparseMatrix have different dimension.";
	if(headnode->triple.row != b.headnode->triple.row || headnode->triple.col != b.headnode->triple.col  )
		throw"SparseMatrix have different dimension.";
	Triple s;
	s.row = headnode->triple.row ; s.col = headnode->triple.col; //value還不知道
	int p = max(s.row,s.col);
	matrix.headnode = new MatrixNode(false,&s);
	
	if(p == 0)
	{
		matrix.headnode->right = matrix.headnode;
	}
	MatrixNode **head = new MatrixNode *[p];
	MatrixNode **head_p  = new MatrixNode *[p];
	MatrixNode *tmp;
	for(int i = 0 ; i < p ; i++)
	{
		head[i] = new MatrixNode(true,0);
		head_p[i] = head[i];
	}
	for(int i = 0 ; i < p-1 ; i++)
	{
		head[i]->next = head[i+1];
	}
	head[p-1]->next = matrix.headnode;
	matrix.headnode->right = head[0];
	MatrixNode *last = head[0];
	int currentRow = 0;
	MatrixNode* aNode = headnode->right->right;
	MatrixNode* bNode = b.headnode->right->right;
	while(aNode->head == true )
		aNode = aNode->next->right;
	while(bNode->head == true )
		bNode = bNode->next->right;
	int aTerm=0,bTerm=0;
	while(aTerm<headnode->triple.value ||  bTerm<b.headnode->triple.value )
	{
		Triple t;
		int r,c,val;
		if(aTerm<headnode->triple.value &&  bTerm<b.headnode->triple.value )
		{
			if(aNode->triple.col == bNode->triple.col && aNode->triple.row == bNode->triple.row )
			{
				r =  aNode->triple.row ; c = aNode->triple.col; val = aNode->triple.value +  bNode->triple.value;
				aTerm++;
				bTerm++;
				if(aNode->right->head == true)
					aNode = aNode->right->next->right;
				else
					aNode = aNode->right;

				if(bNode->right->head == true)
					bNode = bNode->right->next->right;
				else
					bNode = bNode->right;
			}
			else if( aNode->triple.row < bNode->triple.row || (aNode->triple.row == bNode->triple.row)&&aNode->triple.col < bNode->triple.col  )
			{
				aTerm++;
				r =  aNode->triple.row ; c = aNode->triple.col; val = aNode->triple.value;

				if(aNode->right->head == true)
					aNode = aNode->right->next->right;
				else
					aNode = aNode->right;
				
			}
			else
			{
				bTerm++;
				r =  bNode->triple.row ; c = bNode->triple.col; val = bNode->triple.value;
				if(bNode->right->head == true)
					bNode = bNode->right->next->right;
				else
					bNode = bNode->right;
			}
			v++;
		}
		else if(aTerm>=headnode->triple.value)
		{
			bTerm++;
			r =  bNode->triple.row ; c = bNode->triple.col; val = bNode->triple.value;
			if(bNode->right->head == true)
				bNode = bNode->right->next->right;
			else
				bNode = bNode->right;
			v++;
		}
		else if(bTerm>=b.headnode->triple.value)
		{
			aTerm++;
			r =  aNode->triple.row ; c = aNode->triple.col; val = aNode->triple.value;
			if(aNode->right->head == true)
				aNode = aNode->right->next->right;
			else
					aNode = aNode->right;
			v++;
		}
		t.row = r ; t.col = c ; t.value = val;
		if (t.row > currentRow) { // end of current row
			last->right = head[currentRow];
			currentRow = t.row;
			last = head[currentRow];
		}
		last->right = new MatrixNode(false, &t);
		last = last->right;
		head_p[t.col]->down = last;
		head_p[t.col] = head_p[t.col]->down;
		
	}	
	headnode->triple.value = v;
	last->right = head[currentRow];
	for(int i = 0 ; i < s.col ; i++)
		head_p[i]->down = head[i];
	
	return matrix;
}
istream& operator>>(istream& is, Matrix& matrix)
{
	Triple s;
	cout<<"input dimension"<<endl;
	is>>s.row>>s.col>>s.value;
	cout<<"input node"<<endl;
	int p = max(s.row,s.col);
	matrix.headnode = new MatrixNode(false,&s);
	if(p == 0)
	{
		matrix.headnode->right = matrix.headnode;
		return is;
	}
	MatrixNode **head = new MatrixNode *[p];
	MatrixNode **head_p  = new MatrixNode *[p];
	MatrixNode *tmp;
	for(int i = 0 ; i < p ; i++)
	{
		head[i] = new MatrixNode(true,0);
		head_p[i] = head[i];
	}
	for(int i = 0 ; i < p-1 ; i++)
	{
		head[i]->next = head[i+1];
		head[i]->right = head[i];
	}
	head[p-1]->next = matrix.headnode;
	matrix.headnode->right = head[0];
	MatrixNode *last = head[0];
	int currentRow = 0;
	
	for(int i = 0 ; i <s.value ; i++)
	{
		Triple t;
		is >> t.row >> t.col >> t.value;
		if (t.row > currentRow) { // end of current row
			last->right = head[currentRow];
			currentRow = t.row;
			last = head[currentRow];
		}
		last->right = new MatrixNode(false, &t);
		last = last->right;
		head_p[t.col]->down = last;
		head_p[t.col] = head_p[t.col]->down;
		
	}
	last->right = head[currentRow];
	for(int i = 0 ; i < s.col ; i++)
		head_p[i]->down = head[i];
	
	return is;
	
}
ostream& operator<<(ostream& os,  Matrix& matrix) 
{
	
	MatrixNode *tmp = matrix.headnode->right;
	
	for(MatrixNode *n = matrix.headnode->right ; n->head != false; n = n->next)
	{
		for(MatrixNode *m = n->right ; m->head != true ; m = m->right)
		{
			cout<<"("<<m->triple.row<<" "<<m->triple.col<<" "<<m->triple.value<<")";
			cout<<endl;
		}
	}
}

	

int main()
{
	Matrix a,b,add,mul,tra;
	cout<<"input matrix a"<<endl;
	cin>>a;
	cout<<"output matrix a"<<endl;
	cout<<a;
	cout<<"input matrix b"<<endl;
	cin>>b;
	cout<<"output matrix b"<<endl;
	cout<<b;
	cout<<"output matrix a+b"<<endl;
	add = a+b;
	cout<<add;
	add.del();
	cout<<"output matrix a*b"<<endl;
	mul = a*b;
	cout<<mul;
	mul.del();
	cout<<"output matrix a*Transpose()"<<endl;
	tra = a.Transpose();
	cout<<tra;
	tra.del();
	cout<<"copy a to c by copy constructor"<<endl;
	Matrix c(a);
	cout<<"output c"<<endl;
	cout<<c;
}