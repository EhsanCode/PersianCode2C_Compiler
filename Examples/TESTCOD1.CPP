 #include <graphics.h>
 #include <stdlib.h>
 #include <stdio.h>
 #include <conio.h>

void main(void)
	{
    /* request auto detection */
	 int gdriver = DETECT, gmode, errorcode;
	 int maxx, maxy;

   /* User valiabel */
	 int id0 , id1 ;

    /* initialize graphics, local variables */

	 initgraph(&gdriver, &gmode, "");

    /* read result of initialization */
	 errorcode = graphresult();
	 if (errorcode != grOk)
    /* an error occurred */
		{
		 printf("Graphics error: %s\n", grapherrormsg(errorcode));
		 printf("Press any key to halt:");
		 getch();
		 exit(1);
    /* terminate with an error code */
		}
    /* User Code */

	 lb0 :
	 setfillstyle ( SOLID_FILL , getcolor() ) ;
	 floodfill ( 12 , 39 - 37 , 7 ) ;
	 setfillstyle ( SOLID_FILL , getcolor() ) ;
	 floodfill ( id1 , 37 , 7 ) ;
	 setfillstyle ( SOLID_FILL , getcolor() ) ;
	 floodfill ( 12 , 39 - 37 , 2 ) ;
	 setcolor ( 1 ) ;
	 setcolor ( 12 ) ;
	 setbkcolor ( 4 ) ;
	 goto lb1 ;
	 if ( id1 >= 10 ) goto lb2 ;
	 id0 = id1  * 32  - 3498  + id0 ;
	 id1 = 23  * 34 ;
	 cleardevice() ;
	 lb1 :
	 arc ( 67 , id1 , 45 , 56 , 78 ) ;
	 circle ( 23 , 26 , 3 ) ;
	 id1 = 2 ;
	 id1 = 3  * 2  /  ( 2  - 1  + 1  ) ;
	 lb2 :
	 arc ( 67 , 34 , 45 , 56 , 78 ) ;
	 arc ( 67 , 34 , 45 , 56 , 78 ) ;
	 lb3 :
	 line ( 56 , 23 , 67 , 67 ) ;
	 line ( 56 , 23 , 67 , 67 ) ;
	 arc ( 67 , id1 + 34 , 45 , 56 , 78 ) ;
	 rectangle ( 23 , 56 , 56 , 89 ) ;
	 rectangle ( 23 , 56 , 56 , 89 ) ;
	 putpixel ( 5 , 6 , getcolor() ) ;
	 putpixel ( 5 / 4 , 6 , getcolor() ) ;
	 arc ( 45 , 12 , 56 , 56 , 76 ) ;
	 if ( id1 >= 10 ) goto lb2 ;
	 if ( 2 >= id1 * id1 ) goto lb2 ;
	 if ( 2 >= 10 ) goto lb2 ;
	 if ( 2 >= 10 ) goto lb2 ;
	 if ( 2 != 10 ) goto lb2 ;
	 if ( 2 != 10 ) goto lb2 ;
	 if ( 2 >= 10 ) goto lb2 ;
	 if ( 2 == 10 ) goto lb2 ;
	 if ( 2 == 10 ) goto lb2 ;
	 if ( 2 == 10 ) goto lb2 ;
	 if ( 2 <= 10 ) goto lb2 ;

   /* End User Code */
	 closegraph();
	}
