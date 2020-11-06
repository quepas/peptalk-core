add_library( peptalk_io SHARED src/PEPReader.cpp src/PEPWriter.cpp )
target_include_directories( peptalk_io PUBLIC include/ )
set_property( TARGET peptalk_io PROPERTY POSITION_INDEPENDENT_CODE ON )

add_library( peptalk_io_static STATIC src/PEPReader.cpp src/PEPWriter.cpp )
target_include_directories( peptalk_io_static PUBLIC include/ )
set_property( TARGET peptalk_io_static PROPERTY POSITION_INDEPENDENT_CODE ON )
