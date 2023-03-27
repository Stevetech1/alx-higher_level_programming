Untitled document
mkdir 0x05-python-exceptions


cd 0x05-python-exceptions


echo '0x05-python-exceptions' > README.md



vi 0-safe_print_list.py


#!/usr/bin/python3



def safe_print_list(my_list=[], x=0):

    total = 0

    for i in range(x):

        try:

            print("{}".format(my_list[i]), end="")

            total += 1

        except IndexError:

            break

    print("")

    return (total)





vi 1-safe_print_integer.py


#!/usr/bin/python3



def safe_print_integer(value):

    try:

        print("{:d}".format(value))

        return (True)

    except (TypeError, ValueError):

        return (False)


2-main.py



vi 2-safe_print_list_integers.py


#!/usr/bin/python3



def safe_print_list_integers(my_list=[], x=0):

    ret = 0

    for i in range(0, x):

        try:

            print("{:d}".format(my_list[i]), end="")

            ret += 1

        except (ValueError, TypeError):

            continue

    print("")

    return (ret)





vi 3-safe_print_division.py


#!/usr/bin/python3



def safe_print_division(a, b):

    try:

        div = a / b

    except (TypeError, ZeroDivisionError):

        div = None

    finally:

        print("Inside result: {}".format(div))

    return (div)





vi 4-list_division.py


#!/usr/bin/python3



def list_division(my_list_1, my_list_2, list_length):

    new_list = []

    for i in range(0, list_length):

        try:

            div = my_list_1[i] / my_list_2[i]

        except TypeError:

            print("wrong type")

            div = 0

        except ZeroDivisionError:

            print("division by 0")

            div = 0

        except IndexError:

            print("out of range")

            div = 0

        finally:

            new_list.append(div)

    return (new_list)





vi 5-raise_exception.py


#!/usr/bin/python3

def raise_exception():

    raise TypeError





vi 6-raise_exception_msg.py


#!/usr/bin/python3

def raise_exception_msg(message=""):

    raise NameError(message)





vi 100-safe_print_integer_err.py


#!/usr/bin/python3

import sys



def safe_print_integer_err(value):

    try:

        print("{:d}".format(value))

        return (True)

    except (TypeError, ValueError):

        print("Exception: {}".format(sys.exc_info()[1]), file=sys.stderr)

        return (False)







vi 101-safe_function.py


#!/usr/bin/python3


import sys



def safe_function(fct, *args):

    try:

        result = fct(*args)

        return (result)

    except Exception as i:

        print("Exception: {}".format(sys.exc_info()[1]), file=sys.stderr)

        return (None)






vi 102-magic_calculation.py


#!/usr/bin/python3



def magic_calculation(a, b):

    result = 0

    for i in range(1, 3):

        try:

            if i > a:

                raise Exception('Too far')

            else:

                result += a ** b / i

        except Exception:

            result = b + a

            break

    return (result)




vi 103-python.c


#include <Python.h>


void print_python_list(PyObject *p);

void print_python_bytes(PyObject *p);

void print_python_float(PyObject *p);


/**

 * print_python_list - Prints basic info about Python lists.

 * @p: A PyObject list object.

 */

void print_python_list(PyObject *p)

{

        Py_ssize_t size, alloc, i;

        const char *type;

        PyListObject *list = (PyListObject *)p;

        PyVarObject *var = (PyVarObject *)p;


        size = var->ob_size;

        alloc = list->allocated;


        fflush(stdout);


        printf("[*] Python list info\n");

        if (strcmp(p->ob_type->tp_name, "list") != 0)

        {

                printf("  [ERROR] Invalid List Object\n");

                return;

        }


        printf("[*] Size of the Python List = %ld\n", size);

        printf("[*] Allocated = %ld\n", alloc);


        for (i = 0; i < size; i++)

        {

                type = list->ob_item[i]->ob_type->tp_name;

                printf("Element %ld: %s\n", i, type);

                if (strcmp(type, "bytes") == 0)

                        print_python_bytes(list->ob_item[i]);

                else if (strcmp(type, "float") == 0)

                        print_python_float(list->ob_item[i]);

        }

}


/**

 * print_python_bytes - Prints basic info about Python byte objects.

 * @p: A PyObject byte object.

 */

void print_python_bytes(PyObject *p)

{

        Py_ssize_t size, i;

        PyBytesObject *bytes = (PyBytesObject *)p;


        fflush(stdout);


        printf("[.] bytes object info\n");

        if (strcmp(p->ob_type->tp_name, "bytes") != 0)

        {

                printf("  [ERROR] Invalid Bytes Object\n");

                return;

        }


        printf("  size: %ld\n", ((PyVarObject *)p)->ob_size);

        printf("  trying string: %s\n", bytes->ob_sval);


        if (((PyVarObject *)p)->ob_size >= 10)

                size = 10;

        else

                size = ((PyVarObject *)p)->ob_size + 1;


        printf("  first %ld bytes: ", size);

        for (i = 0; i < size; i++)

        {

                printf("%02hhx", bytes->ob_sval[i]);

                if (i == (size - 1))

                        printf("\n");

                else

                        printf(" ");

        }

}


/**

 * print_python_float - Prints basic info about Python float objects.

 * @p: A PyObject float object.

 */

void print_python_float(PyObject *p)

{

        char *buffer = NULL;


        PyFloatObject *float_obj = (PyFloatObject *)p;


        fflush(stdout);


        printf("[.] float object info\n");

        if (strcmp(p->ob_type->tp_name, "float") != 0)

        {

                printf("  [ERROR] Invalid Float Object\n");

                return;

        }


        buffer = PyOS_double_to_string(float_obj->ob_fval, 'r', 0,

                        Py_DTSF_ADD_DOT_0, NULL);

        printf("  value: %s\n", buffer);

        PyMem_Free(buffer);

}


