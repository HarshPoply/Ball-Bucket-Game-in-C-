#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<graphics.h>
union REGS in,out; 		//in dos.h header file
void pos(int *x,int *y)
{
	//Get mouse position coordinates
	in.x.ax=3;
	int86(0x33,&in,&out);
	*x = out.x.cx;		//Position x coordinate of mouse
	*y = out.x.dx;		//Position y coordinate of mouse
}

//To bound the position of mouse
void bound(int x1,int y1,int x2,int y2)
{
	//set horizontal limit of mouse
	in.x.ax = 7;
	in.x.cx = x1;	       	//min x
	in.x.dx = x2;		//max x
	int86(0x33,&in,&out);

	//set vertical limit of mouse i.e y coordinate
	in.x.ax = 8;
	in.x.cx = y1; 		//min y
	in.x.dx = y2;		//max y
	int86(0x33,&in,&out);
}
void main()
{
	clrscr();
	int gd=DETECT,gm,score=0,k=rand()%600,l=70,x,y;
	initgraph(&gd,&gm,"");

	//Bound the mouse positions
	bound(0,410,640,420);

	while(!kbhit())
	{
		pos(&x,&y);

		//Bucket with its colour
		setfillstyle(1,15);
		bar(x,410,x+20,420);

		//Set background color to RED i.e 4 of screen
		setfillstyle(1,4);
		bar(0,0,640,400);

		//At bottom  show black screen i.e 0
		setfillstyle(1,0);
		bar(0,400,640,480);

		//Position the text quote
		gotoxy(5,5);
		cout<<"Player 1: HARSH POPLAY";
		gotoxy(318,5);
		cout<<"Score: "<<score;

		//Colour the ball to BLUE
		setfillstyle(1,BLUE);
		fillellipse(k,l,10,15);

		//l is the y position from where ball drops down
		//k is the x position from where ball drops down
		if(l>410 && l<412) //When ball reaches the surface of ground
		{
			//x is current position of mouse
			//It overrides the bar dimensions
			if(x<k && k<(x+20))
				score = score+1;
		}

		//After the drop down of ball, again initialzing the
		//positions (x,y) of the ball drop down
		if(l>600)
		{
			l = 70;
			k = rand()%600;
		}
		l=l+1;
		delay(5);   		// To increase drop down speed less value of delay
	}//end of while loop
	getch();
	closegraph();
}