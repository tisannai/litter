# Litter - Miscellaneous functions

Litter is a collection of functions that belong to the miscellaneous
category.


## Litter API documentation

See Doxygen documentation. Documentation can be created with:

    shell> doxygen .doxygen


## Examples

All functions and their use is visible in tests. Please refer `test`
directory for testcases.


## Building

Ceedling based flow is in use:

    shell> ceedling

Testing:

    shell> ceedling test:all

User defines can be placed into `project.yml`. Please refer to
Ceedling documentation for details.


## Ceedling

Litter uses Ceedling for building and testing. Standard Ceedling files
are not in GIT. These can be added by executing:

    shell> ceedling new litter

in the directory above Litter. Ceedling prompts for file
overwrites. You should answer NO in order to use the customized files.
