#include "shell.h"

/**
 * print_string - prints an input string
 * @str: the string to be printed
 *
 * Return: Nothing
*/
void print_string(char *str)
{
    int i = 0;

    if (!str)
        return;
    while (str[i] != '\0')
    {
        print_character(str[i]);
        i++;
    }
}

/**
 * print_character - writes the character c to stderr
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/
int print_character(char c)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(2, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * print_character_to_fd - writes the character c to given fd
 * @c: The character to print
 * @fd: The filedescriptor to write to
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
*/
int print_character_to_fd(char c, int fd)
{
    static int i;
    static char buf[WRITE_BUF_SIZE];

    if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
    {
        write(fd, buf, i);
        i = 0;
    }
    if (c != BUF_FLUSH)
        buf[i++] = c;
    return 1;
}

/**
 * print_string_to_fd - prints an input string
 * @str: the string to be printed
 * @fd: the filedescriptor to write to
 *
 * Return: the number of chars put
*/
int print_string_to_fd(char *str, int fd)
{
    int i = 0;

    if (!str)
        return 0;
    while (*str)
    {
        i += print_character_to_fd(*str++, fd);
    }
    return i;
}

/**
 * error_atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
*/
int error_atoi(char *s)
{
    int i = 0;
    unsigned long int result = 0;

    if (*s == '+')
        s++;
    for (i = 0; s[i] != '\0'; i++)
    {
        if (s[i] >= '0' && s[i] <= '9')
        {
            result *= 10;
            result += (s[i] - '0');
            if (result > INT_MAX)
                return -1;
        }
        else
            return -1;
    }
    return result;
}

/**
 * print_error_message - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
*/
void print_error_message(info_t *info, char *error_str)
{
    print_string(info->fname);
    print_string(": ");
    print_decimal(info->line_count, STDERR_FILENO);
    print_string(": ");
    print_string(info->argv[0]);
    print_string(": ");
    print_string(error_str);
}

/**
 * print_decimal - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
*/
int print_decimal(int input, int fd)
{
    int (*print_char)(char) = print_character;
    int i, count = 0;
    unsigned int absolute_value, current;

    if (fd == STDERR_FILENO)
        print_char = print_character_to_fd;
    if (input < 0)
    {
        absolute_value = -input;
        print_char('-');
        count++;
    }
    else
        absolute_value = input;
    current = absolute_value;
    for (i = 1000000000; i > 1; i /= 10)
    {
        if (absolute_value / i)
        {
            print_char('0' + current / i);
            count++;
        }
        current %= i;
    }
    print_char('0' + current);
    count++;

    return count;
}

/**
 * convert_to_string - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
*/
char *convert_to_string(long int num, int base, int flags)
{
    static char *array;
    static char buffer[50];
    char sign = 0;
    char *ptr;
    unsigned long n = num;

    if (!(flags & CONVERT_UNSIGNED) && num < 0)
    {
        n = -num;
        sign = '-';
    }
    array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
    ptr = &buffer[49];
    *ptr = '\0';

    do
    {
        *--ptr = array[n % base];
        n /= base;
    } while (n != 0);

    if (sign)
        *--ptr = sign;
    return ptr;
}

/**
 * remove_comments_from_buffer - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
*/
void remove_comments_from_buffer(char *buffer)
{
    int i;

    for (i = 0; buffer[i] != '\0'; i++)
    {
        if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
        {
            buffer[i] = '\0';
            break;
        }
    }
}
