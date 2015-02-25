#include <Python.h>;

static PyObject* add(PyObject *self, PyObject *args); 
//一定声明为static，把他们限制在这个文件范围里。 几乎所有的参数都是PyObject类型。 在python，每个东西都是object。 

static PyObject* add(PyObject* self, PyObject* args) 
{ 
   int x=0 ; 
   int y=0;
   int z=0;
        if (! PyArg_ParseTuple(args, "i|i", &x, &y))
                return NULL;
        /*第一个参数是self，这个是python用的， 每个函数都要有。我们暂时不管。args是一个参数列表。她把所有的参数都整合成一个string。所以 
        我们需要从这个string里来解析我们的参数。PyArg_ParseTuple来完成这个任务。第一个参数是args， 就是我们要转换的参数。第二个是格式符号。
        “s”代表是个string。 从args里提取一个参数就写"s", 两个的话就写"s|s", 如果是一个string，一个int，就写"s|i", 和printf差不多。第三个
        参数就是提取出来的参数放置的真正位置。必须传递这个参数的地址。对于add， 他将提取两个参数。分别是x和y。*/
z=x+y;
return Py_BuildValue("i", z);
    /*调用完之后我们需要返回结果。这个结果是c的type或者是我们自己定义的类型。必须把他转换成PyObject， 让python认识。这个用Py_BuildValue 
        来完成。他是PyArg_ParseTuple的逆过程。他的第一个参数和PyArg_ParseTuple的第二个参数一样， 是个格式化符号。第三个参数 
        是我们需要转换的参数。Py_BuildValue会把所有的返回只组装成一个tutple给python。*/
} 

static PyMethodDef addMethods[] =
{ 
   {"add",  add, METH_VARARGS, "Execute a shell command."}, 
   {NULL, NULL, 0, NULL}
}; 
/*这个是一个c的结构。他来完成一个映射。 我们需要把我们扩展的函数都映射到这个表里。表的第一个字段是python真正认识的。是python 
里的方法名字。 第二个字段是python里的这个方法名字的具体实现的函数名。 在python里调用add， 真正执行的是用c写的add函数。
第三个字段是METH_VARARGS， 他告诉python，add是调用c函数来实现的。第四个字段是这个函数的说明。如果你在python里来help这个函数，
将显示这个说明。相当于在python里的函数的文档说明。*/

PyMODINIT_FUNC initadd() 
{ 
       Py_InitModule("add", addMethods); 
} 
/*注意，这个函数的名字不能改动。 必须是init+模块名字。 我们的模块名字是add。所以这个函数是initadd()。
这样python在导入add 的模块时候，才会找到这个函数，并调用。这个函数调用Py_InitModule来将模块名字和映射表结合在一起。 
他表示，add这个模块使用addMethods这个映射表。python应该这样导入我们的module的.*/