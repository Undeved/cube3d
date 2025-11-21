#define MINIAUDIO_IMPLEMENTATION
#include "miniaudio.h"
#include "cube.h"

// sound system added after push
void    audio_init(t_parsed_data *pd)
{
    if (ma_engine_init(NULL, &pd->audio.engine) != MA_SUCCESS)
    {
        fprintf(stderr, "Audio: failed to init engine.\n");
        mind_free_all(EXIT_FAILURE); // exits game and cleans up
    }
    pd->audio.bg_music_playing = false;
}

void    audio_cleanup(t_parsed_data *pd)
{
    if (pd->audio.bg_music_playing)
        ma_sound_uninit(&pd->audio.bg_music);

    ma_engine_uninit(&pd->audio.engine);
}

void    play_bg_music(t_parsed_data *pd, const char *path)
{
    if (pd->audio.bg_music_playing)
        ma_sound_uninit(&pd->audio.bg_music);

    if (ma_sound_init_from_file(&pd->audio.engine, path,
            MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL,
            NULL, &pd->audio.bg_music) != MA_SUCCESS)
    {
        fprintf(stderr, "Audio: failed to load background music.\n");
        mind_free_all(EXIT_FAILURE);
    }
    ma_sound_set_looping(&pd->audio.bg_music, MA_TRUE);
    ma_sound_start(&pd->audio.bg_music);
    pd->audio.bg_music_playing = true;
}

void    stop_bg_music(t_parsed_data *pd)
{
    if (!pd->audio.bg_music_playing)
        mind_free_all(EXIT_FAILURE);

    ma_sound_stop(&pd->audio.bg_music);
    ma_sound_uninit(&pd->audio.bg_music);
    pd->audio.bg_music_playing = false;
}

void    play_sound_once(t_parsed_data *pd, const char *path)
{
    ma_engine_play_sound(&pd->audio.engine, path, NULL);
}

void    start_loop_sound(t_parsed_data *pd, ma_sound *snd, const char *path)
{
    if (ma_sound_init_from_file(&pd->audio.engine, path,
        MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC, NULL, NULL, snd) != MA_SUCCESS)
    {
        fprintf(stderr, "Audio: couldn't load loop sound.\n");
        mind_free_all(EXIT_FAILURE);
    }
    ma_sound_set_looping(snd, MA_TRUE);
    ma_sound_start(snd);
}

void    stop_loop_sound(ma_sound *snd)
{
    ma_sound_stop(snd);
    ma_sound_uninit(snd);
}

static void auto_free_sound_callback(void *pUserData, ma_sound *pSound)
{
    (void)pUserData;
    ma_sound_uninit(pSound);
    free(pSound);
}


void play_enemy_sound_3d(t_parsed_data *pd, t_enemy *e, const char *path)
{
    ma_sound* snd = malloc(sizeof(ma_sound));
    if (!snd)
        return;

    if (ma_sound_init_from_file(&pd->audio.engine,
                                path,
                                MA_SOUND_FLAG_DECODE | MA_SOUND_FLAG_ASYNC,
                                NULL, NULL, snd) != MA_SUCCESS)
    {
        free(snd);
        return;
    }

    // distance-based volume
    double dx = e->pos.x - pd->player.pos.x;
    double dy = e->pos.y - pd->player.pos.y;
    double dist = sqrt(dx * dx + dy * dy);

    float vol = 1.0f / (1.0f + (float)dist * 0.3f);
    if (vol < 0.05f)
        vol = 0.05f;

    ma_sound_set_volume(snd, vol);
    ma_sound_start(snd);

    // free sound when done playing
    ma_sound_set_end_callback(snd, auto_free_sound_callback, NULL);
}

