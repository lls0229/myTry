/*************************************************************************
    > File Name: 041.cpp
    > Author: lls
    > Mail: lls840308420@163.com
    > Created Time: 2023年02月01日 星期三 20时37分57秒
 ************************************************************************/
#ifdef DEBUG


#include<iostream>
using namespace std;

int main(int argc, char **argv){

	cout << "DEBUG" << endl;
	return 0;
}
#elif CODE

#include<iostream>
int main() {
	std::cout << "CODE" << std::endl;

	return 0;
}

#endif

