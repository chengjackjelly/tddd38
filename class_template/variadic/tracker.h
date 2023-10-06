template <typename T>
class Tracker: public T{
    public:
    static int data;
    Tracker():T(){
        data++;
    }
    Tracker(T const &other): T(other){
        data++;
    }
    ~Tracker() {
        data--;
    }

};
template <typename T>
int Tracker<T>::data=0;

template <typename T>
int count(){
    return Tracker<T>::data;
}