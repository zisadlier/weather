#include "App.hpp"

#include <iostream>

using namespace std;

int main(int argc, char *argv[]) 
{
	try 
	{
		unique_ptr<App> app = make_unique<App>(argc, argv);
		app->run();
	}
	catch (runtime_error &e)
	{
		cerr << e.what() << endl;
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}