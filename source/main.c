#include <string.h>
#include <stdio.h>
#include <switch.h>
void updateConsole(int current){
	consoleClear();
	printf("NXToolkit++\n");
   	printf("\n\x1b[2;4HAutoRCM");
   	printf("\n\x1b[3;4HExit");
	printf ("\x1b[%d;2H>", current);
}

int main(int argc, char **argv)
{
   
   consoleInit(NULL);
   
   int current = 2;
   int options = 3;

	updateConsole(current);

    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_UP) {
			current += 1;
			if (current > options) {
				current = 2;
			}

			updateConsole(current);
		}
		else if (kDown & KEY_DOWN) {
			current -= 1;
			if (current < options && current == 1) {
				current = options;
			}

			updateConsole(current);
		}
        if (kDown & KEY_PLUS) break;
		if(kDown & KEY_A && current == 3){
			break;
		}
        consoleUpdate(NULL);
    }
	//MARK: EXIT CONSOLE
    consoleExit(NULL);
	//MARK: RETURN AKA FINISH EXIT
    return 0;
}
