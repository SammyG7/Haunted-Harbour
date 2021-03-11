template<int count>
class Counter{
public :
	Counter():c(0){}
int c;
bool operator()(){
	if (c ++ == count){
		c = 0;
		return true;
	}else{
		return false;
	}
}
};