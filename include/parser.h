/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parser.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   Authors: mfaussur                              +:+   +:    +:    +:+     */
/*   <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#      */
/*                                                #+#   ##    ##    #+#       */
/*                                               ###    #+./ #+    ###.fr     */
/*                                                        /   UNIV -          */
/*                                               | |  _  / ___ _ _   / |      */
/*   Created: 2019/10/06 21:11:55 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/10/06 21:26:36 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */


#ifndef PARSER_H
# define PARSER_H
# include <lexer.h>


typedef struct          s_cell
{

    void                **cell;
    char                *label;
    long                value;

}                       cell;

cell                    *parse(token **tokens);

#endif
