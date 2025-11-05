#include "../cube.h"

static int	un_isalpha(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (1);
	return (0);
}

static void read_username(t_parsed_data *pd)
{
    char    username[20];
    ssize_t bytes_read;
    int     i;

    print_comm("Enter Username: ");
    bytes_read = read(STDIN_FILENO, username, 19);
    if (bytes_read == -1)
        mind_free_all(EXIT_FAILURE);
    else if (bytes_read > 17)
    {
        print_error("Error\nUsername Too Long.\n");
        mind_free_all(EXIT_FAILURE);
    }
    else if (bytes_read < 4)
    {
        print_error("Error\nUsername Too Short.\n");
        mind_free_all(EXIT_FAILURE);
    }
    username[bytes_read] = '\0';
    pd->score.username = allocate_gc(ft_substr(username, 0, ft_strlen(username) - 1));
    i = 0;
    while (pd->score.username[i])
    {
        if (!un_isalpha(pd->score.username[i]))
        {
            print_error("Error\nUsername Must Have Only a-z or A-Z\n");
            mind_free_all(EXIT_FAILURE);
        }
        i++;
    }
    printf("your username is: %s\n", pd->score.username);
}

void    get_user(t_parsed_data *pd)
{
    read_username(pd);
    save_to_data_file(pd);
}
