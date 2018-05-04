In this tutorial we will create a Psi4 plugin that computes the MP2 energy using the spin orbital formalism

Create a new plugin with support for integrals transformed to the MO basis

```
> psi4 --plugin-name mp2so_plug --plugin-template mointegrals
```

Next, change directory and generate the CMake command to compile the plugin
```
> cd mp2so_plug
> psi4 --plugin-compile
cmake -C /Users/fevange/anaconda3/envs/p4env/share/cmake/psi4/psi4PluginCache.cmake -DCMAKE_PREFIX_PATH=/Users/fevange/anaconda3/envs/p4env .
```
and execute the command `cmake -C ...` to compile the plugin.
