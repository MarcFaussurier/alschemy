/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lexer.h                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   Authors: mfaussur                              +:+   +:    +:    +:+     */
/*   <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#      */
/*                                                #+#   ##    ##    #+#       */
/*                                               ###    #+./ #+    ###.fr     */
/*                                                        /   UNIV -          */
/*                                               | |  _  / ___ _ _   / |      */
/*   Created: 2019/10/06 21:07:27 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/10/06 21:11:20 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

typedef enum            e_token
{
                        call,
                        identifier,
                        numeric,
                        string,
                        end,
                        nop,
                        eof

}                       token_type;


typedef struct          s_token
{

    token_type          type;
    char                *content;

}                       token;


typedef struct          s_lexer_state
{
    token               **output;
    token               *current_token;
    char                *source;
    int                 output_size;
    int                 i;
    int                 escaped;
    int                 comment;
    int                 comments;
    int                 quote;
    int                 quotes;

}                       lexer_state;

void                    init_token(token *in);

void                    init_lexer_state(lexer_state *state, char *source);

void                    flush_char(lexer_state *state);

void                    flush(lexer_state *state);

void                    flush_end(lexer_state *state);

token                   **lex(char *source);

void                    dump_tokens(token **tokens);

#endif
