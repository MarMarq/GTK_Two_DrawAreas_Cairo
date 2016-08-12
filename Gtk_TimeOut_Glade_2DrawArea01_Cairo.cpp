	#include <stdlib.h>
	#include <gtk/gtk.h>
	#include <glib.h>
	#include <cairo.h>
	#include <math.h>
	#include <unistd.h>
	#include <stdlib.h>

		GtkWidget       *window;
		GtkWidget       *darea1;
		GtkWidget       *darea2;

		bool toggle_stat1 = false;
		bool toggle_stat2 = false;

		double fase1 = 2;
		double amp1  = 1.25;
		double fase2 = 4;
		double amp2  = 1.25;

		gboolean flag_amp1 = TRUE;
		gboolean flag_amp2 = TRUE;

	//*******************************************************************************
	static gboolean  on_toggled1(GtkWidget *widget, gpointer data)
	 {
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
			{toggle_stat1 = true;
			printf("ToggleButton01 --> Acionado / toggle_stat1 = %d\n",toggle_stat1);
			}
		else
			{toggle_stat1 = false;
			printf("ToggleButton01 --> Liberado / toggle_stat1 = %d\n",toggle_stat1);
			}
	return FALSE;
	 }
	//*******************************************************************************
	static gboolean  on_toggled2(GtkWidget *widget, gpointer data)
	 {
		if(gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(widget)))
			{toggle_stat2 = true;
			printf("ToggleButton02 --> Acionado / toggle_stat2 = %d\n",toggle_stat2);
			}
		else
			{toggle_stat2 = false;
			printf("ToggleButton02 --> Liberado / toggle_stat2 = %d\n",toggle_stat2);
			}
	return FALSE;
	 }
	//*******************************************************************************
	//*******************************************************************************
	static gboolean draw_darea1(GtkWidget *widget, cairo_t *cr, gpointer data)
	{
	  static const double dashed1[] = {4.0, 21.0, 2.0};

		cr = gdk_cairo_create(gtk_widget_get_window(widget));
		cairo_set_source_rgba(cr, 0.45, 0.45, 0.45, 1);
		cairo_rectangle(cr,0 , 0, widget->allocation.width, widget->allocation.height);
		cairo_fill(cr);

	double i = widget->allocation.width;
	double j = widget->allocation.height;
	double sc = fase1*M_PI/i;
	double y;
	double h = 0;
	if (amp1 != 0) h = h + j/amp1;
	//---------------------------------------------------------------------------
	cairo_set_source_rgba(cr, 1, 1, 0, 1);
	cairo_set_dash(cr,dashed1, 1, 0 );
	cairo_set_line_width(cr, 1.5);

	cairo_move_to(cr, 0, (j/2)+(sin( (-i/2)*sc   )*(h/2))  );
	for(double x=(-i/2);x<=(i/2);x=x+10)
	{
	y=x*sc;
	cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2))  		);
	}
	cairo_stroke(cr);
		 return TRUE;
	 }
	//*******************************************************************************
	//*******************************************************************************
	static gboolean draw_darea2(GtkWidget *widget, cairo_t *cr, gpointer data)
	{
	  static const double dashed1[] = {4.0, 21.0, 2.0};

		cr = gdk_cairo_create(gtk_widget_get_window(widget));
		cairo_set_source_rgba(cr, 0.45, 0.45, 0.45, 1);
		cairo_rectangle(cr,0 , 0, widget->allocation.width, widget->allocation.height);
		cairo_fill(cr);

	double i = widget->allocation.width;
	double j = widget->allocation.height;
	double sc = fase2*M_PI/i;
	double sc2 = fase2*M_PI/i;
	double y;
	double h = 0;
	if (amp2 != 0) h = h + j/amp2;
	//---------------------
	cairo_set_source_rgba(cr, 0, 1, 0, 1);
	cairo_set_dash(cr,dashed1, 1, 0 );
	cairo_set_line_width(cr, 1.5);

	cairo_move_to(cr, 0, (j/2)+(sin( (-i/2)*sc   )*(h/2))  );
	for(double x=(-i/2);x<=(i/2);x=x+10)
	{
	y=x*sc;
	cairo_line_to(cr,x+(i/2),(j/2)+(sin(y)*(h/2) + x*sc2 )  		);
	}
	cairo_stroke(cr);
		 return TRUE;
	 }
	//*******************************************************************************
	//*******************************************************************************
	static gboolean invalidate_drawing1(GtkWidget *widget)
	  {
			g_print("T_Signal-1 | amp1 = %2.3f   |   ",amp1);
		if (toggle_stat1==true)
			{
				if ((flag_amp1==TRUE)&&(amp1 <= 6))
					amp1=amp1+0.25;
				else
					flag_amp1=FALSE;
				if ((flag_amp1==FALSE)&&(amp1 >= 1.25))
					amp1=amp1-0.25;
				else
					flag_amp1=TRUE;
			}
			//---------------------
			gtk_widget_queue_draw(widget);

			return TRUE;
	  }
	//**********************
	//**********************
	static gboolean invalidate_drawing2(GtkWidget *widget)
	  {
				g_print("T_Signal-2 | amp2 = %2.3f\n",amp2);
			if (toggle_stat2==true)
			{
					if ((flag_amp2==TRUE)&&(amp2 <= 6))
						amp2=amp2+0.25;
					else
						flag_amp2=FALSE;
					if ((flag_amp2==FALSE)&&(amp2 >= 1.25))
						amp2=amp2-0.25;
					else
						flag_amp2=TRUE;
			}
			//---------------------
			gtk_widget_queue_draw(widget);
			return TRUE;
	  }
	//**********************
	int main (int argc, char *argv[])
	{
		GtkBuilder      *builder;
		GtkWidget       *togglebutton1;
		GtkWidget       *togglebutton2;

		gtk_init (&argc, &argv);

		builder = gtk_builder_new ();
		gtk_builder_add_from_file (builder, "GTK_Glade_2DrawArea01-R00.glade", NULL);                        //Carrega as informações do projeto glade para o GtkBuilder
		window          = GTK_WIDGET(gtk_builder_get_object (builder, "window1"));          //Retorna o objeto Window, para mostrá-lo mais tarde
		darea1			= GTK_WIDGET(gtk_builder_get_object (builder, "drawingarea1"));      //Retorna o objeto DrawingArea, para mostrá-lo mais tarde
		darea2			= GTK_WIDGET(gtk_builder_get_object (builder, "drawingarea2"));      //Retorna o objeto DrawingArea, para mostrá-lo mais tarde
		togglebutton1   = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton1"));    //Retorna o objeto togglebutton1, para mostrá-lo mais tarde
		togglebutton2   = GTK_WIDGET(gtk_builder_get_object (builder, "togglebutton2"));    //Retorna o objeto togglebutton1, para mostrá-lo mais tarde

		gtk_window_set_title(GTK_WINDOW(window), "GTK 2 Viewports DrawArea 01");

		gtk_builder_connect_signals (builder, NULL); 	//Conecta todos os eventos dentro do projeto do glade.
		g_object_unref (G_OBJECT (builder)); 			//Exclui o GtkBuilder, pois não iremos mais usá-lo nesse exemplo.

		g_signal_connect(G_OBJECT(togglebutton1)  , "toggled"        , G_CALLBACK(on_toggled1)     ,   NULL);
		g_signal_connect(G_OBJECT(togglebutton2)  , "toggled"        , G_CALLBACK(on_toggled2)     ,   NULL);
		g_signal_connect(G_OBJECT(darea1), "expose-event", G_CALLBACK(draw_darea1), NULL);
		g_signal_connect(G_OBJECT(darea2), "expose-event", G_CALLBACK(draw_darea2), NULL);
		g_signal_connect_swapped(G_OBJECT(window) , "destroy", G_CALLBACK(gtk_main_quit)  , G_OBJECT(window));

			g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE,25,(GSourceFunc)invalidate_drawing1,(gpointer)darea1,NULL);  // Variação atualizada da linha acima :-)
			g_timeout_add_full(G_PRIORITY_DEFAULT_IDLE,25,(GSourceFunc)invalidate_drawing2,(gpointer)darea2,NULL);  // Variação atualizada da linha acima :-)

		gtk_widget_show_all(window);   //Mostra a janela com seus objetos
		gtk_main ();

		return 0;
	}

