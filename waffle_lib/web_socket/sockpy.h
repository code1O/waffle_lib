#define PY_SSIZE_T_CLEAN
#include <stdio.h>
#include <string.h>
#include <Python.h>


typedef struct {
    PyObject_HEAD
    const char* site_name;
    char (*routes);
    int protocol;
} __network_types;


static int init_network(__network_types* self, PyObject* args, PyObject* kwds){
    const char* site_name;

}

static PyTypeObject network = {
    PyVarObject_HEAD_INIT(NULL, 0)
};
