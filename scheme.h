/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   scheme.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   Authors: mfaussur                              +:+   +:    +:    +:+     */
/*   <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#      */
/*                                                #+#   ##    ##    #+#       */
/*                                               ###    #+./ #+    ###.fr     */
/*                                                        /   UNIV -          */
/*                                               | |  _  / ___ _ _   / |      */
/*   Created: 2019/10/06 21:07:27 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/11/12 15:20:03 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */

#ifndef SCHEME_H
# define SCHEME_H
# include <libft/libft.h>
/*     BASE STRUCTURES
 * ========================*/
    //  - TOKENS
typedef enum			e_token
{
						call,
						identifier,
						numeric,
						string,
						end,
						nop
}                       t_token_type;
typedef struct			s_token
{
	t_token_type		type;
	char				*content;
}						t_token;
    // - MEMORY STRUCTURATION
typedef struct          s_scope
{

    t_list              *variables;
    struct s_scope*     parent;

}                       t_scope;
typedef enum			e_cell_type
{
						_unsigned_long_long,
						_unsigned_long,
						_long_long,
						_float,
						_double,
						_long_double,
						_unsigned_int,
						_int,
						_short,
                        _string,
						_char,
						_unsigned_short,
						_unsigned_char,
						_function,
						_ptr,
                        _identifier
}						t_cell_type;
typedef struct			s_cell
{
	t_cell_type	        type;
	char				*identifier;
	void*				value;
	t_bool				locked;
	struct s_cell		*root;
	t_list				*childs;
}						t_cell;
    // - IMPLEMENTATION   SPECIFIC
typedef struct			s_lexer_state
{
	t_list				**output;
	t_token				*current_token;
	char				*source;
	unsigned int		i;
    int					output_size;
	int					escaped;
	int					comment;
	int					comments;
	int					quote;
	int					quotes;
}						t_lexer_state;
/*          RROTOTYPE
 *=========================*/
void					init_token(t_token *in);
void					init_lexer_state(t_lexer_state *state, char *source);
void					flush_char(t_lexer_state *state);
void					flush(t_lexer_state *state);
void					flush_end(t_lexer_state *state);
t_list                  *lex(char *source);
void					dump_tokens(t_list *tokens);
t_cell					*parse(t_list *tokens);
t_cell					*eval(t_cell *input);
void                    dump_cell(t_cell *input);
#endif
