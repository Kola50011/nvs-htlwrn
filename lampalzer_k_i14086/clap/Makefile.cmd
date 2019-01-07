           CC = g++
           AR = ar vr

      SRC_DIR = src
  INCLUDE_DIR = include
   TARGET_DIR = lib

      COMPILE = $(CC) -o $@ -I $(INCLUDE_DIR) -c

       CMDLIB = $(TARGET_DIR)/libcmd.a
       CMDOBJ = $(TARGET_DIR)/cmdline.o \
                $(TARGET_DIR)/cmdarg.o


all: $(CMDLIB) 

clean: clean_cmd 

# Rules for making command line library
$(CMDLIB): $(CMDOBJ)
	$(AR) $@ $(CMDOBJ)

$(TARGET_DIR)/cmdarg.o: $(SRC_DIR)/cmdarg.cc $(INCLUDE_DIR)/cmdarg.hh
	$(COMPILE) $(SRC_DIR)/cmdarg.cc

$(TARGET_DIR)/cmdline.o: $(SRC_DIR)/cmdline.cc $(INCLUDE_DIR)/cmdline.hh
	$(COMPILE) $(SRC_DIR)/cmdline.cc

clean_cmd:
	/usr/bin/rm -f $(CMDOBJ)
	/usr/bin/rm -f $(CMDLIB)

