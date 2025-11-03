#include "../cube.h"

bool all_enemies_dead(t_parsed_data *pd)
{
    int i;

    if (!pd || !pd->enemies || pd->enemy_count == 0)
        return (false);

    i = 0;
    while (i < pd->enemy_count)
    {
        if (!pd->enemies[i].dead)
            return (false);
        i++;
    }
    return (true);
}

uint32_t tint_with_red(uint32_t color, float red_percentage)
{
    uint8_t r = (color >> 24) & 0xFF;
    uint8_t g = (color >> 16) & 0xFF;
    uint8_t b = (color >> 8) & 0xFF;
    
    r = r + (uint8_t)((149 - r) * red_percentage);
    g = g + (uint8_t)((6 - g) * red_percentage);
    b = b + (uint8_t)((6 - b) * red_percentage);
    
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}
