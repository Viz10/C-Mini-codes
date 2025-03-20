#include "myfunc.h"
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

extern void func1();
extern void func2();
extern void func3();
extern void func4();
extern void func5();
extern void func6();

int main() {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	///func1();
	///func2();
	//func3();
	//func4();
	//func5();
	func6();

	return 0;
}