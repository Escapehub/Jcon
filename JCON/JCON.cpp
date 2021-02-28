// JCON.cpp : Defines the entry point for the application.
//

#include "JCON.h"

int main()
{
	Jcon j;

	j.set("name", "Callum");
	j.set("age", 22);
	j.set("Isabout", TRUE);
	j.set("PI", 3.142);

	j.stringify();
	
	return 0;
}
