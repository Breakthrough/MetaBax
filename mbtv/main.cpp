 /* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *                                                                           *
 *                       MetaBaxTV  - Main Source File                       *
 *                                                                           *
 * This file contains the main implementation of MetaBaxTV (mbtv).           * 
 *                                                                           *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * Copyright (c) 2013, Brandon "Breakthrough" Castellano.                    *
 *                                                                           *
 * libmetabax is licensed under the BSD 2-Clause License; see the included   *
 * COPYRIGHT file, or visit http://github.com/Breakthrough/MetaBax.          *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */


#include <MetaBax.h>
#include <SDL.h>

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cassert>


int main()
{
    srand(time(0));

    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER);
    
    SDL_Surface *screen = SDL_SetVideoMode(800, 480, 32, SDL_SWSURFACE | SDL_DOUBLEBUF);
    SDL_Surface *tmp    = SDL_LoadBMP("testmario.bmp");
    SDL_Surface *image  = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);

    
    bool mb_run = true;

    SDL_Event e;

    MetaBax mb(360, 240);
    //MetaBax mb(755, 480);
    //MetaBax mb(2880, 480);

    assert(image->format->BytesPerPixel == 4);

    mb.LoadImage(image->w, image->h, (char*)image->pixels,
        image->format->BytesPerPixel, image->pitch, MetaBax::ARGB32_row_to_yiq);

    SDL_FreeSurface(image);
    

    while (mb_run)
    {

        //
        //SDL_LockSurface(screen);
        //
        //mb.avs_row_to_img(...)
        //
        //SDL_UnlockSurface(screen);
        //

        mb.Update();

        SDL_LockSurface(screen);

        mb.GetImage((char*)screen->pixels, screen->w, screen->h,
            screen->format->BytesPerPixel, screen->pitch, MetaBax::FRGB_row_to_ARGB32);

        SDL_UnlockSurface(screen);


        SDL_Flip(screen);
        SDL_Delay(20);

        while ( SDL_PollEvent( &e ) )
        {
            if ( e.type == SDL_QUIT )
            {
                mb_run = false;
            }
        
            if ( e.type == SDL_KEYDOWN )
            {
                if ( e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q )
                    mb_run = false;
            }
        
            if ( e.type == SDL_MOUSEMOTION )
            {
                /*
                int x, y;
                SDL_GetMouseState( &x, &y );
                float mouse_x = x / (float) (screen->w - 1) * 2 - 1;
                float mouse_y = (1 - y / (float) (screen->h - 1)) * 2 - 1;*/
            }
        }
    }

    return 0;
}
