Create a new plugin with support for integrals transformed to the MO basis

`psi4 --plugin-name mp2so_plug --plugin-template mointegrals`

Next, change directory and generate the CMake command to compile the plugin with the 

`cd mp2so_plug`

```psi4 --plugin-compile```

