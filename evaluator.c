#include <libft/libft.h>
#include <scheme.h>


t_scope     *create_scope(t_scope *parent)
{
    t_scope     *output;

    output = malloc(sizeof(t_scope));
    output->parent = parent;
    output->variables = malloc(1 * sizeof(t_list*));
    *(output->variables) = NULL;
    return (output);
}

t_cell      *create_cell(t_cell_type type, void* value, char *identifier)
{
    t_cell      *output;

    output = malloc(sizeof(t_cell));
    output->value = value;
    output->type = type;
    output->identifier = identifier;
    return (output);
}

t_cell      *create_int_cell(int n, char *label)
{
    return (create_cell(_int, &n, label));
}

t_cell      *create_func_cell(t_cell*(*callback)(t_cell*) , char *label)
{
    return (create_cell(_function, callback, label));
}

t_cell      *create_string_cell(char *str, char *label)
{
    return (create_cell(_string, str, label));
}

void        scope_add_back(t_scope *scope,t_cell *value)
{
    ft_lstadd_back(scope->variables, ft_lstnew(value));
}


t_cell      *resolve(char *label, t_scope *scope)
{
    t_list      *tmp;

    if (!scope || !label || ft_strlen(label) == 0)
        return (NULL);
    tmp = *(scope->variables);
    if (!tmp)
        return (NULL);
    while (TRUE)
    {
        if (tmp->content)
        {
            return (tmp->content);
        }
        tmp = tmp->next;
        if (!tmp)
            break;
    }
    if (scope->parent)
        return(resolve(label, scope->parent));
    else
        return (NULL);
}

t_cell      *eval(t_cell *input, t_scope *parent)
{
    t_scope     *scope;
    t_cell      *occ;
   // t_cell*     (*lambda)(t_cell*);

    scope = create_scope(parent);
    if (input->type == _identifier)
    {
            occ = resolve(input->identifier, scope);
            if (occ)
                ft_putendl("ok2");
            //    occ = (t_cell*)((t_list*)*(scope->variables))->content;
    //    dump_cell(occ);
     //   if (occ)
      /*      switch (occ->type)
            {
                case _function:
                    lambda = (t_cell*(*)(t_cell*)) occ->value;
                    return (lambda(eval(input, scope)));
                default:
                    return (occ);
            }*/

    }

    // eval childs

    return (0);
}
