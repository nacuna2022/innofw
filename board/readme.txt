Application + board level implementation

directory structure

board/<board_name>
- board names are usually the engineering name of the product, 
  e.g. bm11m, bm15m, bm18m, rl06

<board_name>/src
- board level implementation including the application should be found here.

<board_name>/include
- header files for the board

<board_name>/config
- the board defconfigs


board implementations should also have the ff:
Kconfig
defs.mk <- board definitions
Make.def


startup flow.. so we know how to connect things together:

essentially we are working with 4 blocks defined below:
1. the CPU block (arm/armvX...)
2. the MCU block with contains the peripherals
3. the BOARD block which uses the MCU to put peripherals in their working state
   3.1 the board also knows its own configuration e.g. which peripherals 
       to enable and what configuration they need to be in.
4.the FREERTOS block

The flow is as follows:
CPU BLOCK
   we start with the arm specific startup (e.g. armv7-m/armv7_head.c) which 
   defines the initial stack, entry point and the interrupt vectors of the MCU.
   - zero out the BSS
   - relocate readonly data
   - call the libc initialization
   - call the start_board() function

BOARD BLOCK
   the generic board block (board/board.c::start_board()) controls the rest of
   the startup flow from here.
   - initialize the FREERTOS block
   - initialize subsystems (driver/interrupt processing/etc subsystems)
   - register exception handlers? systick handler... etc.
   - call the board_initialize() that is defined by the actual board. 
     (e.g. board/gd32f425_demo/board_init.c)

MCU_BLOCK
   the board_initialize() is the opportunity to initialize the MCU lowlevel 
   peripherals. most of the environment is initialized at this point.
   the code can use the memory allocator, can create tasks, etc.
   - initialize the board peripherals to be used
   - register interrupts (via the interrupt processing subsystem)
   - create tasks used by the board

BOARD BLOCK
   when the board_initialize() returns, control goes back to the BOARD BLOCK
   - just start the FreeRTOS scheduler.

FREERTOS BLOCK
   - the scheduler is running now and tasks are being executed.






