#include "../../cube.h"

uint32_t    apply_shading(uint32_t base_col, double dist, double ao)
{
    double shade;
    uint8_t r;
    uint8_t g;
    uint8_t b;

    shade = 1.0 / (1.0 + dist * 0.1);
    shade *= ao;
    if (shade < 0.2)
        shade = 0.2;

    r = ((base_col >> 24) & 0xFF) * shade;
    g = ((base_col >> 16) & 0xFF) * shade;
    b = ((base_col >>  8) & 0xFF) * shade;

    return (r << 24) | (g << 16) | (b << 8) | 0xFF;
}
uint32_t shade_color(uint32_t base_col, double dist)
{
    double shade;
    uint8_t r, g, b;

    shade = 1.0 / (1.0 + dist * 0.0015); // gentler than wall shading
    // inverse linear fall_off equation

    r = ((base_col >> 24) & 0xFF) * shade;
    g = ((base_col >> 16) & 0xFF) * shade;
    b = ((base_col >>  8) & 0xFF) * shade;

    // return (base_col);
    return ((r << 24) | (g << 16) | (b << 8) | 0xFF);
}

uint32_t prepare_wall_color(t_parsed_data *pd, t_column_data *col, t_pos map)
{
    uint32_t base_col;
    double   shade;

    if (col->side == 1)
        base_col = WALL_SIDE;
    else
        base_col = WALL;

    (void)pd;
    (void)map;
    shade = 1.0 / (1.0 + col->perp_dist * 0.1);
    if (shade < 0.2)
        shade = 0.2;

    return (apply_shading(base_col, col->perp_dist, 1.0));
}
