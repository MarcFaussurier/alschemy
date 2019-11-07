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
	ft_putendl("./scheme filepath1 filepath2 ...");
 }

void			read_eval_loop()
{
	char		*input_buffer;

	ft_putendl("mode: read eval loop");
	while (TRUE)
	{
		input_buffer = ft_read(10);
		// eval
	}
}

void			read_eval_files(char **first, char **last)
{
	ft_putendl("mode: eval files");
	while (first <= last)
	{
		ft_putstr("current file: ");
		ft_putendl(*first);
		// eval
		first += 1;
	}
}

int				main(int argc, char **argv)
{
	welcome();
	if (argc == 1)
		read_eval_loop();
	else if (!ft_strncmp(argv[1],"help",4))
		help();
	else
		read_eval_files(argv + 1, argv + argc - 1);
}
