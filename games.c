#include<ncurses.h>
#include<stdlib.h>
#define SIZE 100

int slab(float ,float ,float ,float ,float ,int);

int top1,speed=8000,h=1,a[SIZE],width=5,inputdisc=1,show=1,speedlevel=5,bgcolor=7,slabcolor=1,countercolor=5;
float gap=1,up;
			
WINDOW *win,*savewin;

struct stack
	{
		int pile[SIZE],top;
	}_tow[4];


int initial(int n)
{
	_tow[3].top=-1;_tow[1].top=-1;_tow[2].top=-1;

	int _i;
	for(_i=0;_i<SIZE;_i++)
	a[_i]=1;
	
	int maxx,maxy;
 	getmaxyx(stdscr,maxy,maxx);
 	
 	while(maxx/6-(inputdisc*width)/2<0)
  		{
  			width--;
  		}
  		
}

int push(struct stack *tower,int n)
{
	tower->top=tower->top+1;
	tower->pile[tower->top]=n;
	return 0;
}
	
int pop(struct stack *tower)
{
	if(tower->top==-1)
	{
		printf("\n\nERROR : STACK EMPTY\n\n");
		return -1;
	} 
	else
	{	
		int temp=tower->pile[tower->top];
		tower->pile[tower->top]=0;
		tower->top--;
		return temp;
	}
}

int top(struct stack *tower)
{
	int ret=tower->pile[tower->top];
	return ret;
}
					


int main()
{
	initscr();
	int n=8,i;
 	system("clear");
 	start_color();
 	init_pair(1,bgcolor,bgcolor);
 	init_pair(2,slabcolor,slabcolor);
	init_pair(9,bgcolor,slabcolor);
	init_pair(21,countercolor,countercolor);
 	
 	highlight();
 	n=inputdisc;
 	
 	for(i=0;i<100;i++)
 	mvchgat(i,0,-1,A_NORMAL,1,NULL);
 	
 	initial(n);
 	
 	for(i=0;i<n;i++)
 	{
 		push(&_tow[1],n-i);
 		slab(0,i,0,i,_tow[1].pile[i]*width,0);
 	}
 	
 	henoy(n,n);
 	getch();
 	main();
 	endwin(); 
}
	

int slab(float tow,float pile,float ntow,float npile,float w,int n)
{
 	float i,maxx,maxy;
  	getmaxyx(stdscr,maxy,maxx);
	noecho();

	init_pair(2,slabcolor,slabcolor);
  
  if(n==0||n==2)
  {	
		if(tow==ntow-1||ntow==tow-1)
		{
			if(npile>=pile)
				up=(maxy-5-2*h)-(npile+1)*(h+gap);
			else 
				up=(maxy-5-2*h)-(pile+1)*(h+gap);
		}
    
		else
		{	
			if(n!=2)
			{
				if(npile>_tow[2].top)
					top1=_tow[(int)ntow+1].top+1;
				else 
					top1=_tow[2].top+1;		
			
				up=(maxy-5-2*h)-(top1+2)*(h+gap);
			}  
		}
		
		tow=maxx*(tow)/3+maxx/6-w/2;
		pile=(maxy-5-2*h)-(pile+1)*(h+gap);
		ntow=maxx*(ntow)/3+maxx/6-w/2;
		npile=(maxy-5-2*h)-(npile+1)*(h+gap);
   }	
   

	  win=newwin(h,w,pile,tow);

		wattron(win,COLOR_PAIR(2));
		  box(win,0,0);
		wattroff(win,COLOR_PAIR(2));
	
		wattron(savewin,COLOR_PAIR(1));
		 box(savewin,0,0);
		wattroff(savewin,COLOR_PAIR(1));
	
		if(n==1)
		{
			wrefresh(savewin);
			refresh();
		}
		
		refresh();
		wrefresh(win);
  		keypad(stdscr,TRUE);
		usleep(speed);
		
		if((pile!=npile&&tow!=ntow)||(pile!=npile&&tow==ntow)||(pile==npile&&tow!=ntow))
  			destroy(win,w);
  	  	
		while(pile>up-2&&tow!=ntow)
		{
		savewin=newwin(h,w,pile,tow);
		pile--;
			if(pile==up-1)
			{
				pile=up;
				break;
			}
				slab(tow,pile,ntow,npile,w,1);
					return 0;
		}
	
   		if(tow>ntow)
	   	{
		  while(tow>ntow)
		  {
			  savewin=newwin(h,w,pile,tow);
		      tow--;
		      if(tow==ntow-1)
			  {
			  	tow=ntow;
			  	break;
			  }
		      slab(tow,pile,ntow,npile,w,1);
		      return 0;
		   }
		}
	
   		else
		{
		  while(tow<ntow)
	      {		
	    	 savewin=newwin(h,w,pile,tow);
		  	 tow++;
	    	 if(tow==ntow+1)
			 {
			 	tow=ntow;
			 	break;
			 }
			 slab(tow,pile,ntow,npile,w,1);
	    	 return 0;
	    	}
	   
		}
			
   		while(pile<=npile)
	   {	
		   	 savewin=newwin(h,w,pile,tow);
	         pile++;
   			if(pile==npile+1)
			 	return 0;
  		
    	slab(tow,pile,ntow,npile,w,1);
			return 0;
		}
}
	
	
int destroy(WINDOW *win,int w)
{
  wborder(win,' ',' ',' ',' ',' ',' ',' ',' ');
  refresh();
  wrefresh(win);
  delwin(win);
}	


