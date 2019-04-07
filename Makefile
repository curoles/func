SRC ?= $(realpath .)

TIME := /usr/bin/time -f "Time:\t%E"

include $(SRC)/test/Makefile
include $(SRC)/app/Makefile
include $(SRC)/doc/Makefile
