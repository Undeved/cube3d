#include "../cube.h"

static void check_file(t_parsed_data *pd)
{
    int fd;

    fd = open("data.undvd", O_RDWR | O_CREAT, 0644);
    if (fd == -1)
    {
        print_error("Error\nCan't Open File\n");
        mind_free_all(EXIT_FAILURE);
    }

}

void    save_to_data_file(t_parsed_data *pd)
{
    check_file(pd);
}
