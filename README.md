
# Project Clips:

Menu UI and character selection :

![[main_menu.gif]]

Game play footage :

![[game_play.gif]]

![[slingshot.gif]]

# 1337 Ways To Die (The Game) :

1337 ways to die is the game we created for our [cub3d](https://harm-smits.github.io/42docs/projects/cub3d) project.\
You can play the game here hosted --> [Play it online](itchio)

of course as our game is an actual game it needs UI and a main menu.
## Main Menu :

here you will be introduced into the UI system I'll explain later on in this documentation.\
like clickable and hover-able buttons.

- START GAME : launches the game and takes you to the in game world.
- CHARACTERS : lets you choose your starting character.
- EXIT : quits the game cleanly.

![[main_menu.png]]

## Characters :

here you can decide your character and playing style, each character you choose\
comes with a different weapon, with different attributes like ammo and damage.

![[characters_bg.png]]

| Character | Weapon     | Damage | Ammo   | Playstyle                                |
| --------- | ---------- | ------ | ------ | ---------------------------------------- |
| Jesse     | Slingshot  | High   | low    | heavy damage but one bullet per reload.  |
| Choris    | M42 Rifle  | Low    | High   | low damage but high amount of ammo.      |
| OussMac   | 9MM Pistol | Medium | Medium | balanced playstyle, right in the middle. |

# The Game Story:

you play as a character from the previous set, no clipped out of reality, and stuck in\
a computer dimension, between the lines of code and cracks of logic, you fight these bugs.\
in order to win you have to kill all the bugs on the level.\
beware of The Segfault.
## Monsters (The Bugs) :

on these levels of the architecture, these are the entities you will come across, each entity\
upon death has a chance to drop a medkit to replenish health.\
and each deal different damage, the more sever the bug the higher the damage.

![[monsters.png]]

| Bug           | Damage | Health | Chance To Drop Medkit |
| ------------- | ------ | ------ | --------------------- |
| Garbage Value | 15     | 42     | 30%                   |
| Memory Leak   | 20     | 70     | 50%                   |
| Segfault      | 37     | 101    | 69%                   |

# Game Play :


## Controls :

| Control     | Function           |
| ----------- | ------------------ |
| W           | Move Forward       |
| S           | Move Backwards     |
| A           | Strafe Left        |
| D           | Strafe Right       |
| Shift       | Running            |
| Left Arrow  | Rotate Left        |
| Right Arrow | Rotate Right       |
| Mouse       | To Look Around     |
| Left Mouse  | Shoot              |
| Right Mouse | Aim                |
| Esc         | Back or Leave Game |

# How To Install and play :

simply clone this repository and cd to it, and make:

```
git clone https://github.com/Undeved/cube3d && cd cube3d
```

```sh
# make the game executable
make all clean
# usuage ./cub3d <map_path>.cub
./cub3d maps/jesse.cub
```

Note : install glfw if you don't have it.
# Code Documentation

## The Parsing :

This is Where My part begins, (OussMac), first i go about parsing the input file and extracting\
all the information needed for the game.

### Evaluating Input

Here I evaluate the input from the user to validate if it is a valid map `<map>.cub`\
i use a simple logic of reverse string search `ft_strrchr` , on the `.` and simply\
compare this using `ft_strcmp` to have `.cub`.

```c
// this happens in my evaluate_input.c
void	evaluate_input(int argc, char **argv)
{
	if (argc != 2)
		// Must be exactly program name and map, Exit.
	if (ft_strcmp(ft_strrchr(argv[1], '.'), ".cub") != 0)
		// If last '.' isn't exactly .cub, Exit.
}
```

### Reading File :

## Game World Structure:

## UI System :

## Player Movement :

## Weapon Logic :

## Health Logic :

## Shading System :

---

## Raycasting :

## Medkit System :
## Enemy Logic :