int a[SIZE],popnum;

int henoy(int n,int discs)
{
	int i=0,y,x,selected=0,tow,pile,ntow,npile,n_,i_=0,maxx,maxy,hpaint;
	getmaxyx(stdscr,maxy,maxx);
	noecho();
	keypad(stdscr,TRUE);
	//move(maxy-5,maxx/6+(i_*maxx)/3);
	int temp;
	while(1)
	{
		//refresh();
		int ch=getch();
		
		if(ch==KEY_RIGHT)
		{	temp=i_;
			i_++;
			if(i_==3)
			i_=2;
			slab(temp,-1,i_,-1,6,2);
			init_pair(2,slabcolor,slabcolor);
			//move(maxy-5,maxx/6+(i_*maxx)/3);
		//mvprintw(0,0,"_i=%d",i_);
			//refresh();
			
		}
	
		else if(ch==KEY_LEFT)
		{	
			temp=i_;
			i_--;
			if(i_==-1)
			i_=0;
			slab(temp,-1,i_,-1,6,2);
			init_pair(2,slabcolor,slabcolor);
		//	move(maxy-5,maxx/6+(i_*maxx)/3);
			//mvprintw(0,0,"_i=%d",i_);
			//refresh();
		}
		else if(ch=='\n'&&selected==0)
		{//mvprintw(3,0,"I am in selected 0");
			tow=i_;
			selected=1;
			//printw(" _i=%d",i_);
			//refresh();
			pile=_tow[tow+1].top;
			if(pile==-1)
			{
			selected=0;
			continue;
			}
			
			//tower is tow
			//pile is _tow[tow+1].top
			//width is top(&_tow[tow+1])*width
			x=maxx*(tow)/3+maxx/6-(top(&_tow[tow+1])*width)/2;
			y=(maxy-5-2*h)-(_tow[tow+1].top+1)*(h+gap);
			n_=pop(&_tow[tow+1]);
			//for(hpaint==0;hpaint<h;hpaint++)
		//	mvchgat(y+hpaint,x,top(&_tow[tow+1])*width,A_NORMAL,21,NULL);
			//for(hpaint==0;hpaint<h;hpaint++)
		//	mvchgat(0,0,top(&_tow[tow+1])*width,A_NORMAL,21,NULL);
			
			if(n_==-1)
			selected=0;
		}
		else if(ch=='\n'&&selected==1)
		{
			if(n_<=top(&_tow[i_+1])||_tow[i_+1].top==-1)
			{
			//mvprintw(3,0,"I am in selected 1");
			ntow=i_;
			npile=_tow[ntow+1].top+1;
			//mvprintw(5,0,"tow=%d,pile=%d,ntow=%d,npile=%d,num=%d",tow,pile,ntow,npile,n_);
			//getch();
			slab(tow,pile,ntow,npile,n_*width,0);
			selected=0;
			push(&_tow[ntow+1],n_);
			if((_tow[1].top==-1&&_tow[2].top==-1)||(_tow[1].top==-1&&_tow[3].top==-1))
			{
				mvprintw(0,0,"CONGRATS");
				getch();
				endwin();
				main();
			}
			}
			else
			{
			selected=0;
			push(&_tow[tow+1],n_);
			}
		}
		
		if(ch=='r'||ch=='R')
		{
				endwin();
				main();
		}
		
	}
}

