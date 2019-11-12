/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   Authors: mfaussur                              +:+   +:    +:    +:+     */
/*   <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#      */
/*                                                #+#   ##    ##    #+#       */
/*                                               ###    #+./ #+    ###.fr     */
/*                                                        /   UNIV -          */
/*                                               | |  _  / ___ _ _   / |      */
/*   Created: 2019/10/06 21:03:05 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/11/12 16:25:32 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <scheme.h>
#include <libft/libft.h>

void			init_token(t_token *in)
{
	in->type            = nop;
	in->content         = malloc(1 * sizeof(char));
    in->content[0]      = '\0';
}

void			init_lexer_state(t_lexer_state *state, char *source)
{
	state->source       = source;
	state->output       = malloc(1 * sizeof(t_list*));
    state->output[0]    = NULL;
	state->current_token= malloc(1 * sizeof(t_token));
	state->output_size  = 0;
	state->escaped      = 0;
	state->comment      = 0;
	state->comments     = 0;
	state->quote        = 0;
	state->quotes       = 0;
	state->i            = 0;
	init_token          (state->current_token);
}

void			flush_char(t_lexer_state *state)
{
	int     len;

	len = strlen(state->current_token->content);
	state->current_token->content = realloc(state->current_token->content, (len + 2) * sizeof(char));
	state->current_token->content[len] = state->source[state->i];
	state->current_token->content[len + 1] = '\0';
}

void			flush(t_lexer_state *state)
{
	ft_lstadd_back(state->output, ft_lstnew(state->current_token));
	state->current_token = malloc(sizeof(t_token));
	init_token(state->current_token);
}

void			flush_call(t_lexer_state *state)
{
	state->current_token->type      = call;
	state->current_token->content   = "(";
	flush(state);
}


void			flush_end(t_lexer_state *state)
{
	state->current_token->type      = end;
	state->current_token->content   = ")";
	flush(state);
}

t_list          *lex(char *source)
{
	t_lexer_state         state;

	init_lexer_state(&state, source);
	while (source[state.i])
	{
		if (state.escaped)
		{
			if (state.quote || state.quotes)
				flush_char(&state);
			else
				write   (1, "Error, unexpected esacpe character", 34);
			continue;
			state.escaped = 0;
		}
		switch (source[state.i])
		{
			case    '(':
				if (state.comment || state.comments)
					break ;
				else if (state.quote)
					flush_char(&state);
				else if (state.quotes)
					flush_char(&state);
				else
				{
					flush(&state);
					flush_call(&state);
				}
				break;
			case    ')':
				if (state.comment || state.comments)
					break ;
				else if (state.quote)
					flush_char(&state);
				else if (state.quotes)
					flush_char(&state);
				else
				{
					flush(&state);
					flush_end(&state);
				}
				break;
			case    '\t':
				if (state.comments || state.comment)
					break ;
				else if (state.quote)
				{
					state.quote = 0;
					flush(&state);
				}
				else if (state.quotes)
					flush_char(&state);
				break ;
			case    ' ':
				if (state.comment || state.comments)
					break ;
				else if (state.quote)
				{
					state.quote = 0;
					flush(&state);
				}
				else if (state.quotes)
					flush_char(&state);
				else
					flush(&state);
				break ;
			case    '\n':
				if (state.comment)
					state.comment = 0;
				else if (state.quote)
				{
					state.quote = 0;
					flush(&state);
				}
				else if (state.quotes)
					flush_char(&state);
				break ;
			case    '\\':
				if (!state.quote && !state.quotes && !state.comment && !state.comments)
					write(1, "Escaping should be used in string and/or comments only", 54);
				else
					state.escaped = 1;
				break ;
			case    '\"':
				if (state.comment || state.comments)
					break ;
				else if (state.quotes)
				{
					state.quotes = 0;
					flush(&state);
				}
				else if (state.quote)
					flush_char(&state);
				else
				{
					flush(&state);
					init_token(state.current_token);
					state.current_token->type = string;
					state.quotes = 1;
				}
				break;
			case    '\'':
				if (state.comment || state.comments)
					break ;
				else if (state.quote)
				{
					state.quote = 0;
					flush(&state);
				}
				else if (state.quotes)
					flush_char(&state);
				else
				{
                    flush(&state);
                    init_token(state.current_token);
					state.current_token->type = string;
					state.quote = 1;
				}
				break ;
			case    ';':
				if (state.comment || state.comments)
					break ;
				else if (state.quote || state.quotes)
					flush_char(&state);
				else
					state.comment = 1;
				break ;
			case    '|':
				if (state.quote || state.quotes)
					flush_char(&state);
				if (state.i > 0 && source[state.i - 1] == '#')
					state.comments = 1;
				break ;
			case    '#':
				if (state.quote || state.quotes)
					flush_char(&state);
				if (state.i > 0 && source[state.i - 1] == '|')
					state.comments = 0;
				break ;
			default:
				if (state.comment || state.comments)
					break ;
				else if ((source[state.i] <= '9' && source[state.i] >= '0'))
					state.current_token->type = numeric;
				else if (!state.quote && !state.quotes)
					state.current_token->type = identifier;
				flush_char(&state);
				break ;
		}
		state.i         += 1;
	}
	flush(&state);
	return(state.output[0]);
}

void        dump_tokens(t_list *tokens)
{
    if (tokens && tokens->content)
	    while (TRUE)
        {
		    switch (((t_token*)tokens->content)->type)
		    {
			    case call:
				    printf("call\t\t\n");
				    break;
			    case end:
				    printf("end\t\t\n");
				    break;
			    case string:
				    printf("str\t\t%s\n", ((t_token*)tokens->content)->content);
				    break;
			    case numeric:
				    printf("num\t\t%s\n", ((t_token*)tokens->content)->content);
				    break;
			    case identifier:
				    printf("id\t\t%s\n", ((t_token*)tokens->content)->content);
				    break;
			    case nop:
				    printf("nop\t\t\n");
				    break ;
			    default:
				    break ;
		    }
            if (!tokens->next)
                return ;
            else
                tokens = tokens->next;
        }
}

