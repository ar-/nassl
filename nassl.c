#include <Python.h>

#include <openssl/ssl.h>
#include <openssl/rand.h>

#include "nassl_SSL_CTX.h"
#include "nassl_SSL.h"




static PyMethodDef nassl_methods[] = {
    {NULL}  /* Sentinel */
};

#ifndef PyMODINIT_FUNC	/* declarations for DLL import/export */
#define PyMODINIT_FUNC void
#endif
PyMODINIT_FUNC initnassl(void) {
    PyObject* m;

    // Initialize OpenSSL
    SSL_library_init();
    SSL_load_error_strings();

    // Check OpenSSL PRNG
    if(RAND_status() != 1) {
        PyErr_SetString(PyExc_EnvironmentError, "OpenSSL PRNG not seeded with enough data");
        return;
    }


    // Initalize the module
    m = Py_InitModule3("nassl", nassl_methods,
                       "Example module that creates an extension type.");

    // nassl.SSL_CTX class
    module_add_SSL_CTX(m);

    // nassl.SSL class
    module_add_SSL(m);

}
