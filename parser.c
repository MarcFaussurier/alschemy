/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: mfaussur <mfaussur@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/11/07 14:25:07 by mfaussur     #+#   ##    ##    #+#       */
/*   Updated: 2019/11/07 14:45:47 by mfaussur    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <libft/libft.h>
#include <scheme.h>


void            dump_cell_type(t_cell *cell)
{
    ft_putstr("\t\t");
    switch(cell->type)
    {
        case _int:
            ft_putstr("INT\t");
            break;
        case _string:
            ft_putstr("STR\t");
            break ;
        case _identifier:
            ft_putstr("ID\t");
            break;
        default:
            break;
    }
}

void            dump_cell_data(t_cell *cell)
{
    switch(cell->type)
    {
        case _int:
            ft_putnbr(*((int*)cell->value));
            break;
        case _string:
            ft_putstr((char*)cell->value);
            break;
        case _identifier:
            ft_putstr(cell->identifier);
            break;
        default:
            break;
    }
    ft_putstr("\n");
}

void            dump_cell_childs(t_cell *cell)
{
    t_list      *data;

    data = cell->childs;
    while (TRUE)
    {
        if (data->content && ((t_cell*)data->content)->type != nop)
            dump_cell((t_cell*)data->content);
        if (!(data = data->next))
            break ;
    }
}

void            dump_cell(t_cell *cell)
{
    if (cell && cell->type != nop)
    {
        dump_cell_type(cell);
        dump_cell_data(cell);
        if (ft_lstsize(cell->childs) > 1)
        {
            ft_putendl("{");
            dump_cell_childs(cell);
            ft_putendl("}");
        }
    }
}

t_cell			*parse(t_list *tokens)
{
    t_cell      *output;
    t_bool      stopme;
    t_cell      *tmp;

    output = malloc(1 * sizeof(t_cell));
    if (!output || !tokens)
        return (NULL);
    output->childs = ft_lstnew(NULL);
    switch (((t_token*)tokens->content)->type)
	{
		case identifier:
            output->type = _identifier;
            output->identifier = ft_strdup(((t_token*)tokens->content)->content);
            break;
		case call:
            free(output);
			output = parse(tokens->next); // should be id
		    tokens = tokens->next->next;
            stopme = FALSE;
            if (tokens)
                while (!stopme)
                {
                    tmp = parse(tokens);
                    if (!tmp)
                        stopme = TRUE;
                    ft_lstadd_back(&output->childs, ft_lstnew(tmp));
                    if (!(tokens = tokens->next))
                        stopme = TRUE ;
                }
            break ;
		case end:
			return (NULL);
            break ;
		case numeric:
            output->type = _int;
            output->value = malloc(1 * sizeof(int));
            *((int*)output->value) = ft_atoi(((t_token*)tokens->content)->content);
			break ;
		case string:
            output->type = _string;
            output->value = ft_strdup(((t_token*)tokens->content)->content);
			break ;
		case nop:
            return(parse(tokens->next));
			break ;
		default:
			break ;
	}
	return(output);
}
