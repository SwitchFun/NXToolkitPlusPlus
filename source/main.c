#include <string.h>
#include <stdio.h>
#include <switch.h>
//RCM VARIABLES | Credit to Rei
#pragma once
#define BCT_SZ 0x4000
#define BCT_KEY_OFF 0x210
#define KB_SZ 0xB0
#define NUM_KBS 32
#define RCM_XOR 0x77

int movable = 1;
int warningRCM = 0;
void updateConsole(int current){
	consoleClear();
	movable = 1;
	printf("NXToolkit++\n");
   	printf("\n\x1b[2;4HAutoRCM");
   	printf("\n\x1b[3;4HExit");
	printf ("\x1b[%d;2H>", current);
}

void AutoRCMWarning(){
	consoleClear();
	movable = 0;
	printf("AutoRCM will boot RCM everytime you boot your switch, continue?\n\n\n");
	warningRCM = 1;
	printf("[Y] Continue\n");
	printf("[B] Return to menu\n");
}
void toggleRcm(){
	consoleClear();
	printf("Toggling RCM...\m");
	FsStorage storage;

	int boot0_part = 0;

	Result r = fsOpenBisStorage(&storage, boot0_part);

	u64 size = 0;

	fsStorageGetSize(&storage, &size);

	if (size == 0)
	{
	printf("[*] Error! Size was 0 unexpected.\n");
	return -1;
	}

	char *buf = (char *)malloc(size);
	r = fsStorageRead(&storage, 0, buf, size);
	for (int i = 0; i < 4; i++)
	{
		printf("[*] BCT - SETTING OFFSET (REPEATING)\n");
		int off = BCT_KEY_OFF + i * BCT_SZ;
		int offAmount = 0;
		buf[off] ^= RCM_XOR;
		if (buf[off] != 0xF7)
		{
			offAmount + offAmount + 1;
			if(offAmount < 4){
			printf("[*] BUFFER != 0xF7! | Time: %d" + offAmount);
			printf("\n");
			}else{
				printf("[*] ERROR offset Amount ='s something about 4.");
			}
		}
	
}

	printf("[*] Preparing to write to onboard storage\n");
    fsStorageWrite(&storage, 0, buf, size);
	printf("[*] Data has been written.\n");
	fsStorageClose(&storage);
	printf("[*] Closing fsStorage\n");
	free(buf);
	printf("\n[*] AutoRCM has been toggled! Enjoy!\n");
	printf("Press B to return back to menu.");
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
		if(movable == 1){
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

		if(kDown & KEY_A & current == 2){
			AutoRCMWarning();
		}
		}
		if(kDown & KEY_B){
			updateConsole(current);
		}
		if(kDown & KEY_Y){
			if(warningRCM == 1){
				toggleRcm();
			}
		}
        consoleUpdate(NULL);
    }
	//MARK: EXIT CONSOLE
    consoleExit(NULL);
	//MARK: RETURN AKA FINISH EXIT
    return 0;
}
