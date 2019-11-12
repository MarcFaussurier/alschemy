/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mfaussur <mfaussur@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 12:36:10 by mfaussur     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 18:39:38 by mfaussur    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft/libft.h>
#include <scheme.h>
#include <unistd.h>
#include <fcntl.h>

const char		*version = "0.01";

void			welcome()
{
	ft_putendl("----------------------");
	ft_putendl("Scheme interpreter");
	ft_putstr("version: ");
	ft_putendl((char*)version);
	ft_putendl("----------------------");
}

void			help()
{
	ft_putendl("Scheme interpreter help");
	ft_putendl("Usage: pass no arguments for interative read/eval loop, or files path.");
	ft_putendl("./scheme");
    ft_putendl("(+ 6 5) .. or ");
    ft_putendl("./scheme filepath1 filepath2 ...");
 }

void            interpret(char *input_buffer)
{
    t_list      *tokens = lex(input_buffer);
    ft_putendl("TOKENS: -------------");
    dump_tokens(tokens);
    t_cell      *evalme = parse(tokens);
    ft_putendl("PARSED CELL: --------");
    dump_cell(evalme);
    t_cell      *result = eval(evalme);
    ft_putendl("RESULT: -------------");
    dump_cell(result);
}

void			read_eval_loop()
{
	char		*input_buffer;

	ft_putendl("mode: read eval loop");
	while (TRUE)
	{
		input_buffer = ft_read(10);
        if (!ft_strlen(input_buffer))
            continue ;
        else if (!ft_strncmp(input_buffer, "help", 5))
            help();
        else if (!ft_strncmp(input_buffer, "exit", 5))
            break ;
        else
            interpret(input_buffer);
    }
}

void			read_eval_files(char **first, char **last)
{
	ft_putendl("mode: eval files");
	while (first <= last)
	{
		ft_putstr("current file: ");
		ft_putendl(*first);
        interpret(ft_read_fd(0, open(*first, O_WRONLY)));
        first += 1;
	}
}

int				main(int argc, char **argv)
{/*
    t_cell      cell;
    t_cell      cell2;
    t_cell      cell3;
    t_cell      cell4;
    t_cell      cell5;

    cell.type = _identifier;
    cell.identifier = ft_strdup("*");

    cell2.type = _int;
    cell2.value = malloc(1*sizeof(int));
    *(int)cell2.value = 42;



    cell3.type = _int;
    cell3.value = malloc(1*sizeof(int));
    *(int)cell3.value = 42;


    cell4.type = _identifier;
    cell4.identifier = ft_strdup("*");


    cell5.type = _int;
    cell5.value = malloc(1*sizeof(int));
    *(int)cell5.value = 42;

    cell.childs = ft_lstnew(NULL);
    ft_lstadd_back(&cell.childs, cell2);
*/
	welcome();
	if (argc == 1)
		read_eval_loop();
	else if (!ft_strncmp(argv[1],"help",5))
		help();
	else
		read_eval_files(argv + 1, argv + argc - 1);
}
