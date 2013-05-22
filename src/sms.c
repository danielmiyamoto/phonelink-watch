//
//  sms.c
//
//
//  Created by Daniel Miyamoto
//
//

#include "pebble_os.h"
#include "pebble_app.h"
#include "pebble_fonts.h"

#include "sms.h"

static Window sms_window;
static ActionBarLayer sms_action_bar_layer;

static HeapBitmap sms_phone;
static HeapBitmap sms_cancel;
static HeapBitmap sms_sms;

static SimpleMenuLayer sms_menu_layer;
static SimpleMenuSection sms_menu_section[1];
static SimpleMenuItem sms_menu_items[5];

void handle_sms_appear(Window *window)
{
}

void sms_select_callback(int index, void *context)
{
  for(int i=0;i<3;i++){
    window_stack_pop(false);
  }
  
  //window_stack_pop_all(false);
}

void handle_sms_unload(Window *window)
{
}

void init_sms_info(){
  sms_menu_items[0] = (SimpleMenuItem) {
      .title = "Mensagem 1",
      .icon = NULL,
      .callback = &sms_select_callback
  };
  
  sms_menu_items[1] = (SimpleMenuItem) {
      .title = "Mensagem 2",
      .icon = NULL,
      .callback = &sms_select_callback
  };
  
  sms_menu_items[2] = (SimpleMenuItem) {
      .title = "Mensagem 3",
      .icon = NULL,
      .callback = &sms_select_callback
  };
  
  sms_menu_items[3] = (SimpleMenuItem) {
      .title = "Mensagem 4",
      .icon = NULL,
      .callback = &sms_select_callback
  };
  
  sms_menu_items[4] = (SimpleMenuItem) {
      .title = "Mensagem 5",
      .icon = NULL,
      .callback = &sms_select_callback
  };
  
  sms_menu_section[0] = (SimpleMenuSection) {
    .items = sms_menu_items,
    .num_items = ARRAY_LENGTH(sms_menu_items)
  };
  
  simple_menu_layer_init(&sms_menu_layer, sms_window.layer.frame, &sms_window, sms_menu_section, ARRAY_LENGTH(sms_menu_section), NULL);
  layer_add_child(&sms_window.layer, &sms_menu_layer.menu.scroll_layer.layer);
}

void init_sms_window()
{
    window_init(&sms_window, "SMS");
    window_set_background_color(&sms_window, GColorWhite);
    window_set_window_handlers(&sms_window, (WindowHandlers) {
        .appear = (WindowHandler)handle_sms_appear,
        .unload = (WindowHandler)handle_sms_unload
    });
	
	init_sms_info();
}

void display_sms()
{   
    init_sms_window();
    
    window_stack_push(&sms_window, true);
}