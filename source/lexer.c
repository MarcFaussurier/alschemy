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
/*   Updated: 2019/10/06 21:24:58 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <lexer.h>

void    init_token(token *in)
{
    in->type            = nop;
    in->content         = malloc(1 * sizeof(char));
}

void    init_lexer_state(lexer_state *state, char *source)
{
    state->source       = source;
    state->output       = malloc(1 * sizeof(token*));
    state->current_token= malloc(1 * sizeof(token));
    state->output_size  = 0;
    state->escaped      = 0;
    state->comment      = 0;
    state->comments     = 0;
    state->quote        = 0;
    state->quotes       = 0;
    state->i            = 0;

    init_token          (state->current_token);
}

void    flush_char(lexer_state *state)
{
    int     len;

    len = strlen(state->current_token->content);
    state->current_token->content = realloc(state->current_token->content, (len + 2) * sizeof(char));
    state->current_token->content[len] = state->source[state->i];
    state->current_token->content[len + 1] = '\0';
}

void    flush(lexer_state *state)
{

    state->output_size  += 1;
    state->output       = realloc(state->output, state->output_size * sizeof(void*));
    state->output[state->output_size - 1] = state->current_token;
    state->current_token = malloc(sizeof(token));
    init_token(state->current_token);
}

void    flush_call(lexer_state *state)
{
        state->current_token->type      = call;
        state->current_token->content   = "(";
        flush           (state);
}


void    flush_end(lexer_state *state)
{
        state->current_token->type      = end;
        state->current_token->content   = ")";
        flush           (state);
}

token   **lex(char *source)
{

    lexer_state         state;

    init_lexer_state    (&state, source);
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
            /*\
            |*| Begin / end functions calls
            \*/ case    '(':
                    if (state.comment || state.comments)
                        break;
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
                        break;
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
            /*\
            |*| Spaces
            \*/ case    '\t':
                    if (state.comments || state.comment)
                        break;
                    else if (state.quote)
                    {
                        state.quote = 0;
                        flush(&state);
                    }
                    else if (state.quotes)
                    {
                        flush_char(&state);
                    }
                    break;
                case    ' ':
                    if (state.comment || state.comments)
                        break;
                    else if (state.quote)
                    {
                        state.quote = 0;
                        flush(&state);
                    }
                    else if (state.quotes)
                    {
                        flush_char(&state);
                    }
                    else
                    {
                        flush(&state);
                        //flush(<#lexer_state *state);
                    }
                    break;
                case    '\n':
                    if (state.comment)
                    {
                        state.comment = 0;
                    }
                    else if (state.quote)
                    {
                        state.quote = 0;
                        flush(&state);
                    }
                    else if (state.quotes)
                    {
                       flush_char(&state);
                    }
                    break;
            /*\
            |*| Escaping
            \*/ case    '\\':
                    if (!state.quote && !state.quotes && !state.comment && !state.comments)
                    {
                        write(1, "Escaping should be used in string and/or comments only", 54);
                    }
                    else
                    {
                        state.escaped = 1;
                    }
                    break;
            /*\
            |*| Strings
            \*/ case    '\"':
                    if (state.comment || state.comments)
                        break;
                    else if (state.quotes)
                    {
                        state.quotes = 0;
                        flush(&state);
                    }
                    else if (state.quote)
                    {
                        flush_char(&state);
                    }
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
                        break;
                    else if (state.quote)
                    {
                        state.quote = 0;
                        flush(&state);
                    }
                    else if (state.quotes)
                    {
                        flush_char(&state);
                    }
                    else
                    {
                        state.current_token->type = string;
                        state.quote = 1;
                    }
                    break;
            /*\
            |*| Comments
            \*/ case    ';':
                    if (state.comment || state.comments)
                        break;
                    else if (state.quote || state.quotes)
                        flush_char(&state);
                    else
                        state.comment = 1;
                    break;
                case    '|':
                    if (state.quote || state.quotes)
                        flush_char(&state);
                    if (state.i > 0 && source[state.i - 1] == '#')
                        state.comments = 1;
                    break;
                case    '#':
                    if (state.quote || state.quotes)
                        flush_char(&state);
                    if (state.i > 0 && source[state.i - 1] == '|')
                        state.comments = 0;
                    break;
                    break;
            /*\
            |*| Default
            \*/ default     :
                    if (state.comment || state.comments)
                        break;
                    else if ((source[state.i] <= '9' && source[state.i] >= '0'))
                        state.current_token->type = numeric;
                    else if (!state.quote && !state.quotes)
                        state.current_token->type = identifier;
                    flush_char(&state);
                    break;

        }
        state.i         += 1;
    }
    flush               (&state);
    state.current_token->type = eof;
    flush(&state);
    return              (state.output);
}

void    dump_tokens(token **tokens)
{
    int                 i;

    i = 0;
    while ((tokens[i])->type != eof)
    {
        switch ((tokens[i])->type)
        {
            case call:
                printf("call\t\t\n");
                break;
            case end:
                printf("end\t\t\n");
                break;
            case string:
                printf("str\t\t%s\n", tokens[i]->content);
                break;
            case numeric:
                printf("num\t\t%s\n", tokens[i]->content);
                break;
            case identifier:
                printf("id\t\t%s\n", tokens[i]->content);
                break;
            case nop:
               // printf("nop\t\t\n");
                break;
            default:
                break;
        }
        i += 1;
    }
}

