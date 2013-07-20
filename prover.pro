TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fol/shared_term_bank.cpp \
    fol/primitive_logic_types.cpp \
    system/parser.cpp \
    murmurhash/murmurhash.cpp \
    system/prover.cpp \
    fol/clausification.cpp

HEADERS += \
    fol/primitive_logic_types.h \
    fol/shared_term_bank.h \
    fol/primitive_logic_types_inl.h \
    fol/utilities.hpp \
    system/parser.hpp \
    murmurhash/murmurhash.hpp \
    system/prover.hpp \
    fol/clausification.hpp

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += \
    fol/grammar.yy
