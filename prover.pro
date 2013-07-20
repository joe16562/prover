TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    fol/shared_term_bank.cpp \
    fol/primitive_logic_types.cpp \
    system/parser.cpp \
    murmurhash/murmurhash.cpp \
    fol/symbol_table.cpp \
    system/prover.cpp \
    fol/clausify.cpp

HEADERS += \
    fol/primitive_logic_types.h \
    fol/shared_term_bank.h \
    fol/primitive_logic_types_inl.h \
    fol/utilities.hpp \
    system/parser.hpp \
    murmurhash/murmurhash.hpp \
    fol/symbol_table.hpp \
    system/prover.hpp \
    fol/clausification.hpp

QMAKE_CXXFLAGS += -std=c++11
