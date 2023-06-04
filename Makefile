# ----------------------------
# Program Options
# ----------------------------

NAME         ?= DUCKHUNT
ICON         ?= icon.png
DESCRIPTION  ?= "(c) 2021-2023, Alvajoy Asante"
COMPRESSED   ?= YES
ARCHIVED     ?= NO

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

