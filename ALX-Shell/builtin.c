#include "shell.h"

/**
 * exit_shell - exits the shell
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: exits with a given exit status
 * (0) if info.argv[0] != "exit"
*/
int exit_shell(info_t *info)
{
    int status = 0;

    if (info->argv[1])
    {
        int checker = error_atoi(info->argv[1]);
        if (checker == -1)
        {
            info->status = 2;
            print_error_message(info, "Illegal number: ");
            print_string(info->argv[1]);
            print_character('\n');
            return 1;
        }
        info->err_num = checker;
        return -2;
    }

    info->err_num = -1;
    return -2;
}

/**
 * change_directory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
*/
int change_directory(info_t *info)
{
    char *current_dir, *new_dir, buffer[1024];
    int chdir_ret;

    current_dir = getcwd(buffer, 1024);
    if (!current_dir)
        _puts("TODO: >>getcwd failure emsg here<<\n");

    if (!info->argv[1])
    {
        new_dir = get_environment_variable(info, "HOME=");
        if (!new_dir)
            chdir_ret = chdir((new_dir = get_environment_variable(info, "PWD=")) ? new_dir : "/");
        else
            chdir_ret = chdir(new_dir);
    }
    else if (_strcmp(info->argv[1], "-") == 0)
    {
        if (!get_environment_variable(info, "OLDPWD="))
        {
            _puts(current_dir);
            _putchar('\n');
            return 1;
        }
        _puts(get_environment_variable(info, "OLDPWD="));
        _putchar('\n');
        chdir_ret = chdir((new_dir = get_environment_variable(info, "OLDPWD=")) ? new_dir : "/");
    }
    else
    {
        chdir_ret = chdir(info->argv[1]);
    }

    if (chdir_ret == -1)
    {
        print_error_message(info, "can't cd to ");
        print_string(info->argv[1]);
        print_character('\n');
    }
    else
    {
        set_environment_variable(info, "OLDPWD", get_environment_variable(info, "PWD="));
        set_environment_variable(info, "PWD", getcwd(buffer, 1024));
    }

    return 0;
}

/**
 * help - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 * constant function prototype.
 * Return: Always 0
*/
int help(info_t *info)
{
    char **args = info->argv;

    _puts("help call works. Function not yet implemented \n");
    if (0)
        _puts(*args); /* temp att_unused workaround */

    return 0;
}

/**
 * display_history - displays the history list, one command by line, preceded
 *              with line numbers, starting at 0.
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
*/
int display_history(info_t *info)
{
    print_list(info->history);
    return 0;
}

/**
 * unset_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
*/
int unset_alias(info_t *info, char *alias)
{
    char *equals, temp;
    int result;

    equals = find_character(alias, '=');
    if (!equals)
        return 1;

    temp = *equals;
    *equals = '\0';
    result = delete_node_at_index(&(info->alias),
                                  get_node_index(info->alias, node_starts_with(info->alias, alias, -1)));
    *equals = temp;

    return result;
}

/**
 * set_alias - sets alias to string
 * @info: parameter struct
 * @str: the string alias
 *
 * Return: Always 0 on success, 1 on error
*/
int set_alias(info_t *info, char *alias)
{
    char *equals;

    equals = find_character(alias, '=');
    if (!equals)
        return 1;

    if (!*++equals)
        return unset_alias(info, alias);

    unset_alias(info, alias);
    return add_node_end(&(info->alias), alias, 0) == NULL;
}


/**
 * print_alias - prints an alias string
 * @node: the alias node
 *
 * Return: Always 0 on success, 1 on error
*/
int print_alias(list_t *alias_node)
{
    char *equals, *alias_str;

    if (alias_node)
    {
        equals = find_character(alias_node->str, '=');
        alias_str = alias_node->str;

        while (alias_str <= equals)
            _putchar(*alias_str++);

        _putchar('\'');
        _puts(equals + 1);
        _puts("'\n");

        return 0;
    }

    return 1;
}

/**
 * alias - mimics the alias builtin (man alias)
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
*/
int alias(info_t *info)
{
    int i;
    char *equals;
    list_t *alias_node = NULL;

    if (info->argc == 1)
    {
        alias_node = info->alias;
        while (alias_node)
        {
            print_alias(alias_node);
            alias_node = alias_node->next;
        }
        return 0;
    }

    for (i = 1; info->argv[i]; i++)
    {
        equals = find_character(info->argv[i], '=');
        if (equals)
            set_alias(info, info->argv[i]);
        else
            print_alias(node_starts_with(info->alias, info->argv[i], '='));
    }

    return 0;
}