int _move(int n,int discs)
{
	int temp,maxx,maxy;
	 getmaxyx(stdscr,maxy,maxx);
					
	if(n%2!=0&&discs%2!=0||n%2==0&&discs%2==0)
	{
		popnum=pop(&_tow[a[n]]);
		 temp=a[n];
								
	if(a[n]-1==0)
		a[n]=4;
										
	  if(show==1)
	  {
  		attron(COLOR_PAIR(9)|A_BOLD|A_UNDERLINE|A_STANDOUT);
		mvprintw(maxy-5,maxx/2-15,"MOVING FROM TOWER %d TO TOWER %d",temp,a[n]-1);
		attroff(COLOR_PAIR(9)|A_BOLD|A_UNDERLINE|A_STANDOUT);
	  }  
	
		slab(temp-1,_tow[temp].top+1,a[n]-2,_tow[a[n]-1].top+1,n*width,0);
		push(&_tow[a[n]-1],popnum);
		a[n]=a[n]-1;
	}
	else
	{
		popnum=pop(&_tow[a[n]]);
		 temp=a[n];
										
		if(a[n]+1==4)
			a[n]=0;
										
	  if(show==1)
	  {
	  	attron(COLOR_PAIR(9)|A_BOLD|A_UNDERLINE|A_STANDOUT);
		mvprintw(maxy-5,maxx/2-15,"MOVING FROM TOWER %d TO TOWER %d",temp,a[n]+1);
		refresh();
		attroff(COLOR_PAIR(9)|A_BOLD|A_UNDERLINE|A_STANDOUT);
	   }

		slab(temp-1,_tow[temp].top+1,a[n],_tow[a[n]+1].top+1,n*width,0);
		push(&_tow[a[n]+1],popnum);
		a[n]=a[n]+1;	
	}
}


int menu(void)
{
	int i,currx,curry;
	
	getyx(stdscr,curry,currx);
	
	start_color();
	
	init_pair(4,COLOR_YELLOW,COLOR_RED);
	init_pair(5,COLOR_MAGENTA,COLOR_CYAN);
	init_pair(8,slabcolor,bgcolor);
	init_pair(7,bgcolor,slabcolor);
	init_pair(20,COLOR_WHITE,COLOR_BLUE);
	
 	for(i=0;i<100;i++)
 	mvchgat(i,0,-1,A_NORMAL,3,NULL);
 	
 	wattron(stdscr,COLOR_PAIR(3)|A_BOLD|A_REVERSE);
	box(stdscr,0,0);
	wattroff(stdscr,COLOR_PAIR(3)|A_BOLD|A_REVERSE);
	
	int y,x;
	
	getmaxyx(stdscr,y,x);
	
	attron(A_REVERSE|COLOR_PAIR(5)|A_BOLD|A_STANDOUT);
	mvprintw(2,x/2-7,"HANOI TOWERS");
	attroff(COLOR_PAIR(5)|A_BOLD|A_REVERSE);

	attron(COLOR_PAIR(20));
	mvprintw(20-8,x/2-15-2,"1.PROGRAMM WILL RUN FOR %d discs  ",inputdisc); 	
	mvprintw(20-8,x/2+15+4,"INC"); 	
	mvprintw(20-8,x/2+15+4+7,"DEC"); 	
	mvprintw(23-8,x/2-15-2,"2.SPEED LEVEL = %d ",speedlevel); 	
	mvprintw(23-8,x/2+15+4,"INC"); 	
	mvprintw(23-8,x/2+15+4+7,"DEC"); 	
	mvprintw(26-8,x/2-15-2,"3.CHANGE COLOR");
	attroff(COLOR_PAIR(20));
	attron(COLOR_PAIR(7));
	mvprintw(26-8,x/2+15+4,"BG"); 	
	attroff(COLOR_PAIR(7));
	attron(COLOR_PAIR(8));
	mvprintw(26-8,x/2+15+4+7,"SLAB"); 	
	attroff(COLOR_PAIR(8));
	attron(COLOR_PAIR(20));
	mvprintw(29-8,x/2-15-2,"4.MOVE DETAILS"); 
	if(show==1)
	mvprintw(29-8,x/2-15-2+14+2,"ON "); 
	else	
	mvprintw(29-8,x/2-15-2+14+2,"OFF"); 
	
	mvprintw(29-8,x/2+15+4,"ON"); 	
	mvprintw(29-8,x/2+15+4+7,"OFF");
	mvprintw(32-8,x/2-15-2,"5.DONE");
	mvprintw(32-8,x/2+15+4,"YES"); 	
	mvprintw(32-8,x/2+15+4+7,"NO"); 	
	mvprintw(35-8,x/2-15-2,"6.EXIT");
	mvprintw(35-8,x/2+15+4,"YES"); 	
	mvprintw(35-8,x/2+15+4+7,"NO"); 	
	attroff(COLOR_PAIR(20));
	refresh();
	move(curry,currx);
}

int length[6][3]={
					31,3,3,
					13,3,3,
					14,2,4,
					14,2,3,
					6,3,2,	
				 	6,3,2
				 };

	
