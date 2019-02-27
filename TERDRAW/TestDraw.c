#include "TestDraw.h"

int main (int argc, char * argv [])
{

  TaskTab tasktab = lireData("../TERPLUS/data/in0", 100);
  //printf("\n \n %d \n", tasktab.nbTask);
  
  tasktab = FirstFit(tasktab, 100, 100);
  // afficheTab(tasktab);

  dataInfo* dataI = initDataInfo(100); // la valeur du initDataInfo c'est la periode
  dataI->tasktabp = &tasktab;


  // task t;
  // t = initTask(0,1,2,4);

  // dataInfo* dataI = malloc(sizeof(dataInfo)); 
  // dataI->tasktabp = malloc(sizeof(TaskTab));
  // TaskTab tasktab = lireData("../TERPLUS/data/in1", 10);
  // tasktab = FirstFit(tasktab, 10, 10);
  // dataI->periode = 10;
  // dataI->tasktabp = &tasktab;
  // dataI->scale = 1;
  // dataI->translate_x = 0;
  // dataI->translate_y = 0;



  GtkWidget * win;

  gtk_init (& argc, & argv);
  win= gtk_window_new (GTK_WINDOW_TOPLEVEL);
  gtk_widget_set_size_request (win, 1200, 600);

  GtkWidget *draw = NULL;
  draw = gtk_drawing_area_new();
  gtk_container_add(GTK_CONTAINER(win), draw);
  gtk_widget_add_events(GTK_WIDGET(win), GDK_SCROLL_MASK);
  g_signal_connect (G_OBJECT(draw), "draw", G_CALLBACK (on_draw_event),dataI);
  g_signal_connect(G_OBJECT(win), "scroll-event", G_CALLBACK(scrollScale), dataI);
  g_signal_connect(G_OBJECT(win), "key_press_event", G_CALLBACK(key_press_cb), dataI);

  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  gtk_widget_show_all (win);  
  gtk_main ();
  
  return 0;
}





 dataInfo* initDataInfo (int periode)  {
  dataInfo* d = malloc(sizeof(dataInfo));

  d->scale = 1;
  d->translate_x = 0;
  d->translate_y = 0;

  d->periode = periode;
  d->tasktabp = malloc(sizeof(TaskTab));

  return d;
}

void makeTask(dataInfo* d, int width, int height, cairo_t * cr) {

  //printf("width : %d, height : %d", width, height);  
  char* c=malloc(sizeof(int)*(log(42)+1));
  cairo_scale(cr,d->scale,d->scale);
  cairo_translate(cr, d->translate_x, d->translate_y);
  cairo_set_source_rgb(cr, 0.5, 0, 0);
  cairo_rectangle(cr, 100, 100, 100*(d->tasktabp->nbTask), 80);
  cairo_rectangle(cr, 100, 300, 100*(d->tasktabp->nbTask), 80);
  cairo_stroke_preserve(cr);

  for (int i = 0; i<d->tasktabp->nbTask; i++){
    if (d->tasktabp->tab[i].place != -1) {
      cairo_set_source_rgb(cr, 1, 1, 1);
      cairo_rectangle(cr, 100+100*(d->tasktabp->tab[i].place), 100, 100*(d->tasktabp->tab[i].cycle[0]), 80);
      cairo_rectangle(cr, 100+100*((d->tasktabp->tab[i].place+d->tasktabp->tab[i].delay)%d->periode), 300, 100*(d->tasktabp->tab[i].cycle[1]), 80);

      cairo_set_source_rgb(cr, 0, 0, 0);
      sprintf(c,"%d",d->tasktabp->tab[i].num);
      cairo_move_to(cr, 100+(100*d->tasktabp->tab[i].cycle[0])/2+100*(d->tasktabp->tab[i].place), 140);
      cairo_show_text(cr, c);
      cairo_move_to(cr, 100+(100*d->tasktabp->tab[i].cycle[1])/2+100*((d->tasktabp->tab[i].place+d->tasktabp->tab[i].delay)%d->periode), 340);
      cairo_show_text(cr, c);
      cairo_stroke_preserve(cr);
     
    }
  } cairo_set_fill_rule(cr, CAIRO_FILL_RULE_EVEN_ODD);
  cairo_fill(cr);
  free(c);
}

