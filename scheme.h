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

#ifndef SCHEME_H
# define SCHEME_H
# include <libft/libft.h>

typedef enum			e_token
{
						call,
						identifier,
						numeric,
						string,
						end,
						nop,
						eof
}                       t_token_type;
typedef struct			s_token
{
	t_token_type		type;
	char				*content;
}						t_token;
typedef struct			s_lexer_state
{
	t_token				**output;
	t_token				*current_token;
	char				*source;
	int					output_size;
	int					i;
	int					escaped;
	int					comment;
	int					comments;
	int					quote;
	int					quotes;
}						t_lexer_state;
void					init_token(t_token *in);
void					init_lexer_state(t_lexer_state *state, char *source);
void					flush_char(t_lexer_state *state);
void					flush(t_lexer_state *state);
void					flush_end(t_lexer_state *state);
t_token					**lex(char *source);
void					dump_tokens(t_token **tokens);
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
						_char,
						_unsigned_short,
						_unsigned_char,
						_function,
						_ptr
}						t_cell_type;
typedef struct			s_cell
{
	t_cell_type	type;
	char				*identifier;
	void*				value;
	t_bool				locked;
	struct s_cell		*root;
	t_list				*childs;
}						t_cell;
typedef struct			s_parser_state
{
	t_bool				is_flushable;
	unsigned int		i;
	t_cell				*output;
	t_cell				*buffer;
	char				*str;
	double				double_num;
	unsigned long long	positive_num;
	long long			num;
	t_cell_type			type;
}						t_parser_state;
t_cell					*parse(t_token **tokens);
t_cell					*eval(t_cell *input);
#endif
