#include<signal.h>
#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/time.h>
#include<gtk/gtk.h>
// 这是每个gtk+2.0 程序都要包含的头文件。

// 声明回调函数on_delete_event
void on_delete_event(GtkWidget *widget,GdkEvent *event,gpointer data)
{
  gtk_main_quit();// 还是需要调用系统的。
}


GtkWidget* g_label;

static void
elsfTimer(int signo)
{
 	char buf[20] = "";

	struct timeval tp;
	struct tm* tm;
	gettimeofday(&tp,NULL); //gettimeofday函数获得系统当前时间(s & us)
	tm = localtime(&tp.tv_sec);// localtime取得当地目前时间和日期
	
	sprintf(buf,"%d-%d-%d %d:%d:%d\n",
	tm->tm_year+1900,tm->tm_mon+1,tm->tm_mday,
	tm->tm_hour,tm->tm_min,tm->tm_sec); //打印当地目前时间和日期

	gtk_label_set_text(GTK_LABEL(g_label),buf);//update 
}

static void
initTime(int tv_sec,int tv_usec)
{
	struct itimerval value;

	signal(SIGALRM,elsfTimer);
	value.it_value.tv_sec = tv_sec;// 首次启动的时间
	value.it_value.tv_usec = tv_usec;
	
	value.it_interval.tv_sec = tv_sec;//间隔时间
	value.it_interval.tv_usec = tv_usec;

	setitimer(ITIMER_REAL,&value,NULL);// setitimer发送信号.定时器类型为ITIMER_REAL
}

void
set_widget_font_size(GtkWidget *widget,int size,int is_button)
{
   GtkWidget *labelChild;
   PangoFontDescription *font;
   gint fontSize = size;

   font = pango_font_description_from_string("Sans");//字体名
   pango_font_description_set_size(font,fontSize*PANGO_SCALE);// 设置字体大小

   if(is_button){
        labelChild = gtk_bin_get_child(GTK_BIN(widget));
   }else{
       labelChild = widget;
   }
   // 设置label字体
   gtk_widget_modify_font(GTK_WIDGET(labelChild),font);
   pango_font_description_free(font);
}



int
main(int argc,char *argv[])
{
    GtkWidget *window;
    gtk_init(&argc,&argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

	// 信号回调函数
    g_signal_connect(G_OBJECT(window),"delete_event"
           ,G_CALLBACK(on_delete_event),NULL);

    gtk_window_set_title(GTK_WINDOW(window),"当前时间");

    gtk_window_set_default_size(GTK_WINDOW(window),500,100);

    gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);

    gtk_container_set_border_width(GTK_CONTAINER(window),0);

    g_label = gtk_label_new("");// 显示空字符

  	elsfTimer(1); //随便传一个数字.默认起来,显示当前时间

    set_widget_font_size(g_label,23,FALSE);

    gtk_container_add(GTK_CONTAINER(window),g_label);

    gtk_widget_show(g_label);
    gtk_widget_show(window);// 显示控件。参数是要显示的控件的指针。

	initTime(1,0); //每隔1s刷新时间
	// 事件循环。
    gtk_main();
	return 0;
}



