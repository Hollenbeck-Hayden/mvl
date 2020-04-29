# mvl
Mathematical Vector Library in C++

Current Implementation Plan:
The entire project is based of the Matrix class. Vector and SMatrix classes
are just typedefs of the Matrix class to the appropriate restrictions. Methods
specific to these objects will be declared in the namespace scope. Thus conversion
is merely a renaming for the convenience of the user, rather than actual
compile time changing of the interface.

__Pitchfork branch TODO__
 - Add testing setup (Catch)
 - Add GitHub actions
 - Code coverage
 - Code formatting
 - Sanitizing, linting, memory checks
 - Support for GCC, LLVM compilers

__Main branch TODO__
 - Finish affine library
 - Documentation (DOxygen)
 - Speed testing
 - Memory testing
