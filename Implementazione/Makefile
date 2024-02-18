
CC=g++

# Additional Directories
SRC_CAMERA_DIR=./Components/Camera/src
OBJ_CAMERA_DIR=./Components/Camera/obj
BIN_CAMERA_DIR=./Components/Camera/bin

SRC_CONDITIONER_DIR=./Components/Conditioner/src
OBJ_CONDITIONER_DIR=./Components/Conditioner/obj
BIN_CONDITIONER_DIR=./Components/Conditioner/bin

SRC_DEVICE_DIR=./Components/Device/src
OBJ_DEVICE_DIR=./Components/Device/obj
BIN_DEVICE_DIR=./Components/Device/bin

SRC_LIGHT_DIR=./Components/Light/src
OBJ_LIGHT_DIR=./Components/Light/obj
BIN_LIGHT_DIR=./Components/Light/bin

SRC_SENSOR_DIR=./Components/Sensor/src
OBJ_SENSOR_DIR=./Components/Sensor/obj
BIN_SENSOR_DIR=./Components/Sensor/bin

SRC_SENSORGARDEN_DIR=./Components/SensorGarden/src
OBJ_SENSORGARDEN_DIR=./Components/SensorGarden/obj
BIN_SENSORGARDEN_DIR=./Components/SensorGarden/bin

SRC_DB_DIR=./con2db/src
OBJ_DB_DIR=./con2db/obj


SRC_FUNC_DIR=./Monitors/Functional/src
OBJ_FUNC_DIR=./Monitors/Functional/obj

SRC_NFUN_DIR=./Monitors/NonFunctional/src
OBJ_NFUN_DIR=./Monitors/NonFunctional/obj

SRC_COMMAND_DIR=./Components/Command/src
OBJ_COMMAND_DIR=./Components/Command/obj
BIN_COMMAND_DIR=./Components/Command/bin

SRC_SOFTWARE_DIR=./Components/Software/src
OBJ_SOFTWARE_DIR=./Components/Software/obj
BIN_SOFTWARE_DIR=./Components/Software/bin

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
DEPS8 = $(wildcard $(SRC_COMMAND_DIR)/*.h)
DEPS9 = $(wildcard $(SRC_SOFTWARE_DIR)/*.h)



SRC_CAMERA = $(wildcard $(SRC_CAMERA_DIR)/*.cpp)
OBJ_CAMERA = $(patsubst $(SRC_CAMERA_DIR)/%.cpp, $(OBJ_CAMERA_DIR)/%.o, $(SRC_CAMERA))
BIN_CAMERA = $(BIN_CAMERA_DIR)/camera_executable

SRC_CONDITIONER = $(wildcard $(SRC_CONDITIONER_DIR)/*.cpp)
OBJ_CONDITIONER = $(patsubst $(SRC_CONDITIONER_DIR)/%.cpp, $(OBJ_CONDITIONER_DIR)/%.o, $(SRC_CONDITIONER))
BIN_CONDITIONER = $(BIN_CONDITIONER_DIR)/conditioner_executable

SRC_DEVICE = $(wildcard $(SRC_DEVICE_DIR)/*.cpp)
OBJ_DEVICE = $(patsubst $(SRC_DEVICE_DIR)/%.cpp, $(OBJ_DEVICE_DIR)/%.o, $(SRC_DEVICE))
BIN_DEVICE = $(BIN_DEVICE_DIR)/device_executable

SRC_LIGHT = $(wildcard $(SRC_LIGHT_DIR)/*.cpp)
OBJ_LIGHT = $(patsubst $(SRC_LIGHT_DIR)/%.cpp, $(OBJ_LIGHT_DIR)/%.o, $(SRC_LIGHT))
BIN_LIGHT = $(BIN_LIGHT_DIR)/light_executable

SRC_SENSOR = $(wildcard $(SRC_SENSOR_DIR)/*.cpp)
OBJ_SENSOR = $(patsubst $(SRC_SENSOR_DIR)/%.cpp, $(OBJ_SENSOR_DIR)/%.o, $(SRC_SENSOR))
BIN_SENSOR = $(BIN_SENSOR_DIR)/sensor_executable

SRC_SENSORGARDEN = $(wildcard $(SRC_SENSORGARDEN_DIR)/*.cpp)
OBJ_SENSORGARDEN = $(patsubst $(SRC_SENSORGARDEN_DIR)/%.cpp, $(OBJ_SENSORGARDEN_DIR)/%.o, $(SRC_SENSORGARDEN))
BIN_SENSORGARDEN = $(BIN_SENSORGARDEN_DIR)/sensorgarden_executable

SRC_DB = $(wildcard $(SRC_DB_DIR)/*.cpp)
OBJ_DB = $(patsubst $(SRC_DB_DIR)/%.cpp, $(OBJ_DB_DIR)/%.o, $(SRC_DB))

SRC_FUNC = $(wildcard $(SRC_FUNC_DIR)/*.cpp)
OBJ_FUNC = $(patsubst $(SRC_FUNC_DIR)/%.cpp, $(OBJ_FUNC_DIR)/%.o, $(SRC_FUNC))

SRC_NFUN = $(wildcard $(SRC_NFUN_DIR)/*.cpp)
OBJ_NFUN = $(patsubst $(SRC_NFUN_DIR)/%.cpp, $(OBJ_NFUN_DIR)/%.o, $(SRC_NFUN))

SRC_COMMAND = $(wildcard $(SRC_COMMAND_DIR)/*.cpp)
OBJ_COMMAND = $(patsubst $(SRC_COMMAND_DIR)/%.cpp, $(OBJ_COMMAND_DIR)/%.o, $(SRC_COMMAND))
BIN_COMMAND = $(BIN_COMMAND_DIR)/command_executable

SRC_SOFTWARE = $(wildcard $(SRC_SOFTWARE_DIR)/*.cpp)
OBJ_SOFTWARE = $(patsubst $(SRC_SOFTWARE_DIR)/%.cpp, $(OBJ_SOFTWARE_DIR)/%.o, $(SRC_SOFTWARE))
BIN_SOFWARE = $(BIN_SOFTWARE_DIR)/software_executable


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

$(OBJ_FUNC_DIR)/%.o: $(SRC_FUNC_DIR)/%.cpp 
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_NFUN_DIR)/%.o: $(SRC_NFUN_DIR)/%.cpp
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_COMMAND_DIR)/%.o: $(SRC_COMMAND_DIR)/%.cpp $(DEPS8)
	$(CC) -c -o $@ $< $(CFLAGS)

$(OBJ_SOFTWARE_DIR)/%.o: $(SRC_SOFTWARE_DIR)/%.cpp $(DEPS9)
	$(CC) -c -o $@ $< $(CFLAGS)

$(BIN_CAMERA): $(OBJ_CAMERA)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_CONDITIONER): $(OBJ_CONDITIONER)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_DEVICE): $(OBJ_DEVICE)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_LIGHT): $(OBJ_LIGHT)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_SENSOR): $(OBJ_SENSOR)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_SENSORGARDEN): $(OBJ_SENSORGARDEN)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_COMMAND): $(OBJ_COMMAND)
	$(CC) -o $@ $^ $(CFLAGS)

$(BIN_SOFTWARE): $(OBJ_SOFTWARE)
	$(CC) -o $@ $^ $(CFLAGS)

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
	rm -f $(OBJ_FUNC_DIR)/*.o *~ $(SRC_FUNC_DIR)/*~ core
	rm -f $(OBJ_NFUN_DIR)/*.o *~ $(SRC_NFUN_DIR)/*~ core

	