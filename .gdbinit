set pagination off
set confirm off
set print pretty on
set disassemble-next-line on

layout split

file build/firmware.elf

target extended-remote localhost:3333


monitor reset halt

break main
continue