int highlight(void)
{	
	int y,x,maxx,maxy;
	int i=0,j=0,inc=0,dec=0;	
	getmaxyx(stdscr,maxy,maxx);
	y=20-8;
	x=maxx/2-15-2;
	init_pair(3,COLOR_BLUE,COLOR_WHITE);
	noecho();
	raw();
	keypad(stdscr,TRUE);
	mvprintw(maxy-5,maxx/2-15,"                                ");
	menu();
	move(y,x);
	reverse(length[i][j]);
		
	while(1)
	{	
		reverse(length[i][j]);
		int ch=getch();
		menu();
		if(ch==KEY_UP)
		{	i--;
			if(i>5||i<0)
			{i++;continue;}
			y=y-3;
			move(y,x);
			reverse(length[i][j]);
			
		}
		else if(ch==KEY_DOWN)
		{	i++;
			if(i<0||i>5)
			{i--;continue;}
			y=y+3;
			move(y,x);
			reverse(length[i][j]);
		}
		else if(ch==KEY_RIGHT)
		{	if(j==0)
				inc=36;
			if(j==1)
				inc=7;
			j++;
				if(j>2||j<0)
				{j--;continue;}
			x=x+inc;
			move(y,x);
			reverse(length[i][j]);
		}
		else if(ch==KEY_LEFT)
		{	if(j==1)
			dec=36;
			if(j==2)
			dec=7;
			j--;
				if(j>2||j<0)
				{j++;continue;}
			x=x-dec;
			move(y,x);
			reverse(length[i][j]);
			}
			
		else if(ch=='\n')
		{
			if(i==0&&j==1)
			{
				inputdisc++;
				menu();
			}
			
			if(i==0&&j==2&&inputdisc>1)
			{
				inputdisc--;
				menu();
			}
			
			if(i==1&&j==1)
			{
				if(speed>=1600&&speedlevel<10)
				{	
					speed=speed-1600;	
					speedlevel++;	
					menu();
					init_pair(1,COLOR_WHITE,COLOR_WHITE);
					slab(0,13,2,13,5,0);
					init_pair(1,bgcolor,bgcolor);
					menu();
				}	
			}
			
			if(i==1&&j==2&&speedlevel>1)
			{
					speed=speed+1600;
					speedlevel--;
					menu();
					init_pair(1,COLOR_WHITE,COLOR_WHITE);
					slab(0,13,2,13,5,0);
					init_pair(1,bgcolor,bgcolor);
					menu();
			}
	
					
			if(i==3&&j==1)
			{
				show=1;
				menu();
			}
			
			if(i==3&&j==2)
			{
				show=0;
				menu();
			}
			
			if(i==2&&j==1)
			{
				colorhighlight(1);
				return 0;
				continue;
			}
			
			if(i==2&&j==2)
			{
				colorhighlight(2);
				return 0;
				continue;
			}
			
			
			if(i==4&&j==1&&inputdisc>0)
			{
				return 0;
			}
			
			if(i==4&&j==1)
			{
				continue;
			}
			if(i==5&&j==1)
			{
				endwin();
				system("clear");
				exit(1);
			}
		}			
	}
}								

reverse(int l)
{
	int x,y;
	char ch;
	getyx(stdscr,y,x);
	int remy=y,remx=x;
	
	chgat(l,A_REVERSE,3,NULL);
		refresh();
		move(remy,remx);
}

int changecolor(void)
{
	int i,y,x,j=0,colh=4;
	getmaxyx(stdscr,y,x);
	
	for(i=0;i<8;i++)
	{	
		init_pair(10+i,COLOR_BLACK,i);
 		mvchgat((y-28)/2+4*i,5+j,5,A_NORMAL,10+i,NULL);
	}
}

int colorhighlight(int c)
{ 
	int y,x,maxx,maxy;
	getmaxyx(stdscr,maxy,maxx);
	int i=0;	
	y=(maxy-28)/2;
	x=4;
	noecho();
	raw();
	changecolor();
	move(y,x);
	keypad(stdscr,TRUE);
		
	while(1)
	{	
		int ch=getch();
		changecolor();
				
		if(ch==KEY_UP)
		{	i--;
			if(i>7||i<0)
			{i++;continue;}
			y=y-4;
			move(y,x);
		}
		else if(ch==KEY_DOWN)
		{	i++;
			if(i<0||i>7)
			{i--;continue;}
			y=y+4;
			move(y,x);
		}
		else if(ch=='\n')
		{
			if(c==1)
			bgcolor=i;
			else
			slabcolor=i;
			init_pair(9,bgcolor,slabcolor);
			init_pair(c,i,i);
			highlight();
			return 0;
		}
	}
}

