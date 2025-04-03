Building runtime for STM32L476RG (Cortex-M4F) without using HAL and generated headers.
Running on the Nucleo-64 L476RG board.

At the moment the program only blinks the USER LED built on the nucleo board twice per second using Timer7 and interrupts.
I hope to get DMA working soon.

This project is similar to my other project "avr_minimal_runtime" which was based on Atmega8, AVR architecture.
(As of writing this, available at https://github.com/msaw328/avr_minimal_runtime)

Hopefully i will get around to documenting both projects, but for now the best writeup
is in the comments and notes directory.

Heavily based on excellent blog posts (first 3 at the moment) available here:
https://vivonomicon.com/category/stm32_baremetal_examples/page/2/
with some modifications since:
 - I used a different chip
 - I found some code to be easy to optimize (for instance the vector table, with a use of a macro)
 - I did not want to use vendor headers

Recommended manuals which helped me along the way, in no specific order:
 (from ST website)
 - Nucleo board PDF (Nucleo 64, ST32L476RG) UM1724/MB1136 (first is doc ID, second board ID i think?)
 - STM32L476xx Data sheet
 - STM32L4xxxx Reference manual RM0351
 - STM32 Cortex-M4 Programming manual PM0214
 - Electronic schematics of the board (MB1136 maybe is the doc id of schematic?)
 - STM32 Application note AN2606 (for information on boot modes)

 (from ARM website)
 - ARM and THUMB instruction set specs
 - Cortex-M4 Technical reference manual
 - ARM7M Architecture Reference manual 

The solution to any problem usually required knowledge from multiple of those sources.
I recommend looking in all of them selectively by topic when needed.
In this project, references are made to mentioned documents in notes, as well as in some places in code.
