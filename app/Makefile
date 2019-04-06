APP := $(SRC)/app

ifdef DEBUG
APP_CFLAGS := -g -O2 -I$(SRC) -Wall -Werror
else
APP_CFLAGS := -flto -O3 -I$(SRC) -Wall -Werror
endif

APP_LIST := clrz
APP_LIST +=

.PHONY: app $(APP_LIST)
app: $(APP_LIST)
	@echo done building apps

define do_app
	rm -rf $@
	gcc $(APP_CFLAGS) $< -o $@
endef

clrz: $(APP)/clrz/clrz.c
	$(call do_app)
