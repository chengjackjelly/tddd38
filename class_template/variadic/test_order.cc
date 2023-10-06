
template <typename... Ts>
void fun(Ts... list);
template <typename T, typename... Ts>
void fun_helper(T first, Ts... rest);
void fun_helper();


template <typename... Ts>
void fun(Ts... list)
{
fun_helper(list...);
}
// this is used for recursing through the parameter pack
template <typename T, typename... Ts>
void fun_helper(T first, Ts... rest)
{
// do thing with first here
// drop the first element and continue
fun_helper(rest...);
}
// base case
void fun_helper()
{ }
int main(){
    fun(1,"a",3,2.0);
}