/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   Authors: mfaussur                              +:+   +:    +:    +:+     */
/*   <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#      */
/*                                                #+#   ##    ##    #+#       */
/*                                               ###    #+./ #+    ###.fr     */
/*                                                        /   UNIV -          */
/*                                               | |  _  / ___ _ _   / |      */
/*   Created: 2019/11/12 20:10:17 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/11/13 09:34:37 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
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
        case _function:
            ft_putstr("FUNC\t");
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
        ft_putstr("childs: ");
        ft_putnbr(ft_lstsize(cell->childs) - 1);
        ft_putendl("");
        if (ft_lstsize(cell->childs) > 1)
        {
            ft_putendl("{");
            dump_cell_childs(cell);
            ft_putendl("}");
        }
    }
}

t_list          *get_after_call(t_list *tokens)
{
    int         level;
    t_bool      updated;

    if (!tokens)
        return (NULL);
    updated = FALSE;
    level = 0;
    while (TRUE)
    {
        if (((t_token*)tokens->content)->type == call)
        {
            level += 1;
            updated = TRUE;
        }else if (((t_token*)tokens->content)->type == end)
            level -= 1;
        if ((updated && (level == 0)))
        {
            return (tokens->next);
        }
        if (!(tokens = tokens->next))
            break ;
    }
    return (tokens);
}

t_cell			*parse(t_list *tokens)
{
    t_cell      *output;
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
            break ;
		case call:
            free(output);
			output = parse(tokens->next); // should be id
		    tokens = tokens->next->next;
            while (tokens)
            {

                if (((t_token*)tokens->content)->type == end)
                    break;
                else if (((t_token*)tokens->content)->type == nop)
                {
                    tokens = tokens->next;
                    continue ;
                }
                tmp = parse(tokens);
                if (!tmp)
                    break ;
                ft_lstadd_back(&output->childs, ft_lstnew(tmp));
                if (((t_token*)tokens->content)->type == call)
                    tokens = get_after_call(tokens);
                else
                    tokens = tokens->next;
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
