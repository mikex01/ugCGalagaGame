//Standar library includes
#include <stdio.h>
#include <stdlib.h>
//Allegro framework includes
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/keyboard.h>
//Own includes
#include "enemies.h"
#include "player.h"
#include "background.h"
#include "menu.h"
#define FPS 60.0
#define SCREEN_W 1000
#define SCREEN_H 600
//prototipado de funciones
int init_framework_components();
int clean();
//creacion de variables
ALLEGRO_DISPLAY *display = NULL;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_TIMER *timer = NULL;
enum KEYS{UP, DOWN, LEFT, RIGHT };
int teclas[4] = {0, 0, 0, 0};

void update_screen();

int main(int argc, char **argv){
  menu();

 
  init_framework_components();
  //Configuraciones miscelaneas
  al_inhibit_screensaver(1);//evitar suspencion de pc
  al_set_window_title(display, "Space"); //titulo de la ventana
  //Registramos las fuentes de eventos
  al_register_event_source(event_queue, al_get_keyboard_event_source());
  al_register_event_source(event_queue, al_get_timer_event_source(timer));
  //Inicializamos al jugador principal
  fondo = init_background();
  player = init_player();
  if(!player->nave) clean();
  if(!fondo->bg_image) clean();
  al_flip_display(); /*damos vida al display! :D*/
  srand(time(NULL));
  al_start_timer(timer);//comenzamos el timer
  int terminar = 0; //teclado para salir
  ALLEGRO_EVENT ev;//variable que recive evento
 // level_generator(enemies_r);
  while(!terminar) {//cuerpo del juego
    al_wait_for_event(event_queue, &ev);
    if(ev.type == ALLEGRO_EVENT_KEY_UP) {
      switch(ev.keyboard.keycode) {
        case ALLEGRO_KEY_ESCAPE:	terminar = 1; break;
        case ALLEGRO_KEY_UP:      teclas[UP]=0;	break;
        case ALLEGRO_KEY_DOWN:	teclas[DOWN]=0;	break;
        case ALLEGRO_KEY_LEFT:	teclas[LEFT]=0;	break;
        case ALLEGRO_KEY_RIGHT:	teclas[RIGHT]=0;break;
      }
    } else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
      switch(ev.keyboard.keycode){
        case ALLEGRO_KEY_UP:	teclas[UP]=1;	break;
        case ALLEGRO_KEY_DOWN:	teclas[DOWN]=1;	break;
        case ALLEGRO_KEY_LEFT:	teclas[LEFT]=1;	break;
        case ALLEGRO_KEY_RIGHT:	teclas[RIGHT]=1;break;
      }
    } else if(ev.type == ALLEGRO_EVENT_TIMER) {
      if(teclas[UP]){
        dibujarFondo();
       	moverArriba(player);
      }else if(teclas[DOWN]){
        dibujarFondo();
      	moverAbajo(player);
      }else if(teclas[LEFT]){	
        dibujarFondo();
        moverIzquierda(player);
      }else if(teclas[RIGHT]){
        dibujarFondo();
        moverDerecha(player);
      }
    } 
    // dibujamos al jugador
  }
  // siempre hay que limpiar memoria
  clean();
  return 0;
}

int clean(){
  al_destroy_display(display);
  al_destroy_event_queue(event_queue);
  al_destroy_bitmap(fondo->bg_image);
  al_destroy_bitmap(player->nave);
  al_destroy_timer(timer);
  free(player);
  return 0;
}
int init_framework_components(){
  //inicializacion del librerias
  if(!al_init()) { 
    fprintf(stderr, "%s\n", "No se pudo inicializar allegro 5"); 
    return -1; 
  }
  if(!al_init_image_addon()){ 
    fprintf(stderr,"%s\n", "No se pudo inicializar el addon");
    al_destroy_display(display);
    return -1; 
  }
  display = al_create_display(SCREEN_W, SCREEN_H);
  if(!display){ 
    fprintf(stderr, "%s\n", "No se pudo crear un display"); 
    al_destroy_display(display);  
    return -1;
  } 
  if(!al_install_keyboard()){
    fprintf(stderr, "%s\n", "No se pudo instalar el teclado");
    al_destroy_display(display);
    return -1; 
  }
  timer = al_create_timer(1.0 / FPS); //Inicializo imer del juego
  event_queue = al_create_event_queue(); //Cola global para eventos
  return 0;
}
