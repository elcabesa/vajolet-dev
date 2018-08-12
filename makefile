################################################################################
# Automatically-generated file. Do not edit!
################################################################################

RM := rm -rf

# All of the sources participating in the build are defined here

CPP_SRCS := \
./benchmark.cpp \
./bitops.cpp \
./book.cpp \
./command.cpp \
./data.cpp \
./endgame.cpp \
./eval.cpp \
./hashKeys.cpp \
./io.cpp \
./magicmoves.cpp \
./movegen.cpp \
./parameters.cpp \
./position.cpp \
./search.cpp \
./see.cpp \
./thread.cpp \
./transposition.cpp \
./vajolet.cpp \
./syzygy/tbprobe.cpp 

OBJS :=  \
./benchmark.o \
./bitops.o \
./book.o \
./command.o \
./data.o \
./endgame.o \
./eval.o \
./hashKeys.o \
./io.o \
./magicmoves.o \
./movegen.o \
./parameters.o \
./position.o \
./search.o \
./see.o \
./thread.o \
./transposition.o \
./vajolet.o \
./syzygy/tbprobe.o 



# Each subdirectory must supply rules for building sources it contributes
%.o: ./%.cpp
	g++ -std=c++1z -O3 -msse4.2 -mpopcnt -pedantic -Wall -Wextra -c -fmessage-length=0  -o "$@" "$<"

# Every subdirectory with source files must be described here
SUBDIRS := \
. \
syzygy \


# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: vajolet

# Tool invocations
vajolet: $(OBJS)

	g++ -s -pthread -o "vajolet" $(OBJS)


# Other Targets
clean:
	-$(RM) $(OBJS) vajolet
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

