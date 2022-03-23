#include <iostream>
using namespace std;
template<class Object>
class List;
template<class Object>
class ListItr;
template <class Object>
class ListNode
	{
		ListNode(const Object & theElement = Object(),ListNode * n = NULL)
			: element( theElement ),next( n ) {}
		Object element;
		ListNode *next;
	friend class List<Object>;
	friend class ListItr<Object>;
	};

template<class Object>
class ListItr
	{
	public:
		ListItr( ) : current ( NULL ){}
		bool isPastEnd( ) const
		{
			return current== NULL;
		}
		void advance( )
		{
			if( !isPastEnd( ) )
				current = current->next;
		}
		const Object & retrieve( ) const
		{
			if( isPastEnd( ) )
				return NULL;
			return current->element;
		}
	private:
		ListNode<Object> *current;
		ListItr( ListNode<Object> *theNode ) : current( theNode ) {}
	friend class List<Object>;
	};

template<class Object>
class List
	{
	public:
		List( );
		List( const List & rhs);
		~List( );
		bool isEmpty( ) const;
		void makeEmpty( );
		ListItr<Object> zeroth( ) const;
		ListItr<Object> first( ) const;
		void insert( const Object & x, const ListItr<Object> & p );
		ListItr<Object> find( const Object & x ) const;
		ListItr<Object> findPrevious( const Object & x ) const;
		int remove( const Object & x );
		const List & operator=( const List & rhs);
	private:
		ListNode<Object> *header;
	};

//--------------------------------------List-----------------------------------------
template <class Object>
List<Object>::List( )
	{
		header = new ListNode<Object>;
	}

//--------------------------------------isEmpty--------------------------------------
template <class Object>
bool List<Object>::isEmpty( ) const
	{
		return header->next== NULL;
	}

//--------------------------------------zeroth---------------------------------------
template <class Object>
ListItr<Object> List<Object>::zeroth( ) const
	{
		return ListItr<Object>( header );
	}

//--------------------------------------first----------------------------------------
template <class Object>
ListItr<Object> List<Object>::first( ) const
	{
		return ListItr<Object>( header->next );
	}

//--------------------------------------PrintList------------------------------------
template <class Object>
int printList( const List<Object> & theList )
	{
		int n = 0;
		if( theList.isEmpty( ) )
			cout<< "Empty List"<<endl;
		else
		{
			ListItr<Object> itr = theList.first();
			for(; !itr.isPastEnd(); itr.advance())
			{
				cout<<"["<<itr.retrieve()<<"] ";
				n++;
			}
		}
		cout << endl;
		return n;
	}

//--------------------------------------find-----------------------------------------
template<class Object>
ListItr<Object> List<Object>::find( const Object & x ) const
	{
		ListNode<Object> *itr = header->next;
		int A = 1;
		while( itr != NULL && itr->element != x ) {
			itr = itr->next;
		A++;
		}
		if(itr==NULL) cout<<"Find Not Found!!";
		else {
			cout<<"ListNode Address is : "<<itr<<endl;
			cout<<"Position of ListNode is : "<<A;
		}
		return ListItr<Object>( itr );
	}

//--------------------------------------remove---------------------------------------
template<class Object>
int List<Object>::remove( const Object & x )
	{
		ListItr<Object> p = findPrevious( x );
		if( p.current->next != NULL)
		{
			ListNode<Object> *oldNode = p.current->next;
			p.current->next = p.current->next->next;
			delete oldNode;
			return 1;
		}
		return 0;
	}

//--------------------------------------findPrevious---------------------------------
template <class Object>
ListItr<Object> List<Object>::findPrevious( const Object & x ) const
	{
		ListNode<Object> *itr = header;
		while( itr->next != NULL && itr->next->element != x )
		itr = itr->next;
		return ListItr<Object>( itr );
	}

