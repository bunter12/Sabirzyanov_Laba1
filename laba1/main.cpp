#include <iostream>
#include <string>
#include "pipeline.h"
#include "nps.h"

using namespace std;

int main() {
	nps odin;
	odin.SetName("52");
	cout << odin.GetName();
}