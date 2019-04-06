SRC ?= $(realpath .)

include $(SRC)/test/Makefile
include $(SRC)/app/Makefile
include $(SRC)/doc/Makefile
