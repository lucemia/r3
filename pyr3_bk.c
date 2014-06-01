#include <Python.h>
#include "r3.h"
#include "r3_str.h"
#include "str_array.h"

// http://stackoverflow.com/questions/5734016/how-can-we-pass-a-c-structure-to-python
// https://docs.python.org/2/distutils/setupscript.html
// https://hackpad.com/r3-Python-Y0aBkj2VCae
typedef struct {
    PyObject_HEAD
    node* node;
} r3_TrieObject;

static PyTypeObject r3_TrieType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "r3.Trie",             /*tp_name*/
    sizeof(r3_TrieObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    Trie_dealloc,                /*tp_dealloc*/
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
    Py_TPFLAGS_DEFAULT,        /*tp_flags*/
    "Noddy objects",           /* tp_doc */
    0,                     /* tp_traverse */
    0,                     /* tp_clear */
    0,                     /* tp_richcompare */
    0,                     /* tp_weaklistoffset */
    0,                     /* tp_iter */
    0,                     /* tp_iternext */
    Trie_methods,             /* tp_methods */
    Trie_members,             /* tp_members */
    0,                         /* tp_getset */
    0,                         /* tp_base */
    0,                         /* tp_dict */
    0,                         /* tp_descr_get */
    0,                         /* tp_descr_set */
    0,                         /* tp_dictoffset */
    (initproc)Trie_init,      /* tp_init */
    0,                         /* tp_alloc */
    Trie_new,                 /* tp_new */
};

static void
Trie_dealloc(Trie * self) {
    r3_tree_free(self.node);
    self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
Trie_new(PyObject* type, PyObject* args, PyObject* kwds) {
    Trie *self;

    self = (Trie *)type->tp_alloc(type, 0);
    if (self != NULL) {
        // TODO: cap
        self->node = r3_tree_create(100);
    }

    return (PyObject *)self;
}


static PyMethodDef Trie_methods[] = {
    // {"fib", fib, METH_VARARGS, "Calculate the Fibonacci numbers."},
    {NULL, NULL, 0, NULL}
};


static PyMethodDef module_methods[] = {
    {NULL}  /* Sentinel */
};


#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

PyMODINIT_FUNC initr3(void) {
    PyObject* m;
    r3_TrieType.tp_new = PyType_GenericNew;
    if (PyType_Ready(&r3_TrieType) < 0)
        return;

    m = Py_InitModule3("r3", module_methods,
                       "Example module that creates an extension type.");

    Py_INCREF(&r3_TrieType);
    PyModule_AddObject(m, "Trie", (PyObject *)&r3_TrieType);
}
