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
/*   Created: 2019/10/06 21:13:24 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/10/06 21:32:34 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */

#include <lexer.h>
#include <parser.h>

cell *parse(token **tokens)
{
    int         i;
    cell        *output;

    dump_tokens(tokens);
    i = 0;
    output = 0;
    (void) tokens;
    return (output);
}
