SRC := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ := $(SRC:.cpp=.o)
EXE := NeuronsDetector

EIGEN_PREFIX         := $(HOME)/aams/libs/eigen
BOOST_PREFIX         := $(HOME)/aams/libs/boost
OPENCV_PREFIX        := $(HOME)/aams/libs/opencv
TIFF_PREFIX          := $(HOME)/aams/libs/tiff

CPP := g++
CPPFLAGS := -Wall \
			-std=c++0x \
			-g \
            -O0 \
            -Wfatal-errors \
            -I$(BOOST_PREFIX)/include \
            -I$(OPENCV_PREFIX)/include \
            -I$(TIFF_PREFIX)/include \
            -I$(EIGEN_PREFIX)
LDFLAGS :=  -L$(BOOST_PREFIX)/lib \
			-L$(TIFF_PREFIX)/lib \
            -L$(OPENCV_PREFIX)/lib \
            -ltiff \
            -lopencv_core \
            -lopencv_highgui \
            -lopencv_imgproc \
            -lopencv_features2d \
            -lopencv_ml \
            -lopencv_objdetect \
            -lopencv_flann \
			-lopencv_photo \
			-lopencv_calib3d \
			-lopencv_nonfree \
            -lboost_program_options \
            -lboost_date_time \
            -lboost_filesystem \
            -lboost_system \
            -lopencv_video

$(OBJDIR)/%.o:	      %.cpp
		      $(CPP) $(CPPFLAGS) -o $@ -c $<

$(EXE):		      $(OBJ)
		      $(CPP) $(OBJ) $(LDFLAGS) -o $@

all:		      $(EXE)

clean:
		      rm $(OBJ)

install:	      all
		      mkdir $(INSTALL_BIN_DIR) >/dev/null 2>&1 || true
		      install -m 0755 $(EXE) $(INSTALL_BIN_DIR)/
