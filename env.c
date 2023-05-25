#include "shell.h"

/**
 * print_environment - prints the current environment
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
*/
int print_environment(info_t *info)
{
    print_list_str(info->env);
    return 0;
}

/**
 * get_environment_variable - gets the value of an environ variable
 * @info: Structure containing potential arguments. Used to maintain
 * @name: env var name
 *
 * Return: the value
*/
char *get_environment_variable(info_t *info, const char *name)
{
    list_t *node = info->env;
    char *value = NULL;

    while (node)
    {
        if (starts_with(node->str, name))
        {
            value = strchr(node->str, '=');
            if (value)
                return value + 1; // Skip the '=' character
        }
        node = node->next;
    }

    return NULL;
}

/**
 * set_environment_variables - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: Always 0
*/
int set_environment_variables(info_t *info)
{
    if (info->argc != 3)
    {
        print_string("Incorrect number of arguments\n");
        return 1;
    }

    if (set_environment_variable(info, info->argv[1], info->argv[2]) == 0)
        return 1;

    return 0;
}

/**
 * unset_environment_variables - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
*/
int unset_environment_variables(info_t *info)
{
    if (info->argc == 1)
    {
        print_string("Too few arguments.\n");
        return 1;
    }

    for (int i = 1; i < info->argc; i++)
        unset_environment_variable(info, info->argv[i]);

    return 0;
}

/**
 * populate_environment_list - populates env linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
*/
int populate_environment_list(info_t *info)
{
    list_t *node = NULL;
    size_t i = 0;

    while (environ[i] != NULL)
    {
        add_node_end(&node, environ[i], 0);
        i++;
    }

    info->env = node;
    return 0;
}

/**
 * copy_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
*/
char **copy_environ(info_t *info)
{
    if (!info->environ || info->env_changed)
    {
        info->environ = list_to_string_array(info->env);
        info->env_changed = 0;
    }

    return info->environ;
}

/**
 * unset_environment_variable - Remove an environment variable
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 *  Return: 1 on delete, 0 otherwise
 * @var: the string env var property
*/
int unset_environment_variable(info_t *info, char *var)
{
    list_t *node = info->env;
    size_t index = 0;
    char *p;

    if (!node || !var)
        return 0;

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->env), index);
            index = 0;
            node = info->env;
            continue;
        }
        node = node->next;
        index++;
    }

    return info->env_changed;
}

/**
 * set_environment_variable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 *  Return: Always 0
*/
int set_environment_variable(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return 0;

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return 1;
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return 0;
        }
        node = node->next;
    }
    add_node_end(&(info->env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return 0;
}
