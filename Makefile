# ----------------------------
# Program Options
# ----------------------------

NAME         ?= DUCKHUNT
ICON         ?= icon.png
DESCRIPTION  ?= "DuckHunt v1.0"
COMPRESSED   ?= YES
ARCHIVED     ?= NO

CFLAGS ?= -Wall -Wextra -Oz
CXXFLAGS ?= -Wall -Wextra -Oz

# ----------------------------

ifndef CEDEV
$(error CEDEV environment path variable is not set)
endif

include $(CEDEV)/meta/makefile.mk

