
/**
 * @file main
 *
 */

/*********************
 *      INCLUDES
 *********************/
#define _DEFAULT_SOURCE /* needed for usleep() */
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include "lvgl/lvgl.h"
#include "lvgl/examples/lv_examples.h"
#include "lvgl/demos/lv_demos.h"
//#include "glob.h" libreria escluida para windows use poxi

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static lv_display_t * hal_init(int32_t w, int32_t h);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

extern void freertos_main(void);

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *      VARIABLES
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/
#ifdef _WIN32
#include <windows.h> // Para usar ShowWindow y GetConsoleWindow
#else
#include <unistd.h> // Para usleep
#endif

//evento boton1 lanza demo musical
static void btn_event_handler(lv_event_t * e)
{
  lv_obj_t * btn = lv_event_get_target(e);
  LV_UNUSED(btn); // Evita el warning de variable no usada

  //Lanza la demo musical
  lv_demo_music();
}

//evento boton2 lanza demo de benchmark
static void btn_event_handler2(lv_event_t * e)
{
  lv_obj_t * btn = lv_event_get_target(e);
  LV_UNUSED(btn); // Evita el warning de variable no usada

  //Lanza la demo de benchmark
  lv_demo_benchmark();
}

//evento boton3 lanza demo de widgets
static void btn_event_handler3(lv_event_t * e)
{
  lv_obj_t * btn = lv_event_get_target(e);
  LV_UNUSED(btn); // Evita el warning de variable no usada

  //Lanza la demo de widgets
  lv_demo_widgets();
}

int main(int argc, char **argv)
{
  (void)argc; /*Unused*/
  (void)argv; /*Unused*/

  //evita que la terminal se muestre en la pantalla en windows
  #ifdef _WIN32
  HWND hWnd = GetConsoleWindow();
  if (hWnd != NULL) {
    ShowWindow(hWnd, SW_HIDE); // Oculta la ventana de la consola

  }
  #endif

  /*Initialize LVGL*/
  lv_init();

  /*Initialize the HAL (display, input devices, tick) for LVGL*/
  hal_init(320, 480);

  #if LV_USE_OS == LV_OS_NONE



  //crea una lista de botones
  lv_obj_t * btns = lv_obj_create(lv_screen_active());
  lv_obj_set_size(btns, 320, 480);
  lv_obj_set_style_bg_color(btns, lv_color_black(), 0);
  lv_obj_set_style_border_width(btns, 0, 0);



  //agrega title a la pantalla
  lv_obj_t * title = lv_label_create(btns);
  lv_label_set_text(title, "LVGL JeanCode");
  lv_obj_set_style_text_color(title, lv_color_white(), 0);
  lv_obj_set_style_text_font(title, &lv_font_montserrat_20, 0);
  lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 10);
  lv_obj_set_style_bg_color(title, lv_color_black(), 0);

  //crea los botones
  lv_obj_t * btn1 = lv_btn_create(btns);
  //aling center
  lv_obj_align(btn1, LV_ALIGN_CENTER, 0, -50);
  lv_obj_add_event_cb(btn1, btn_event_handler, LV_EVENT_CLICKED, NULL);
  //agrega un label al boton
  lv_obj_t * label1 = lv_label_create(btn1);
  lv_label_set_text(label1, "Demos");

  //crea boton 2
  lv_obj_t * btn2 = lv_btn_create(btns);
  //aling center
  lv_obj_align(btn2, LV_ALIGN_CENTER, 0, 0);
  lv_obj_add_event_cb(btn2, btn_event_handler2, LV_EVENT_CLICKED, NULL);
  //agrega un label al boton
  lv_obj_t * label2 = lv_label_create(btn2);
  lv_label_set_text(label2, "Demo 2");


  //crea boton 3
  lv_obj_t * btn3 = lv_btn_create(btns);
  //aling center
  lv_obj_align(btn3, LV_ALIGN_CENTER, 0, 50);
  lv_obj_add_event_cb(btn3, btn_event_handler3, LV_EVENT_CLICKED, NULL);
  //agrega un label al boton
  lv_obj_t * label3 = lv_label_create(btn3);
  lv_label_set_text(label3, "Demo 3");

  //agrega la version de LVGL
  lv_obj_t * version_label = lv_label_create(btns);
  lv_label_set_text_fmt(version_label, "LVGL Version: %s", lv_version_info());
  lv_obj_set_style_text_color(version_label, lv_color_white(), 0);
  lv_obj_set_style_text_font(version_label, &lv_font_montserrat_12, 0);
  lv_obj_align(version_label, LV_ALIGN_CENTER, 0,150);

  while(1) {
    /* Periodically call the lv_task handler.
     * It could be done in a timer interrupt or an OS task too.*/
    lv_timer_handler();
    usleep(800);
  }

  #elif LV_USE_OS == LV_OS_FREERTOS

  /* Run FreeRTOS and create lvgl task */
  freertos_main();

  #endif

  return 0;
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/**
 * Initialize the Hardware Abstraction Layer (HAL) for the LVGL graphics
 * library
 */
static lv_display_t * hal_init(int32_t w, int32_t h)
{

  lv_group_set_default(lv_group_create());

  lv_display_t * disp = lv_sdl_window_create(w, h);

  lv_indev_t * mouse = lv_sdl_mouse_create();
  lv_indev_set_group(mouse, lv_group_get_default());
  lv_indev_set_display(mouse, disp);
  lv_display_set_default(disp);

  LV_IMAGE_DECLARE(mouse_cursor_icon); /*Declare the image file.*/
  lv_obj_t * cursor_obj;
  cursor_obj = lv_image_create(lv_screen_active()); /*Create an image object for the cursor */
  lv_image_set_src(cursor_obj, &mouse_cursor_icon);           /*Set the image source*/
  lv_indev_set_cursor(mouse, cursor_obj);             /*Connect the image  object to the driver*/

  lv_indev_t * mousewheel = lv_sdl_mousewheel_create();
  lv_indev_set_display(mousewheel, disp);
  lv_indev_set_group(mousewheel, lv_group_get_default());

  lv_indev_t * kb = lv_sdl_keyboard_create();
  lv_indev_set_display(kb, disp);
  lv_indev_set_group(kb, lv_group_get_default());

  return disp;
}
