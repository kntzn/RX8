set pagination off
set confirm off
set print pretty on
set disassemble-next-line on

break main

layout split

target extended-remote localhost:3333

monitor reset halt