/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   Authors: mfaussur                              +:+   +:    +:    +:+     */
/*   <marc.faussurier@etu.univ-lyon1.fr>           #+#   #+    #+    #+#      */
/*                                                #+#   ##    ##    #+#       */
/*                                               ###    #+./ #+    ###.fr     */
/*                                                        /   UNIV -          */
/*                                               | |  _  / ___ _ _   / |      */
/*   Created: 2019/10/06 11:58:20 by mfaussur    | |_| || / _ \ ' \  | |      */
/*   Updated: 2019/10/06 21:29:45 by mfaussur    |____\_, \___/_||_| |_|      */
/*                                                    /__/            .fr     */
/* ************************************************************************** */

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#include <lexer.h>
#include <parser.h>
#include <compiler.h>
#include <interpreter.h>

int     main()
{
    char* input = "(define square (lambda (a) (* a a))) \"dwadawd\" #| 025 |# 1; okok";


    compile(interpret(parse(lex(input))));
    return (0);
}