void makeTask2(dataInfo* d, int width, int height, cairo_t * cr) {

  //printf("width : %d, height : %d", width, height);  
  char* c=malloc(sizeof(int)*(log(42)+1));
  cairo_scale(cr,d->scale,d->scale);
  cairo_translate(cr, d->translate_x, d->translate_y);
  cairo_set_source_rgb(cr, 0.5, 0, 0);

  cairo_rectangle(cr, (-5*(d->tasktabp->nbTask)/10+(width/200.0)/d->scale)*100, (-1.5+(height/200.0)/d->scale)*100, 100*(d->tasktabp->nbTask), 100);
  cairo_rectangle(cr, (-5*(d->tasktabp->nbTask)/10+(width/200.0)/d->scale)*100, (0.5+(height/200.0)/d->scale)*100, 100*(d->tasktabp->nbTask), 100);
  cairo_move_to(cr, (0+(width/200.0)/d->scale)*100-1,(0+(height/200.0)/d->scale)*100-1);
  cairo_show_text(cr, "0");
  // cairo_rectangle(cr, 100, height/4, 100*(d->tasktabp->nbTask), 80);
  // cairo_rectangle(cr, 100, 35*height/60, 100*(d->tasktabp->nbTask), 80);
  cairo_stroke(cr);

  for (int i = 0; i<d->tasktabp->nbTask; i++){
    if (d->tasktabp->tab[i].place != -1) {
      cairo_set_source_rgb(cr, 1, 1, 1);
      cairo_rectangle(cr, (5*(d->tasktabp->tab[i].place)/10+(width/200.0)/d->scale)*100, (-1.5+(height/200.0)/d->scale)*100, 100*(d->tasktabp->tab[i].cycle[0]), 100);
      cairo_rectangle(cr, (5*((d->tasktabp->tab[i].place+d->tasktabp->tab[i].delay)%d->periode)/10+(width/200.0)/d->scale)*100, (0.5+(height/200.0)/d->scale)*100, 100*(d->tasktabp->tab[i].cycle[1]), 100);

      cairo_set_source_rgb(cr, 0, 0, 0);
      sprintf(c,"%d",d->tasktabp->tab[i].num);
      cairo_move_to(cr, 100+(100*d->tasktabp->tab[i].cycle[0])/2+100*(d->tasktabp->tab[i].place), (height/4)+50 );
      cairo_show_text(cr, c);
      cairo_move_to(cr, 100+(100*d->tasktabp->tab[i].cycle[1])/2+100*((d->tasktabp->tab[i].place+d->tasktabp->tab[i].delay)%d->periode), (35*height/60)+50 );
      cairo_show_text(cr, c);
      cairo_stroke_preserve(cr);
     
    }
  }
  
  cairo_set_fill_rule(cr, CAIRO_FILL_RULE_EVEN_ODD);
  cairo_fill(cr);
  free(c);
}

static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer data) {

  int width = gtk_widget_get_allocated_width(widget);
  int height = gtk_widget_get_allocated_height(widget);
  
  makeTask(data, width, height, cr);
  // makeTask2(data, width, height, cr);

  return FALSE;
} 

void dataChangeScale(dataInfo* d, int choice) {
  if (choice == 0) { d->scale = d->scale + 0.01; }
  if (choice == 1 && d->scale > 0.1) { d->scale = d->scale - 0.01; }
}

static gboolean scrollScale(GtkWidget *widget, GdkEventScroll *scroll_event, gpointer data) {
  if (scroll_event->direction == GDK_SCROLL_UP) { dataChangeScale(data, 0); }
  if (scroll_event->direction == GDK_SCROLL_DOWN) { dataChangeScale(data, 1); }
	gtk_widget_queue_draw(widget);
  
  return TRUE;
}

void dataChangeTranslate(dataInfo* d, int choice) {
  if (choice == 0) { d->translate_x = d->translate_x + 10; }
  if (choice == 1) { d->translate_x = d->translate_x - 10; }
  if (choice == 2) { d->translate_y = d->translate_y - 10; }
  if (choice == 3) { d->translate_y = d->translate_y + 10; }
  if (choice == 4) { d->scale =1; d->translate_x = 0; d->translate_y = 0;}
}

gint key_press_cb(GtkWidget *widget, GdkEventKey *kevent, gpointer data)  { 
  if(kevent->keyval == GDK_KEY_q)  { dataChangeTranslate(data, 0); }
  if(kevent->keyval == GDK_KEY_d)  { dataChangeTranslate(data, 1); }
  if(kevent->keyval == GDK_KEY_s)  { dataChangeTranslate(data, 2); }
  if(kevent->keyval == GDK_KEY_z)  { dataChangeTranslate(data, 3); }
	if(kevent->keyval == GDK_KEY_r)  { dataChangeTranslate(data, 4); } 
  
  if (kevent->keyval == GDK_KEY_e) { dataChangeScale(data, 0); }
  if (kevent->keyval == GDK_KEY_a) { dataChangeScale(data, 1); }

	gtk_widget_queue_draw(widget);
  
  return TRUE;
}





