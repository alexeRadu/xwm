#include <stdio.h>
#include <X11/Xlib.h>

void display_info(Display *display)
{
	int screen, nscreens, default_screen;

	printf("X%d.%d:\n", XProtocolVersion(display), XProtocolRevision(display));
	printf("Vendor: %s - release %d\n", XServerVendor(display), XVendorRelease(display));
	printf("Connection number: %d\n", XConnectionNumber(display));
	printf("Request: size %ld units, ext size %ld units (each unit = 4 bytes)\n", XMaxRequestSize(display), XExtendedMaxRequestSize(display));
	printf("Request: next id %lu, last id %lu\n", XNextRequest(display), XLastKnownRequestProcessed(display));
	printf("Queue length: %d\n", XQLength(display));

	if (XImageByteOrder(display) == LSBFirst)
		printf("Image byte order: lsb\n");
	else
		printf("Image byte order: msb\n");

	printf("Bitmap unit: %d\n", XBitmapUnit(display));

	if (XBitmapBitOrder(display) == LSBFirst)
		printf("Bitmap bit order: lsb\n");
	else
		printf("Bitmap bit order: msb\n");

	printf("Bitmap pad: %d\n", XBitmapPad(display));

	nscreens = XScreenCount(display);
	default_screen = XDefaultScreen(display);
	for (screen = 0; screen < nscreens; screen++) {
		XPixmapFormatValues* pfv;
		int count, i;

		if (screen == default_screen)
			printf("# Screen %d (default)\n", screen);
		else
			printf("# Screen %d\n", screen);

		printf("depth: %d\n", XDisplayPlanes(display, screen));
		printf("default depth: %d\n", XDefaultDepth(display, screen));
		printf("colormap cells: %d\n", XDisplayCells(display, screen));
		printf("width x height: %d (%d) x %d (%d) pixels (mm)", XDisplayWidth(display, screen), XDisplayWidthMM(display, screen), XDisplayHeight(display, screen), XDisplayHeightMM(display, screen));

		pfv = XListPixmapFormats(display, &count);
		if (!pfv)
			continue;

		for (i = 0; i < count; i++)
			printf("## Pixmap depth %d - bits per pixel %d - scanline pad %d\n", pfv[i].depth, pfv[i].bits_per_pixel, pfv[i].scanline_pad);
		XFree(pfv);
	}
}

int main(int argc, char **argv)
{
	Display *display;
	Window rootwnd, wnd;
	int loop = 1;

	display = XOpenDisplay(NULL);
	if (display == NULL) {
		printf("Unable to open the default display\n");
		return 1;
	}

	display_info(display);

	rootwnd = XDefaultRootWindow(display);
	XSelectInput(display, rootwnd, ButtonPressMask);
	XSync(display, 0);

	wnd = XCreateWindow(display, rootwnd,
						10, 10, 300, 300,
						1, CopyFromParent, InputOutput, CopyFromParent,
						SubstructureNotifyMask, 0);
	XMapWindow(display, wnd);

	while (loop) {
		XEvent e;

		XNextEvent(display, &e);

		switch (e.type) {
			case ButtonPress:
				loop = 0;
				break;
			default:
				printf("XEvent not yet handledi\n");
		}
	}

	return 0;
}
