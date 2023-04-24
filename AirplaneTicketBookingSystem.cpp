#include<bits/stdc++.h>
#include<graphics.h>
using namespace std;

struct Econo_Airlines
{
    int seat_identification_number;
    char status;
    char last_name[20];
    char first_name[20];

} flight[12];

void setup()
{
    for (int i = 0; i < 13; i++)
    {
        flight[i].status = 'A';
    }

    FILE *inf;
    struct Econo_Airlines dummy;

    inf = fopen("c1.txt", "r");
    int i = 0;
    while (fread(&dummy, sizeof(struct Econo_Airlines), 1, inf))
    {
        flight[i].status = dummy.status;
        strcpy(flight[i].first_name, dummy.first_name);
        strcpy(flight[i].last_name, dummy.last_name);
        i += 1;
    }
    fclose(inf);
}

void seat_assignments()
{
    printf("------------SEAT ASSIGNMENTS------------\n");
    for (int i = 1; i <= 12; i++)
    {
        if (i % 2)
        {
            printf("\n");
        }
        printf("\tSEAT %.2d: %c", i, flight[i].status);
    }
    printf("\n\n");
    printf("\tA = AVAILABLE \t N = NOT AVAILABLE\n\n");
}

void get_available_seats()
{
    int count = 0;
    for (int i = 1; i <= 12; i++)
    {
        if (i % 2)
        {
            printf("\n");
        }
        if (flight[i].status == 'A')
        {
            printf("\tSEAT %.2d\t", i);
            count += 1;
        }
        else
        {
            printf("\t ----\t");
        }
    }
    printf("\n\n\tTOTAL AVAILABLE SEATS : %d\n\n", count);
}

void get_assigned_seats()
{
    int count = 0;
    for (int i = 1; i <= 12; i++)
    {
        if (i % 2)
        {
            printf("\n");
        }
        if (flight[i].status == 'N')
        {
            printf("\tSEAT-%.2d OWNER : %s", i, flight[i].first_name);
            count += 1;
        }
        else
        {
            printf("\t\t----\t");
        }
    }
    printf("\n\n\tTOTAL ASSIGNED SEATS : %d \n\n", count);
}
void assigned_seat()
{
    int n;
    char f_name[50], l_name[50];
    printf("Enter a seat no :");
    scanf("%d", &n);
    if (flight[n].status == 'A')
    {
        printf("Enter Your First Name \n");
        scanf("%s", f_name);
        strcpy(flight[n].first_name, f_name);
        printf("Enter Your Last Name \n");
        scanf("%s", l_name);
        strcpy(flight[n].last_name, l_name);
        flight[n].status = 'N';
        printf("Seat %d is assigned to %s %s successfully\n\n", n, flight[n].first_name, flight[n].last_name);
    }
    else
    {
        printf("Seat %d is not available\n\n", n);
    }
}
void delete_reservation()
{
    int n;
    printf("Enter a seat no :");
    scanf("%d", &n);
    flight[n].status = 'A';
    strcpy(flight[n].first_name, "");
    strcpy(flight[n].last_name, "");
    printf("Seat No %d is deleted sucessfull\n\n", n);
}

void delete_all_seat()
{
    for (int i = 0; i <= 12; i++)
    {
        flight[i].status = 'A';
        strcpy(flight[i].first_name, "");
        strcpy(flight[i].last_name, "");
    }
    printf("Delete ALL seat assignments successfully\n\n");
}
void save_data()
{
    FILE *of;
    of = fopen("c1.txt", "w");
    for (int i = 0; i <= 12; i++)
    {
        fwrite(&flight[i], sizeof(struct Econo_Airlines), 1, of);
    }
    fclose(of);
}


void arrow(int color,int pos)
{
	setcolor(color);
	int points[8]={170,190+pos*50,220-10,210+pos*50,170,230+pos*50,170,190+pos*50};
	drawpoly(4,points);
	setfillstyle(SOLID_FILL,color);
	fillpoly(4,points);

}

// menu bar
void menu(int box_color,int text_color)
{
    setcolor(box_color);

    setcolor(text_color);
	settextstyle(EUROPEAN_FONT,HORIZ_DIR,4);
	outtextxy(240,200,"A) Display ALL seat assignments");
	outtextxy(240,250,"B) Show Available seats");
	outtextxy(240,300,"C) Show Assigned seats");
	outtextxy(240,350,"D) Assigned a seat");
	outtextxy(240,400,"E) Delete One seat assignment");
	outtextxy(240,450,"F) Delete All seat assignment");
	outtextxy(240,500,"Q) Quit program");
}
int mainmenu()
{
	initwindow(1000,1000,"Booking Menu",150,50);
	int arrow_color=14;
   	int box_color=11;
   	int text_color=14;
   	int pos=0;
   	int page=0;
   	arrow(arrow_color, pos);
   	do{
   		setactivepage(page);
   		setvisualpage(1-page);
		cleardevice();
		if (GetAsyncKeyState(VK_DOWN))
        {
        	pos = (pos + 1) % 7;
        }
        else if (GetAsyncKeyState(VK_UP))
        {
            pos = (pos +6) % 7;
        }
		arrow(arrow_color, pos);
		menu(box_color,text_color);
		delay(250);
		page=1-page;

	}while(!GetAsyncKeyState(VK_SPACE));
	closegraph();
	return pos;
}

int main()
{
    setup();
	int ch;
 do{
       ch=mainmenu();

		switch(ch)
		{
			case 0:
				seat_assignments();
				break;
			case 1:
				get_available_seats();
				break;
			case 2:
				get_assigned_seats();
				break;
			case 3:
				assigned_seat();
				break;
			case 4:
				delete_reservation();
				break;
			case 5:
				delete_all_seat();
				break;
			case 6:
				save_data();
				break;
		}
	}while(ch!=7);
	return 0;
}