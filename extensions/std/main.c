#include <scheme.h>

int		main()
{
	t_cell 	*test;

	test = create_cell(_int, malloc(sizeof(int)), "");
	dump_cell(test);
}
