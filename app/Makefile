APP := $(SRC)/app

APP_CFLAGS := -I$(APP) -I$(SRC) -Wall -Werror

ifdef DEBUG
APP_CFLAGS += -g -O2
else
APP_CFLAGS += -flto -O3
endif

APP_LIST := clrz chase
APP_LIST +=

.PHONY: app $(APP_LIST)
app: $(APP_LIST)
	@echo done building apps

define do_app
	rm -rf $@
	gcc $(APP_CFLAGS) $^ -o $@ $(LDFLAGS)
endef

clrz: $(APP)/clrz/clrz.c $(APP)/clrz/text.c
	$(call do_app)

chase: LDFLAGS := $(LDFLAGS) -lncurses
chase: $(addprefix $(APP)/chase/,main.c view.c model.c ctrl.c)
	$(call do_app)
