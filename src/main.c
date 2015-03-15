#include <pebble.h>
#include "calculator.h"

static Window *window;
static TextLayer *DigitLayer;
static TextLayer *QueryLayer;
static TextLayer *OperatorLayer;

static CircularBuffer s_digitList;
static CircularBuffer s_operatorList;

static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(DigitLayer, "Select");
  text_layer_set_text(QueryLayer, "Select");
  text_layer_set_text(OperatorLayer, "Select");
}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(DigitLayer, "Up");
  text_layer_set_text(QueryLayer, "Up");
  text_layer_set_text(OperatorLayer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(DigitLayer, "Down");
  text_layer_set_text(QueryLayer, "Down");
  text_layer_set_text(OperatorLayer, "Down");
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
  GRect bounds = layer_get_bounds(window_layer);

  DigitLayer = text_layer_create((GRect) { .origin = { 0, 0 }, .size = { bounds.size.w, 50 } });
  QueryLayer = text_layer_create((GRect) { .origin = { 0, 50 }, .size = { bounds.size.w, 68 } });
  OperatorLayer = text_layer_create((GRect) { .origin = { 0, 118 }, .size = { bounds.size.w, 50 } });

  text_layer_set_text(DigitLayer, "Press a button");
  text_layer_set_text_alignment(DigitLayer, GTextAlignmentLeft);
  
  text_layer_set_text(QueryLayer, "Press a button");
  text_layer_set_text_alignment(QueryLayer, GTextAlignmentLeft);
  
  text_layer_set_text(OperatorLayer, "Press a button");
  text_layer_set_text_alignment(OperatorLayer, GTextAlignmentLeft);

  layer_add_child(window_layer, text_layer_get_layer(DigitLayer));
  layer_add_child(window_layer, text_layer_get_layer(QueryLayer));
  layer_add_child(window_layer, text_layer_get_layer(OperatorLayer));
}

static void window_unload(Window *window) {
  text_layer_destroy(DigitLayer);
  text_layer_destroy(OperatorLayer);
  text_layer_destroy(QueryLayer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Pushed window: %p", window);
  
  PopulateDigitList(&s_digitList);
  PopulateOperatorList(&s_operatorList);
  APP_LOG(APP_LOG_LEVEL_DEBUG, "Populated circular buffers");
}

static void deinit(void) {
  window_destroy(window);
  DeleteCircularBuffer(&s_digitList);
  DeleteCircularBuffer(&s_operatorList);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing");

  app_event_loop();
  deinit();
}
