/*
 * Author:              Fatih Mert Doğancan
 * Author Web:          fatihmert.dev
 *
 * Simple Terminal HexView with C99
 *
 * Example use
 *  simple_terminal_hexview.exe -[your imagination without space like variable :)] filename.bin
 *  simple_terminal_hexview.exe -f filename.bin
 *  simple_terminal_hexview.exe -f*ck filename.bin
 * */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <ctype.h>

#define BLOCK_WIDTH 16

typedef unsigned char byte, *buffer;

int main(int argc, char **argv) {
    unsigned int fileLen;                   // File size

    FILE *fp;                               // File object
    int fileIdx = (-1);                     // file index

    if(argc >= 3){
        fp = fopen(argv[2],"rb");
    } else {
        fp = fopen("test.bin", "rb");
    }

    buffer buff;

    fseek(fp, 0, SEEK_END);            // Jump to the end of the file
    fileLen = ftell(fp);                      // Get the current byte offset in the file
    fseek(fp, 0, SEEK_SET);            // Jump back to the beginning of the file
    buff = calloc(fileLen, sizeof(byte));     // fully into until file size empty bytes
    fread(buff, sizeof(byte), fileLen, fp);   // assign file to buff
    fclose(fp);

    int width_current = 0,
        dump_current = 1,
        dump_current_start = 0;
    while( ++fileIdx <= fileLen ){
        byte current = buff[fileIdx];

        if ( ++width_current < BLOCK_WIDTH){
            printf("%.2X ", current);
        } else {
            width_current = 0;
            printf(" | ");

            for (; dump_current_start < dump_current * BLOCK_WIDTH; ++dump_current_start) {
                byte current_tmp = buff[dump_current_start];

                // write half-readable
                setlocale(LC_ALL, "");
                printf("%lc", isprint(current_tmp) ? current_tmp : '.');
            }

            dump_current_start = (++dump_current-1) * BLOCK_WIDTH;
            printf("\n");
        }
    }

    fclose(fp);
    return 0;
}
