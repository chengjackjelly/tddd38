#include <iostream>
#include <cassert>
#include <sstream>

// Originally taken from: 2022-03-17 Assignment #4
// Modified so that it doesn't require type converting operators.
template<typename T>
class Stack{
	private:
	T data[100];
	int top;
	public:
	template<typename... Ts>
	Stack(Ts... list) {
		top=-1;
		count_helper(list...);
	}
	template<typename U, typename... Ts>
	void count_helper(U first, Ts... rest){
		top++;
		data[top]=first;
		count_helper(rest...);
	}
	void count_helper(){}
	bool operator==(T value){
		std::cout<<data[top]<<std::endl;
		return data[top]==value;
	}
	bool is_empty(){
		return top==-1;
	}
	Stack<T>& operator<<(T a){
		top+=1;
		if(top>=100){
			std::cerr<<"max size is 100";
			exit(-1);
		}
		data[top]=a;
		return *this;
	}
	Stack<T>& operator>>(T& a){
		if(top==-1){
			std::cout<<"empty stack";
			exit(-1);
		}
		a=data[top];
		top-=1;
		return *this;
	}
	int getTop(){
		return top;
	}
	T getData(int index){
		return data[index];
	}
};
template<typename T>
std::ostringstream& operator<<(std::ostringstream& os,Stack<T> stack){
	int t=stack.getTop();
	for(int i=t;i>=0;i--){
		os<<stack.getData(i)<<" ";
	}
	return os;

}
int main()
{
    {
	Stack<int> st { 6, 5, 4 };

	// 4 should be at the top of the stack
	assert( st == 4 );
	
	// pushing 3, 2 and 1 to the stack
	st << 3 << 2 << 1;

	// now 1 should be at the top
	assert( st == 1 );

	std::ostringstream oss { };
	oss << st;
	std::cout<<oss.str()<<std::endl;
	assert( oss.str() == "1 2 3 4 5 6 ");

	// popping into a, b and c as a chained operator call.
	int a, b, c;
	st >> a >> b >> c;

	assert( a == 1 );
	assert( b == 2 );
	assert( c == 3 );

	// pop the values one by one
	int i { 4 };
	while (st.is_empty())
	{
	    int x;
	    st >> x;

	    assert(x == i);
	    ++i;
	}
    }
}
