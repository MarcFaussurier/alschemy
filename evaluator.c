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
    output->childs = malloc (1 * sizeof(t_list*));
    *(output->childs) = NULL;
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

    (void) scope;
    if (0 == ft_lstsize(*(scope->variables)))
    {
        if (scope->parent)
            return (resolve(label, scope->parent));
        else
            return (NULL);
    }
    else
    {
        tmp = *(scope->variables);
        while (TRUE)
        {
            if (!(ft_strncmp((char*)((t_cell*)tmp->content)->identifier, label, ft_strlen(label) + 1)))
            {
                return (tmp->content);
            }
            tmp = tmp->next;
            if (!tmp)
                break ;
        }
    }
    return (NULL);
}

t_cell      *eval(t_cell *input, t_scope *parent)
{
    t_scope     *scope;
    t_cell      *occ;
    t_cell*     (*lambda)(t_cell*);
    t_list      *tmp;

    if (!input)
        return (0);
    scope = create_scope(parent);
    if (ft_lstsize(*(input->childs)) > 0)
    {
        tmp = *(input->childs);
        while (TRUE)
        {
            tmp->content = eval((t_cell*)tmp->content, scope);
            tmp = tmp->next;
            if (!tmp)
                break ;
        }
    }
    if (input->type == _identifier)
    {
        occ = resolve(input->identifier, scope);
        if (occ)
            switch (occ->type)
            {
                case _function:
                    lambda = occ->value;
                    return (lambda(input));
                default:
                    return (occ);
            }

    }

    // eval childs

    return (input);
}
