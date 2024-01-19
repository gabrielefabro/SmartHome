

#IDIR=../hdr
IDIR=.
ODIR=../obj
BDIR=../bin

CC=g++

# Additional Directories
SRC_CAMERA_DIR=../../Components/Camera/src
OBJ_CAMERA_DIR=../../Components/Camera/obj

SRC_CONDITIONER_DIR=../../Components/Conditioner/src
OBJ_CONDITIONER_DIR=../../Components/Conditioner/obj

SRC_DEVICE_DIR=../../Components/Device/src
OBJ_DEVICE_DIR=../../Components/Device/obj

SRC_LIGHT_DIR=../../Components/Light/src
OBJ_LIGHT_DIR=../../Components/Light/obj

SRC_SENSOR_DIR=../../Components/Sensor/src
OBJ_SENSOR_DIR=../../Components/Sensor/obj

SRC_SENSORGARDEN_DIR=../../Components/SensorGarden/src
OBJ_SENSORGARDEN_DIR=../../Components/SensorGarden/obj

SRC_DB_DIR=../../con2db/src
OBJ_DB_DIR=../../con2db/obj

# use this when connecting to Postgresql (library lpq)
#CFLAGS=-std=c++11 -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm 
CFLAGS=-std=c++20 -I. -I$(IDIR) -I/usr/include/postgresql -lpq -lm 
LIBDIR = -L/path/to/redis/lib
LIBS = -lhiredis -lpq -lm

# use this when no connection to Postgresql (library lpq) is needed
#CFLAGS=-std=c++11 -I. -I$(IDIR) -lm 

DEPS = $(wildcard $(IDIR)/*.h)
#OBJ = $(wildcard $(ODIR)/*.o)

DEPS1 = $(wildcard $(SRC_CAMERA_DIR)/*.h)
DEPS2 = $(wildcard $(SRC_CONDITIONER_DIR)/*.h)
DEPS3 = $(wildcard $(SRC_DEVICE_DIR)/*.h)
DEPS4 = $(wildcard $(SRC_LIGHT_DIR)/*.h)
DEPS5 = $(wildcard $(SRC_SENSOR_DIR)/*.h)
DEPS6 = $(wildcard $(SRC_SENSORGARDEN_DIR)/*.h)
DEPS7 = $(wildcard $(SRC_DB_DIR)/*.h)

SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, $(ODIR)/%.o, $(SRC))

SRC_CAMERA = $(wildcard $(SRC_CAMERA_DIR)/*.cpp)
OBJ_CAMERA = $(patsubst $(SRC_CAMERA_DIR)/%.cpp, $(OBJ_CAMERA_DIR)/%.o, $(SRC_CAMERA))

SRC_CONDITIONER = $(wildcard $(SRC_CONDITIONER_DIR)/*.cpp)
OBJ_CONDITIONER = $(patsubst $(SRC_CONDITIONER_DIR)/%.cpp, $(OBJ_CONDITIONER_DIR)/%.o, $(SRC_CONDITIONER))

SRC_DEVICE = $(wildcard $(SRC_DEVICE_DIR)/*.cpp)
OBJ_DEVICE = $(patsubst $(SRC_DEVICE_DIR)/%.cpp, $(OBJ_DEVICE_DIR)/%.o, $(SRC_DEVICE))

SRC_LIGHT = $(wildcard $(SRC_LIGHT_DIR)/*.cpp)
OBJ_LIGHT = $(patsubst $(SRC_LIGHT_DIR)/%.cpp, $(OBJ_LIGHT_DIR)/%.o, $(SRC_LIGHT))

SRC_SENSOR = $(wildcard $(SRC_SENSOR_DIR)/*.cpp)
OBJ_SENSOR = $(patsubst $(SRC_SENSOR_DIR)/%.cpp, $(OBJ_SENSOR_DIR)/%.o, $(SRC_SENSOR))

SRC_SENSORGARDEN = $(wildcard $(SRC_SENSORGARDEN_DIR)/*.cpp)
OBJ_SENSORGARDEN = $(patsubst $(SRC_SENSORGARDEN_DIR)/%.cpp, $(OBJ_SENSORGARDEN_DIR)/%.o, $(SRC_SENSORGARDEN))

SRC_DB = $(wildcard $(SRC_DB_DIR)/*.cpp)
OBJ_DB = $(patsubst $(SRC_DB_DIR)/%.cpp, $(OBJ_DB_DIR)/%.o, $(SRC_DB))


all: $(BDIR)/main

$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_CAMERA_DIR)/%.o: $(SRC_CAMERA_DIR)/%.cpp $(DEPS1)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_CONDITIONER_DIR)/%.o: $(SRC_CONDITIONER_DIR)/%.cpp $(DEPS2)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DEVICE_DIR)/%.o: $(SRC_DEVICE_DIR)/%.cpp $(DEPS3)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_LIGHT_DIR)/%.o: $(SRC_LIGHT_DIR)/%.cpp $(DEPS4)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_SENSOR_DIR)/%.o: $(SRC_SENSOR_DIR)/%.cpp $(DEPS5)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_SENSORGARDEN_DIR)/%.o: $(SRC_SENSORGARDEN_DIR)/%.cpp $(DEPS6)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_DB_DIR)/%.o: $(SRC_DB_DIR)/%.cpp $(DEPS7)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BDIR)/main: $(OBJ) $(OBJ_CAMERA) $(OBJ_CONDITIONER) $(OBJ_DEVICE) $(OBJ_LIGHT) $(OBJ_SENSOR) $(OBJ_SENSORGARDEN) $(OBJ_DB) $(DEPS) $(DEPS1) $(DEPS2) $(DEPS3) $(DEPS4) $(DEPS5) $(DEPS6) $(DEPS7)
	$(CC) -o $@ $(OBJ) $(OBJ_CAMERA) $(OBJ_CONDITIONER) $(OBJ_DEVICE) $(OBJ_LIGHT) $(OBJ_SENSOR) $(OBJ_SENSORGARDEN) $(OBJ_DB) $(CFLAGS) -L/path/to/redis/lib $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ $(IDIR)/*~ core
	rm -f $(OBJ_CAMERA_DIR)/*.o *~ $(SRC_CAMERA_DIR)/*~ core
	rm -f $(OBJ_CONDITIONER_DIR)/*.o *~ $(SRC_CONDITIONER_DIR)/*~ core
	rm -f $(OBJ_DEVICE_DIR)/*.o *~ $(SRC_DEVICE_DIR)/*~ core
	rm -f $(OBJ_LIGHT_DIR)/*.o *~ $(SRC_LIGHT_DIR)/*~ core
	rm -f $(OBJ_SENSOR_DIR)/*.o *~ $(SRC_SENSOR_DIR)/*~ core
	rm -f $(OBJ_SENSORGARDEN_DIR)/*.o *~ $(SRC_SENSORGARDEN_DIR)/*~ core
	rm -f $(OBJ_DB_DIR)/*.o *~ $(SRC_DB_DIR)/*~ core

	