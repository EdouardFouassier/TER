#ifndef TESTDRAW
#define TESTDRAW

#include <gtk/gtk.h>
#include <cairo.h>
#include <math.h>

#include "../TERPLUS/FirstFit.h"

typedef struct dataInfo {
  double scale;
  int translate_x;
  int translate_y;

  int periode;
  TaskTab* tasktabp;
} dataInfo;

dataInfo* initDataInfo(int periode);

void makeTask(dataInfo* d, int width, int height, cairo_t * cr);
void makeTask2(dataInfo* d, int width, int height, cairo_t * cr);
static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data);

void dataChangeScale(dataInfo* d, int choice);
static gboolean scrollScale(GtkWidget *widget, GdkEventScroll *scroll_event, gpointer data);

void dataChangeTranslate(dataInfo* d, int choice);
gint key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data);


#endif