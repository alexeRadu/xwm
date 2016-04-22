#include <stdio.h>
#include <X11/Xlib.h>

int main(int argc, char **argv)
{
	Display *display;
	int screen;

	display = XOpenDisplay(NULL);
	if (display == NULL) {
		printf("Unable to open the default display\n");
		return 1;
	}

	printf("Connection number: %d\n", XConnectionNumber(display));
	printf("Display number: %d\n", XDefaultScreen(display));

	screen = DefaultScreen(display);	
	printf("Display width x height: %d x %d\n", DisplayWidth(display, screen), DisplayHeight(display, screen));

	return 0;
}