//--------------------------------------insert---------------------------------------
template<class Object>
void List<Object>::insert( const Object & x,const ListItr<Object> & p )
	{
		if( p.current != NULL )
			p.current->next = new ListNode<Object>( x, p.current->next );
	}

//--------------------------------------makeEmpty------------------------------------
template <class Object>
void List<Object>::makeEmpty( )
	{
		while( !isEmpty( ) )
			remove( first( ).retrieve( ) );
	}

//--------------------------------------~List----------------------------------------
template<class Object>
List<Object>::~List( )
	{
		makeEmpty( );
		delete header;
	}

//--------------------------------------main-----------------------------------------
int main(){
	List<int> a;
	ListItr<int> b;
	//ListItr<int> c;
	b=a.zeroth();
	int Amount=0,f=0,r,n=0;
	bool exit = true;
	char choice;
	int x , l;
	do {
		system("cls");
		cout<<"====== Linked List ====== "<<endl;
		cout<<"\t1.Insert"<<endl;
		cout<<"\t2.Print"<<endl;
		cout<<"\t3.Find"<<endl;
		cout<<"\t4.Remove"<<endl;
		cout<<"\t5.FindKth"<<endl;
		cout<<"\t6.Quit"<<endl;
		cout<<"Enter : ";
		cin>>choice;
		cout<<endl;
	switch(choice) {
//--------------------------------------insert---------------------------------------
	case '1':
		char insert_choice;
		b=a.zeroth();
		cout<<"-----Insert--------\n1.Insert Front\n2.Insert Position\n3.Insert Back";
		cout<<"\nEnter : ";
		cin>>insert_choice; switch (insert_choice) {
		case '1'://front
			b=a.zeroth();
			cout<<"Enter Element : ";
			cin>>x;
			a.insert(x,b);
			cout<<endl;
			Amount++;
			system("pause");
			break;
		
		case '2': //position if(Amount>0) {
			if(Amount>0) {
			int p;
		do {
			cout<<"Enter Position (not more "<<Amount+1<<") : ";
			cin>>p;
			if(p>Amount+1) cout<<"No This Position Plase Try Again "<<endl;
		}while(p>Amount+1);
			for(int i=1; i<p; i++)
				b.advance(); 
			}
			cout<<"Enter Element : ";
			cin>>x;
			a.insert(x,b);
			cout<<endl;
			Amount++;
			system("pause"); break;
		
		case '3'://back
			b = a.findPrevious(NULL);
			cout<<"Enter Element : ";
			cin>>x;
			a.insert(x,b);
			cout<<endl;
			Amount++;
			system("pause");
			break;
	}
	break;

//--------------------------------------Print----------------------------------------
	case '2':
		Amount = printList(a);
		cout<<"Amount of ListNode : "<<Amount<<endl<<endl;
		system("pause");
		break;

//--------------------------------------find-----------------------------------------
	case '3':
		f=1;
		cout<<"Enter Element : ";
		cin>>x;
		a.find(x);
		cout<<endl<<endl;
		system("pause");
		break;

//--------------------------------------remove---------------------------------------
	case '4':
		cout<<"Enter Element : ";
		cin>>x;
		r=a.remove(x);
			if(r==1) {
				cout<<"This Element is Removed . . ."<<endl;
				Amount-=r;
			}
			else cout<<"This Element is Not Remove . . ."<<endl;
		cout<<endl;
		system("pause");
		break;

//-----------------------------------FindKth-----------------------------------------
	case '5':
		do{
		cout << "Enter Position : ";
		cin >> l;
		if (l<=n){
		}else{
		cout<<" ";}
		b = a.first();
		for(int i=1; i<l; i++){
		b.advance();
		}
		cout<<"Element of this Position is "<<b.retrieve()<<endl;
		system("pause");
		}while(l<=n);
	break;

//--------------------------------------Exit-----------------------------------------
	case '6':
		exit = false;
		break;
	}
	}while(exit);
	return 0;
}