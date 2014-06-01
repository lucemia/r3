#include <Python.h>
#include "structmember.h"
#include "r3.h"
#include "r3_str.h"
#include "str_array.h"

typedef struct {
    PyObject_HEAD
    node *root;
} R3Tree;

static void
R3Tree_dealloc(R3Tree* self)
{
    if(self->root != NULL) {
      r3_tree_free(self->root);
    }
    self->root = NULL;
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject *
R3Tree_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
    R3Tree *self;

    self = (R3Tree *)type->tp_alloc(type, 0);
    if (self != NULL) {
        self->root = r3_tree_create(255);
    }

    return (PyObject *)self;
}

static int
R3Tree_init(R3Tree *self, PyObject *args, PyObject *kwds)
{
    // TODO: may need to add init here
    return 0;
}

static PyMemberDef R3Tree_members[] = {
    // {"number", T_INT, offsetof(R3Tree, number), 0,
    //  "R3Tree number"},
    {NULL}  /* Sentinel */
};

static PyObject *
R3Tree_insert_path(R3Tree* self, PyObject *args, PyObject *kwds)
{
  //http://stackoverflow.com/questions/9896032/how-to-get-a-char-from-a-pyobject-which-points-to-a-string
    PyObject* path = NULL, *data = NULL;

    static char *kwlist[] = {"path", "data", NULL};

    if (! PyArg_ParseTupleAndKeywords(args, kwds, "|OOi", kwlist,
                                      &path, &data))
        return NULL ;

    if (path == NULL) {
        PyErr_SetString(PyExc_AttributeError, "path");
        return NULL;
    }
    if (data == NULL) {
        PyErr_SetString(PyExc_AttributeError, "data");
        return NULL;
    }

    PyObject* objectsRepresentation = PyObject_Repr(path);
    const char* s = PyString_AsString(objectsRepresentation);

    r3_tree_insert_path(self->root, s, data);

    return NULL;
}

static PyObject*
R3Tree_insert_pathl(R3Tree* self, PyObject* args, PyObject *kwds) {

}

static PyObject*
R3Tree_compile(R3Tree* self) {
  r3_tree_compile(self->root);
}

static PyObject*
R3Tree_matchl(R3Tree* self) {

}



static PyMethodDef R3Tree_methods[] = {
    {"insert_path", (PyCFunction)R3Tree_insert_path, METH_NOARGS,
     "Return the name, combining the first and last name"
    },
    {NULL}  /* Sentinel */
};

static PyGetSetDef R3Tree_getseters[] = {
    {NULL}  /* Sentinel */
};

static PyTypeObject R3TreeType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "R3Tree.R3Tree",             /*tp_name*/
    sizeof(R3Tree),             /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)R3Tree_dealloc, /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "R3Tree objects",           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    R3Tree_methods,             /* tp_methods */
    R3Tree_members,             /* tp_members */
    R3Tree_getseters,           /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)R3Tree_init,      /* tp_init */
    0,                         /* tp_alloc */
    R3Tree_new,                 /* tp_new */
};

static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC  /* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC
initpyr3(void)
{
    PyObject* m;

    if (PyType_Ready(&R3TreeType) < 0)
        return;

    m = Py_InitModule3("R3Tree", module_methods,
                       "Example module that creates an extension type.");

    if (m == NULL)
      return;

    Py_INCREF(&R3TreeType);
    PyModule_AddObject(m, "R3Tree", (PyObject *)&R3TreeType);
}
