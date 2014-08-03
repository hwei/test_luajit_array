Test Luajit Array
=================

FFI array VS table array VS C API array in Luajit.

Result
------

```
➜  src git:(master) ✗ ./luajit ~/git/test_luajit_array/test_array.lua
sum is 2.2517997801308e+15
test_ffi elapsed 0.410000
sum is 2.2517998472397e+15
test_table elapsed 0.830000
sum is 2.2517997801308e+15
test_c elapsed 11.580000
➜  src git:(master) ✗ ./luajit -joff ~/git/test_luajit_array/test_array.lua
sum is 2.2517997801308e+15
test_ffi elapsed 11.210000
sum is 2.2517998472397e+15
test_table elapsed 2.510000
sum is 2.2517997801308e+15
test_c elapsed 12.350000
```

Conclusion
----------

* Use FFI, if JIT is available.
* Use table, if JIT is not available.
* If not sure whether JIT is available, stick to table.
* Never implement array with userdata.
