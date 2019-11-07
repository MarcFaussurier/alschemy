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


static void		init_parser_state(t_parser_state *state)
{
	state->is_flushable		= FALSE;
	state->i				= -1;
	state->output			= malloc(1 * sizeof(t_cell));
	state->output[0].type	= nop;
	state->buffer			= 0;
	state->str				= 0;
	state->double_num		= 0;
	state->positive_num		= 0;
	state->num				= 0;
	state->type				= _int;
}

t_cell			*parse(t_token **tokens)
{
	t_parser_state	state;

	init_parser_state(&state);
	while (tokens[++state.i]->type != eof)
	{
		switch (tokens[state.i]->type)
		{
			case identifier:
				state.buffer = malloc(1 * sizeof(t_cell));
				break ;
			case call:
				state.buffer = parse(tokens + state.i);
				break ;
			case end:
				break ;
			case numeric:
				break ;
			case string:
				break ;
			case nop:
				break ;
			case eof:
				break ;
			default :
				break ;
		}
		state.i += 1;
	}
	return(state.output);
}
