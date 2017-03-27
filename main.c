#include <stdio.h>
#include <stdlib.h>
#include "krypt.h"

int main(int argc, char* argv[])
{
	if ( argc < 3 ){
		PRINT_USAGE;
	}

	toggle_all_files_in(argv[0], argv[1], argv[2]);

	return 0;
}
