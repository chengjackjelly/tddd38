#include<cstddef>
#include<stdexcept>

class queue_error : std::runtime_error {
    public:
    queue_error(const std::string& message) : std::runtime_error(message) {}
};


template<typename T, size_t N>
class Queue{
private:
    int head;
    int tail;
    int size;
    T data[N]{};

public:
    Queue(): head(0),tail(0),size(0){
        static_assert(N > 0, "N must be positive");
    }
    // Queue(Queue const &other){

    // }
    // Queue(Queue &&other);
    // ~Queue();
    template<size_t N2>
    Queue<T,N+N2> copy_and_expand(){
        Queue<T,N+N2> ret;
        Queue<T,N> tmp{*this};
        while(!tmp.empty()){
            ret.enqueue(tmp.dequeue());
        }
        return ret;
    }

    void enqueue(T value){
        if(!full()){
        data[tail]=value;
        tail=(tail+1)%N;
        size++;}
        else{
            throw queue_error("enqueue values into an already full queue");
        }
    }
    T dequeue(){
        if(!empty()){
        T ret=data[head];
        head=(head+1)%N;
        size--;
        return ret;}
        else{
            throw queue_error("dequeue a value from an empty queue");
        }
    }
    bool empty() const{
        return size==0;
    }
    bool full(){
        return size==N;
    }
    void clear();
    T const & front() const {
        if(!empty()){
        T const & ret= data[head];
        return ret;}
        else{
            throw queue_error("access the front of an empty queue.");
        }
    }
    

};